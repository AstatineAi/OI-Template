/*
最大流 A+B problem 
*/
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<iostream>
#include<utility>
#include<queue>

#define space putchar(' ')
#define enter putchar('\n')
#define mian main

#define ff(a,b,c) for(register int a = (b);a <= (c);++a)
#define fb(a,b,c) for(register int a = (b);a >= (c);--a)
#define fe(a,b) for(register int a = head[b]; ~a ; a = e[a].nxt)
#define mems(a,b) memset(a,b,sizeof(a))

#define Min(a,b) (a) < (b) ? (a) : (b)

#define DEBUG
#define ONLINE_JUDGE
#define O(a) std::cerr<<#a<<':'<<a<<std::endl;

typedef long long ll;
typedef double db;
typedef std::pair<int,int> pii;

constexpr int N = 105;
constexpr int M = 105;
constexpr ll INF = 1e18;
constexpr int MOD = 998244353;

inline ll read() {
	ll res = 0;bool m = 0;char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') m = 1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		res = (res << 3) + (res << 1) + (ch ^ 48);
		ch = getchar();
	}
	return m ? -res : res;
}

inline void write(ll x) {
	if(x < 0) putchar('-'),x = -x;
	static int sta[35];int top = 0;
	do {
		sta[top++] = x % 10,x /= 10;
	} while(x);
	while(top) putchar(sta[--top] + 48);
}

int s,t;
int head[N],ecnt = -1;
struct Edge {
	int nxt,to;
	ll cap;
}e[M << 1];

int dep[N];
int cur[N];
bool bfs() {
	mems(dep,-1);
	dep[s] = 0;
	std::queue<int> q;
	q.push(s);
	while(!q.empty()) {
		int u = q.front();q.pop();
		cur[u] = head[u];
		fe(i,u) {
			int& v = e[i].to;
			if(~dep[v] || !e[i].cap) continue;
			dep[v] = dep[u] + 1;
			q.push(v);
		}
	}
	return ~dep[t];
}

ll dfs(int u,ll c) {
	if(u == t || !c) return c;
	ll flow = 0,f;
	for(register int i = cur[u]; ~i ;i = e[i].nxt) {
		int& v = e[i].to;
		cur[u] = i;
		if(dep[v] != dep[u] + 1) continue;
		f = dfs(v,Min(c,e[i].cap));
		e[i].cap -= f,e[i ^ 1].cap += f;
		flow += f,c -= f;
	}
	return flow;
}

ll dinic() {
	ll maxf = 0;
	while(bfs())
		maxf += dfs(s,INF);
	return maxf;
}

int mian() {
	mems(head,-1);
	s = 0,t = 1;
	auto AddEdge = [&] (int st,int ed,ll cap) {
					e[++ecnt] = (Edge){head[st],ed,cap},head[st] = ecnt;
					e[++ecnt] = (Edge){head[ed],st,0},head[ed] = ecnt;};
	ll a = read(),b = read();
	AddEdge(s,t,a),AddEdge(s,t,b);
	write(dinic());
	return 0;
}
