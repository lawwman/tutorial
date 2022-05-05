# I don't intend to go deep into this, but good reads:
- [Article: An Introduction to Bitcoin Script](https://academy.binance.com/en/articles/an-introduction-to-bitcoin-script)
- [YT vid: Dissecting a P2PKH Bitcoin Transaction down to the last Byte](https://www.youtube.com/watch?v=1n4g3eYX1UI)
  - pretty cool breakdown
  - At my current level, I don't think its important to know.
- [Article: list of script commands](https://en.bitcoin.it/wiki/Script)

# My understanding

2 script components in a UTXO transaction: unlocking and locking script.

- `scriptSig`: contains required info (signature, sometimes public key) to `unlock` the UTXO. The `unlocking` script.
- `scriptPubkey`: used to verify if given `scriptSig` is valid. It keeps the UTXO locked if condition is not met. The `locking` script.

## Pay to Pubkey (P2PK)
- funds are locked to a `public key`

- `scriptSig`: signature signed by `private key` (key to the lock)
- `scriptPubkey`: contains `public key` and logic to verify the `scriptSig` (key to lock).

## Pay to Pubkey-hash (P2PKH)
- funds are locked to the `hash of the public key`

- `scriptSig`: (signature signed by `private key`) and `public key`.
- `scriptPubkey` contains `hash of public key` and following logic:
  - check if hash of `public key` in `scriptSig` matches the hash of `public key` in `scriptPubkey`
  - check if public key and signature in `scriptSig` matches each other.

## P2PK vs P2PKH
- P2PK contains `public key`
- P2PKH contains hash of `public key`





