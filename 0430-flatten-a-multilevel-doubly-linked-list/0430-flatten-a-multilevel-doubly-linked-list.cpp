class Solution {
public:

    Node* flatten(Node* head) {

        if (!head)
            return head;

        flattenHelper(head);

        return head;
    }

    Node* flattenHelper(Node* curr) {

        Node* node = curr;
        Node* last = curr;

        while (node) {

            Node* next = node->next;

            if (node->child) {

                Node* child = node->child;

                Node* childLast =
                    flattenHelper(child);

                node->next = child;
                child->prev = node;

                node->child = nullptr;

                if (next) {

                    childLast->next = next;
                    next->prev = childLast;
                }

                last = childLast;
            }
            else {

                last = node;
            }

            node = next;
        }

        return last;
    }
};