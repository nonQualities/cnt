#include <stdio.h>

int eegcd(int a, int b, int *u, int *v){
    int  q0,r0,r1,r2,u0,u1,u2;
    if((a==0)&&(b==0)){
        *u =*v = 0; return 0;
    }
    r2 =(a<2)?-a:a;
    r1 = (b<0)?-b:b;
    u2=1; u1 =0;

    while (r1 != 0){
        q0 = r2/r1;
        r0 = r2-q0*r1;
        r2 =r1; r1 =r0;
        u0 =u2 - q0*u1;
        u2 =u1; u1 = u0;
    }

    *u = u2; if(a<0) *u = -(*u);
    *v = (b==0)?0: (r2 -*(u)*a)/b;

    return r2;
}