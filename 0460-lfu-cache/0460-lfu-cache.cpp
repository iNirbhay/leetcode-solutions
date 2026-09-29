class LFUCache {

    struct Node {

        int key;
        int value;
        int freq;

        Node* prev;
        Node* next;

        Node(int k, int v) {

            key = k;
            value = v;
            freq = 1;

            prev = nullptr;
            next = nullptr;
        }
    };

    struct DLL {

        Node* head;
        Node* tail;

        int size;

        DLL() {

            head = new Node(0, 0);
            tail = new Node(0, 0);

            head->next = tail;
            tail->prev = head;

            size = 0;
        }

        void addFirst(Node* node) {

            node->next = head->next;
            node->prev = head;

            head->next->prev = node;
            head->next = node;

            size++;
        }

        void remove(Node* node) {

            node->prev->next = node->next;
            node->next->prev = node->prev;

            size--;
        }

        Node* removeLast() {

            if (size == 0)
                return nullptr;

            Node* node = tail->prev;

            remove(node);

            return node;
        }
    };

    unordered_map<int, Node*> nodes;
    unordered_map<int, DLL*> freqList;

    int capacity;
    int size;
    int minFreq;

public:

    LFUCache(int capacity) {

        this->capacity = capacity;
        size = 0;
        minFreq = 0;
    }

    int get(int key) {

        if (nodes.find(key) == nodes.end())
            return -1;

        Node* node = nodes[key];

        increaseFrequency(node);

        return node->value;
    }

    void put(int key, int value) {

        if (capacity == 0)
            return;

        if (nodes.find(key) != nodes.end()) {

            Node* node = nodes[key];

            node->value = value;

            increaseFrequency(node);

            return;
        }

        if (size == capacity) {

            DLL* list =
                freqList[minFreq];

            Node* removed =
                list->removeLast();

            nodes.erase(removed->key);

            delete removed;

            size--;
        }

        Node* node =
            new Node(key, value);

        nodes[key] = node;

        if (!freqList.count(1))
            freqList[1] = new DLL();

        freqList[1]->addFirst(node);

        minFreq = 1;

        size++;
    }

private:

    void increaseFrequency(Node* node) {

        int oldFreq = node->freq;

        DLL* oldList =
            freqList[oldFreq];

        oldList->remove(node);

        if (oldFreq == minFreq &&
            oldList->size == 0) {

            minFreq++;
        }

        node->freq++;

        if (!freqList.count(node->freq))
            freqList[node->freq] = new DLL();

        freqList[node->freq]->addFirst(node);
    }
};