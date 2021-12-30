#include<stdio.h>

#define N 105
#define Max(a,b) ((a) > (b) ? (a) : (b))

int n,v;
int w[N],c[N];
int f[1005];

int main(void) {
    scanf("%d%d",&v,&n);
    for(int i = 1;i <= n;++i)
        scanf("%d%d",&w[i],&c[i]);
    for(int i = 1;i <= n;++i) 
        for(int j = v;j >= w[i];--j)
            f[j] = Max(f[j],f[j - w[i]] + c[i]);
    printf("%d\n",f[v]);
    return 0;
}