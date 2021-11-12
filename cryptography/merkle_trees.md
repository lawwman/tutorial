# Learning [Merkle Trees](https://en.wikipedia.org/wiki/Merkle_tree)

In the wiki, a [preimage attack](https://en.wikipedia.org/wiki/Preimage_attack) is mentioned.

## Firstly, what is a preimage (aka. [inverse image](https://en.wikipedia.org/wiki/Image_(mathematics)#Inverse_image))?
Suppose we have a function `F`. The domain of `F` is set `A`. The range of `F` is set `B`. \
Example: `A` = [1, 2, 3]. `F` is (input) => input * 2. Then `B` = [2, 4, 6]! \
If we have a subset of `A`, which is set `E`. The `direct image` of `E` is `F(E)`. Simple. \
Example: `E` = [1], which is a subset of `A`. `Direct image` of `E` is [2]. \
An `inverse image` or `preimage` is just the reverse. Taking the above example, `preimage` of [10, 20] would be [5, 10], assuming we use the same function `F`.

What is the preimage of a hashed value? A set of values that when hashed, produce the same results.

## What is a preimage attack?
[Wiki's definition](https://en.wikipedia.org/wiki/Preimage_attack#Restricted_preimage_space_attacks)

[Pretty good examples I found](https://cstheory.stackexchange.com/questions/585/what-is-the-difference-between-a-second-preimage-attack-and-a-collision-attack)

## Simple fix against second preimage attack...
https://en.wikipedia.org/wiki/Merkle_tree#Second_preimage_attack I dont get it... Revisit this next time