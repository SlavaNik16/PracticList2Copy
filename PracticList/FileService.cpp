#include <fstream>
#include "DoublyLinkedList.cpp"
#include "CircularLinkedList.cpp"
#include <iostream>
using namespace std;

struct FileService {
    char* data;
    int length;
    bool truncated;

    FileService() : data(nullptr), length(0), truncated(false) {}

    ~FileService() {
        if (data != nullptr) {
            delete[] data;
        }
    }
};