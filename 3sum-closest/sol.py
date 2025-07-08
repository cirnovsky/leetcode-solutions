class Solution:
    def threeSumClosest(self, nums: list[int], target: int) -> int:
        nums.sort()
        def cmin(a, b):
            return a if abs(target - a) < abs(target - b) else b
        ans = 10**18
        for i in range(len(nums)):
            l, r = i + 1, len(nums)
            while l < r - 1:
                s = nums[i] + nums[l] + nums[r - 1]
                ans = cmin(ans, s)
                if s < target:
                    l += 1
                elif s > target:
                    r -= 1
                else:
                    l += 1
                    r -= 1
        return ans

u = Solution()
print(u.threeSumClosest([1, 1, 1, 0], -100))
