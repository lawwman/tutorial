# How does bitcoin prevent double spending?
https://www.reddit.com/r/BitcoinBeginners/comments/7pkpgl/how_does_bitcoin_prevent_double_spending/

## Question
Seems like the only way to verify whether someone actually has the coins available is to go through the entire blockchain and see how much they have received and sent.

## Answer
Yes-ish. You don't have to go through the whole blockchain every time though. You can go through it once and generate the "UTXO" set, which is a list of all unspent Bitcoin and their addresses. Once you've got that, you just update it after each block and check new transactions against that set.