#include "gpaint.h"

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>



SDL_AppResult SDL_AppInit(void ** appstate , int argc , char * argv[]){
    Paint* p = new Paint();
    *appstate = p;

    if(!p->Init())return SDL_APP_FAILURE;

    SDL_Log("\nPress q for exit, Up for increasing brush size, Down for decreasing it, Right click for cleaning the canvas");

    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppIterate(void * appstate){
    
    Paint * p = (Paint*)appstate;
    p->Render();
   
    return SDL_APP_CONTINUE;

}


SDL_AppResult SDL_AppEvent(void * appstate , SDL_Event* event){
    Paint * p = (Paint*)appstate;

    if(event->type == SDL_EVENT_QUIT || event->key.key == SDLK_Q){
        return SDL_APP_SUCCESS;
    }
    p->HandleEvents(event); 

    return SDL_APP_CONTINUE;

}
void SDL_AppQuit(void *appstate, SDL_AppResult result){

}