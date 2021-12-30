/*
Luogu P1379 八数码难题
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
#include <functional>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>

#define space putC(' ')
#define enter putC('\n')

#define rep(a,b,c) for(int a = (b);a <= (c);++a)
#define repb(a,b,c) for(int a = (b);a >= (c);--a)
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

constexpr int N = 100005;
constexpr int INF = 1e9;
constexpr int MOD = 998244353;

namespace IO {
	#define IS stdin
	#define OS stdout
	FILE *is,*os;
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
	}
	
	inline void putC(char ch) {
		if(_o == obuf + IOLIM) {
			fwrite(obuf,_o - obuf,sizeof(char),OS);
			_o = obuf;
		}
		*_o++ = ch;
	}
	
	inline void write(int x) {
		static int sta[20];int top = 0;
		do
			sta[top++] = x % 10,x /= 10;
		while(x);
		while(top) putC(sta[--top] + '0');
	}
	
	inline void getStr(char *s) {
	    char ch = getC();int len = 0;
	    while(!isdigit(ch)) ch = getC();
	    while(isdigit(ch)) {
	        s[len++] = ch;
	        ch = getC();
	    }
	    s[len] = '\0';
	}
}
using IO::init_IO;
using IO::end_IO;
using IO::write;
using IO::getStr;
using IO::putC;

constexpr int movx[] = {0,1,-1,0,0};
constexpr int movy[] = {0,0,0,1,-1};

constexpr int id[5][5] = {
	{0,0,0,0,0},
	{0,1,2,3,0},
	{0,8,0,4,0},
	{0,7,6,5,0},
	{0,0,0,0,0}
};

bool vis[400000];
int fac[15];
char str[15];

struct Node {
	int mat[4][4];
	int step,he;
	int x,y;
	inline bool operator > (const Node &oth) const {
		return he + step > oth.he + oth.step;
	}
	inline bool operator < (const Node &oth) const {
		return he + step < oth.he + oth.step;
	}
}s;

inline int h(Node a) {
	int cnt = 0;
	rep(i,1,3) rep(j,1,3)
		cnt += (a.mat[i][j] != id[i][j]); 
	return cnt;
}

inline void init() {
	fac[0] = 1;
	rep(i,1,9)
	    fac[i] = fac[i - 1] * i;	
}

inline int Cantor(Node a) {
	int res = 0;
	int seq[10];
	rep(i,1,9)
		seq[i] = a.mat[(i - 1) / 3 + 1][(i - 1) % 3 + 1];
	repb(i,9,1) {
		int cnt = 0;
		rep(j,i + 1,9) if(seq[j] < seq[i]) cnt++;
		res += cnt * fac[9 - i];
	}
	return res;
}

int bfs() {
	__gnu_pbds::priority_queue<Node,std::greater<Node>,__gnu_pbds::pairing_heap_tag> q;
	q.push(s);
	while(!q.empty()) {
		Node u = q.top();q.pop();
		int id = Cantor(u);
		vis[id] = 1;
		rep(i,1,4) {
			int tx = u.x + movx[i];
			int ty = u.y + movy[i];
			if(tx < 1 || tx > 3 || ty < 1 || ty > 3) continue;
			Node p = u;
			p.step = u.step + 1,p.x = tx,p.y = ty;
			std::swap(p.mat[u.x][u.y],p.mat[tx][ty]);
			p.he = h(p);
			if(p.he == 0)
				return p.step;
			id = Cantor(p);
			if(!vis[id]) q.push(p);
		}
	}
	return INF;
}

int main() {
    init_IO();
	init();
	getStr(str + 1);
	rep(i,0,2) {
		rep(j,1,3) {
			s.mat[i + 1][j] = str[i * 3 + j] - '0';
			if(s.mat[i + 1][j] == 0) s.x = i + 1,s.y = j;
		}
	}
	s.he = h(s);
	s.step = 0;
	if(s.he) write(bfs());
	else putC('0');
	end_IO();
	return 0;
}