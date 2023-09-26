#pragma once
#include "object.h"

class SignalObject: public Object{
    int signals;
    
public:
    void addSignals(const int signals_);
    void clearSignals();
    bool checkSignals(const int signals_);
};