main links:
- [oa website](https://www.openattestation.com/)
- [oa architecture decision records (ADR)](https://github.com/Open-Attestation/adr)



# useful ADR
- [why DNS TXT records](https://github.com/Open-Attestation/adr/blob/master/decentralized_identity_proof_DNS-TXT.md)
- [considerations when revoking DID](https://github.com/Open-Attestation/adr/blob/master/did-certificate-revocation.md)
  - to use `Online Certificate Status Protocol` or `Certificate Revocation List`?
- [Proposal for OA V3](https://github.com/Open-Attestation/adr/blob/master/signature-proof-spec/spec.md)
- [Issuing with DID](https://github.com/Open-Attestation/adr/blob/master/issuing_using_did.md)



# TOR
- decentralised rendering
  - other systems should safely ignore this.
  - OA should not throw errors when it is encountered.
- more did methods
- bbs+

OaV3 has a reliance on `openAttestationMetadata`, but according to W3C VC, it should rely on `issuer` more.

