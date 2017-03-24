#include <SDL_image.h>
#include "gui.h"

#define SCREEN_WIDTH 1000

#define DATA_WINDOW_WIDTH  200
#define DATA_WINDOW_BOT    300

#define CANNON_WIDTH       9
#define CANNONBALL_RADIUS  4

#define WIN_SCREEN_X 400
#define WIN_SCREEN_Y 200

GUIData *InitGUIData( SDL_Surface *pScreen )
{
    GUIData *pGUIData = (GUIData *)malloc( sizeof( GUIData ) );
    if( pGUIData == NULL )
    {
        fprintf(stderr, "Can not allocate enough memory!\n");
        exit(1);
    }

    pGUIData->pScreen     = pScreen;
    pGUIData->pBackground = IMG_Load( "resources/hatter.png" );
    if ( pGUIData->pBackground == NULL )
    {
        fprintf(stderr, "Nem sikerult betolteni a hatteret!\n");
        exit(1);
    }

    for( int i=0; i<8; ++i )
    {
        char path1[20] = "resources/lovX.png";
        char path2[20] = "resources/lovXk.png";
        path1[13] = i + '1';
        path2[13] = i + '1';

        pGUIData->arrKnightP1[i] = IMG_Load( path1 );
        pGUIData->arrKnightP2[i] = IMG_Load( path2 );

        if( pGUIData->arrKnightP1[i] == NULL || pGUIData->arrKnightP2[i] == NULL )
        {
            fprintf(stderr, "Nem sikerult betolteni a lovagok kepet!\n");
            exit(1);
        }
    }

    return pGUIData;
}

void DestructGUIData( GUIData *pGUIData )
{
    SDL_FreeSurface( pGUIData->pScreen );
    SDL_FreeSurface( pGUIData->pBackground );

    for(int i=0; i<8; ++i)
    {
        SDL_FreeSurface( pGUIData->arrKnightP1[i] );
        SDL_FreeSurface( pGUIData->arrKnightP2[i] );
    }

    free( pGUIData );
}

void RefreshGUI( GUIData *pGUIData, GameData *pGameData )
{
    SDL_Surface *pScreen = pGUIData->pScreen;

    SDL_BlitSurface( pGUIData->pBackground, NULL, pScreen, NULL );

    _PaintDataWindow( pScreen, pGameData );

    _PaintKnights( pGUIData, pGameData->pFirstKnightPlayer1 );
    _PaintKnights( pGUIData, pGameData->pFirstKnightPlayer2 );

    _PaintCannonBalls( pScreen, pGameData );
    _PaintCannons(     pScreen, pGameData );

    _PaintWinScreen( pScreen, pGameData );

    SDL_Flip(pScreen);
}

void _PaintDataWindow( SDL_Surface *pScreen, GameData *pGameData )
{
    // KNIGHT PRICE
    char strPriceP1[50];
    sprintf( strPriceP1, "Knight price:%6d gold", pGameData->iKnightPricePlayer1 );
    char strPriceP2[50];
    sprintf( strPriceP2, "Knight price:%6d gold", pGameData->iKnightPricePlayer2 );
    stringRGBA( pScreen, 0,                        DATA_WINDOW_BOT, strPriceP1, 0, 0, 0, 255 );
    stringRGBA( pScreen, SCREEN_WIDTH - DATA_WINDOW_WIDTH, DATA_WINDOW_BOT, strPriceP2, 0, 0, 0, 255 );

    // GOLD
    char strGoldP1[50];
    sprintf( strGoldP1, "Treasury:%10d gold", pGameData->iGoldPlayer1 );
    char strGoldP2[50];
    sprintf( strGoldP2, "Treasury:%10d gold", pGameData->iGoldPlayer2 );
    stringRGBA( pScreen, 0,                        DATA_WINDOW_BOT - 8, strGoldP1, 0, 0, 0, 255 );
    stringRGBA( pScreen, SCREEN_WIDTH - DATA_WINDOW_WIDTH, DATA_WINDOW_BOT - 8, strGoldP2, 0, 0, 0, 255 );

    //LOAD
    char strLoadP1[50];
    sprintf( strLoadP1, "Cannon load: %6d %%", ROUND_DOUBLE_TO_INT( pGameData->dLoadPercentPlayer1 * 100 ) );
    char strLoadP2[50];
    sprintf( strLoadP2, "Cannon load: %6d %%", ROUND_DOUBLE_TO_INT( pGameData->dLoadPercentPlayer2 * 100 ) );
    stringRGBA( pScreen, 0,                        DATA_WINDOW_BOT - 16, strLoadP1, 0, 0, 0, 255 );
    stringRGBA( pScreen, SCREEN_WIDTH - DATA_WINDOW_WIDTH, DATA_WINDOW_BOT - 16, strLoadP2, 0, 0, 0, 255 );

    //ECONOMY
    char strEconomyP1[50];
    int iEconomyLevelP1 = pGameData->iEconomyPlayer1;
    sprintf( strEconomyP1, "Economy %4d: %5d gold", iEconomyLevelP1, GetUpgradePrice( iEconomyLevelP1 ) );
    char strEconomyP2[50];
    int iEconomyLevelP2 = pGameData->iEconomyPlayer2;
    sprintf( strEconomyP2, "Economy %4d: %5d gold", iEconomyLevelP2, GetUpgradePrice( iEconomyLevelP2 ) );
    stringRGBA( pScreen, 0,                        DATA_WINDOW_BOT - 24, strEconomyP1, 0, 0, 0, 255 );
    stringRGBA( pScreen, SCREEN_WIDTH - DATA_WINDOW_WIDTH, DATA_WINDOW_BOT - 24, strEconomyP2, 0, 0, 0, 255 );

    //LOAD_TIME
    char strLoadTimeP1[50];
    int iLoadTimeLevelP1 = pGameData->iLoadTimePlayer1;
    sprintf( strLoadTimeP1, "Load time %2d: %5d gold", iLoadTimeLevelP1, GetUpgradePrice( iLoadTimeLevelP1 ) );
    char strLoadTimeP2[50];
    int iLoadTimeLevelP2 = pGameData->iLoadTimePlayer2;
    sprintf( strLoadTimeP2, "Load time %2d: %5d gold", iLoadTimeLevelP2, GetUpgradePrice( iLoadTimeLevelP2 ) );
    stringRGBA( pScreen, 0,                        DATA_WINDOW_BOT - 32, strLoadTimeP1, 0, 0, 0, 255 );
    stringRGBA( pScreen, SCREEN_WIDTH - DATA_WINDOW_WIDTH, DATA_WINDOW_BOT - 32, strLoadTimeP2, 0, 0, 0, 255 );

    //SPAWN_HP
    char strSawnHPP1[50];
    int iSawnHPLevelP1 = pGameData->iKnightSpawningHpPlayer1;
    sprintf( strSawnHPP1, "Spawn HP %3d: %5d gold", iSawnHPLevelP1, GetUpgradePrice( iSawnHPLevelP1 ) );
    char strSawnHPP2[50];
    int iSawnHPLevelP2 = pGameData->iKnightSpawningHpPlayer2;
    sprintf( strSawnHPP2, "Spawn HP %3d: %5d gold", iSawnHPLevelP2, GetUpgradePrice( iSawnHPLevelP2 ) );
    stringRGBA( pScreen, 0,                        DATA_WINDOW_BOT - 40, strSawnHPP1, 0, 0, 0, 255 );
    stringRGBA( pScreen, SCREEN_WIDTH - DATA_WINDOW_WIDTH, DATA_WINDOW_BOT - 40, strSawnHPP2, 0, 0, 0, 255 );

    //DAMAGE
    char strDMGP1[50];
    int iDMGLevelP1 = pGameData->iKnightDamagePlayer1;
    sprintf( strDMGP1, "Knight DMG%2d: %5d gold", iDMGLevelP1, GetUpgradePrice( iDMGLevelP1 ) );
    char strDMGP2[50];
    int iDMGLevelP2 = pGameData->iKnightDamagePlayer2;
    sprintf( strDMGP2, "Knight DMG%2d: %5d gold", iDMGLevelP2, GetUpgradePrice( iDMGLevelP2 ) );
    stringRGBA( pScreen, 0,                        DATA_WINDOW_BOT - 48, strDMGP1, 0, 0, 0, 255 );
    stringRGBA( pScreen, SCREEN_WIDTH - DATA_WINDOW_WIDTH, DATA_WINDOW_BOT - 48, strDMGP2, 0, 0, 0, 255 );
}

void _PaintKnights( GUIData *pGUIData, Knight *pFirstKnight )
{
    if( pFirstKnight == NULL )
        return;

    if( pFirstKnight->ePlayer == PLAYER_1 )
    {
        for( Knight *pKnight = pFirstKnight; pKnight != NULL; pKnight = pKnight->pNextKnight )
        {
            SDL_Rect rect = { pKnight->iXPos + KNIGHT_PATH_LEFT, KNIGHT_PATH_TOP, KNIGHT_WIDTH, KNIGHT_HEIGHT };
            SDL_BlitSurface( pGUIData->arrKnightP1[pKnight->eState], NULL, pGUIData->pScreen, &rect );
        }
    }
    else
    {
        for( Knight *pKnight = pFirstKnight; pKnight != NULL; pKnight = pKnight->pNextKnight )
        {
            SDL_Rect rect = { pKnight->iXPos + KNIGHT_PATH_LEFT, KNIGHT_PATH_TOP, KNIGHT_WIDTH, KNIGHT_HEIGHT };
            SDL_BlitSurface( pGUIData->arrKnightP2[pKnight->eState], NULL, pGUIData->pScreen, &rect );
        }
    }
}

void _PaintCannons( SDL_Surface *pScreen, GameData *pGameData )
{
    double dAngle1 = pGameData->dCannonAnglePlayer1;
    thickLineRGBA( pScreen, CANNON_POSX_P1, CANNON_POSY, CANNON_POSX_P1 + cos( dAngle1 ) * CANNON_LENGTH, CANNON_POSY - sin( dAngle1 ) * CANNON_LENGTH, CANNON_WIDTH, 0, 0, 0, 255 );

    double dAngle2 = pGameData->dCannonAnglePlayer2;
    thickLineRGBA( pScreen, CANNON_POSX_P2, CANNON_POSY, CANNON_POSX_P2 + cos( dAngle2 ) * CANNON_LENGTH, CANNON_POSY - sin( dAngle2 ) * CANNON_LENGTH, CANNON_WIDTH, 0, 0, 0, 255 );
}

void _PaintCannonBalls( SDL_Surface *pScreen, GameData *pGameData )
{
    if( pGameData->cannonBallPlayer1.bValid == true )
    {
        int iX = ROUND_DOUBLE_TO_INT( pGameData->cannonBallPlayer1.vectorPos.dX );
        int iY = ROUND_DOUBLE_TO_INT( pGameData->cannonBallPlayer1.vectorPos.dY );
        filledCircleRGBA( pScreen, iX, iY, CANNONBALL_RADIUS, 0, 0, 0, 255 );
    }

    if( pGameData->cannonBallPlayer2.bValid == true )
    {
        int iX = ROUND_DOUBLE_TO_INT( pGameData->cannonBallPlayer2.vectorPos.dX );
        int iY = ROUND_DOUBLE_TO_INT( pGameData->cannonBallPlayer2.vectorPos.dY );
        filledCircleRGBA( pScreen, iX, iY, CANNONBALL_RADIUS, 0, 0, 0, 255 );
    }
}

void _PaintWinScreen( SDL_Surface *pScreen, GameData *pGameData )
{
    char strGameOver[70] = "GAME OVER - Winner: ";
    switch( pGameData->ePlayerWon )
    {
        case PLAYER_NONE: break;
        case PLAYER_BOTH: stringRGBA( pScreen, WIN_SCREEN_X, WIN_SCREEN_Y, strcat( strGameOver, "DRAW" ), 0, 0, 0, 255 ); break;
        case PLAYER_1   : stringRGBA( pScreen, WIN_SCREEN_X, WIN_SCREEN_Y, strcat( strGameOver, pGameData->strNamePlayer1 ), 0, 0, 0, 255 ); break;
        case PLAYER_2   : stringRGBA( pScreen, WIN_SCREEN_X, WIN_SCREEN_Y, strcat( strGameOver, pGameData->strNamePlayer2 ), 0, 0, 0, 255 ); break;
        default: break;
    }
}
