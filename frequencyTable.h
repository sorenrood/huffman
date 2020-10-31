/*
 Filename: frequencyTable.h
 Description: Declaration of the class frequencyTable. DlinkedList UDT.
 Author: Soren Rood
 Date: 6/7/20
 Course: Data Structures II
*/

#ifndef HUFFMAN_FREQUENCYTABLE_H
#define HUFFMAN_FREQUENCYTABLE_H
#include <string>
#include "tree.h"
using std::string;

class FrequencyTable {
private:
    struct ListNode{
        TreeNode *data;
        ListNode *next;
        ListNode *previous;
    };
    ListNode *_head;
    ListNode *_tail;
    size_t _size;
public:
    FrequencyTable();
    ~FrequencyTable();

    bool Insert(TreeNode *a); //Maybe it should take a DataBlock input and put the info into a treeNode type?...
    string Get(size_t index);
    TreeNode* Remove();
    bool IsEmpty() const;
    void Clear();
    size_t GetSize();
    string OutputData();
    TreeNode* GetHead();

};


#endif //HUFFMAN_FREQUENCYTABLE_H
