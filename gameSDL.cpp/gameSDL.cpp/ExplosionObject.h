#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "AmoObject.h"
#include"common_Function.h"


const int EXP_WIDTH = 165;
const int EXP_HEIGHT = 165;

class ExplosionObject : public baseobject
{
public:
    ExplosionObject();
    ~ExplosionObject();
    //tao 1 clip
    void set_clip();
    //xet khung cho vu no
    void set_frame(const int& fr) {frame_ = fr;}
    //show ra screen
    void ShowEx(SDL_Surface* des);



private:
        int frame_;
        SDL_Rect clip_[4];

};





#endif