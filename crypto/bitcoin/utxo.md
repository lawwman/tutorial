# how I reached the point where I needed to write this...
I didn't even see this term in the BTC whitepaper. Came across it many times when reading up on double spending, ETH whitepaper, BTC Scripting etc...

Apparently... THIS IS IMPT! LISTEN UP!

# Prereq
- BTC Whitepaper
- The BTC portion of the ETH whitepaper. Make sure you read the transactions part

# Prior understandings
`If you have 2 BTC. All of it is owned by you. You cannot just send 1 BTC to Tom. In a BTC transaction, all of the 2 BTC is used in the input of that transaction. You get your change back in the output when the transaction sets Tom as the owner of 1 BTC, while you are the owner of 1 as well.`

Makes sense to me. You need a transaction() function to reassign ownership. But a pro here is that you can split up your BTC into any denomination.

# UTXO
`An unspent transaction output (UTXO) is a discrete piece of bitcoin. UTXOs can be combined and split up to make payments in any denomination.`

Initially I thought, then isn't every BTC a UTXO? What is the point of this term? If I spend it, then it becomes someone else's UTXO. DUH. I don't see the significance. Is there such a thing as a spent TXO?

Then I realised, once a UTXO becomes an input to a transaction (aka, it is being `spent`), it doesn't "exist" anymore. You don't own that UTXO too because it doesn't exist. It is the new UTXO that is created in the output that matters. So in a pool of UTXO, it is constantly changing, being created and destroyed over and over again via transactions.

# UTXO Set
The UTXO set is the comprehensive set of all UTXOs existing at a given point in time. The sum of the amounts of each UTXO in this set is the total supply of existing bitcoin at that point of time.

Bitcoin is special as a money in that anyone can verify the total supply at any time in a trustless manner. All nodes maintain identical copies of the UTXO set. When a new block is created, the UTXO set is updated as some UTXOs were spent and new ones were created.

The UTXO set is also important because it allows all nodes in the Bitcoin network to detect and reject attempted double spends, wherein someone attempts to spend the same bitcoin twice. Nodes must store the entire UTXO at all times in order to determine which bitcoin exist, and thus can be spent, at any given point in time.

# Sources
- https://river.com/learn/bitcoins-utxo-model/
  - very good read
- https://river.com/learn/terms/u/utxo-set/