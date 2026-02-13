#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include <map>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#define TARGET_FPS 120


enum colors_name{
    White,
    Black,
    Red,
    Orange,
    Cyan,
    Pink,
    Purple,
    Green, 
    Blue,
    Yellow,
};


class Paint{


    private : 
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        float Delay_ms = (1.0f / TARGET_FPS) * 1000;


        std::map<colors_name , SDL_Color> Colors;        

        std::vector<SDL_FRect> ColorRects;
        SDL_FRect Brush_rect = {0,300,50,50};

        SDL_Color Brush_color;

        SDL_FRect rect_brush {0,0,7,7};


    public : 

        bool Init();
        void Render();
        void RenderColorRects();
        void HandleEvents(SDL_Event * event);
        bool Clicks_onColorRect(float px , float py);
        void Paint_at_point(float x , float y);

};
