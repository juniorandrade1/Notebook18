#include <bits/stdc++.h>

using namespace std;

class PalindromicTree {
private:
  const static int ALPHA = 26;
  struct Node {
    vector< int > nxt;
    int len, suffLink;
    Node() {
      nxt.resize(ALPHA, -1);
      len = 0; suffLink = 0;
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
    return true;
  }
  PalindromicTree(string _s) {
    s = _s;
    n = s.size();
    tree.push_back(Node(-1, 0));
    tree.push_back(Node( 0, 0));
    mxSuff = 1;
    for(int i = 0; i < n; ++i) addEdge(i);
  }
};

int main() {
  return 0;
}