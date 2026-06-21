REPRESENTATION OF BIG INTEGERS
--------------------------------


It is customery to express big integer n in some predetermined base B, and store the B-ary digits of n in an array of integers, so chosen that each B-ary digit fit into a single built-in integer type.

> In 32 bit machines, the base B is generally taken as 2^32
> In 64 bit machines, the base is generally taken as 2^64

An integer thus represented is called, a multiprecision integer.
                                       --------------------------

For a computer scientist, the most natural way to think about base conversion is not in terms of positional notation, but in terms of **storage**.

Suppose a user types the decimal string

```text
123454321
```

The machine receives a sequence of characters. The problem is to construct an internal representation of the integer using some radix (B). In a big-integer library, (B) is usually chosen to match the machine architecture. A common choice is (B=256), since one base-256 digit occupies exactly one byte.

The fundamental observation is that if we have already processed some prefix of the input and obtained the corresponding integer (n), then reading one additional decimal digit (d) transforms the value into

$10n+d$

Thus the conversion algorithm does not need to know the entire number in advance. It merely maintains a running value and updates it as each digit arrives.

Let (n) initially be zero. For each input digit (d),

$n \leftarrow 10n+d$

This deceptively simple recurrence is the entire algorithm.

The only complication is that (n) is stored as an array of base-(B) digits rather than as a machine integer. Therefore the operations "multiply by 10" and "add (d)" must be performed on that array.

For example, suppose (B=256) and we have already processed

```text
1234
```

The internal representation is

$(4,210)_{256}$,

which you may visualize as the byte array

```text
[4][210]
```

because

$4\cdot256+210=1234$

Now the next input digit is (5). The algorithm computes

$1234\cdot10+5$

First multiply by 10: $1234\cdot10=12340$
Expressed in base 256,
$12340 = 48\cdot256 + 52$, so the byte array becomes

```text
[48][52]
```
Then add the new digit: $52+5=57$. The final representation becomes

```text
[48][57]
```

or

$(48,57)_{256}$

One can observe that at no point did we first construct the decimal integer and then convert it. The conversion happened incrementally as the input was being read. A number with a million decimal digits can be processed one character at a time, because the algorithm requires only the current internal representation and the next input digit.

In pseudocode:

```text
n ← 0

for each digit d in the input string:
    n ← n × 10
    n ← n + d
```

The elegance of the method lies in the fact that it is independent of the target base. Whether the internal radix is 256, (2^{32}), (10^9), or any other convenient value, the algorithm remains unchanged. Only the implementation of multiplication and addition on the digit array differs. The mathematical idea is always the same: every new decimal digit extends the current value by the transformation

$n \leftarrow 10n+d$

