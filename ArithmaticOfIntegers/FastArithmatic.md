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
  - $\implies x.y = $(2^{n/2} x_h + x_l)$ . $(2^{n/2}y_h + y_l)$
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

## Tim-Cook Multiplication:
