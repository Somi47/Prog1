#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <stdbool.h>
#include "event_handler.h"
#include "game_data.h"
#include "gui.h"

Uint32 TimerTick(Uint32 ms, void *param)
{
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}

int main(int argc, char *argv[])
{
    SDL_Event    event;
    SDL_Surface *pScreen;
    EventData   *pEventData;
    GameData    *pGameData;
    GUIData     *pGUIData;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    SDL_AddTimer(35, TimerTick, NULL);
    pScreen    = SDL_SetVideoMode(1000, 600, 0, SDL_ANYFORMAT);

    pEventData = InitEventData();
    pGameData  = InitGameData();
    pGUIData   = InitGUIData( pScreen );

    if ( pScreen == NULL )
    {
        fprintf(stderr, "Nem sikerult megnyitni az ablakot!\n");
        exit(1);
    }
    SDL_WM_SetCaption("NHF - Somorjai Balazs", "NHF - Somorjai Balazs");

    while( UserTerminated( pEventData ) == false )
    {
        RefreshGUI( pGUIData, pGameData );
        SDL_WaitEvent(&event);
        HandleEvent( pEventData, &event, pGameData );
    }

    DestructEventData( pEventData );
    DestructGameData(  pGameData  );
    DestructGUIData(   pGUIData   );
    SDL_Quit();

    return 0;
}
