# **same length**
class Solution:
    def findSubstring(self, s: str, words: list[str]) -> list[int]:
        L = len(words[0])
        count = {}
        used = [False for _ in range(L)]
        for word in words:
            if word not in count:
                count[word] = 0
            count[word] += 1
        def check(pos):
            i = pos
            while i >= 0:
                if s[i : i + L]

u = Solution()
print(u.findSubstring("barfoothefoobarman", ["foo", "bar"]))
