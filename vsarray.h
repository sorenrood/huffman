/*
 Filename: vsarray.h
 Description: Declaration of the class fsarray.
 Author: Soren Rood
 Date: 6/7/20
 Course: Data Structures II
*/

#ifndef HUFFMAN_VSARRAY_H
#define HUFFMAN_VSARRAY_H
#include <string>
using std::string;

struct DataBlock{
    char character;
    size_t frequency;
};

class VSArray {
private:


    double _delta;
    VSArray(const VSArray&);
    const VSArray& operator=(const VSArray&);
    void Resize();

public:
    DataBlock *_data;
    size_t _size;
    size_t _capacity;

    VSArray(size_t capacity, double increasePercentage = 0.5);
    ~VSArray();
    bool Insert(char element);
    int IndexOf(char element)const;
    bool Remove(size_t position);
    char Get(size_t position)const;
    void Clear();
    size_t GetCapacity()const;
};


#endif //HUFFMAN_VSARRAY_H
