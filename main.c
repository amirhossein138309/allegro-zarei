#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
	ALLEGRO_BITMAP  *Dog1=NULL;
	
	ALLEGRO_BITMAP  *Cat2=NULL;
	ALLEGRO_BITMAP  *Dog2=NULL;
	ALLEGRO_BITMAP  *Dog3=NULL;
	ALLEGRO_BITMAP  *Dog4=NULL;
	ALLEGRO_BITMAP  *mouse_1=NULL;
	ALLEGRO_BITMAP  *mouse_2=NULL;
	ALLEGRO_BITMAP  *mouse_3=NULL;


	
typedef struct khoone {
	int x;
	int y;
}khoone;


typedef struct button{
	int x1;
	int x2;
	int y1;
	int y2;
	
}button;



typedef struct Cat{                                             // struct for cats..............................
	int x;
	int y;
	int attack;
	int defence;
	int mojaz;
	int locked;
}Cat;





struct dog{                                                   // struct for dogs................................
	int x;
	int y;
	int speed;
	int power;
	int energy;
};








typedef struct fish{                                      // struct for fishes...............................
	int x;
	int y;
	int energy;
	int noe;
}fish;





typedef struct mouse{                                    //struct for mouses.................................
	int x;
	int y;
	int point;
	int tedad;
	int move;
}mouse;


typedef struct shokolat{
	int x;
	int y;
}shokolat;                                                                  // payan struct ha..........................


void must_init(bool test, const char* description)
{
	if (test) return;

	printf("couldn't initialize %s\n", description);
	exit(1);
}

int check_mouse_position(button* btn, ALLEGRO_MOUSE_STATE* mouse) {
	if (mouse->x > btn->x1 && mouse->x <btn->x2 && mouse->y > btn->y1 && mouse->y < btn->y2) {
		return 1;
	}
	return 0;
}


void cleararray(int x[][16]){
	for(int i=1;i<16;i++){
		for(int j=1;j<16;j++){
			x[i][j]=0;
		}
	}
}


void mouselocation(struct mouse mouses[],int visited[16][16]){                           // function for mouse location.............
	int x,y;
	for(int i = 0 ; i < mouses[0].tedad; i++){
		x = (rand() % 15) + 1;
		y = (rand() % 15) + 1;
		if (visited[x][y] == 0){
			mouses[i].x = x;
			mouses[i].y = y;
			mouses[i].point = mouses[0].point;
			mouses[i].move = mouses[0].move;
			visited[x][y] = 1;
		}
		else i--;
	}
}
void fishlocation(struct fish fishes[], int visited[][16]){                             // function for fish location.............
	for(int i = 0 ; i < 10 ; i++){
		int x = (rand() % 15)+1;
		int y = (rand() % 15)+1;
		if (visited[x][y] == 0){
			fishes[i].x = x;
			fishes[i].y = y;
			fishes[i].energy = fishes[0].energy;
			visited[x][y] = 1;	
		
		}
		else i--;
	}
}
void shokolatlocation(struct shokolat shokolats[], int visited[][16]){                  //function for shokolats location...............
	for(int i = 0 ; i < 8 ; i++){
		int x = (rand() % 15)+1;
		int y = (rand() % 15)+1;
		if (visited[x][y] == 0){
			shokolats[i].x = x;
			shokolats[i].y = y;
			visited[x][y] = 1;	
		
		}
		else i--;
	}
}
void eatfish(struct Cat cats[],struct fish fishes[]){                                 // function for eating fish --> cats..............
	for(int i = 0 ;i < 2 ; i++){
		for(int j = 0 ; j < 4 ; j++){
			if (cats[i].x == fishes[j].x && cats[i].y == fishes[j].y){
				cats[i].defence += 1000;
				fishes[j].y = -1;
			}
		}
	}
	for(int i = 0 ; i < 2 ; i++){
		for(int j = 4 ; j < 8 ; j++){
			if(cats[i].x == fishes[j].x && cats[i].y == fishes[j].y){
				cats[i].defence += 3;
				fishes[j].y = -1;
			}
		}
	}
	for(int i = 0 ; i < 2 ; i++){
		for(int j = 8 ; j < 10 ; j++){
			if (cats[i].x == fishes[j].x && cats[i].y == fishes[j].y){
				cats[i].defence += 4;
				fishes[j].y = -1;
			}
	}	
	
}
}


void doglocation(struct dog dogs[],int visited[16][16]){                          // function for dog location...............
	int x,y;
	time_t t;
	srand((unsigned) time(&t));
	for(int i = 0 ; i < 4 ; i++ ){
		x = (rand() % 7)+1;
		y = (rand() % 7)+1;
		if(visited[x][y] == 0){
			if (i == 0){
				dogs[0].x = x;
				dogs[0].y = y;
				dogs[0].energy = 30;
				dogs[0].speed = 5;
				dogs[0].power = 5;
			}
			else if(i==1){
				x = x+8;
				y = y+8;
				dogs[1].x = x;
				dogs[1].y = y;
				dogs[1].energy = 15;
				dogs[1].speed = 2;
				dogs[1].power = 2;
			}
			else if(i==2){
				y = y+8;
				dogs[2].x = x;
				dogs[2].y = y;
				dogs[2].energy = 30;
				dogs[2].speed = 2;
				dogs[2].power = 3;
			}
			else if(i==3){
				x = x+8;
				
				dogs[3].x = x;
				dogs[3].y = y;
				dogs[3].energy = 5;
				dogs[3].speed = 1;
				dogs[3].power = 1;
			}
			visited[x][y] = 1;
		}
		else i--;
	}
}
void dogmove(struct dog dogs[]){                                     // function for dogs move.....................
	int s;
	for(int i = 0 ; i < 4 ; i++){
		if (i == 0){
			int dog0[16][16];
			for(int k = 1 ; k < 16 ; k++){
				for(int l = 1 ; l < 16 ; l++){
					dog0[k][l] = 0;
				}
			}
			for(int j = 1 ; j <= dogs[i].speed ; j++){
		
				s = (rand() % 4) + 1;
				int x2 = dogs[i].x;
				int y2 = dogs[i].y;
				if(s == 1){
					if(dogs[i].x+1 < 16 && dog0[x2 + 1][y2] == 0 ){
						cleararray(dog0);
						dogs[i].x++;
					
						dog0[x2 + 1][y2] = 1;
					
					}
					else{
						j--;
					}
				
				
				}
				else if(s == 2){
					if(0 < dogs[i].x-1 && dog0[x2 - 1][y2] == 0){
						cleararray(dog0);
							dogs[i].x--;
							
							dog0[x2 - 1][y2] = 1;
						
					}	
					else{
						j--;
					}
					
				}
				else if(s == 3){
					if(dogs[i].y+1 < 16 && dog0[x2][y2 + 1] == 0){
						cleararray(dog0);
					dogs[i].y++;
				
					dog0[x2][y2 + 1] = 1;
			
					}
					
					else{
						j--;
					}
				}
				else if(s == 4){
					if(0 < dogs[i].y-1 && dog0[x2][y2 - 1] == 0){
						cleararray(dog0);
						dogs[i].y--;
						
					
						dog0[x2][y2 - 1] = 1;
					}
					
					else{
						j--;
					}
					
				}
				
			
			}
		}
		else if ( i == 1){
			int dog1[16][16];
			for(int k = 1 ; k < 16 ; k++){
				for(int l = 1 ; l < 16 ; l++){
					dog1[k][l] = 0;
				}
			}
			for(int j = 1 ; j <= dogs[i].speed ; j++){
				s = (rand() % 4) + 1;
				int x2 = dogs[i].x;
				int y2 = dogs[i].y;
				if (s == 1){
					if(dogs[i].x + 1 < 16 && dog1[x2 + 1][y2] == 0){
						cleararray(dog1);
						dogs[i].x++;
						dog1[x2 + 1][y2] = 1;
					}
					else j--;
					
				}
				else if (s == 2){
					if(dogs[i].x - 1 > 0 && dog1[x2 - 1][y2] == 0){
						cleararray(dog1);
						dogs[i].x--;
						dog1[x2 - 1][y2] = 1;
					}
					else j--;
					
				}
				else if (s == 3){
					if(dogs[i]. y + 1 < 16 && dog1[x2][y2 + 1] == 0){
						cleararray(dog1);
						dogs[i].y++;
						dog1[x2][y2 + 1] = 1;
					}
					else j--;
				
				}
				else if (s == 4){
					if(dogs[i].y - 1 > 0 && dog1[x2][y2 - 1] == 0){
						cleararray(dog1);
						dogs[i].y--;
						dog1[x2][y2 - 1] = 1;
					}
					else j--;
					
				}
			}
		}
		else if ( i == 2){
			int dog2[16][16];
			for(int k = 1 ; k < 16 ; k++){
				for(int l = 1 ; l < 16 ; l++){
					dog2[k][l] = 0;
				}
			}
			for(int j = 1 ; j <= dogs[i].speed ; j++){
				s = (rand() % 4 ) + 1;
				int x2 = dogs[i].x;
				int y2 = dogs[i].y;
				if (s == 1){
					if(dogs[i].x + 1 < 16 && dog2[x2 + 1][y2] == 0){
						cleararray(dog2);
						dogs[i].x++;
						dog2[x2 + 1][y2] = 1;
					}
					else j--;
				}
				else if (s == 2){
					if(dogs[i].x - 1 > 0 && dog2[x2 - 1][y2] == 0){
						cleararray(dog2);
						dogs[i].x--;
						dog2[x2 - 1][y2] = 1;
					}
					else j--;
				}
				else if (s == 3){
					if(dogs[i].y + 1 < 16 && dog2[x2][y2 + 1] == 0){
						cleararray(dog2);
						dogs[i].y++;
						dog2[x2][y2 + 1] = 1;
					}
					else j--;
				}
				else if (s == 4){
					if(dogs[i].y - 1 > 0 && dog2[x2][y2 - 1] == 0){
						cleararray(dog2);
						dogs[i].y--;
						dog2[x2][y2 - 1] = 1;
					}
					else j--;
				}
			}
		}
		else if( i == 3){
			int dog3[16][16];
			for(int k = 1; k < 16 ; k++){
				for(int l = 1 ; l < 16 ; l++){
					dog3[k][l] = 0;
				}
			}
			for(int j = 1 ; j <= dogs[i].speed ; j++){
				s = (rand() % 4) + 1;
				int x2 = dogs[i].x;
				int y2 = dogs[i].y;
				if (s == 1){
					if(dogs[i].x + 1 < 16 && dog3[x2 + 1][y2] == 0){
						cleararray(dog3);
						dogs[i].x++;
						dog3[x2 + 1][y2] = 1;
						
					}
					else j--;
				}
				else if(s == 2){
					if(dogs[i].x - 1 > 0 && dog3[x2 - 1][y2] == 0){
						cleararray(dog3);
						dogs[i].x--;
						dog3[x2 - 1][y2] = 1;
					}
					else j--;
				}
				else if(s == 3){
					if(dogs[i].y + 1 < 16 && dog3[x2][y2 + 1] == 0){
						cleararray(dog3);
						dogs[i].y++;
						dog3[x2][y2 + 1] = 1;
					}
					else j--;
				}
				else if (s == 4){
					if(dogs[i].y - 1 > 0 && dog3[x2][y2 - 1] == 0){
						cleararray(dog3);
						dogs[i].y--;
						dog3[x2][y2 - 1] = 1;
					}
					else j--;
				}
			}
		}
	}
}
void mousemove(struct mouse mouses[]){                                          // function for mouse move................
	for(int i = 0 ; i < mouses[0].tedad ; i++){
		for(int j = 1 ; j <= mouses[0].move ; j++){
			int s = (rand() % 4) + 1;
			if (s == 1){
				if (mouses[i].x + 1 < 16){
					mouses[i].x++;
				}
				else j--;
			}
			else if (s == 2){
				if(mouses[i].x - 1 > 0){
					mouses[i].x--;
				}
				else j--;
			}
			else if (s == 3){
				if(mouses[i].y + 1 < 16){
					mouses[i].y++;
				}
				else j--;
			}
			else if (s == 4){
				if(mouses[i].y - 1 > 0){
					mouses[i].y--;
				}
				else j--;
			}
		}
	}
}
void fightdogcat(struct Cat cats[], struct dog dogs[]){                               //function for fighting between cat and dog.............
	for(int i = 0 ; i < 2 ; i++){
		for(int j = 0 ; j < 4 ;j++){
			if (cats[i].x == dogs[j].x && cats[i].y == dogs[j].y){
				if (cats[i].attack * cats[i].defence > dogs[j].energy * dogs[j].power){
					dogs[j].x = 1000;
					cats[i].defence = cats[i].defence - (dogs[j].energy * dogs[j].power)/cats[i].attack;
				}
				else {
					cats[i].locked = 2;
					dogs[j].power = dogs[j].power - (cats[i].defence * cats[i].attack)/dogs[j].energy;
					cats[i].attack = 2;
					cats[i].defence = 5;
				}
			}
	}	}
}
void fightcat(struct Cat cats[]){                                                   //function for fighting between two cats..............
	if(cats[0].x==cats[1].x && cats[0].y==cats[1].y){
		if(cats[0].defence*cats[0].attack>cats[1].defence*cats[1].attack){
			cats[1].locked= 2;
			cats[0].defence=cats[0].defence-(cats[1].attack*cats[1].defence)/cats[0].attack;
			cats[1].attack= 1;
			cats[1].defence= 0;
		}
		else{
			cats[0].locked= 2;
			cats[1].defence=cats[1].defence-(cats[0].attack*cats[0].defence)/cats[1].attack;
			cats[0].attack= 2;
			cats[0].defence= 5;
		}		
	}	
	
}
void eat_shokolat(struct Cat cats[],struct shokolat shokolats[]){                  //function for eating shokolats...................
	for(int i = 0 ; i < 2 ; i++){
		for(int j = 0 ; j < 8 ; j++){
			if (cats[i].x == shokolats[j].x && cats[i].y == shokolats[j].y){
				cats[i].attack++;
				shokolats[j].x = 1000;
			}
		}
	}
}


void ShowMap(){                                                 //function for showing map.....................
	int i,j;
	int a=50;
	for(i=1;i<16;i++){
		for(j=1;j<16;j++){
			al_draw_rectangle(i*a,j*a,i*a+a,j*a+a,al_map_rgb(0,0,0),2);
			al_draw_filled_rectangle(i*a,j*a,i*a+a,j*a+a,al_map_rgb(51,102,0));
		}
		
	}
		
    	
		al_draw_line(100,100,200,100,al_map_rgb(255,0,0),20);
		al_draw_line(600,600,600,700,al_map_rgb(255,0,0),20);
		al_draw_line(590,700,650,700,al_map_rgb(255,0,0),20);
		al_draw_line(300,300,300,400,al_map_rgb(255,0,0),20);
		al_draw_line(610,200,550,200,al_map_rgb(255,0,0),20);
		al_draw_line(600,200,600,300,al_map_rgb(255,0,0),20);
		al_draw_line(200,600,300,600,al_map_rgb(255,0,0),20);
		al_draw_line(50,50,50,800,al_map_rgb(51,25,0),6);
		al_draw_line(50,50,800,50,al_map_rgb(51,25,0),6);
		al_draw_line(800,50,800,800,al_map_rgb(51,25,0),6);
		al_draw_line(50,800,800,800,al_map_rgb(51,25,0),6);
		
	 
} 

















int main(void){
	srand(time(0));
	khoone block[15][15];
	shokolat shokolats[8];
	int a=50,b=50;
	int visited[16][16];
	for(int i = 0 ; i < 16 ;i++){
		for(int j = 0 ; j < 16 ; j++){
			visited[i][j] = 0;
		}
	}
	
	for(int i=0;i<15;i++){
		a=50;
		for(int j=0;j<15;j++){
			block[i][j].x=a;
			block[i][j].y=b;
			a+=50;
		}
		b=b+50;
	}
	
	int round=1,done=1;
	struct dog dogs[4];
	struct mouse mouse1[8];
    mouse1[0].tedad = 8;
    mouse1[0].point = 1;
    mouse1[0].move = 1;
    struct mouse mouse2[6];
    mouse2[0].tedad = 6;
    mouse2[0].point = 2;
    mouse2[0].move = 2;
    struct mouse mouse3[4];
    mouse3[0].tedad = 4;
    mouse3[0].point = 3;
    mouse3[0].move = 3;
    struct fish fishes[10];
    
    
    
    fishlocation(fishes,visited);
    doglocation(dogs,visited);
	mouselocation(mouse1,visited);
	mouselocation(mouse2,visited);
	mouselocation(mouse3,visited);
	shokolatlocation(shokolats,visited);
	
	Cat cats[4];
	for(int i=0;i<4;i++){
		cats[i].x=8;
		cats[i].y=8;
		cats[i].defence=5;
		cats[i].attack=2;
		cats[i].mojaz=3;
		cats[i].locked=0;
	}

	al_init();
	ALLEGRO_DISPLAY *display=al_create_display(850,850);
	ALLEGRO_FONT *font1=NULL;
	ALLEGRO_FONT *font2=NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	event_queue=al_create_event_queue();
	al_register_event_source(event_queue,al_get_keyboard_event_source());
	ALLEGRO_BITMAP  *background=NULL;
	ALLEGRO_BITMAP  *house=NULL;
		ALLEGRO_BITMAP  *fish=NULL;
	ALLEGRO_BITMAP  *shokolat=NULL;
	
	
	
	background=al_load_bitmap("Images/Cat.jpg");
	house=al_load_bitmap("Images/house.jpg");
	Cat2=al_load_bitmap("Images/Cat2.jpg");
	Dog1=al_load_bitmap("Images/Dog1.jpg");
	Dog2=al_load_bitmap("Images/Dog2.jpg");
	Dog3=al_load_bitmap("Images/Dog3.jpg");
	Dog4=al_load_bitmap("Images/Dog4.jpg");
	fish=al_load_bitmap("Images/fish.png");
	mouse_1=al_load_bitmap("Images/mouse1.jpg");
	mouse_2=al_load_bitmap("Images/mouse2.jpg");
	mouse_3=al_load_bitmap("Images/mouse3.jpg");
	shokolat=al_load_bitmap("Images/shokolat.jpg");
	font1=al_load_ttf_font("tahoma.ttf",50,0);
	font2=al_load_ttf_font("tahoma.ttf",20,0);
	al_clear_to_color(al_map_rgb(255,255,255));
	
	must_init(al_init(), "allegro");
	must_init(al_install_keyboard(), "keyboard");
	must_init(al_init_primitives_addon(), "primitives");
	must_init(al_install_keyboard(), "keyboard");
	
	ALLEGRO_EVENT ev;
	al_draw_bitmap(background,cats[0].x*50,cats[0].y*50,0);
	al_draw_bitmap(house,400,400,0);
	al_draw_textf(font1 , al_map_rgb(0 , 0 , 0) , 500 , -10 , ALLEGRO_ALIGN_CENTER , "%d" , round);
	al_draw_text(font2,al_map_rgb(0,0,0),600,10,0,"PRESS ESC TO EXIT");
	al_draw_text(font1,al_map_rgb(0,0,0),400,-10,ALLEGRO_ALIGN_CENTER,"ROUND");
	ShowMap();
	al_draw_text(font1,al_map_rgb(0,0,0),400,-10,ALLEGRO_ALIGN_CENTER,"ROUND");
			al_draw_bitmap(Cat2,cats[1].x*50,cats[1].y*50,0);
			al_draw_bitmap(background,cats[0].x*50,cats[0].y*50,0);
			al_draw_bitmap(Dog1,dogs[0].x*50,dogs[0].y*50,0);
			al_draw_bitmap(Dog2,dogs[1].x*50,dogs[1].y*50,0);
			al_draw_bitmap(Dog3,dogs[2].x*50,dogs[2].y*50,0);
			al_draw_bitmap(Dog4,dogs[3].x*50,dogs[3].y*50,0);
			al_draw_bitmap(fish,fishes[0].x*50,fishes[0].y*50,0);
			al_draw_bitmap(fish,fishes[1].x*50,fishes[1].y*50,0);
			al_draw_bitmap(fish,fishes[2].x*50,fishes[2].y*50,0);
			al_draw_bitmap(fish,fishes[3].x*50,fishes[3].y*50,0);
			al_draw_bitmap(fish,fishes[4].x*50,fishes[4].y*50,0);
			al_draw_bitmap(fish,fishes[5].x*50,fishes[5].y*50,0);
			al_draw_bitmap(fish,fishes[6].x*50,fishes[6].y*50,0);
			al_draw_bitmap(fish,fishes[7].x*50,fishes[7].y*50,0);
			al_draw_bitmap(fish,fishes[8].x*50,fishes[8].y*50,0);
			al_draw_bitmap(fish,fishes[9].x*50,fishes[9].y*50,0);
			for(int i=0;i<8;i++)
				al_draw_bitmap(shokolat,shokolats[i].x*50,shokolats[i].y*50,0);
			for(int i=0;i<8;i++)
				al_draw_bitmap(mouse_1,mouse1[i].x*50,mouse1[i].y*50,0);
			for(int i=0;i<6;i++)
				al_draw_bitmap(mouse_2,mouse2[i].x*50,mouse2[i].y*50,0);
			for(int i=0;i<4;i++)
				al_draw_bitmap(mouse_3,mouse3[i].x*50,mouse3[i].y*50,0);
			al_draw_bitmap(house,400,400,0);
			al_flip_display();
	done=0;
	while(1){ 
		al_wait_for_event(event_queue,&ev);
			switch (ev.type)
			{
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				return 0;
				break;
			case ALLEGRO_EVENT_KEY_DOWN:
				if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
					return 0;
    		    if(ev.keyboard.keycode != ALLEGRO_KEY_ESCAPE)
                    break;
		    }

			al_draw_filled_rectangle(0,0,800,45,al_map_rgb(255,255,255));
	        al_draw_textf(font1, al_map_rgb(0 , 0 , 0) , 500 , -10 , ALLEGRO_ALIGN_CENTER , "%d" , round);
			ShowMap();
			al_draw_text(font1,al_map_rgb(0,0,0),400,-10,ALLEGRO_ALIGN_CENTER,"ROUND");
			al_draw_text(font2,al_map_rgb(0,0,0),600,10,0,"PRESS ESC TO EXIT");
			al_draw_text(font1,al_map_rgb(0,0,0),400,-10,ALLEGRO_ALIGN_CENTER,"ROUND");
			al_draw_bitmap(Cat2,cats[1].x*50,cats[1].y*50,0);
			al_draw_bitmap(background,cats[0].x*50,cats[0].y*50,0);
			al_draw_bitmap(Dog1,dogs[0].x*50,dogs[0].y*50,0);
			al_draw_bitmap(Dog2,dogs[1].x*50,dogs[1].y*50,0);
			al_draw_bitmap(Dog3,dogs[2].x*50,dogs[2].y*50,0);
			al_draw_bitmap(Dog4,dogs[3].x*50,dogs[3].y*50,0);
			for(int i=0;i<8;i++)
				al_draw_bitmap(shokolat,shokolats[i].x*50,shokolats[i].y*50,0);
			for(int i=0;i<8;i++)
				al_draw_bitmap(mouse_1,mouse1[i].x*50,mouse1[i].y*50,0);
			for(int i=0;i<6;i++)
				al_draw_bitmap(mouse_2,mouse2[i].x*50,mouse2[i].y*50,0);
			for(int i=0;i<4;i++)
			al_draw_bitmap(mouse_3,mouse3[i].x*50,mouse3[i].y*50,0);
			
			al_draw_bitmap(fish,fishes[0].x*50,fishes[0].y*50,0);
			al_draw_bitmap(fish,fishes[1].x*50,fishes[1].y*50,0);
			al_draw_bitmap(fish,fishes[2].x*50,fishes[2].y*50,0);
			al_draw_bitmap(fish,fishes[3].x*50,fishes[3].y*50,0);
			al_draw_bitmap(fish,fishes[4].x*50,fishes[4].y*50,0);
			al_draw_bitmap(fish,fishes[5].x*50,fishes[5].y*50,0);
			al_draw_bitmap(fish,fishes[6].x*50,fishes[6].y*50,0);
			al_draw_bitmap(fish,fishes[7].x*50,fishes[7].y*50,0);
			al_draw_bitmap(fish,fishes[8].x*50,fishes[8].y*50,0);
			al_draw_bitmap(fish,fishes[9].x*50,fishes[9].y*50,0);
			for(int i=0;i<8;i++)
				al_draw_bitmap(shokolat,shokolats[i].x*50,shokolats[i].y*50,0);
			al_draw_bitmap(house,400,400,0);
            
			if(cats[1].locked>0){
        			cats[1].locked--;
				}
		    if(cats[0].locked>0){
					cats[0].locked--;
				}
		 if(ev.type == ALLEGRO_EVENT_KEY_DOWN && cats[0].defence>0 &&  cats[0].mojaz>0 && cats[0].locked == 0 )                            //shoroe code.............................
        	{
        	
        			
				switch(ev.keyboard.keycode)
            	{
            	 case ALLEGRO_KEY_ENTER:
            	 	cats[0].mojaz=0;
            	 	break;
				 case ALLEGRO_KEY_UP:
				 	if(cats[0].y - 1 > 0){
                    cats[0].y--;
                    cats[0].defence--;
                    cats[0].mojaz--;
                }
                	break;
                case ALLEGRO_KEY_DOWN:
                	if(cats[0].y + 1 < 16){	
                    cats[0].y++;
                    cats[0].defence--;
                    cats[0].mojaz--;
                }
                    break;
                case ALLEGRO_KEY_RIGHT:
                	if(cats[0].x + 1 < 16){
                    cats[0].x++;
                    cats[0].defence--;
                    cats[0].mojaz--;
                }
                    break;
                case ALLEGRO_KEY_LEFT:
                	if(cats[0].x - 1 > 0){
                	cats[0].x--;
                	cats[0].defence--;
                	cats[0].mojaz--;
                }
                	break;   
                }
            }
            
			
            else if(ev.type == ALLEGRO_EVENT_KEY_DOWN && cats[1].defence>0 &&  cats[1].mojaz>0 && cats[1].locked == 0)
        	{
        		
			
        			
				switch(ev.keyboard.keycode)
            	{
            	 case ALLEGRO_KEY_ENTER:
            	 	cats[1].mojaz=0;
            	 	break;
            	 
				 case ALLEGRO_KEY_UP:
				 	if(cats[1].y - 1 > 0){
                    cats[1].y--;
                    cats[1].defence--;
                    cats[1].mojaz--;
                }
                	break;
                case ALLEGRO_KEY_DOWN:
                	if(cats[1].y + 1 < 16){
                    cats[1].y++;
                    cats[1].defence--;
                    cats[1].mojaz--;
                }
                    break;
                case ALLEGRO_KEY_RIGHT:
                	if(cats[1].x + 1 < 16){
                    cats[1].x++;
                    cats[1].defence--;
                    cats[1].mojaz--;
                }
                    break;
                case ALLEGRO_KEY_LEFT:
                	if(cats[1].x - 1 > 0){
                	cats[1].x--;
                	cats[1].defence--;
                	cats[1].mojaz--;
                }
                	break;   
            	
            }
            
		}
		
			if(cats[0].mojaz==0 && cats[1].mojaz==0){
		   	   cats[0].mojaz=3;
               cats[1].mojaz=3;
               round++;
               dogmove(dogs);
               mousemove(mouse1);
               mousemove(mouse2);
               mousemove(mouse3);
			}
			if(cats[0].mojaz==0 && cats[1].defence==0){
		   	   cats[0].mojaz=3;
               cats[1].mojaz=3;
               round++;
               dogmove(dogs);
               mousemove(mouse1);
               mousemove(mouse2);
               mousemove(mouse3);
			}
			if(cats[0].defence==0 && cats[1].mojaz==0){
		   	   cats[0].mojaz=3;
               cats[1].mojaz=3;
               round++;
               dogmove(dogs);
               mousemove(mouse1);
               mousemove(mouse2);
               mousemove(mouse3);
			}
				eatfish(cats,fishes);
				fightcat(cats);
				fightdogcat(cats,dogs);
				eat_shokolat(cats,shokolats);
					
			ShowMap();
            al_draw_text(font1,al_map_rgb(0,0,0),400,-10,ALLEGRO_ALIGN_CENTER,"ROUND");
			al_draw_bitmap(Cat2,cats[1].x*50,cats[1].y*50,0);
			al_draw_bitmap(background,cats[0].x*50,cats[0].y*50,0);
			al_draw_bitmap(Dog1,dogs[0].x*50,dogs[0].y*50,0);
			al_draw_bitmap(Dog2,dogs[1].x*50,dogs[1].y*50,0);
			al_draw_bitmap(Dog3,dogs[2].x*50,dogs[2].y*50,0);
			al_draw_bitmap(Dog4,dogs[3].x*50,dogs[3].y*50,0);
			
			for(int i=0;i<8;i++)
				al_draw_bitmap(shokolat,shokolats[i].x*50,shokolats[i].y*50,0);
			for(int i=0;i<8;i++)
				al_draw_bitmap(mouse_1,mouse1[i].x*50,mouse1[i].y*50,0);
			for(int i=0;i<6;i++)
				al_draw_bitmap(mouse_2,mouse2[i].x*50,mouse2[i].y*50,0);
			for(int i=0;i<4;i++)
			al_draw_bitmap(mouse_3,mouse3[i].x*50,mouse3[i].y*50,0);
			
			al_draw_bitmap(fish,fishes[0].x*50,fishes[0].y*50,0);
			al_draw_bitmap(fish,fishes[1].x*50,fishes[1].y*50,0);
			al_draw_bitmap(fish,fishes[2].x*50,fishes[2].y*50,0);
			al_draw_bitmap(fish,fishes[3].x*50,fishes[3].y*50,0);
			al_draw_bitmap(fish,fishes[4].x*50,fishes[4].y*50,0);
			al_draw_bitmap(fish,fishes[5].x*50,fishes[5].y*50,0);
			al_draw_bitmap(fish,fishes[6].x*50,fishes[6].y*50,0);
			al_draw_bitmap(fish,fishes[7].x*50,fishes[7].y*50,0);
			al_draw_bitmap(fish,fishes[8].x*50,fishes[8].y*50,0);
			al_draw_bitmap(fish,fishes[9].x*50,fishes[9].y*50,0);
			for(int i=0;i<8;i++)
				al_draw_bitmap(shokolat,shokolats[i].x*50,shokolats[i].y*50,0);
			al_draw_bitmap(house,400,400,0);
			
            al_flip_display();
                    
             
			}
			
			
			
			al_destroy_bitmap(house);
			al_destroy_bitmap(fish);
			al_destroy_bitmap(Dog1);
			al_destroy_bitmap(Dog2);
			al_destroy_bitmap(Dog3);
			al_destroy_bitmap(Dog4);
			al_destroy_bitmap(background);
			al_destroy_bitmap(Cat2);
			al_destroy_display(display);

            return 0;
        }
		
		
	
	
	


	
	
	

