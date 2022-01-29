//
// Created by macho on 1/29/22.
//

#ifndef FINALPROJECT_TRIETREE_H
#define FINALPROJECT_TRIETREE_H

#endif //FINALPROJECT_TRIETREE_H
template <class T>

class TrieTree{
    class TrieNode{
    public:
        TrieNode** nodes = new TrieNode*[60];
        int childrenCount = 0;
        bool isEndOfWord = false;
        T* data = nullptr;

    };
    TrieNode* root = new TrieNode;
public:
    void insert(T* newData){
        TrieNode* cursor = root;
        for (int i = 0; i < newData->name.size(); ++i) {
            int index = newData->name[i] - 'A';
            if(cursor->nodes[index] == nullptr){
                cursor->nodes[index] = new TrieNode;
                cursor->childrenCount++;
            }
            cursor = cursor->nodes[index];
        }
        cursor->isEndOfWord = true;
        cursor->data = newData;
    }
    T* get(string name){
        TrieNode* cursor = root;
        for (int i = 0; i < name.size(); ++i) {
            int index = name[i] - 'A';
            if(cursor->nodes[index] == nullptr){
                return nullptr;
            }
            cursor = cursor->nodes[index];
        }
        return cursor->data;
    }
    TrieNode* remove(TrieNode* node, string name, int depth){
        if(node == nullptr)
            return nullptr;
        if(depth == name.size()){
            node->isEndOfWord = false;
            if(node->childrenCount==0){
                delete node;
                return nullptr;
            }
            node->data = nullptr;
            return node;
        }
        bool hasData = node->nodes[name[depth]-'A'] != nullptr;
        node->nodes[name[depth]-'A'] = remove(node->nodes[name[depth]-'A'],name,depth+1);
        if (hasData && node->nodes[name[depth]-'A'] == nullptr){
            node->childrenCount--;
        }
        if (node == root)
            return node;
        if (node->childrenCount==0 && !node->isEndOfWord){
            delete node;
            return nullptr;
        }
        return node;
    }
    void remove(string name){
        root = remove(root,name,0);
    }
};