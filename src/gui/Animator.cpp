#include "Animator.h"

//template<typename T>
Animator::Animator(float max, float min, float speed) {
    Max = max;
    Min = min;
    Speed = speed;
}

//template<typename T>
void Animator::Pulse(float *value, bool *tick) {
    if (*tick || *value >= Max) {
        *tick = true;
        if (*value > Min)
            *value -= Speed;
        else if (*value <= Min)
            *tick ^= 1;
    } else if (!*tick || *value != Max) {
        *tick = false;
        if (*value < Max)
            *value += Speed;
        else if (*value >= Max)
            *tick ^= 1;
    }
}

//template<typename T>
//void Animator<T>::FadeIn(T &value) {
//    if (value < Max)
//        value += Speed;
//}
//template<typename T>
//void Animator<T>::FadeOut(T &value) {
//    if (value > Min)
//        value -= Speed;
//}
