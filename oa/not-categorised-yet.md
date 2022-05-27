main links:
- [oa website](https://www.openattestation.com/)
- [oa architecture decision records (ADR)](https://github.com/Open-Attestation/adr)

As seen in github readme.md, OA is an `attestation` and `notary` framework for any document types on the blockchain.

[attestation vs notarization](https://www.superiornotaryservices.com/blog/difference-notarization-attestation/):
- **Attestation** happens when a person not involved in a transaction (a third party) “attests” or witnesses the two involved parties sign a document. The third party then signs a statement that he or she saw the two involved parties sign the document, and sometimes verifies the content itself.
- **Notarization** is the act of assuring each of the parties in a transaction that the document they’re signing is authentic. It’s an effort to prevent fraud and ensure that each signer is authentic.

**Some differences**:
- While only a state-commissioned public notary can perform a notarization, anyone can perform an attestation.
- If you only need a witness to sign a document, that’s a simple attestation. Anyone can do it. But if you need to ensure that neither party is defrauding the other, you’ll have to get in touch with a state-commissioned notary

Qn: It's kind of related but I don't get why the terms `attestation` and `notary` are used?



# useful ADR
- [why DNS TXT records](https://github.com/Open-Attestation/adr/blob/master/decentralized_identity_proof_DNS-TXT.md)
- [considerations when revoking DID](https://github.com/Open-Attestation/adr/blob/master/did-certificate-revocation.md)
  - to use `Online Certificate Status Protocol` or `Certificate Revocation List`?
- [Proposal for OA V3](https://github.com/Open-Attestation/adr/blob/master/signature-proof-spec/spec.md)

