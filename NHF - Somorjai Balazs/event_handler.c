#include "event_handler.h"

#define NOTUSED()

EventData *InitEventData()
{
    EventData *pEventData  = (EventData *)malloc( sizeof( EventData ) );
    if( pEventData == NULL )
    {
        fprintf(stderr, "Can not allocate enough memory!\n");
        exit(1);
    }
    pEventData->pLastEvent = NULL;

    return pEventData;
}

void DestructEventData( EventData *pEventData )
{
    free( pEventData );
}

void HandleEvent( EventData *pEventData, SDL_Event *pEvent, GameData *pGameData )
{
    if( EvaluateWin( pGameData ) )
        return;

    pEventData->pLastEvent = pEvent;

    switch (pEvent->type)
    {
        case SDL_KEYDOWN  : _HandleKeyEvent(   pEventData, pEvent, pGameData ); break;
        case SDL_USEREVENT: _HandleTimerEvent( pEventData, pEvent, pGameData ); break;
    }
    // TODO
}

bool UserTerminated( EventData *pEventData )
{
    if( pEventData->pLastEvent == NULL )
        return false;

    return pEventData->pLastEvent->type == SDL_QUIT;
}

void _HandleKeyEvent( EventData *pEventData, SDL_Event *pEvent, GameData *pGameData  )
{
    switch( pEvent->key.keysym.sym )
    {
        // Player1
        case SDLK_TAB      : AddKnight(      pGameData, PLAYER_1 ); break;
        case SDLK_w        : MoveCannonUp(   pGameData, PLAYER_1 ); break;
        case SDLK_s        : MoveCannonDown( pGameData, PLAYER_1 ); break;
        case SDLK_LSHIFT   : FireCannon(     pGameData, PLAYER_1 ); break;
        case SDLK_1        : UpgradeEconomy( pGameData, PLAYER_1 ); break;
        case SDLK_2        : UpgradeLoad(    pGameData, PLAYER_1 ); break;
        case SDLK_3        : UpgradeSpawnHP( pGameData, PLAYER_1 ); break;
        case SDLK_4        : UpgradeDamage(  pGameData, PLAYER_1 ); break;

        // Player2
        case SDLK_SPACE    : AddKnight(      pGameData, PLAYER_2 ); break;
        case SDLK_UP       : MoveCannonUp(   pGameData, PLAYER_2 ); break;
        case SDLK_DOWN     : MoveCannonDown( pGameData, PLAYER_2 ); break;
        case SDLK_RSHIFT   : FireCannon(     pGameData, PLAYER_2 ); break;
        case SDLK_v        : UpgradeEconomy( pGameData, PLAYER_2 ); break;
        case SDLK_b        : UpgradeLoad(    pGameData, PLAYER_2 ); break;
        case SDLK_n        : UpgradeSpawnHP( pGameData, PLAYER_2 ); break;
        case SDLK_m        : UpgradeDamage(  pGameData, PLAYER_2 ); break;
        default: break;
    }
}

void _HandleTimerEvent( EventData *pEventData, SDL_Event *pEvent, GameData *pGameData )
{
    ++pGameData->iTickCount;

    StepKnights(     pGameData );
    FightKnights(    pGameData );
    MoveCannonBall(  pGameData );
    RegisterHit(     pGameData );
    UpdateCannLoad(  pGameData );
    CalculateIncome( pGameData );
}
