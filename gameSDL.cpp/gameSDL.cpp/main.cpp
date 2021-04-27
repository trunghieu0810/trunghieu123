
#include"common_Function.h"
#include"mainobject.h"
#include"baseObject.h"
#include"ThreatsObject.h"
#include"AmoObject.h"
#include"ExplosionObject.h"
#include"PlayerPower.h"
#include"TextObject.h"



TTF_Font* g_font_text = NULL;
TTF_Font* g_font_menu = NULL;

//hàm init khởi tạo các thuộc tính ban đầu
bool Init()
{
    //khởi tạo thư viện (khởi động)
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
  {
    return false;
  }
  //định dạng màn hình được hiển thị
  g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
  if (g_screen == NULL)
  {
    return false;
  }


  if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
      return false;
  //doc file wav audio
  g_sound_amo[0] = Mix_LoadWAV("laser.wav");
  g_sound_amo[1] = Mix_LoadWAV("Fire1.wav");
  g_sound_exp[0] = Mix_LoadWAV("Explosion+1.wav");
  g_sound_exp[1] = Mix_LoadWAV("Bomb1.wav");
  g_sound_exp[2] = Mix_LoadWAV("nhac_nen.wav");
 
  if(g_sound_amo[0] == NULL || g_sound_amo[1] == NULL || g_sound_exp[0] == NULL || g_sound_exp[1] == NULL || g_sound_exp[2] == NULL )
  {
  return false;
  }

  if(TTF_Init() == -1)
  {
  return false;
  }

  g_font_text = TTF_OpenFont("XeroxSansSerifWideBoldOblique.ttf", 20);
  g_font_menu = TTF_OpenFont("AARDC___.TTF", 60);
  if(g_font_text == NULL)
  {
  return false;
  }

  return true;
}
 

int main(int argc, char* argv[])
{
    bool is_run_screen = true;
    int bkgn_x = 0; 
    //gọi hàm Init và kiểm tra nếu thành công thì tiếp tục
  bool is_quit = false;
  if (Init() == false)
   return 0;


 //gọi hàm loadimage để đọc image và trả vào biến g_background
  g_bkground = SDLcommonFunc::LoadImage("bk2.png");
  if (g_bkground == NULL)
  {
    return 0;
  }

  //mang cua nhan vat
  PlayerPower player_power;
  player_power.Init();

  TextObject mark_game;
  mark_game.SetColor(TextObject::WHITE_TEXT);

  //show ảnh nhân vật ra màn hình 
  mainobject human_object;
  human_object.SetRect(100, 200);
 bool ret = human_object.LoadImg("plane1.png");
 if(!ret)
 {
     return 0;
 }
 //xu li vu no
   
 ExplosionObject exp_main;
 ret = exp_main.LoadImg("exp_main.png");
 exp_main.set_clip();
 if(ret == false) return 0;



  //make THREATOBJECT
 ThreatsObject* p_threats = new ThreatsObject[NUM_THREATS];//mảng số lượng nhân vật địch, chạy vòng lặp
 for(int q=0; q < NUM_THREATS ; q++)
    {  
     ThreatsObject* p_threat = (p_threats + q);
     if(p_threat)
     {
     ret = p_threat->LoadImg("af1.png");
     if(ret == false)
     {
     return 0;
     }
     //random vi tri moi
     int rand_y = rand()%400;
     if(rand_y > SCREEN_HEIGHT - 200)
     {
     rand_y = SCREEN_HEIGHT*0.3;
     }
    
     p_threat->SetRect(SCREEN_WIDTH + q*800, rand_y);
     p_threat->set_x_val(SPEED_THREAT);

     AmoObject* p_amo = new AmoObject();

     p_threat->InitAmo(p_amo);
     }
    }
    
 unsigned int die_number = 0;
 unsigned int mark_value = 0;

 //show menu
 Mix_PlayChannel(-1, g_sound_exp[2], 0);
 int ret_menu = SDLcommonFunc::ShowMenu(g_screen, g_font_menu);
 Mix_HaltChannel(-1);
 if(ret_menu == 1)
 {
     is_quit = true;
 }


again_label:


  //vòng lặp luôn cập nhật image và sự kiện
 //hàm SDL_Flip sẽ liên tục cập nhật cửa sổ và giữ cho chương trình trong trạng thái liên tục chạy
 while (!is_quit) 
  {
    while (SDL_PollEvent(&g_even)) 
    {
      if (g_even.type == SDL_QUIT) //khi có sự kiện quit thì mới dừng lại
      {
        is_quit = true;
        break;
      }
      human_object.HandleInputAction(g_even, g_sound_amo);
    }
    //apply kết quả trong background vào screen
    
    //xử lí di chuyển màn hình
   if(is_run_screen == true)
     {
     bkgn_x -= 2;
     if(bkgn_x <= -(WIDTH_BACKGROUND - SCREEN_WIDTH))
     {
         is_run_screen = false;
     }
     else
     {
         SDLcommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
     }
    }
    else
     {
         SDLcommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
     }

     //hiển thị mạng nhân vật
     player_power.Render(g_screen);
     //show diem
    std::string val_str_mark = std::to_string(mark_value);
    std::string strMark("Mark: ");
    strMark += val_str_mark;

    mark_game.SetText(strMark);
    mark_game.CreatGameText(g_font_text,g_screen);

     //thực hiện main object
     human_object.Show(g_screen);
     human_object.HandleMove();
     human_object.MakeAmo(g_screen);
    
     
    //thực hiện THREAT
    for(int tt=0; tt < NUM_THREATS; tt++)
    {
    ThreatsObject* p_threat = (p_threats + tt);    
    if(p_threat)
    {     
    p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
    p_threat->Show(g_screen);   
    p_threat->MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);  
     
     //check va chạm máy bay và đạn địch
        bool is_col1 = false;
        std::vector<AmoObject*> amo_arr = p_threat->GetAmolist();
        for (int am = 0; am < amo_arr.size(); am++)
        {
          AmoObject* p_amo = amo_arr.at(am);
          if (p_amo)
          {
            is_col1 = SDLcommonFunc::CheckCollision(p_amo->GetRect(), human_object.GetRect());
            if (is_col1 == true)
            {
              p_threat->Reset(SCREEN_WIDTH + tt*400);
              p_threat->ResetAmo(p_amo);
              Mix_PlayChannel(-1, g_sound_exp[1], 0);
              break;
            }
          }
        }

    //check va cham của máy bay và địch
    bool is_col = SDLcommonFunc::CheckCollision(human_object.GetRect(),p_threat->GetRect());
    
      //xu li vu no
    if(is_col1 || is_col)
    {
     for(int ex = 0; ex < 4; ex++)
        {
          int x_pos = (human_object.GetRect().x + human_object.GetRect().w * 0.5 - EXP_WIDTH*0.5);
          int y_pos = (human_object.GetRect().y + human_object.GetRect().h * 0.5 - EXP_HEIGHT*0.5);

          exp_main.set_frame(ex);
          exp_main.SetRect(x_pos, y_pos);
          exp_main.ShowEx(g_screen);
          
          if ( SDL_Flip(g_screen) == -1)
           {
            p_threat->Reset(SCREEN_WIDTH + tt*400);
            delete [] p_threats;
            SDLcommonFunc::CleanUp();
            SDL_Quit();
            return 0;
           }
        }
            Mix_PlayChannel(-1, g_sound_exp[1], 0);
            
            die_number++;
            if(die_number <= 2)
            {
                SDL_Delay(1000);
                human_object.SetRect(100,200);
                player_power.Decrease();
                player_power.Render(g_screen);

                if(SDL_Flip(g_screen)==-1)
                {
                    delete [] p_threats;
                    SDLcommonFunc::CleanUp();
                    SDL_Quit();
                    return 0;
                }
            }
            else if(die_number > 2)
            {
              int ret_lose =  SDLcommonFunc::ShowLose(g_screen, g_font_menu);
              if (ret_lose == 1)
                {
                 delete [] p_threats;
                 SDLcommonFunc::CleanUp();
                 SDL_Quit();
                 return 1;
                }
              // play again
              else if(ret_lose == 0)
              {
                
                human_object.setX_val(0);
                human_object.setY_val_(0);
                human_object.SetRect(100,200);
                player_power.Init();
                die_number=0;
                bkgn_x = 0;
                p_threat->Reset(SCREEN_WIDTH);
                player_power.Render(g_screen);
                mark_value = 0;

                goto again_label;
              }
             }
    }

    //va cham dan va may bay dich
    //reset threat
    std::vector<AmoObject*>amo_list = human_object.GetAmolist();
    for(int im = 0; im < amo_list.size();im++)
    {
        AmoObject* p_amo = amo_list.at(im);
        if(p_amo != NULL)
        {
            bool ret_col = SDLcommonFunc::CheckCollision(p_amo->GetRect(),p_threat->GetRect());
            if(ret_col)
            {

           mark_value += 10;
          //xu li vu no
          for(int ex = 0; ex < 4; ex++)
           {
            //xac dinh vi tri va cham
            int x_pos = (p_threat->GetRect().x + p_threat->GetRect().w * 0.5 - EXP_WIDTH*0.5);
            int y_pos = (p_threat->GetRect().y + p_threat->GetRect().h * 0.5 - EXP_HEIGHT*0.5);

            //xu li vu no clip
            exp_main.set_frame(ex);
            exp_main.SetRect(x_pos, y_pos);
            exp_main.ShowEx(g_screen);

            
            if ( SDL_Flip(g_screen) == -1)
            {
            delete [] p_threats;
            SDLcommonFunc::CleanUp();
            SDL_Quit();
            return 0;
            }
           }
            p_threat->Reset(SCREEN_WIDTH + tt*400);
            human_object.RemoveAmo(im);
            Mix_PlayChannel(-1, g_sound_exp[0], 0);
           }
        }
      }
    }
  }

    //update screen
  if ( SDL_Flip(g_screen) == -1)
    {
      delete [] p_threats;
      SDLcommonFunc::CleanUp();
      SDL_Quit();
      return 0;
    }
  }
    
  

 delete [] p_threats; 

 //khi có sự kiện "quit" chương trình sẽ gọi hàm "clean up" để giải phóng cho các biến
  SDLcommonFunc::CleanUp();
  SDL_Quit();
  return 1;
}
 