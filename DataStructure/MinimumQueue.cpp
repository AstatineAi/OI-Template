/*
Luogu P1886 : Minimum Queue
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
#include <deque>

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

constexpr int N = 1000005;
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
	
	inline ll read() {
		ll res = 0;char ch = getC();bool m = 1;
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
	
	inline void write(ll x) {
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

struct Node {
	int v,pos;
	bool operator > (const Node &oth) const {
		return v > oth.v;
	}
	
	bool operator < (const Node &oth) const {
		return v < oth.v;
	}
	
	bool operator >= (const Node &oth) const {
		return !(v < oth.v);
	}
	
	bool operator <= (const Node &oth) const {
		return !(v > oth.v);
	}
}t;

template <class T>
class MinimumQueue {
	private :
		int fr,re;
		int siz;
		T q[N << 2];
	
	public : 
		
		inline void init(int s) {
			siz = s;
			fr = re = 0;
		}
		
		inline bool empty() {
			return fr == re;
		}
		
		inline T front() {
			return q[fr];
		}
		
		inline void push(T p) {
			while(p >= q[re - 1] && re != fr)
				--re;
			q[re++] = p;
		}
		
		inline void pop() {
			++fr;
		}
};

/*
template <class T>
class MinimumQueue {
	private :
		int fr,re;
		int siz;
		T q[N];
	
	public : 
		
		inline void init(int s) {
			siz = s;
			fr = re = 0;
		}
		
		inline bool empty() {
			return fr == re;
		}
		
		inline T front() {
			return q[fr];
		}
		
		inline void push(T p) {
			while(p >= q[(re - 1 + siz) % siz] && re != fr)
				re = (re - 1 + siz) % siz;
			q[re] = p;
			re = (re + 1) % siz;
		}
		
		inline void pop() {
			fr = (fr + 1) % siz;
		}
};
*/

template <class T>
class MinimumQueue2 {
	private :
		int fr,re;
		int siz;
		T q[N << 2];
	
	public : 
		
		inline void init(int s) {
			siz = s;
			fr = re = 0;
		}
		
		inline bool empty() {
			return fr == re;
		}
		
		inline T front() {
			return q[fr];
		}
		
		inline void push(T p) {
			while(p <= q[re - 1] && re != fr)
				--re;
			q[re++] = p;
		}
		
		inline void pop() {
			++fr;
		}
};

MinimumQueue<Node> q1;
MinimumQueue2<Node> q2;

int val[N];
int ans[2][N];

int main() {
	init_IO();
	int n = read(),k = read();
	q1.init(k + 1);
	q2.init(k + 1);
	rep(i,1,n) val[i] = read();
	rep(i,1,k) {
		q1.push((Node){val[i],i});
		q2.push((Node){val[i],i});
	}
	ans[0][1] = q1.front().v;
	ans[1][1] = q2.front().v;
	rep(i,k + 1,n) {
		q1.push((Node){val[i],i});
		q2.push((Node){val[i],i});
		while(q1.front().pos < i - k + 1)
			q1.pop();
		while(q2.front().pos < i - k + 1)
			q2.pop();
		ans[0][i - k + 1] = q1.front().v;
		ans[1][i - k + 1] = q2.front().v;
	}
	rep(i,1,n - k + 1)
		write(ans[1][i]),space;
	enter;
	rep(i,1,n - k + 1)
		write(ans[0][i]),space;
	end_IO();
	return 0;
}