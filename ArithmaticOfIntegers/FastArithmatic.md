# Fast Arithmatic

Schoolbook methods of addition and substraction takes $O(n)$ time, and cannot be improved furthur. On the contrary, the $O(n^2)$-time schoolbook algorithms for multiplying two $n$-digit integers and for dividing a $2n$-digit integer by an $n$-digit integer are far from optimal.


## Karatsuba-Ofman Multiplication:
> reference: A.Karatsuba and Yu Ofman, Multiplication of many digital numbers by automatic computers, *Doklady Akad. Nauk. SSSR Vol,.145,* 1962.

**Input** : n bit numbers : $x,y$ \
**Output** : $2n$ bit number : $xy$

- Split $x$ and $y$ into $(n/2)$ length number as :
  - $x= 2^{n/2} x_h + x_l$ and $y=2^{n/2}y_h + y_l$
    - We assume that n is even, for simplicity.
  - Multiplying by $2^{n/2}$ is effectively shifts the number $x_h$ by $n/2$ bits to the left and the shifted bits are padded with 0s and adding $x_l$ results in the same original integer $x$. Same goes for y.
  - $\implies x.y =$ $(2^{n/2} x_h + x_l)$ . $(2^{n/2}y_h + y_l)$
    - $\implies x.y = 2^{n/2}x_hy_h + 2^{n/2}x_hy_l+2^{n/2}x_ly_h+x_ly_l$
    -  $\implies x.y = 2^{n/2}x_hy_h + 2^{n/2}(x_hy_l+x_ly_h)+x_ly_l$
  
  ```text
  fun MAC(x,y):
    if bit < 2:
        return x.y
    xh,xl <= split(x)
    yh,yl <= split(y)
    hh <= MAC(xh,yh)
    hl <= MAC(xh,yl)
    lh <= MAC(xl,yh)
    ll <= MAC(xl,yl)

    return (2^n)*hh + (2^(n/2))*(hl+lh)+ll 
  ```

  - **Karatsuba's Trick:** Note that $(x_h+x_l)(y_h+y_l) = x_hy_l+x_hy_l+x_ly_h+x_ly_l$
    - $x_hy_l+x_ly_h = (x_h+x_l)(y_h+y_l)-x_hy_h-x_ly_l$
    - One can reduce, the recursive calls from four to three and $x_hy_h,x_ly$ are already computed, hence, reduces redundant multiplications.
    - replacing, the value of $x_hy_l+x_ly_h = (x_h+x_l)(y_h+y_l)-x_hy_h-x_ly_l$ in $2^{n/2}x_hy_h + 2^{n/2}(x_hy_l+x_ly_h)+x_ly_l$, we reduce runtime to $T(n/2) = O(n^{log_23}) = o(n^{1.6})$ which is better than the general $O(n^2)$
```text
fun KOM(x,y):
    if bits < 2:
        return x.y
    xh,xl <= split(x)
    yh,yl <= split(y)
    hh <= KOM(xh,yh)
    ll <= KOM(xl,yl)
    n  <= KOM(xh+xl,yh+yl)
    return (2^n)*hh+2^(n/2)*(n-hh-ll)+ll
```

## Toom-Cook (Toom-3) Multiplication:
Let $a$ and $b$ be $n$-digit integers. Take $m=\lceil(n/3)\rceil$ and write: 
$$a= A_2R^2+A_1R+A_0 \\ b=B_2R^2+B_1R+B_0$$
where $R=B^m$. The product $c=ab$ can be expressed as the polynomia:
$$c=C_4R^4+C_3R^3+C_2R^2+C_1R+C_0 --- (I)$$
where, the coeffs:
$$\begin{align}
   C_4 = A_2B_2\\ C_3=A_2B_1+A_1B_2 \\ C_2=A_2b_0+A_1B_1+A_0B_2 \\ C_1 = A_1B_0+A_0B_1\\C_0=A_0B_0 
\end{align}$$
here, instead of computing nine subproducts, $A_iB_j$ for $i,j=0,1,2$ we compute only five coeff of $n/3$-digit integers. We calculate for $c(k) (from \dashrightarrow I)$ at specific points of $k$ namely $k=\infty,0,1,-1,-2$, lead to the following:
$$\begin{pmatrix}
    c(\infin)\\
    c(0)\\
    c(1)\\
    c(-1)\\
    c(-2)
\end{pmatrix} = \begin{pmatrix}
    1 & 0 & 0 & 0 & 0 \\
    0 & 0 & 0 & 0 & 1 \\
    1 & 1 & 1 & 1 & 1 \\
    1 & -1 & 1 & -1 & 1 \\
    16 & -8 & 4 & -2 & 1
\end{pmatrix}
\begin{pmatrix}
    C_4\\ C_3\\C_2\\C_1\\C_0
\end{pmatrix}
$$ 

These formulas involve multipliaction and divisins by small integers. Multiplying or dividing an $m$-digit multiple-precision intger by a single precision integer can be completed in $O(m)$ time, so this is no trouble. 

In general, Toom-3 runs in $O(n^{log(2k-1)/logk})$, which can be improved by taking K adaptively, optimal is shown to be $k=2^{\lceil \log r \rceil}$ where each input is broken in $k$ parts each of size $r$. This gives an asymptotic running time of $O(n2^{\sqrt{\log n}})$ for the optimal Toom-Cook method. **Unfortunately, practical implementation do not behave well for $k\geq 4$**.


## FFT-Based (Fast Fourier Transform) Multiplication 
