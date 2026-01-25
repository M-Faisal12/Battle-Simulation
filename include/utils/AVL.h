#pragma once

class Unit; // Forward declaration

template <typename K, typename V>
class AVL
{
private:
    struct Node
    {
        K key;
        V value;
        Node *left;
        Node *right;
        int height;

        Node(const K &k, const V &v)
            : key(k), value(v), left(0), right(0), height(1) {}
    };

    Node *root;

    // ---------- Utility ----------
    int max(int a, int b) const
    {
        return (a > b) ? a : b;
    }

    int height(Node *n) const
    {
        return n ? n->height : 0;
    }

    int balanceFactor(Node *n) const
    {
        return n ? height(n->left) - height(n->right) : 0;
    }

    void updateHeight(Node *n)
    {
        n->height = 1 + max(height(n->left), height(n->right));
    }

    // ---------- Rotations ----------
    Node *rotateRight(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node *rotateLeft(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // ---------- Insert ----------
    Node *insert(Node *node, const K &key, const V &value)
    {
        if (!node)
            return new Node(key, value);

        if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        else
        {
            node->value = value; // Update value if key exists
            return node;
        }

        updateHeight(node);

        int bf = balanceFactor(node);

        // LL
        if (bf > 1 && key < node->left->key)
            return rotateRight(node);

        // RR
        if (bf < -1 && key > node->right->key)
            return rotateLeft(node);

        // LR
        if (bf > 1 && key > node->left->key)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // RL
        if (bf < -1 && key < node->right->key)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // ---------- Min Value Node ----------
    Node *minValueNode(Node *node)
    {
        Node *current = node;
        while (current && current->left)
            current = current->left;
        return current;
    }

    // ---------- Delete ----------
    Node *remove(Node *node, const K &key)
    {
        if (!node)
            return node;

        if (key < node->key)
            node->left = remove(node->left, key);
        else if (key > node->key)
            node->right = remove(node->right, key);
        else
        {
            // one or zero child
            if (!node->left || !node->right)
            {
                Node *temp = node->left ? node->left : node->right;

                if (!temp)
                {
                    temp = node;
                    node = 0;
                }
                else
                {
                    *node = *temp;
                }

                delete temp;
            }
            // two children
            else
            {
                Node *temp = minValueNode(node->right);
                node->key = temp->key;
                node->value = temp->value;
                node->right = remove(node->right, temp->key);
            }
        }

        if (!node)
            return node;

        updateHeight(node);
        int bf = balanceFactor(node);

        // LL
        if (bf > 1 && balanceFactor(node->left) >= 0)
            return rotateRight(node);

        // LR
        if (bf > 1 && balanceFactor(node->left) < 0)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // RR
        if (bf < -1 && balanceFactor(node->right) <= 0)
            return rotateLeft(node);

        // RL
        if (bf < -1 && balanceFactor(node->right) > 0)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // ---------- Destroy ----------
    void destroy(Node *node)
    {
        if (!node)
            return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    AVL() : root(0) {}

    ~AVL()
    {
        destroy(root);
    }

    void insert(const K &key, const V &value)
    {
        root = insert(root, key, value);
    }

    void remove(const K &key)
    {
        root = remove(root, key);
    }

    V find(const K &key) const
    {
        Node *current = root;
        while (current)
        {
            if (key < current->key)
                current = current->left;
            else if (key > current->key)
                current = current->right;
            else
                return current->value;
        }
        return nullptr; // Not found
    }

    bool contains(const K &key) const
    {
        Node *current = root;
        while (current)
        {
            if (key < current->key)
                current = current->left;
            else if (key > current->key)
                current = current->right;
            else
                return true;
        }
        return false;
    }
};
