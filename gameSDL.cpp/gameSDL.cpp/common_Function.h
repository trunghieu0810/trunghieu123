
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_


#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>


//thông số đại diện cho background
const int WIDTH_BACKGROUND = 9600;
const int HEIGHT_BACKGROUND = 600;

//các thông số cố định quy định màn hình
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
//so luong dich
const int NUM_THREATS = 3;
//toc do
const int SPEED_THREAT = 4;
const int SPEED_AMO = 8;

 //biến quản lí screen và background thành các biến global
static SDL_Surface* g_screen = NULL;
static SDL_Surface* g_bkground = NULL;
static SDL_Surface* g_img_menu = NULL;
static SDL_Surface* g_img_lose = NULL;
static SDL_Event g_even; 

//bien global quan ly am thanh
static Mix_Chunk* g_sound_amo[2];
static Mix_Chunk* g_sound_exp[3];

namespace SDLcommonFunc
{
    SDL_Surface* LoadImage(std::string file_path);
    //truyen vao man hinh
    SDL_Rect ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
    //truyen lien tiep hinh anh tao clip
    void ApplySurfacelip(SDL_Surface* src, SDL_Surface* des,SDL_Rect* clip, int x, int y);
    void CleanUp();
    //check va cham
    bool CheckCollision(const SDL_Rect& object1,const SDL_Rect& object2); 
    //show menu
    int ShowMenu(SDL_Surface* des,TTF_Font* font);
    //show lose
    int ShowLose(SDL_Surface* des,TTF_Font* font);
    //kiem tra toa do 1 diem
    bool CheckForcusWithRect(const int& x,const int& y,const SDL_Rect& rect);
}
#endif



//commonfunction: các hàm xử lý chung