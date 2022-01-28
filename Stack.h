//
// Created by macho on 1/28/22.
//

#ifndef FINALPROJECT_STACK_H
#define FINALPROJECT_STACK_H

#endif //FINALPROJECT_STACK_H
class Stack {
public:
    char *arr = new char[10];
    int capacity = 10;
    int size = 0;

    void push(char number) {
        if (size == capacity) {
            capacity *= 2;
            char *newArr = new char[capacity];
            for (int i = 0; i < size; ++i) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }
        arr[size++] = number;
    }

    char pop() {
        if (size != 0) {
            return arr[--size];
        }
    }

    char peek() {
        if (size != 0)
            return arr[size - 1];
        return ' ';
    }

};