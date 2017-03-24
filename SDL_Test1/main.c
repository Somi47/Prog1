#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    SDL_Event event;
    SDL_Surface *screen;

    /* SDL inicializálása és ablak megnyitása */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    screen = SDL_SetVideoMode(360, 360, 0, SDL_ANYFORMAT);
    if (!screen) {
        fprintf(stderr, "Nem sikerult megnyitni az ablakot!\n");
        exit(1);
    }
    SDL_WM_SetCaption("SDL esemenyek", "SDL esemenyek");

    /* az esemenyvezerelt hurok */
    bool quit = false;
    bool click = false;
    int elozox = 0;
    int elozoy = 0;
    while (!quit) {
        SDL_WaitEvent(&event);

        bool rajzoltam = false;

        switch (event.type) {
            /* eger kattintas */
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    click = true;
                    elozox = event.button.x;
                    elozoy = event.button.y;
                }
                else if (event.button.button == SDL_BUTTON_RIGHT) {
                    boxColor(screen, 0, 0, 359, 359, 0x000000FF);
                    rajzoltam = true;
                }
                break;
            /* egergomb elengedese */
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    click = false;
                }
                break;
            /* eger mozdulat */
            case SDL_MOUSEMOTION:
                if (click) {
                    aalineColor(screen, elozox, elozoy,
                                event.motion.x, event.motion.y, 0xFFFFFFFF);
                    rajzoltam = true;
                }
                /* a kovetkezo mozdulat esemenyhez */
                elozox = event.motion.x;
                elozoy = event.motion.y;
                break;
            case SDL_KEYDOWN :
                if( event.key.keysym.sym == SDLK_x )
                {
                    boxColor(screen, 0, 0, 359, 359, 0x000000FF);
                    rajzoltam = true;
                }

                break;
            /* ablak bezarasa */
            case SDL_QUIT:
                quit = true;
                break;
        }

        if (rajzoltam)
            SDL_Flip(screen);
    }

    SDL_Quit();

    return 0;
}
