//
// Created by macho on 1/25/22.
//

#ifndef FINALPROJECT_HASHTABLE_H
#define FINALPROJECT_HASHTABLE_H

#endif //FINALPROJECT_HASHTABLE_H
#include "Things.h"
template<class T>
class HashTable {
    T **arr = new T*[58];
public:
    bool add(T* t) {
        int i = hash(t->name[0]);
        if (i == -1)
            return false;
        arr[i] = t;
        return true;
    }
    T* get(string name){
        char c = name[0]-'A';
        for (int i = 0; i < 58; ++i) {
            int index = (c % hash() + i)%hash();
            if(arr[index] == nullptr)
                break;
            if(arr[index]->name == name)
                return arr[index];
        }
        return nullptr;
    }

    int hash(char c) {
        c -= 'A';
        for (int i = 0; i < 56; ++i) {
            int index = (c % hash() + i) % hash();
            if (arr[i] == nullptr)
                return index;
        }
        return -1;
    }
    int hash(){
        return ('z' - 'A' + 1);
    }
};