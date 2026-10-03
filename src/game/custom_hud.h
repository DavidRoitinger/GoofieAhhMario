
#include <PR/ultratypes.h>
#include <PR/gbi.h>

struct Entity {
    s32 spriteIndex;
    Vec3f pos;
    f32 angleInDegrees;
};

struct Ray {
  Vec3f hitPosition;
  f32 distance;
  Bool8 hit;
};

struct Pos {
    f32 dist;
    Bool8 hit;
    s32 x;
    s32 y;
};

struct Dialog {
    s32 charIndex;
    s32 lineIndex;
    s32 lineCount;
    char textBuffer[][72];
};

struct Choice {
    s32 selectedOption;
    s32 optionCount;
    s32 answer;
    char textBuffer[10][24];
};

struct Enemy{
    char name[50];
    s8 spriteIndex;
    s32 health;
    s32 damage;
};

struct PlayerStats{
    s32 health;
    s32 damage;
    f32 fokus;
};

void custom_hud();
void allocate_area();
void handel_transition();

void start_choice(char *textBuffer[], s32 optionCount);
void handel_choice(struct Choice *choice);

void start_dialog(char *textBuffer[], s32 lineCount);
void add_dialog(char *textBuffer[], s32 lineCount);
void handel_dialog(struct Dialog *dialog);
void handle_dialog_input(struct Dialog *dialog);
void draw_dialog_box();

void combat_area();

void draw_player_stat_box();

void handle_choice_input();
void draw_ui_icon_options(s32 x, s32 options[], s32 selected, s32 count);
void draw_ui_text_options(s32 x, s32 y, char options[][24], s32 selected, s32 count);

void draw_3d_render();
void draw_render_demo();
void draw_floor_tile(f32 distance, f32 angleInDegrees, s32 texture, s32 i);

f32 floor(f32 f);

f32 ceil(f32 f);

void draw_entity(struct Entity *entity);
void draw_background();
void add_texture(s8 glyphIndex);

void render_tile(s32 x, s32 y);
void render_tile_sized(s32 x, s32 y, s32 xSize, s32 ySize);
void render_tile_cords(s32 x, s32 y, s32 x2, s32 y2);

void render_tile_tinted(s32 x, s32 y);

void move_tile(Vec3f *pos, Vec3f targetPos, f32 velocity);
void handle_stick_movement(struct Entity *entity, f32 velocity);

void castRay(Vec3f start, f32 angleInDegrees, const s32 grid[10][10], struct Ray *ray, s32 i);