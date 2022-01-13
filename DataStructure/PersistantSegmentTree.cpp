/*
Luogu P3834 Persistant Segment Tree
Author : AstatineAi
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <climits>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <utility>

#define space putC(' ')
#define enter putC('\n')
#define El_Pueblo_Unido_Jamas_Sera_Vencido

#define rep(a,b,c) for(int a = (b);a <= (c);++a)
#define repb(a,b,c) for(int a = (b);a >= (c);--a)
#define repl(a,b,c) for(int a = (b);a < (c);++a)
#define repr(a,b,c) for(int a = (b);a > (c);--a)
#define repg(a,b) for(int a = head[b]; ~a ; a = e[a].nxt)
#define mems(a,b) memset(a,b,sizeof(a))

#define DEBUG
// #define NDEBUG // ban assert
#define O(a) std::cerr<<#a<<':'<<a<<std::endl;

typedef long long ll;
typedef unsigned long long ull;
typedef __uint128_t I128;
typedef double db;
typedef std::pair<int,int> pii;

constexpr int N = 200005;
constexpr int INF = 1e9;
constexpr int MOD = 998244353;

namespace IO {
	#define IS stdin
	#define OS stdout
	constexpr int IOLIM = 10000;
	char ibuf[IOLIM],obuf[IOLIM];
	char *_i = ibuf,*_o = obuf;
	inline void init_IO() {
		fread(ibuf,IOLIM,sizeof(char),IS);
	}
	
	inline char getC() {
		if(_i == ibuf + IOLIM) {
			mems(ibuf,0);
			fread(ibuf,IOLIM,sizeof(char),IS);
			_i = ibuf;
		}
		return *_i++;
	}
	
	inline void end_IO() {
		fwrite(obuf,_o - obuf,sizeof(char),OS);
		fclose(IS),fclose(OS);
	}
	
	inline void putC(char ch) {
		if(_o == obuf + IOLIM) {
			fwrite(obuf,_o - obuf,sizeof(char),OS);
			_o = obuf;
		}
		*_o++ = ch;
	}
	
	inline int read() {
		int res = 0;char ch = getC();bool m = 1;
		while(!isdigit(ch)) {
			if(ch == '-') m = 0;
			ch = getC();
		}
		while(isdigit(ch)) {
			res = res * 10 + (ch ^ 48);
			ch = getC();
		}
		return m ? res : -res;
	}
	
	inline void write(int x) {
		if(x < 0) putC('-'),x = -x;
		static int sta[20];int top = 0;
		do
			sta[top++] = x % 10,x /= 10;
		while(x);
		while(top) putC(sta[--top] + '0');
	}
}
using IO::init_IO;
using IO::end_IO;
using IO::read;
using IO::write;
using IO::putC;

int len,ind[N];

inline int GetRnk(int x) {
	return std::lower_bound(ind + 1,ind + len + 1,x) - ind;
}

struct PersistantSgementTree {
	int rt[N],tot;
	struct Node {
		int ls,rs;
		int v;
	}T[N * 30];
	
	void build(int &p,int pl,int pr) {
		p = ++tot;
		if(pl == pr) return ;
		int mid = (pl + pr) >> 1;
		build(T[p].ls,pl,mid);
		build(T[p].rs,mid + 1,pr);
	}
	
	void insert(int &p,int pre,int pl,int pr,int pos) {
		p = ++tot;
		T[p].ls = T[pre].ls,T[p].rs = T[pre].rs,T[p].v = T[pre].v + 1;
		if(pl == pr) return ;
		int mid = (pl + pr) >> 1;
		if(pos <= mid) insert(T[p].ls,T[pre].ls,pl,mid,pos);
		else insert(T[p].rs,T[pre].rs,mid + 1,pr,pos);
	}
	
	int query(int l,int r,int pl,int pr,int k) {
		int d = T[T[r].ls].v - T[T[l].ls].v,mid = (pl + pr) >> 1;
		if(pl == pr) return pl;
		if(k <= d) return query(T[l].ls,T[r].ls,pl,mid,k);
		else return query(T[l].rs,T[r].rs,mid + 1,pr,k - d);
	}
	
	inline int QueryKth(int l,int r,int k) {
		return query(rt[l - 1],rt[r],1,len,k);
	}
}T;



int val[N];

int main() {
	init_IO();
	int n = read(),m = read();
	rep(i,1,n) val[i] = read();
	memcpy(ind,val,sizeof(int) * (n + 1));
	std::sort(ind + 1,ind + n + 1);
	len = std::unique(ind + 1,ind + n + 1) - ind - 1;
	T.build(T.rt[0],1,len);
	rep(i,1,n) T.insert(T.rt[i],T.rt[i - 1],1,len,GetRnk(val[i]));
	while(m--) {
		int l = read(),r = read(),k = read();
		write(ind[T.QueryKth(l,r,k)]),enter;
	}
	end_IO();
	return 0;
}