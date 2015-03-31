/************************

マインスイーパー
サンプルプログラム

2000/6/4,by adas

************************/
#include "mine.h"
main(int argc,char **argv){
	
	prepare();
	set_stage(20,15);
	gameloop();
	finalize();
	return(0);
	
}

void drawConfig(void){
	
	
	CBmpsBlit(bmps,screen,50,320-256,50);
	CBmpsBlit(bmps,screen,30,320-256,200);
	CBmpsBlit(bmps,screen,40,320-256,300);
	CBmpsBlit(bmps,screen,31+index_ratio,320,200);
	CBmpsBlit(bmps,screen,41+index_xyset,320,300);
	
}
void Configclickcheck(int x,int y){
	
	SDL_Rect w;
	
	int n_index_ratio=sizeof(ratio)/sizeof(ratio[0]);
	int n_index_xyset=sizeof(xyset)/sizeof(xyset[0]);
	
	w.x=320-256;
	w.y=200;
	w.w=512;
	w.h=50;
	
	if(RectIn(&w,x,y)){
		index_ratio++;
		if(index_ratio==n_index_ratio)index_ratio=0;
	}
	
	w.y=300;
	
	if(RectIn(&w,x,y)){
		index_xyset++;
		if(index_xyset==n_index_xyset)index_xyset=0;
	}
	
}

void moveTilescroll(void){
	
	CTileScroll *p;
	int interval=66;//milisec
	p=&tscroll;
	
	if(p->clock+interval<gametime.clock){
		p->x--;
		if(p->x<=-(p->bmp->w))p->x=0;
		p->y--;
		if(p->y<=-(p->bmp->h))p->y=0;
		
		p->clock=gametime.clock;
	}else{
		if(p->clock>gametime.clock+interval*5)p->clock=gametime.clock;
	}
	
}
void drawTilescroll(void){
	
	int x,y;
	
	for(y=tscroll.y;y<screen->h;y+=tscroll.bmp->h){
		for(x=tscroll.x;x<screen->w;x+=tscroll.bmp->w){
		
			CBmpsBlit(bmps,screen,21,x,y);
		}
	}
	
}

void drawResult(void){
	static char buf[2048];
	
	int x=400;
	int y=0;
	
	CffontBlitxy(font,"-Result of this game-",screen,x+0,y);
	
	sprintf(buf,"Trial times  %4d",n_trial);
	CffontBlitxy(font,buf,screen,x+0,y+32);
	sprintf(buf,"Size    %2d x %2d",stage_size_x,stage_size_y);
	CffontBlitxy(font,buf,screen,x+0,y+48);
	sprintf(buf,"Bomb Ratio %2.0f%%",ratio[index_ratio]*100);
	CffontBlitxy(font,buf,screen,x+0,y+64);
	
	sprintf(buf,"Total time : %4d.%02d",total_thinking/1000,(total_thinking%1000)/10);
	CffontBlitxy(font,buf,screen,x+0,y+80);
	
}

void openAll(void){
	int i,j;
	Cstage *p;
	for(j=1;j<stage_size_y+1;++j)
	for(i=1;i<stage_size_x+1;++i){
		p=&(stage[i][j]);
		p->isOpen=1;
		
	}
}


void gamestate_handling(void){
	switch(game_state){
		case GAME_RESTART:
			
			set_stage(8,8);
			gametime.clock=0;
			
		break;
	}//end of switch
}
void drawState(void){
	switch(game_state){
		case GAME_CLEAR:
			
			CBmpsBlit(bmps,screen,26,0,240-50);
			
		break;
		case GAME_OVER:
			
			CBmpsBlit(bmps,screen,25,0,240-50);
			
		break;
	}//end of switch
	
	
}
void drawMenu(void){
	CBmpsBlit(bmps,screen,23,640-200,480-50);
	CBmpsBlit(bmps,screen,24,640-200,480-100);
	
	if(game_state==GAME_CLEAR)
		CBmpsBlit(bmps,screen,27,0,480-50);
	
}
void Menuclickcheck(int x,int y){
	
	SDL_Rect w;
	
	w.x=640-200;
	w.y=480-50;
	w.w=200;
	w.h=50;
	
	if(RectIn(&w,x,y))game_state=GAME_QUIT;
	
	w.y=480-100;
	
	if(RectIn(&w,x,y)){
		game_state=GAME_RESTART;
		n_trial++;
	}
	
	w.x=0;
	w.y=480-50;
	if(game_state==GAME_CLEAR){
		if(RectIn(&w,x,y))game_state=GAME_RESULT;
	}
	
	
}
int RectIn(SDL_Rect *p,int x,int y){
	if(x>=p->x && x<p->x+p->w && y>=p->y && y<p->y+p->h)return 1;
	return 0;
}

void drawCursor(void){
	int x,y;
	SDL_GetMouseState(&x,&y);
	CBmpsBlit(bmps,screen,22,x,y);
}

void drawTime(void){
	static char buf[2048];
	
	sprintf(buf,"Time : %4d.%02d",gametime.clock/1000,(gametime.clock%1000)/10);
	CffontBlitxy(font,buf,screen,0,0);
	sprintf(buf,"Frames per sec : %4d",gametime.fps);
	CffontBlitxy(font,buf,screen,0,16);
	
}

void finalize(void){
	CffontFree(font);
	CBmpsFree(bmps);
}

int gameloop(void){
	
	unsigned char flag=0;
	CTimeReset(&gametime);
	do{
		if(!gametime.isDelay){
//			drawback();
			drawTilescroll();
			if(game_state==GAME_CONFIG){
				drawConfig();
			}
			else{
				drawTiles();
				drawMenu();
			}
			drawTime();
			drawState();
			if(game_state==GAME_RESULT)drawResult();
			drawCursor();
			
			SDL_Flip(screen);
//			SDL_UpdateRect(screen,0,0,0,0);
		}
		moveTilescroll();
		CTimeWait(&gametime);
		if(readkeys()==-1)return -1;
		
		if(game_state==GAME_QUIT)break;
		gamestate_handling();
		
	}while(1);
	return(0);
}
void drawback(void){
	
	SDL_Rect dest;
	SDL_Surface *p;
	p=bmps->bmp[21];
	
	dest.w=p->w;
	dest.h=p->h;
	dest.x=0;
	dest.y=0;
	SDL_BlitSurface(p,NULL,screen,&dest);
}

int buttoncheck(int x,int y){
	
	int tile_x,tile_y;
	
	tile_x=(x-stage_area_x)/TILE_X+1;
	tile_y=(y-stage_area_y)/TILE_Y+1;
	
	if(tile_x <= 0 || tile_x > stage_size_x)return 0;
	if(tile_y <= 0 || tile_y > stage_size_y)return 0;
	
	reveal(tile_x,tile_y);
	
}

int readkeys(void){
	
	static int screennumber=0;
	char buf[200];
	SDL_Event e;
	SDLKey *key;
	
	while ( SDL_PollEvent(&e) > 0 ) {
		switch (e.type) {
			
			case SDL_KEYDOWN: {
				key=&(e.key.keysym.sym);
				
				if(*key==293){//F12
					
					sprintf(buf,"screenshot%04d.bmp",screennumber++);
					if(screennumber>9999)screennumber=0;
					SDL_SaveBMP(screen,buf);
					
				}
				
				if(*key==27){//ESC
					
					return(-1);
				}
				
			}
			break;
			
			case SDL_MOUSEMOTION:{
				;
			}
			break;
			case SDL_MOUSEBUTTONDOWN:{
				
				SDL_MouseButtonEvent *mp;
				mp=&(e.button);
				if(mp->button!=1){
					if(game_state==GAME_LOOP)game_state=GAME_CONFIG;
					else if(game_state==GAME_CONFIG)game_state=GAME_LOOP;
					
					break;
				}
				
				if(mp->button==1){
					if(game_state==GAME_CONFIG){
						Configclickcheck(mp->x,mp->y);
					}else{
						buttoncheck(mp->x,mp->y);
						Menuclickcheck(mp->x,mp->y);
					}
				}
				
			}
			break;
			
			case SDL_QUIT: {
				return(-1);
			}
			break;
		}
	}
	return(0);
	
}

int prepare(void){
	
	char *grafixfile="graph.txt";
	bmps=CBmpsInit(GRAPHIC_MAX);
	
	CBmpsLoadFromFile(bmps,grafixfile);
	font=CffontInit("font168.bmp",8,16,0x0ff,0,0x0ff);

//	screen=CScreenInitDefault();
	screen=CScreenInitDefaultHW();
	
	SDL_SetAlpha(font->font,SDL_SRCALPHA,128);
	SDL_DisplayFormat(font->font);
	
	SDL_SetAlpha(bmps->bmp[25],SDL_SRCALPHA,128);
	SDL_SetAlpha(bmps->bmp[26],SDL_SRCALPHA,128);
	
	CBmpsConvert(bmps);
	
	tscroll.bmp=bmps->bmp[21];
	tscroll.x=0;
	tscroll.y=0;
	tscroll.clock=0;
	
	
	return(0);
}

void drawTiles(void){
	int i,j;
	Cstage *p;
	SDL_Rect dest;
	int gnumber;
	
	for(j=1;j<stage_size_y+1;++j)
	for(i=1;i<stage_size_x+1;++i){
		p=&(stage[i][j]);
		
		if(p->isOpen){
			if(p->bomb>=MSSTG_BOMB)gnumber=20;
			if(p->bomb >=0 && p->bomb <= 8)gnumber=p->bomb+10;
		}else gnumber=19;
		
		dest.w=TILE_X;
		dest.h=TILE_Y;
		dest.x=(i-1)*TILE_X+stage_area_x;
		dest.y=(j-1)*TILE_Y+stage_area_y;
		SDL_BlitSurface(bmps->bmp[gnumber],NULL,screen,&dest);
		
	}
}

/*
開けてどきどきチェック
*/
void reveal(int x,int y){
	
	Cstage *p;
	
	p=&(stage[x][y]);
	
	if(p->isOpen)return;
	
	p->isOpen=1;
	real_left--;
	if(real_left==0){
		game_state=GAME_CLEAR;
		total_thinking=gametime.clock;
	}
	if(p->bomb>=MSSTG_BOMB){
		openAll();
		game_state=GAME_OVER;
	}
	if(p->bomb!=0)return;
	
	
	if(x>1)reveal(x-1,y);
	if(x<stage_size_x)reveal(x+1,y);
	if(y>1)reveal(x,y-1);
	if(y<stage_size_y)reveal(x,y+1);
	
}

/*
爆弾設置
*/
//x and y is not available now.
void set_stage(int x,int y){
	
	int i,j,n_bomb;
	Cstage *p;
	
	time_t tt;
	
	tt=time(NULL);
	srand((unsigned)tt);
	
	if(x>MAX_X)x=MAX_X;
	if(y>MAX_Y)x=MAX_Y;
	
	x=xyset[index_xyset].x;
	y=xyset[index_xyset].y;
	
	
	stage_size_x=x;
	stage_size_y=y;
	
	stage_area_x=640/2-x*TILE_X/2;
	stage_area_y=480/2-y*TILE_Y/2;
	
	real_bombs=0;
	game_state=GAME_LOOP;
	
	for(j=0;j<y+2;++j)
	for(i=0;i<x+2;++i){
		p=&(stage[i][j]);
		p->bomb=MSSTG_NONE;
		p->isOpen=0;
	}
	
//	n_bomb=x*y*BOMB_RATIO;
	n_bomb=x*y*ratio[index_ratio];
	
	while((n_bomb--)>0){
		i=((double)rand()/RAND_MAX)*x+1;
		j=((double)rand()/RAND_MAX)*y+1;
		
		if(stage[i][j].bomb>=MSSTG_BOMB)continue;
		
		stage[i][j].bomb=MSSTG_BOMB;
		
		stage[i-1][j-1].bomb++;
		stage[i  ][j-1].bomb++;
		stage[i+1][j-1].bomb++;
		stage[i-1][j  ].bomb++;
		stage[i+1][j  ].bomb++;
		stage[i-1][j+1].bomb++;
		stage[i  ][j+1].bomb++;
		stage[i+1][j+1].bomb++;
		
		real_bombs++;
		
	};
	real_left=x*y-real_bombs;
	
}
