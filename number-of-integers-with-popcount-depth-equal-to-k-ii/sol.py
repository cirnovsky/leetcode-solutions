class BIT:
    def __init__(self, size):
        self.n = size
        self.tree = [0] * (size + 1)
    def add(self, pos, delta):
        while pos <= self.n:
            self.tree[pos] += delta
            pos += pos & -pos
    def ask(self, pos):
        res = 0
        while pos > 0:
            res += self.tree[pos]
            pos -= pos & -pos
        return res
    def rask(self, l, r):
        return self.ask(r) - self.ask(l - 1)
class Solution:
    def popcountDepth(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        def foo_(n):
            if n == 1:
                return 1
            return foo_(n.bit_count()) + 1
        def foo(n):
            return 0 if n == 1 else foo_(n.bit_count())
        trees = [BIT(len(nums)) for _ in range(6)]
        for i, x in enumerate(nums):
            trees[foo(x)].add(i + 1, 1)
        ans = []
        for uu in queries:
            if uu[0] == 1:
                ans.append(trees[uu[3]].rask(uu[1] + 1, uu[2] + 1))
            else:
                trees[foo(nums[uu[1]])].add(uu[1] + 1, -1)
                nums[uu[1]] = uu[2]
                trees[foo(nums[uu[1]])].add(uu[1] + 1, 1)
        return ans
