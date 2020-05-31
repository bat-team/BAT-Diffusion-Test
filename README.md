# BAT-Diffusion-Test

Diffusion tests of round functions and key schedules of BAT block ciphers.

## The diffusion tests of round functions

We test the rounds of achieving full diffusion (**at bit level**) for BAT-64, BAT-128, SIMON-64 and SIMON-128. The codes for these tests are given in BAT and SIMON directories. The results can be found in the directory **[diffusion_tests](https://github.com/bat-team/BAT-Diffusion-Test/tree/master/diffusioin_tests)**.

| Cipher    | Rounds for full diffusion |
|:---------:|:-------------------------:|
| BAT-64    | 7                         |
| BAT-128   | 9                         |
| SIMON-64  | 9                         |
| SIMON-128 | 13                        |



## The diffusion tests of key schedules

We also perform the algebraic expressions of linear key schedule of BAT and SIMON. By setting all master key bits as variables, we then can express each bit of the subkey for each round. The results can be found in the directory **[keyschedule_tests](https://github.com/bat-team/BAT-Diffusion-Test/tree/master/keyschedule_tests)**.

Like for SIMON-64128 (full 44 rounds), we can get the following results for the last round subkey (index starts from 0)

> R43:(['min:51', 'max:51', 'len:32', 'avg:51.00'],)

- min: the bit in current round subkey that has the minimum number of master key bits involved.
- max: the bit in current round subkey that has the maximum number of master key bits involved.
- len: the length of current round subkey in terms of bit.
- avg: the involved number of master key bits for each bit of round subkey on average.


