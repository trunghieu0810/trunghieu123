
#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H
#include"baseObject.h"
#include<string>
#include<SDL_ttf.h>
class TextObject : public baseobject
{
public: 
   enum TextColor
   {
   RED_TEXT = 0,
   WHITE_TEXT = 1,
   BLACK_TEXT =2,
   };

  TextObject();
  ~TextObject();

  void SetText(const std::string& text) {str_val_ = text;}
  void SetColor(const int& type);
  void CreatGameText(TTF_Font* font, SDL_Surface* des);

private:

std::string str_val_;
SDL_Color text_color_;

};




#endif