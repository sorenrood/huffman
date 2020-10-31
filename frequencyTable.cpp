/*
 Filename: frequencyTable.cpp
 Description: Definition of the dlinkedlist frequencyTable.
 Author: Soren Rood
 Date: 6/7/20
 Course: Data Structures II
*/

#include "frequencyTable.h"
#include <sstream>
#include <iostream>

using namespace std;

FrequencyTable::FrequencyTable()
: _head(nullptr), _tail(nullptr), _size(0){
}

FrequencyTable::~FrequencyTable(){
    Clear();
}

bool FrequencyTable::Insert(TreeNode *a){
    // This implementation inserts the lowest frequency at the start of the list.
    // construct the new ListNode
    ListNode *newNode = new ListNode;
    newNode->data = a;
    //size_t ascii = a->ascii;
    string strng = a->strng;
    size_t frequency = a->frequency;

    // Convert 10 and 13 into line feed and carriage return.
    if(strng == "\r")
        newNode->data->strng = "LF";
    if(strng == "\n")
        newNode->data->strng = "CR";
    // if list is empty
    if(_size == 0){
        _head = newNode;
        _tail = newNode;
        _size++;
        return true;
    }
    //if list is empty check 2
    else if(_head == nullptr){
        _head = newNode;
        _tail = newNode;
        _size++;
        return true;
    }
    // for insert in front of the head
    else if((frequency == _head->data->frequency && strng < _head->data->strng) || frequency < _head->data->frequency){
        _head->previous = newNode;
        newNode->next = _head;
        _head = newNode;
        _size++;
        return true;
    }
    // end case assuming we insert after the tail
    else if((frequency == _tail->data->frequency && strng > _tail->data->strng) || newNode->data->frequency > _tail->data->frequency){
        _tail->next = newNode;
        newNode->previous = _tail;
        _tail = newNode;
        _size++;
        return true;
    }
    // if we want to insert into the middle of the list
    else{
        ListNode *curNode = _head;
        while(curNode != nullptr){
            if(frequency > curNode->data->frequency){
                curNode = curNode->next;
                continue;
            }
            else if(frequency == curNode->data->frequency){
                if(strng > curNode->data->strng){
                    curNode = curNode->next;
                    continue;
                }
            }
            newNode->next = curNode;
            newNode->previous = curNode->previous;
            curNode->previous = newNode;
            newNode->previous->next = newNode;
            _size++;
            return true;
        }
    }
    //this should never happen...?
    delete newNode;
    return false;
}

string FrequencyTable::Get(size_t index){
    size_t count = 0;
    ListNode *cur = _head;
    while(cur != nullptr){
        if(count == index){
            return cur->data->strng;
        }
        ++count;
        cur = cur->next;
    }
}

TreeNode* FrequencyTable::Remove(){
    //if size == 1
    if(_size == 1){
        TreeNode *retVal = _head->data;
        delete _head;
        _head = nullptr;
        _tail = nullptr;
        _size--;
        return retVal;
    }
    ListNode *headPt = _head;
    _head = headPt->next;
    _head->previous = nullptr; //sswpp
    TreeNode *retVal = headPt->data;
    delete headPt;
    _size--;
    return retVal;
}

bool FrequencyTable::IsEmpty() const{
    // return false if head != nullptr. If _head == nullptr, then the list IS empty.
    return _head != nullptr;
}

void FrequencyTable::Clear(){
    if(_head == nullptr)
        return;
    ListNode *cur = _head;
    ListNode *tmp;
    // Iterate through the entire list.
    for(size_t i = 0; i < _size; i++){
        tmp = cur->next;
        //delete cur->data;
        delete cur;
        cur = tmp;
    }
}

size_t FrequencyTable::GetSize() {
    return _size;
}

string FrequencyTable::OutputData(){
    stringstream retVal;
    ListNode *tmp = _head;
    for(size_t i = 0; i < _size; i++){
        cout << "\"" << tmp->data->strng << "\"" << ", " << tmp->data->frequency << endl;
        tmp = tmp->next;
    }
    return retVal.str();
}

TreeNode* FrequencyTable::GetHead() {
    return _head->data;
}
