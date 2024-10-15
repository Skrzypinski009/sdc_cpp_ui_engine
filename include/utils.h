#ifndef UTILS_H
#define UTILS_H

#include <vector>

std::size_t findInString(const char* char_str, char c);

template<class T> int findObjectInVector(std::vector<T*> vec, T* object){
    for(int i=0; i<vec.size(); i++){
        if(object == vec.at(i)){
            return i;
        }
    }
    return -1;
}

#endif