#include <stdio.h>
#include <stdlib.h>

#include "SDL/SDL.h"

#include "vector.h"

#define BYTE unsigned char
#define RANDRANGE(from, to) rand()%(to-from)+from
#define P particles[i]

#define WIDTH 400
#define HEIGHT 300
#define COUNT 200
#define GRID_SIZE 20
#define G 12 // Universal gravitational constant for this simulation

typedef struct {
    float posX, posY;
    Vector velocity;
} Particle;

int main(int argc, char* argv[]) {
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
        Particle particle = {RANDRANGE(5, WIDTH), RANDRANGE(5, HEIGHT), {rand()%6-3, rand()%6-3}};
        particles[i] = particle;
    }

    BYTE running = 1;
    while(running) {
        SDL_Event event;

        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
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
            Vector blackHole = {WIDTH/2.f, HEIGHT/2.f};

            Vector v1 = {blackHole.x - P.posX, blackHole.y - P.posY};
            Vector v2 = vec_normalize(v1);

            float distance = vec_length(v1);
            float magnitude = 1/(fabsf(distance) < .1f ? .1f : distance) * G;
            Vector a = {v2.x*magnitude, v2.y*magnitude};

            P.velocity.x += a.x;
            P.velocity.y += a.y;

            P.posX += P.velocity.x;
            P.posY += P.velocity.y;

            SDL_RenderDrawPointF(ren, particles[i].posX, particles[i].posY);
        }

        SDL_RenderPresent(ren);
        SDL_Delay(50);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    return 0;
}
