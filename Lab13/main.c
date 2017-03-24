#include <stdio.h>

int main(void) {
    typedef enum LyAllapot {
        alap, l_volt, ll_volt
    } LyAllapot;

    char ujszoveg[1000];
    int  iNewPos = 0;
    LyAllapot all = alap;
    int c;
    while ((c=getchar()) != EOF) {
        switch (all) {
            case alap:
                if (c == 'l') all = l_volt;
                else ujszoveg[iNewPos++] = c;
                break;

        case l_volt:
            switch (c) {
                case 'l': all = ll_volt; break;
                case 'y': ujszoveg[iNewPos++] = 'j'; all = alap; break;
                default:  ujszoveg[iNewPos++] = 'l'; ujszoveg[iNewPos++] = c; all = alap; break;
            }
            break;

        case ll_volt:
            switch (c) {
                case 'l': ujszoveg[iNewPos++] = 'l'; break;
                case 'y': ujszoveg[iNewPos++] = 'j'; ujszoveg[iNewPos++] = 'j'; all = alap; break;
                default:  ujszoveg[iNewPos++] = 'l'; ujszoveg[iNewPos++] = 'l'; ujszoveg[iNewPos++] = c; all = alap; break;
            }
            break;
        }
    }

    printf( ujszoveg );

    return 0;
}
