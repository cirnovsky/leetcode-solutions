class Solution:
    def threeSum(self, nums: list[int]) -> list[list[int]]:
        ans = []
        indexes = {}
        count = {}
        for num in nums:
            if num not in count:
                count[num] = 0
            count[num] += 1
        nums = []
        for num in count.keys():
            nums.extend([num] * min(3, count[num]))
        for i, num in enumerate(nums):
            if num not in indexes:
                indexes[num] = []
            indexes[num].append(i)
        print(nums, indexes)
        for i in range(len(nums)):
            for j in range(i + 1, len(nums)):
                if -(nums[i] + nums[j]) in indexes:
                    for k in indexes[-(nums[i] + nums[j])]:
                        if k > j:
                            ans.append(sorted([nums[i], nums[j], nums[k]]))
        ans.sort()
        tmp = []
        i = 0
        while i < len(ans):
            tmp.append(ans[i])
            j = i
            while j < len(ans) and ans[j] == ans[i]:
                j += 1
            i = j
        return tmp
