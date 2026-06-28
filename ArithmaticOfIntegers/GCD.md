# Greatest Common Divisor

**Definition 1.12:** Let $a,b \in \Z$ be not both zero. The largest positive integer $d$ that divides both $a$ and $b$  is called the **Greatest Common Divisor** of $a$ and $b$.
- Clearly, $gcd(a,b)=gcd(b,a)$
- if $gcd(a,b)=1$ then $a$ and $b$ are called co-primes.


**Theorem 1.15:** [Euclidean GCD] Let $a,b \in \Z$ with $b\neq 0$ and $r=a(rem)b$. Then, $gcd(a,b)=gcd(b,r)$.

ex: $gcd(252,91)$ 
$$\begin{align}
252 = 2 \times 91 + 70 \\
91 = 70 \times + 21 \\
70 = 21 \times 3 + 7\\
21 = 3 \times 7  
\end{align}
$$
 Remarks:
 - The remainder sequence follows the chain of inequalities: $r_1 > r_2>r_3>....>r_{k-1}>r_k$, that is the procedure terminates after a finite steps, specifically it continues for **atmost** $r_1 = b$ iterations. **However in practice it takes way less time, as after every iterations, the remainder reduces by atleast a factor of two**, $\implies$ after $O(\lg(min(a,b)))$ iterations, the remainder reduces to zero.
```C
#include <stdio.h>

int egcd(int a, int b){
    int r;
    if((a == 0) && (b == 0)) return 0;
    if(a < 0) a = -a;
    if(b < 0) b = -b;

    while (b!=0) {
        r = a % b;
        a = b; b = r;
    }
    
    return a;
}
```
## Extended GDC Algorithm:

**Theorem 1.17**[Bézout Relation] For $a,b \in \Z$, not both zero, there exits integers $u,v$ satisfying $gcd(a,b) = ua+vb$
- the computation of $u,v$ along with gcd is called the **extended GCD Algorithm**. 
