#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>
#include <gb/font.h>

//#include "gbt_player.h"

#include "Splash_tiles.h"
#include "Splash_map.h"

#include "Title_tiles.h"
#include "Title_map.h"

#include "Lvl_R2_tiles.h"

#include "Lvl1_R2_map.h"
#include "Lvl2_R2_map.h"
#include "Lvl3_R2_map.h"

#include "Blank_map.h"
#include "Blank_map_tiles.h"

#include "Window_tiles.h"
#include "Window_map.h"

#include "hero.h"

#define MIN(A,B) ((A)<(B)? (A):(B))

#define D_0 0x01
#define D_1 0x02
#define D_2 0x03
#define D_3 0x04
#define D_4 0x05
#define D_5 0x06
#define D_6 0x07
#define D_7 0x08
#define D_8 0x09
#define D_9 0x0A

#define L_A 0x0B
#define L_B 0x0C
#define L_C 0x0D
#define L_D 0x0E
#define L_E 0X0F
#define L_F 0x10
#define L_G 0x11
#define L_H 0x12
#define L_I 0x13
#define L_J 0x14
#define L_K 0x15
#define L_L 0x16
#define L_M 0x17
#define L_N 0X18
#define L_O 0x19
#define L_P 0x1A
#define L_Q 0x1B
#define L_R 0x1C
#define L_S 0x1D
#define L_T 0x1E
#define L_U 0x1F
#define L_V 0x20
#define L_W 0X21
#define L_X 0x22
#define L_Y 0x23
#define L_Z 0x24

uint8_t joy;

// current and old positions of the camera in pixels
int16_t camera_x = 0, camera_y = 0, old_camera_x = 0, old_camera_y = 0, next_camera_x = 0, next_camera_y = 0, camera_max_x, camera_max_y;

// current and old position of the map in tiles
uint8_t map_pos_x, map_pos_y, old_map_pos_x, old_map_pos_y;

//redraw flage, indicates that camera position was changed
uint8_t redrawFlag;

uint8_t playerPosX = 40;
uint8_t playerPosY = 32;
uint8_t playerNextPosX = 40;
uint8_t playerNextPosY = 32;
uint8_t press_Left = 0;
uint8_t press_UP = 0;
uint8_t player_Control_Enable = 1u;

const uint8_t playerSingleMoveDistance = 8;
const uint8_t centerPosition_X = 72, centerPosition_Y = 56;
const uint8_t strawberryCollectableID = 0x26;
const uint8_t keyCollectableID = 0x27;

uint8_t lvl_over = 0;

// for keeping track of the player's position in map space
uint8_t playerMapSpacePositionX = 5; 
uint8_t playerMapSpacePositionY = 4;
uint16_t mapPositionIndex;
// direction for updating map space coordinates
int8_t map_Dir_X = 0;
int8_t map_Dir_Y = 0;

uint8_t test = 0;

uint8_t mapPos_x= 0u, mapPos_y = 0u;

// tile numbers (level independent)
uint8_t strawberry_num = 0;
uint8_t keyCollectable_Num = 0;
uint8_t door_Top_ID = 58u;
uint8_t door_Bottom_ID = 60u;
uint8_t trophy_ID [] = {91u,92u,93u,94u};

uint8_t Timer_Counter = 0;
uint8_t game_over = 0;
uint8_t Digit_0 = 9u;
uint8_t Digit_1 = 9u;
uint8_t Digit_2 = 1u;

// All Level parameters
uint16_t key_location_Index[] = {4558,315,3997}; // Map space coordinates of keys on all levels
uint8_t key_location_X[] = {78,75,77};
uint8_t key_location_Y[] = {56,3,49};
uint8_t key_collected[] = {0,0,0};   // Keeps track of whether a key has been collected or not.


uint8_t current_Lvl;
uint16_t strawberry_Location_Index[9]; // Map space coordinates of collectables
uint8_t strawberry_collected[] = {0,0,0,0,0,0,0,0,0};   // Keeps track of whether a strawberry has been collected or not.
uint8_t strawberry_Location_X[9];
uint8_t strawberry_Location_Y[9];
uint8_t door_Location_X[4]; // map space of door cells
uint8_t door_Location_Y[4];
uint16_t door_Index[4];
uint8_t  door_Opened;

uint8_t fade_black_values [] = {0xE4, 0xF9, 0xFE, 0xFF};
uint8_t fade_white_values [] = {0xE4, 0x90, 0x40, 0x00};
uint8_t fadeDelay = 100;

//Individual Level Variables
//Level 1
uint16_t strawberry_location_level_1_Index[] = {3361,3381,4737,2632,1912,1110,626,2274,338}; // Map space coordinates of collectables
uint8_t strawberry_location_level_1_X[] = { 1, 21, 17, 72, 72, 70, 66, 34, 18};
uint8_t strawberry_location_level_1_Y[] = {42, 42, 59, 32, 23, 13,  7, 28, 4};
uint8_t door_X_level1[] = {28,29,28,29}; // map space of door cells
uint8_t door_Y_level1[] = {3,3,4,4};
uint16_t door_Index_level1[] = {268,269,348,349};
uint8_t door_Opened_level1 = 0;


//Level 2
uint16_t strawberry_location_level_2_Index[] = {563, 372, 1251, 1514, 1864, 3171, 3674, 4294, 4402}; 
uint8_t strawberry_location_level_2_X[] = {3, 52, 51, 74, 24, 51, 74, 54, 2};
uint8_t strawberry_location_level_2_Y[] = {7, 4, 15, 18, 23, 39, 45, 53, 55};
uint8_t door_X_level2[] = {9, 10, 9, 10}; 
uint8_t door_Y_level2[] = {52, 52, 53, 53};
uint16_t door_Index_level2[] = {4169, 4170, 4249, 4250};
uint8_t door_Opened_level2 = 0;


//Level 3

uint16_t strawberry_location_level_3_Index[] = {1201, 1229, 220, 1811, 2345, 2958, 3571, 4245, 4500}; 
uint8_t strawberry_location_level_3_X[] = {1, 29, 60, 51, 25, 78, 51, 5, 20};
uint8_t strawberry_location_level_3_Y[] = {15, 15, 2, 22, 29, 36, 44, 53, 56}; 
uint8_t door_X_level3[] = {74, 75, 74, 75}; 
uint8_t door_Y_level3[] = {4, 4, 5, 5};
uint16_t door_Index_level3[] = {394, 395, 474, 475};
uint8_t door_Opened_level3 = 0;


uint8_t animationFrame = 0; // For changing frame during animation in SetActionSprite();
 
void SplashScreen();
void TitleScreen();
void WinScreen(uint8_t stageBeat);
void GameOverScreen();
void fade_Out_Black();
void fade_In_Black();
void fade_In_White();
void fade_Out_White();

void Update_HUD_Time();
void Set_Camera(unsigned char BK_map[], uint8_t BK_mapWidth, uint8_t BK_mapHeight);
void Redraw_Blank(uint8_t BK_mapWidth); // Redraws a cell blank if collectable is collected
void Setup_Display(unsigned char BK_map[], uint8_t BK_mapWidth);
void Setup_Sprites();
void Move_Sprites(int8_t xLoc, int8_t yLoc);
void SetStandingSprite(int8_t direction_X, int8_t direction_Y);
void SetActionSprite(int8_t direction_X, int8_t direction_Y);
void UseKey();
void EnableSound();

void Player_Control(unsigned char BK_map[], uint8_t BK_mapWidth, uint8_t Bk_mapHeight);
void Update_Player_Position();
void Update_Camera_Pan_Movement();  
void Update_Collectable_HUD();

void Level_One();
void Level_Two();
void Level_Three();
void Level_Four();
void Level_Five();

void Update_Player_Map_Space_Coordinate( /*int8_t xPosAddition, int8_t yPosAddition*/);
void CollectItem(uint8_t cellIndex_X, uint8_t cellIndex_Y, uint8_t BK_mapWidth);
void CollectKey(uint8_t cellIndex_X, uint8_t cellIndex_Y, uint8_t Bk_mapWidth);
void SetMapTileBlank(uint8_t cellIndex_X, uint8_t cellIndex_Y);
void End_Level();
uint8_t Can_Player_Move(int8_t moveToCellX, int8_t moveToCellY, unsigned char BK_map[], uint8_t BK_mapWidth, uint8_t BK_mapHeight);
void TestMethod();

void DoorOpenSound();
void CollectStrawberrySound();
void CollectKeySound();
void LevelFinishSound();
void WalkSound();
void DyingSound();
void Game();
void cpyArray(uint16_t destinationArray [], uint16_t sourceArray [], uint16_t sizeOfArray );
void Reset_Level_Parameters();
void Reset_Game();
void TestButtons();

void Reset_Level_Parameters(){

for (uint8_t i = 0; i< 9; i++){
    strawberry_collected[i] = 0;
}

camera_x = 0; 
camera_y = 0;
old_camera_x = 0;
old_camera_y = 0;
next_camera_x = 0;
next_camera_y = 0;

map_pos_x = 0;
map_pos_y = 0;
old_map_pos_x = 0; 
old_map_pos_y = 0;


playerPosX = 40;
playerPosY = 32;
playerNextPosX = 40;
playerNextPosY = 32;
press_Left = 0;
press_UP = 0;
player_Control_Enable = 1u;

lvl_over = 0;

playerMapSpacePositionX = 5; 
playerMapSpacePositionY = 4;

map_Dir_X = 0;
map_Dir_Y = 0;

mapPos_x= 0u;
mapPos_y = 0u;

Digit_0 = 9u;
Digit_1 = 9u;
Digit_2 = 1u;

}

void TestButtons(){
    enable_interrupts();
    joy = joypad();
    

    while (1){
        if (joy & J_A){
        DyingSound();
        }
        wait_vbl_done();
    }
    
}

int main(){
    EnableSound();
    Game(); 
    return 0;   
}

void Game(){

    while(TRUE){
        SplashScreen();
        TitleScreen();
        
        Level_One();
        WinScreen(1);
        
        Level_Two();
        WinScreen(2);
        
        Level_Three(); 
        WinScreen(3);
        Reset_Game();
    }
}

void SplashScreen(){
    
    BGP_REG = 0x00; //Set all pixels to white

    DISPLAY_OFF;
    SHOW_BKG;

    set_bkg_data(0, 127, Splash_tiles);
    set_bkg_tiles(0,0,20,18, Splash_map);
    
    DISPLAY_ON;
    fade_In_White();

    delay(1200);

    fade_Out_Black();

    HIDE_BKG;
    DISPLAY_OFF;
}

void WinScreen(uint8_t stageBeat){
    uint8_t t = 0; // Adjust 'press start' text for game completion screen
    fade_In_White();
    //printf("%d", stageBeat);
    //set_bkg_tiles(0,0,20,18,0x00);
    move_win(0,0);

    for (uint8_t j = 0; j<18; j++){
        for (uint8_t i = 0; i<20; i++){
            set_win_tile_xy(i,j, 0x00);
        }
    }
    /*
    //checkered strawberry border
    uint8_t checkered_Pattern_Horizontal = 0;
    //uint8_t checkered_Pattern_Vertical = 0;

    for (uint8_t k = 0; k<18; k++){
        for (uint8_t l = 0; l<21; l++){
            if (k == 0 || k == 17 || (l > 0 & l <3)|| l>18){
                set_win_tile_xy (l, k, 0x26);
            } 
        }
    }
    */

    //Border
    set_win_tile_xy (5, 2, 0x53);  // top left corner
    set_win_tile_xy (16, 2, 0x55);  // top right corner
    set_win_tile_xy (5, 12, 0x54);  // bottom left corner
    set_win_tile_xy (16, 12, 0x56);  // bottom right corner

    set_win_tile_xy (5, 3, 0x57);  // left side of border
    set_win_tile_xy (5, 4, 0x57);
    set_win_tile_xy (5, 5, 0x57);
    set_win_tile_xy (5, 6, 0x57);
    set_win_tile_xy (5, 7, 0x57);
    set_win_tile_xy (5, 8, 0x57);
    set_win_tile_xy (5, 9, 0x57);
    set_win_tile_xy (5, 10, 0x57);
    set_win_tile_xy (5, 11, 0x57);

    set_win_tile_xy (16, 3, 0x59);  // right side of border
    set_win_tile_xy (16, 4, 0x59);
    set_win_tile_xy (16, 5, 0x59);
    set_win_tile_xy (16, 6, 0x59);
    set_win_tile_xy (16, 7, 0x59);
    set_win_tile_xy (16, 8, 0x59);
    set_win_tile_xy (16, 9, 0x59);
    set_win_tile_xy (16, 10, 0x59);
    set_win_tile_xy (16, 11, 0x59);

    set_win_tile_xy (6, 2, 0x5A);  // top side of border
    set_win_tile_xy (7, 2, 0x5A);
    set_win_tile_xy (8, 2, 0x5A);
    set_win_tile_xy (9, 2, 0x5A);
    set_win_tile_xy (10, 2, 0x5A);
    set_win_tile_xy (11, 2, 0x5A);
    set_win_tile_xy (12, 2, 0x5A);
    set_win_tile_xy (13, 2, 0x5A);
    set_win_tile_xy (14, 2, 0x5A);
    set_win_tile_xy (15, 2, 0x5A);

    set_win_tile_xy (6, 12, 0x58);  // bottom side of border
    set_win_tile_xy (7, 12, 0x58);  
    set_win_tile_xy (8, 12, 0x58);  
    set_win_tile_xy (9, 12, 0x58);  
    set_win_tile_xy (10, 12, 0x58);  
    set_win_tile_xy (11, 12, 0x58);  
    set_win_tile_xy (12, 12, 0x58);  
    set_win_tile_xy (13, 12, 0x58); 
    set_win_tile_xy (14, 12, 0x58);
    set_win_tile_xy (15, 12, 0x58); 


    // Trophy image
    set_win_tile_xy (10, 3, 0x5B);
    set_win_tile_xy (11, 3, 0x5C);
    set_win_tile_xy (10, 4, 0x5D);
    set_win_tile_xy (11, 4, 0x5E);
    
    //Text
    set_win_tile_xy (7, 6, L_C);
    set_win_tile_xy (8, 6, L_O);
    set_win_tile_xy (9, 6, L_N);
    set_win_tile_xy (10, 6, L_G);
    set_win_tile_xy (11, 6, L_R);
    set_win_tile_xy (12, 6, L_A);
    set_win_tile_xy (13, 6, L_T);
    set_win_tile_xy (14, 6, L_S);

    set_win_tile_xy (7, 8, L_Y);
    set_win_tile_xy (8, 8, L_O);
    set_win_tile_xy (9, 8, L_U);

    set_win_tile_xy (11, 8, L_B);
    set_win_tile_xy (12, 8, L_E);
    set_win_tile_xy (13, 8, L_A);
    set_win_tile_xy (14, 8, L_T);

    set_win_tile_xy (7, 10, L_L);
    set_win_tile_xy (8, 10, L_E);
    set_win_tile_xy (9, 10, L_V);
    set_win_tile_xy (10, 10, L_E);
    set_win_tile_xy (11, 10, L_L);

    if (stageBeat == 1){
        set_win_tile_xy (14, 10, D_1);
    } else if (stageBeat == 2){
        set_win_tile_xy (14, 10, D_2);
    } else {
        set_win_tile_xy (7, 10, L_T);
        set_win_tile_xy (8, 10, L_H);
        set_win_tile_xy (9, 10, L_E);
        set_win_tile_xy (10, 10, 0x00);
        set_win_tile_xy (11, 10, L_G);
        set_win_tile_xy (12, 10, L_A);
        set_win_tile_xy (13, 10, L_M);
        set_win_tile_xy (14, 10, L_E);

        for (uint8_t y = 0; y<13; y++){
            set_win_tile_xy (5+y, 12, 0x00);
        }
        set_win_tile_xy (9, 12, 0x26);
        // set strawberries collected on cells 9 & 10
        set_win_tile_xy (10, 12, L_O);
        set_win_tile_xy (11, 12, L_F);
        set_win_tile_xy (13, 12, D_2);
        set_win_tile_xy (14, 12, D_7);

        set_win_tile_xy (5, 12, 0x57); // Extra length sides
        set_win_tile_xy (16, 12, 0x59);

        set_win_tile_xy (5, 13, 0x54);  // bottom left corner
        set_win_tile_xy (16, 13, 0x56);  // bottom right corner

        set_win_tile_xy (6, 13, 0x58);  // bottom side of border
        set_win_tile_xy (7, 13, 0x58);  
        set_win_tile_xy (8, 13, 0x58);  
        set_win_tile_xy (9, 13, 0x58);  
        set_win_tile_xy (10, 13, 0x58);  
        set_win_tile_xy (11, 13, 0x58);  
        set_win_tile_xy (12, 13, 0x58);  
        set_win_tile_xy (13, 13, 0x58); 
        set_win_tile_xy (14, 13, 0x58);
        set_win_tile_xy (15, 13, 0x58);
        
        // Sets player score
        if (strawberry_num < 10){
            set_win_tile_xy (7, 12, 1);
            set_win_tile_xy (8, 12, strawberry_num + 1);

        } else if (strawberry_num < 20){
            set_win_tile_xy (7, 12, 0x02);
            set_win_tile_xy (8, 12, (strawberry_num - 10) + 1);

        } else {
            set_win_tile_xy (7, 12, 0x03);
            set_win_tile_xy (8, 12, (strawberry_num - 20) + 1);
        }

        if (strawberry_num == 27){
            // Trophy image
            set_win_tile_xy (7, 3, 0x5B);
            set_win_tile_xy (8, 3, 0x5C);
            set_win_tile_xy (7, 4, 0x5D);
            set_win_tile_xy (8, 4, 0x5E);

            set_win_tile_xy (13, 3, 0x5B);
            set_win_tile_xy (14, 3, 0x5C);
            set_win_tile_xy (13, 4, 0x5D);
            set_win_tile_xy (14, 4, 0x5E);
        }

        t = 1; // move 'Press Start' down one unit.

    }

    SHOW_WIN;
    SHOW_BKG;

    uint8_t start_game = 0;
    uint8_t flash_counter = 0;

    for (uint8_t m = 0; m<20; m++){
        wait_vbl_done();
    }

    while (start_game == 0){

        if (flash_counter < 30){
            //Set 'press start tiles blank'
            set_win_tile_xy (5, 14+t, 0x00);
            set_win_tile_xy (6, 14+t, 0x00);
            set_win_tile_xy (7, 14+t, 0x00);
            set_win_tile_xy (8, 14+t, 0x00);
            set_win_tile_xy (9, 14+t, 0x00);
            set_win_tile_xy (12, 14+t, 0x00);
            set_win_tile_xy (13, 14+t, 0x00);
            set_win_tile_xy (14, 14+t, 0x00);
            set_win_tile_xy (15, 14+t, 0x00);
            set_win_tile_xy (16, 14+t, 0x00);

        } else if (flash_counter < 70){
            set_win_tile_xy (5, 14+t, L_P);
            set_win_tile_xy (6, 14+t, L_R);
            set_win_tile_xy (7, 14+t, L_E);
            set_win_tile_xy (8, 14+t, L_S);
            set_win_tile_xy (9, 14+t, L_S);

            set_win_tile_xy (12, 14+t, L_S);
            set_win_tile_xy (13, 14+t, L_T);
            set_win_tile_xy (14, 14+t, L_A);
            set_win_tile_xy (15, 14+t, L_R);
            set_win_tile_xy (16, 14+t, L_T); 
        } else {
            flash_counter = 0;
        }
        flash_counter++;
        joy = joypad();
        if (joy & J_START){
            start_game = 1;
        }
        wait_vbl_done();
    }   
    fade_Out_White();
    HIDE_WIN;
    HIDE_BKG;
}

void GameOverScreen(){
    
    move_win(0,0);
    // Set screen Blank
    for (uint8_t i = 0; i<18; i++){
        for (uint8_t j = 0; j<20; j++){
            set_win_tile_xy (j, i, 0x00);
        }
    }

    set_win_tile_xy (6, 9, L_G);
    set_win_tile_xy (7, 9, L_A);
    set_win_tile_xy (8, 9, L_M);
    set_win_tile_xy (9, 9, L_E);
    set_win_tile_xy (11, 9, L_O);
    set_win_tile_xy (12, 9, L_V);
    set_win_tile_xy (13, 9, L_E);
    set_win_tile_xy (14, 9, L_R);

    HIDE_SPRITES;
    SHOW_WIN;
    SHOW_BKG;
    fade_In_White();

    for (uint8_t k = 0; k<200; k++){
        wait_vbl_done();
    }

    fade_Out_White();

    HIDE_BKG;
    HIDE_WIN;

    Reset_Game();
    Game();
    
}

void TitleScreen(){

    uint8_t start_game = 0;
    uint8_t flash_counter = 0; // Counter for making the 'press start' text flash
    
    SHOW_BKG;

    set_bkg_data(0,105, Title_tiles);
    set_bkg_tiles(0,0,20,18, Title_map);

    DISPLAY_ON;
    fade_In_Black();
    

    while (start_game == 0){
        joy = joypad();
        flash_counter++;

        if (joy & J_START){

            start_game = 1;
        }

        if (joy & J_A){
            DyingSound();
        }
        
        
        if (flash_counter == 40){
            for (uint8_t i = 0; i < 12; i++){
                set_bkg_tiles(4+i, 13, 1, 1, 0x00);
            }
        } else if (flash_counter == 60){
            set_bkg_data(0,105, Title_tiles);
            set_bkg_tiles(0,0,20,18, Title_map);
            flash_counter = 0;
        }  
        wait_vbl_done();
    } 
    fade_Out_White();
    HIDE_BKG;
    DISPLAY_OFF;
    delay(250);
}

void EnableSound(){
    NR52_REG = 0x80;
    NR50_REG = 0x77;
    NR51_REG = 0xFF;
}

void Level_One(){
    fade_In_White();
    Reset_Level_Parameters();

    camera_max_x = ((Lvl1_R2_mapWidth - 20) * 8);
    camera_max_y = ((Lvl1_R2_mapHeight - 18) * 8);

    //Need to reset all of the coordinates to originals

    current_Lvl = 1;
    current_Lvl--; // Iterate down one for entry into arrays


    cpyArray(strawberry_Location_Index, strawberry_location_level_1_Index, 9 );
    cpyArray(strawberry_Location_X, strawberry_location_level_1_X, 9 );
    cpyArray(strawberry_Location_Y, strawberry_location_level_1_Y, 9 );

    cpyArray(door_Location_X, door_X_level1, 4 );
    cpyArray(door_Location_Y, door_Y_level1, 4 );
    cpyArray(door_Index, door_Index_level1, 4 );
    door_Opened = door_Opened_level1;
    

    Setup_Display(Lvl1_R2_map, Lvl1_R2_mapWidth);
    Setup_Sprites();

    while(lvl_over == 0){    // Will have to pass maps as parameters
        Player_Control(Lvl1_R2_map, Lvl1_R2_mapWidth, Lvl1_R2_mapHeight);
        //TestMethod();
        Update_HUD_Time();
    }
}

void Level_Two(){
    fade_In_White();
    Reset_Level_Parameters();

    
    camera_max_x = ((Lvl2_R2_mapWidth - 20) * 8);
    camera_max_y = ((Lvl2_R2_mapHeight - 18) * 8);

    //Need to reset all of the coordinates to originals

    current_Lvl = 2;
    current_Lvl--; // Iterate down one for entry into arrays

    cpyArray(strawberry_Location_Index, strawberry_location_level_2_Index, 9 );
    cpyArray(strawberry_Location_X, strawberry_location_level_2_X, 9 );
    cpyArray(strawberry_Location_Y, strawberry_location_level_2_Y, 9 );

    cpyArray(door_Location_X, door_X_level2, 4 );
    cpyArray(door_Location_Y, door_Y_level2, 4 );
    cpyArray(door_Index, door_Index_level2, 4 );
    door_Opened = door_Opened_level2;
    

    Setup_Display(Lvl2_R2_map, Lvl2_R2_mapWidth);
    Setup_Sprites();

    while(lvl_over == 0){    
        Player_Control(Lvl2_R2_map, Lvl2_R2_mapWidth, Lvl2_R2_mapHeight);
        Update_HUD_Time();
    }
}

void Level_Three(){
    fade_In_White();
    Reset_Level_Parameters();

    camera_max_x = ((Lvl3_R2_mapWidth - 20) * 8);
    camera_max_y = ((Lvl3_R2_mapHeight - 18) * 8);

    //Need to reset all of the coordinates to originals

    current_Lvl = 3;
    current_Lvl--; // Iterate down one for entry into arrays

    cpyArray(strawberry_Location_Index, strawberry_location_level_3_Index, 9 );
    cpyArray(strawberry_Location_X, strawberry_location_level_3_X, 9 );
    cpyArray(strawberry_Location_Y, strawberry_location_level_3_Y, 9 );

    cpyArray(door_Location_X, door_X_level3, 4 );
    cpyArray(door_Location_Y, door_Y_level3, 4 );
    cpyArray(door_Index, door_Index_level3, 4 );
    door_Opened = door_Opened_level3;
    

    Setup_Display(Lvl3_R2_map, Lvl3_R2_mapWidth);
    Setup_Sprites();

    while(lvl_over == 0){    
        Player_Control(Lvl3_R2_map, Lvl3_R2_mapWidth, Lvl3_R2_mapHeight);
        Update_HUD_Time();
    }
}



void Setup_Sprites(){
    SPRITES_8x16;
    set_sprite_data(0,40, hero);

    set_sprite_tile(0,0);
    set_sprite_tile(1,2);

    Move_Sprites(playerPosX, playerPosY);

    SHOW_SPRITES;
}

void Setup_Display(unsigned char BK_map[], uint8_t BK_mapWidth){

    font_t min_font;
    font_init();
    min_font = font_load(font_min);
    font_set(min_font);

    DISPLAY_OFF;
    SHOW_BKG;
    SHOW_WIN;

    set_bkg_data(38, 57u, Lvl_R2_tiles);
    set_win_data(83,8, Window_tiles);
   //set_bkg_data(91, 4, Lvl_R2_tiles); 

    map_pos_x = map_pos_y = 0;
    old_map_pos_x = old_map_pos_y = 255;
    
    set_bkg_submap(map_pos_x, map_pos_y, 22, 20, BK_map, BK_mapWidth);

    //Set up Window
    set_win_tiles(0,0,20,3,Window_map);
    move_win(7,120);

    //Set up Collectable Values
    set_win_tile_xy(1,1,38);
    Update_Collectable_HUD();

    //Set up Key Values
    set_win_tile_xy(6,1,39);
    set_win_tile_xy(8,1,D_0);
    set_win_tile_xy(9,1,keyCollectable_Num+ 1u);

    //Set up Time Values
    set_win_tile_xy(11,1, L_T);
    set_win_tile_xy(12,1, L_I);
    set_win_tile_xy(13,1, L_M);
    set_win_tile_xy(14,1, L_E);

    set_win_tile_xy(18,1,Digit_0 + 1u);
    set_win_tile_xy(17,1,Digit_1 + 1u);
    set_win_tile_xy(16,1,Digit_2 + 1u);

    DISPLAY_ON;

    camera_x = camera_y = 0;
    old_camera_x = camera_x;
    old_camera_y = camera_y;

    redrawFlag = FALSE;

    SCX_REG = camera_x;
    SCY_REG = camera_y;

}

void Update_HUD_Time(){
    Timer_Counter++;
    if (Timer_Counter == 40){   // Will need to update this to pass slower in the game after testing is complete.
        Timer_Counter = 0;
        
        if (game_over == 0) {
            if (Digit_0 > 0) {
                Digit_0--;
            }
            else{
                Digit_0 = 9;
                if (Digit_1 > 0) Digit_1--;
                else{
                    Digit_1 = 9;
                    if (Digit_2 > 0) Digit_2--;
                    else {
                        game_over == 1;
                        GameOverScreen();
                    }
                }
            }
            set_win_tile_xy(18,1,Digit_0 + 1u);
            set_win_tile_xy(17,1,Digit_1 + 1u);
            set_win_tile_xy(16,1,Digit_2 + 1u);
        } else {
            // game over
            DyingSound();
            set_win_tile_xy(18,1,D_0);
            set_win_tile_xy(17,1,D_0);
            set_win_tile_xy(16,1,D_0);
        }  
    }
}

void Set_Camera(unsigned char BK_map[], uint8_t BK_mapWidth, uint8_t BK_mapHeight){    // update hardware scroll position
    SCY_REG = camera_y; SCX_REG = camera_x;

    // updating memory for the up or down directions of movement
    map_pos_y = (uint8_t) (camera_y >> 3u);

    if (map_pos_y != old_map_pos_y){
        if (camera_y < old_camera_y){
            set_bkg_submap(map_pos_x, map_pos_y, MIN(21u, BK_mapWidth - map_pos_x), 1, BK_map, BK_mapWidth);
            mapPos_y--;
        } else {
            if ((BK_mapHeight - 18u) > map_pos_y) 
            set_bkg_submap (map_pos_x, map_pos_y + 18u, MIN(21u, BK_mapWidth - map_pos_x), 1, BK_map, BK_mapWidth);
            mapPos_y++;
        }
        old_map_pos_y = map_pos_y;
    }

    // updating memory for the left or right directions of movement
    map_pos_x = (uint8_t)(camera_x >> 3u);

    if (map_pos_x != old_map_pos_x){
        if (camera_x < old_camera_x){
            set_bkg_submap(map_pos_x, map_pos_y, 1, MIN(19u, BK_mapHeight - map_pos_y), BK_map, BK_mapWidth);
            mapPos_x--;
        }else{
            if ((BK_mapWidth - 20u) > map_pos_x)
            set_bkg_submap(map_pos_x + 20u, map_pos_y, 1, MIN(19u, BK_mapHeight - map_pos_y), BK_map, BK_mapWidth);
            mapPos_x++;
        }
        old_map_pos_x = map_pos_x;
    }

    //set old camera position to current camera position
    old_camera_x = camera_x;
    old_camera_y = camera_y;
 
    // For each value in strawberry bool array, if value is 1, then draw over the value with 0x00 
    Redraw_Blank(BK_mapWidth);
    
}

void Redraw_Blank(uint8_t BK_mapWidth){ // Tests if the collected items are within the screen space and sets them to blank
    uint16_t map_Index_Lower_Limit = BK_mapWidth * map_pos_y + map_pos_x;   // Map space coordinate of the upper left cell of the screen
    uint16_t map_Index_Upper_Limit = BK_mapWidth * (map_pos_y + 19u) + (map_pos_x + 21u); // Map space coordinate of the lower right cell of the screen

    for (uint8_t i = 0; i < 9; i++)
    {
        if ( strawberry_collected[i] != 0){
            if(strawberry_Location_Index[i] >= map_Index_Lower_Limit){
                if (strawberry_Location_Index [i] <= map_Index_Upper_Limit){ 

                    uint8_t x_Pos = strawberry_Location_X[i];
                    uint8_t y_Pos = strawberry_Location_Y[i];

                    set_bkg_submap(x_Pos, y_Pos, 1, 1, 0x00, 1);
                    //set_bkg_tile_xy(x_Pos, y_Pos, 0x00);
                }
            }
        }
    } 

    if (key_collected[current_Lvl] != 0){
        set_bkg_submap(key_location_X[current_Lvl], key_location_Y[current_Lvl], 1, 1, 0x00, 1); // Sets single tile to blank (0x00)
        //set_bkg_tile_xy(key_location_X[current_Lvl], key_location_Y[current_Lvl], 0x00);
    }

    if ( door_Opened != 0){   // What happens when there is more than one door in the level!!!!
        for (uint8_t k = 0; k<4; k++){
            set_bkg_submap( door_Location_X[k], door_Location_Y[k], 1, 1, 0x00, 1); // Sets 4 tiles of the door blank
            //set_bkg_tile_xy(door_Location_X[k], door_Location_Y[k], 0x00);
        }
    }
}


void Move_Sprites(int8_t xLoc, int8_t yLoc){
    move_sprite(0, xLoc+8, yLoc+16);  
    move_sprite(1, xLoc+16, yLoc+16);
}


void SetStandingSprite(int8_t direction_X, int8_t direction_Y){
    if ( direction_X > 0){

        set_sprite_tile(0,33); 
        set_sprite_tile(1,35);
        
    } else if (direction_X < 0){
        set_sprite_tile(0,25); 
        set_sprite_tile(1,27);

    } else if (direction_Y > 0){
        set_sprite_tile(0,0); 
        set_sprite_tile(1,2);

    } else if (direction_Y < 0){
        set_sprite_tile(0,13); 
        set_sprite_tile(1,15);
    }
}

void SetActionSprite(int8_t direction_X, int8_t direction_Y){

    if ( direction_X > 0){
        set_sprite_tile(0, 37); 
        set_sprite_tile(1, 39);

    } else if (direction_X < 0){
        set_sprite_tile(0,29); 
        set_sprite_tile(1,31);
    }

    if (animationFrame == 0){
        if (direction_Y > 0){
            set_sprite_tile(0,4); 
            set_sprite_tile(1,6);

        } else if (direction_Y < 0){
            set_sprite_tile(0,17); 
            set_sprite_tile(1,19);
        }
        animationFrame = 1;
    } else {
        if (direction_Y > 0){
            set_sprite_tile(0,9); 
            set_sprite_tile(1,11);

        } else if (direction_Y < 0){
            set_sprite_tile(0,21); 
            set_sprite_tile(1,23);
        }
        animationFrame = 0;
    } 
}

void CollectItem(uint8_t cellIndex_X, uint8_t cellIndex_Y, uint8_t BK_mapWidth){  // collect item must compare location to strawberry location [] to get index - update bool to 1 so that 1: it doesn't get collected again, 2: Update Camera paints blank cell at that location.
    // find the map index of the cell
    uint16_t mapIndex = cellIndex_Y * BK_mapWidth + cellIndex_X;

    // compare the map index of the cell to the array of strawberries
    // for the i'th component of the array of strawberries, mark the corresponding value in the bool array as 1, so it is always drawn over with 0x00.
    // for the i'th component increase the strawberry inventory by one only once.
    for (uint8_t i = 0; i < 9; i++)
    {
        if ( strawberry_Location_Index[i] == mapIndex){
            if (strawberry_collected[i] == 0){
                CollectStrawberrySound();
                strawberry_num ++; 
                strawberry_collected[i] = 1;
            }  
        }
    }
    Update_Collectable_HUD();
    // If collected already, blank the strawberry cell out!
    Redraw_Blank(BK_mapWidth); 
}

void Update_Collectable_HUD(){
    for (uint8_t j = 1; j < 10; j++){
        if ((j*10) < strawberry_num){ 

            uint8_t remainder = strawberry_num -(j*10);

            if (remainder <= 9){
                set_win_tile_xy(3,1,j+1u);
                set_win_tile_xy(4,1, remainder + 1u);
            }
        }
    } 

    if ( strawberry_num <= 9u){
        set_win_tile_xy(4,1, strawberry_num +1u);
    }
}

void End_Level(){
    HIDE_SPRITES;
    fade_Out_White();
    HIDE_BKG;
    
    lvl_over = 1;
}

void CollectKey(uint8_t cellIndex_X, uint8_t cellIndex_Y, uint8_t BK_mapWidth){          // This needs to be built up like the strawberry!!
    // find the map index of the cell
    uint16_t mapIndex = cellIndex_Y * BK_mapWidth + cellIndex_X;
    
    // compare the map index of the cell to the array of keys
    // for the i'th component of the array of keys, mark the corresponding value in the bool array as 1, so it is always drawn over with 0x00.
    // for the i'th component increase the key inventory by one only once.
    if (key_collected[current_Lvl] == 0){
        CollectKeySound();
        keyCollectable_Num ++; 
        key_collected[current_Lvl] = 1;
    }  

    if ( keyCollectable_Num <= 9u){
        set_win_tile_xy(9,1, keyCollectable_Num +1u);
    }
    // If key collected already, blank the key cell out!
    Redraw_Blank(BK_mapWidth); 
}

void UseKey(){
    keyCollectable_Num--;
    set_win_tile_xy(9,1, keyCollectable_Num+1u);
    DoorOpenSound();
}


uint8_t Can_Player_Move(int8_t moveToCellX, int8_t moveToCellY, unsigned char BK_map[], uint8_t BK_mapWidth, uint8_t BK_mapHeight){  // moveToCellX & moveToCellY are 1,2,3... etc not multiples of 8.
    // find the cell index relative to the player's position on map
    // find the companion index ralative to the first cell
    // test these cells if it is 0x00, if it is return 1, else return 0

    uint8_t cellIndex_X = moveToCellX + playerMapSpacePositionX;
    uint8_t cellIndex_Y = moveToCellY + playerMapSpacePositionY;
    uint16_t mapPositionIndex = (BK_mapWidth * cellIndex_Y) + cellIndex_X; 

    
    // Keep Player within map boundary
    if (camera_x == 0 && playerMapSpacePositionX == 0 && moveToCellX < 0){
        return 0;
    } else if (camera_x == camera_max_x && playerMapSpacePositionX == (BK_mapWidth - 2) && moveToCellX >0){
        return 0;
    }
    if (camera_y == 0 && playerMapSpacePositionY == 0 && moveToCellY < 0){
        return 0;
    }else if (camera_y == camera_max_y && playerMapSpacePositionY == (BK_mapHeight - 5) && moveToCellY > 0){
        return 0;
    }
    

    // Check Surrounding Cells
    if ( moveToCellX != 0 ){ 
        //Check for collectable if in the next cell
        if (BK_map[mapPositionIndex] == strawberryCollectableID ){ //Check for collectable #1
            CollectItem(cellIndex_X, cellIndex_Y, BK_mapWidth);  // Need to identify exact location of strawberry, and pass to collect item.
            return 1;
        } else if (BK_map[mapPositionIndex + BK_mapWidth] == strawberryCollectableID) {  
            CollectItem(cellIndex_X, cellIndex_Y + 1, BK_mapWidth);
            return 1;
        } else if (BK_map[mapPositionIndex] == keyCollectableID ){ //Check for collectable #2
            CollectKey(cellIndex_X, cellIndex_Y, BK_mapWidth);            
            return 1;
        } else if (BK_map[mapPositionIndex + BK_mapWidth] == keyCollectableID){
            CollectKey(cellIndex_X, cellIndex_Y + 1, BK_mapWidth);        
            return 1;
        }

        for (uint8_t i = 0; i <4; i++){
            if (BK_map[mapPositionIndex] == trophy_ID [i] || BK_map[mapPositionIndex + BK_mapWidth] == trophy_ID [i]){
                End_Level();
            }
        }

        //Check for blank walkable ground  
        if (BK_map[mapPositionIndex] == 0x00 && BK_map[mapPositionIndex + BK_mapWidth] == 0x00){  
            return 1;
        } else {
            return 0;
        }
        
    } else if ( moveToCellY != 0){   // Need to be careful - what if collectable was right beside object????? BUG
        //Check for collectable if in the next cell
        
        if (BK_map[mapPositionIndex] == strawberryCollectableID ){ //Check for collectable #1
            CollectItem(cellIndex_X, cellIndex_Y, BK_mapWidth);
            return 1;
        } else if (BK_map[mapPositionIndex + 1] == strawberryCollectableID) {
            CollectItem(cellIndex_X + 1, cellIndex_Y, BK_mapWidth);
            return 1;
        } else if (BK_map[mapPositionIndex] == keyCollectableID ){ //Check for collectable #2
            CollectKey(cellIndex_X, cellIndex_Y, BK_mapHeight);  //////////////////////////////////////////Will need to update when making multiple levels!!!!!!!
            return 1;
        } else if (BK_map[mapPositionIndex + 1] == keyCollectableID){
            CollectKey(cellIndex_X + 1, cellIndex_Y, BK_mapWidth);  //////////////////////////////////////////Will need to update when making multiple levels!!!!!!!
            return 1;
        } else if (BK_map[mapPositionIndex] == door_Top_ID || BK_map[mapPositionIndex] == door_Bottom_ID ) {
            if (door_Opened != 0){
                return 1;
            }
            if (keyCollectable_Num >= 1){ 
                UseKey();
                door_Opened = 1;
                DoorOpenSound();
                Redraw_Blank(BK_mapWidth);
                return 1;
            } else return 0;
        }

        for (uint8_t i = 0; i <4; i++){
            if (BK_map[mapPositionIndex] == trophy_ID [i] || BK_map[mapPositionIndex + 1u] == trophy_ID [i]){
                End_Level();
            }
        } 

        if (BK_map[mapPositionIndex] == 0x00 && BK_map[mapPositionIndex + 1] == 0x00){
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}

void Update_Player_Map_Space_Coordinate(){ 
    //Updates the map position for the character
    playerMapSpacePositionX = (playerPosX + camera_x) >>3u;
    playerMapSpacePositionY = (playerPosY + camera_y) >>3u;
}

uint8_t Abs_Value_difference (int8_t nextPos, int8_t Pos){ // return abs value of first input minus the second
    uint8_t abs_difference;
    if ((nextPos - Pos) >=0){
        return (abs_difference = nextPos - Pos);
    } else {
        return (abs_difference = Pos - nextPos);
    }
}

//Gradually moves player to position & adjusts player position in space updating toward the goal of the next position each frame
void Update_Player_Position(){  
    
    // Updating player movement
    // determine move distance for X direction
    uint8_t abs_difference_POS_X = Abs_Value_difference(playerNextPosX, playerPosX);
    uint8_t abs_difference_POS_Y = Abs_Value_difference(playerNextPosY, playerPosY);
    uint8_t abs_difference_CAM_X = Abs_Value_difference(next_camera_x, camera_x);
    uint8_t abs_difference_CAM_Y = Abs_Value_difference(next_camera_y, camera_y);


    // Update position (move) each frame independently in either x or y direction depending on abs_difference value
    if (abs_difference_POS_X > 0){
        //Animation and Sounds
        if (abs_difference_POS_X == 8){
            WalkSound();
            SetActionSprite(playerNextPosX - playerPosX, 0);

        } else if (abs_difference_POS_X == 3){
            SetStandingSprite(playerNextPosX - playerPosX, 0);
        }

        // Updating Position per frame
        playerPosX += (playerNextPosX - playerPosX) < 0? -1: 1 ;
        Move_Sprites(playerPosX, playerPosY);

    } else if (abs_difference_POS_Y > 0){
        if (abs_difference_POS_Y == 8){
            WalkSound();
            SetActionSprite(0, playerNextPosY - playerPosY);

        } else if (abs_difference_POS_Y == 3){
            SetStandingSprite(0, playerNextPosY - playerPosY);
        }

        playerPosY += (playerNextPosY - playerPosY) < 0? -1: 1 ;
        Move_Sprites(playerPosX, playerPosY); 

    } else if (abs_difference_CAM_X > 0){ // Update position (move) each frame independently in either x or y direction depending on abs_difference value
        if (abs_difference_CAM_X == 8){
            WalkSound();
            SetActionSprite(next_camera_x - camera_x, 0);
        } else if (abs_difference_CAM_X == 3){
            SetStandingSprite(next_camera_x - camera_x, 0);
        }

        camera_x += (next_camera_x - camera_x) < 0? -1: 1 ;
        SCX_REG = camera_x; // move camera with hardware

    } else if (abs_difference_CAM_Y > 0){
        // Animation and Sounds
        if (abs_difference_CAM_Y == 8){
            WalkSound();
            SetActionSprite(0, next_camera_y - camera_y);

        } else if (abs_difference_CAM_Y == 3){
            SetStandingSprite(0, next_camera_y - camera_y);
        }
        
        camera_y += (next_camera_y - camera_y) < 0? -1: 1 ;
        SCY_REG = camera_y;
    }
    
     // Release movement and allow player to control again 
    if (abs_difference_POS_X == 0 & abs_difference_POS_Y == 0 & abs_difference_CAM_X == 0 & abs_difference_CAM_Y == 0 ) {
        player_Control_Enable = 1;
        Update_Player_Map_Space_Coordinate(); 
    }
}

// Controls the camera snap on the edges as well as handling input
void Player_Control(unsigned char BK_map[], uint8_t BK_mapWidth, uint8_t BK_mapHeight){  
    joy = joypad(); // already done on title screen 

    /*
    if (joy & J_A){ 
        DoorOpenSound(); 
        
    } else if (joy & J_B){
        CollectStrawberrySound();
    }
    */

    if (player_Control_Enable == 1) {
        if (joy & J_RIGHT){
            if (Can_Player_Move(2,0, BK_map, BK_mapWidth, BK_mapHeight) != 0){ // make sure the cells two cells away is blank (as player is 2 cells wide)
                player_Control_Enable = 0;
                if (camera_x == 0){
                    if (playerPosX >= centerPosition_X){
                        // camera movement
                        next_camera_x = camera_x + playerSingleMoveDistance;
                    } else {
                        // player movement
                        playerNextPosX = playerPosX + playerSingleMoveDistance;  
                    }

                } else if (camera_x == camera_max_x){
                    if (playerPosX >= centerPosition_X){
                        playerNextPosX = playerPosX + playerSingleMoveDistance;
                        
                    } else if (playerPosX < centerPosition_X){
                        next_camera_x = camera_x + playerSingleMoveDistance;
                    } 
                } else {
                    next_camera_x = camera_x + playerSingleMoveDistance;
                }
            }
        } else if (joy & J_LEFT){
            if (Can_Player_Move(-1,0, BK_map, BK_mapWidth, BK_mapHeight)){ //check if can move left 1 cell
                player_Control_Enable = 0;
                if (camera_x == 0){
                    if (playerPosX <= centerPosition_X){
                        playerNextPosX = playerPosX - playerSingleMoveDistance;
                    } else {
                        next_camera_x = camera_x - playerSingleMoveDistance;
                    }

                } else if (camera_x == camera_max_x){
                    if (playerPosX <= centerPosition_X){
                        next_camera_x = camera_x - playerSingleMoveDistance;
                        
                    } else {
                        playerNextPosX = playerPosX - playerSingleMoveDistance;
                    }

                } else {
                    next_camera_x = camera_x - playerSingleMoveDistance;
                }
            }   
        } 
        
        if (joy & J_UP){
            if (Can_Player_Move(0,-1, BK_map, BK_mapWidth, BK_mapHeight)){ // check if can move up 1 cell
                player_Control_Enable = 0;
                if (camera_y == 0){
                    if (playerPosY <= centerPosition_Y){
                        playerNextPosY = playerPosY - playerSingleMoveDistance;
                    } else {
                        next_camera_y = camera_y - playerSingleMoveDistance;
                    }
                } else if (camera_y == camera_max_y){
                    if (playerPosY <= centerPosition_Y){ 
                        next_camera_y = camera_y - playerSingleMoveDistance;

                    } else {
                        playerNextPosY = playerPosY - playerSingleMoveDistance;
                    }
                } else {
                    next_camera_y = camera_y - playerSingleMoveDistance;
                }
            }           
        }else if (joy & J_DOWN){
            if (Can_Player_Move(0,2, BK_map, BK_mapWidth, BK_mapHeight)){ // check if 2 cells down is blank (player height = 2 cells)
                player_Control_Enable = 0;
                if (camera_y == 0){
                    if (playerPosY >= centerPosition_Y){
                        next_camera_y = camera_y + playerSingleMoveDistance; 
                    } else {
                        playerNextPosY = playerPosY + playerSingleMoveDistance;
                    }
                } else if (camera_y == camera_max_y){
                    if (playerPosY >= centerPosition_Y){
                        playerNextPosY = playerPosY + playerSingleMoveDistance;
                        
                    } else {
                        next_camera_y = camera_y + playerSingleMoveDistance;
                    }
                } else {
                    next_camera_y = camera_y + playerSingleMoveDistance; 
                }
            } 
        }   
    }
    
    if (player_Control_Enable == 0){
        Update_Player_Position();
        redrawFlag = TRUE;
    }
    
    
    if (redrawFlag){
        wait_vbl_done();
        Set_Camera( BK_map, BK_mapWidth, BK_mapHeight);
        redrawFlag = FALSE;
    } else wait_vbl_done();   
}

//Sounds
void DoorOpenSound(){
    //SoundMode_1
    NR10_REG = 0x00;
    NR11_REG = 0x87;
    NR12_REG = 0x86;
    NR13_REG = 0x9F;
    NR14_REG = 0x86;
}
void CollectKeySound(){
    
    NR21_REG = 0x40;
    NR22_REG = 0xA3;
    NR23_REG = 0xEF;
    NR24_REG = 0x86;

    delay(50);
}
void CollectStrawberrySound(){
    
    NR10_REG = 0x45;
    NR11_REG = 0x81;
    NR12_REG = 0x4B;
    NR13_REG = 0x73;
    NR14_REG = 0x86;

    delay(50);
}
void LevelFinishSound(){
    //SoundMode_2
    NR21_REG = 0x0D;
    NR22_REG = 0xC7;
    NR23_REG = 0xFA;
    NR24_REG = 0x86;
}
void WalkSound(){
    NR10_REG = 0x23;
    NR11_REG = 0x81;
    NR12_REG = 0x4B;
    NR13_REG = 0x59;
    NR14_REG = 0x86;
}
void DyingSound(){
    //SoundMode_4
    NR10_REG = 0x7F;
    NR11_REG = 0xFF;
    NR12_REG = 0x4D;
    NR13_REG = 0x72;
    NR14_REG = 0x86;

    delay(650);

    NR41_REG = 0x39;
    NR42_REG = 0xF2;
    NR43_REG = 0x98;
    NR44_REG = 0x80;

    //delay(200);

    NR10_REG = 0x79;
    NR11_REG = 0x43;
    NR12_REG = 0x43;
    NR13_REG = 0x73;
    NR14_REG = 0x86;
}


void fade_Out_Black(){
    for (uint8_t i = 0; i<4; i++){
        BGP_REG = fade_black_values[i];
        delay(fadeDelay);
    }
}
void fade_In_Black(){
    for (int8_t i = 3; i>=0; i--){
        BGP_REG = fade_black_values[i];
        delay(fadeDelay);
    }
}
void fade_Out_White(){
    for (uint8_t i = 0; i<4; i++){
        BGP_REG = fade_white_values[i];
        delay(fadeDelay);
    }
}
void fade_In_White(){
    for (int8_t i = 3; i>=0; i--){
        BGP_REG = fade_white_values[i];
        delay(fadeDelay);
    }
}

void cpyArray(uint16_t destinationArray [], uint16_t sourceArray [], uint16_t sizeOfArray ){
    for (uint16_t i = 0; i< sizeOfArray; i++){
        destinationArray[i] = sourceArray[i];
    }
}

void cpyCharArray(char destinationArray [], char sourceArray [], uint32_t sizeOfArray ){
    for (uint32_t i = 0; i< sizeOfArray; i++){
        destinationArray[i] = sourceArray[i];
    }
}

void Reset_Game(){
    SCY_REG = 0;
    SCX_REG = 0;

    game_over = 0;

    strawberry_num = 0;
    keyCollectable_Num = 0;

    Reset_Level_Parameters();

    for (uint8_t j = 0; j<3; j++){
        key_collected[j] = 0;
    }

}