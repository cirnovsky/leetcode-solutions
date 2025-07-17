from collections import deque
class Solution:
    def minJumps(self, arr: list[int]) -> int:
        mp = {}
        cnt = len(arr)
        for i, x in enumerate(arr):
            if x not in mp:
                mp[x] = cnt
                cnt += 1
        adj = [[] for i in range(cnt)]
        for i in range(0, len(arr)):
            if i - 1 >= 0:
                adj[i].append((i - 1, 1))
            if i + 1 < len(arr):
                adj[i].append((i + 1, 1))
        for i, x in enumerate(arr):
            adj[i].append((mp[x], 1))
            adj[mp[x]].append((i, 0))
        q = deque([0])
        d = [10**18] * cnt
        d[0] = 0
        while q:
            u = q[0]
            q.popleft()
            for v, w in adj[u]:
                if d[v] > d[u] + w:
                    d[v] = d[u] + w
                    q.append(v)
        return d[len(arr) - 1]

u = Solution()
print(u.minJumps([100,-23,-23,404,100,23,23,23,3,404]))
print(u.minJumps([7]))
print(u.minJumps([7,6,9,6,9,6,9,7]))
