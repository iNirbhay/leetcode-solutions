class MyLinkedList {

    struct Node {
        int val;
        Node* prev;
        Node* next;

        Node(int value) {
            val = value;
            prev = nullptr;
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;
    int size;

public:

    MyLinkedList() {

        head = new Node(0);
        tail = new Node(0);

        head->next = tail;
        tail->prev = head;

        size = 0;
    }

    int get(int index) {

        if (index < 0 || index >= size)
            return -1;

        Node* curr;

        if (index < size / 2) {

            curr = head->next;

            for (int i = 0; i < index; i++)
                curr = curr->next;
        }
        else {

            curr = tail->prev;

            for (int i = size - 1; i > index; i--)
                curr = curr->prev;
        }

        return curr->val;
    }

    void addAtHead(int val) {

        addBetween(
            head,
            head->next,
            val
        );
    }

    void addAtTail(int val) {

        addBetween(
            tail->prev,
            tail,
            val
        );
    }

    void addAtIndex(int index, int val) {

        if (index < 0 || index > size)
            return;

        Node* curr;

        if (index < size / 2) {

            curr = head->next;

            for (int i = 0; i < index; i++)
                curr = curr->next;
        }
        else {

            curr = tail;

            for (int i = size; i > index; i--)
                curr = curr->prev;
        }

        addBetween(
            curr->prev,
            curr,
            val
        );
    }

    void deleteAtIndex(int index) {

        if (index < 0 || index >= size)
            return;

        Node* curr;

        if (index < size / 2) {

            curr = head->next;

            for (int i = 0; i < index; i++)
                curr = curr->next;
        }
        else {

            curr = tail->prev;

            for (int i = size - 1; i > index; i--)
                curr = curr->prev;
        }

        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        delete curr;

        size--;
    }

private:

    void addBetween(
        Node* prev,
        Node* next,
        int val) {

        Node* node = new Node(val);

        node->prev = prev;
        node->next = next;

        prev->next = node;
        next->prev = node;

        size++;
    }
};