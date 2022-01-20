//
// Created by macho on 1/20/22.
//
#ifndef FINALPROJECT_THINGS_H
#define FINALPROJECT_THINGS_H
#endif //FINALPROJECT_THINGS_H

#include <string>
#include "KDTree.h"
using namespace std;

class Point{
public:
    int x;
    int y;

};
class Bank{
public:
    Point point;
    string name;
    KDTree branches;
};
class BankBranch{
    Point point;
    string bankName;
    string name;
};