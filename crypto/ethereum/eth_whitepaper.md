> Thoughts when reading [ethereum whitepaper](https://ethereum.org/en/whitepaper/):

# Introduction to Bitcoin and Existing Concepts

## History
Mechanism behind `proof-of-work` solved 2 problems:
- simple and effective consensus algorithm, allowing nodes in the network to collectively agree on a set of canonical updates to the state of the Bitcoin ledger
- free entry into the consensus process, solving the political problem of deciding who gets to influence the consensus, while simultaneously preventing sybil attacks
  - the weight of a single node in the consensus voting process is proportional to the computing power of the node
  - sybil attacks - attack on network by creating large number of pseudonymous identities and uses them to gain a disproportionately large influence

## Bitcoin As A State Transition System
Think of BTC as a state transition system. There is a `state`, `transaction` and `state transition function`.

In **standard bank**, `state` is balance sheet. `transaction` is request to move $X from A to B. `state transition function` performs the request.

In **BTC**, the `state` is the collection of coins
- technically, coins in this context refers to "unspent transaction outputs" or `UTXO` that have been mined but not spent.
- each UTXO have a denomination and an owner (defined by a 20-byte address which is essentially a cryptographic public key)

In BTC, the `transaction` contains >= 1 `inputs` and >= 1 `outputs`.

each `input` contain a reference to:
- an existing `UTXO`
- signature produced by the private key associated with the owner's address

each `output` containing a new `UTXO` to be added to the state.

In BTC, the `state transition function`, e.g. `APPLY(S,TX) -> S'` can be defined as:
1. for each input in TX:
    1. If referenced UTXO is not in S, return an error.
    2. If signature does not match the owner of the UTXO, return an error.
2. If the sum of the denominations of all input UTXO is less than the sum of the denominations of all output UTXO, return an error.
3. Return S with all input UTXO removed and all output UTXO added.

`Suppose Alice sends 11.7 BTC to Bob. Alice will look for a set of UTXO that she owns that totals up to at least 11.7 BTC. Realistically, Alice will not be able to get exactly 11.7 BTC; e.g. smallest she can get is 6+4+2=12 BTC. She creates a transaction with those three inputs and two outputs. The first output will be 11.7 BTC with Bob's address as its owner, and the second output will be the remaining 0.3 BTC "change", with the owner being Alice herself.`

## Mining
Algorithm for checking if block is valid

1. Check if the previous block referenced by the block exists and is valid.
2. Check that the timestamp of the block is greater than that of the previous block and less than 2 hours into the future
3. Check that the proof-of-work on the block is valid.
4. Let S[0] be the state at the end of the previous block.
5. Suppose TX is the block's transaction list with n transactions. For all i in 0...n-1, set S[i+1] = APPLY(S[i],TX[i]) If any application returns an error, exit and return false.
6. Return true, and register S[n] as the state at the end of this block.

---
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

`transaction`: signed data package that stores a message to be sent from an `externally owned account`.

transactions contain:
- recipient of message
- signature identifying the sender
- amount of ether to transfer from sender -> recipient
- optional data field
- `STARTGAS` value: representing max no. of computational steps the transaction execution is allowed to take.
- `GASPRICE` value: representing the fee the sender pays per computational step.

`STARTGAS` and `GASPRICE` used for anti-denial of service model. Since each computational step has a cost and there is a limit to the total number of steps.

There is also a fee of 5 gas for every byte in the transaction data. The intent of the fee system is to require an attacker to pay proportionately for every resource that they consume, including computation, bandwidth and storage; hence, any transaction that leads to the network consuming a greater amount of any of these resources must have a gas fee roughly proportional to the increment.

`messages`: virtual objects that are never serialised and exist only in the Ethereum execution environment. sent from `contracts` to other `contracts`.

message contains:
- The sender of the message (implicit)
- recipient of message
- amount of ether to transfer alongside the message
- optional data field
- A STARTGAS value

message vs transaction:
- message produced by `contract`. transaction produced by `externally owned account`.

A message is produced when a contract currently executing code executes the CALL `opcode`, which produces and executes a message.

## Ethereum State Transition Function
The Ethereum state transition function, `APPLY(S,TX) -> S'` can be defined as follows:
1. Check if the transaction has:
    1. the right number of values
    2. the signature is valid
    3. nonce matches the nonce in the sender's account. If not, return an error.
2. transaction fee=`STARTGAS`*`GASPRICE`. If `STARTGAS`=1000 and `GASPRICE`=0.01 eth, deduct 1 eth from sender account. Increment the sender's nonce. If sender does not have enough eth, return an error.
3. Initialize GAS=`STARTGAS`, and take off a certain quantity of gas per byte to pay for the bytes in the transaction. *if transaction is 170 bytes and byte-fee is 5, subtract 850 from GAS.*
4. Transfer the transaction value from the sender's account to the receiving account. If the receiving account does not yet exist, create it. If the receiving account is a contract, run the contract's code either to completion or until the execution runs out of gas.
5. If the value transfer failed because the sender did not have enough money, or the code execution ran out of gas, revert all state changes except the payment of the fees, and add the fees to the miner's account.
6. Otherwise, refund the fees for all remaining gas to the sender, and send the fees paid for gas consumed to the miner. REFUND=`REMAINING_GAS`*`GASPRICE`

## Code Execution
The code in Ethereum contracts is written in a low-level, stack-based bytecode language, referred to as "Ethereum virtual machine code" or "EVM code".

The code consists of a series of bytes, where each byte represents an operation.

In general, code execution is an infinite loop that consists of repeatedly carrying out the operation at the current program counter (which begins at zero) and then incrementing the program counter by one, until the end of the code is reached or an error or `STOP` or `RETURN` instruction is detected. The operations have access to three types of space in which to store data:
- The `stack`, a last-in-first-out container to which values can be pushed and popped
- `Memory`, an infinitely expandable byte array
- The contract's long-term `storage`, a key/value store. Unlike stack and memory, which reset after computation ends, storage persists for the long term.

The code can also access the value, sender and data of the incoming message, as well as block header data, and the code can also return a byte array of data as an output.

The formal execution model of EVM code is surprisingly simple. While the Ethereum virtual machine is running, its full computational state can be defined by the tuple (`block_state`, `transaction`, `message`, `code`, `memory`, `stack`, `pc`, `gas`), where block_state is the global state containing all accounts and includes balances and storage.

Examples of operations:
- `ADD` pops two items off the stack and pushes their sum, reduces gas by 1 and increments pc by 1
- `SSTORE` pushes the top two items off the stack and inserts the second item into the contract's storage at the index specified by the first item.

## Blockchain and Mining
The main difference between Ethereum and Bitcoin with regard to the blockchain architecture is that, unlike Bitcoin, Ethereum blocks contain a copy of both the transaction list and the most recent state. Aside from that, two other values, the block number and the difficulty, are also stored in the block. The basic block validation algorithm in Ethereum is as follows:
1. Check if the previous block referenced exists and is valid.
2. Check that the timestamp of the block is greater than that of the referenced previous block and less than 15 minutes into the future
3. Check that the block number, difficulty, transaction root, uncle root and gas limit (various low-level Ethereum-specific concepts) are valid.
4. Check that the proof-of-work on the block is valid.
5. Let `S[0]` be the state at the end of the previous block.
6. Let `TX` be the block's transaction list, with n transactions. For all i in 0...n-1, set S[i+1] = APPLY(S[i],TX[i]). If any applications returns an error, or if the total gas consumed in the block up until this point exceeds the `GASLIMIT`, return an error.
7. Let `S_FINAL` be S[n], but adding the block reward paid to the miner.
8. Check if the Merkle tree root of the state `S_FINAL` is equal to the final state root provided in the block header. If it is, the block is valid; otherwise, it is not valid.

The approach may seem highly inefficient at first glance, because it needs to store the entire state with each block, but in reality efficiency should be comparable to that of Bitcoin. The reason is that the state is stored in the tree structure, and after every block only a small part of the tree needs to be changed. Thus, in general, between two adjacent blocks the vast majority of the tree should be the same, and therefore the data can be stored once and referenced twice using pointers (ie. hashes of subtrees). A special kind of tree known as a "Patricia tree" is used to accomplish this, including a modification to the Merkle tree concept that allows for nodes to be inserted and deleted, and not just changed, efficiently. Additionally, because all of the state information is part of the last block, there is no need to store the entire blockchain history - a strategy which, if it could be applied to Bitcoin, can be calculated to provide 5-20x savings in space.

A commonly asked question is "where" contract code is executed, in terms of physical hardware. This has a simple answer: the process of executing contract code is part of the definition of the state transition function, which is part of the block validation algorithm, so if a transaction is added into block B the code execution spawned by that transaction will be executed by all nodes, now and in the future, that download and validate block B