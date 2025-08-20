#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include <chrono>

/// {{{ definitions
using ll = long long;
using ull = unsigned long long;
using db = double;
using ldb = long double;

#define pb push_back
#define eb emplace_back
#define mkp std::make_pair
#define allu(u) (u).begin(), (u).end()
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
#define rng(l, r) std::uniform_int_distribution<ll>(l, r - 1)(rnd)

#define rep1(n) for (int _ = 0; _ < n; ++_)
#define rep2(i, n) for (int i = 0; i < (n); ++i)
#define rep3(i, l, h) for (auto i = (l); i < (h); ++i)
#define rep4(i, l, h, d) for (auto i = (l); i < (h); i += (d))
#define drep1(n) for (int _ = (n) - 1; _ >= 0; --_)
#define drep2(i, n) for (int i = (n) - 1; i >= 0; --i)
#define drep3(i, h, l) for (auto i = (h) - 1; i >= l; --i)
#define drep4(i, h, l, d) for (auto i = (h) - 1; i >= l; i -= (d))
#define __overload(a, b, c, d, e, ...) e
#define rep(...) __overload(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)
#define drep(...) __overload(__VA_ARGS__, drep4, drep3, drep2, drep1)(__VA_ARGS__)

using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vll = std::vector<ll>;
using vvll = std::vector<vll>;
using bsi = std::basic_string<int>;
template <typename Tp>
using vt = std::vector<Tp>;
template <typename Tp>
using bst = std::basic_string<Tp>;

template <typename Tp> void rd(Tp& x) { std::cin >> x; }
template <typename Tp, typename... Args>
void rd(Tp& x, Args&... args) {
	rd(x), rd(args...);
}
template <typename Tp>
void rds(Tp* v, int n) {
	for (int i = 0; i < n; ++i)
		rd(v[i]);
}
template <typename Tp>
void rds(std::vector<Tp> &v) {
	for (Tp& x : v)
		rd(x);
}
template <typename Tp>
void prts(std::vector<Tp> &v, char sep=' ', char end='\n') {
	const int n = v.size();

	if (n == 0) {
		std::cout << end;
		return;
	}
	for (int i = 0; i < n - 1; ++i)
		std::cout << v[i] << sep;
	std::cout << v[n - 1] << end;
}
template <typename Tp>
Tp& cmax(Tp& x, const Tp& y) {
	return x = std::max(x, y);
}
template <typename Tp>
Tp& cmin(Tp& x, const Tp& y) {
	return x = std::min(x, y);
} // }}}

using namespace std;

const int INF = 1e9;

int op(int x, int y) { return min(x, y); }
int e() { return INF; }
    #include <cassert>

struct RMQ {
    const int n;
    int t;
    vvi fi;
    RMQ(const vi& v) : n(v.size()) {
        t = __lg(n)+1;
        fi = vvi(t);
        fi[0] = v;
        for (int i=1;i<t;++i) {
            fi[i] = vi(n-(1<<i)+1);
            for (int j=0;j+(1<<i)<=n;++j) {
                fi[i][j] = std::min(fi[i-1][j], fi[i-1][j+(1<<(i-1))]);
            }
        }
    }
    int min(int l, int r) {
        assert(0 <= l && l < r && r <= n);
        int k = __lg(r-l);
        return std::min(fi[k][l], fi[k][r-(1<<k)]);
    }
};

class Solution {
public:
	int solve(int n, int m, vi sa, vi da, vi sb, vi db) {
		const int N = 1e5 + 1145;
		vi f1(N + 1, INF), f2(N + 1, INF);
		rep(i, m) {
		  cmin(f1[sb[i]], db[i]);
		  cmin(f2[sb[i]], db[i] + sb[i]);
		}
		RMQ t1(f1), t2(f2);
		int res = INF;
		rep(i, n) {
			int in = sa[i] + da[i] + t1.min(sa[i], min(sa[i] + da[i], N + 1));
			int out = sa[i] + da[i] >= N ? INF : t2.min(sa[i] + da[i], N + 1);
      cmin(res, min(in, out));
		}
		return res;
	}
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, vector<int>& waterStartTime, vector<int>& waterDuration) {
    	const int n = landStartTime.size();
    	const int m = waterDuration.size();
    	return min(solve(n, m, landStartTime, landDuration, waterStartTime, waterDuration),
    	           solve(m, n, waterStartTime, waterDuration, landStartTime, landDuration));
    }
};
©leetcode
