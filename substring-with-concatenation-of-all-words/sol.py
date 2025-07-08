# **same length**
# extreme case
# aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa, [a, a, a, a, a, a, b]
class Solution:
    def findSubstring(self, s: str, words: list[str]) -> list[int]:
        L = len(words[0])
        count = {}
        for word in words:
            if word not in count:
                count[word] = 0
            count[word] += 1
        def solve(obj):
            if len(obj) < len(words):
                return []
            tmp = len(words)
            now = count.copy()
            print(obj)
            def remove(u):
                if u not in now:
                    now[u] = 0
                now[u] += 1
                if now[u] == 0:
                    now.pop(u)
            def add(u):
                if u not in now:
                    now[u] = 0
                now[u] -= 1
                if now[u] == 0:
                    now.pop(u)
            left, right = 0, 0
            while right < tmp:
                add(obj[right])
                right += 1
            tmp = len(obj)
            res = []
            while right < tmp:
                print(obj[left:right], now)
                if len(now) == 0:
                    res.append(left)
                remove(obj[left])
                add(obj[right])
                left += 1
                right += 1
            if len(now) == 0:
                res.append(left)
            return res
        tmp = len(s)
        res = []
        for offset in range(L):
            ret = solve([s[i:i + L] for i in range(offset, tmp - L + 1, L)])
            res.extend(list(map(lambda x : x * L + offset, ret)))
        return res

u = Solution()
print(u.findSubstring("lingmindraboofooowingdingbarrwingmonkeypoundcake", ["fooo","barr","wing","ding","wing"]))
