#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair< int, int > ii;
typedef vector<ll> vi;
typedef vector< ii > vii;

#define INF 0x3F3F3F3F
#define LINF 0x3F3F3F3F3F3F3F3FLL
#define pb push_back
#define mp make_pair
#define pq priority_queue
#define LSONE(s) ((s)&(-s)) //LASTBIT
#define DEG_to_RAD(X)   (X * PI / 180)
#define F first
#define S second
#define PI 2*acos(0)

#ifdef ONLINE_JUDGE
#define debug(args...)
#else
#define debug(args...) fprintf(stderr,args)
#endif

//////////////////////
int dx[] = {1,-1,0,0};
int dy[] = {0,0,-1,1};
//////////////////////

/*
  Author: Junior Andrade
*/ 

void arquivo() {
  freopen("connect.in","r",stdin);
  freopen("connect.out","w",stdout);
}

const int N = 300300;

struct no {
  char op;
  int x, y, id;
  no(){}
  no(int _x, int _y, int _id) {
    x = _x;
    y = _y;
    id = _id;
  }
};

struct DSU {

  int *pset;
  int n, sp;
  no *rollback;
  int qtd;

  DSU() {
    n = N;
    pset = new int[N];
    rollback = new no[5000000];
    sp = 0;
    qtd = n;
    for(int i = 0; i < n; ++i) pset[i] = i;
  }
  DSU(int _n) {
    n = _n;
    pset = new int[n];
    rollback = new no[5000000];
    sp = 0;
    qtd = n;
    for(int i = 0; i < n; ++i) pset[i] = i;
  }
  int Find(int x) {
    if(x == pset[x]) return x;
    rollback[sp++] = (no(x, pset[x], qtd));
    return pset[x] = Find(pset[x]);
  }

  void Union(int x, int y){
    x = Find(x);
    y = Find(y);
    rollback[sp++] = (no(y, pset[y], qtd));
    if(x != y) qtd--;
    pset[y] = x;
  }
  void Rollback(){
    sp--;
    int x = rollback[sp].x, y = rollback[sp].y;
    qtd = rollback[sp].id;
    pset[x] = y;
  }
};

int n, m;
no v[N];
DSU dsu;
int lst[N], nxt[N];
map< ii, int > foo;

int ans[N];

void solve( int l, int r ) {
  if(l > r) return;
  if(l == r) {
    if(v[l].op == '?')  ans[v[l].id] = dsu.qtd;
    return;
  }
  int mid = (l + r) >> 1, len = dsu.sp;
  for(int i = mid + 1; i <= r; ++i) {
    if(v[i].op == '-' && lst[i] < l) dsu.Union(v[i].x, v[i].y);
  }
  solve(l, mid);
  while(dsu.sp > len) dsu.Rollback();

  for(int i = l; i <= mid; ++i) {
    if(v[i].op == '+' && nxt[i] > r) dsu.Union(v[i].x, v[i].y);
  }
  solve(mid + 1, r);
  while(dsu.sp > len) dsu.Rollback();
}

int main() {
  //ios::sync_with_stdio(0);
  arquivo();
  memset(lst,-1,sizeof lst);
  memset(nxt,INF,sizeof nxt);
	scanf("%d %d", &n, &m);
  dsu = DSU(n);
  int qtdQuerys = 0;
  for(int i = 0; i < m; ++i) {
    scanf(" %c", &v[i].op);
    if( v[i].op != '?' ){
      scanf("%d %d", &v[i].x, &v[i].y);
      v[i].x--; v[i].y--;
      if(v[i].x > v[i].y) swap(v[i].x, v[i].y);
      if(foo.count(mp(v[i].x, v[i].y))) {
        lst[i] = foo[mp(v[i].x, v[i].y)];
        nxt[foo[mp(v[i].x, v[i].y)]] = i;
      }
      foo[mp(v[i].x, v[i].y)] = i;
    }
    else v[i].id = qtdQuerys++;
  }

  solve(0,m-1);
  for(int i = 0; i < qtdQuerys; ++i) printf("%d\n", ans[i]);
  return 0;
}