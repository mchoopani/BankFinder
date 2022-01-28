#include <iostream>
#include "KDTree.h"
#include "HashTable.h"
#include "Stack.h"
// MOVED BANK CLASS TO STACK.h
int main() {
    KDTree allBranches;
    KDTree mainBranches;
    HashTable<Area> areas;
    HashTable<Bank> banks;
    Bank *mostBranches = nullptr;
    Stack commands;
    while (true) {
        string command;
        cin >> command;
        if (command == "addB") {
            string name;
            cin >> name;
            int x, y;
            cin >> x >> y;
            // check old banks to avoid duplicate instancing.
            Bank *bank = new Bank(name, x, y);
            BankBranch *mainBranch = new BankBranch(x, y);
            mainBranch->name = "Main Branch";
            mainBranch->bankName = name;
            bool result = allBranches.add(mainBranch);
            if (result) {
                bank->branches.add(mainBranch);
                mainBranches.add(mainBranch);
                banks.add(bank);
                commands.push(new Command(allBranches,banks,command,mainBranch,bank));
                if (mostBranches == nullptr) {
                    mostBranches = bank;
                }
                cout << "Main Branch Of bank " << name << " successfully added." << endl;
            } else {
                cout << "There is a branch of a bank in this point. please build your bank in other place." << endl;
            }
        } else if (command == "addBr") {
            string bankName, branchName;
            int x, y;
            cin >> bankName;
            cin >> branchName;
            cin >> x >> y;
            Bank *bank = banks.get(bankName);
            if (bank == nullptr) {
                cout << "Bank Doesn't exist." << endl;
                continue;
            }
            BankBranch *branch = new BankBranch(x, y);
            branch->name = branchName;
            branch->bankName = bankName;
            bool result = allBranches.add(branch);
            if (result) {
                bank->branches.add(branch);
                commands.push(new Command(allBranches,"addBr",branch, bank ));
                if (bank->branchesCount() > mostBranches->branchesCount()) {
                    mostBranches = bank;
                }
                cout << "Branch " << branchName << " Of bank " << bankName << " successfully added." << endl;
            } else {
                cout << "There is a branch of a bank in this point. please build your branch in other place." << endl;
            }
        } else if (command == "listBrs") {
            string bankName;
            cin >> bankName;
            Bank *bank = banks.get(bankName);
            if (bank == nullptr){
                cout << bankName << " Not Found." << endl;
                continue;
            }
            bank->branches.traversal();
        } else if (command == "delBr") {
            int x, y;
            cin >> x >> y;
            BankBranch* deletedBranch = allBranches.del(x, y, true);
            if (deletedBranch != nullptr) {
                Bank *bank = banks.get(deletedBranch->bankName);
                bank->branches.del(x, y, false);
                commands.push(new Command(allBranches,command,deletedBranch,bank));
            }
        } else if (command == "nearBr") {
            int x, y;
            cin >> x >> y;
            Node *near = allBranches.nearest(x, y);
            cout << "the nearest branch is " << near->branch->name << " of bank " << near->branch->bankName
                 << " at dimension " << near->branch->point.x << ", " << near->branch->point.y << endl;
        } else if (command == "nearB") {
            int x, y;
            cin >> x >> y;
            Node *near = mainBranches.nearest(x, y);
            cout << "the nearest main branch is " << near->branch->name << " of bank " << near->branch->bankName
                 << " at dimension " << near->branch->point.x << ", " << near->branch->point.y << endl;

        } else if (command == "listB") {
            string name;
            cin >> name;
            Area *found = areas.get(name);
            if (found == nullptr){
                cout << name << " Not exist." << endl;
            }
            allBranches.printNodesInArea(*found);
        } else if (command == "availB") {
            int x, y, r;
            cin >> x >> y >> r;
            allBranches.availableNodes(*new Area(x - r, x + r, y - r, y + r),
                                       *new Point(x, y), r);
        } else if (command == "addN") {
            string name;
            int x1, x2, y1, y2;
            cin >> name;
            cin >> x1 >> x2 >> y1 >> y2;
            Area *area = new Area(name, x1, x2, y1, y2);
            areas.add(area);
            commands.push(new Command(areas,"addN",area));
        } else if (command == "mostBrs") {
            cout << "The Most Branches Bank Is: " << mostBranches->name << " With " << mostBranches->branchesCount()
                 << " Branches.";
        } else if (command == "undo"){
            int p;
            cin >> p;
            int stackSize = commands.size;
            for (int i = 0; i < stackSize-p; ++i) {
                commands.pop()->reverseBack();
            }
        }
        else if (command == "exit") {
            break;
        }
    }
    return 0;
}
