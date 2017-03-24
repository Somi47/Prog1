#include "game_data.h"
#include <math.h>
#include <stdio.h>

#define DAMAGE_MULTIPLIER       10
#define KNIGHT_PRICE_MULTIPLIER  1.20
#define LOAD_MULTIPLIER          0.001
#define INCOME_MULTIPLIER       50
#define SPAWN_HP_MULTIPLIER    100

#define CANNON_ANGLE_CHANGE 0.1

#define GROUND_POS_Y 515

GameData *InitGameData()
{
    FILE *pFileNames = fopen( "players.txt", "r" );
    if( pFileNames == NULL )
    {
        fprintf(stderr, "Nem sikerult betolteni a players.txt-t!\n");
        exit(1);
    }

    GameData *pGameData = (GameData *)malloc( sizeof( GameData ) );
    if( pGameData == NULL )
    {
        fprintf(stderr, "Can not allocate enough memory!\n");
        exit(1);
    }

    pGameData->iTickCount               = 0;
    pGameData->ePlayerWon               = PLAYER_NONE;
    pGameData->strNamePlayer1           = _GetLine( pFileNames );
    pGameData->strNamePlayer2           = _GetLine( pFileNames );
    pGameData->pFirstKnightPlayer1      = NULL;
    pGameData->pFirstKnightPlayer2      = NULL;
    pGameData->cannonBallPlayer1.bValid = false;
    pGameData->cannonBallPlayer2.bValid = false;
    pGameData->dCannonAnglePlayer1      = M_PI / 6;
    pGameData->dCannonAnglePlayer2      = 5 * M_PI / 6;
    pGameData->dLoadPercentPlayer1      = 0.0;
    pGameData->dLoadPercentPlayer2      = 0.0;
    pGameData->iGoldPlayer1             = 0;
    pGameData->iGoldPlayer2             = 0;
    pGameData->iKnightPricePlayer1      = 500;
    pGameData->iKnightPricePlayer2      = 500;

    //Improvements
    pGameData->iKnightSpawningHpPlayer1 = 1;
    pGameData->iKnightSpawningHpPlayer2 = 1;
    pGameData->iKnightDamagePlayer1     = 1;
    pGameData->iKnightDamagePlayer2     = 1;
    pGameData->iLoadTimePlayer1         = 1;
    pGameData->iLoadTimePlayer2         = 1;
    pGameData->iEconomyPlayer1          = 1;
    pGameData->iEconomyPlayer2          = 1;

    fclose( pFileNames );
    return pGameData;
}

void DestructGameData( GameData *pGameData )
{
    free( pGameData->strNamePlayer1 );
    free( pGameData->strNamePlayer2 );

    Knight *pNextKnight = pGameData->pFirstKnightPlayer1;
    while( pNextKnight != NULL )
    {
        Knight *pTmpKnight = pNextKnight;
        pNextKnight = pNextKnight->pNextKnight;
        free( pTmpKnight );
    }

    pNextKnight = pGameData->pFirstKnightPlayer2;
    while( pNextKnight != NULL )
    {
        Knight *pTmpKnight = pNextKnight;
        pNextKnight = pNextKnight->pNextKnight;
        free( pTmpKnight );
    }

    free( pGameData );
}

void StepKnights( GameData *pGameData )
{
    for( Knight *pKnightPlayer1 = pGameData->pFirstKnightPlayer1; pKnightPlayer1 != NULL; pKnightPlayer1 = pKnightPlayer1->pNextKnight )
    {
        if( _GetCanKnightMove( pGameData, pKnightPlayer1 ) )
        {
            pKnightPlayer1->iXPos += 1;

            if( pGameData->iTickCount % 2 == 0 ) // new state applies in every second tick
            {
                if( pKnightPlayer1->eState >= S7 )
                    pKnightPlayer1->eState = S0;
                else
                    pKnightPlayer1->eState += 1;
            }
        }
    }

    for( Knight *pKnightPlayer2 = pGameData->pFirstKnightPlayer2; pKnightPlayer2 != NULL; pKnightPlayer2 = pKnightPlayer2->pNextKnight )
    {
        if( _GetCanKnightMove( pGameData, pKnightPlayer2 ) )
        {
            pKnightPlayer2->iXPos -= 1;

            if( pGameData->iTickCount % 2 == 0 ) // new state applies in every second tick
            {
                if( pKnightPlayer2->eState >= S7 )
                    pKnightPlayer2->eState = S0;
                else
                    pKnightPlayer2->eState += 1;
            }
        }
    }
}

void FightKnights( GameData *pGameData )
{
    Knight *pKnightPlayer1 = pGameData->pFirstKnightPlayer1;
    Knight *pKnightPlayer2 = pGameData->pFirstKnightPlayer2;
    if( pKnightPlayer1 == NULL || pKnightPlayer2 == NULL )
        return;

    int iPosKnight1 = pKnightPlayer1->iXPos;
    int iPosKnight2 = pKnightPlayer2->iXPos;
    if( iPosKnight2 - iPosKnight1 > KNIGHT_ADJACENCY )
        return;

    // State change to imitate fighting
    if( pGameData->iTickCount % 3 == 0 )
    {
        if( pKnightPlayer1->eState == S0 && pKnightPlayer2->eState == S0 )
        {
            pKnightPlayer1->eState = S4;
            pKnightPlayer2->eState = S4;
        }
        else
        {
            pKnightPlayer1->eState = S0;
            pKnightPlayer2->eState = S0;
        }
    }

    int iDamageDoneByPlayer1 = rand() % ( pGameData->iKnightDamagePlayer1 * DAMAGE_MULTIPLIER );
    int iDamageDoneByPlayer2 = rand() % ( pGameData->iKnightDamagePlayer2 * DAMAGE_MULTIPLIER );

    pKnightPlayer1->iHp -= iDamageDoneByPlayer2;
    if( pKnightPlayer1->iHp <= 0 )
    {
        pGameData->pFirstKnightPlayer1 = pGameData->pFirstKnightPlayer1->pNextKnight;
        if( pGameData->pFirstKnightPlayer1 != NULL )
            pGameData->pFirstKnightPlayer1->pPrevKnight = NULL;
        free( pKnightPlayer1 );
    }

    pKnightPlayer2->iHp -= iDamageDoneByPlayer1;
    if( pKnightPlayer2->iHp <= 0 )
    {
        pGameData->pFirstKnightPlayer2 = pGameData->pFirstKnightPlayer2->pNextKnight;
        if( pGameData->pFirstKnightPlayer2 != NULL )
            pGameData->pFirstKnightPlayer2->pPrevKnight = NULL;
        free( pKnightPlayer2 );
    }
}

void AddKnight( GameData *pGameData, EPlayer ePlayer )
{
    Knight *pKnight;
    if( ePlayer == PLAYER_1 )
    {
        if( pGameData->iGoldPlayer1 < pGameData->iKnightPricePlayer1 )
            return;

        pKnight = pGameData->pFirstKnightPlayer1;
        pGameData->iGoldPlayer1        -= pGameData->iKnightPricePlayer1;
        pGameData->iKnightPricePlayer1  = ROUND_DOUBLE_TO_INT( pGameData->iKnightPricePlayer1 * KNIGHT_PRICE_MULTIPLIER );
    }
    else
    {
        if( pGameData->iGoldPlayer2 < pGameData->iKnightPricePlayer2 )
            return;

        pKnight = pGameData->pFirstKnightPlayer2;
        pGameData->iGoldPlayer2        -= pGameData->iKnightPricePlayer2;
        pGameData->iKnightPricePlayer2  = ROUND_DOUBLE_TO_INT( pGameData->iKnightPricePlayer2 * KNIGHT_PRICE_MULTIPLIER );
    }

    if( pKnight == NULL )
    {
        if( ePlayer == PLAYER_1 )
            pGameData->pFirstKnightPlayer1 = _CreateKnight( pGameData, ePlayer, NULL );
        else
            pGameData->pFirstKnightPlayer2 = _CreateKnight( pGameData, ePlayer, NULL );

        return;
    }

    while( pKnight->pNextKnight != NULL )
        pKnight = pKnight->pNextKnight;

    _CreateKnight( pGameData, ePlayer, pKnight );
}

void MoveCannonUp( GameData *pGameData, EPlayer ePlayer )
{
    if( ePlayer == PLAYER_1 )
        pGameData->dCannonAnglePlayer1 += CANNON_ANGLE_CHANGE;
    else
        pGameData->dCannonAnglePlayer2 -= CANNON_ANGLE_CHANGE;
}

void MoveCannonDown( GameData *pGameData, EPlayer ePlayer )
{
    if( ePlayer == PLAYER_1 )
        pGameData->dCannonAnglePlayer1 -= CANNON_ANGLE_CHANGE;
    else
        pGameData->dCannonAnglePlayer2 += CANNON_ANGLE_CHANGE;
}

void FireCannon( GameData *pGameData, EPlayer ePlayer )
{
    if( ePlayer == PLAYER_1 )
    {
        if( pGameData->cannonBallPlayer1.bValid == true )
            return; // Cannon ball is already flying

        if( pGameData->dLoadPercentPlayer1 < 1.0 )
            return;

        pGameData->dLoadPercentPlayer1 = 0.0;
        pGameData->cannonBallPlayer1.bValid         = true;
        pGameData->cannonBallPlayer1.vectorPos.dX   = CANNON_POSX_P1 + cos( pGameData->dCannonAnglePlayer1 ) * CANNON_LENGTH;
        pGameData->cannonBallPlayer1.vectorPos.dY   = CANNON_POSY - sin( pGameData->dCannonAnglePlayer1 ) * CANNON_LENGTH;
        pGameData->cannonBallPlayer1.vectorSpeed.dX =  cos( pGameData->dCannonAnglePlayer1 ) * CANNONBALL_INITIAL_SPEED;
        pGameData->cannonBallPlayer1.vectorSpeed.dY = -sin( pGameData->dCannonAnglePlayer1 ) * CANNONBALL_INITIAL_SPEED;
    }
    else
    {
        if( pGameData->cannonBallPlayer2.bValid == true )
            return; // Cannon ball is already flying

        if( pGameData->dLoadPercentPlayer2 < 1.0 )
            return;

        pGameData->dLoadPercentPlayer2 = 0.0;
        pGameData->cannonBallPlayer2.bValid         = true;
        pGameData->cannonBallPlayer2.vectorPos.dX   = CANNON_POSX_P2 + cos( pGameData->dCannonAnglePlayer2 ) * CANNON_LENGTH;
        pGameData->cannonBallPlayer2.vectorPos.dY   = CANNON_POSY - sin( pGameData->dCannonAnglePlayer2 ) * CANNON_LENGTH;
        pGameData->cannonBallPlayer2.vectorSpeed.dX =  cos( pGameData->dCannonAnglePlayer2 ) * CANNONBALL_INITIAL_SPEED;
        pGameData->cannonBallPlayer2.vectorSpeed.dY = -sin( pGameData->dCannonAnglePlayer2 ) * CANNONBALL_INITIAL_SPEED;
    }
}

void MoveCannonBall( GameData *pGameData )
{
    if( pGameData->cannonBallPlayer1.bValid == true )
    {
        if( pGameData->cannonBallPlayer1.vectorPos.dY > GROUND_POS_Y ) // Below ground
        {
            pGameData->cannonBallPlayer1.bValid = false;
        }
        else
        {
            pGameData->cannonBallPlayer1.vectorPos.dX   += pGameData->cannonBallPlayer1.vectorSpeed.dX;
            pGameData->cannonBallPlayer1.vectorPos.dY   += pGameData->cannonBallPlayer1.vectorSpeed.dY;
            pGameData->cannonBallPlayer1.vectorSpeed.dY += CANNONBALL_GRAVITY;
        }
    }

    if( pGameData->cannonBallPlayer2.bValid == true )
    {
        if( pGameData->cannonBallPlayer2.vectorPos.dY > GROUND_POS_Y ) // Below ground
        {
            pGameData->cannonBallPlayer2.bValid = false;
        }
        else
        {
            pGameData->cannonBallPlayer2.vectorPos.dX   += pGameData->cannonBallPlayer2.vectorSpeed.dX;
            pGameData->cannonBallPlayer2.vectorPos.dY   += pGameData->cannonBallPlayer2.vectorSpeed.dY;
            pGameData->cannonBallPlayer2.vectorSpeed.dY += CANNONBALL_GRAVITY;
        }
    }
}

void RegisterHit( GameData *pGameData )
{
    int iXPosCannonBall_1 = ROUND_DOUBLE_TO_INT( pGameData->cannonBallPlayer1.bValid ? pGameData->cannonBallPlayer1.vectorPos.dX : -1.0 );
    int iYPosCannonBall_1 = ROUND_DOUBLE_TO_INT( pGameData->cannonBallPlayer1.bValid ? pGameData->cannonBallPlayer1.vectorPos.dY : -1.0 );
    int iXPosCannonBall_2 = ROUND_DOUBLE_TO_INT( pGameData->cannonBallPlayer2.bValid ? pGameData->cannonBallPlayer2.vectorPos.dX : -1.0 );
    int iYPosCannonBall_2 = ROUND_DOUBLE_TO_INT( pGameData->cannonBallPlayer2.bValid ? pGameData->cannonBallPlayer2.vectorPos.dY : -1.0 );

    for( Knight *pKnightPlayer1 = pGameData->pFirstKnightPlayer1; pKnightPlayer1 != NULL; pKnightPlayer1 = pKnightPlayer1->pNextKnight )
    {
        if( _GetKnightHit( pKnightPlayer1, iXPosCannonBall_1, iYPosCannonBall_1 ) ||
            _GetKnightHit( pKnightPlayer1, iXPosCannonBall_2, iYPosCannonBall_2 ) )
        {
            if( pKnightPlayer1->pPrevKnight != NULL )
                pKnightPlayer1->pPrevKnight->pNextKnight = pKnightPlayer1->pNextKnight;

            if( pKnightPlayer1->pNextKnight != NULL )
                pKnightPlayer1->pNextKnight->pPrevKnight = pKnightPlayer1->pPrevKnight;

            if( pKnightPlayer1 == pGameData->pFirstKnightPlayer1 )
                pGameData->pFirstKnightPlayer1 = pKnightPlayer1->pNextKnight;

            free( pKnightPlayer1 );
        }
    }

    for( Knight *pKnightPlayer2 = pGameData->pFirstKnightPlayer2; pKnightPlayer2 != NULL; pKnightPlayer2 = pKnightPlayer2->pNextKnight )
    {
        if( _GetKnightHit( pKnightPlayer2, iXPosCannonBall_1, iYPosCannonBall_1 ) ||
            _GetKnightHit( pKnightPlayer2, iXPosCannonBall_2, iYPosCannonBall_2 ) )
        {
            if( pKnightPlayer2->pPrevKnight != NULL )
                pKnightPlayer2->pPrevKnight->pNextKnight = pKnightPlayer2->pNextKnight;

            if( pKnightPlayer2->pNextKnight != NULL )
                pKnightPlayer2->pNextKnight->pPrevKnight = pKnightPlayer2->pPrevKnight;

            if( pKnightPlayer2 == pGameData->pFirstKnightPlayer2 )
                pGameData->pFirstKnightPlayer2 = pKnightPlayer2->pNextKnight;

            free( pKnightPlayer2 );
        }
    }
}

void UpdateCannLoad( GameData *pGameData )
{
    pGameData->dLoadPercentPlayer1 += pGameData->iLoadTimePlayer1 * LOAD_MULTIPLIER;
    pGameData->dLoadPercentPlayer2 += pGameData->iLoadTimePlayer2 * LOAD_MULTIPLIER;

    if( pGameData->dLoadPercentPlayer1 > 1.0 )
        pGameData->dLoadPercentPlayer1 = 1.0;

    if( pGameData->dLoadPercentPlayer2 > 1.0 )
        pGameData->dLoadPercentPlayer2 = 1.0;
}

void CalculateIncome( GameData *pGameData )
{
    if( pGameData->iTickCount % 20 != 0 )
        return;

    pGameData->iGoldPlayer1 += pGameData->iEconomyPlayer1 * INCOME_MULTIPLIER;
    pGameData->iGoldPlayer2 += pGameData->iEconomyPlayer2 * INCOME_MULTIPLIER;
}

bool EvaluateWin( GameData *pGameData )
{
    bool bWonP1 = pGameData->pFirstKnightPlayer1 != NULL && pGameData->pFirstKnightPlayer1->iXPos >= KNIGHT_PATH_LENGHT;
    bool bWonP2 = pGameData->pFirstKnightPlayer2 != NULL && pGameData->pFirstKnightPlayer2->iXPos < 0;

    if( bWonP1 && bWonP2 )
        pGameData->ePlayerWon = PLAYER_BOTH;
    else if( bWonP1 )
        pGameData->ePlayerWon = PLAYER_1;
    else if( bWonP2 )
        pGameData->ePlayerWon = PLAYER_2;

    return bWonP1 || bWonP2;
}

int GetUpgradePrice( int iLevel )
{
    return pow( 2, iLevel - 1 ) * 100; // this makes upgrade prices exponentially increasing
}

void UpgradeEconomy( GameData *pGameData, EPlayer ePlayer )
{
    if( ePlayer == PLAYER_1 )
    {
        int iPrice = GetUpgradePrice( pGameData->iEconomyPlayer1 );
        if( pGameData->iGoldPlayer1 < iPrice )
            return;

        pGameData->iEconomyPlayer1 += 1;
        pGameData->iGoldPlayer1    -= iPrice;
    }
    else
    {
        int iPrice = GetUpgradePrice( pGameData->iEconomyPlayer2 );
        if( pGameData->iGoldPlayer2 < iPrice )
            return;

        pGameData->iEconomyPlayer2 += 1;
        pGameData->iGoldPlayer2    -= iPrice;
    }
}

void UpgradeLoad( GameData *pGameData, EPlayer ePlayer )
{
    if( ePlayer == PLAYER_1 )
    {
        int iPrice = GetUpgradePrice( pGameData->iLoadTimePlayer1 );
        if( pGameData->iGoldPlayer1 < iPrice )
            return;

        pGameData->iLoadTimePlayer1 += 1;
        pGameData->iGoldPlayer1     -= iPrice;
    }
    else
    {
        int iPrice = GetUpgradePrice( pGameData->iLoadTimePlayer2 );
        if( pGameData->iGoldPlayer2 < iPrice )
            return;

        pGameData->iLoadTimePlayer2 += 1;
        pGameData->iGoldPlayer2     -= iPrice;
    }
}

void UpgradeSpawnHP( GameData *pGameData, EPlayer ePlayer )
{
    if( ePlayer == PLAYER_1 )
    {
        int iPrice = GetUpgradePrice( pGameData->iKnightSpawningHpPlayer1 );
        if( pGameData->iGoldPlayer1 < iPrice )
            return;

        pGameData->iKnightSpawningHpPlayer1 += 1;
        pGameData->iGoldPlayer1             -= iPrice;
    }
    else
    {
        int iPrice = GetUpgradePrice( pGameData->iKnightSpawningHpPlayer2 );
        if( pGameData->iGoldPlayer2 < iPrice )
            return;

        pGameData->iKnightSpawningHpPlayer2 += 1;
        pGameData->iGoldPlayer2             -= iPrice;
    }
}

void UpgradeDamage( GameData *pGameData, EPlayer ePlayer )
{
    if( ePlayer == PLAYER_1 )
    {
        int iPrice = GetUpgradePrice( pGameData->iKnightDamagePlayer1 );
        if( pGameData->iGoldPlayer1 < iPrice )
            return;

        pGameData->iKnightDamagePlayer1 += 1;
        pGameData->iGoldPlayer1         -= iPrice;
    }
    else
    {
        int iPrice = GetUpgradePrice( pGameData->iKnightDamagePlayer2 );
        if( pGameData->iGoldPlayer2 < iPrice )
            return;

        pGameData->iKnightDamagePlayer2 += 1;
        pGameData->iGoldPlayer2         -= iPrice;
    }
}

bool _GetCanKnightMove( GameData *pGameData, Knight *pKnight )
{
    if( pKnight == NULL )
        return false;

    if( pKnight->ePlayer == PLAYER_1 )
    {
        if( pKnight == pGameData->pFirstKnightPlayer1 )
        {
            if( pGameData->pFirstKnightPlayer2 != NULL )
                if( pGameData->pFirstKnightPlayer2->iXPos - pGameData->pFirstKnightPlayer1->iXPos <= KNIGHT_ADJACENCY )
                    return false;
        }
        else if( pKnight->pPrevKnight != NULL )
        {
            if( pKnight->pPrevKnight->iXPos - pKnight->iXPos <= KNIGHT_ADJACENCY )
                return false;
        }
    }
    else
    {
        if( pKnight == pGameData->pFirstKnightPlayer2 )
        {
            if( pGameData->pFirstKnightPlayer1 != NULL )
                if( pGameData->pFirstKnightPlayer2->iXPos - pGameData->pFirstKnightPlayer1->iXPos <= KNIGHT_ADJACENCY )
                    return false;
        }
        else if( pKnight->pPrevKnight != NULL )
        {
            if( pKnight->iXPos - pKnight->pPrevKnight->iXPos <= KNIGHT_ADJACENCY )
                return false;
        }
    }

    return true;
}

Knight *_CreateKnight( GameData *pGameData, EPlayer ePlayer, Knight *pPrevKnight  )
{
    Knight *pKnightCreated = (Knight *)malloc( sizeof( Knight ) );
    if( pKnightCreated == NULL )
    {
        fprintf(stderr, "Can not allocate enough memory!\n");
        exit(1);
    }

    pKnightCreated->pPrevKnight = pPrevKnight;
    pKnightCreated->pNextKnight = NULL;
    pKnightCreated->ePlayer     = ePlayer;
    pKnightCreated->eState      = S4;

    if( pPrevKnight != NULL )
        pPrevKnight->pNextKnight = pKnightCreated;

    if( ePlayer == PLAYER_1 )
    {
        pKnightCreated->iXPos = 0;
        pKnightCreated->iHp   = pGameData->iKnightSpawningHpPlayer1 * SPAWN_HP_MULTIPLIER;
    }
    else
    {
        pKnightCreated->iXPos = KNIGHT_PATH_LENGHT - 1;
        pKnightCreated->iHp   = pGameData->iKnightSpawningHpPlayer2 * SPAWN_HP_MULTIPLIER;
    }

    return pKnightCreated;
}

bool _GetKnightHit( Knight *pKnight, int posXCannonBall, int posYCannonBall )
{
    if( posYCannonBall < KNIGHT_PATH_TOP )
        return false;

    if( posYCannonBall > GROUND_POS_Y )
        return false;

    if( posXCannonBall < pKnight->iXPos + KNIGHT_PATH_LEFT )
        return false;

    if( posXCannonBall > pKnight->iXPos + KNIGHT_PATH_LEFT + KNIGHT_WIDTH )
        return false;

    return true;
}

char* _GetLine( FILE *pFile )
{
    char *strLine = (char *)malloc( sizeof(char) * 50 );
    if( strLine == NULL )
    {
        fprintf(stderr, "Can not allocate enough memory!\n");
        exit(1);
    }

    int i = 0;
    char c = (char)fgetc( pFile );
    for( i = 0; i<49 && c != '\r' && c != '\n' && c != '\0' && c != EOF; ++i )
    {
        strLine[i] = c;
        c = (char)fgetc( pFile );
    }
    strLine[i+1] = '\0';

    return strLine;
}
