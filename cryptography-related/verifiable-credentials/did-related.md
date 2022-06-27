- [DID primer](https://w3c-ccg.github.io/did-primer/)
- [DID spec](https://www.w3.org/TR/did-core/)
- [DID methods](https://w3c.github.io/did-spec-registries/#did-methods)
  - [did:web](https://w3c-ccg.github.io/did-method-web/)
  - [did:dns](https://danubetech.github.io/did-method-dns/)
  - [did:key](https://w3c-ccg.github.io/did-method-key/)


DID is an identity. Do not confuse it with Verifiable Credentials. It is an identity.

A DID Document describes the DID.

# did:web
## identifier
web-did = "did:web:" domain-name
web-did = "did:web:" domain-name * (":" path)


## create
register a `domain name`. the DID document will be stored in the `domain name` found in the DID.

```
did:web:w3c-ccg.github.io
 -> https://w3c-ccg.github.io/.well-known/did.json
```

## methods:
- read: reading is simply just looking up the domain name.
- update: just update the json file being stored.
- deactivate: just remove the json or make the domain unavailable


# did:dns
## target system
The set of DNS zone files controlled by the authoritative DNS servers of the domain name that is the method-specific identifier in the DID.

## identifier
dns-did = "did:dns:" domain-name

## create
register a `domain name`. Configuring the domain name's zone file to include Resource Records (RRs) of a certain pattern.

## methods:
- resolve: lookup domain name's RRs that match the condition:
  - `type` of `URI`
  - `name` with pattern: `_<id>._did.<method-specific-id>.`

the `RDATA` field of the URI RR is a `did:key` DID. Resolve the `did:key` to a DID document. This is called the `verification method DID document`.

There is a resolved DID document that contains:
- `id`: the `did:dns` id
- `verificationMethod` from `verification method DID document`
  - `id`
  - `controller`


# did:key
## identifer
did-key-format := did:key:MULTIBASE(base58-btc, MULTICODEC(public-key-type, raw-public-key-bytes))

basically, an encoding of a public key.

Implementers might note that this DID Method is purely generative, requiring no look ups in a registry.
- basically, just like a JWT. Then how to resolve...

## creation
From the public key found in the DID, it alone is enough to create the DID document.

## other methods
`did:key` does not support update and delete.
