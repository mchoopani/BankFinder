//
// Created by macho on 1/20/22.
//
#ifndef FINALPROJECT_THINGS_H
#define FINALPROJECT_THINGS_H

#include <string>
#include "KDTree.h"

using namespace std;

class Point {
public:
    int x;
    int y;

    bool equals(Point point) {
        return point.x == x && point.y == y;
    }

    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

class BankBranch {
public:
    Point point;
    string bankName;
    string name;

    BankBranch(int x, int y) : point(x, y) {
    }

    void toString() {
        cout << "+-+-+-+--+-+" << endl;
        cout << "Bank Name : " << bankName << endl;
        cout << "Branch Name : " << name << endl;
        cout << "X: " << point.x << endl;
        cout << "Y: " << point.y << endl;
        cout << "+-+-+-+--+-+" << endl;
    }
};

#endif //FINALPROJECT_THINGS_H
