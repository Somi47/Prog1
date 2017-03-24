#include <stdio.h>
#include <math.h>
#include <stdbool.h>

double f2_kob( double x )
{
    return x*x*x;
}

double f2_abszolut( double x )
{
    return x > 0 ? x : -x;
}

void f2()
{
    double x;
    scanf( "%lf", &x );

    for( int i = -10; i < 10; ++i )
    {
        double szam = x + i * 0.1;
        printf( "%f, %f, %f, %f\n", szam, f2_kob( szam ), f2_abszolut( szam ), sin( szam ) );
    }
}

void f3()
{
    char c;
    while (scanf("%c", &c) != EOF)
    {
        char c2 = c >= 'A' && c <= 'Z' ? c - 'A' + 'a' : c;
        if (c2=='a' || c2=='e' || c2=='i' || c2=='o' || c2=='u')
            printf("%cv%c", c, c2);
        else
            printf("%c", c);
    }
}
typedef struct Datum {
    int ev, ho, nap;
} Datum;

typedef struct Versenyzo {
    char nev[31];
    Datum szuletes;
    int helyezes;
} Versenyzo;

void datum_kiir(Datum d) {
    printf("%d.%d.%d.", d.ev, d.ho, d.nap);
}

void versenyzo_kiir(Versenyzo v) {
    /* a versenyző összes adatának kiírása */
    printf( "%s\t", v.nev );
    datum_kiir( v.szuletes );
    printf( "\t%d\n", v.helyezes );
}

void f4()
{
    Versenyzo versenyzok[5] = {
        { "Am Erika", {1984, 5, 6}, 1 },
        { "Break Elek", {1982, 9, 30}, 3 },
        { "Dil Emma", {1988, 8, 25}, 2 },
        { "Kasza Blanka", {1979, 6, 10}, 5 },
        { "Reset Elek", {1992, 4, 5}, 4 },
    };

    /* 0-s versenyző neve - printf %s */
    printf( "%s\n", versenyzok[0].nev );
    /* 2-es versenyző helyezése */
    printf( "%d\n", versenyzok[0].helyezes );
    /* 4-es versenyző születési dátumát a megadott függvénnyel */
    datum_kiir( versenyzok[0].szuletes );
    printf("\n");
    /* 1-es versenyző nevének kezdőbetűjét (ne feledd, a sztring karaktertömb) */
    printf( "%c\n", versenyzok[1].nev[0]);
    /* az 1-es versenyző dobogós-e? igen/nem, akár ?: operátorral */
    versenyzok[1].helyezes < 4 ? printf( "igen\n" ) : printf( "nem\n" );
    /* az 4-es versenyző gyorsabb-e, mint a 3-as versenyző? */
    versenyzok[4].helyezes < versenyzok[3].helyezes ? printf( "igen\n" ) : printf( "nem\n" );
    /* az 1-es versenyző ugyanabban az évben született-e, mint a 2-es? */
    versenyzok[1].szuletes.ev == versenyzok[2].szuletes.ev ? printf( "igen\n" ) : printf( "nem\n" );
    /* egészítsd ki a versenyzo_kiir() függvényt,
     * aztán írd ki az 1-es versenyző összes adatát */
    versenyzo_kiir( versenyzok[1] );
    /* végül listázd ki az összes versenyzőt sorszámozva. */
    for(int i = 0; i < 5; ++i)
    {
        printf( "%d: ", i );
        versenyzo_kiir( versenyzok[i] );
    }
}

int f5_alap()
{
    return 1;
}

int f5_hozzaad1( int a )
{
    return a + 1;
}

int f5_elojelfordit( int a )
{
    return -a;
}

int f5_szoroz2( int a )
{
    return a*2;
}

void f5()
{
    printf("0. Alapertek visszaallitasa (a = 1)\n"
       "1. Hozzaad 1-et\n"
       "2. Megforditja az elojelet\n"
       "3. Szorozza 2-vel\n"
       "9. Kilepes\n");

    int a = f5_alap();
    char c;
    do
    {
        scanf("%c", &c);

        switch(c)
        {
        case '0': printf( "a = %d\n", a = f5_alap() );
            break;
        case '1': printf( "a = %d\n", a = f5_hozzaad1( a ) );
            break;
        case '2': printf( "a = %d\n", a = f5_elojelfordit( a ) );
            break;
        case '3': printf( "a = %d\n", a = f5_szoroz2( a ) );
            break;
        case '\n':
        case '9' : /*Nothing, just not default*/
            break;
        default: printf( "Input error -> do nothing\n" );
        }
    }while( c!='9' );
}

typedef struct {
    int x;
    int y;
}Pont;

double Tav( Pont pont1, Pont pont2 )
{
    return sqrt( (pont1.x - pont2.x) * (pont1.x - pont2.x) + (pont1.y - pont2.y) * (pont1.y - pont2.y) );
}

bool Egybeesik( Pont pont1, Pont pont2 )
{
    return pont1.x == pont2.x && pont1.y == pont2.y;
}

Pont beolv()
{
    Pont pont;
    int x, y;
    scanf( "%d %d", &x, &y );
    pont.x = x;
    pont.y = y;
    return pont;
}

void f6()
{
    Pont pont1 = { 3, 2 };
    Pont pont2 = { 5, 2 };

    printf( "%f", Tav( pont1, pont2 ) );
}

int main()
{
    //f2();
    //f3();
    //f4();
    //f5();
    f6();

    return 0;
}
