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

#include "atcoder/segtree"

int op(int x, int y) { return min(x, y); }
int e() { return numeric_limits<int>::max(); }

using segt = atcoder::segtree<int, op, e>;

class Solution {
public:
	int solve(int n, int m, vi sa, vi da, vi sb, vi db) {
		const int N = 1e5;
		segt t1(N + 1), t2(N + 1);
		rep(i, m) {
			t1.set(sb[i], db[i]);
			t2.set(sb[i], db[i] + sb[i]);
		}
		int res = numeric_limits<int>::max();
		rep(i, n) {
			int in = sa[i] + da[i] + t1.prod(sa[i], sa[i] + da[i]);
			int out = t2.prod(sa[i] + da[i], N + 1);
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

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(0);
}
