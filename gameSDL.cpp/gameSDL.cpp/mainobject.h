
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include"baseObject.h"
#include"common_Function.h"
#include"AmoObject.h"
#include<vector>

#define WIDTH_MAIN_OBJECT 77
#define HEIGHT_MAIN_OBJECT 52

class mainobject : public baseobject
{
    public:
    mainobject();
    ~mainobject();


    //dinh nghia ham xu ly di chuyen va gioi han di chuyen
    void HandleInputAction(SDL_Event events, Mix_Chunk* amo_sound[2]);
    void HandleMove();
    void SetAmolist(std::vector<AmoObject*>amo_list)  { p_amo_list_ = amo_list;}

    std::vector<AmoObject*> GetAmolist() const {return p_amo_list_;}
    void MakeAmo(SDL_Surface* des);
    
    //dinh nghia ham xoa vien dan
    void RemoveAmo(const int& idx);

    void setX_val(int x_val_);
    void setY_val_(int y_val_);

private:
    int x_val_;
    int y_val_; 

    std::vector<AmoObject*>p_amo_list_;


};


#endif