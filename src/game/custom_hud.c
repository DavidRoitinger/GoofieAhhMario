#include <PR/ultratypes.h>
#include <string.h>

#include "sm64.h"
#include "actors/common1.h"
#include "gfx_dimensions.h"
#include "game_init.h"
#include "level_update.h"
#include "camera.h"
#include "print.h"
#include "ingame_menu.h"
#include "segment2.h"
#include "area.h"
#include "save_file.h"
#include "print.h"
#include "engine/surface_load.h"
#include "engine/math_util.h"
#include "puppycam2.h"
#include "puppyprint.h"

#include "custom_hud.h"

#include "config.h"

s32 grid[10][10][10] = {
    {
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
        {11, 10, 10, 10, 11, 14, 10, 14, 10, 11},
        {11, 10, 10, 10, 11, 10, 11, 11, 13, 11},
        {11, 12, 10, 10, 13, 10, 10, 10, 10, 11},
        {11, 10, 10, 10, 10, 11, 14, 11, 13, 11},
        {11, 10, 14, 10, 12, 11, 10, 13, 10, 11},
        {11, 14, 10, 12, 10, 11, 14, 10, 10, 11},
        {11, 10, 10, 10, 10, 11, 11, 11, 10, 11},
        {11, 13, 10, 14, 10, 13, 11, 10, 15, 11},
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
    },
    {
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
        {11, 10, 15, 10, 11, 14, 10, 14, 10, 11},
        {11, 10, 11, 10, 11, 10, 11, 11, 13, 11},
        {11, 12, 10, 10, 13, 10, 10, 10, 10, 11},
        {11, 11, 11, 11, 10, 11, 14, 11, 13, 11},
        {11, 10, 14, 11, 12, 11, 10, 13, 10, 11},
        {11, 14, 10, 12, 10, 11, 14, 11, 11, 11},
        {11, 10, 11, 11, 11, 11, 10, 11, 10, 11},
        {11, 13, 10, 14, 10, 13, 10, 10, 10, 11},
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
    },
    {
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
        {11, 10, 10, 10, 10, 14, 10, 14, 15, 11},
        {11, 10, 11, 10, 11, 10, 11, 11, 13, 11},
        {11, 12, 10, 10, 13, 10, 10, 10, 10, 11},
        {11, 11, 11, 10, 10, 11, 14, 11, 13, 11},
        {11, 10, 14, 11, 12, 10, 10, 13, 10, 11},
        {11, 14, 10, 12, 10, 10, 14, 11, 11, 11},
        {11, 10, 11, 10, 11, 11, 10, 10, 14, 11},
        {11, 13, 10, 14, 10, 13, 10, 13, 10, 11},
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
    },
    {
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
        {11, 10, 10, 10, 10, 10, 10, 10, 10, 11},
        {11, 10, 11, 10, 11, 10, 11, 10, 11, 11},
        {11, 10, 10, 10, 10, 10, 10, 10, 10, 11},
        {11, 11, 10, 11, 10, 11, 10, 11, 10, 11},
        {11, 10, 10, 10, 10, 10, 10, 10, 10, 11},
        {11, 10, 11, 10, 11, 10, 11, 10, 11, 11},
        {11, 10, 10, 10, 10, 10, 10, 10, 10, 11},
        {11, 12, 10, 11, 10, 11, 10, 11, 10, 11},
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
    }

};

s32 layer = 0;

const s32 MAP_SIZE = 10;
const s32 WALL = 11;

s32 sprite_count = 0;
s32 hit_count = 0;
s32 ray_count = 0;


const s32 HEIGHT = 240; // 224?
const s32 HEIGHT_CENTER = HEIGHT / 2;
const s32 WIDTH = 320; // 304?
const s32 WIDTH_CENTER = WIDTH / 2;
const s32 TILE_SIZE = 16;
const f32 TURN_SPEED = 3.0f;
const f32 MOVE_SPEED = 1.0f;
const f32 PI = 3.141592653589793f;
const s32 FOV = 80;
const f32 SLICE_SIZE = 2.0f;
const s32 NUM_RAYS = FOV / SLICE_SIZE;
const s32 COLUMN_WIDTH = WIDTH / (f32) NUM_RAYS;


const s32 posStackSize = 16;
struct Pos posStack[16];
s32 posStackIndex = 0;

const s32 MAX_RAYCAST_DEPTH = 4;


f32 angleInDegrees = 0.0f;

struct Ray ray = {.hitPosition = {0.0f, 0.0f, 0.0f}, .distance=0.0f, .hit=FALSE};

struct Entity player = { .spriteIndex = 1, .pos={24.0f, 24.0f, 0.0f}, .angleInDegrees = 0.0f};

char buffer[100];



struct Enemy enemyList[100] = {
    { .name = "BOB", .spriteIndex = 0, .health = 10, .damage = 1},
    { .name = "BOB1", .spriteIndex = 1, .health = 11, .damage = 1},
    { .name = "BOB2", .spriteIndex = 2, .health = 12, .damage = 1},
    { .name = "BOB3", .spriteIndex = 3, .health = 13, .damage = 1},
    { .name = "BOBUS", .spriteIndex = 4, .health = 3, .damage = 2}
};
s32 enemyListCount = 5;




//Used for Transitions
u8 targetGameType = OVERWORLD;




struct Dialog dialog = { .textBuffer = {"eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee","BADAD ASDA ASADA FASDFA  ASDFASD ASDASDA AAASDADADADAS",
"Test qwertzuiooopasdfghjklyxcvbnm", "fghjklyxcvbnm"}, .charIndex = 0, .lineIndex = 0, .lineCount = 4};

struct Choice choice = { .selectedOption = 0, .optionCount = 0, .answer = 0, .textBuffer = {}};


struct Enemy enemy = { .name = "Placeholder", .spriteIndex = 0, .health = 1, .damage = 1};

struct PlayerStats playerStats = { .health = 10, .damage = 2, .fokus = 1};


void custom_hud(){
    // for (s8 i = 0; i < 25; i++)
    // {
    //     gSPDisplayList(gDisplayListHead++, dl_hud_img_begin_tinted);
    //     add_texture(11);
    //     gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);
    //     gDPSetPrimColor(gDisplayListHead++, 0, 0, 255-i*10, 255-i*10, 255-i*10, 255);
    //     render_tile(10+i*16, 100);
    //     gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
    // }

    sprite_count = 0;
    hit_count = 0;
    ray_count = 0;

    handel_transition();

    
    allocate_area();
    
    handel_dialog(&dialog);
    handel_choice(&choice);

    sprintf(buffer, "S: %d", sprite_count);
    print_text(230, 220, buffer);

    sprintf(buffer, "H: %d", hit_count);
    print_text(230, 200, buffer);

    sprintf(buffer, "M: %d", NUM_RAYS - hit_count);
    print_text(230, 180, buffer);
 
    sprintf(buffer, "NR: %d", NUM_RAYS);
    print_text(230, 160, buffer);
 
    sprintf(buffer, "RC: %d", ray_count);
    print_text(230, 140, buffer);
    
}

void allocate_area(){

    switch (gMarioState->gameType)
    {
    case OVERWORLD:
        handle_stick_movement(&player, MOVE_SPEED);
        draw_3d_render();
        //draw_render_demo();
        break;

    case COMBAT:
        combat_area();
        break;

    default:
        break;
    }
}


void handel_transition(){

    //begin transition
    int mapX = (int)(player.pos[0] / 16);
    int mapY = (int)(player.pos[1] / 16);


    switch(grid[layer][mapY][mapX]){
        case 12:
            grid[layer][mapY][mapX] = 10;
            targetGameType = COMBAT;
            gMarioState->transDelay = 25;
            break;
        case 15:
            layer++;
            break;
        default:
            break;
    }


    //wait for the transition animation to end 
    if(gMarioState->transDelay > 0){
        gMarioState->transDelay--;
    }
    if(gMarioState->transDelay == 0){
        gMarioState->gameType = targetGameType;
        gMarioState->transDelay = -1;
    }


}


void combat_area(){

    switch (gMarioState->combatState)
    {
    case START:
        if(dialog.lineCount > 0) break;
        if(choice.optionCount > 0) break;

        start_dialog((char*[]){"Hello?", "Hello, is this working?", "Great!"}, 3);

        enemy = enemyList[RAND(5)];

        gMarioState->combatState = PLAYER_TURN;

        break;
    
    case PLAYER_TURN:

        if(dialog.lineCount > 0) break;
        if(choice.optionCount > 0) break;

        start_choice((char*[]){"Attack", "Fokus"}, 2);

        gMarioState->combatState = PLAYER_ATTACK;

        break;
        
        case PLAYER_ATTACK:
        
        if(dialog.lineCount > 0) break;
        if(choice.optionCount > 0) break;

        if(choice.answer == 0){
            enemy.health -= (s32) floor(playerStats.damage * playerStats.fokus);
            playerStats.fokus = 1;
        }    

        if(choice.answer == 1){
            playerStats.fokus = playerStats.fokus * 1.75f;
        }    
        
        
        sprintf(buffer, "Player uses option: %d", choice.answer);
        
        start_dialog((char*[]){buffer, "It works!"}, 2);  
        
        gMarioState->combatState = ENEMY_ATTACK;

        break;

    case ENEMY_ATTACK:

        if(dialog.lineCount > 0) break;
        if(choice.optionCount > 0) break;

        playerStats.health -= enemy.damage;

        start_dialog((char*[]){"The Enemy does things!", "Wow!"}, 2);

        gMarioState->combatState = PLAYER_TURN;

        break;
    
    case WIN:
        if(dialog.lineCount > 0) break;
        if(choice.optionCount > 0) break;

        start_dialog((char*[]){"The Enemy is dead!", "You get nothing!"}, 2);

        //Temp solution...
        gMarioState->combatState = START;
        targetGameType = OVERWORLD;
        gMarioState->transDelay = 25;
        break;

    case LOSE:
        break;

    default:
        break;
    }

    if(gMarioState->combatState != WIN && gMarioState->combatState != START && enemy.health <= 0){
        
        gMarioState->combatState = WIN;
    }





    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    add_texture(20);
    gSPScisTextureRectangle(gDisplayListHead++, 0 << 2, 0 << 2, (0 + WIDTH) << 2,
    (0 + HEIGHT) << 2, G_TX_RENDERTILE, 0, 0, 100, 5 << 4);
    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
    

    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin_tinted);

    add_texture(enemy.spriteIndex);

    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);
    if(enemy.health <= 0){
        gDPSetPrimColor(gDisplayListHead++, 0, 0, 255, 50, 50, 255);
    }else{
        gDPSetPrimColor(gDisplayListHead++, 0, 0, 255, 255, 255, 255);
    }
    
    
    render_tile_tinted(WIDTH/2-8, HEIGHT/3);
    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);

    print_text_centered(WIDTH/2, HEIGHT-50, enemy.name);

    sprintf(buffer, "%d", enemy.health);
    print_text_centered(WIDTH/2, HEIGHT-110, buffer);
    
    sprintf(buffer, "%d", playerStats.health);
    print_text(10, HEIGHT-150, buffer);


    draw_player_stat_box();


}

void start_choice(char *textBuffer[], s32 optionCount){
    if(dialog.lineCount > 0) return;
    if(choice.optionCount > 0) return;
    
    for (s32 i = 0; i < optionCount; i++)
    {
        strcpy(choice.textBuffer[i], textBuffer[i]);
    }
    
    choice.optionCount = optionCount;    
}

void start_dialog(char *textBuffer[], s32 lineCount){
    if(dialog.lineCount > 0) return;
    if(choice.optionCount > 0) return;
    
    for (s32 i = 0; i < lineCount; i++)
    {
        strcpy(dialog.textBuffer[i], textBuffer[i]);
    }
    
    dialog.lineCount = lineCount;    
}

void add_dialog(char *textBuffer[], s32 lineCount){
    for (s32 i = dialog.lineCount - 1; i < lineCount + dialog.lineCount; i++)
    {
        strcpy(dialog.textBuffer[i], textBuffer[i]);
    }
    
    dialog.lineCount += lineCount;    
}


void handel_choice(struct Choice *choice){
    if (choice->optionCount <= 0) return;
    
    draw_dialog_box();
    
    draw_ui_text_options( 20, 50, choice->textBuffer, choice->selectedOption, choice->optionCount);
    
    handle_choice_input(choice);

}




void handel_dialog(struct Dialog *dialog){
    if(dialog->lineCount <= 0) return;

    draw_dialog_box();

    char lines[3][72] = {};
    
    for (s32 i = 0; i < dialog->charIndex; i++)
    {
        if(dialog->textBuffer[dialog->lineIndex][i] == '\0') break;

        if(i < 24){
            lines[0][i] = dialog->textBuffer[dialog->lineIndex][i];
        } else if (i < 48){
            lines[1][i - 24] = dialog->textBuffer[dialog->lineIndex][i];
        }else{
            lines[2][i - 48] = dialog->textBuffer[dialog->lineIndex][i];
        }
        
        
    }

    print_text(16, 50, lines[0]);
    print_text(16, 30, lines[1]);
    print_text(16, 10, lines[2]);

    if(dialog->charIndex < 71) dialog->charIndex++;

    handle_dialog_input(dialog);
}

void handle_dialog_input(struct Dialog *dialog){
        if(gMarioState->controller->buttonPressed & A_BUTTON){
        dialog->charIndex = 0,
        dialog->lineIndex++;

        //End of Dialog?
        if(dialog->lineIndex == dialog->lineCount){
            dialog->lineIndex = 0;
            dialog->lineCount = 0;
        }
    }
}

void draw_dialog_box(){
    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    add_texture(11);
    render_tile_cords(4, HEIGHT-80, WIDTH, HEIGHT);
    add_texture(10);
    render_tile_cords(9, HEIGHT-75, WIDTH-5, HEIGHT-5);
    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
}

void draw_player_stat_box(){
    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    add_texture(11);
    render_tile_cords(4, HEIGHT-115, WIDTH/3, HEIGHT-75);
    add_texture(10);
    render_tile_cords(9, HEIGHT-110, WIDTH/3-5, HEIGHT-80);
    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
}

void handle_choice_input(struct Choice *choice){

    if(dialog.lineCount > 0) return;
    
    struct Controller *controller = gMarioState->controller;

    
    if(gMarioState->controller->buttonPressed & A_BUTTON){
        choice->answer = choice->selectedOption;
        choice->selectedOption = 0;
        choice->optionCount = 0;
        
    }

    if(choice->selectedOption > 0 &&
        controller->buttonPressed & U_CBUTTONS){

        choice->selectedOption -= 1;
    }

    if(choice->selectedOption < (choice->optionCount - 1) &&
        controller->buttonPressed & D_CBUTTONS){

        choice->selectedOption += 1;
    } 


}



void draw_ui_icon_options(s32 x, s32 options[], s32 selected, s32 count){
    s32 spacing = WIDTH / count;

    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    add_texture(15);
    render_tile((spacing >> 1) + (spacing * selected) - 8, x);
    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);

    for (s32 i = 0; i < count; i++)
    {
        gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
        add_texture(options[i]);
        render_tile((spacing >> 1) + (spacing * i) - 8, x);
        gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
    }
}

void draw_ui_text_options(s32 x, s32 y, char options[][24], s32 selected, s32 count){

    draw_dialog_box();

    s32 spacing = 40;

    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    add_texture(15);
    render_tile(x,  HEIGHT - y + (spacing * selected) - 16);
    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);

    for (s32 i = 0; i < count; i++)
    {
        print_text(x + 20, y - (spacing * i), options[i]);
    }
}




void draw_3d_render(){

    for (s32 i = 0; i < FOV / SLICE_SIZE; i++){
        s32 angle = player.angleInDegrees + FOV/-2 + (i * SLICE_SIZE);
	    castRay(player.pos, angle, grid[layer], &ray, i);
        
        // if(ray.hit){
        //     ray.distance *= coss(degrees_to_angle(player.angleInDegrees - angle));

        //     f32 wallHeight = (TILE_SIZE * HEIGHT) / ray.distance;
        //     if(wallHeight > HEIGHT){
        //         wallHeight = HEIGHT;
        //     }

        //     f32 wallOffset = HEIGHT / 2.0f - wallHeight / 2.0f;

        //     gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
        //     add_texture(WALL);
        //     render_tile_sized((COLUMN_WIDTH) * i, wallOffset, COLUMN_WIDTH, wallHeight);
        //     // render_tile_cords((WIDTH / (FOV / SLICE_SIZE)) * i, (HEIGHT/2) + 25 * (ray.distance/10), (WIDTH / (FOV / SLICE_SIZE)) * (i + 1), (HEIGHT/2) - 25 * (ray.distance/10));
        //     gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
        // }
    }
}

void draw_render_demo(){
    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    Vec3f tilePos;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            add_texture(grid[layer][i][j]);
            vec3f_set(tilePos, 8 + (j * TILE_SIZE), 0, 8 + i * TILE_SIZE);
            render_tile(tilePos[0], tilePos[2]);
        }
    }
    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);

    for (int i = FOV/-2; i < FOV; i+= SLICE_SIZE){
	    castRay(player.pos, player.angleInDegrees + i, grid[layer], &ray, i);

        gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
        if(ray.hit){
            add_texture(2);
        }else{
            add_texture(3);
        }
        render_tile(ray.hitPosition[0], ray.hitPosition[1]);
        gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
    }

    //Player
    draw_entity(&player);
}


void draw_entity(struct Entity *entity){
    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    add_texture(entity->spriteIndex);
    render_tile(entity->pos[0], entity->pos[1]);
    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
}


void draw_background(){
    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);

    s32 currentSprite = 2;
    add_texture(currentSprite);

    Vec3f tilePos;
    

    for (int i = 0; i <= HEIGHT; i += TILE_SIZE) {
        for (int j = 0; j <= WIDTH; j += TILE_SIZE) {
            if(i == 0 || i == HEIGHT || j == 0 || j >= WIDTH){
                vec3f_set(tilePos, j, 0, i);
                render_tile(tilePos[0], tilePos[2]);
            }
        }
    }

    for (int i = 0; i <= 224; i += 16) {
            if(currentSprite == 1){
                currentSprite = 2;
                add_texture(2);
            }else{
                currentSprite = 1;
                add_texture(1);
            }
        for (int j = 0; j < 416; j += 16) {
            if(currentSprite == 1){
                currentSprite = 2;
                add_texture(2);
            }else{
                currentSprite = 1;
                add_texture(1);
            }

            vec3f_set(tilePos, j, 0, i);
            //move_tile(&tilePos, enemyPos, 10);
            render_tile(tilePos[0], tilePos[2]);
        }
    }

    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
}


void add_texture(s8 glyphIndex){
    const Texture *const *glyphs = segmented_to_virtual(edit_custom_textures);

    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, glyphs[glyphIndex]);
    gSPDisplayList(gDisplayListHead++, dl_hud_img_load_tex_block);
}

void add_texture_tinted(s8 glyphIndex){
    const Texture *const *glyphs = segmented_to_virtual(edit_custom_textures);

    gDPPipeSync(gDisplayListHead++);
    gDPLoadTextureBlock(
        gDisplayListHead++,
        glyphs[glyphIndex],
        G_IM_FMT_RGBA, G_IM_SIZ_16b,
        16, 16,
        0, G_TX_CLAMP, G_TX_CLAMP,
        G_TX_NOMASK, G_TX_NOMASK,
        G_TX_NOLOD, G_TX_NOLOD
    );
}


void render_tile(s32 x, s32 y) {
    s32 rectBaseX = x;
    s32 rectBaseY = y;
    s32 rectX;
    s32 rectY;

    rectX = rectBaseX;
    rectY = rectBaseY;
    gSPScisTextureRectangle(gDisplayListHead++, rectX << 2, rectY << 2, (rectX + 16) << 2,
                        (rectY + 16) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
}

void render_tile_sized(s32 x, s32 y, s32 xSize, s32 ySize) {
    s32 rectBaseX = x;
    s32 rectBaseY = y;
    s32 rectX;
    s32 rectY;

    rectX = rectBaseX;
    rectY = rectBaseY;
    gSPScisTextureRectangle(gDisplayListHead++, rectX << 2, rectY << 2, (rectX + xSize) << 2,
                        (rectY + ySize) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

}

void render_tile_cords(s32 x, s32 y, s32 x2, s32 y2) {
    x2--;
    y2--;

    gSPScisTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x2) << 2,
                        (y2) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 4 << 10);
}

void render_tile_tinted(s32 x, s32 y) {
    s32 rectBaseX = x;
    s32 rectBaseY = y;
    s32 rectX;
    s32 rectY;

    rectX = rectBaseX;
    rectY = rectBaseY;
    gSPScisTextureRectangle(gDisplayListHead++, rectX << 2, rectY << 2, (rectX + 16) << 2,
                        (rectY + 16) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
}


void move_tile(Vec3f *pos, Vec3f targetPos, f32 velocity) {
    const f32 deltaTime = 0.03;

    Vec3f difference;
    vec3f_set(difference, 0, 0, 0);

    vec3f_diff(difference, targetPos, *pos);
    vec3f_normalize(difference);

    Vec3f movement;
    vec3f_copy(movement, difference)
    vec3_scale(movement, velocity);

    Vec3f timedMovement;
    vec3f_copy(timedMovement, movement)
    vec3_scale(movement, deltaTime);

    vec3f_sum(*pos, *pos, timedMovement)
}


void handle_stick_movement(struct Entity *entity, f32 velocity){

    //Lock movement while in dialog
    if(dialog.lineCount > 0) return;

    Vec3f stickVec = {0.0f, 0.0f, 0.0f};
    Vec3f rotVec = {0.0f, 0.0f, 0.0f};
    
    struct Controller *controller = gMarioState->controller;


    if(controller->buttonDown & L_CBUTTONS){
        entity->angleInDegrees -= TURN_SPEED;
    }

    if(controller->buttonDown & R_CBUTTONS){
        entity->angleInDegrees += TURN_SPEED;
    }

    f32 mag = ((controller->stickMag / 64.0f) * (controller->stickMag / 64.0f)) * 64.0f;

    //inverts Y-axis, because why not?
    vec3f_set(stickVec, controller->stickX, -controller->stickY, 0);
    vec3f_normalize(stickVec);
    vec3_scale(stickVec, mag / 64.0f)

    vec3_scale(stickVec, velocity);

    s16 angle = degrees_to_angle(270 - entity->angleInDegrees); //360° - x - 90°

    f32 rotationMatrix[3][3] ={
        {coss(angle), -sins(angle), 0},
        {sins(angle), coss(angle), 0},
        {0, 0, 1},
    };

    // sprintf(buffer, "%.1f %.1f", stickVec[0], stickVec[1]);
    // print_text(0, 20, buffer);

    linear_mtxf_mul_vec3(rotationMatrix, rotVec, stickVec);
    
    // sprintf(buffer, "%.1f %.1f", rotVec[0], rotVec[1]);
    // print_text(0, 40, buffer);


    f32 newX = entity->pos[0] + rotVec[0];
    f32 newY = entity->pos[1] + rotVec[1];

    
    s32 gridX = (s32)(newX / TILE_SIZE); 
    s32 gridY = (s32)(newY / TILE_SIZE);

    rotVec[0] = grid[layer][gridY][gridX] == WALL ? 0 : rotVec[0];
    rotVec[1] = grid[layer][gridY][gridX] == WALL ? 0 : rotVec[1];

    vec3f_sum(entity->pos, entity->pos, rotVec);
    3;
}

void draw_floor_tile(f32 distance, f32 angleInDegrees, s32 texture, s32 i){

    s32 angle = angleInDegrees + FOV/-2 + (i * SLICE_SIZE);


    distance *= coss(degrees_to_angle(angleInDegrees - angle));

    f32 wallHeight = (TILE_SIZE * HEIGHT) / distance;
    if(wallHeight > HEIGHT){
        wallHeight = HEIGHT;
    }

    f32 wallOffset = HEIGHT / 2.0f - wallHeight / 2.0f;

    // Uncomment to toggle floorrendering...

    // gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    // add_texture(texture);
    // render_tile_sized((COLUMN_WIDTH ) * i, wallOffset, COLUMN_WIDTH, wallHeight);
    // gSPDisplayList(gDisplayListHead++, dl_hud_img_end);



    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin_tinted);
    add_texture(texture);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);


    s32 brightness = 255 - (s32)floor((distance * 7) - 1);
    
    if (brightness < 0) brightness = 0;
    
    gDPSetPrimColor(gDisplayListHead++, 0, 0, brightness, brightness, brightness, 255);

    render_tile_sized((COLUMN_WIDTH ) * i, wallOffset, COLUMN_WIDTH, wallHeight);
    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);

    sprite_count++;
    
}

void selectionSort(struct Pos arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].dist < arr[min].dist)
                min = j;
        }
       if (min != i) {
            struct Pos temp = arr[min];
            arr[min] = arr[i];
            arr[i] = temp;
        }
    }
}

f32 floor(f32 f){
    return (f32)(s32)f;
}


//TODO: Fix Visual Bug with occurs a coloured tile is on the edge of the render distance
//TODO: Try if increasing the render distance is possible
void castRay(Vec3f start, f32 angleInDegrees, const s32 grid[MAP_SIZE][MAP_SIZE], struct Ray *ray, s32 slice_index){
    ray_count++;
    s16 angle = degrees_to_angle(angleInDegrees);
    float vtan = -tans(angle), htan = -1.0f / tans(angle);
    float cellSize = 16;
    Bool8 hit = FALSE;
    s32 vdof = 0, hdof = 0;

    // Could be optimised:/...
    draw_floor_tile(1.0f, angleInDegrees, 
            grid[(int)(start[1] / 16)][(int)(start[0] / 16)], slice_index);

    posStackIndex = 0;

    for (s32 i = 0; i < 16; i++) {
        posStack[i].hit = FALSE;
        posStack[i].dist = (float) S32_MAX;
        posStack[i].x = 0;
        posStack[i].y = 0;
    }
    
    float vdist = (float) S32_MAX;
    float hdist = (float) S32_MAX;

    Vec3f vRayPos, hRayPos, offset;

    if (coss(angle) > 0.001f) {
        vRayPos[0] = floor(start[0] / cellSize) * cellSize + cellSize;
        vRayPos[1] = (start[0] - vRayPos[0]) * vtan + start[1];
        offset[0] = cellSize;
        offset[1] = -offset[0] * vtan;
    } else if (coss(angle) < -0.001f) {
        vRayPos[0] = floor(start[0] / cellSize) * cellSize - 0.01f;
        vRayPos[1] = (start[0] - vRayPos[0]) * vtan + start[1];
        offset[0] = -cellSize;
        offset[1] = -offset[0] * vtan;
    } else {
        vdof = MAX_RAYCAST_DEPTH;
    }


    for (; vdof < MAX_RAYCAST_DEPTH; vdof++) {
        int mapX = (int)(vRayPos[0] / cellSize);
        int mapY = (int)(vRayPos[1] / cellSize);

        if (mapY < MAP_SIZE && mapX < MAP_SIZE) {

            // draw_floor_tile(sqrtf((vRayPos[0] - start[0]) * (vRayPos[0] - start[0]) +
            //                 (vRayPos[1] - start[1]) * (vRayPos[1] - start[1])),
            //                 player.angleInDegrees, grid[mapY][mapX], slice_index);
            posStackIndex++;
            posStack[posStackIndex].dist = sqrtf((vRayPos[0] - start[0]) * (vRayPos[0] - start[0]) +
                                (vRayPos[1] - start[1]) * (vRayPos[1] - start[1]));
            posStack[posStackIndex].x = mapX;
            posStack[posStackIndex].y = mapY;

            if (grid[mapY][mapX] == WALL){ 
                hit = TRUE;
                posStack[posStackIndex].hit = TRUE;
                vdist = sqrtf((vRayPos[0] - start[0]) * (vRayPos[0] - start[0]) +
                                    (vRayPos[1] - start[1]) * (vRayPos[1] - start[1]));
                break;
            }else{
                posStack[posStackIndex].hit = FALSE;
            }
        }
        vRayPos[0] += offset[0];
        vRayPos[1] += offset[1];
    }
    
    
    if (sins(angle) > 0.001f) {
        hRayPos[1] = floor(start[1] / cellSize) * cellSize + cellSize;
        hRayPos[0] = (start[1] - hRayPos[1]) * htan + start[0];
        offset[1] = cellSize;
        offset[0] = -offset[1] * htan;
    } else if (sins(angle) < -0.001f) {
        hRayPos[1] = floor(start[1] / cellSize) * cellSize - 0.01f;
        hRayPos[0] = (start[1] - hRayPos[1]) * htan + start[0];
        offset[1] = -cellSize;
        offset[0] = -offset[1] * htan;
    } else {
        hdof = MAX_RAYCAST_DEPTH;
    }

    for (; hdof < MAX_RAYCAST_DEPTH; hdof++) {
        int mapX = (int)(hRayPos[0] / cellSize);
        int mapY = (int)(hRayPos[1] / cellSize);

        if (mapY < MAP_SIZE && mapX < MAP_SIZE) {

            // draw_floor_tile(sqrtf((hRayPos[0] - start[0]) * (hRayPos[0] - start[0]) +
            //     (hRayPos[1] - start[1]) * (hRayPos[1] - start[1])),
            //     player.angleInDegrees, grid[mapY][mapX], slice_index);
            posStackIndex++;
            posStack[posStackIndex].dist = sqrtf((hRayPos[0] - start[0]) * (hRayPos[0] - start[0]) +
                (hRayPos[1] - start[1]) * (hRayPos[1] - start[1]));
            posStack[posStackIndex].x = mapX;
            posStack[posStackIndex].y = mapY;

            if(grid[mapY][mapX] == WALL){
                posStack[posStackIndex].hit = TRUE;
                hit = TRUE;
                hdist = sqrtf((hRayPos[0] - start[0]) * (hRayPos[0] - start[0]) +
                    (hRayPos[1] - start[1]) * (hRayPos[1] - start[1]));
                break;
            }else {
                    posStack[posStackIndex].hit = FALSE;
            }
        }
        hRayPos[0] += offset[0];
        hRayPos[1] += offset[1];
    }

    selectionSort(posStack, posStackSize);

    for (s32 i = 0; i <= posStackIndex; i++)
    {
        draw_floor_tile(posStack[i].dist, angleInDegrees, 
            grid[posStack[i].y][posStack[i].x], slice_index);
        if(posStack[i].hit){
            hit_count++;
            break;
        }
    }

        // draw_floor_tile(posStack[0].dist, player.angleInDegrees, 
        //     grid[posStack[0].y][posStack[0].x], slice_index);
        // draw_floor_tile(posStack[1].dist, player.angleInDegrees, 
        //     grid[posStack[1].y][posStack[1].x], slice_index);

    if (hdist < vdist){
        ray->hitPosition[0] = hRayPos[0];
        ray->hitPosition[1] = hRayPos[1];
    }else{
        ray->hitPosition[0] = vRayPos[0];
        ray->hitPosition[1] = vRayPos[1];
    }


    ray->distance = MIN(hdist, vdist);
    ray->hit = hit;
}



// void castRay(Vec3f start, f32 angleInDegrees, const s32 grid[MAP_SIZE][MAP_SIZE], struct Ray *ray, s32 i){

    
//     s16 angle = degrees_to_angle(angleInDegrees);
//     float vtan = -tans(angle), htan = -1.0f / tans(angle);
//     float cellSize = 16;
//     Bool8 hit = FALSE;
//     Bool8 vHit = FALSE;
//     Bool8 hHit = FALSE;
//     s32 vdof = 0, hdof = 0;
//     float vdist = (float) S32_MAX;
//     float hdist = (float) S32_MAX;

//     Vec3f vRayPos, hRayPos, vOffset, hOffset;

//     if (coss(angle) > 0.001f) {
//         vRayPos[0] = floor(start[0] / cellSize) * cellSize + cellSize;
//         vRayPos[1] = (start[0] - vRayPos[0]) * vtan + start[1];
//         vOffset[0] = cellSize;
//         vOffset[1] = -vOffset[0] * vtan;
//     } else if (coss(angle) < -0.001f) {
//         vRayPos[0] = floor(start[0] / cellSize) * cellSize - 0.01f;
//         vRayPos[1] = (start[0] - vRayPos[0]) * vtan + start[1];
//         vOffset[0] = -cellSize;
//         vOffset[1] = -vOffset[0] * vtan;
//     } else {
//         vdof = MAX_RAYCAST_DEPTH;
//     }

//     if (sins(angle) > 0.001f) {
//     hRayPos[1] = floor(start[1] / cellSize) * cellSize + cellSize;
//     hRayPos[0] = (start[1] - hRayPos[1]) * htan + start[0];
//     hOffset[1] = cellSize;
//     hOffset[0] = -hOffset[1] * htan;
//   } else if (sins(angle) < -0.001f) {
//     hRayPos[1] = floor(start[1] / cellSize) * cellSize - 0.01f;
//     hRayPos[0] = (start[1] - hRayPos[1]) * htan + start[0];
//     hOffset[1] = -cellSize;
//     hOffset[0] = -hOffset[1] * htan;
//   } else {
//     hdof = MAX_RAYCAST_DEPTH;
//   }


//     for (int d = 0; d < MAX_RAYCAST_DEPTH; d++) {

//         gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
//         add_texture(7);
//         render_tile(vRayPos[0], vRayPos[1]);
//         gSPDisplayList(gDisplayListHead++, dl_hud_img_end);

//         gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
//         add_texture(7);
//         render_tile(hRayPos[0], hRayPos[1]);
//         gSPDisplayList(gDisplayListHead++, dl_hud_img_end);

//         if(!vHit){
//             int vMapX = (int)(vRayPos[0] / cellSize);
//             int vMapY = (int)(vRayPos[1] / cellSize);

//             if (vMapY >= 0 && vMapX >= 0 && vMapY < MAP_SIZE && vMapX < MAP_SIZE && vdof < MAX_RAYCAST_DEPTH) {

//                 // draw_floor_tile(sqrtf((vRayPos[0] - start[0]) * (vRayPos[0] - start[0]) +
//                 //                 (vRayPos[1] - start[1]) * (vRayPos[1] - start[1])),
//                 //                 player.angleInDegrees, grid[vMapY][vMapX], i);

//                 if (grid[vMapY][vMapX] != 0){ 
//                     vHit = TRUE;
//                     // break;
//                 }else {
//                     vRayPos[0] += vOffset[0];
//                     vRayPos[1] += vOffset[1];
//                     vdist = sqrtf((vRayPos[0] - start[0]) * (vRayPos[0] - start[0]) +
//                         (vRayPos[1] - start[1]) * (vRayPos[1] - start[1]));
//                 }


//             }else {
//                 vdist = (float) S32_MAX;
//                 vdof = MAX_RAYCAST_DEPTH;
//             }
//         }
//         if(!hHit){
//             int hMapX = (int)(hRayPos[0] / cellSize);
//             int hMapY = (int)(hRayPos[1] / cellSize);

//             if (hMapY >= 0 && hMapX >= 0 && hMapY < MAP_SIZE && hMapX < MAP_SIZE && hdof < MAX_RAYCAST_DEPTH) {

//                 // draw_floor_tile(sqrtf((hRayPos[0] - start[0]) * (hRayPos[0] - start[0]) +
//                 //     (hRayPos[1] - start[1]) * (hRayPos[1] - start[1])),
//                 //     player.angleInDegrees, grid[hMapY][hMapX], i);

//                 if(grid[hMapY][hMapX] != 0){
//                     hHit = TRUE;
//                     // break;
//                 }else {
//                     hRayPos[0] += hOffset[0];
//                     hRayPos[1] += hOffset[1];
//                     hdist = sqrtf((hRayPos[0] - start[0]) * (hRayPos[0] - start[0]) +
//                         (hRayPos[1] - start[1]) * (hRayPos[1] - start[1]));
//                 }
                

//             }else {
//                 vdist = (float) S32_MAX;
//                 hdof = MAX_RAYCAST_DEPTH;
//             }
//         }
        

//         if(hHit && vHit){
//             if (hdist < vdist){
//                 hit = hHit;
//                 ray->hitPosition[0] = hRayPos[0];
//                 ray->hitPosition[1] = hRayPos[1];
//                 ray->distance = hdist;

//                 // draw_floor_tile(hdist,
//                 //     player.angleInDegrees, 1, i);
//                 break;
//             }else {
//                 hit = vHit;
//                 ray->hitPosition[0] = vRayPos[0];
//                 ray->hitPosition[1] = vRayPos[1];
//                 ray->distance = vdist;

//                 // draw_floor_tile(vdist,
//                 //     player.angleInDegrees, 1, i);
//                 break;
//             }
//         }




//         if(hHit || vHit){
//             if(hdist < vdist){
//                 if (hHit){

//                     hit = hHit;
//                     ray->hitPosition[0] = hRayPos[0];
//                     ray->hitPosition[1] = hRayPos[1];
//                     ray->distance = hdist;

//                     // draw_floor_tile(hdist,
//                     //     player.angleInDegrees, grid[hMapY][hMapX], i);
//                     break;
//                 }else {
//                     continue;
//                 }
//             }else{
//                 if (vHit){

//                     hit = vHit;
//                     ray->hitPosition[0] = vRayPos[0];
//                     ray->hitPosition[1] = vRayPos[1];
//                     ray->distance = vdist;

//                     // draw_floor_tile(hdist,
//                     //     player.angleInDegrees, grid[hMapY][hMapX], i);
//                     break;
//                 }else {
//                     continue;
//                 }
//             }
//         }else{

//             if (hdist < vdist){
//                 ray->hitPosition[0] = hRayPos[0];
//                 ray->hitPosition[1] = hRayPos[1];
//                 ray->distance = hdist;

//                 // draw_floor_tile(hdist,
//                 //     player.angleInDegrees, grid[hMapY][hMapX], i);
//             }else {
//                 ray->hitPosition[0] = vRayPos[0];
//                 ray->hitPosition[1] = vRayPos[1];
//                 ray->distance = vdist;

//                 // draw_floor_tile(vdist,
//                 //     player.angleInDegrees, grid[vMapY][vMapX], i);
//             }
//         }

//     }

//     sprintf(buffer, "%.1f", ray->distance);
//     print_text(100, 40, buffer);
    
//     ray->hit = hit;
// }






// OLD MEANINGLESS COMMENTS



    //fuck????
    // fuck++;
    // //print_text(200, 100, fuck+"");
    // gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    // add_texture(4);
    // render_tile_sized(0,224, WIDTH, HEIGHT);
    // gSPDisplayList(gDisplayListHead++, dl_hud_img_end);

    //Stripes Demo
    // gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    // add_texture(4);
    // for (int i = 0; i <= WIDTH; i ++) {
    //     render_tile_sized(i, 100 + roundf(random_float() * 50), 1, 100);
    // }
    // gSPDisplayList(gDisplayListHead++, dl_hud_img_end);


    
    // handle_stick_movement(&player, 2.0f);
    // sprintf(buffer, "D %.2f", player.angleInDegrees);
    // print_text(200, 100, buffer);
    // sprintf(buffer, "R %.5f", player.angleInDegrees* PI / 180.0f);
    // print_text(200, 120, buffer);
	// sprintf(buffer, "SR %.3f", sins(player.angleInDegrees* PI / 180.0f));
    // print_text(200, 140, buffer);
	// sprintf(buffer, "SD %.3f", sins(player.angleInDegrees* PI / 180.0f));
    // print_text(200, 160, buffer);
	// sprintf(buffer, "SA %.3f", sins(degrees_to_angle(player.angleInDegrees)));
    // print_text(200, 180, buffer);
	// sprintf(buffer, "FL %.3f", (f32)(s32)(player.angleInDegrees* PI / 180.0f));
    // print_text(200, 200, buffer);
	// sprintf(buffer, "sqrtf %.1f", sqrtf(player.angleInDegrees));
    // print_text(200, 220, buffer);



    


    // sprintf(buffer, "start %.1f %.1f", ray.hitPosition[0], ray.hitPosition[1]);
    // print_text(100, 20, buffer);
    // sprintf(buffer, "hit %d", ray.hit);
    // print_text(100, 40, buffer);



    //draw_background();




    // gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    // add_texture(0);
    // render_tile(playerPos[0], playerPos[2]);
    // gSPDisplayList(gDisplayListHead++, dl_hud_img_end);

    //Enemy
    // gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    // add_texture(3);
    // move_tile(&enemyPos, player.pos, 0.1f);
    // render_tile(enemyPos[0], enemyPos[2]);
    // gSPDisplayList(gDisplayListHead++, dl_hud_img_end);