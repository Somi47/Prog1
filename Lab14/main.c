#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct vector{
    int sor, oszlop;
} vector;

typedef enum{
    FEL,
    LE,
    JOBB,
    BAL
} EIrany;

void Kirajzol( char labirintus[][11] )
{
    for( int i=0; i<10; ++i )
        printf( "%s\n", labirintus[i] );
}

void KeresJatekos( vector *jatekoshely, char labirintus[][11] )
{
    for( int i=0; i<10; ++i )
        for( int j=0; j<10; ++j )
            if( labirintus[i][j] == '@' )
            {
                jatekoshely->sor = i;
                jatekoshely->oszlop = j;
                return;
            }

    jatekoshely->sor = 0;
    jatekoshely->oszlop = 0;
}

int KincsekSzama( char labirintus[][11] )
{
    int db = 0;
    for( int i=0; i<10; ++i )
        for( int j=0; j<10; ++j )
            if( labirintus[i][j] == '$' )
                ++db;

    return db;
}

bool MehetArra( EIrany eIrany, vector *jatekoshely, char labirintus[][11] )
{
    switch( eIrany )
    {
        case FEL:  if( labirintus[jatekoshely->sor - 1][jatekoshely->oszlop    ] != '#' ) return true;
        case LE:   if( labirintus[jatekoshely->sor + 1][jatekoshely->oszlop    ] != '#' ) return true;
        case JOBB: if( labirintus[jatekoshely->sor    ][jatekoshely->oszlop + 1] != '#' ) return true;
        case BAL:  if( labirintus[jatekoshely->sor    ][jatekoshely->oszlop - 1] != '#' ) return true;
    }

    return false;
}

int Kijut( int sor, int oszlop, char labirintus[][11], bool jartitt[][10] )
{
    if( jartitt[sor][oszlop] )
        return false;

    if( labirintus[sor][oszlop] == '#' )
        return false;

    jartitt[sor][oszlop] = lepseszam;

    if( sor == 0 || oszlop == 0 || sor == 9 || oszlop == 9 ) //kijarat beégetve
        return true;

    return Kijuthat( sor + 1, oszlop,     labirintus, jartitt, lepseszam + 1) ||
           Kijuthat( sor - 1, oszlop,     labirintus, jartitt, lepseszam + 1) ||
           Kijuthat( sor,     oszlop + 1, labirintus, jartitt, lepseszam + 1) ||
           Kijuthat( sor,     oszlop - 1, labirintus, jartitt, lepseszam + 1);
}

int main()
{
    vector jatekoshely;
    char labirintus[10][11] = { "###### ###",
                                "#$   #   #",
                                "#### ### #",
                                "#        #",
                                "# #### ###",
                                "# #    #$#",
                                "# ##$# # #",
                                "#@ ### # #",
                                "#   $#   #",
                                "##########" };


    Kirajzol( labirintus );
    KeresJatekos( &jatekoshely, labirintus );

    printf( "Pos: %d:%d\n", jatekoshely.sor, jatekoshely.oszlop );
    printf( "Kincsek szama: %d\n", KincsekSzama( labirintus ) );

    if( MehetArra( BAL, &jatekoshely, labirintus ) )
        printf( "Mehet balra\n" );
    else
        printf( "Nem mehet balra\n" );

    if( MehetArra( FEL, &jatekoshely, labirintus ) )
        printf( "Mehet fel\n" );
    else
        printf( "Nem mehet fel\n" );

    int jartitt[10][10];
    for( int i=0; i<10; ++i )
        for( int j=0; j<10; ++j )
            jartitt[i][j] = -1;

    if( Kijuthat( jatekoshely.sor, jatekoshely.oszlop, labirintus, jartitt, 0 ) )
        printf( "Kijuthat" );
    else
        printf( "Nem juthat ki" );

    return 0;
}
