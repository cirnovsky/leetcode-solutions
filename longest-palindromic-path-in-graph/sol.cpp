#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxLen(int n, vector<vector<int>>& edges, string label) {
        vector dp(1 << n, vector(n, vector<int>(n)));
        for (int i = 0; i < n; ++i)
            dp[1 << i][i][i] = 1;
        vector adj(n, vector<int>());
        for (auto &&e : edges)
            adj[e[0]].push_back(e[1]), adj[e[1]].push_back(e[0]);
        for (int mask = 0; mask < (1 << n); ++mask)
            for (int i = 0; i < n; ++i)
                if ((mask >> i) & 1)
                    for (int j = 0; j < n; ++j)
                        if (((mask >> j) & 1) && (
                            __builtin_popcount(mask) == 1 || i != j
                        ) && dp[mask][i][j])
                            for (int k : adj[i])
                                if (~(mask >> k) & 1)
                                    for (int l : adj[j])
                                        if ((~(mask >> l) & 1) && k != l && label[k] == label[l])

                                            dp[mask | (1 << k) | (1 << l)][k][l] |= dp[mask][i][j];

        int res = 0;
        for (int mask = 0; mask < (1 << n); ++mask)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    if (dp[mask][i][j])
                        res = max(res, __builtin_popcount(mask));

        return res;
    }
};
int main()
{
  Solution u;
  cout << u.maxLen(3, {{2, 0}, {2, 1}}, "mll")
}
