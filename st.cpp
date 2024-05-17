#include <bits/stdc++.h>
using namespace std;

struct st_t {
    long long val;
    long long lazy;
    static const long long null_l = 0;

    //initial value, used when er initializing & for returning outside node (but technically it shudnt happen i think)
    st_t(): val(0), lazy(null_l) {}

    //used when initializing given a value
    st_t(long long v): val(v), lazy(null_l) {}

    // used when updating when passing a value v
    st_t(bool lz, long long v): lazy(v) {}

    // push up, used in init, returning update & query
    st_t op(st_t& other) {
        return st_t(val + other.val);
    }

    // push up when only one node is in range
    st_t op(bool rhs) {
        return *this;
    }

    // applying lazy, used when reaching the final node in update / when theres lazy in querying
    void lazy_app(int size) {
        if(lazy == null_l)return;
        val = lazy;
    }

    // used when pushing down lazy to children nodes & combining lazy to target node when updating
    // NOTE: remember to not accidentally push down er null_l, so ig can return if v.lazy == null_l
    long long lazy_comb(st_t& v) {
        return lazy + v.lazy;
    }
};

template <typename num_t> 
struct segtree {
    int n;
    int inline ls(int i){return 2*i+1; }
    int inline rs(int i){return 2*i+2; }
    vector<num_t> tree;

    void init(int s, vector<long long>& arr) {
        n = s;
        tree = vector<num_t>(4 * s);
        init(0, 0, n - 1, arr);
    }

    num_t init(int i, int l, int r, vector<long long>& arr) {
        if (l == r) return tree[i] = num_t(arr[l]);
        int mid = (l + r) / 2;
        num_t a = init(ls(i), l, mid, arr),
              b = init(rs(i), mid + 1, r, arr);
        return tree[i] = a.op(b);
    }

    void update(int l, int r, long long v) {
        if (l > r) return;
        update(0, 0, n - 1, l, r, num_t(true, v));
    }

    num_t update(int i, int tl, int tr, int ql, int qr, num_t v) {
        eval_lazy(i, tl, tr);
	
        if (tr < ql || qr < tl) return tree[i];
        if (ql <= tl && tr <= qr) {
            tree[i].lazy = tree[i].lazy_comb(v);
            eval_lazy(i, tl, tr);
            return tree[i];
        }

        int mid = (tl + tr) / 2;
        num_t a = update(ls(i), tl, mid, ql, qr, v),
              b = update(rs(i), mid + 1, tr, ql, qr, v);
        return tree[i] = a.op(b);
    }

    num_t query(int l, int r) {
        // if (l > r) return num_t::null_v;
        assert(r >= l);
        return query(0, 0, n-1, l, r);
    }

    num_t query(int i, int tl, int tr, int ql, int qr) {
        eval_lazy(i, tl, tr);

        if (ql <= tl && tr <= qr) return tree[i];

        int mid = (tl + tr) / 2;

        if(mid >= ql && qr >= tl && tr >= ql && qr >= mid+1){
            num_t a = query(ls(i), tl, mid, ql, qr);
            num_t b = query(rs(i), mid + 1, tr, ql, qr);
            return a.op(b);
        }else if(mid >= ql && qr >= tl){
            num_t a = query(ls(i), tl, mid, ql, qr);
            return a.op(false);
        }else if(tr >= ql && qr >= mid+1){
            num_t b = query(rs(i), mid + 1, tr, ql, qr);
            return b.op(true);
        }
        return num_t::null_l; // wont happen kot probably
    }

    void eval_lazy(int i, int l, int r) {
        tree[i].lazy_app(r - l + 1);
        if (l != r) {
            tree[ls(i)].lazy = tree[ls(i)].lazy_comb(tree[i]);
            tree[rs(i)].lazy = tree[rs(i)].lazy_comb(tree[i]);
        }
        tree[i].lazy = num_t::null_l;

    }
};
