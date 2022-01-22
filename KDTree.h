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
    Node* findMinimum(Node* node, bool minBaseX,bool isXBase){
        if(minBaseX == isXBase){
            if(node -> left != nullptr){
                return findMinimum(node->left,minBaseX,!isXBase);
            }else{
                return node;
            }
        }else{
            Node* minInLeft = findMinimum(node->left,minXBase,!isXBase);
            Node* minInRight = findMinimum(node->right,minXBase,!isXBase);
            if(isXBase){
                Node *res = node;
                if (minInLeft != nullptr && minInLeft->point.x < res->point.x)
                    res = y;
                if (minInRight != nullptr && minInRight->point.x < res->point.x)
                    res = z;
                return res;
            }else{
                Node *res = node;
                if (minInLeft != nullptr && minInLeft->point.y < res->point.y)
                    res = y;
                if (minInRight != nullptr && minInRight->point.y < res->point.y)
                    res = z;
                return res;
            }
        }
    }
    Node* del(Node* node, bool isXBase){
        if(node->right != nullptr){

        }
        else if (node->left != nullptr ){

        }
        else {

        }
    }


    // print in-order traversal
    void traversal(Node* node){
        if(node == nullptr)
            return;
        traversal(node->left);
        node->branch->toString();
        traversal(node->right);
    }
    void traversal(){
        traversal(this->root);
    }
};

#endif //FINALPROJECT_KDTREE_H