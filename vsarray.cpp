/*
 Filename: vsarray.cpp
 Description: Definition of the vsarray.
 Author: Soren Rood
 Date: 6/7/20
 Course: Data Structures II
*/

#include "vsarray.h"
#include <sstream>

#include <string>
using std::string;
using std::stringstream;

VSArray::VSArray(size_t capacity, double increasePercentage)
        : _capacity(capacity), _delta(increasePercentage) {
    _data = new DataBlock[capacity];
    for(size_t i = 0; i < _capacity; i++){
        _data[i].character = '\0'; // fill with null character...?
        _data[i].frequency = 0;
        _size = 0;
    }
}

VSArray::~VSArray(){
    Clear();
}

const VSArray& VSArray::operator=(const VSArray& rhs){ // we don't use this
    _capacity = rhs._capacity;
    _delta = rhs._delta;
    for(size_t i = 0; i < rhs._capacity; i++){
        _data[i].character = rhs._data[i].character;
        _data[i].frequency = rhs._data[i].frequency;
    }
    return *this;
}

bool VSArray::Insert(const char element){ // always insert at the end
    int tempIndex = IndexOf(element);
    // if size is full, Resize...
    if(_size + 1 == _capacity)
        Resize();
    //if tempIndex is -1, that means that the element does not exist in the array.
    if(tempIndex == -1){
        _data[_size].character = element;
        _data[_size].frequency++;
        _size++;
        return true;
    }
    //if tempIndex is not -1, that means the element exists in the array so we increase it's frequency by 1.
    else{
        _data[tempIndex].frequency++;
        return false;
    }
}

int VSArray::IndexOf(char element)const{
    for(size_t i = 0; i < _size; i++){
        if(_data[i].character == element)
            return i;
    }
    return -1;
}

bool VSArray::Remove(size_t position){
    //make sure position is in bounds
    if(position < 0 || position > _size - 1)
        return false;
        //tailcase
    else if(position == _size - 1){
        _data[_size - 1].character = '\0';
        _data[_size - 1].frequency = 0;
        _size--;
        return true;
    }
        //headcase
    else if(position == 0){
        _data[0].character = '\0';
        _data[0].frequency = 0;
        for(size_t i = 0; i < _size - 1; i++){
            _data[i].character = _data[i + 1].character;
            _data[i].frequency = _data[i + 1].frequency;
        }
        _size--;
        return true;
    }
        //all other cases (insert in middle)
    else{
        _data[position].character = '\0';
        _data[position].frequency = 0;
        for(size_t i = position; i < _size - 1; i++){
            _data[i].character = _data[i + 1].character;
            _data[i].frequency = _data[i + 1].frequency;
        }
        _size--;
        return true;
    }
}

char VSArray::Get(size_t position)const{
    //check if position is in bounds
    if(position < 0 || position > _size)
        return '\0'; // return null character
    return _data[position].character;
}

void VSArray::Clear(){
    delete [] _data; //ez pz bbb
}

void VSArray::Resize() {
    // calculate new capacity
    size_t nCapacity = (1 + _delta) * _capacity;
    // instantiate the new array
    DataBlock temp[nCapacity];
    for(size_t i = 0; i < _capacity; i++){
        temp[i].character = _data[i].character;
        temp[i].frequency = _data[i].frequency;
    }
    // assign new array
    delete [] _data;
    _data = temp;
    // update the capacity
    _capacity = nCapacity;
}

size_t VSArray::GetCapacity() const {
    return _capacity;
}

