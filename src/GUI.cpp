#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "battle.hpp"

#define BG_WIDTH 512
#define BG_HEIGHT 288
#define PB_WIDTH 512
#define PB_HEIGHT 64
#define PB_ERROR_W 127
#define PB_ERROR_H 17
#define EB_WIDTH 256
#define EB_HEIGHT 128
#define EB_ERROR 110
#define POKEMON_HEIGHT 160
#define POKEMON_WIDTH 160
#define POKEMON1_ERROR 50
#define POKEMON2_ERROR 50
#define BBOX_HEIGHT 50
#define BBOX_EDGE_WIDTH 40
#define BBOX_SPLIT_HEIGHT 34
#define BBOX1_WIDTH 208
#define BBOX1_ERROR_H 44
#define BBOX2_WIDTH 240
#define BBOX2_ERROR_H 38
#define TEXT_INDENT 5
#define HPBAR_WIDTH 100
#define HPBAR_HEIGHT 8
#define HPBAR_ERROR_W 98
#define HPBAR_ERROR_H 3
#define HPBAR_UPDATE_ERROR 2
#define HP_SPACING 5
#define MENU_HEIGHT 0

static constexpr SDL_Color black = {0, 0, 0, SDL_ALPHA_OPAQUE};
static constexpr SDL_Color white = {255, 255, 255, SDL_ALPHA_OPAQUE};

using namespace std;
int main()
{
    Battle b("trainer1.txt", "trainer2.txt");

    TTF_Init();
    TTF_Font* pkem = TTF_OpenFont("fonts/pkmnem.ttf", 27);
    TTF_Font* bold = TTF_OpenFont("fonts/pkmndpb.ttf", 15);

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* w = SDL_CreateWindow("Bois", 100, 100, BG_WIDTH, BG_HEIGHT + MENU_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* s_bg = IMG_Load("img/bg1.png");
    SDL_Surface* s_pb = IMG_Load("img/pbase1.png");
    SDL_Surface* s_eb = IMG_Load("img/ebase1.png");
    SDL_Texture* bg = SDL_CreateTextureFromSurface(renderer, s_bg);
    SDL_Texture* pb = SDL_CreateTextureFromSurface(renderer, s_pb);
    SDL_Texture* eb = SDL_CreateTextureFromSurface(renderer, s_eb);
    SDL_FreeSurface(s_bg);
    SDL_FreeSurface(s_pb);
    SDL_FreeSurface(s_eb);

    SDL_Surface* s_p1 = IMG_Load(b.active_pkmn_img(0).c_str());
    SDL_Surface* s_p2 = IMG_Load(b.active_pkmn_img(1).c_str());
    SDL_Texture* p1 = SDL_CreateTextureFromSurface(renderer, s_p1);
    SDL_Texture* p2 = SDL_CreateTextureFromSurface(renderer, s_p2);
    SDL_FreeSurface(s_p1);
    SDL_FreeSurface(s_p2);

    SDL_Surface* s_bbox = IMG_Load("img/battlebox.png");
    SDL_Surface* s_bbox1_edge = IMG_Load("img/bbox1_edge.png");
    SDL_Surface* s_bbox2_edge = IMG_Load("img/bbox2_edge.png");
    SDL_Texture* bbox = SDL_CreateTextureFromSurface(renderer, s_bbox);
    SDL_Texture* bbox1_edge = SDL_CreateTextureFromSurface(renderer, s_bbox1_edge);
    SDL_Texture* bbox2_edge = SDL_CreateTextureFromSurface(renderer, s_bbox2_edge);
    SDL_FreeSurface(s_bbox);
    SDL_FreeSurface(s_bbox1_edge);
    SDL_FreeSurface(s_bbox2_edge);

    string p1name = b.active_pkmn_name(0), p2name = b.active_pkmn_name(1);
    SDL_Surface* s_p1_text = TTF_RenderUTF8_Solid(pkem, p1name.c_str(), black);
    SDL_Surface* s_p2_text = TTF_RenderUTF8_Solid(pkem, p2name.c_str(), black);
    SDL_Texture* p1_text = SDL_CreateTextureFromSurface(renderer, s_p1_text);
    SDL_Texture* p2_text = SDL_CreateTextureFromSurface(renderer, s_p2_text);
    SDL_FreeSurface(s_p1_text);
    SDL_FreeSurface(s_p2_text);

    SDL_Surface* s_hp = TTF_RenderUTF8_Solid(bold, "HP", white);
    SDL_Surface* s_hpbar = IMG_Load("img/hpbar.png");
    SDL_Texture* hp = SDL_CreateTextureFromSurface(renderer, s_hp);
    SDL_Texture* hpbar = SDL_CreateTextureFromSurface(renderer, s_hpbar);
    SDL_FreeSurface(s_hp);
    SDL_FreeSurface(s_hpbar);
    
    bool open = true;
    while(open)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                open = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_Rect bgRect = {0, 0, BG_WIDTH, BG_HEIGHT};
        SDL_Rect pbRect = {0, BG_HEIGHT - PB_HEIGHT + PB_ERROR_H, PB_WIDTH - PB_ERROR_W, PB_HEIGHT - PB_ERROR_H};
        SDL_Rect pbError = {PB_ERROR_W, 0, PB_WIDTH, pbRect.h};
        SDL_Rect ebRect = {BG_WIDTH - EB_WIDTH, EB_ERROR, EB_WIDTH, EB_HEIGHT};
        SDL_RenderCopy(renderer, bg, NULL, &bgRect);
        SDL_RenderCopy(renderer, pb, &pbError, &pbRect);
        SDL_RenderCopy(renderer, eb, NULL, &ebRect);

        SDL_Rect p1Rect = {POKEMON1_ERROR, BG_HEIGHT - POKEMON_HEIGHT, POKEMON_WIDTH, POKEMON_HEIGHT};
        SDL_Rect p2Rect = {BG_WIDTH / 2 + EB_WIDTH / 2 - POKEMON_WIDTH/2, POKEMON2_ERROR, POKEMON_WIDTH, POKEMON_HEIGHT};
        SDL_RenderCopy(renderer, p1, NULL, &p1Rect);
        SDL_RenderCopy(renderer, p2, NULL, &p2Rect);

        SDL_Rect bbox1Rect = {BG_WIDTH - BBOX1_WIDTH, EB_HEIGHT + EB_ERROR - BBOX1_ERROR_H, BBOX1_WIDTH, BBOX_HEIGHT};
        SDL_RenderCopy(renderer, bbox, NULL, &bbox1Rect);
        SDL_Rect bbox1_edgeRect = {bbox1Rect.x - BBOX_EDGE_WIDTH, bbox1Rect.y, BBOX_EDGE_WIDTH, BBOX_HEIGHT};
        SDL_RenderCopy(renderer, bbox1_edge, NULL, &bbox1_edgeRect);
        SDL_Rect bbox2Rect = {0, BBOX2_ERROR_H, BBOX2_WIDTH, BBOX_HEIGHT};
        SDL_RenderCopy(renderer, bbox, NULL, &bbox2Rect);
        SDL_Rect bbox2_edgeRect = {BBOX2_WIDTH, bbox2Rect.y, BBOX_EDGE_WIDTH, BBOX_HEIGHT};
        SDL_RenderCopy(renderer, bbox2_edge, NULL, &bbox2_edgeRect);

        int text_w, text_h;
        TTF_SizeText(pkem, p1name.c_str(), &text_w, &text_h);
        SDL_Rect p1_textRect = {bbox1Rect.x + TEXT_INDENT, bbox1Rect.y + TEXT_INDENT, text_w, text_h};
        TTF_SizeText(pkem, p2name.c_str(), &text_w, &text_h);
        SDL_Rect p2_textRect = {bbox2Rect.x + TEXT_INDENT, bbox2Rect.y + TEXT_INDENT, text_w, text_h};
        SDL_RenderCopy(renderer, p1_text, NULL, &p1_textRect);
        SDL_RenderCopy(renderer, p2_text, NULL, &p2_textRect);

        SDL_Rect hpbar1Rect = {bbox1Rect.x + HPBAR_ERROR_W, bbox1Rect.y + BBOX_SPLIT_HEIGHT + HPBAR_ERROR_H, HPBAR_WIDTH, HPBAR_HEIGHT};
        SDL_RenderCopy(renderer, hpbar, NULL, &hpbar1Rect);
        SDL_Rect hpbar2Rect = {bbox2Rect.x + HPBAR_ERROR_W, bbox2Rect.y + BBOX_SPLIT_HEIGHT + HPBAR_ERROR_H, HPBAR_WIDTH, HPBAR_HEIGHT};
        SDL_RenderCopy(renderer, hpbar, NULL, &hpbar2Rect);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        if(b.active_pkmn_hp_percent(0) != 0)
        {
            SDL_Rect hpbar1RectX = {hpbar1Rect.x + HPBAR_UPDATE_ERROR, hpbar1Rect.y + HPBAR_UPDATE_ERROR, ((hpbar1Rect.w - 2 * HPBAR_UPDATE_ERROR) * b.active_pkmn_hp_percent(0)) / 100, hpbar1Rect.h - 2 * HPBAR_UPDATE_ERROR};
            SDL_RenderFillRect(renderer, &hpbar1RectX);
            SDL_RenderDrawRect(renderer, &hpbar1RectX);
        }
        if(b.active_pkmn_hp_percent(1) != 0)
        {
            SDL_Rect hpbar2RectX = {hpbar2Rect.x + HPBAR_UPDATE_ERROR, hpbar2Rect.y + HPBAR_UPDATE_ERROR, ((hpbar2Rect.w - 2 * HPBAR_UPDATE_ERROR) * b.active_pkmn_hp_percent(1)) / 100, hpbar2Rect.h - 2 * HPBAR_UPDATE_ERROR};
            SDL_RenderFillRect(renderer, &hpbar2RectX);
            SDL_RenderDrawRect(renderer, &hpbar2RectX);
        }
        TTF_SizeText(bold, "HP", &text_w, &text_h);
        SDL_Rect hp1Rect = {hpbar1Rect.x - text_w - HP_SPACING, hpbar1Rect.y - HP_SPACING, text_w, text_h};
        SDL_RenderCopy(renderer, hp, NULL, &hp1Rect);
        SDL_Rect hp2Rect = {hpbar2Rect.x - text_w - HP_SPACING, hpbar2Rect.y - HP_SPACING, text_w, text_h};
        SDL_RenderCopy(renderer, hp, NULL, &hp2Rect);

        SDL_RenderPresent(renderer);

        b.take_commands();

        if(p1name != b.active_pkmn_name(0))
        {
            p1name = b.active_pkmn_name(0);
            SDL_Surface* s_p1_text = TTF_RenderUTF8_Solid(pkem, p1name.c_str(), black);
            p1_text = SDL_CreateTextureFromSurface(renderer, s_p1_text);
            SDL_FreeSurface(s_p1_text);
            SDL_Surface* s_p1 = IMG_Load(b.active_pkmn_img(0).c_str());
            p1 = SDL_CreateTextureFromSurface(renderer, s_p1);
            SDL_FreeSurface(s_p1);
        }
        if(p2name != b.active_pkmn_name(1))
        {
            p2name = b.active_pkmn_name(1);
            SDL_Surface* s_p2_text = TTF_RenderUTF8_Solid(pkem, p2name.c_str(), black);
            p2_text = SDL_CreateTextureFromSurface(renderer, s_p2_text);
            SDL_FreeSurface(s_p2_text);
            SDL_Surface* s_p2 = IMG_Load(b.active_pkmn_img(1).c_str());
            p2 = SDL_CreateTextureFromSurface(renderer, s_p2);
            SDL_FreeSurface(s_p2);
        }
    }

    SDL_DestroyTexture(hp);
    SDL_DestroyTexture(hpbar);

    SDL_DestroyTexture(p2_text);
    SDL_DestroyTexture(p1_text);

    SDL_DestroyTexture(bbox2_edge);
    SDL_DestroyTexture(bbox1_edge);
    SDL_DestroyTexture(bbox);

    SDL_DestroyTexture(p2);
    SDL_DestroyTexture(p1);

    SDL_DestroyTexture(eb);
    SDL_DestroyTexture(pb);
    SDL_DestroyTexture(bg);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(w);
    SDL_Quit();

    TTF_CloseFont(pkem);
    TTF_Quit();
}