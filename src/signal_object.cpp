#include "signal_object.h"

void SignalObject::addSignals(const int signals_){
    signals |= signals_;
}

void SignalObject::clearSignals(){
    signals = 0;
}

bool SignalObject::checkSignals(const int signals_){
    return (signals & signals_) == signals;
}