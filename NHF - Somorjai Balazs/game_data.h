#include <stdbool.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#ifndef GAME_DATA_H_INCLUDED
#define GAME_DATA_H_INCLUDED

#define CANNON_LENGTH             60
#define KNIGHT_PATH_LENGHT       770
#define KNIGHT_PATH_LEFT         100
#define KNIGHT_PATH_TOP          475
#define KNIGHT_WIDTH              31
#define KNIGHT_HEIGHT             40
#define KNIGHT_ADJACENCY          30
#define CANNONBALL_INITIAL_SPEED  10.0
#define CANNONBALL_GRAVITY         0.2
#define CANNON_POSX_P1           100
#define CANNON_POSX_P2           900
#define CANNON_POSY              400

#define ROUND_DOUBLE_TO_INT( d ) (int)( d > 0 ? d + 0.5 : d - 0.5 )


typedef enum{
    PLAYER_1,
    PLAYER_2,
    PLAYER_NONE,
    PLAYER_BOTH
} EPlayer;

typedef struct{
    double dX, dY;
} Vector;

typedef struct{
    Vector vectorPos;
    Vector vectorSpeed;
    bool   bValid;
} CannonBall;

typedef enum{
    S0,
    S1,
    S2,
    S3,
    S4,
    S5,
    S6,
    S7,
} EAnimState;

typedef struct Knight{
    EPlayer        ePlayer;
    int            iHp;
    int            iXPos;
    EAnimState     eState;
    struct Knight *pPrevKnight;
    struct Knight *pNextKnight;
} Knight;

typedef struct GameData{
    int         iTickCount;
    EPlayer     ePlayerWon;
    char       *strNamePlayer1;
    char       *strNamePlayer2;
    Knight     *pFirstKnightPlayer1;
    Knight     *pFirstKnightPlayer2;
    CannonBall  cannonBallPlayer1;
    CannonBall  cannonBallPlayer2;
    double      dCannonAnglePlayer1;
    double      dCannonAnglePlayer2;
    int         iGoldPlayer1;
    int         iGoldPlayer2;
    double      dLoadPercentPlayer1;
    double      dLoadPercentPlayer2;
    int         iKnightPricePlayer1;
    int         iKnightPricePlayer2;

    //Improvements
    int iKnightSpawningHpPlayer1;
    int iKnightSpawningHpPlayer2;
    int iKnightDamagePlayer1;
    int iKnightDamagePlayer2;
    int iLoadTimePlayer1;
    int iLoadTimePlayer2;
    int iEconomyPlayer1;
    int iEconomyPlayer2;
} GameData;

GameData *InitGameData();
void      DestructGameData( GameData *pGameData );
void      StepKnights(     GameData *pGameData );
void      FightKnights(    GameData *pGameData );
void      AddKnight(       GameData *pGameData, EPlayer ePlayer );
void      MoveCannonUp(    GameData *pGameData, EPlayer ePlayer );
void      MoveCannonDown(  GameData *pGameData, EPlayer ePlayer );
void      FireCannon(      GameData *pGameData, EPlayer ePlayer );
void      MoveCannonBall(  GameData *pGameData );
void      RegisterHit(     GameData *pGameData );
void      UpdateCannLoad(  GameData *pGameData );
void      CalculateIncome( GameData *pGameData );

bool EvaluateWin( GameData *pGameData );

//Upgrades
void UpgradeEconomy( GameData *pGameData, EPlayer ePlayer );
void UpgradeLoad(    GameData *pGameData, EPlayer ePlayer );
void UpgradeSpawnHP( GameData *pGameData, EPlayer ePlayer );
void UpgradeDamage(  GameData *pGameData, EPlayer ePlayer );

int GetUpgradePrice( int iLevel );

//private:
bool    _GetCanKnightMove( GameData *pGameData, Knight *pKnight );
Knight *_CreateKnight( GameData *pGameData, EPlayer ePlayer, Knight *pPrevKnight );
bool    _GetKnightHit( Knight *pKnight, int posXCannonBall, int posYCannonBall );
char*   _GetLine( FILE *pFile );
#endif // GAME_DATA_H_INCLUDED
