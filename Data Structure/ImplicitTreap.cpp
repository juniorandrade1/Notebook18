template <class T>
class ImplicitTreap {
  private:
  struct node {
    T key;
    int prior;
    int size;
    node *l, *r;
    node(){};
    node(T key, int prior) : key(key), prior(prior), size(1), l(NULL), r(NULL) {}
    node(T key) : key(key), prior(rand()), size(1), l(NULL), r(NULL) {}
  };
  typedef node* pnode;
  int getSize(pnode p) { return p ? p->size : 0; }
  void updateNode(pnode p) { 
    if(p) {
      p->size = getSize(p->l) + getSize(p->r) + 1; 
    }
  }
  void pushLazy(pnode p) {
    if(p) {
      //DO LAZY HERE
    }
  }
  void split (pnode t, pnode &l, pnode &r, int key, int add = 0) {
    if (!t) return void(l = r = NULL);
    pushLazy(t);
    int cur_key = add + getSize(t->l);
    if (key <= cur_key) split(t->l, l, t->l, key, add), r = t;
    else split(t->r, t->r, r, key, add + 1 + getSize(t->l)), l = t;
    updateNode(t);
  }
  void merge(pnode &t, pnode l, pnode r) {
    pushLazy(l);
    pushLazy(r);
    if(!l || !r) t = l ? l : r;
    else if(l->prior > r->prior) merge(l->r, l->r, r), t = l;
    else merge(r->l, l, r->l), t = r;
    updateNode(t);
  }
  void insert(pnode &t, int idx, T val) {
    pnode left, mid, right;
    split(t, left, right, idx);
    mid = new node(val);
    merge(mid, mid, right);
    merge(t, left, mid);
  }
  void sendToStart(pnode &t, int l, int r) {
    pnode left, mid, right;
    split(t, left, mid, l);
    split(mid, mid, right, r - l + 1);
    merge(t, mid, left);
    merge(t, t, right);
  }
  void preOrder(pnode t) {
    pushLazy(t);
    if(!t) return;
    preOrder(t->l);
    cout << t->key << " ";
    preOrder(t->r);
  }
  public:
  pnode root;
  ImplicitTreap(){
    root = NULL; 
    srand(time(NULL));
  };
  void insert(int pos, T key) { insert(root, pos, key); }
  void preOrder() { preOrder(root); }
  void sendToStart(int l, int r) { sendToStart(root, l, r); }
};