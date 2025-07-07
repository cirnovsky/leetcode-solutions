class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        s, tmp = list(s), list(p)
        p = []
        tag = []
        len_tmp = len(tmp)
        i = 0
        while i < len_tmp:
            p.append(tmp[i])
            if i + 1 < len_tmp and tmp[i + 1] == '*':
                tag.append(True)
                while i + 1 < len_tmp and tmp[i + 1] == '*':
                    i += 1
            else:
                tag.append(False)
            i += 1
        dp = [[False for j in range(len(p) + 1)] for i in range(len(s) + 1)]
        visited = [[False for j in range(len(p) + 1)] for i in range(len(s) + 1)]
        def match(i, j):
            if visited[i][j]:
                return dp[i][j]
            visited[i][j] = True
            if i == len(s):
                flag = True
                for k in range(j, len(p)):
                    flag = flag and tag[k]
                dp[i][j] = j == len(p) or flag
                return dp[i][j]
            if j == len(p):
                dp[i][j] = False
                return dp[i][j]
            if s[i] == p[j] or p[j] == '.':
                dp[i][j] = match(i + 1, j + 1) or (tag[j] and (match(i, j + 1) or match(i + 1, j)))
                return dp[i][j]
            else:
                dp[i][j] = tag[j] and match(i, j + 1)
                return dp[i][j]
        return match(0, 0)

sol = Solution()

print(sol.isMatch("aaaaaaaaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*"))

while False:
    s, p = input().split()
    print(sol.isMatch(s, p))
