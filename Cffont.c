/*

text put structures for SDL


*/
#include "Cffont.h"
#include "SDL.h"
/*private funcs for init*/
void CffontSetup(Cffont *this){
	
	int i;
	int x,y;
	SDL_Rect *w;
	
printf("%d,%d,%d,%d\n",this->width,this->height,this->font->w,this->font->h);
	x=0;
	y=0;
	w=this->fontarea;
	for(i=0;i<N_ASCII;++i,++w){
		w->w=this->width;
		w->h=this->height;
		w->x=x;
		w->y=y;
		x+=this->width;
		if(x>=this->font->w){
			x=0;
			y+=this->height;
		}
	}
	
}

//16x16 bitmaped font loading func
Cffont* CffontInitDefault16(char *filename){
	return CffontInit(filename,16,16,0x0ff,0,0x0ff);
}
//16x16 bitmaped font loading func
Cffont* CffontInitDefault32(char *filename){
	return CffontInit(filename,32,32,0x0ff,0,0x0ff);
}

Cffont* CffontInit(char *filename,int width,int height,int r,int g,int b){
	
	Cffont *p;
	Uint32 color;
	
	p=(Cffont *)malloc(sizeof(Cffont));
	if(NULL==p){
		fprintf(stderr,"ERROR:no memory at CffontInit\n");
		return(NULL);
	}
	memset(p,0,sizeof(Cffont));
	p->font=SDL_LoadBMP(filename);
	if(NULL==p->font){
		fprintf(stderr,"ERROR:NO MEMORY or cant find %s at CffontInit\n",filename);
		free(p);
		return(NULL);
	}
	color=SDL_MapRGB(p->font->format,r,g,b);
	SDL_SetColorKey(p->font,SDL_SRCCOLORKEY,color);
	p->width=width;
	p->height=height;
//	SDL_DisplayFormat(p->font);
	CffontSetup(p);
	
	return(p);
	

}

void CffontFree(Cffont *this){
	if(NULL==this)return;
	if(NULL==this->font)return;
	SDL_FreeSurface(this->font);
	free(this);
}


int CffontBlit(Cffont *this,char *string,SDL_Surface *surf){
	return CffontBlitxy(this,string,surf,0,0);
}
int CffontBlitxy(Cffont *this,char *string,SDL_Surface *surf,int x,int y){
	SDL_Rect src,dest;
	dest.x=x;
	dest.y=y;
	
	while(*string!=0){
		dest.w=this->width;
		dest.h=this->height;
		src=this->fontarea[*string];
		SDL_BlitSurface(this->font,&src,surf,&dest);
		string++;
		dest.x+=this->width;
	}
	return(0);
}
