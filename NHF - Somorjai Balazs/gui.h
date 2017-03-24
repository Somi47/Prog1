#include <stdbool.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include "game_data.h"

#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

typedef struct GUIData{
    SDL_Surface *pScreen;
    SDL_Surface *pBackground;
    SDL_Surface *arrKnightP1[8]; // 8db surface pointert tároló tömb
    SDL_Surface *arrKnightP2[8]; // 8db surface pointert tároló tömb
} GUIData;

GUIData *InitGUIData( SDL_Surface *pScreen );
void     DestructGUIData( GUIData *pGUIData );
void     RefreshGUI( GUIData *pGUIData, GameData *pGameData );

// private
void _PaintDataWindow(  SDL_Surface *pScreen, GameData *pGameData );
void _PaintKnights(     GUIData     *pGUIData, Knight *pFirstKnight );
void _PaintCannons(     SDL_Surface *pScreen, GameData *pGameData );
void _PaintCannonBalls( SDL_Surface *pScreen, GameData *pGameData );
void _PaintWinScreen(   SDL_Surface *pScreen, GameData *pGameData );

#endif // GUI_H_INCLUDED
