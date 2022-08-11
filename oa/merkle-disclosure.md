JWP encodings for merkle proofs.

- [JWP draft](https://github.com/json-web-proofs/json-web-proofs/blob/main/draft-jmiller-json-web-proof.md)
- [JPA for JWP](https://json-web-proofs.github.io/json-web-proofs/draft-jmiller-json-proof-algorithms.html)
- [JWP for merkle disclosure](https://w3c-ccg.github.io/Merkle-Disclosure-2021/jwp/)

# Transmute implementation

## pre salting before creating merkle tree
- rootNonce: random value
- messageNonce: hash(message + index + rootNonce)
- saltedMember: hash(message + messageNonce)

inputs to creating the merkle tree is arr of saltedMembers

creating of merkle is very similar to OA.

## generating proof for a member of the merkle tree
getting all nodes required to generate root hash. arr of `Sibling`. (object with field `left` or `right`)

## encoding proof / arr of `Sibling`


## membership
```typescript
export type MemberProof = {
  member: Buffer; // this is the message
  proof: BinaryAuditPathAndNonce;
};

// returned from generateMembership
export type FullDisclosureProof = {
  root: Buffer; // this is the merkle root
  nonce: Buffer; // this is the root nonce
  membership: Array<MemberProof>;
};

export type SelectiveDisclosureProof = {
  root: Buffer;
  membership: Array<MemberProof>;
};
```

how can we use it?