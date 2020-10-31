/*
 Filename: main.cpp
 Description: Main Program that drives this program
 Author: Soren Rood
 Date: 6/7/20
 Course: Data Structures II
*/

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include "vsarray.h"
#include "tree.h"
#include "frequencyTable.h"
using namespace std;

TreeNode* MergeNodes(TreeNode *left, TreeNode *right);

int main(int argc, char* argv[]) {
    //command line argument handling
    if(argc != 4){
        cout << "Invalid command line operands. Should be like: ./huffman <action> <inputfile.txt> <outputfile.txt>" << endl;
        return -1;
    }
    // command line argument variables... used later
    string action = argv[1];
    string fileString = argv[2];
    string outputString = argv[3];



    // ----------ENCODE----------
    if(action == "-encode") {
        //variables
        ifstream file;
        char tempChar;
        VSArray arr(200, .05);
        // Open a file
//        cout << "----------OPEN A FILE----------" << endl << endl;
        file.open(fileString);
        //Loop until correct input file is chosen.
        while (!file.is_open()) {
            cerr << " \"" << fileString << "\"" << " is not able to be opened... Try again..." << endl;
            getline(cin, fileString);
            file.open(fileString);
        }
        // Read from the file character by character and add each char to VSArray.
//        cout << "----------CREATING VSARRAY FREQ TABLE FROM INPUT FILE----------" << endl << endl;
        while (!file.eof()) {
            tempChar = file.get();
            int tempInt = tempChar;
            if (tempInt == -1) { //if ascii code is -1, don't insert...
                continue;
            }
            arr.Insert(tempChar);
        }
        file.close();
        // Output the VSArray for testing purposes
//        cout << "----------OUTPUTTING VSARRAY FREQUENCYTABLE----------" << endl << endl;
//        for (size_t i = 0; i < arr._size; i++) {
//            cout << "\"" << arr._data[i].character << "\"" << ", " << arr._data[i].frequency << endl;
//        }
        // Move data from the VSArray into a DLinkedList. (It will insert in sorted order)
//        cout << "----------MOVING DATA FROM VSARRAY INTO SORTED DLINKEDLIST----------" << endl << endl;
        FrequencyTable list;
        for (int i = 0; i < arr._size; i++) {
            string currString;
            currString += arr._data[i].character;
            TreeNode *a = new TreeNode;
            a->frequency = arr._data[i].frequency;
            a->strng = currString;
            list.Insert(a);
        }
//        cout << "----------OUTPUTTING DLINKEDLIST----------" << endl << endl;
//        cout << list.OutputData();

//        cout << "----------LINKING TREENODES----------" << endl << endl;
        while (list.GetSize() != 1) {
            TreeNode *a = list.Remove();
            TreeNode *b = list.Remove();
            TreeNode *c = MergeNodes(a, b);
            list.Insert(c);
        }
//        cout << "----------BUILDING HUFFMAN TREE----------" << endl << endl;
        // Create a tree
        Tree a(list.GetHead(), arr._size);
        // Create a dictionary
//        cout << "----------CREATING DICTIONARY----------" << endl << endl;
        a.CreateDictionary();
        // output dictionary
        cout << "----------DISPLAYING DICTIONARY----------" << endl << endl;
        // sort it
        a.SortDictionary();
        // output it
        cout << a.OutputDictionary() << endl;
        cout << "Writing to file " << "\"" << outputString << "\"" << endl << endl;
        ofstream outputFile;
        outputFile.open(outputString);
        file.open(fileString);
        // write to a file
        while (!file.eof()) {
            string curVal;
            curVal += file.get(); // ignore this error
            outputFile << a.GetDictionaryValue(curVal);
        }
        //close files
        file.close();
        outputFile.close();
        cout << "----------ENCODING COMPLETE----------" << endl << endl;
        return 0;
    }



    // ----------DECODE----------
    else if(action == "-decode"){
        cout << "Decode not implemented" << endl;
        return 0;
    }
    else{
        cout << "Invalid action argument. Must be -encode or -decode" << endl;
        return 0;
    }
}

TreeNode* MergeNodes(TreeNode *left, TreeNode *right){
    TreeNode *retVal = new TreeNode;
    retVal->frequency = left->frequency + right->frequency;
    retVal->strng = left->strng + right->strng;
    retVal->leftChild = left;
    retVal->rightChild = right;
    return retVal;
}

