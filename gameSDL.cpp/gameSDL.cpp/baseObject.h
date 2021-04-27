
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include"common_Function.h"

//tạo 1 lớp chính
class baseobject
{
//lớp kế thừa
public:
    baseobject();
    ~baseobject();
    void Show(SDL_Surface* des);
    bool LoadImg(const char* file_name);
       
//xac dinh vi tri cua nhan vat
    void SetRect(const int& x,const int& y) { rect_.x = x, rect_.y = y;}
    SDL_Rect GetRect() const{ return rect_;}
    SDL_Surface* GetObject() {return p_object_;}


//định nghĩa các biến thành viên
protected:
    SDL_Rect rect_;
    SDL_Surface* p_object_;


};


#endif




//baseobject: lớp cơ sở
