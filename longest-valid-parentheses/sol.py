import itertools

class Solution:
    def longestValidParentheses(self, s: str) -> int:
        arr = list(itertools.accumulate(map(lambda x : 1 if x == '(' else -1, s)))

u = Solution()
print(u.longestValidParentheses(")()())"))
