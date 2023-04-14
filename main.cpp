#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>


using namespace std;


void mainloop(SDL_Renderer* renderer,SDL_Texture* myspaceship, SDL_Texture* bulletimg, SDL_Texture* background,SDL_Texture* enemycraft,SDL_Rect &enemy, SDL_Rect& rectangle, SDL_Rect& bulletrect,SDL_Texture* bulletenemy,SDL_Rect enemybulletrect);
void view(SDL_Renderer *renderer, SDL_Texture *myspaceship, SDL_Texture *bulletimg, SDL_Texture *background,SDL_Texture* enemycraft,SDL_Rect &enemy, SDL_Rect &rectangle, SDL_Rect &bulletrect,bool *bulletfire,SDL_Texture* bulletenemy,SDL_Rect& enemybulletrect,bool* enemybulletfire);
void clear(SDL_Window *window,SDL_Renderer *renderer, SDL_Texture *myspaceship, SDL_Surface *image, SDL_Surface *spaceship, SDL_Surface *bulletSurface, SDL_Texture *bulletimg, SDL_Texture *background, SDL_Rect &rectangle, SDL_Rect &bulletrect,SDL_Texture* enemycraft,SDL_Rect& enemy,SDL_Surface* enemySurface,SDL_Texture *bulletenemy);
void imageinit(SDL_Window* window,SDL_Renderer *renderer);



void imageinit(SDL_Window* window,SDL_Renderer *renderer){

    SDL_Rect rectangle={500,650,150,150};
    SDL_Surface *spaceship = IMG_Load("./images/spaceship5.png");
	SDL_Texture *myspaceship = SDL_CreateTextureFromSurface(renderer, spaceship);

    SDL_Rect bulletrect = {rectangle.x+25,rectangle.y-90, 100, 80};
	SDL_Surface* bulletSurface = IMG_Load("./images/bullet.png");
    SDL_Texture* bulletimg = SDL_CreateTextureFromSurface(renderer, bulletSurface);

    SDL_Rect enemy = {500,50, 150, 150};
	SDL_Surface* enemySurface = IMG_Load("./images/enemy.png");
    SDL_Texture* enemycraft= SDL_CreateTextureFromSurface(renderer, enemySurface);

	SDL_Rect enemybulletrect = {enemy.x+25,enemy.y+90, 100, 80};
	SDL_Surface* bulletSurface2 = IMG_Load("./images/bulletenemy.png");
    SDL_Texture* bulletenemy = SDL_CreateTextureFromSurface(renderer, bulletSurface2);
	
	
	SDL_Surface *image=IMG_Load("./images/earth.png");
	SDL_Texture *background = SDL_CreateTextureFromSurface(renderer, image);

    mainloop(renderer,myspaceship,bulletimg,background,enemycraft,enemy,rectangle,bulletrect,bulletenemy,enemybulletrect);

    clear(window,renderer, myspaceship, image, spaceship, bulletSurface, bulletimg, background, rectangle, bulletrect,enemycraft,enemy,enemySurface,bulletenemy);
}

void  mainloop(SDL_Renderer* renderer,SDL_Texture* myspaceship, SDL_Texture* bulletimg, SDL_Texture* background,SDL_Texture* enemycraft,SDL_Rect &enemy, SDL_Rect& rectangle, SDL_Rect& bulletrect,SDL_Texture* bulletenemy,SDL_Rect enemybulletrect){

    bool quit = false;
	bool bulletfire = false;
	bool enemybulletfire = false;
	int player_change = 0;
	int player2_change = 0;

	while (!quit) {

		SDL_Event  event;
		while (SDL_PollEvent(&event)) {
           
		    if(event.type==SDL_QUIT){
			   quit = true;
			   return;
		   }
            if(event.type==SDL_KEYDOWN){
                if(event.key.keysym.sym==SDLK_RIGHT){
					player_change = 10;
		        }
			    if (event.key.keysym.sym == SDLK_LEFT) {
					player_change = - 10;
		        }

                if (event.key.keysym.sym == SDLK_SPACE) {
                    bulletfire = true;
			    }
				if (event.key.keysym.sym == SDLK_s) {
                    enemybulletfire = true;
			    }
			    if (event.key.keysym.sym == SDLK_a) {
					player2_change = - 10;
			    }
			    if (event.key.keysym.sym == SDLK_d) {
					player2_change = 10;
			    }
		    }
			if(event.type==SDL_KEYUP){
                if(event.key.keysym.sym==SDLK_RIGHT){
					player_change = 0;
				}
			    if (event.key.keysym.sym == SDLK_LEFT) {
					player_change = 0;
				}
			    if (event.key.keysym.sym == SDLK_a) {
					player2_change = 0;
			    }
			    if (event.key.keysym.sym == SDLK_d) {
					player2_change = 0;
			    }
		    }
			rectangle.x += player_change;
			enemy.x += player2_change;
			if(rectangle.x<=50){
				rectangle.x = 50;
			}
			if(rectangle.x>=1300){
				rectangle.x = 1300;
			}
			if(enemy.x<=50){
				enemy.x = 50;
			}
			if(enemy.x>=1300){
				enemy.x = 1300;
			}
		}
		if(!bulletfire){
			bulletrect.x = rectangle.x+25;
		}
		if(!enemybulletfire){
			enemybulletrect.x = enemy.x+25;
		}
		view(renderer, myspaceship, bulletimg, background, enemycraft, enemy, rectangle, bulletrect, &bulletfire,bulletenemy,enemybulletrect,&enemybulletfire);
	}
}

void view(SDL_Renderer* renderer,SDL_Texture* myspaceship, SDL_Texture* bulletimg, SDL_Texture* background,SDL_Texture* enemycraft,SDL_Rect &enemy,SDL_Rect& rectangle, SDL_Rect& bulletrect,bool *bulletfire,SDL_Texture* bulletenemy,SDL_Rect &enemybulletrect,bool* enemybulletfire){

	static int score1 = 0;
	static int score2 = 0;

	string scoreText = "Score: " + to_string(score1);
	string scoreText2 = "Score: " + to_string(score2);
    //audio 
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_AllocateChannels(2);
	Mix_Chunk* popSound = Mix_LoadWAV("./music/pop.wav");

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_AllocateChannels(3);
	Mix_Chunk* popSound2 = Mix_LoadWAV("./music/pop2.wav");
	
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, background, NULL, NULL);
//bullet out of frame
	if(bulletrect.y<=0){
		*bulletfire = false;
		bulletrect.x = rectangle.x + 25;
		bulletrect.y = rectangle.y - 90;
	}
	if(enemybulletrect.y>=800){
		*enemybulletfire = false;
	    enemybulletrect.x = enemy.x + 25;
		enemybulletrect.y = enemy.y + 90;
	}
//bullet hit enemy
    if(*bulletfire && bulletrect.x>=enemy.x-30 && bulletrect.x<=enemy.x+80 && bulletrect.y>=enemy.y && bulletrect.y<=enemy.y+130){
		*bulletfire = false;
		bulletrect.x = rectangle.x + 25;
		bulletrect.y = rectangle.y - 90;
		enemy.x = 500;
		enemy.y = 50;
		score1 = score1 + 5;
		Mix_PlayChannel(-1, popSound, 0);
	}
	
	if(*enemybulletfire && enemybulletrect.x>=rectangle.x-30 && enemybulletrect.x<=rectangle.x+80 && enemybulletrect.y>=rectangle.y&& enemybulletrect.y<=rectangle.y+130){
		*enemybulletfire = false;
		enemybulletrect.x = enemy.x + 25;
		enemybulletrect.y = enemy.y + 90;
		rectangle.x = 500;
		rectangle.y = 650;
		score2 = score2 + 5;
		Mix_PlayChannel(-1, popSound2, 0);
	}
	
	//print bulet
	if (*bulletfire) {
		SDL_RenderCopy(renderer, bulletimg, NULL, &bulletrect);
        bulletrect.y -= 14;	
	}
	if (*enemybulletfire) {
		SDL_RenderCopy(renderer, bulletenemy, NULL, &enemybulletrect);
		enemybulletrect.y = enemybulletrect.y + 14;
	}

	SDL_RenderCopy(renderer, myspaceship, NULL,&rectangle);
	SDL_RenderCopy(renderer, enemycraft, NULL, &enemy);

	//displaying score
	
	SDL_Rect textrectangle={500,800,150,50};
	SDL_Rect textrectangle2={500,20,150,50};
	TTF_Init();
	
	TTF_Font *textFont = TTF_OpenFont("./fonts/font5.ttf", 32);

	SDL_Surface *textsurface = TTF_RenderText_Solid(textFont,scoreText.c_str(), {255, 0, 0});
	SDL_Texture *texttexture = SDL_CreateTextureFromSurface(renderer,textsurface);
	SDL_FreeSurface(textsurface);

	SDL_Surface *textsurface2 = TTF_RenderText_Solid(textFont,scoreText2.c_str(), {255, 0, 0});
	SDL_Texture *texttexture2 = SDL_CreateTextureFromSurface(renderer,textsurface2);
	SDL_FreeSurface(textsurface2);

	SDL_RenderCopy(renderer, texttexture, NULL, &textrectangle);
	SDL_RenderCopy(renderer, texttexture2, NULL, &textrectangle2);


	SDL_RenderPresent(renderer);

	SDL_DestroyTexture(texttexture);
	SDL_DestroyTexture(texttexture2);
	SDL_Delay(20);
	
}


void clear(SDL_Window *window,SDL_Renderer* renderer,SDL_Texture* myspaceship,SDL_Surface *image,SDL_Surface *spaceship,SDL_Surface *bulletSurface, SDL_Texture* bulletimg, SDL_Texture* background, SDL_Rect& rectangle, SDL_Rect& bulletrect,SDL_Texture* enemycraft,SDL_Rect& enemy,SDL_Surface * enemySurface,SDL_Texture * bulletenemy){


    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_FreeSurface(image);
	SDL_FreeSurface(spaceship);
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(myspaceship);
	SDL_DestroyTexture(bulletimg);
    SDL_FreeSurface(bulletSurface);
	SDL_DestroyTexture(enemycraft);
    SDL_FreeSurface(enemySurface);
	SDL_DestroyTexture(bulletenemy);
	//enemybulletwindowdestroy


	IMG_Quit;
	TTF_Quit;

	SDL_Quit();

	return ;
}



int main(int argc,char* args[]) {

     SDL_Init(SDL_INIT_EVERYTHING);
	 SDL_Window* window;
     SDL_Renderer *renderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 0 ;
	}
    window = SDL_CreateWindow("first try", 0,25, 1500, 900, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_AllocateChannels(1);
    Mix_Music* music = Mix_LoadMUS("./music/music.mp3");
	Mix_PlayMusic(music, -1);

    imageinit(window,renderer);

    Mix_FreeMusic(music);
    return 0;
}

