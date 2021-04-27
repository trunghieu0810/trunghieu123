

#include"ThreatsObject.h"
#include"AmoObject.h"

ThreatsObject::ThreatsObject()
{
    rect_.x = SCREEN_WIDTH;
    rect_.y = SCREEN_HEIGHT*0.5;
    rect_.w = WIDTH_THREAT;
    rect_.h = HEIGHT_THREAT;    

    x_val_ = 0;
    y_val_ = 0;
}


ThreatsObject::~ThreatsObject()
{
    if(p_amo_list_.size() > 0)
    {
        for(int i=0;i < p_amo_list_.size(); i++)
        {
            AmoObject* p_amo = p_amo_list_.at(i);
            if(p_amo != NULL)
            {
            delete p_amo;
            p_amo = NULL;
            }
        }
        p_amo_list_.clear();

    }
}

//thực hiện load hình ảnh đạn bắn cho địch
void ThreatsObject::InitAmo(AmoObject* p_amo)
{
    if(p_amo)
    {
        bool ret = p_amo->LoadImg("sphere2.png");
        if(ret)
        {
            p_amo->set_is_move(true);
            p_amo->SetWidthHeight(WIDTH_SPHERE,HEIGHT_SPHERE);
            p_amo->set_type(AmoObject::SPHERE);
            p_amo->SetRect(rect_.x,rect_.y + rect_.h* 0.5);
            p_amo->set_x_val(SPEED_AMO);
            p_amo_list_.push_back(p_amo);
        }
    }
}

//lớp đạn bắn của địch
void ThreatsObject::MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit)
{
    for(int i=0; i < p_amo_list_.size() ; i++)
    {
        AmoObject* p_amo = p_amo_list_.at(i);
        if(p_amo)
        {
        if(p_amo->get_is_move())
        {
            p_amo->Show(des);
            //hướng đạn từ phải qua trái
            p_amo->HanndleMoveRightToLeft();
        }
        else 
        {
            p_amo->set_is_move(true);
            p_amo->SetRect(rect_.x, rect_.y + rect_.h* 0.5);
        }
      }
   }
}

//tạo random các vị trí cho địch
void ThreatsObject::HandleMove(const int& x_border, const int& y_border)
{
    rect_.x -= x_val_;
    if(rect_.x < 0)
    {
        rect_.x = SCREEN_WIDTH;

        int rand_y = rand()%400;
        if(rand_y > SCREEN_HEIGHT - 200)
        {
            rand_y = SCREEN_HEIGHT*0.3;
        }
        rect_.y = rand_y;
    }
}

void ThreatsObject::HandInputAction(SDL_Event event)
{

}

//reset lai dich khi bi ban
void ThreatsObject::Reset(const int& xboder)
{
 rect_.x = xboder;
 int rand_y = rand()%400;
 if(rand_y > SCREEN_HEIGHT - 200)
 {
    rand_y = SCREEN_HEIGHT*0.3;
 }
  rect_.y = rand_y;
 for(int i=0; i<p_amo_list_.size();i++)
   {
    AmoObject* p_amo = p_amo_list_.at(i);
    if(p_amo)
    {
      ResetAmo(p_amo);
    }
   }
}

//reset dan ban cua dich
void ThreatsObject::ResetAmo(AmoObject* p_amo)
{
    p_amo->SetRect(rect_.x,rect_.y + rect_.h* 0.5);
}