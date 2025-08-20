class Solution:
    def countTrapezoids(self, points: list[list[int]]) -> int:
        dic = {}
        for t in points:
            if t[1] not in dic:
                dic[t[1]] = set()
            dic[t[1]].add(t[0])
        MOD = 10**9+7
        def choose(n, k):
            if n < k:
                return 0
            return n * (n - 1) // k % MOD
        tu = [choose(len(dic[key]), 2) for key in dic]
        all = sum(tu)
        ans = 0
        for val in tu:
            ans += (all - val) * val % MOD
        return ans * (MOD + 1) // 2 % MOD
