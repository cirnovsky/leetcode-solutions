class Solution:
    def findMedianSortedArrays(self, nums1: list[int], nums2: list[int]) -> float:
        INF = float("inf")
        n, m = len(nums1), len(nums2)
        if n == 0:
            return self.findMedianSortedArrays(nums2, nums1)
        nums1.insert(0, -INF)
        nums2.insert(0, -INF)
        low, high = 0, n
        while low <= high:
            i = (low + high) // 2
            j = (n + m + 1) // 2 - i
            if j > m:
                low = i + 1
                continue
            elif j < 0:
                high = i - 1
                continue
            lmax = max(nums1[i], nums2[j])
            rmin = min(INF if i + 1 > n else nums1[i + 1], INF if j + 1 > m else nums2[j + 1])
            if lmax <= rmin:
                return lmax if (n + m) % 2 == 1 else (lmax + rmin) / 2
            elif nums1[i] > rmin:
                high = i - 1
            else:
                low = i + 1
        return 114514

u = Solution()
print(u.findMedianSortedArrays([3], [-2, -1]))
print(u.findMedianSortedArrays([1,2,3,4,5], [6,7,8,9,10,11,12,13,14,15,16,17]))
print(u.findMedianSortedArrays([6,7,8,9,10,11,12,13,14,15,16,17], [1,2,3,4,5]))
print(u.findMedianSortedArrays([], [1]))
print(u.findMedianSortedArrays([1, 3], [2]))
print(u.findMedianSortedArrays([1, 2], [3, 4]))
