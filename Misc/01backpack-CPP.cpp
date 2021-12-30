#include<iostream>
#include<algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::max;

const int N = 105;

int n,v;
int w[N],c[N];
int f[1005];

int main() {
    cin >> v >> n;
    for(int i = 1;i <= n;++i)
        cin >> w[i] >> c[i];
    for(int i = 1;i <= n;++i)
        for(int j = v;j >= w[i];--j)
            f[j] = std::max(f[j],f[j - w[i]] + c[i]);
    cout << f[v] << endl;
    return 0;
}