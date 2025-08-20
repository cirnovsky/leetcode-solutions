
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include <chrono>
#include <cassert>

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

class Solution
{
	public:
	vi subarrayMajority(vi &nums, vector<vi> &queries)
	{
		const int n = nums.size(), q = queries.size();
		const int B = sqrt(n);
		vi id(q);
		iota(allu(id), 0);
		sort(allu(id), [&](int lhs, int rhs)
			{
				int l1 = queries[lhs][0], l2 = queries[rhs][0];
				int r1 = queries[lhs][1], r2 = queries[rhs][1];
				if (l1 / B == l2 / B)
				{
					return r1 < r2;
				}
				else
				{
					return l1 / B < l2 / B;
				}
			});
		vi mp;
		{ // discretisation
			vi dup(allu(nums));
			sort(allu(dup));
			const auto last = unique(allu(dup));
			mp.resize(last - dup.begin());
			for (auto &x : nums)
			{
				int y = lower_bound(dup.begin(), last, x) - dup.begin();
				mp[y] = x;
				x = y;
			}
		}
		vi bucket(n), mn(n), bucket2(n);
		const int INF = numeric_limits<int>::max();
		vi ans(q);
		int start = 0, end = 0;
		int last = -1, now = INF;
		rep(i, q)
		{
			int l = queries[id[i]][0], r = queries[id[i]][1] + 1, low = queries[id[i]][2];
			const int L = l / B * B, R = min((l / B + 1) * B, n);
			if (L <= l && r <= R)
			{
				int &res = ans[id[i]];
				res = INF;
				rep(j, l, r)
				{
					int &cnt = bucket2[nums[j]];
					cnt++;
					if (cnt >= low)
					{
						if (res == INF)
						{
							res = nums[j];
						}
						else if (cnt > bucket2[res])
						{
							res = nums[j];
						}
						else if (cnt == bucket2[res])
						{
							cmin(res, nums[j]);
						}
					}
				}
				rep(j, l, r)
				{
					bucket2[nums[j]]--;
				}
			}
			else
			{
				auto add = [&](int x)
				{
					bucket[x]++;
					if (now == INF || bucket[x] > bucket[now])
					{
						now = x;
					}
					else if (bucket[x] == bucket[now])
					{
						cmin(now, x);
					}
				};
				if (l / B != last)
				{
					while (start < R)
					{
						bucket[nums[start++]]--;
					}
					while (end > L)
					{
						bucket[nums[--end]]--;
					}
					last = l / B;
					now = INF;
				}
				while (end < r)
				{
					add(nums[end++]);
				}
				int tmp = now;
				while (start > l)
				{
					add(nums[--start]);
				}
				ans[id[i]] = now == INF ? now : (bucket[now] >= low ? now : INF);
				now = tmp;
				while (start < R)
				{
					bucket[nums[start++]]--;
				}
			}
		}
		for (auto &x : ans)
		{
			if (x == INF)
			{
				x = -1;
			}
			else
			{
				assert(x != (int) mp.size());
				x = mp[x];
			}
		}
		return ans;
	}
};

int main()
{
	int n, q;
	cin >> n >> q;
	vi nums(n);
	rds(nums);
	vector<vi> queries(q, vi(3));
	for (auto &query : queries)
	{
		rds(query);
	}
	Solution u;
	vi test;
	prts(test = u.subarrayMajority(nums, queries));
}
