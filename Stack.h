//
// Created by macho on 1/28/22.
//

#ifndef FINALPROJECT_STACK_H
#define FINALPROJECT_STACK_H

#endif //FINALPROJECT_STACK_H
#include <string>
#include "KDTree.h"
class Command {
    static KDTree kdTree;
    string type;
    Area* area = nullptr;
    BankBranch* bankBranch = nullptr;
    void set(string type,Area* area){
        this->type = type;
        this->area = area;
    }
    void set(string type, BankBranch* branch){
        this->type = type;
        this->bankBranch = branch;
    }


};

class Stack {
public:
    Command **arr = new Command*[10];
    int capacity = 10;
    int size = 0;

    void push(Command* number) {
        if (size == capacity) {
            capacity *= 2;
            Command** newArr = new Command*[capacity];
            for (int i = 0; i < size; ++i) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }
        arr[size++] = number;
    }

    Command* pop() {
        if (size != 0) {
            return arr[--size];
        }
    }

    Command* peek() {
        if (size != 0)
            return arr[size - 1];
        return nullptr;
    }

};