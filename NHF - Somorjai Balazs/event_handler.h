#include <stdbool.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include "game_data.h"

#ifndef EVENT_HANDLER_H_INCLUDED
#define EVENT_HANDLER_H_INCLUDED


///////////////////
// Event Handler //
///////////////////

typedef struct EventData{
    SDL_Event   *pLastEvent;
} EventData;

EventData *InitEventData();
void       DestructEventData( EventData *pEventData );
void       HandleEvent   ( EventData *pEventData, SDL_Event *pEvent, GameData *pGameData );
bool       UserTerminated( EventData *pEventData );

void _HandleKeyEvent(   EventData *pEventData, SDL_Event *pEvent, GameData *pGameData );
void _HandleTimerEvent( EventData *pEventData, SDL_Event *pEvent, GameData *pGameData );

#endif // EVENT_HANDLER_H_INCLUDED
