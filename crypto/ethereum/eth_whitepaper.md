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
- create a protocol for building decentralised applications
- useful for situations requiring:
  - rapid development time
  - security for small and rarely used applications
  - ability of different applications to very efficiently interact

it is a blockchain with a built-in `Turing-complete programming language`, allowing anyone to write `smart contracts` and `decentralized applications` where they can create their own arbitrary rules for ownership, transaction formats and state transition functions.

## Ethereum Accounts
In Ethereum, the state is made up of objects called "accounts", each with 20-byte address. It contains:
- The `nonce`, a counter used to make sure each transaction can only be processed once
- The account's current `ether balance`
- The account's `contract code`, if present
- The account's `storage` (empty by default)

There are two types of accounts:
- `externally owned accounts`: controlled by private keys
  - has no code
  - one can send messages from an externally owned account by creating and signing a transaction
- `contract accounts`: controlled by their contract code
  - every time the contract account receives a message its code activates, allowing it to read and write to internal storage and send other messages or create contracts in turn.

`state transitions` are direct transfers of value and information between `accounts`. `Ether` is the main internal crypto-fuel of Ethereum, and is used to pay transaction fees.

Note that "contracts" in Ethereum should not be seen as something that should be "fulfilled" or "complied with"; rather, they are more like "autonomous agents" that live inside of the Ethereum execution environment, always executing a specific piece of code when "poked" by a message or transaction, and having direct control over their own ether balance and their own key/value store to keep track of persistent variables.

## Messages and Transactions

`transaction`: signed data package that stores a message to be sent from an `externally owned account`. Contains:
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
- A `STARTGAS` value

message vs transaction:
- message produced by `contract`. transaction produced by `externally owned account`.
- transactions are recorded into each block in the blockchain. messages are not.

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

# Applications

## Token systems
tokens can represent:
- USD, gold
- company stocks
- smart property
- coupons
- even point systems used to incentivise

Token systems are easy to implement in Ethereum since ETH or tokens are just... units.

Basic serpent code to implement `token system`
```
def send(to, value):
    if self.storage[msg.sender] >= value:
        self.storage[msg.sender] = self.storage[msg.sender] - value
        self.storage[to] = self.storage[to] + value
```

*Theoretically, Ethereum-based token systems acting as sub-currencies can potentially include another important feature that on-chain Bitcoin-based meta-currencies lack*: the ability to pay transaction fees directly in that currency. The way this would be implemented is that the contract would maintain an ether balance with which it would refund ether used to pay fees to the sender, and it would refill this balance by collecting the internal currency units that it takes in fees and reselling them in a constant running auction. Users would thus need to "activate" their accounts with ether, but once the ether is there it would be reusable because the contract would refund it each time.

## Financial derivatives and Stable-Value Currencies
smart contracts can be coded to hold ether and hedge against ether's volatility (w.r.t to USD). The contract would need to know the value of ETH/USD, probably provided by another party `data feed contract`.

The contract could look like this:
1. Wait for party A to input 1000 ether.
2. Wait for party B to input 1000 ether.
3. Record the USD value of 1000 ether, calculated by querying the `data feed contract`, in storage, say this is $x.
After 30 days, allow A or B to "reactivate" the contract in order to send $x worth of ether (calculated by querying the `data feed contract` again to get the new price) to A and the rest to B.

### Problem
Although many users may want the security and convenience of dealing with cryptographic assets, they many not wish to face that prospect of losing 23% of the value of their funds in a single day.

### Common solution...
Up until now, the most commonly proposed solution has been issuer-backed assets; the idea is that an issuer creates a sub-currency in which they have the right to issue and revoke units, and provide one unit of the currency to anyone who provides them (offline) with one unit of a specified underlying asset (eg. gold, USD). The issuer then promises to provide one unit of the underlying asset to anyone who sends back one unit of the crypto-asset. This mechanism allows any non-cryptographic asset to be "uplifted" into a cryptographic asset, provided that the issuer can be trusted.

In practice, however, issuers are not always trustworthy, and in some cases the banking infrastructure is too weak, or too hostile, for such services to exist. Financial derivatives provide an alternative. Here, instead of a single issuer providing the funds to back up an asset, a decentralized market of speculators, betting that the price of a cryptographic reference asset (eg. ETH) will go up, plays that role. Unlike issuers, speculators have no option to default on their side of the bargain because the hedging contract holds their funds in escrow. Note that this approach is not fully decentralized, because a trusted source is still needed to provide the price ticker, although arguably even still this is a massive improvement in terms of reducing infrastructure requirements (unlike being an issuer, issuing a price feed requires no licenses and can likely be categorized as free speech) and reducing the potential for fraud.

## Identity and Reputation Systems
Blockchain to provide a name registration system, where users can register their names in a public database alongside other data. For e.g. a DNS system.

## Decentralized file storage

### current solution and problems
Over the past few years, there have emerged a number of popular online file storage startups, the most prominent being Dropbox, seeking to allow users to upload a backup of their hard drive and have the service store the backup and allow the user to access it in exchange for a monthly fee. However, at this point the file storage market is at times relatively inefficient; a cursory look at various existing solutions shows that, particularly at the "uncanny valley" 20-200 GB level at which neither free quotas nor enterprise-level discounts kick in, monthly prices for mainstream file storage costs are such that you are paying for more than the cost of the entire hard drive in a single month.

### application of ETH
Ethereum contracts can allow for the development of a decentralized file storage ecosystem, where individual users can earn small quantities of money by renting out their own hard drives and unused space can be used to further drive down the costs of file storage.

The key underpinning piece of such a device would be what we have termed the "decentralized Dropbox contract". This contract works as follows. First, one splits the desired data up into blocks, encrypting each block for privacy, and builds a Merkle tree out of it. One then makes a contract with the rule that, every N blocks, the contract would pick a random index in the Merkle tree (using the previous block hash, accessible from contract code, as a source of randomness), and give X ether to the first entity to supply a transaction with a simplified payment verification-like proof of ownership of the block at that particular index in the tree. When a user wants to re-download their file, they can use a micropayment channel protocol (eg. pay 1 szabo per 32 kilobytes) to recover the file; the most fee-efficient approach is for the payer not to publish the transaction until the end, instead replacing the transaction with a slightly more lucrative one with the same nonce after every 32 kilobytes.

An important feature of the protocol is that, although it may seem like one is trusting many random nodes not to decide to forget the file, one can reduce that risk down to near-zero by splitting the file into many pieces via secret sharing, and watching the contracts to see each piece is still in some node's possession. If a contract is still paying out money, that provides a cryptographic proof that someone out there is still storing the file.

## Others
- Decentralized Autonomous Organizations
- Savings wallets
- A decentralized data feed
- Cloud computing


# Stop here
Further readings are not meaningful without deeper knowledge. I think its better to cover it in another session.