# Definition for singly-linked list.

from typing import Optional
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
class Solution:
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        def revers(now):
            for i in range(k // 2):
                cor = now
                print("step: ", k - 1 - i)
                for _ in range(k - 1 - 2 * i):
                    cor = cor.next
                    if cor is None:
                        return None
                cor.val, now.val = now.val, cor.val
                now = now.next
                print(" ", now.val, cor.val)
            for _ in range((k + 1) // 2):
                now = now.next
            return now
        test = head
        while (test := revers(test)) is not None:
            pass
        return head
        
solution = Solution()
tmp = solution.reverseKGroup(ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5))))), 4)
while tmp is not None:
    print(tmp.val, end=' ')
    tmp = tmp.next
