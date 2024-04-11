#ifndef MY_AVLTREE_HPP_
#define MY_AVLTREE_HPP_

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

/**
 * IMPORTANT:
 *      The implementation for this AVL Tree is NOT my own.
 *      I took this from: https://github.com/KadirEmreOto/AVL-Tree
 *      The treeMedian is my own work
 */

struct AVLTreeNode
{
    AVLTreeNode *left;
    AVLTreeNode *right;

    const int value;
    int count; // how many nodes are there in this subtree
    int height;

    AVLTreeNode(int value) : value(value)
    {
        count = 1;
        height = 1;

        left = nullptr;
        right = nullptr;
    }

    void updateValues()
    {
        count = (left != nullptr ? left->count : 0) + (right != nullptr ? right->count : 0) + 1;

        height = std::max(left != nullptr ? left->height : 0,
                          right != nullptr ? right->height : 0) +
                 1;
    }

    int balanceFactor()
    {
        return (left != nullptr ? left->height : 0) - (right != nullptr ? right->height : 0);
    }

    AVLTreeNode *left_rotate()
    {
        AVLTreeNode *R = right;
        right = right->left;
        R->left = this;

        this->updateValues(); // the order is important
        R->updateValues();

        return R;
    }

    AVLTreeNode *right_rotate()
    {
        AVLTreeNode *L = left;
        left = left->right;
        L->right = this;

        this->updateValues(); // the order is important
        L->updateValues();

        return L;
    }
};

class AVLTree
{
private:
    int _size;
    AVLTreeNode *root;

    void balance(std::vector<AVLTreeNode **> path)
    { // starting from root
        std::reverse(path.begin(), path.end());

        for (auto indirect : path)
        {
            (*indirect)->updateValues();

            if ((*indirect)->balanceFactor() >= 2 and (*indirect)->left->balanceFactor() >= 0) // left - left
                *indirect = (*indirect)->right_rotate();

            else if ((*indirect)->balanceFactor() >= 2)
            { // left - right
                (*indirect)->left = (*indirect)->left->left_rotate();
                *indirect = (*indirect)->right_rotate();
            }

            else if ((*indirect)->balanceFactor() <= -2 and (*indirect)->right->balanceFactor() <= 0) // right - right
                *indirect = (*indirect)->left_rotate();

            else if ((*indirect)->balanceFactor() <= -2)
            { // right - left
                (*indirect)->right = ((*indirect)->right)->right_rotate();
                *indirect = (*indirect)->left_rotate();
            }
        }
    }

public:
    AVLTree()
    {
        root = nullptr;
        _size = 0;
    }

    ~AVLTree()
    {
        clear();
    }

    void clear()
    {
        std::vector<AVLTreeNode *> stack;

        if (root != nullptr)
            stack.push_back(root);

        while (!stack.empty())
        {
            AVLTreeNode *node = stack.back();
            stack.pop_back();

            if (node->left != nullptr)
                stack.push_back(node->left);

            if (node->right != nullptr)
                stack.push_back(node->right);

            _size--;
            delete node;
        }

        root = nullptr;
    }

    void insert(int value)
    {
        AVLTreeNode **indirect = &root;   // to generalize insertion
        std::vector<AVLTreeNode **> path; // to update height values

        while (*indirect != nullptr)
        {
            path.push_back(indirect);

            if ((*indirect)->value > value)
                indirect = &((*indirect)->left);
            else
                indirect = &((*indirect)->right);
        }

        *indirect = new AVLTreeNode(value);
        path.push_back(indirect);

        balance(path);
        _size++;
    }

    void erase(int value)
    {
        AVLTreeNode **indirect = &root;   // to generalize insertion
        std::vector<AVLTreeNode **> path; // to update height values

        while (*indirect != nullptr and (*indirect)->value != value)
        {
            path.push_back(indirect);

            if ((*indirect)->value > value)
                indirect = &((*indirect)->left);
            else
                indirect = &((*indirect)->right);
        }

        if (*indirect == nullptr) // the value does not exist in tree
            return;               // may be raising an Exception is more elegant

        else
            path.push_back(indirect);

        std::size_t index = path.size();

        if ((*indirect)->left == nullptr and (*indirect)->right == nullptr)
        {                     // the node is leaf
            delete *indirect; // just delete node
            *indirect = nullptr;
            path.pop_back(); // pop the deleted node from path
        }

        else if ((*indirect)->right == nullptr)
        { // only left child exists
            AVLTreeNode *toRemove = *indirect;

            (*indirect) = (*indirect)->left;
            delete toRemove;

            path.pop_back();
        }

        else
        { // right child exists
            AVLTreeNode **successor = &((*indirect)->right);

            while ((*successor)->left != nullptr)
            {
                path.push_back(successor);
                successor = &((*successor)->left);
            }

            if (*successor == (*indirect)->right)
            {
                (*successor)->left = (*indirect)->left;

                AVLTreeNode *toRemove = *indirect;
                *indirect = *successor;
                delete toRemove;
            }

            else
            {
                AVLTreeNode *tmp = *path.back(), *suc = *successor;

                tmp->left = (*successor)->right;
                suc->left = (*indirect)->left;
                suc->right = (*indirect)->right;

                delete *indirect;
                *indirect = suc;
                path[index] = &(suc->right);
            }
        }

        balance(path);
        _size--;
    }

    int size() const
    {
        return _size;
    }

    const int &find_min() const
    {
        AVLTreeNode *cur = root;

        while (cur->left != nullptr)
            cur = cur->left;

        return cur->value;
    }

    const int &find_max() const
    {
        AVLTreeNode *cur = root;

        while (cur->right != nullptr)
            cur = cur->right;

        return cur->value;
    }

    const int &operator[](std::size_t idx) const
    {
        AVLTreeNode *cur = root;
        int left = cur->left != nullptr ? cur->left->count : 0;

        while (left != idx)
        {
            if (left < idx)
            {
                idx -= left + 1;

                cur = cur->right;
                left = cur->left != nullptr ? cur->left->count : 0;
            }
            else
            {
                cur = cur->left;
                left = cur->left != nullptr ? cur->left->count : 0;
            }
        }

        return cur->value;
    }
};

void treeMedian(const std::vector<int> *instructions);

#endif
