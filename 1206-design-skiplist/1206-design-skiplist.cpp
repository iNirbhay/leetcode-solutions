class Skiplist {

    static const int MAX_LEVEL = 16;

    struct Node {
        int val;
        vector<Node*> next;

        Node(int value, int level)
            : val(value),
              next(level, nullptr) {}
    };

    Node* head;

    int randomLevel() {

        int level = 1;

        while (
            level < MAX_LEVEL &&
            (rand() & 1)
        ) {
            level++;
        }

        return level;
    }

public:

    Skiplist() {

        head =
            new Node(-1, MAX_LEVEL);
    }

    bool search(int target) {

        Node* curr = head;

        for (int level = MAX_LEVEL - 1;
             level >= 0;
             level--) {

            while (
                curr->next[level] &&
                curr->next[level]->val < target
            ) {

                curr = curr->next[level];
            }
        }

        curr = curr->next[0];

        return curr &&
               curr->val == target;
    }

    void add(int num) {

        vector<Node*> update(MAX_LEVEL);

        Node* curr = head;

        for (int level = MAX_LEVEL - 1;
             level >= 0;
             level--) {

            while (
                curr->next[level] &&
                curr->next[level]->val < num
            ) {

                curr = curr->next[level];
            }

            update[level] = curr;
        }

        int levelCount = randomLevel();

        Node* node =
            new Node(num, levelCount);

        for (int i = 0;
             i < levelCount;
             i++) {

            node->next[i] =
                update[i]->next[i];

            update[i]->next[i] = node;
        }
    }

    bool erase(int num) {

        vector<Node*> update(MAX_LEVEL);

        Node* curr = head;

        for (int level = MAX_LEVEL - 1;
             level >= 0;
             level--) {

            while (
                curr->next[level] &&
                curr->next[level]->val < num
            ) {

                curr = curr->next[level];
            }

            update[level] = curr;
        }

        curr = curr->next[0];

        if (!curr || curr->val != num)
            return false;

        for (int i = 0;
             i < MAX_LEVEL;
             i++) {

            if (update[i]->next[i] != curr)
                break;

            update[i]->next[i] =
                curr->next[i];
        }

        delete curr;

        return true;
    }
};