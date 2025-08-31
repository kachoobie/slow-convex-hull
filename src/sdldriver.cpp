#include <stdio.h>
#include "../include/sdldriver.h"

SDLDriver::SDLDriver(int width, int height, int size, const char *windowName)
{
    windowWidth = width;
    windowHeight = height;
    pixelSize = size;

    window = SDL_CreateWindow(windowName, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, NULL);
}

SDL_AppResult SDLDriver::drive()
{

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SlowConvexHull sch;

    SDL_Event event;
    bool running = true;
    while(running) {
        SDL_RenderClear(this->renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            } else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                float mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                sch.addPoint(mouseX, mouseY);
            } else if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.scancode == SDL_SCANCODE_SPACE) {
                    for (int i = 0; i < 10; ++i) {
                        std::random_device rd;
                        std::mt19937 gen(rd());
                        std::uniform_int_distribution<> distribWidth(100, windowWidth - 100);
                        std::uniform_int_distribution<> distribHeight(100, windowHeight - 100);
                        int randomXCoor = distribWidth(gen), randomYCoor = distribHeight(gen);
                        sch.addPoint(randomXCoor, randomYCoor);
                    }
                } else if (event.key.scancode == SDL_SCANCODE_C) {
                    sch.dump();
                } else if (event.key.scancode == SDL_SCANCODE_RETURN) {
                    std::cout << "Finding convex hull..." << std::endl;
                    sch.generateConvexHull();
                    std::vector<Segment> currentConvexHull = sch.convexHull;
                    std::cout << "Number of segments: " << currentConvexHull.size() << std::endl;
                    for (int i = 0; i < currentConvexHull.size(); ++i) {
                        std::cout << currentConvexHull.at(i).toString() << std::endl;
                    }
                } else if (event.key.scancode == SDL_SCANCODE_T) {
                    for (int i = 0; i < 1000; ++i) {
                        std::random_device rd;
                        std::mt19937 gen(rd());
                        std::uniform_int_distribution<> distribWidth(100, windowWidth - 100);
                        std::uniform_int_distribution<> distribHeight(100, windowHeight - 100);
                        int randomXCoor = distribWidth(gen), randomYCoor = distribHeight(gen);
                        sch.addPoint(randomXCoor, randomYCoor);
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        std::vector<Point>::iterator it;
        std::vector<Point> pointSet = sch.pointSet;
        for (it = pointSet.begin(); it != pointSet.end(); ++it) {
            Point currentPoint = *it;
            SDL_FRect vertex;
            vertex.x = currentPoint.x, vertex.y = currentPoint.y, vertex.w = pixelSize, vertex.h = pixelSize;
            if (!SDL_RenderFillRect(renderer, &vertex)) {
                SDL_Log("Could not draw rectangle: %s", SDL_GetError());
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        std::vector<Segment>::iterator segit;
        std::vector<Segment> convexHull = sch.convexHull;
        for (segit = convexHull.begin(); segit != convexHull.end(); ++segit) {
            Segment currentSegment = *segit;
            Point point1 = currentSegment.start;
            Point point2 = currentSegment.end;
            if (!SDL_RenderLine(renderer, point1.x, point1.y, point2.x, point2.y)) {
                SDL_Log("Could not draw line: %s", SDL_GetError());
            }
        }

        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    }

    SDL_Quit();
    return SDL_APP_CONTINUE;
}