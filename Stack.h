//
// Created by macho on 1/28/22.
//

#ifndef FINALPROJECT_STACK_H
#define FINALPROJECT_STACK_H

#endif //FINALPROJECT_STACK_H
#include <string>
#include "KDTree.h"
class Bank {
public:
    Point point;
    string name;
    KDTree branches;

    int branchesCount() {
        return branches.size;
    }

    Bank(string name, int x, int y) : point(x, y) {
        this->name = name;
    }
};
class Command {
    string type;
    Area* area = nullptr;
    BankBranch* bankBranch = nullptr;
    Bank* bank = nullptr;
    KDTree kdTree;
    HashTable<Bank> banks;
    HashTable<Area> areas;
public:
    Command(HashTable<Area> areas, string type,Area* area){
        this->areas = areas;
        this->type = type;
        this->area = area;
    }
    Command(KDTree all,string type, BankBranch* branch, Bank* bank){
        this->kdTree = all;
        this->type = type;
        this->bankBranch = branch;
        this->bank = bank;
    }
    Command(KDTree all,HashTable<Bank> banks,string type, BankBranch* branch, Bank* bank){
        this->kdTree = all;
        this->banks = banks;
        this->type = type;
        this->bankBranch = branch;
        this->bank = bank;
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