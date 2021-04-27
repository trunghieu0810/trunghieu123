
#include"mainobject.h"
#include"AmoObject.h"

mainobject::mainobject()
{
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = WIDTH_MAIN_OBJECT;
    rect_.h = HEIGHT_MAIN_OBJECT;

    x_val_ = 0;
    y_val_ = 0;
}

mainobject::~mainobject()
{
;
}

//ham xu ly di chuyen
void mainobject::HandleInputAction(SDL_Event event, Mix_Chunk* amo_sound[2])
{
    if(event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            y_val_ -= HEIGHT_MAIN_OBJECT/5;
            break;
        case SDLK_DOWN:
            y_val_ += HEIGHT_MAIN_OBJECT/5;
            break;
        case SDLK_RIGHT:
            x_val_ += WIDTH_MAIN_OBJECT/5;
             break;
        case SDLK_LEFT:
            x_val_ -= WIDTH_MAIN_OBJECT/5;
            break;  
            default:
            break;
        }
    }
    else if(event.type == SDL_KEYUP)
    {
     switch (event.key.keysym.sym)
     {
         case SDLK_UP:
            y_val_ += HEIGHT_MAIN_OBJECT/5;
            break;
        case SDLK_DOWN:
            y_val_ -= HEIGHT_MAIN_OBJECT/5;
            break;
        case SDLK_RIGHT:
            x_val_ -= WIDTH_MAIN_OBJECT/5;
            break;
        case SDLK_LEFT:
            x_val_ += WIDTH_MAIN_OBJECT/5;
            break;  
            default:
            break;
     
     }
    }

    //xử lí chuột cho lớp đạn bắn
    else if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        AmoObject* p_amo = new AmoObject();
    if(event.button.button == SDL_BUTTON_LEFT)
        {
            p_amo->SetWidthHeight(WIDTH_LASER, HEIGHT_LASER);
            p_amo->LoadImg("laser.png");
            p_amo->set_type(AmoObject::LASER);
            //chen am thanh
            Mix_PlayChannel(-1, amo_sound[0], 0);
        }
        else if(event.button.button == SDL_BUTTON_RIGHT)
        {
            p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
            p_amo->LoadImg("sphere.png");
            p_amo->set_type(AmoObject::SPHERE);
            //chen am thanh
            Mix_PlayChannel(-1, amo_sound[1], 0);
        }

        p_amo->SetRect(this->rect_.x + this->rect_.w - 42, this->rect_.y + this->rect_.h*0.7);
        p_amo->set_is_move(true);   
        p_amo->set_x_val(20);
        p_amo_list_.push_back(p_amo);


    }
   

}

//chạy amo
void mainobject::MakeAmo(SDL_Surface* des)
{
 for (int i = 0; i < p_amo_list_.size(); i++)
    {
      AmoObject* p_amo = p_amo_list_.at(i);
      if (p_amo != NULL)
      {
        if (p_amo->get_is_move())
        {
          p_amo->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
          p_amo->Show(des);
        }
        else 
        {
          if (p_amo != NULL)    
          {
            p_amo_list_.erase(p_amo_list_.begin() + i);
            delete p_amo;
            p_amo = NULL;
          }
        }
      }
    }

}


//xu ly gioi han di chuyen
void mainobject::HandleMove()
{
    rect_.x += x_val_;
    if(rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH)
    {   
        rect_.x -= x_val_;
    }

    rect_.y += y_val_;
    if(rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT)
    {
        rect_.y -= y_val_;
    }
}  

//ham xoa vien dan
void mainobject::RemoveAmo(const int& idx)
{
 for(int i=0;i < p_amo_list_.size();i++)
   {
    if( idx < p_amo_list_.size())
    {
    
         AmoObject* p_amo = p_amo_list_.at(idx);
         p_amo_list_.erase(p_amo_list_.begin() + idx);
         if(p_amo != NULL)
         {
          delete p_amo;
          p_amo = NULL;
          }
       }
    }
}

void mainobject::setX_val(int x_val_)
{
    this->x_val_=x_val_;
}

void mainobject::setY_val_(int y_val_)
{
    this->y_val_=y_val_;
}