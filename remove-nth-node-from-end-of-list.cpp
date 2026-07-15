/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
// TC: O(n), SC: O(1)
// where n = length of list (not the nth from end of list)
class Solution {
    int findLen(ListNode* head) {
        ListNode* curr = head;
        int count = 0;

        while (curr){
            curr = curr->next;
            
            count++;
        }

        return count;
    }
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* slow = head;
        int count = 0;
        int len = findLen(head);
        int targetIndex = len - n;

        // Removing the head
        if (targetIndex == 0) {
            return head->next;
        }
        
        while (count < targetIndex - 1){
            slow = slow->next;
            count++;
        }
        
        slow->next = slow->next->next;
       
        return head;
    }
};
// divergences:
// - thought I needed curr in the removeNthFromEnd() function