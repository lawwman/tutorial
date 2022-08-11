
# v3
- `document["@context"]` = ["https://www.w3.org/2018/credentials/v1", "https://schemata.openattestation.com/com/openattestation/1.0/OpenAttestation.v3.json"]
- `document.version` = SchemaId.v3
- and all the other fields that the input json object T has (T extends `OpenAttestationDocument`)

## salting
generate a `salt` object from the document.

each field in the `salt` obj
- represents primitive in the document
  - `path`: `field1.nestedfield1` <- example
  - `value`: 32 bytes random


## digest
for each field in the `salt` obj
- generate a hash via: `hash(stringify( { [salt.path]: <32 random bytes>:<actual value to that path> } ))`

1. The above results in an array of hashes.
2. concat with array of hashes of obfuscated data and sort
3. finally, keccak256(JSON.stringify(sortedHashes))

