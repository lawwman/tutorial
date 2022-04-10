# Thoughts when reading [ethereum whitepaper](https://ethereum.org/en/whitepaper/):

# Introduction to Bitcoin and Existing Concepts

## History
Mechanism behind `proof-of-work` solved 2 problems:
- simple and effective consensus algorithm, allowing nodes in the network to collectively agree on a set of canonical updates to the state of the Bitcoin ledger
- free entry into the consensus process, solving the political problem of deciding who gets to influence the consensus, while simultaneously preventing sybil attacks
  - the weight of a single node in the consensus voting process is proportional to the computing power of the node
  - sybil attacks - attack on network by creating large number of pseudonymous identities and uses them to gain a disproportionately large influence

## Bitcoin As A State Transition System
Think of BTC as a state transition system...

- the `state` is the ownership status of all existing BTC.
- the `state transition function` takes a `state` and a `transaction` and outputs a new `state`

In standard bank, `state` is balance sheet. `transaction` is request to move $X from A to B. `state transition function` does the request.

In BTC, the `state` is the collection of coins
- technically, coins in this context refers to "unspent transaction outputs" or `UTXO` that have been mined but not spent.
- each UTXO have a denomination and an owner (defined by a 20-byte address which is essentially a cryptographic public key)

In BTC, the `transaction` contains >= 1 inputs, with each input containing a reference to existing UTXO and a signature produced by the private key associated with the owner's address, and one or more outputs, with each output containing a new UTXO to be added to the state.

In BTC, the `state transition function`, e.g. `APPLY(S,TX) -> S'` can be defined as:
1. for each input in TX:
    1. If referenced UTXO is not in S, return an error.
    2. If signature does not match the owner of the UTXO, return an error.
2. If the sum of the denominations of all input UTXO is less than the sum of the denominations of all output UTXO, return an error.
3. Return S with all input UTXO removed and all output UTXO added.

`Suppose Alice sends 11.7 BTC to Bob. Alice will look for a set of UTXO that she owns that totals up to at least 11.7 BTC. Realistically, Alice will not be able to get exactly 11.7 BTC; e.g. smallest she can get is 6+4+2=12 BTC. She creates a transaction with those three inputs and two outputs. The first output will be 11.7 BTC with Bob's address as its owner, and the second output will be the remaining 0.3 BTC "change", with the owner being Alice herself.`

## Mining
Algorithm for checking if block is valid
```javascript
function isBlockValid() {
    if (!("previous block referenced by the block exists" && "is valid")) return false;
    if (("timestamp of the block is <= previous block timestamp") || ("timestamp < 2 hours into the future")) return false;
    if (!PoW.isValid()) return false;

    let S[0] // state at the end of the previous block
    for (let i = 0; i < transactions.length; i++) {
        S[i + 1] = APPLY(S[i], transactions[i]); // if APPLY throws error, return false
    }
    S[transactions.length] // new state at the end of this block
    return true;

}
```
1. `Note that the state is not encoded in the block in any way; it is purely an abstraction to be remembered by the validating node and can only be (securely) computed for any block by starting from the genesis state and sequentially applying every transaction in every block.`

2. `Additionally, note that the order in which the miner includes transactions into the block matters; if there are two transactions A and B in a block such that B spends a UTXO created by A, then the block will be valid if A comes before B but not otherwise.`

## Merkle Trees
`A protocol known as "simplified payment verification" (SPV) allows for another class of nodes to exist, called "light nodes", which download the block headers, verify the proof-of-work on the block headers, and then download only the "branches" associated with transactions that are relevant to them. This allows light nodes to determine with a strong guarantee of security what the status of any Bitcoin transaction, and their current balance, is while downloading only a very small portion of the entire blockchain.`

## Scripting
Bitcoin protocol actually does facilitate a weak version of a concept of "smart contracts".

UTXO in Bitcoin can be owned not just by a public key, but also by a more complicated script expressed in a simple stack-based programming language. In this paradigm, a transaction spending that UTXO must provide data that satisfies the script.

Indeed, even the basic public key ownership mechanism is implemented via a script:
1. the script takes an elliptic curve signature as input
2. verifies it against the transaction and the address that owns the UTXO, and returns 1 if the verification is successful and 0 otherwise.

Other, more complicated examples:
- a script that requires signatures from two out of a given three private keys to validate ("multisig"). (useful for corporate accounts, secure savings accounts etc)
- a script to pay bounties for solutions to computational problems.
- a script that says something like "this Bitcoin UTXO is yours if you can provide an SPV proof that you sent a Dogecoin transaction of this denomination to me", essentially allowing decentralized cross-cryptocurrency exchange.

Limitations of BTC Scripting:
- BTC Scripting is very limited. E.g: NO LOOPS. This is done to avoid infinite loops during transaction verification; technically we can just repeat the code... but not space-inefficient.
- `BLOCKCHAIN BLINDNESS`: UTXO are blind to blockchain data such as the nonce, the timestamp and previous block hash
- `VALUE BLINDNESS`: UTXO scripts have limited control over amount to be withdrawn
- `LACK OF STATE`: UTXO can either be spent or unspent; there is no opportunity for multi-stage contracts or scripts which keep any other internal state beyond that. This makes it hard to make multi-stage options contracts, decentralized exchange offers or two-stage cryptographic commitment protocols (necessary for secure computational bounties). It also means that UTXO can only be used to build simple, one-off contracts and not more complex "stateful" contracts such as decentralized organizations, and makes meta-protocols difficult to implement. Binary state combined with value-blindness also mean that another important application, withdrawal limits, is impossible.

Don't know too much about it... except that it sucks.

# Ethereum
intent:
- protocol for building decentralised applications
- emphasis on situations requiring:
  - rapid development time
  - security for small and rarely used applications
  - ability of different applications to very efficiently interact

it is a blockchain with a built-in `Turing-complete programming language`, allowing anyone to write `smart contracts` and `decentralized applications` where they can create their own arbitrary rules for ownership, transaction formats and state transition functions.

## Ethereum Accounts
In Ethereum, the state is made up of objects called "accounts".

- An `account` has a 20-byte address.
- `state transitions` are direct transfers of value and information between `accounts`.

An Ethereum `account` contains four fields:
- The `nonce`, a counter used to make sure each transaction can only be processed once
- The account's current `ether balance`
- The account's `contract code`, if present
- The account's `storage` (empty by default)

`Ether` is the main internal crypto-fuel of Ethereum, and is used to pay transaction fees.

There are two types of accounts:
- `externally owned accounts`: controlled by private keys
  - has no code
  - one can send messages from an externally owned account by creating and signing a transaction
- `contract accounts`: controlled by their contract code
  - every time the contract account receives a message its code activates, allowing it to read and write to internal storage and send other messages or create contracts in turn.


Note that "contracts" in Ethereum should not be seen as something that should be "fulfilled" or "complied with"; rather, they are more like "autonomous agents" that live inside of the Ethereum execution environment, always executing a specific piece of code when "poked" by a message or transaction, and having direct control over their own ether balance and their own key/value store to keep track of persistent variables.

## Messages and Transactions
