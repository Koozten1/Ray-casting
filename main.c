#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <math.h> 
#include <stdio.h> 


#define HIGHT  16
#define WIDTH 16

int is_wall(int *map, int x, int y);
double new_coordination(double *x, double *y, double rotation);
double degrees_to_radians(double degrees);

int main(){

    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, true);


    int map_x = 16;
    int map_y = 16;

    double fDeph = 9;
    double step_roat = (double)60 / 160; 
    double st_angle;


    float rotation = 0;
    float pos_x = 8;
    float pos_y = 8;
    
    char key;

    int map[16][16] = { {1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1},
                        {1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,2, 0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1},
                        {1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1}};


    while (1){
        key = getch();
        if(key == 'A' || key == 'a'){
            rotation += 0.5;
        }

        else if(key == 'D' || key == 'd'){
            rotation -= 0.5;
        }

        else if(key == 'w' || key == 'W'){
            
            pos_x +=  (float)sin(degrees_to_radians(rotation));
            pos_y += (float)cos(degrees_to_radians(rotation));
            if(!is_wall(*map, (int)pos_x, (int)pos_y)){
                pos_x -=  (float)sin(degrees_to_radians(rotation));
                pos_y -= (float)cos(degrees_to_radians(rotation));
            }
        }

        else if(key == 'S' || key == 's'){
            pos_x -=  (float)sin(degrees_to_radians(rotation));
            pos_y -= (float)cos(degrees_to_radians(rotation));
            if(!is_wall(*map, (int)pos_x, (int)pos_y)){
                pos_x +=  (float)sin(degrees_to_radians(rotation)) ;
                pos_y += (float)cos(degrees_to_radians(rotation));
            }
        
        }

        st_angle = (int)rotation % 360 - (60 / 2);

        clear();
        printw("x=%f y=%f rot=%f \n", pos_x, pos_y, rotation);
        



        for(int y = 0; y < 16; y++){
            for(int x = 0; x < 16; x++){

                if((int)pos_x == x && (int)pos_y == y){
                    printw("@");
                }

                else if(map[y][x] == 1){
                    printw("1");
                }

                else{
                    printw(" ");
                }
            }   

            printw("\n");
        }

        refresh();
        usleep(10000);
    }


    return 0;


}

double new_coordination(double *x, double *y, double rotation){
    *x  += (double)sin(degrees_to_radians(rotation));
    *y += (double)cos(degrees_to_radians(rotation));
}

int is_wall(int *map, int x, int y){
    int result = 1;
    if(*(map + y * 16 + x) == 1 || x % WIDTH == 0 || y %  HIGHT  == 0){
        result = 0;
    }
    return result; 
}

double degrees_to_radians(double degrees){ 
        return degrees / 180.0 * M_PI; 
} 


