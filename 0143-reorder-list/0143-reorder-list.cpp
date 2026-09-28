class Solution {
public:
    void reorderList(ListNode* head) {

        if (!head || !head->next)
            return;

        // Find middle
        ListNode* slow = head;
        ListNode* fast = head;

        while (
            fast->next &&
            fast->next->next
        ) {

            slow = slow->next;
            fast = fast->next->next;
        }

        // Reverse second half
        ListNode* second = slow->next;
        slow->next = nullptr;

        ListNode* prev = nullptr;

        while (second) {

            ListNode* next = second->next;

            second->next = prev;

            prev = second;
            second = next;
        }

        second = prev;

        // Merge
        ListNode* first = head;

        while (second) {

            ListNode* next1 = first->next;
            ListNode* next2 = second->next;

            first->next = second;
            second->next = next1;

            first = next1;
            second = next2;
        }
    }
};