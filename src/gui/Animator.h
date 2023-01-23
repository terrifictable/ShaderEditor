#ifndef ANIMATOR_H
#define ANIMATOR_H

template<typename T>
class Animator {
private:
    T Max;
    T Speed;

public:
    Animator(T max, T speed);
    ~Animator();

    void Pulse(T &value, bool &tick);
};


#endif
