import pprint
class Solution:
    def countTrapezoids(self, points: list[list[int]]) -> int:
        n = len(points)
        idx = 0
        dic = {}
        def slope(i, j):
            x1, y1 = points[i]
            x2, y2 = points[j]
            if x1 == x2:
                return float('inf')
            return round((y2 - y1) / (x2 - x1), 8)
        def intercept(i, j):
            x1, y1 = points[i]
            return round(y1 - x1 * slope(i, j), 8)
        def altin(i, j):
            x1, y1 = points[i]
            return round(x1, 8)
        for i in range(n):
            for j in range(i + 1, n):
                # if slope(i, j) == 1.5152:
                    # print(points[i], points(j))
                if slope(i, j) not in dic:
                    dic[slope(i, j)] = {}
                    idx += 1
                if slope(i, j) == float('inf'):
                    if altin(i, j) not in dic[slope(i, j)]:
                        dic[slope(i, j)][altin(i, j)] = 0
                    dic[slope(i, j)][altin(i, j)] += 1
                else:
                    if intercept(i, j) not in dic[slope(i, j)]:
                        dic[slope(i, j)][intercept(i, j)] = 0
                    dic[slope(i, j)][intercept(i, j)] += 1
        def choose(n):
            if n < 2:
                return 0
            return n * (n - 1) // 2
        ans = 0
        pprint.pprint(dic)
        for arr in dic.values():
            mag = 0
            for mm in arr.values():
                mag += mm
                ans -= choose(mm)
            ans += choose(mag)
        def count(points):
            st = set(map(tuple, points))
            res = 0
            for i in range(len(points)):
                x1, y1 = points[i]
                for j in range(len(points)):
                    if i == j:
                        continue
                    x2, y2 = points[j]
                    for k in range(j + 1, len(points)):
                        x3, y3 = points[k]
                        x4, y4 = x1 + x2 - x3, y1 + y2 - y3
                        if i == k or j == k or (x1 == x2 == x3 == x4 or y1 == y2 == y3 == y4):
                            continue
                        res += (x4, y4) in st
                        # if (x4, y4) in st:
                            # print(points[i], points[j], points[k], [x4, y4])
            return res // 4
        return ans - count(points)

u = Solution()
print(u.countTrapezoids([[13,53],[-72,-80],[48,56],[52,78],[48,43],[-28,47],[-15,43],[39,78],[48,-35],[-41,83],[-22,63],[-15,-11],[17,43],[44,78]]))
