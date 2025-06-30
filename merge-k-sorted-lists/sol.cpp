#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void print(ListNode *lsn) {
  for (ListNode *it = lsn; it != nullptr; it = it->next)
    std::cout << " " << (it->val);
  std::cout << "\n";
}

class Solution {
public:
  void merge(ListNode *lhs, ListNode *rhs) {
    while (lhs != nullptr) {
      ListNode *tmp = lhs->next;
      while (rhs != nullptr && (rhs->val) >= (lhs->val) && (tmp == nullptr || (rhs->val) <= (tmp->val)))
        lhs->next = rhs, lhs = lhs->next, rhs = rhs->next;
      lhs->next = tmp;
      lhs = lhs->next;
    }
  }

  ListNode* mergeKLists(vector<ListNode*>& lists) {
    int n = lists.size();

    for (int turns = 1; turns < n; turns <<= 1)
      for (int i = 0; i + turns < n; i += turns * 2) {
        if (lists[i] == nullptr || (lists[i + turns] != nullptr && lists[i]->val > lists[i + turns]->val))
          std::swap(lists[i], lists[i + turns]);
        merge(lists[i], lists[i + turns]);
      }

    return n ? lists[0] : nullptr;
  }
};

int main(){
  Solution sol;
  vector<ListNode*> vec;
  vec.push_back(new ListNode(2));
  vec.push_back(nullptr);
  vec.push_back(new ListNode(-1));
  // vec.push_back(new ListNode(1, new ListNode(4, new ListNode(5))));
  // vec.push_back(new ListNode(1, new ListNode(3, new ListNode(4))));
  // vec.push_back(new ListNode(2, new ListNode(6)));
  // vec.push_back(new ListNode(2, new ListNode(6)));
  // vec.push_back(new ListNode(2, new ListNode(6)));
  // vec.push_back(new ListNode(2, new ListNode(6)));
  auto result = sol.mergeKLists(vec);
  print(result);
  return 0;
}
