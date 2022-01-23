//
// Created by macho on 1/20/22.
//
#ifndef FINALPROJECT_KDTREE_H
#define FINALPROJECT_KDTREE_H

#include <iostream>
#include "Things.h"

using namespace std;

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

    Node *findMinimum(Node *node, bool minBaseX, bool isXBase) {
        if (node == nullptr)
            return nullptr;
        if (minBaseX == isXBase) {
            if (node->left != nullptr) {
                return findMinimum(node->left, minBaseX, !isXBase);
            } else {
                return node;
            }
        } else {
            Node *minInLeft = findMinimum(node->left, minBaseX, !isXBase);
            Node *minInRight = findMinimum(node->right, minBaseX, !isXBase);
            if (isXBase) {
                Node *res = node;
                if (minInLeft != nullptr && minInLeft->branch->point.x < res->branch->point.x)
                    res = minInLeft;
                if (minInRight != nullptr && minInRight->branch->point.x < res->branch->point.x)
                    res = minInRight;
                return res;
            } else {
                Node *res = node;
                if (minInLeft != nullptr && minInLeft->branch->point.y < res->branch->point.y)
                    res = minInLeft;
                if (minInRight != nullptr && minInRight->branch->point.y < res->branch->point.y)
                    res = minInRight;
                return res;
            }
        }
    }

    void copySecondInFirstNode(Node *first, Node *second) {
        first->branch = second->branch;
    }

    bool notSeen = true;
    BankBranch *deletedBranch = nullptr;

    Node *del(Node *node, int x, int y, bool isXBase) {
        if (node == nullptr)
            return nullptr;
        if (node->branch->point.x == x, node->branch->point.y == y) {
            if (notSeen && node->branch->name == "Main Branch") {
                return node;
            }
            if (notSeen) {
                deletedBranch = node->branch;
            }
            notSeen = false;
            if (node->right != nullptr) {
                Node *min = findMinimum(node->right, isXBase, !isXBase);
                copySecondInFirstNode(node, min);
                node->right = del(node->right, min->branch->point.x, min->branch->point.y, !isXBase);
            } else if (node->left != nullptr) {
                Node *min = findMinimum(node->left, isXBase, !isXBase);
                copySecondInFirstNode(node, min);
                node->right = del(node->right, min->branch->point.x, min->branch->point.y, !isXBase);
            } else {
                delete node;
                return nullptr;
            }
        } else {
            if (isXBase) {
                if (x <= node->branch->point.x) {
                    node->left = del(node->left, x, y, !isXBase);
                } else {
                    node->right = del(node->right, x, y, !isXBase);
                }
            } else {
                if (y <= node->branch->point.y) {
                    node->left = del(node->left, x, y, !isXBase);
                } else {
                    node->right = del(node->right, x, y, !isXBase);
                }
            }
        }
        return node;
    }

    void del(int x, int y) {
        notSeen = true;
        Node *node = del(root, x, y, true);
        if (notSeen) {
            cout << "Main Branch Of Bank Can't be delete." << endl;
        } else {
            cout << "Branch " << deletedBranch->name << " Of Bank " <<
                 deletedBranch->bankName << " deleted." << endl;
        }
        notSeen = true;
    }


    // print in-order traversal
    void traversal(Node *node) {
        if (node == nullptr)
            return;
        traversal(node->left);
        node->branch->toString();
        traversal(node->right);
    }

    void traversal() {
        traversal(this->root);
    }

    Node *closer(Node *node1, Node *node2, Point point) {
        if (node1 == nullptr)
            return node2;
        if (node2 == nullptr)
            return node1;
        if ((node1->branch->point.x - point.x) * (node1->branch->point.x - point.x) +
            (node1->branch->point.y - point.y) * (node1->branch->point.y - point.y)
            >
            (node2->branch->point.x - point.x) * (node2->branch->point.x - point.x) +
            (node2->branch->point.y - point.y) * (node2->branch->point.y - point.y)
                )
            return node2;
        return node1;


    }

    Node *nearest(Node *node, Point target, bool isXBase) {
        if (node == nullptr)
            return nullptr;
        Node *next = nullptr;
        Node *other = nullptr;

        if (isXBase) {
            if (target.x > node->branch->point.x) {
                next = node->right;
                other = node->left;
            } else {
                next = node->left;
                other = node->right;
            }
        } else {
            if (target.y > node->branch->point.y) {
                next = node->right;
                other = node->left;
            } else {
                next = node->left;
                other = node->right;
            }
        }
        Node *temp = nearest(next, target, !isXBase);
        Node *best = closer(temp, node, target);
        long distance = isXBase ? target.x-node->branch->point.x : target.y-node->branch->point.y;
        if (
                (target.x - best->branch->point.x) * (target.x - best->branch->point.x) +
                (target.y - best->branch->point.y) * (target.y - best->branch->point.y)
                >
                distance * distance
           ){
            temp = nearest(other,target,!isXBase);
            return closer(temp,best,target);
        }
        return best;
    }

    Node *nearest(int x, int y) {
        return nearest(root,*new Point(x,y),true);
    }
};

#endif //FINALPROJECT_KDTREE_H