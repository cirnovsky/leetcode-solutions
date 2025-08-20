from collections import deque
class Solution:
    def findMaxPathScore(self, edges: list[list[int]], online: list[bool], k: int) -> int:
        n = len(online)
        adj = [[] for i in range(n)]
        max_cost = 0
        for e in edges:
            adj[e[0]].append((e[1], e[2]))
            max_cost = max(max_cost, e[2])
        def check(low):
            q = deque([0])
            dis = [10**18] * n
            dis[0] = 0
            while q:
                u = q.popleft()
                for v, w in adj[u]:
                    if w >= low and dis[u] + w < dis[v] and online[v]:
                        dis[v] = dis[u] + w
                        q.append(v)
            return dis[n - 1] <= k
        left, right, ans = 0, max_cost, -1
        while left <= right:
            mid = (left + right) // 2
            if check(mid):
                ans = mid
                left = mid + 1
            else:
                right = mid - 1
        return ans

u = Solution()
print(u.findMaxPathScore(edges = [[0,1,5],[1,3,10],[0,2,3],[2,3,4]], online = [True,True,True,True], k = 10))
