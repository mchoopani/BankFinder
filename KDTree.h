//
// Created by macho on 1/20/22.
//
#ifndef FINALPROJECT_KDTREE_H
#define FINALPROJECT_KDTREE_H

#include "Things.h"

class Node {
public:
    BankBranch *branch;
    Node *father = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;

    Node(BankBranch *bankBranch) {
        branch = bankBranch;
    }

};

class KDTree {
private:
    Node *root = nullptr;
public:
    bool add(BankBranch *branch) {
        if (root == nullptr) {
            root = new Node(branch);
            return true;
        }
        bool isXBase = true;
        Node *ptr = root;
        Node *backupPtr = nullptr;
        bool addToRight = false;
        while (ptr != nullptr) {
            if (ptr->branch->point.equals(branch->point))
                return false;
            if (isXBase) {
                if (ptr->branch->point.x <= branch->point.x) {
                    // should go right
                    backupPtr = ptr;
                    ptr = ptr->right;
                    addToRight = true;
                } else {
                    // should go left
                    backupPtr = ptr;
                    ptr = ptr->left;
                    addToRight = false;
                }
            } else {
                if (ptr->branch->point.y <= branch->point.y) {
                    // should go right
                    backupPtr = ptr;
                    ptr = ptr->right;
                    addToRight = true;
                } else {
                    // should go left
                    backupPtr = ptr;
                    ptr = ptr->left;
                    addToRight = false;
                }
            }
            isXBase = !isXBase;
        }
        Node *newNode = new Node(branch);
        newNode->father = backupPtr;
        addToRight ? backupPtr->right = newNode : backupPtr->left = newNode;
        return true;
    }
};

#endif //FINALPROJECT_KDTREE_H