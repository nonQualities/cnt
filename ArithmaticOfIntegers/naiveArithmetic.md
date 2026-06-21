# Schoolbook Arithmatic

Here, we shall talk about some basic arithmatic operations without any heed to scopes for optimization, for big integers or formally, multi-precision integers:

## Addition:
Let two multi-precision integers be $a=(a_{s-1}, a_{s-2}, ...a_1, a_0)_B$ and $b=(b_{t-1},b_{t-2},...,b_1,b_0)_B$ and without loss any generality we can assume, $s=t$ as, if, we simply pad the smaller operand with leading zero. We keep adding $(a_i + b_i)$.
One problem that occur is, when the result of addition is more than $2^{32} - 1$, there is a complicated business of input and output carry. 

>[!Important]
> Input and Output Carry:
> **Input carry** is the overflow coming into a digit position; **output > carry** is the overflow leaving that digit position.
> Or, in computer arithmetic:
> 
> $$
 c_{out}=
\begin{cases}
1, & \text{if } a_i+b_i+c_{in}\ge B,\\
0, & \text{otherwise},
\end{cases}
> $$
> 
> 
where (B) is the radix (e.g., (256), (2^{32}), (10), etc.). The output carry of one position becomes the input carry of the next position.

Modern Computers generally return the least significant bit when there is a overflow,i.e, addition, substraction and multiplication is actually computed modulo 256. Mathematically,
$$a_i \plusmn or\times  b_i (\mod 2^{32})$$

- **Input Carry = 0:** the modulo-B sum of $a_i + b_i \nleq a_i \wedge b_i$
- **Input Carry $\geq 0$:**  the modulo-B sum of $a_i + b_i \leq a_i \wedge b_i$ 

## Substraction:
Similar to addition, here we must handle the borrows, denoted by $c_{in}, c_{out}$ respectively for input borrow and output borrow. For $a_i -b_i - c_{in}$:
- If $c_{in} = 0$: $c_{out} = 1$ iff $a_i \lneq b_i$
- If $c_{in} = 1$: $c_{out} = 1$ iff $a_i \leq b_i$

>[!Note]
>Even in the case of output borrow, one can simple compute the modular substraction and keep returned valued as the output word, given the CPU support 2's-compliment arithmetic.
> If not: $a_i-b_i-c_{in}$ can be computed $a_i + (B-b_i-c_{in})$ where,$(B-b_i-c_{in})$ is the bitwise complement of $b_i$ and $B-b_i$ is one more than that.

## Multiplication:
[I have skipped multiplication for now, it seemed very complicated] \
. . . \
. . . 

## Euclidean Division:
This turns out to be the most tricky of all the arithmetic operations. But this is euclidean divisoin is : 

$$ a = bq+r $$

$\forall a,b \in \Z \wedge 0\leq r\leq |b| -1$ and $q$ and $r$ are unique.

Computing q and r involves efficiently, guessing the B-nary digits of q from the most significant end. In order to do that, we need to *normalize* $b$, making it satisfy the assumption that **most significant word of $b$ is atleast as large as $B/2$**. If the condition not satisfied, we multiply both $a$ and $b$ by a suitable power of 2 and we shall do the same with $r$ too. 

...[TODO: Complete the rest of this]
