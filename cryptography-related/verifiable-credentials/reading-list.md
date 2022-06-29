- [have not read yet](https://www.lfph.io/wp-content/uploads/2021/02/Verifiable-Credentials-Flavors-Explained.pdf)

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

# [Notes from Evernym blog on Link secrets](https://www.evernym.com/blog/how-does-a-verifier-know-the-credential-is-yours/)

A link secret is a random number that is "wrapped". This wrapping is known as a [cryptographic commitment](https://en.wikipedia.org/wiki/Commitment_scheme).

A cryptographic `commitment` allows someone to "commit" to a value. They can then only share the `commitment` without revealing the value. They can then choose to reveal the value.

The holder of the link secret can also `blind` the `commitment`. The same `commitment`s will not have any relation to one another once `blinded`.

why use link secrets?:
- only the holder knows the secret. verifiers are sure that the individual presenting the credential is legit
- link secret is same across all credentials of holder. can combine several credentials into single proof.

because of `blinding`, it is much better for privacy than using DIDs. *Using a DID for the holder or subject of a credential is a bit like giving every verifier the same super-cookie that they can use to track everything you do.*
