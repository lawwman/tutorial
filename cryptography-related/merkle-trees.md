# Learning [Merkle Trees](https://en.wikipedia.org/wiki/Merkle_tree)

In the wiki, a [preimage attack](https://en.wikipedia.org/wiki/Preimage_attack) is mentioned.

## Firstly, what is a preimage (aka. [inverse image](https://en.wikipedia.org/wiki/Image_(mathematics)#Inverse_image))?
Suppose we have a function `F`. The domain of `F` is set `A`. The range of `F` is set `B`. Example:
- `A` = [1, 2, 3].
- `F` is (input) => input * 2.
- `B` = [2, 4, 6]!

If we have a subset of `A`, which is set `E`. The `direct image` of `E` is `F(E)`. Simple. Example:
- `E` = [1], which is a subset of `A`.
- `Direct image` of `E` is [2].

An `inverse image` or `preimage` is just the reverse. Taking the above example, `preimage` of [10, 20] would be [5, 10], assuming we use the same function `F`.

What is the preimage of a hashed value? A set of values that when hashed, produce the same results.


## preimage resistance and attack!
`preimage` resistance: for essentially all pre-specified outputs, it is computationally infeasible to find any input that hashes to that output; i.e., given y, it is difficult to find an x such that h(x) = y

`basically, a measure of how much the function is "one-way".`

`preimage` attack: given that we know what the output is, what is the input?

## second-preimage resistance and attack!
`second-preimage` resistance: for a specified input, it is computationally infeasible to find another input which produces the same output; i.e., given x, it is difficult to find a second preimage x′ ≠ x such that h(x) = h(x′).


`second-preimage` attack: given that we know what the output and original input is, find a second input that gives the
same output.

# Good reads on preimage attacks
- [Pretty good examples I found](https://cstheory.stackexchange.com/questions/585/what-is-the-difference-between-a-second-preimage-attack-and-a-collision-attack)
  - still don't fully get it yet, but getting there ^.
- [addressing 2nd preimage attack in merkle](https://en.wikipedia.org/wiki/Merkle_tree#Second_preimage_attack)

let salted_members be the series defined by hashing the concatonation of each member bytes with its member nonce.
let salted_members be the first level of a binary merkle tree, where each salted member is a leaf.
for each pair of 2 leaves in the first level of the merkle tree, concatonate the leave and hash the result yielding the next first level of the merkle tree.
if the first level of the tree is odd AND its length is not 1 (the end state), promote the odd leaf to the next leve and repeat the process.
The algorithm ends when the first level of the merkle tree has length 1, its single element is the merkle root.


# Good read on Merkle proofs and BTC
https://bitcoin.stackexchange.com/questions/69018/merkle-root-and-merkle-proofs