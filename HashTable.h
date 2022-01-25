//
// Created by macho on 1/25/22.
//

#ifndef FINALPROJECT_HASHTABLE_H
#define FINALPROJECT_HASHTABLE_H

#endif //FINALPROJECT_HASHTABLE_H

template<class T>
class HashTable{
    T** arr = new T[56];
public:
    bool add(T t){
        int i = hash(t->name[0]);
        if(i == -1)
            return false;
        return true;
    }
    int hash(char c){
        for (int i = 0; i < 56; ++i) {
            int index = c % ('z'-'A'+1) + i;
            if (arr[i] == nullptr)
                return index;
        }
        return -1;
    }
};