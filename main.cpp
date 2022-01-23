#include <iostream>
#include "KDTree.h"

class Bank {
public:
    Point point;
    string name;
    KDTree branches;

    Bank(string name, int x, int y) : point(x, y) {
        this->name = name;
    }
};

int main() {
    KDTree allBranches;
    KDTree mainBranches;
    // TODO: Change Array TO Hash Table
    // ----------------------------------
    int ctr = 0;
    Bank **banks = new Bank *[1500];
    while (true) {
        string command;
        cin >> command;
        if (command == "addB") {
            string name;
            cin >> name;
            int x, y;
            cin >> x >> y;
            // check old banks to avoid duplicate instancing.
            bool continueOuter = false;
            // TODO: change array to hash table to decrease time complexity.
            for (int i = 0; i < ctr; ++i) {
                if (banks[i]->name == name) {
                    cout << "Bank exists." << endl;
                    continueOuter = true;
                    break;
                }
            }
            if (continueOuter)
                continue;
            Bank *bank = new Bank(name, x, y);
            BankBranch *mainBranch = new BankBranch(x, y);
            mainBranch->name = "Main Branch";
            mainBranch->bankName = name;
            bool result = allBranches.add(mainBranch);
            if (result) {
                bank->branches.add(mainBranch);
                mainBranches.add(mainBranch);
                banks[ctr++] = bank;
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
            Bank *bank = nullptr;
            for (int i = 0; i < ctr; ++i) {
                if (banks[i]->name == bankName) {
                    bank = banks[i];
                    break;
                }
            }
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
                banks[ctr++] = bank;
                cout << "Branch " << branchName << " Of bank " << bankName << " successfully added." << endl;
            } else {
                cout << "There is a branch of a bank in this point. please build your branch in other place." << endl;
            }
        } else if (command == "listBrs") {
            string bankName;
            cin >> bankName;
            Bank *bank = nullptr;
            for (int i = 0; i < ctr; ++i) {
                if (banks[i]->name == bankName) {
                    bank = banks[i];
                    break;
                }
            }
            if (bank == nullptr) {
                cout << "Bank Not Found." << endl;
                continue;
            }
            bank->branches.traversal();
        } else if (command == "delBr") {
            int x, y;
            cin >> x >> y;
            allBranches.del(x, y);
        } else if (command == "nearBr") {
            int x, y;
            cin >> x >> y;
            Node *near = allBranches.nearest(x, y);
            cout << "the nearest branch is " << near->branch->name << " of bank " << near->branch->bankName
                 << " at dimension " << near->branch->point.x << ", " << near->branch->point.y << endl;
        }
        else if (command == "nearB"){
            int x, y;
            cin >> x >> y;
            Node *near = mainBranches.nearest(x, y);
            cout << "the nearest main branch is " << near->branch->name << " of bank " << near->branch->bankName
                 << " at dimension " << near->branch->point.x << ", " << near->branch->point.y << endl;

        }
        else if (command == "exit") {
            break;
        }
    }
    // ----------------------------------
    return 0;
}
