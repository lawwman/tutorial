# v2
schemaId:
- v2: https://schema.openattestation.com/2.0/schema.json
- v3: https://schema.openattestation.com/3.0/schema.json

stored as `document.version`.


## salting
arrays and objects are preserved. primitives are transformed:
1. all primitives to string
2. all primitive strings to `<uuid()>:<primitive>`

stored as `document.data`.

## validate
validate `document.data` against schemaId chosen.

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

