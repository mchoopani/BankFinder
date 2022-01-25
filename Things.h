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

    long squearedDistance(Point other) {
        return (this->x - other.x) * (this->x - other.x) +
               (this->y - other.y) * (this->y - other.y);
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

class Area {
public:
    string name;
    int x1, x2;
    int y1, y2;

    Area(int x1, int x2, int y1, int y2) {
        if (x1 < x2) {
            this->x1 = x1;
            this->x2 = x2;
        } else {
            this->x1 = x2;
            this->x2 = x1;
        }
        if (y1 < y2) {
            this->y1 = y1;
            this->y2 = y2;
        } else {
            this->y1 = y2;
            this->y2 = y1;
        }
    }

    int containsPoint(Point point, bool xBase) {
        if (xBase) {
            if (point.x >= x1 && point.x <= x2)
                return 0;
            else if (point.x > x2) {
                return +1;
            } else if (point.x < x1) {
                return -1;
            }
        } else {
            if (point.y >= y1 && point.y <= y2)
                return 0;
            else if (point.y > y2) {
                return +1;
            } else if (point.y < y1) {
                return -1;
            }
        }

    }
};
#endif //FINALPROJECT_THINGS_H
