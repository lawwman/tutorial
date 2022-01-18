# Thoughts when reading [bitcoin whitepaper](https://bitcoin.org/bitcoin.pdf):

## 1. Introduction
`Completely non-reversible transactions are not really possible, since financial institutions cannot
avoid mediating disputes. The cost of mediation increases transaction costs, limiting the
minimum practical transaction size and cutting off the possibility for small casual transactions,
and there is a broader cost in the loss of ability to make non-reversible payments for nonreversible services.`

*What we want are non-reversible transactions. But institutions may sometimes reverse transactions during disputes?*

`What is needed is an electronic payment system based on cryptographic proof instead of trust,
allowing any two willing parties to transact directly with each other without the need for a trusted
third party. Transactions that are computationally impractical to reverse would protect sellers
from fraud...`

*I guess just another reason that non-reversible transactions are good.*


## 2. Transactions
`We define an electronic coin as a chain of digital signatures.`

*Basically, an ordered list of owners (represented by signatures)*

Lets say I have a transaction between a receiver and a giver involving an `electronic coin`. What will that transaction look like?

- transaction signature = signed( hash( `Receiver Public Key` + `hash of previous transaction` ), `Giver Private Key` )
- transaction = `Receiver Public Key` + (hash of previous transaction) + signature

*digitally signed via publickey-privatekey pair*

Anyone can use the Giver's public key to verify that he did intend to pay the Receiver. How? Because the signature contains Receiver's key. If the signature is verified, only the Giver could have signed it (Assuming the Giver takes good care of his secrets...)

Above system is flawed. The Giver could use his private key again to sign the same `hash of previous transaction` away to another receiver.

How do we resolve this without a single organisation managing all transactions?
- Transactions must be publicly announced. Anyone can look into the ledger.
- we need a system for participants to agree on a single history of the order in which they were received. The receiver needs proof that at the time of each transaction, the majority of nodes agreed it was the first received.

## 3. Timestamp Server (No comments)
No comments


## 4. Proof-of-work
*Pretty straight forward this one. We need a way to "lock" transactions in time. A hash-based method works.*

I guess a block would look like this?: \
block = (prev hash) + nonce + transaction_1 + transaction_2 + ...

*Take note that transaction_1 itself would be = (receiver/owner's public key) + (hash of previous transaction) + signature*


## 5. Network, 6. Incentive (No comments)
No comments


## 7. Reclaiming Disk Space
*Very cool! Did not expect to see Merkle Trees used here! Read about that in DynamoDB white paper :)*


## For the rest (No comments)
No comments
