class Solution:
    def __init__(self):
        self.ans = []
    def solve(self, n, l, r, cur):
        if l >= n and r >= n:
            self.ans.append(cur)
            return
        if l < n:
            self.solve(n, l + 1, r, cur + '(')
        if r < n and r < l:
            self.solve(n, l, r + 1, cur + ')')
    def generateParenthesis(self, n: int) -> list[str]:
        self.solve(n, 0, 0, '')
        return self.ans
        
solution = Solution()
print(solution.generateParenthesis(3))
