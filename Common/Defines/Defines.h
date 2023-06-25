#ifndef COMMON_DEFINES_H_
#define COMMON_DEFINES_H_

#define PATH "assets/config/config.yaml"
#define MAP_WIDTH 1920 * 2
#define MAP_HEIGTH 1080

#define FRAME_RATE 60
#define SIZE_QUEUE 256

#define CREATE_MENU 1
#define JOIN_MENU 2

// Paths assets
#define PATH_OBSTACLES "assets/images/sdl/obstacles/"
#define PATH_MAPS "assets/images/sdl/maps/"
#define PATH_ENEMIES "assets/images/sdl/enemies/"
// Path Music
#define PATH_MUSIC_LAUNCHER "../assets/music/launcher/"
#define PATH_MUSIC_LOBBY "assets/music/sdl/sound/lobby.wav"
#define PATH_MUSIC_GAME "assets/music/sdl/sound/game.wav"
#define PATH_MUSIC_OPERATOR "assets/music/sdl/units/"
#define PATH_MUSIC_ENEMY "assets/music/sdl/enemies/"

// Animation SDL
#define SIZE_FRAME 128
#define SIZE_FRAME_ENEMY 96
#define SIZE_SPRITE_X 64
#define SIZE_SPRITE_Y 68
#define SIZE_SPRITE_MAP_X 1920
#define SIZE_SPRITE_MAP_Y 1080
#define SPEED_IDLE 150
#define SPEED_RUN 120
#define SPEED_ATACK 200
#define SPEED_INJURE 110
#define SPEED_RECHARGE 290
#define SPEED_SKILL 190
#define SPEED_DEAD 120
#define COLOR_WHITE {255, 255, 255, 255}
#define SIZE_SPRITE_64 64
#define SIZE_SPRITE_32 32
#define SPRITE_BG_W 309
#define SPRITE_BG_H 188
#define HEALTH_BG_W 448
#define HEALTH_FILL_W 412
#define HEALTH_FILL_H 25
#define WIDTH_SCREEN_INIT 1440

// Protocol Code
#define CREATE_CODE 0x01
#define JOIN_CODE 0x02
#define START_CODE 0x03
#define PLAYING_CODE 0x04
#define MOVE_CODE 0x05
#define STOP_MOVE_CODE 0x06
#define THROW_SMOKE_CODE 0x07
#define STOP_SMOKE_CODE 0x08
#define THROW_GRENADE_CODE 0x09
#define STOP_GRENADE_CODE 0x10
#define BLITZ_ATACK_CODE 0x11
#define SHOOT_CODE 0x12
#define STOP_SHOOT_CODE 0x13
#define RECHARGE_CODE 0x14
#define REANIMATE_CODE 0x15
#define STOP_REANIMATE_CODE 0x16
#define LEAVE_CODE 0x17
#define END_CODE 0x18
#define STATS_CODE 0x19
#define CHEAT_FINISH_GAME_CODE 0x20
#define CHEAT_INFINITE_MUNITION_CODE 0x21
#define CHEAT_MORE_VELOCITY_CODE 0x22
#define CHEAT_KILL_ENEMIES_CODE 0x23
#define CHEAT_INFINITE_HEALTH_CODE 0x24

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
#define STATE_RECHARGE 0x05

#define INFECTED_ZOMBIE 0x00
#define INFECTED_JUMPER 0x01
#define INFECTED_WITCH 0x02
#define INFECTED_SPEAR 0x03
#define INFECTED_VENOM 0x04

#define DIFFICULTY_IDLE 0x00
#define DIFFICULTY_EASY 0x01
#define DIFFICULTY_NORMAL 0x02
#define DIFFICULTY_HARD 0x03
#define DIFFICULTY_GOD 0x04

// Server
#define JOIN_OK 0x00
#define JOIN_FAILED 0X01

#define INITIAL_PLAYERS_AMOUNT 0x00
#define INITIAL_PLAYER_ID 0x00
#define INITIAL_INFECTED_ID 50
#define INITIAL_OBSTACLE_ID 240

#define OBSTACLE_TIRE 0x00
#define OBSTACLE_CRATER 0x01

#define CLOSE_DISTANCE 50
#define HOSTILE_RANGE 500

#define QUEUE_MAX_SIZE 1000
#define MAX_ITERATIONS 10

#define TIRE_WIDTH 30
#define TIRE_HEIGHT 50
#define CRATER_WIDTH 60
#define CRATER_HEIGHT 60

#define PLAYER_WIDTH 20
#define PLAYER_HEIGHT 20

#define FELL_DOWN_LIMIT 3
#define STEP_TIME 0.05
#endif
