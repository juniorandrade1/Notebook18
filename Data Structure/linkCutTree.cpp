#include <bits/stdc++.h>

using namespace std;

class LinkCutTree {
private:
  
  struct Node {
    int v, sz, mn, sm;
    Node *l, *r, *p, *pp;
    Node() {
      mn = -1;
      v = -1;
      sz = 0;
      sm = 0;
      l = r = p = pp = NULL;
    }
    Node(int _v) {
      v = _v;
      mn = _v;
      sm = _v + 1;
      sz = 0;
      l = r = p = pp = NULL;
    }
  };
  
  vector< Node > e;
  int n;

  void update(Node *x) {
    x->sz = 1;
    x->mn = x->v;
    x->sm = x->v + 1;
    if(x->l) {
      x->sz += x->l->sz;
      x->mn = min(x->mn, x->l->mn);
      x->sm += x->l->sm;
    }
    if(x->r) {
      x->sz += x->r->sz;
      x->mn = min(x->mn, x->r->mn);
      x->sm += x->r->sm;
    }
  }

  void rotr(Node *x) {
    Node *y, *z;
    y = x->p, z = y->p;
    if((y->l = x->r)) y->l->p = y;
    x->r = y, y->p = x;
    if((x->p = z)) {
      if(y == z->l) z->l = x;
      else z->r = x;
    }
    x->pp = y->pp;
    y->pp = 0;
    update(y);
  }

  void rotl(Node *x) {
    Node *y, *z;
    y = x->p, z = y->p;
    if((y->r = x->l)) y->r->p = y;
    x->l = y, y->p = x;
    if((x->p = z)) {
      if(y == z->l) z->l = x;
      else z->r = x;
    }
    x->pp = y->pp;
    y->pp = 0;
    update(y);
  }

  void splay(Node *x) {
    Node *y, *z;
    while(x->p) {
      y = x->p;
      if(y->p == 0){
        if(x == y->l) rotr(x);
        else rotl(x);
      }
      else {
        z = y->p;
        if(y == z->l){
          if(x == y->l) rotr(y), rotr(x);
          else rotl(x), rotr(x);
        }
        else {
          if(x == y->r) rotl(y), rotl(x);
          else rotr(x), rotl(x);
        }
      }
    }
    update(x);
  }


  Node *access(Node *x) {
    splay(x);
    if(x->r) {
      x->r->pp = x;
      x->r->p = 0;
      x->r = 0;
      update(x);
    }
    Node *lst = x;
    while(x->pp) {
      Node *y = x->pp;
      lst = y;
      splay(y);
      if(y->r) {
        y->r->pp = y;
        y->r->p = 0;
      }
      y->r = x;
      x->p = y;
      x->pp = 0;
      update(x);
      splay(x);
    }
    return lst;
  }

  Node *root(Node *x) {
   access(x);
    while(x->l) x = x->l;
    splay(x);
    return x;
  }

  void link(Node *x, Node *y) {
    access(x);
    access(y);
    x->l = y;
    y->p = x;
    update(x);
  }
  void cut(Node *x) {
    access(x);
    x->l->p = 0;
    x->l = 0;
    update(x);
  } 

  Node *getLca(Node *x, Node *y) {
    access(x);
    return access(y);
  }

  int getMin(Node *x, Node *y) {
    access(x);
    Node *l = access(y);
    access(l);
    if(l->v != x->v && l->v != y->v) {
      splay(x);
      splay(y);
      return min(l->v, min(x->mn, y->mn));
    }
    else {
      if(l->v != x->v) {
        access(x);
        access(y);
        splay(x);
        return min(y->v, x->mn);
      }
      else {
        access(y);
        access(x);
        splay(y);
        return min(x->v, y->mn);
      }
    }
  }

public:
  LinkCutTree(int _n) {
    n = _n;
    for(int i = 0; i < n; ++i) {
      e.push_back(Node(i));
      update(&e[i]);
    }
  }
  void link(int x, int y) {
    link(&e[x], &e[y]);
  }
  void cut(int x) {
    cut(&e[x]);
  }
  int getLca(int x, int y) {
    return getLca(&e[x], &e[y])->v;
  }
  int getMin(int x, int y) {
    return getMin(&e[x], &e[y]);
  }
};

int n, m;
LinkCutTree *tree;
char str[123];

int main() {
  scanf("%d %d", &n, &m);
  tree = new LinkCutTree(n);
  for(int i = 0; i < m; ++i) {
    scanf(" %s", str);
    if(str[0] == 'l') {
      int x, y; scanf("%d %d", &x, &y); x--; y--;
      if(str[1] == 'c') printf("%d\n", tree->getLca(x, y) + 1);
      else tree->link(x, y);
    }
    else if(str[0] == 'c') {
      int x; scanf("%d", &x); x--;
      tree->cut(x);
    }
    else if(str[0] == 'm') {
      int x, y; scanf("%d %d", &x, &y); x--; y--;
      printf("%s %d %d -> %d\n", str, x + 1, y + 1, tree->getMin(x, y) + 1);
    }
  }
  return 0;
}