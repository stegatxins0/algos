#include <algorithm>
#include <vector>

// {{{ DSU
struct dsu {
  public:
    dsu() : _n(0) {}
    explicit dsu(int n) : _n(n), par_siz(n, -1) {}

    int merge(int a, int b) {
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-par_siz[x] < -par_siz[y]) std::swap(x, y);
        par_siz[x] += par_siz[y];
        par_siz[y] = x;
        return x;
    }

    bool same(int a, int b) {
        return leader(a) == leader(b);
    }

    int leader(int a) {
        if (par_siz[a] < 0) return a;
        return par_siz[a] = leader(par_siz[a]);
    }

    int size(int a) {
        return -par_siz[leader(a)];
    }

    std::vector<std::vector<int>> groups() {
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            std::remove_if(result.begin(), result.end(),
                           [&](const std::vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }

  private:
    int _n;
    std::vector<int> par_siz;
};
// }}}
