 
#include"baseObject.h"


baseobject::baseobject()
{
    rect_.x = 0;
    rect_.y = 0;        
    p_object_ = NULL;
}

baseobject::~baseobject()
{
    if (p_object_ != NULL)
    {
        SDL_FreeSurface(p_object_);

    }
}
//load anh
bool baseobject::LoadImg(const char* file_name)
{
    p_object_ = SDLcommonFunc::LoadImage(file_name);
    if(p_object_ == NULL)
    {return false;}
        return true;    
    
}

//ham show ra man hinh
void baseobject::Show(SDL_Surface* des)
{
    if(p_object_ != NULL)
    {
      rect_ =  SDLcommonFunc::ApplySurface(p_object_, des, rect_.x, rect_.y);
    }

}