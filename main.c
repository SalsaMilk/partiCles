#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"

#include "vector.h"

#define BYTE unsigned char
#define RANDRANGE(from, to) rand()%(to-from)+from
#define P particles[i]

#define PI 3.14159265

#define WIDTH 400
#define HEIGHT 300
#define COUNT 500
#define GRID_SIZE 20 // Size of a grid square for computations
#define G 15 // Universal gravitational constant for this simulation

SDL_Point GetLocalCursorPos(SDL_Window* window) {
    POINT cursorPos;
    GetCursorPos(&cursorPos);

    SDL_Point windowPos;
    SDL_GetWindowPosition(window, &windowPos.x, &windowPos.y);

    SDL_Point ret = {cursorPos.x-windowPos.x, cursorPos.y-windowPos.y};
    return ret;
}

typedef struct {
    Vector pos, velocity;
} Particle;

int main(int argc, char* argv[]) {
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        fprintf(stderr, "Error initializing SDL");
        return -1;
    }

    SDL_Window* window;
    SDL_Renderer* ren;

    window = SDL_CreateWindow("partiCles",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WIDTH, HEIGHT, 0);

    ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

    Particle particles[COUNT];
    for (int i = 0; i < COUNT; i++) {
        Particle particle = {RANDRANGE(5, WIDTH), RANDRANGE(5, HEIGHT), {rand()%4-1.5f, rand()%4-1.5f}};
        particles[i] = particle;
    }

    Vector blackHole = {WIDTH/2.f, HEIGHT/2.f};
    BYTE running = 1;
    while(running) {
        SDL_Event event;

        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_Point cursorPos = GetLocalCursorPos(window);
                    blackHole.x = cursorPos.x;
                    blackHole.y = cursorPos.y;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_ESCAPE:
                            running = 0;
                            break;
                        default: break;
                    }
            }
        }

        SDL_SetRenderDrawColor(ren, 13, 9, 9, 255);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
        for(int i = 0; i < COUNT; i++) {
            Vector v1 = {blackHole.x - P.pos.x, blackHole.y - P.pos.y};
            Vector v2 = vec_normalize(v1);

            float distance = vec_length(v1);
            float magnitude = G/(fabsf(distance) < 15.f ? 15.f : distance);
            Vector a = {v2.x*magnitude, v2.y*magnitude};

            P.velocity.x += a.x;
            P.velocity.y += a.y;

            P.pos.x += P.velocity.x;
            P.pos.y += P.velocity.y;

            if (P.pos.x < 0 || P.pos.x > 400)
                P.velocity.x = -P.velocity.x;
            if (P.pos.y < 0 || P.pos.y > 300)
                P.velocity.y = -P.velocity.y;

            SDL_RenderDrawPointF(ren, P.pos.x, P.pos.y);
        }

        {
            SDL_SetRenderDrawColor(ren, 255, 255, 255, 100);
            SDL_Rect focus = {particles[0].pos.x - 2, particles[0].pos.y - 2, 5, 5};
            SDL_RenderDrawRect(ren, &focus);

            SDL_SetRenderDrawColor(ren, 255, 0, 0, 100);
            SDL_RenderDrawLineF(ren, blackHole.x, blackHole.y,
                                particles[0].pos.x, particles[0].pos.y);

            aacircleColor(ren, blackHole.x, blackHole.y, 2, 0x64f22fff);
            aacircleColor(ren, particles[0].pos.x, particles[0].pos.y, 2, 0x64ffffff);
        }

        printf("Speed: %.1f | Distance: %.1f\r", vec_length(particles[0].velocity),
                                               distance(particles[0].pos, blackHole));

        SDL_RenderPresent(ren);
        SDL_Delay(30);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    return 0;
}
