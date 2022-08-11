# Learning [Merkle Trees](https://en.wikipedia.org/wiki/Merkle_tree)

In the wiki, a [preimage attack](https://en.wikipedia.org/wiki/Preimage_attack) is mentioned.

# Firstly, what is a preimage (aka. [inverse image](https://en.wikipedia.org/wiki/Image_(mathematics)#Inverse_image))?
Suppose we have a function `F`. The input of `F` is set `A`. The output of `F` is set `B`. Example:
- `A` = [1, 2, 3]
- `F` is (input) => input * 2
- `B` = [2, 4, 6]

- The `direct image` of `A` (or any subset) is `F(A)` or simply `B`.
- The `inverse image` of `B` (or any subset) is `A`.

`inverse image` aka `preimage`.

What is the preimage of a hashed value? A set of values that when hashed, produce the same results.

# preimage resistance and attack!
`preimage` resistance: for essentially all pre-specified outputs, it is computationally infeasible to find any input that hashes to that output; i.e., given y, it is difficult to find an x such that h(x) = y. `basically, a measure of how much the function is "one-way".`

`preimage` attack: given that we know what the output is, what is the input?

# second-preimage resistance and attack!
`second-preimage` resistance: for a specified input, it is computationally infeasible to find another input which produces the same output; i.e., given x, it is difficult to find a second preimage x′ ≠ x such that h(x) = h(x′).

`second-preimage` attack: given that we know what the output and original input is, find a second input that gives the same output.

# Good reads on 2nd preimage attacks
- [wiki's take on 2nd preimage attack](https://en.wikipedia.org/wiki/Merkle_tree#Second_preimage_attack)
- [2nd preimage vs collision attack](https://cstheory.stackexchange.com/questions/585/what-is-the-difference-between-a-second-preimage-attack-and-a-collision-attack)

# Good reads on 2nd preimage attacks in the context of Merkle trees
- [good explanation on 2nd preimage attack](https://flawed.net.nz/2018/02/21/attacking-merkle-trees-with-a-second-preimage-attack/)
- [why using different hashes for internal and leaf nodes prevent 2nd preimage attack](https://crypto.stackexchange.com/questions/2106/what-is-the-purpose-of-using-different-hash-functions-for-the-leaves-and-interna)

# attack on unbalanced merkle tree (BTC vulnerability)
- [weird implementation by BTC's merkle](https://bitcointalk.org/?topic=102395)
  - BTC's merkle implementation pads odd numbered inputs with duplicates of the last input. Even for intermediate hashes, this behaviour is consistent till root hash is obtained. 2nd preimage can be obtained by simply duplicating inputs when they happen to be odd numbered.

# Good read on Merkle proofs and BTC
- [discussion on efficiency of merkle proofs](https://bitcoin.stackexchange.com/questions/69018/merkle-root-and-merkle-proofs)