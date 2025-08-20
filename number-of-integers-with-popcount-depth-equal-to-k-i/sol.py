class Solution:
    def popcountDepth(self, n: int, k: int) -> int:
        if k == 0:
            return 1
        def f(n):
            if n == 0:
                return -1
            if n == 1:
                return 0
            return f(n.bit_count()) + 1
        bits = bin(n)[2:]
        memo = [[[-1 for _ in range(2)] for _ in range(len(bits) + 2)] for _ in range(len(bits) + 1)]
        def dp(pos, cnt, limit, upper):
            if cnt > upper:
                return 0
            if pos == len(bits):
                return int(cnt == upper)
            if memo[pos][cnt][limit] != -1:
                return memo[pos][cnt][limit]
            res = 0
            upp = int(bits[pos]) if limit else 1
            for i in range(0, upp + 1):
                res += dp(pos + 1, cnt + i, limit and i == upp, upper)
            memo[pos][cnt][limit] = res
            return res
        res = 0
        # for i in range(1, n + 1):
            # if f(i) == k:
                # res += 1
                # print(bin(i))
        # return res
        for i in range(1, len(bits) + 1):
            if f(i) + 1 == k:
                # print(i, bits)
                res += dp(0, 0, True, i) - (i == 1)
                memo = [[[-1 for _ in range(2)] for _ in range(len(bits) + 2)] for _ in range(len(bits) + 1)]
        return res

u = Solution()
print(u.popcountDepth(4, 1))
print(u.popcountDepth(7, 2))
# print(u.popcountDepth(10**15, 4))
print(u.popcountDepth(15, 2))
