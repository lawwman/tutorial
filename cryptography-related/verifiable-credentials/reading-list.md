- [zero knowledge proof](https://en.wikipedia.org/wiki/Zero-knowledge_proof)
- [verifiable credentials primer](https://www.w3.org/TR/vc-data-model/)
- [have not read yet](https://www.lfph.io/wp-content/uploads/2021/02/Verifiable-Credentials-Flavors-Explained.pdf)

@context: https://www.w3.org/2018/credentials/v1


# [Notes from the Evernym blog on BBS+](https://www.evernym.com/blog/bbs-verifiable-credentials/)

Evernym developed [anoncreds](https://github.com/hyperledger/ursa/blob/main/libursa/docs/anoncreds-design.md) based on Camenisch-Lysyanskaya signatures (CL sigs are based on RSA).

it supports:
- **selective disclosure**
- **signature blinding**
  - this allows the issuer’s signature, which is a unique value and therefore a correlating factor, to be randomized before it is shared with a verifier.
- **predicate proofs**
  - these allow hidden values to be used in operations with a value provided by the verifier. For example, predicates can be used to prove that the holder’s bank account balance is above a certain threshold, without revealing the balance.
- **link secrets**
- **revocation capability**

Code is open-sourced on HyperLedger.

Evernym then worked with Sovrin on:
- Rich Schemas to:
  - bring the open-sourced code into compliance with VC data model.
  - use json-ld
- anoncred 2.0
  - discovered BBS+
  - used [Bulletproofs](https://crypto.stanford.edu/bulletproofs/)

Both Rich Schemas and anoncred 2.0 did not produce much results.

MATTR then announced BBS+ LD-proofs:
- compatible with VC data model
- BBS+
- using json-ld
- They let go of ZKP predicates