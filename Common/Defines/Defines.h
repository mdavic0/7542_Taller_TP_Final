#ifndef COMMON_DEFINES_H_
#define COMMONO_DEFINES_H_

#define PATH "assets/config/config.yaml"
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGTH 768

#define FRAME_RATE 60
#define SIZE_QUEUE 256

#define CREATE_MENU 1
#define JOIN_MENU 2

// Animation SDL
#define SIZE_FRAME 128
#define SIZE_SPRITE_X 64
#define SIZE_SPRITE_Y 68
#define SPEED_IDLE 150
#define SPEED_RUN 100

#define CREATE_CODE 0x01
#define JOIN_CODE 0x02
#define MOVE_CODE 0x03
#define STOP_MOVE_CODE 0x04
#define PLAYING_CODE 0x05
#define START_CODE 0x06
#define LEAVE_CODE 0x07

#define IDF_CODE 0x01
#define P90_CODE 0x02
#define SCOUT_CODE 0x03

#define SURVIVAL_CODE 0x01
#define CLEAR_ZONE_CODE 0x02

#define RIGHT_CODE 0x01
#define LEFT_CODE 0x02
#define UP_CODE 0x03
#define DOWN_CODE 0x04

#define STATE_IDLE 0x00
#define STATE_MOVING 0x01
#define STATE_ATACK 0x02
#define STATE_INJURE 0x03
#define STATE_HABILITY 0x04

#endif