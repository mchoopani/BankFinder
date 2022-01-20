//
// Created by macho on 1/20/22.
//
#ifndef FINALPROJECT_KDTREE_H
#define FINALPROJECT_KDTREE_H
#endif //FINALPROJECT_KDTREE_H

#include "Things.h"

class Node {
public:
    BankBranch *branch;
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
            if (ptr->branch->point.equals(branch))
                return false;
            if (isXBase) {
                if (ptr->branch->point.x <= branch->point.x) {
                    // should go right
                    ptr = ptr->right;
                    backupPtr = ptr;
                    addToRight = true;
                } else {
                    // should go left
                    ptr = ptr->left;
                    backupPtr = ptr;
                    addToRight = false;
                }
            } else {
                if (ptr->branch->point.y <= branch->point.y) {
                    // should go right
                    ptr = ptr->right;
                    backupPtr = ptr;
                    addToRight = true;
                } else {
                    // should go left
                    ptr = ptr->left;
                    backupPtr = ptr;
                    addToRight = false;
                }
            }
            isXBase = !isXBase;
        }
        addToRight ? backupPtr->right = branch : backupPtr->left = branch;
    }
};