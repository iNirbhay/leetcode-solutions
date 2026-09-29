class TextEditor {

    struct Node {

        char ch;

        Node* prev;
        Node* next;

        Node(char c) {

            ch = c;
            prev = nullptr;
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;

    // Cursor is the node immediately
    // AFTER the cursor position.
    Node* cursor;

public:

    TextEditor() {

        head = new Node('#');
        tail = new Node('#');

        head->next = tail;
        tail->prev = head;

        cursor = tail;
    }

    void addText(string text) {

        for (char c : text) {

            Node* node =
                new Node(c);

            Node* prev =
                cursor->prev;

            prev->next = node;
            node->prev = prev;

            node->next = cursor;
            cursor->prev = node;
        }
    }

    int deleteText(int k) {

        int deleted = 0;

        while (
            k > 0 &&
            cursor->prev != head
        ) {

            Node* node =
                cursor->prev;

            node->prev->next = cursor;
            cursor->prev = node->prev;

            delete node;

            deleted++;
            k--;
        }

        return deleted;
    }

    string cursorLeft(int k) {

        while (
            k > 0 &&
            cursor->prev != head
        ) {

            cursor = cursor->prev;
            k--;
        }

        return getLastTen();
    }

    string cursorRight(int k) {

        while (
            k > 0 &&
            cursor != tail
        ) {

            cursor = cursor->next;
            k--;
        }

        return getLastTen();
    }

private:

    string getLastTen() {

        string result;

        Node* curr =
            cursor->prev;

        int count = 0;

        while (
            curr != head &&
            count < 10
        ) {

            result.push_back(curr->ch);

            curr = curr->prev;

            count++;
        }

        reverse(
            result.begin(),
            result.end()
        );

        return result;
    }
};