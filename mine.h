/************************

Mine Sweeper sample

2000/6/4,by adas

************************/
#include "SDL.h"

#include "CBmps.h"
#include "CTime.h"
#include "Cffont.h"

#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************
global variables
***************/
#define MAX_X 40
#define MAX_Y 25
#define BOMB_RATIO 0.15
#define TILE_X	16
#define TILE_Y	16

/*

stage array area is [1..MAX_X][1..MAX_Y]
*/
typedef struct{
	int isOpen;
	int bomb;//0ならまわりに爆弾無し。100以上なら爆弾そのもの。それ以外はまわりにある爆弾の数
}Cstage;

Cstage stage[MAX_X+2][MAX_Y+2];


#define MSSTG_NONE	0
#define MSSTG_BOMB	100

int stage_size_x,stage_size_y;//ゲームサイズ
int stage_area_x,stage_area_y;//ゲームエリアの左隅座標
int real_bombs;
int real_left;//開けるべき残りパネル数

//result score
Uint32 longest_thinking;
Uint32 shortest_thinking;
Uint32 average_thinking;
Uint32 total_thinking;

Uint32 n_trial=1;

#define GAME_OVER	100
#define GAME_CLEAR	101
#define GAME_LOOP	1
#define GAME_NONE	0
#define GAME_QUIT	2
#define GAME_RESTART	3
#define GAME_RESULT	4
#define GAME_CONFIG	5
int game_state;


//regulation set
typedef struct{
	int x;
	int y;
}txyset;

txyset xyset[]={
	{8,8},
	{12,12},
	{18,12},
	{20,15},
};

int index_xyset=0;

double ratio[]={
	0.15,
	0.18,
	0.21,
	0.24,
};

int index_ratio=0;

//graphics
#define GRAPHIC_MAX 100
CBmps *bmps;
SDL_Surface *screen;
Cffont *font;
CTime gametime;

typedef struct{
	
	int x;
	int y;
	SDL_Surface *bmp;
	int clock;
	
}CTileScroll;

CTileScroll tscroll;


/***************
function prototype declaration
***************/
void set_stage(int,int);
void reveal(int,int);
void drawTiles(void);
int prepare(void);
void finalize(void);
int gameloop(void);
int readkeys(void);
int buttoncheck(int,int);
void drawback(void);
void drawTime(void);
void drawMenu(void);
void Menuclickcheck(int ,int);
int RectIn(SDL_Rect*,int,int);
void gamestate_handling(void);
void openAll(void);
void drawResult(void);
void drawTilescroll(void);
void moveTilescroll(void);
void drawConfig(void);
void Configclickcheck(int,int);
