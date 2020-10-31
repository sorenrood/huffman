/*
 Filename: tree.cpp
 Description: Definition of the tree.cpp
 Author: Soren Rood
 Date: 6/7/20
 Course: Data Structures II
*/

#include "tree.h"
#include <sstream>
#include <iostream>
#include <string>
using std::stringstream;


Tree::Tree(TreeNode *root, size_t capacity){
    _root = root;
    _data = new Map[capacity];
    for(size_t i = 0; i < capacity; i++){
        _data->size = 0;
        _data->key = "";
        _data->value = "";
    }
}

Tree::~Tree(){
    delete[] _data; // ezpz
    BreakItDown(_root);
}

void Tree::BreakItDown(TreeNode *root) {
    if(root->leftChild){
        BreakItDown(root->leftChild);
    }
    if(root->rightChild){
        BreakItDown(root->rightChild);
    }
    delete root;
}


void Tree::CreateDictionary() {
    stringstream os;
    CreateDictionary(_root, "");
}

void Tree::CreateDictionary(TreeNode *root, string s) {
    if(root->leftChild == nullptr && root->rightChild == nullptr){
        _data[_data->size].key = root->strng;
        _data[_data->size].value = s;
        _data->size++;
        return;
    }
    stringstream os1;
    os1 << s << "1";
    CreateDictionary(root->leftChild, os1.str());
    stringstream os2;
    os2 << s << "0";
    CreateDictionary(root->rightChild, os2.str());
}

size_t Tree::GetSize() {
    return _data->size;
}

string Tree::GetDictionaryValue(string &element) {
    for(size_t i = 0; i < _data->size; i++){
        if(_data[i].key == element){
            return _data[i].value;
        }
    }
    return "";
}

string Tree::OutputDictionary() {
    stringstream retVal;
    //todo sort this somehow
    for (size_t i = 0; i < _data->size; i++) {
        retVal << "{key: " << _data[i].key << ", " << "value: " << _data[i].value << "}" << endl;
    }
    return retVal.str();
}

void Tree::SortDictionary(){
    // bread and butter selection sort -_-

    int i; //outer loop
    int j; //inner loop
    int length = _data->size;

    // iterate through the entire dictionary
    for (i = 0; i < length-1; i++){
        int jMin = i; // sets the min to the first element.
        // find the smallest element of the unsorted list
        for (j = i+1; j < length; j++){
            // if an element is less than min, swap the index.
            if ((_data[j].value.size() == _data[jMin].value.size() && _data[j].value  < _data[jMin].value) || _data[j].value.size() < _data[jMin].value.size()){
                jMin = j;
            }
        }
        // If min == i, no need to swap because they would be the same...
        if (jMin != i){
            //do the swap here. Could also use a swap helper function to simplify the code.
            string tempKey = _data[i].key;
            string tempValue = _data[i].value;
            _data[i].key = _data[jMin].key;
            _data[i].value = _data[jMin].value;
            _data[jMin].key = tempKey;
            _data[jMin].value = tempValue;
        }
    }
}




