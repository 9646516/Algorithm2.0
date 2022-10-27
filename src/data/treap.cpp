template <typename T> struct Treap {
  private:
    static const int P = 1e9 + 7;
    struct Node {
        Node *son[2];
        int key, cnt, size;
        T v;
        Node(T v) : key(rand() % P), v(v), cnt(1), size(1) { son[0] = son[1] = null; }
        Node(void *) : key(P), cnt(0), size(0) { son[0] = son[1] = 0; }
        int MinID() { return son[0]->key > son[1]->key; }
        void Up() { size = son[0]->size + cnt + son[1]->size; }
    } * root;
    static Node *null;
    static void Trans(Node *&pos, int d) {
        Node *s = pos->son[d];
        pos->son[d] = s->son[!d];
        s->son[!d] = pos;
        pos->Up(), s->Up();
        pos = s;
    }
    static int Adjust(Node *&pos) {
        int d = pos->MinID();
        if (pos->key > pos->son[d]->key) {
            Trans(pos, d);
            return !d;
        } else
            return -1;
    }
    static void Insert(Node *&pos, T v) {
        if (pos == null)
            pos = new Node(v);
        else if (pos->v == v) {
            pos->cnt++;
            pos->Up();
        } else {
            Insert(pos->son[pos->v < v], v);
            pos->Up();
            Adjust(pos);
        }
    }
    static void Remove(Node *&pos) {
        if (pos->son[0] == null && pos->son[1] == null)
            pos = null;
        else {
            int p = Adjust(pos);
            Remove(pos->son[p]);
            pos->Up();
        }
    }
    static void Delete(Node *&pos, T v) {
        if (pos->v == v) {
            if (--pos->cnt == 0) {
                pos->key = P;
                Remove(pos);
            } else
                pos->Up();
        } else {
            Delete(pos->son[pos->v < v], v);
            pos->Up();
        }
    }

  public:
    Treap() : root(null) {}
    void Insert(T x) { Insert(root, x); }
    void Delete(T x) { Delete(root, x); }
    // number of nodes < v
    int Rank(T v) {
        int res = 0;
        for (Node *pos = root; pos != null;)
            if (pos->v < v) {
                res += pos->cnt + pos->son[0]->size;
                pos = pos->son[1];
            } else
                pos = pos->son[0];
        return res;
    }
    // 1 based
    T Kth(int k) {
        for (Node *pos = root; pos != null;)
            if (pos->son[0]->size + 1 <= k && k <= pos->son[0]->size + pos->cnt)
                return pos->v;
            else if (k <= pos->son[0]->size)
                pos = pos->son[0];
            else {
                k -= pos->son[0]->size + pos->cnt;
                pos = pos->son[1];
            }
        throw;
    }
    T Pred(T v) {
        int res;
        for (Node *pos = root; pos != null;) {
            if (pos->v < v) {
                res = pos->v;
                pos = pos->son[1];
            } else
                pos = pos->son[0];
        }
        return res;
    }
    T Succ(T v) {
        int res;
        for (Node *pos = root; pos != null;) {
            if (pos->v > v) {
                res = pos->v;
                pos = pos->son[0];
            } else
                pos = pos->son[1];
        }
        return res;
    }
};
template <typename T> typename Treap<T>::Node *Treap<T>::null = new Treap<T>::Node((void *)0);
