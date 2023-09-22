#include "snake.h"
#include "glyphs.c"

#if 0
//FULLSCREEN
#define WINDOW_X 0
#define WINDOW_Y 0
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#else
//STREAM
#define WINDOW_WIDTH 1770
#define WINDOW_HEIGHT 1405
#define WINDOW_X 10
#define WINDOW_Y -20
#endif

#define GRID_SIZE 28
#define GRID_DIM 1000

#define DELAY 2


enum {
    SNAKE_UP,
    SNAKE_DOWN,
    SNAKE_LEFT,
    SNAKE_RIGHT,
};

typedef struct {
    int x;
    int y;
    int score;
    int top_score;
} apple;

apple Apple;

struct snake {
    int x;
    int y;
    int dir;
    
    struct snake *next;

};
typedef struct snake Snake;

Snake *head;
Snake *tail;

void init_snake()
{
    Snake *new = malloc(sizeof(Snake));
    new->x = rand() % (GRID_SIZE / 2) + (GRID_SIZE / 4);
    new->y = rand() % (GRID_SIZE / 2) + (GRID_SIZE / 4);
    new->dir = SNAKE_UP;
    new->next = NULL;
    
    head = new;
    tail = new;


    return;
}

void increase_snake()
{
    Snake *new = malloc(sizeof(Snake));
    
    switch(tail->dir) {
        case SNAKE_UP:
            new->x = tail->x;
            new->y = tail->y +1;
            break;
        case SNAKE_DOWN:
            new->x = tail->x;
            new->y = tail->y - 1;
            break;
        case SNAKE_LEFT:
            new->x = tail->x + 1;
            new->y = tail->y;
            break;
        case SNAKE_RIGHT:
            new->x = tail->x - 1;
            new->y = tail->y;
            break;
    }






    new->dir = tail->dir;

    new->next = NULL;
    tail->next = new;

    tail = new;


    return;
}

void move_snake()
{

    int prev_x = head->x;
    int prev_y = head->y;
    int prev_dir = head->dir;

    switch(head->dir) {
        case SNAKE_UP:
            head->y--;
            break;
        case SNAKE_DOWN:
            head->y++;
            break;
        case SNAKE_LEFT:
            head->x--;
            break;
        case SNAKE_RIGHT:
            head->x++;
            break;
    }

    Snake *track = head;

    if(track->next != NULL) {
        track = track->next;
    }

    while(track != NULL) {

        int save_x = track->x;
        int save_y = track->y;
        int save_dir = track->dir;

        track->x = prev_x;
        track->y = prev_y;
        track->dir = prev_dir;

        track = track->next;

        prev_x = save_x;
        prev_y = save_y;
        prev_dir = save_dir;

    }


    return;
}


void reset_snake()
{
    Snake *track = head;
    Snake *temp;

    while(track != NULL) {
        temp = track;
        track = track->next;
        free(temp);
    }

    init_snake();
    increase_snake();
    increase_snake();
    increase_snake();

    if(Apple.score > Apple.top_score) {
        Apple.top_score = Apple.score;
    }

    Apple.score = 0;

    return;
}

void render_snake(SDL_Renderer *renderer, int x, int y)
{


    int seg_size = GRID_DIM / GRID_SIZE;
    SDL_Rect seg;
    seg.w = seg_size - 2;
    seg.h = seg_size - 2;

    SDL_Rect seg_out;
    seg_out.w = seg_size;
    seg_out.h = seg_size;

    Snake *track = head;

    int bright = 255;
    int b_dir = 0;


    while(track != NULL) {

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, bright, 255);
        seg_out.x = x + track->x * seg_size;
        seg_out.y = y + track->y* seg_size;

        SDL_RenderFillRect(renderer, &seg_out);

        SDL_SetRenderDrawColor(renderer, 0x00, bright, 0x00, 255);
        seg.x = x + track->x * seg_size + 1;
        seg.y = y + track->y* seg_size + 1;

        SDL_RenderFillRect(renderer, &seg);

        track = track->next;

        if(b_dir == 0) {
            bright -= 5;
            if(bright < 150) {
                b_dir = 1;
            }
        }
        if(b_dir == 1) {
            bright += 5;
            if(bright > 250) {
                b_dir = 0;
            }
        }



    }


    return;
}

void flash_snake(SDL_Renderer *renderer, int x, int y)
{


    int seg_size = GRID_DIM / GRID_SIZE;
    SDL_Rect seg;
    seg.w = seg_size - 2;
    seg.h = seg_size - 2;

    SDL_Rect seg_out;
    seg_out.w = seg_size;
    seg_out.h = seg_size;

    Snake *track = head;

    int bright = 255;
    int b_dir = 0;

    int r = rand() % 255;
    int g = rand() % 255;
    int b = rand() % 255;

    while(track != NULL) {

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, bright, 255);
        seg_out.x = x + track->x * seg_size;
        seg_out.y = y + track->y* seg_size;

        SDL_RenderFillRect(renderer, &seg_out);

        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        seg.x = x + track->x * seg_size + 1;
        seg.y = y + track->y* seg_size + 1;

        SDL_RenderFillRect(renderer, &seg);

        track = track->next;

        if(b_dir == 0) {
            bright -= 5;
            if(bright < 150) {
                b_dir = 1;
            }
        }
        if(b_dir == 1) {
            bright += 5;
            if(bright > 250) {
                b_dir = 0;
            }
        }



    }


    return;
}

void render_grid(SDL_Renderer *renderer, int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0xff, 255);

#if 0

    int cell_size = GRID_DIM / GRID_SIZE;

    SDL_Rect cell;
    cell.w = cell_size;
    cell.h = cell_size;

    for(int i = 0; i < GRID_SIZE; i++) {
        for(int j = 0; j < GRID_SIZE; j++) {
            cell.x = x + (i * cell_size);
            cell.y = y + (j * cell_size);
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
#else


    for(int i = 0; i < 255; i++) {




        SDL_SetRenderDrawColor(renderer, 0, 0, 255 - i, 255 - i);

        SDL_Rect outline;
        outline.x = x - i;
        outline.y = y - i;
        outline.w = GRID_DIM + i + i;
        outline.h = GRID_DIM + i + i;

        SDL_RenderDrawRect(renderer, &outline);
    }

#endif
    return;
}


void gen_apple()
{

    bool in_snake;

    do {
        in_snake = false;
        Apple.x = rand() % GRID_SIZE;    
        Apple.y = rand() % GRID_SIZE;    

        Snake *track = head;

        while(track != NULL) {
            if(track->x == Apple.x && track->y == Apple.y) {
                in_snake = true;
            }

            track = track->next;
        }
    }
    while(in_snake);


    Apple.score++;

    return;
}

void render_apple(SDL_Renderer *renderer, int x, int y)
{

    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 255);

    int apple_size = GRID_DIM / GRID_SIZE;

    SDL_Rect app;
    app.w = apple_size;
    app.h = apple_size;
    app.x = x + Apple.x * apple_size;
    app.y = y + Apple.y * apple_size;

    SDL_RenderFillRect(renderer, &app);

}

void detect_apple()
{
    if(head->x == Apple.x && head->y == Apple.y) {
        gen_apple();
        increase_snake();
    }

    return;
}

void detect_crash()
{
    if(head->x < 0 || head->x >= GRID_SIZE || head->y < 0 || head->y >= GRID_SIZE) {
        reset_snake();   
    }

    Snake *track = head;

    if(track->next != NULL) {
        track = track->next;
    }

    while(track != NULL) {
        if(track->x == head->x && track->y == head->y) {
            reset_snake();   
        }
        track = track->next;
    }


    return;
}

void turn_left()
{
    switch(head->dir) {
        case SNAKE_UP:
            head->dir = SNAKE_LEFT;
            break;
        case SNAKE_DOWN:
            head->dir = SNAKE_RIGHT;
            break;
        case SNAKE_LEFT:
            head->dir = SNAKE_DOWN;
            break;
        case SNAKE_RIGHT:
            head->dir = SNAKE_UP;
            break;
    }

    return;
}

void turn_right()
{
    switch(head->dir) {
        case SNAKE_UP:
            head->dir = SNAKE_RIGHT;
            break;
        case SNAKE_DOWN:
            head->dir = SNAKE_LEFT;
            break;
        case SNAKE_LEFT:
            head->dir = SNAKE_UP;
            break;
        case SNAKE_RIGHT:
            head->dir = SNAKE_DOWN;
            break;
    }

    return;
}

enum {
    TRY_FORWARD,
    TRY_LEFT,
    TRY_RIGHT,
};


int state(int try)
{
    int reward = 0;

    int try_x = head->x;
    int try_y = head->y;


    switch(head->dir) {
        case SNAKE_UP:
            switch(try) {
                case TRY_FORWARD:
                    try_y--;
                    break;
                case TRY_LEFT:
                    try_x--;
                    break;
                case TRY_RIGHT:
                    try_x++;
                    break;
            }
            break;
        case SNAKE_DOWN:
            switch(try) {
                case TRY_FORWARD:
                    try_y++;
                    break;
                case TRY_LEFT:
                    try_x++;
                    break;
                case TRY_RIGHT:
                    try_x--;
                    break;
            }
            break;
        case SNAKE_LEFT:
            switch(try) {
                case TRY_FORWARD:
                    try_x--;
                    break;
                case TRY_LEFT:
                    try_y++;
                    break;
                case TRY_RIGHT:
                    try_y--;
                    break;
            }
            break;
        case SNAKE_RIGHT:
            switch(try) {
                case TRY_FORWARD:
                    try_x++;
                    break;
                case TRY_LEFT:
                    try_y--;
                    break;
                case TRY_RIGHT:
                    try_y++;
                    break;
            }
            break;
    }

    //DETECT WALL CRASH
    if(try_x < 0 || try_x > GRID_SIZE - 1) {
        reward += -100;
    }
    if(try_y < 0 || try_y > GRID_SIZE - 1) {
        reward += -100;
    }

    //DETECT APPLE
    if(try_x == Apple.x && try_y == Apple.y) {
        reward += 100;
    }

    //MOVE TOWARDS APPLE
    int diff_x = abs(head->x - Apple.x);
    int diff_y = abs(head->y - Apple.y);
    int try_diff_x = abs(try_x - Apple.x);
    int try_diff_y = abs(try_y - Apple.y);
    
    if(try_diff_x < diff_x) {
        reward += 5;
    }
    if(try_diff_y < diff_y) {
        reward += 5;
    }


    //DETECT TAIL
    
    Snake *track = head;

    if(track->next != NULL) {
        track = track->next;
    }
    while(track != NULL) {
        if(try_x == track->x && try_y == track->y) {
            reward += -100;
        }

        track = track->next;
    }




    return reward;
}

void ai()
{
    int try_f = state(TRY_FORWARD);
    int try_l = state(TRY_LEFT);
    int try_r = state(TRY_RIGHT);

    if(try_f >= try_l && try_f >= try_r) {
        //CONTINUE FOWARD
    }
    else {
        if(try_l > try_r) {
            turn_left();
        }
        else {
            turn_right();
        }

    }


    return;
}

void render_score(SDL_Renderer *renderer, int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 255);

    int cell_size = 11;

    SDL_Rect cell;
    cell.w = cell_size - 2;
    cell.h = cell_size - 2;

    char buff[10];
    snprintf(buff, sizeof(buff), "%4d", Apple.score);

    for(int k = 0; k < 4; k++) {
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                if(glyphs[buff[k]][j][i]) {
                    cell.x = x + cell_size * i + (cell_size * 9 * k);
                    cell.y = y + cell_size * j;
                    SDL_RenderFillRect(renderer, &cell);
                }
            }
        }
    }

    return;
}

void render_top_score(SDL_Renderer *renderer, int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 255);

    int cell_size = 11;

    SDL_Rect cell;
    cell.w = cell_size - 2;
    cell.h = cell_size - 2;

    char buff[10];
    snprintf(buff, sizeof(buff), "%4d", Apple.top_score);

    for(int k = 0; k < 4; k++) {
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                if(glyphs[buff[k]][j][i]) {
                    cell.x = x + cell_size * i + (cell_size * 9 * k);
                    cell.y = y + cell_size * j;
                    SDL_RenderFillRect(renderer, &cell);
                }
            }
        }
    }

    return;
}


int main()
{
    srand(time(0));

    init_snake();
    increase_snake();
    increase_snake();
    increase_snake();

    gen_apple();
    Apple.score = 0;




    SDL_Window *window;
    SDL_Renderer *renderer;

    if(SDL_INIT_VIDEO < 0) {
        fprintf(stderr, "ERROR: SDL_INIT_VIDEO");
    }

    window = SDL_CreateWindow(
        "Snake",
        WINDOW_X,
        WINDOW_Y,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );
    
    if(!window) {
        fprintf(stderr, "ERROR: !window");
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(!renderer) {
        fprintf(stderr, "!renderer");
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);


    int grid_x = (WINDOW_WIDTH / 2) - (GRID_DIM / 2);
    int grid_y = (WINDOW_HEIGHT / 2) - (GRID_DIM / 2);

    int flash = 0;
    bool quit = false;
    SDL_Event event;

    while(!quit) {
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYUP:
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_UP:
                            head->dir = SNAKE_UP;
                            break;
                        case SDLK_DOWN:
                            head->dir = SNAKE_DOWN;
                            break;
                        case SDLK_LEFT:
                            head->dir = SNAKE_LEFT;
                            break;
                        case SDLK_RIGHT:
                            head->dir = SNAKE_RIGHT;
                            break;
                    }
                    break;
            }
        }

        SDL_RenderClear(renderer);
        //RENDER LOOP START

        move_snake();
        detect_apple();
        detect_crash();




        render_grid(renderer, grid_x, grid_y);
        render_snake(renderer, grid_x, grid_y);

        if(Apple.score % 10 == 0 && Apple.score != 0 ) {
            flash = 10;
        }
        if(flash > 0) {
            flash_snake(renderer, grid_x, grid_y);
            flash--;
        }


        render_apple(renderer, grid_x, grid_y);


        render_score(renderer, WINDOW_WIDTH / 2 - 100, 50);
        render_top_score(renderer, WINDOW_WIDTH / 2 + 200, 50);

        ai();

        //RENDER LOOP END
        SDL_SetRenderDrawColor(renderer, 0x11, 0x11,0x11, 255);
        SDL_RenderPresent(renderer);
        
        SDL_Delay(DELAY);

    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}
