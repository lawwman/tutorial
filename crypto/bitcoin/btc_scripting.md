# I don't intend to go deep into this, but good reads:
- [Article: The Bitcoin Script Language](https://betterprogramming.pub/the-bitcoin-script-language-e4379908448f)
- [Article: An Introduction to Bitcoin Script](https://academy.binance.com/en/articles/an-introduction-to-bitcoin-script)
- [YT vid: Dissecting a P2PKH Bitcoin Transaction down to the last Byte](https://www.youtube.com/watch?v=1n4g3eYX1UI)
- [Article: list of script commands](https://en.bitcoin.it/wiki/Script)

# My understanding
Transactions between UTXO involve scripts!

From what I can tell, we have basic unlocking and locking scripts.

unlocking script is pretty straight forward... it just contains the signature and public key. It is less of an actual script and more of just information to prove that you own the input. But it is still referred to as a script it seems.
```
// example of unlocking script

3045022100b7393ff959120e3ccb5284e3cf2eaa200235643a1549a4e6faaa911619089e2b02207b677827c7beeb53503e016a8dd29164d07cb79f0f1e058df9b8dfa3568d029001  // script signature
04c4b7a7f7bb2c899f4aeab75b41567c040ae79506d43ee72f650c95b6319e47402f0ba88d1c5a294d075885442679dc24882ea37c31e0dbc82cfd51ed185d7e94  // public key
```

locking script is more complicated in that you have "functions" or "commands" like `OP_CHECKSIG`, `OP_EQUALVERIFY` and so on.
```
// example of locking script

OP_DUP OP_HASH160 7ddb236e7877d5040e2a59e4be544c65934e573a OP_EQUALVERIFY OP_CHECKSIG
```

If you put the 2 together, you get the script for the transaction.
```
// example of Unlocking a Transaction

3045022100b7393ff959120e3ccb5284e3cf2eaa200235643a1549a4e6faaa911619089e2b02207b677827c7beeb53503e016a8dd29164d07cb79f0f1e058df9b8dfa3568d029001 04c4b7a7f7bb2c899f4aeab75b41567c040ae79506d43ee72f650c95b6319e47402f0ba88d1c5a294d075885442679dc24882ea37c31e0dbc82cfd51ed185d7e94 OP_DUP OP_HASH160 7ddb236e7877d5040e2a59e4be544c65934e573a OP_EQUALVERIFY OP_CHECKSIG
```

