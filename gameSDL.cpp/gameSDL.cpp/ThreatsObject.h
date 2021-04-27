

#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_

#include"common_Function.h"
#include"baseObject.h"
#include"AmoObject.h"
#include<vector>

#define WIDTH_THREAT 80
#define HEIGHT_THREAT 33



class ThreatsObject : public baseobject
{
public:
    ThreatsObject();
    ~ThreatsObject();
    //ham xu li move
    void HandleMove(const int& x_border,const int& y_border);
    void HandInputAction(SDL_Event event);
    void set_x_val(const int& val) {x_val_ = val;}
    void set_y_val(const int& val) {y_val_ = val;}
    int get_x_val() const { return x_val_;}
    int get_y_val() const { return y_val_;}
    
    //vector
    void SetAmolist(std::vector<AmoObject*>amo_list)  { p_amo_list_ = amo_list;}
    std::vector<AmoObject*> GetAmolist() const {return p_amo_list_;} 
    
   
    void InitAmo(AmoObject* p_amo);
    void MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit );

    //reset lai dich va dan ban cua dich
    void Reset(const int& xboder);
    void ResetAmo(AmoObject* p_amo);

private:
    int x_val_;
    int y_val_;

     std::vector<AmoObject*>p_amo_list_;

};

#endif