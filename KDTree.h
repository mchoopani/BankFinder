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
        if(node == nullptr)
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
    Node *del(Node *node, int x, int y, bool isXBase) {
        if (node->branch->point.x == x, node->branch->point.y == y) {
            if(notSeen && node->branch->name == "Main Branch"){
                return node;
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
            if(isXBase){
                if(x <= node->branch->point.x){
                    node->left = del(node->left,x,y,!isXBase);
                }else{
                    node->right = del(node->right,x,y,!isXBase);
                }
            }
            else{
                if(y <= node->branch->point.y){
                    node->left = del(node->left,x,y,!isXBase);
                }else{
                    node->right = del(node->right,x,y,!isXBase);
                }
            }
        }
        return node;
    }
    void del(int x,int y){
        notSeen = true;
        del(root,x,y,true);
        if(!notSeen){
            cout << "Main Branch Of Bank Can't be delete." << endl;
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
};

#endif //FINALPROJECT_KDTREE_H