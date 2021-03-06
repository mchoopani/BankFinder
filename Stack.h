//
// Created by macho on 1/28/22.
//

#ifndef FINALPROJECT_STACK_H
#define FINALPROJECT_STACK_H

#endif //FINALPROJECT_STACK_H

#include <string>
#include "KDTree.h"
#include "TrieTree.h"

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
    Area *area = nullptr;
    BankBranch *bankBranch = nullptr;
    Bank *bank = nullptr;
    KDTree kdTree;
    TrieTree<Bank> banks;
    TrieTree<Area> areas;
    HashTable<Bank> banksForMostBr;
public:
    Command(TrieTree<Area> areas, string type, Area *area) {
        this->areas = areas;
        this->type = type;
        this->area = area;
    }

    Command(KDTree all, string type, BankBranch *branch, Bank *bank) {
        this->kdTree = all;
        this->type = type;
        this->bankBranch = branch;
        this->bank = bank;
    }

    Command(KDTree all, TrieTree<Bank> banks, string type, HashTable<Bank> banksH, BankBranch *branch, Bank *bank) {
        this->kdTree = all;
        this->banks = banks;
        this->type = type;
        this->bankBranch = branch;
        this->bank = bank;
        this->banksForMostBr = banksH;
    }

    void reverseBack() {
        if (type == "addB") {
            kdTree.del(bankBranch->point.x, bankBranch->point.y, false, true);
            bank->branches.del(bankBranch->point.x, bankBranch->point.y, false, true);
            banks.remove(bank->name);
            banksForMostBr.del(bank->name);
        }
        if (type == "addBr") {
            kdTree.del(bankBranch->point.x, bankBranch->point.y, false, true);
            bank->branches.del(bankBranch->point.x, bankBranch->point.y, false, true);
        } else if (type == "addN") {
            areas.remove(area->name);
        } else if (type == "delBr") {
            kdTree.add(bankBranch);
            bank->branches.add(bankBranch);
        }
    }
};

class Stack {
public:
    Command **arr = new Command *[10];
    int capacity = 10;
    int size = 0;

    void push(Command *number) {
        if (size == capacity) {
            capacity *= 2;
            Command **newArr = new Command *[capacity];
            for (int i = 0; i < size; ++i) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }
        arr[size++] = number;
    }

    Command *pop() {
        if (size != 0) {
            return arr[--size];
        }
    }

    Command *peek() {
        if (size != 0)
            return arr[size - 1];
        return nullptr;
    }

};