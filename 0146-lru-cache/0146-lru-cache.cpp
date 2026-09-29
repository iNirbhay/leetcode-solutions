class LRUCache {

    struct Node {

        int key;
        int value;

        Node* prev;
        Node* next;

        Node(int k, int v) {
            key = k;
            value = v;
            prev = nullptr;
            next = nullptr;
        }
    };

    unordered_map<int, Node*> mp;

    Node* head;
    Node* tail;

    int capacity;

public:

    LRUCache(int capacity) {

        this->capacity = capacity;

        head = new Node(0, 0);
        tail = new Node(0, 0);

        head->next = tail;
        tail->prev = head;
    }

    void addFirst(Node* node) {

        node->next = head->next;
        node->prev = head;

        head->next->prev = node;
        head->next = node;
    }

    void remove(Node* node) {

        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    int get(int key) {

        if (mp.find(key) == mp.end())
            return -1;

        Node* node = mp[key];

        remove(node);
        addFirst(node);

        return node->value;
    }

    void put(int key, int value) {

        if (mp.find(key) != mp.end()) {

            Node* node = mp[key];

            node->value = value;

            remove(node);
            addFirst(node);

            return;
        }

        Node* node =
            new Node(key, value);

        mp[key] = node;

        addFirst(node);

        if (mp.size() > capacity) {

            Node* last = tail->prev;

            remove(last);

            mp.erase(last->key);

            delete last;
        }
    }
};