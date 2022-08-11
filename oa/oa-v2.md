## raw doc will have the fields as meta data:
- $template
  - name
  - type: "EMBEDDED_RENDERER"
  - url: the renderer url
- issuers (array)... each object contains the fields:
  - name
  - id: the `did:ethr` e.g. "did:ethr:0xaCc51f664D647C9928196c4e33D46fd98FDaA91D"
  - revocation
  - identityProof
    - type: DNS-DID
    - location: domain the issuer owns
    - key: also the `did:ethr` did.

plus the actual fields we want in the docs.

raw docs is then salted. lets call this `salted-docs`.

## salting
arrays and objects are preserved. primitives are transformed:
1. all primitives to string
2. all primitive strings to `<uuid()>:<primitive>`

## transform
new document is created with 2 fields, `version` and `data`.

- version: `https://schema.openattestation.com/2.0/schema.json` or `https://schema.openattestation.com/3.0/schema.json`
- data: { ...`salted-docs` }


## digest
1. get array of hashes from `document.privacy.obfuscatedData`
2. flatley flatten `document.data` into an array.
3. combine both arrays of hashes and sort.
4. finally, keccak256(JSON.stringify(sortedHashes))

### flatley flatten:
meaning that nested object or array gets flatten to depth of 1
```javascript
// example
{
  'key1.keyA': 'valueI',
  'key2.keyB': 'valueII',
  'key3.a.b.c': 2
}
```

### merkle tree derivation
- receives a list of hashes (in buffer form)
- list of hashes gets sorted
- 2d array of `layers` created. layers[0] = sorted list of hashes
- while last item of `layers` is an arr with length > 1:
  - grab the last item of `layers`, which is an arr.
  - for every 0, 2, 4... even `idx`, combine it with the elem of `idx + 1`.
    - if `idx + 1` does not exist, return `idx`.
    - combine by: sort and join, hash and change to buffer
- each item in `layer` represents all the nodes in one level of the merkle tree

### merkle proof derivation
- requires the `layers` and `index` of node we want the proof for.
- gets all the pairs required to obtain the merkle root hash.
- returns as a list of nodes required


## signature
document now has:
- version: `https://schema.openattestation.com/2.0/schema.json` or `https://schema.openattestation.com/3.0/schema.json`
- data: { ...`salted-docs` }
- signature (an object with the following fields)
  - type: "SHA3MerkleProof"
  - targetHash: `digest`
  - merkleRoot: `digest`
  - proof: [] // if its a singular raw document. no need for merkle proof here


For wrapping an object, `signature` field is added. For signing an object, `proof` field is added.

document would have:
- version
- data
- signature
- proof (an object with the following fields)
  - type: "OpenAttestationSignature2018",
  - created: "2022-08-10T06:05:06.438Z",
  - proofPurpose: "assertionMethod",
  - verificationMethod: "did:ethr:0xaCc51f664D647C9928196c4e33D46fd98FDaA91D#controller",
  - signature: signature of merkle root with private key