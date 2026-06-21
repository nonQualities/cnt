REPRESENTATION OF BIG INTEGERS
--------------------------------
<small> author: Ronit Choudhury <br>
date: 21/06/26 <br>
references : <ol> 
                <li> <a href="https://www.sunshine2k.de/articles/coding/biguint/bigunsignedint.html"> Big Unsigned Ints </a>
                <li> <a href="https://maths-people.anu.edu.au/~brent/pub/pub226.html"> Modern Computer Arithmetic </a>
            </ol>
</small>


-----

It is customery to express big integer n in some predetermined base B, and store the B-ary digits of n in an array of integers, so chosen that each B-ary digit fit into a single built-in integer type.

>[!Note]
> In 32 bit machines, the base B is generally taken as $2^{32}$. \
> In 64 bit machines, the base is generally taken as $2^{64}$

An integer thus represented is called, a multiprecision integer.
For computer science purposes, the most natural way to think about base conversion is definitely not in terms of positional notation, as it is simpler to think in terms of **storage** by many folds. Suppose a user types the decimal string

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

For example, suppose (B=256) and we have already **processed**

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

### For Example:
Q: Convert 12343 to base-256:
Soln: 

- $1 \times 10 + 0 = 1$
- $1\times 10 + 2 = 12$
- $12\times 10 + 3 = 123$
- $123\times 10 = 1230$ which is larger than 255, 
  - therefore, we must convert $1230$ to base-256 beofore adding 4.
  - Divide $1230$ by $256$ until remainder is less than the `base` (in our case 256)
  - $\therefore$ $4\times 256+206 = 1230$ where, r=206 < base=256 : $(4, 206)_{256}$.
  - now we add the next digit from the number $1234$ which is 4, as we have already added till 3: $(4, 206)_{256} + 4 = (4,210)_{256}$
- for the last digit, again we follow the same procedure: since we converted till 4,i.e, 1234, we do:
  - $1234\times 10 = 12340$ convert 12340 into base 256 which would yeild: $12340 = 48 \times 256+52$ 
  - $\implies 12340 \equiv (48,52)_{256}$ adding the last digit 3 to it makes: $(48, 55)_{256}$


