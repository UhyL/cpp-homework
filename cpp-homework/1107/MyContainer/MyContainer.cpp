#include "MyContainer.h"

int MyContainer::_count = 0;

MyContainer::MyContainer(int size) : _size(size) {
    // TODO: finish me
    _data = new int[size];
    ++_count;
}

MyContainer::~MyContainer() {
    // TODO: finish me
    delete[] _data;
    --_count;
}

MyContainer::MyContainer(const MyContainer &Other) : _size(Other._size) {
    // TODO: finish me
    _data = new int[_size];
    for(int i = 0; i < _size; ++i) 
        _data[i] = Other._data[i];
    
    ++_count;
}

MyContainer& MyContainer::operator=(const MyContainer &Other) {
    // TODO: finish me
    if(this != &Other) {
        _size = Other._size;
        _data = new int[_size];
        for(int i = 0; i < _size; ++i) 
            _data[i] = Other._data[i];
    }
    
    return *this;
}

int MyContainer::size() const {
    return _size;
}

int* MyContainer::data() const {
    return _data;
}

int MyContainer::count() {
    return _count;
}