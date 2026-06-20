//shall we not start with something simple? 
// Euclidean GCD

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

int main(){

    int n1,n2;
    printf("Enter two numbers: \n");
    scanf("%d %d", &n1, &n2);

    printf("GCD using the Euclidean GCD technique: %d", egcd(n1, n2));
    return 0;
}