template <class T>
class Treap {
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
  void split (pnode t, T key, pnode &l, pnode &r) {
    if (!t) l = r = NULL;
    else if (key < t->key) split (t->l, key, l, t->l),  r = t;
    else split (t->r, key, t->r, r),  l = t;
    updateNode(t);
  }
  void merge(pnode &t, pnode l, pnode r) {
    if(!l || !r) t = l ? l : r;
    else if(l->prior > r->prior) merge(l->r, l->r, r), t = l;
    else merge(r->l, l, r->l), t = r;
    updateNode(t);
  }
  void insert(pnode it, pnode &t) {
    if(!t) t = it;
    else if(it->prior > t->prior) split(t, it->key, it->l, it->r), t = it;
    else insert(it, it->key < t->key ? t->l : t->r);
    updateNode(t);
  }
  void erase(T key, pnode &t) {
    if(!t) return;
    if(t->key == key) merge(t, t->l, t->r);
    else erase(key, key < t->key ? t->l : t->r);
    updateNode(t);
  }
  void preOrder(pnode t) {
    if(!t) return;
    preOrder(t->l);
    cout << t->key << endl;
    preOrder(t->r);
  }
  int lessOrEqualThanK(T key, pnode t) {
    if(!t) return 0;
    if(t->key <= key) return getSize(t->l) + 1 + lessOrEqualThanK(key, t->r);
    else return lessOrEqualThanK(key, t->l);
  }
  public:
  pnode root;
  Treap(){
    root = NULL; 
    srand(time(NULL));
  };
  void insert(T key) { insert(new node(key), root); }
  void erase(T key) { erase(key, root); }
  void preOrder() { preOrder(root); }
  int lessOrEqualThanK(T key) { return lessOrEqualThanK(key, root); }
  int getQtdInRange(T left, T right) { return lessOrEqualThanK(right, root) - lessOrEqualThanK(left - 1, root); }
  int getSizeTree() { return getSize(root); }
};