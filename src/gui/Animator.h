#ifndef ANIMATOR_H
#define ANIMATOR_H

//template<typename T>
class Animator {
private:
    float Max;
    float Min;
    float Speed;

public:
    Animator(float max, float min, float speed);
    ~Animator() = default;


    void Pulse(float *value, bool *tick);
    void FadeIn(float *value);
    void FadeOut(float *value);
};


#endif
