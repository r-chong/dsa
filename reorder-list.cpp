// 1. Find middle.
// 2. Cut list into two lists.
// 3. Reverse second list only.
// 4. Weave the two lists.

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
// n is length of LList
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        
        while (curr) {
            ListNode* temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }

        return prev;
    }

    ListNode* findMid(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;

        int i = 0;
        while (fast) {
            if (fast->next) {
                fast = fast->next;
            } else {
                break;
            }

            if (i % 2 == 0) {
                slow = slow->next;
            }
            i++;
        }

        return slow;
    }

    void reorderList(ListNode* head) {
        ListNode* left = head;

        ListNode* mid = findMid(head);

        ListNode* right = reverseList(mid);

        while (left && right) {
            ListNode* temp1 = left->next;

            if (left->next == right) {
                break;
            }

            left->next = right;
            left = temp1;

            ListNode* temp2 = right->next;

            if (right->next == left) {
                break;
            }

            right->next = left;
            right = temp2;
        }
    }
};
// divergences:
// - reversing the list meant that left points to the tail.. had to reverse mid
// - was unsure if I should do a linked list reversal... thankfully trusted instincts
// - pointer errors
// - couldn't figure out the invariant