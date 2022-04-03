# Thoughts when reading [bitcoin whitepaper](https://bitcoin.org/bitcoin.pdf):

# 1. Introduction
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


# 2. Transactions
`We define an electronic coin as a chain of digital signatures.`

*Basically, an ordered list of owners (represented by signatures)*

Lets say I have a transaction from a giver to a receiver involving an `electronic coin`. What will that transaction look like?

- transaction = `Receiver Public Key` + (hash of previous transaction) + signature
- transaction signature = signed( hash( `Receiver Public Key` + `hash of previous transaction` ), `Giver Private Key` )

*digitally signed via publickey-privatekey pair*

Anyone can use the Giver's public key to verify that he did intend to pay the Receiver. How? Because the signature contains Receiver's key. If the signature is verified, only the Giver could have signed it (Assuming the Giver takes good care of his secrets...)

Above system is flawed. The Giver could use his private key again to sign the same `hash of previous transaction` away to another receiver.

How do we resolve this without a single organisation managing all transactions?
- Transactions must be publicly announced. Anyone can look into the ledger.
- we need a system for participants to agree on a single history of the order in which they were received. The receiver needs proof that at the time of each transaction, the majority of nodes agreed it was the first received.

# 3. Timestamp Server
How do we achieve this "single history"? We have a `single chain` made up of `hashes` of `blocks` of `items`. More specifically, we incorporate the `hash` of the previous `block` in the next upcoming `hash` of `blocks`. Because we use `hashes`, if any detail about any item changes, the `hash` changes. And the `hash` of ALL the subsequent `blocks` change. Hence... you can't really change data once they enter this chain.


# 4. Proof-of-work
*Pretty straight forward this one. We need a way to "lock" transactions in time. A hash-based method works.*

*`The proof-of-work involves scanning for a value that when hashed, such as with SHA-256, the
hash begins with a number of zero bits. The average work required is exponential in the number
of zero bits required and can be verified by executing a single hash.`*

I guess a block would look like this?:
- block = (prev hash) + nonce + transaction_1 + transaction_2 + ...

*Take note that transaction_1 itself would be = [ `(receiver/owner's public key)`, `(hash of previous transaction)`, `signature*` ]


# 5. Network

## Steps
1. New transactions are broadcast to all nodes.
2. Each node collects new transactions into a block.
3. Each node works on finding a difficult proof-of-work for its block.
4. When a node finds a proof-of-work, it broadcasts the block to all nodes.
5. Nodes accept the block only if all transactions in it are valid and not already spent.
6. Nodes express their acceptance of the block by working on creating the next block in the chain, using the hash of the accepted block as the previous hash.

## Gotchas
- Nodes consider longest chain to be correct (will keep extending it)
- If nodes receive different versions of next block
  - there will be many "branches" as each version is valid.
  - each branch is kept in view.
  - Tie breaker comes when one branch becomes longer than the rest. That branch will become the main one.

# 6. Incentive
- First transaction of a block is a new coin given to miner. Incentive to support the network.
- Transaction fee. If output value of transaction < input value, the difference is a transaction fee.
- Once a predetermined number of coins have entered circulation, the incentive can transition entirely to transaction fees and be completely inflation free

## Honesty
Incentive = encourage nodes to be honest. For an attacker, its more profitable to play by the rules, such rules that favour him with more new coins, than to undermine the system and the validity of his own wealth.

# 7. Reclaiming Disk Space
*Very cool! Did not expect to see Merkle Trees used here! Read about that in DynamoDB white paper :)*

As seen previously:
- block = (prev hash) + nonce + transaction_1 + transaction_2 + ...

More specifically, the nonce is used to create a hash with set number of 0s. Another way to view it is:
- block = hash( prev hash + nonce + `root hash of transactions` ) + transactions.

*block hash is also referred to as the block header*.

## What is Root hash of transactions
Note that we don't actually put all the `transaction` in the block hash. We hash transactions in a merkle tree:
- leaves = actual transactions
- every other node is just a hash of the children

*`Once the latest transaction in a coin is buried under enough blocks, the spent transactions before it can be discarded to save disk space. To facilitate this without breaking the block's hash, transactions are hashed in a Merkle Tree`*


# 8. Simplified Payment Verification
> I understood more when reading ETH Whitepaper.

`It is possible to verify payments without running a full network node. A user only needs to keep a copy of the block headers of the longest proof-of-work chain...`

Basically, you don't need to download the whole chain's data. You just need the block headers. Once you have the block header, you can then download the merkle branch for JUST THAT BLOCK! Don't need to download the merkle trees for EVERY block. How convenient.


# 9. Combining and Splitting Values
> This seemed more important after reading ETH Whitepaper...

My understanding after reading both whitepapers is that BTC is very rigid. If you received 2BTC and 3BTC, you can't just pick out 1BTC or 4BTC to send to someone else. You need a `transaction` that accepts multiple inputs. Say you have to send 4BTC, you would need a transaction that receives 2BTC and 3BTC, send 4BTC to destination then send 1BTC back to yourself.

Point is, that extra 1BTC has to be part of the process. You can't just send 4 only.

# 10. Privacy
Although all transactions are public, but public keys (your addresses) are anonymous.

As an additional layer, each transaction creates a new key pair (can't be linked to common owner).

# For the rest (No comments)
ETH whitepaper provides another interesting look into BTC as a state transition system!
