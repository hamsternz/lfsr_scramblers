# lfsr_scramblers
Experiments with self-synchronizing LFSR scramblers.

Scramblers are useful to convert a a somewhat predictable sequence
of bits into what look like random bits, with approximately even 
numbers of '1's and '0's (so minimal DC bias).

This allows them to be easily transmitted and recoverd (e.g. over radio or optics)

The structure of the LFSR scrambler is such that it self-synchronizes between
encoder and decoder, and that RX errors will quickly clear from the receiver.

## The two programs

find_scramblers.c : Search for 1-tap maximal LFSRs (repeat period is 2^n-1)

scramble.c : Show a scrambler in action
