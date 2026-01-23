#include "gpaint.h"

bool Paint::Init(){

    if(!SDL_CreateWindowAndRenderer("Gipsy Paint", 800 , 600 , 0 , &window , &renderer)){
        SDL_Log("\nError : %s " , SDL_GetError());
        return false;
    }


    //Initialize colors unordered map , 1st column
    Colors[White] = SDL_Color{255,255,255,255};
    Colors[Cyan] = SDL_Color{0,255,255,255};
    Colors[Black] = SDL_Color{0,0,0,255};
    Colors[Blue] = SDL_Color{0,0,255,255};
    Colors[Purple] = SDL_Color{128,0,128,255};
    //2nd column
    Colors[Red] = SDL_Color{255,0,0,255};
    Colors[Orange] = SDL_Color{255,165,0,255};
    Colors[Pink] = SDL_Color{255,192,203,255};
    Colors[Green] = SDL_Color{0,255,0,255};
    Colors[Yellow] = SDL_Color{255,255,0,255};


    Brush_color = Colors[Black];

    //Initialize Color Rects, 2 columns of 5 colors each ; !st column : White Red, Cyan , Purple , Blue ; 2nd column : Black, Orange, Pink, Green, Yellow
    float rect_w = 50.0f;
    float rect_h = 50.0f;
    ColorRects.reserve(10);

    for(int i = 0 ; i < 5 ; i++){
        SDL_FRect r1 = {0.0f , (float)i * rect_h , rect_w , rect_h};
        ColorRects.emplace_back(r1);

        SDL_FRect r2 = {rect_w , (float)i * rect_h , rect_w , rect_h};
        ColorRects.emplace_back(r2);
    }
    SDL_FRect brush_rect = {100 , 0 ,50 , 50};


    SDL_SetRenderDrawColor(renderer , 255,255,255,255);
    SDL_RenderClear(renderer);


    return true;
}


void Paint::RenderColorRects(){
    
    
    int index = 0;
    for ( auto const &pair : Colors){
        SDL_SetRenderDrawColor(renderer , pair.second.r , pair.second.g , pair.second.b , pair.second.a);
        SDL_RenderFillRect(renderer , &ColorRects[index]);
        index++;
    }
    SDL_SetRenderDrawColor(renderer , Brush_color.r , Brush_color.g , Brush_color.b , Brush_color.a);
    SDL_RenderFillRect(renderer , &Brush_rect);

}


void Paint::Render(){
    

    this->RenderColorRects();

    SDL_Delay(Delay_ms);
    SDL_RenderPresent(renderer);
    
}

bool Paint::Clicks_onColorRect(float px , float py){


    if(px > 100 || py > 250){
        return false;
    }

    //Set Brush to Color clikecd
    int index = 0;
    for ( auto const &pair : Colors){
        if(px > ColorRects[index].x && py > ColorRects[index].y && px < (ColorRects[index].x + 50) && py <(ColorRects[index].y + 50)){
            //Estamois dentro del color
            Brush_color = pair.second;
        }
        index++;
    }

    return true;


}


void Paint::HandleEvents(SDL_Event * event){

    if(event->button.button == SDL_BUTTON_RIGHT){
        SDL_SetRenderDrawColor(renderer , 255,255,255,255);
        SDL_RenderClear(renderer);
    }
    if(event->key.key == SDLK_UP){
        rect_brush.w ++;
        rect_brush.h ++;
    }

    if(event->key.key == SDLK_DOWN){
        rect_brush.w --;
        rect_brush.h --;
    }

    if(event->type == SDL_EVENT_MOUSE_BUTTON_DOWN){
        if(this->Clicks_onColorRect(event->button.x , event->button.y))return;
    }

    if(event->type == SDL_EVENT_MOUSE_MOTION){
        if(event->motion.state & SDL_BUTTON_LMASK){
            SDL_SetRenderDrawColor(renderer , Brush_color.r, Brush_color.g , Brush_color.b , Brush_color.a);
            rect_brush.x = event->button.x ; 
            rect_brush.y = event->button.y ; 
            SDL_RenderFillRect(renderer , &rect_brush);
        }
    }
}