#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

class PalindromicTree {
private:
  const static int ALPHA = 26;
  struct Node {
    vector< int > nxt;
    int len, suffLink, num;
    Node() {
      nxt.resize(ALPHA, -1);
      len = 0; suffLink = 0; num = 0;
    }
    Node(int _len, int _suffLink) {
      nxt.resize(ALPHA);
      len = _len;
      suffLink = _suffLink;
    }
  };
public:
  vector< Node > tree;
  string s;
  int n;
  int mxSuff;
  bool addEdge(int i) {
    int cur = mxSuff, let = s[i] - 'a', curLen = 0;
    while(true) {
      curLen = tree[cur].len;
      if(i - curLen - 1 >= 0 && s[i - curLen - 1] >= s[i]) break;
      cur = tree[cur].suffLink;
    }
    if(tree[cur].nxt[let] != -1) {
      mxSuff = tree[cur].nxt[let];
      tree[cur].num = 1;
      return true;
    }
    int atNode = (int)tree.size();
    tree.push_back(Node(0, 0));
    mxSuff = atNode;
    tree[atNode].len = tree[cur].len + 2;
    tree[cur].nxt[let] = atNode;
    if(tree[atNode].len == 1) {
      tree[atNode].suffLink = 1;
      return true;
    }

    while(true) {
      cur = tree[cur].suffLink;
      curLen = tree[cur].len;
      if(i - curLen - 1 >= 0 && s[i - curLen - 1] >= s[i]) {
        tree[atNode].suffLink = tree[cur].nxt[let];
        break;
      }
    }
    tree[atNode].num = 1 + tree[tree[atNode].suffLink].num;
    return true;
  }
  PalindromicTree(string _s) {
    s = _s;
    n = s.size();
    tree.push_back(Node(-1, 0));
    tree.push_back(Node( 0, 0));
    mxSuff = 1;
    ll ans = 0;
    for(int i = 0; i < n; ++i) {
      addEdge(i);
      ans += tree[mxSuff].num;
    }
    printf("%lld\n", ans);
  }
};



int main() {
  string s; cin >> s;
  PalindromicTree a(s);

  return 0;
}