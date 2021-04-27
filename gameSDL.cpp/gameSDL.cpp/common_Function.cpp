
#include"common_Function.h"
#include"TextObject.h"
 //check vi tri 1 diem
bool SDLcommonFunc::CheckForcusWithRect(const int& x,const int& y,const SDL_Rect& rect)
{
    if(x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
    {
     return true;
    }
    return false;
}
 //show menu
 int SDLcommonFunc::ShowMenu(SDL_Surface* des,TTF_Font* font)
 {
    g_img_menu = LoadImage("MENU.png");
    if(g_img_menu == NULL)
    {
     return 1;
    }

    const int kMenuItemNum = 2;
    SDL_Rect pos_arr[kMenuItemNum];
    pos_arr[0].x = 200;
    pos_arr[0].y = 400;

    pos_arr[1].x = 200;
    pos_arr[1].y = 480;

    TextObject text_menu[kMenuItemNum];

    text_menu[0].SetText("Play Game");
    text_menu[0].SetColor(TextObject::BLACK_TEXT);
    text_menu[0].SetRect(pos_arr[0].x,pos_arr[0].y);
    
    text_menu[1].SetText("Exit");
    text_menu[1].SetColor(TextObject::BLACK_TEXT);
    text_menu[1].SetRect(pos_arr[1].x,pos_arr[1].y);
    
    bool selected[kMenuItemNum] = {0,0};
    int xm = 0;
    int ym = 0;
    
    SDL_Event m_event;
    while(true)
    {
        SDLcommonFunc::ApplySurface(g_img_menu, des, 0, 0);
        for(int i=0;i<kMenuItemNum;i++)
        {
            text_menu[i].CreatGameText(font, des);
        }
        while(SDL_PollEvent(&m_event))
        {
            switch (m_event.type)
            {
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEMOTION:
                {
                    xm = m_event.motion.x;
                    ym = m_event.motion.y;

                    for(int i=0;i<kMenuItemNum;i++)
                    {
                        if(CheckForcusWithRect(xm , ym, text_menu[i].GetRect()))
                        {
                            if(selected[i] == false)
                            {
                                selected[i] = 1;
                                text_menu[i].SetColor(TextObject::RED_TEXT);            
                            }
                        }
                        else
                        {
                            if(selected[i] == true)
                            {
                                selected[i] = 0;
                                text_menu[i].SetColor(TextObject::BLACK_TEXT);
                            }
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    xm = m_event.button.x;
                    ym = m_event.button.y;
                  for(int i=0;i<kMenuItemNum;i++)
                   {
                    if(CheckForcusWithRect(xm , ym, text_menu[i].GetRect()))
                     {
                      return i;
                     }
                   }
                }
                break;
            case SDL_KEYDOWN:
                if(m_event.key.keysym.sym == SDLK_ESCAPE)
                {
                  return 1;
                }
            default:
                break;
            }
        }
        SDL_Flip(des);
    }
    return 1;
}

 //show man hinh cuoi
 int SDLcommonFunc::ShowLose(SDL_Surface* des,TTF_Font* font)
 {
    g_img_lose = LoadImage("lose.png");
    if(g_img_lose == NULL)
    {
     return 1;
    }

    const int kLoseItemNum = 3;
    SDL_Rect pos_arr[kLoseItemNum];
    pos_arr[0].x = 450;
    pos_arr[0].y = 380;

    pos_arr[1].x = 500;
    pos_arr[1].y = 460;

    pos_arr[2].x = 500;
    pos_arr[2].y = 200;

    TextObject text_lose[kLoseItemNum];

    text_lose[0].SetText("Play Again");
    text_lose[0].SetColor(TextObject::BLACK_TEXT);
    text_lose[0].SetRect(pos_arr[0].x,pos_arr[0].y);
    
    text_lose[1].SetText("Exit");
    text_lose[1].SetColor(TextObject::BLACK_TEXT);
    text_lose[1].SetRect(pos_arr[1].x,pos_arr[1].y);
    
    bool select[kLoseItemNum] = {0,0};
    int xm = 0;
    int ym = 0;
    
    SDL_Event m_event;
    while(true)
    {
        SDLcommonFunc::ApplySurface(g_img_lose, des, 0, 0);
        for(int i=0;i<kLoseItemNum;i++)
        {
            text_lose[i].CreatGameText(font, des);
        }
        while(SDL_PollEvent(&m_event))
        {
            switch (m_event.type)
            {
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEMOTION:
                {
                    xm = m_event.motion.x;
                    ym = m_event.motion.y;

                    for(int i=0;i<kLoseItemNum;i++)
                    {
                        if(CheckForcusWithRect(xm , ym, text_lose[i].GetRect()))
                        {
                            if(select[i] == false)
                            {
                                select[i] = 1;
                                text_lose[i].SetColor(TextObject::RED_TEXT);            
                            }
                        }
                        else
                        {
                            if(select[i] == true)
                            {
                                select[i] = 0;
                                text_lose[i].SetColor(TextObject::BLACK_TEXT);
                            }
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                {
                    xm = m_event.button.x;
                    ym = m_event.button.y;
                  for(int i=0;i<kLoseItemNum;i++)
                   {
                    if(CheckForcusWithRect(xm , ym, text_lose[i].GetRect()))
                     {
                      return i;
                     }
                   }
                }
                break;
            case SDL_KEYDOWN:
                if(m_event.key.keysym.sym == SDLK_ESCAPE)
                {
                  return 1;
                }
            default:
                break;
            }
        }
        SDL_Flip(des);
    }
    return 1;
}

 //hàm loadimage thực hiện việc đọc các image
SDL_Surface* SDLcommonFunc::LoadImage(std::string file_path)
{
    //sdl_surface là 1 kiểu dữ liệu để chứa các image
  SDL_Surface * load_image = NULL;
  SDL_Surface* optimize_image = NULL;
  load_image = IMG_Load(file_path.c_str());
  if (load_image != NULL)
  {

    //hàm định dạng hiển thị tối ưu hóa kiểu dữ liệu cho phù hợp
    optimize_image= SDL_DisplayFormat(load_image);

    //giải phóng cho loadimage
    SDL_FreeSurface(load_image);

    //kĩ thuật color key
    if (optimize_image != NULL) 
 {
        //truyền vào mã màu của phông ảnh dạng hexa
   UINT32 color_key = SDL_MapRGB(optimize_image->format, 0, 0xFF, 0xFF); 
   SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
 }
  }
  return optimize_image;
}
 

//hàm applysurface thực hiện việc loadimage vào màn hình
SDL_Rect SDLcommonFunc::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface(src, NULL, des, &offset);
  return offset;
}

//tao clip
void SDLcommonFunc::ApplySurfacelip(SDL_Surface* src, SDL_Surface* des,SDL_Rect* clip, int x, int y)
{
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface(src, clip, des, &offset);
}

//xu li va cham
bool SDLcommonFunc::CheckCollision(const SDL_Rect& object1,const SDL_Rect& object2) 
   {
  int left_a = object1.x;
  int right_a = object1.x + object1.w;
  int top_a = object1.y;
  int bottom_a = object1.y + object1.h;
 
  int left_b = object2.x;
  int right_b = object2.x + object2.w;
  int top_b = object2.y;
  int bottom_b = object2.y + object2.h;
 
  // Case 1: size object 1 < size object 2
  if (left_a > left_b && left_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }
 
  if (left_a > left_b && left_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }
 
  if (right_a > left_b && right_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }
 
  if (right_a > left_b && right_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }
  
  // Case 2: size object 1 < size object 2
  if (left_b > left_a && left_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }
 
  if (left_b > left_a && left_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }
 
  if (right_b > left_a && right_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }
 
  if (right_b > left_a && right_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }
 
   // Case 3: size object 1 = size object 2
  if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
  {
    return true;
  }
 
  return false;
}
 

//hàm giải phóng các đối tượng biến global
void SDLcommonFunc::CleanUp()
{
  SDL_FreeSurface(g_screen);
  SDL_FreeSurface(g_bkground);
}