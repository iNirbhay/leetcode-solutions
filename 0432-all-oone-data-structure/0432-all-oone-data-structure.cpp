class AllOne {

    struct Node {

        int count;

        unordered_set<string> keys;

        Node* prev;
        Node* next;

        Node(int c) {

            count = c;
            prev = nullptr;
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;

    unordered_map<string, Node*> mp;

public:

    AllOne() {

        head = new Node(0);
        tail = new Node(0);

        head->next = tail;
        tail->prev = head;
    }

    void insertAfter(Node* prev,
                     Node* node) {

        node->next = prev->next;
        node->prev = prev;

        prev->next->prev = node;
        prev->next = node;
    }

    void remove(Node* node) {

        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void inc(string key) {

        if (!mp.count(key)) {

            Node* first = head->next;

            if (first != tail &&
                first->count == 1) {

                first->keys.insert(key);

                mp[key] = first;
            }
            else {

                Node* node = new Node(1);

                node->keys.insert(key);

                insertAfter(head, node);

                mp[key] = node;
            }

            return;
        }

        Node* curr = mp[key];

        Node* next = curr->next;

        if (next != tail &&
            next->count == curr->count + 1) {

            next->keys.insert(key);

            mp[key] = next;
        }
        else {

            Node* node =
                new Node(curr->count + 1);

            node->keys.insert(key);

            insertAfter(curr, node);

            mp[key] = node;
        }

        curr->keys.erase(key);

        if (curr->keys.empty())
            remove(curr);
    }

    void dec(string key) {

        Node* curr = mp[key];

        if (curr->count == 1) {

            curr->keys.erase(key);

            mp.erase(key);
        }
        else {

            Node* prev = curr->prev;

            if (prev != head &&
                prev->count == curr->count - 1) {

                prev->keys.insert(key);

                mp[key] = prev;
            }
            else {

                Node* node =
                    new Node(curr->count - 1);

                node->keys.insert(key);

                insertAfter(prev, node);

                mp[key] = node;
            }

            curr->keys.erase(key);
        }

        if (curr->keys.empty())
            remove(curr);
    }

    string getMaxKey() {

        if (tail->prev == head)
            return "";

        return *tail->prev->keys.begin();
    }

    string getMinKey() {

        if (head->next == tail)
            return "";

        return *head->next->keys.begin();
    }
};