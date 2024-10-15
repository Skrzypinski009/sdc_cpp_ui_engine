#pragma once

#include <vector>

template<class T> int findObjectInVector(std::vector<T*> vec, T* object){
    for(int i=0; i<vec.size(); i++){
        if(object == vec.at(i)){
            return i;
        }
    }
    return -1;
}

size_t findInString(const char* char_str, char c);