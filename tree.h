/*
 Filename: tree.h
 Description: Declaration of the class tree.
 Author: Soren Rood
 Date: 6/7/20
 Course: Data Structures II
*/

#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H
#include <string>
using std::string;
using namespace std;

struct TreeNode{
    string strng;
    size_t frequency;
    TreeNode *leftChild = nullptr;
    TreeNode *rightChild = nullptr;
};
struct Map{
    string key; // string like "a"
    string value; // value like "011"
    size_t size; // keep track of the size
};

class Tree {
private:
    TreeNode *_root;
    void CreateDictionary(TreeNode *head, string s);

public:
    Map *_data;
    Tree(TreeNode *root, size_t capacity);
    ~Tree();
    void CreateDictionary();
    size_t GetSize();
    string GetDictionaryValue(string &element);
    void BreakItDown(TreeNode *root);
    string OutputDictionary();
    void SortDictionary();
};


#endif //HUFFMAN_TREE_H
