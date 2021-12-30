v,n = map(int,input().split())

f = [0 for siz in range(v + 5)]

for i in range (n) :
    w,c = map(int,input().split())
    for j in range(v,w - 1,-1) :
        f[j] = max(f[j],f[j - w] + c)

print(f[v])