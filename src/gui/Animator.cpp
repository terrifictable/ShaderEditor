#include "Animator.h"

template<typename T>
Animator<T>::Animator(T max, T speed) {
    Max = max;
    Speed = speed;
}

template<typename T>
Animator<T>::~Animator() {}


template<typename T>
void Animator<T>::Pulse(T &value, bool &tick) {
    if (value < Max) {
        value += Speed;
    } else if (value >= Max) {
        value -= Speed;
    }
}

