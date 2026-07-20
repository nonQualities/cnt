# Congruences and Modular Arithmatic

- Definition: **Congruence** : Let $m\in \N$. Two integers $a,b \in \Z$ are called $\text{congruent modulo m}$ denoted by $a \equiv b(\mod m)$ if $m | (a-b)$ or if remainder of a divided by m is equal to b divided by m. In this case, $m$ is called the modulus of the congruence.
  - In general, the integers congruent to $a \mod m$ are $a+km \ \forall_{k \in \Z}$  
  
- Definition: **A Complete Residue System** is a set of $m$ integers such that every integer $a$ is congruent to one and only one of the integers $a_i$ for $0\leq i \leq m-1$. That is, a modulo $m$ congruence leaves remainders from $0$ to $m$, and a complete resdidue system has exactly one element for each of the possible set of remainders for the congruent modulo $m$.
  - Denoted by $\Z_m$,and $\Z_m$ is a commutative ring with identity under addition and multiplication.
    - The additive identity of $\Z_m$ is its member congruent to 0, whereas the multiplicative identity of $\Z_m$ is that member which is congruent to 1 modulo m
- Definition: $a\in \Z$ is called **invertible modulo m** if $\exist_{u \in \Z_m}: (m|ua-1)$ and inverse exists for a iff $gcd(a,m)=1$
