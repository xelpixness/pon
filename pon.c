#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
// #include <windows.h>  // для самостоятельного шарика на винде
// #include<unistd.h>    // для самостоятельного шарика на linux

#define FIELD_WIDTH 80
#define FIELD_HEIGHT 25

char key;

int racket_one_pos_x = 5;
int racket_one_pos_y = 10;

int racket_two_pos_x = 74;
int racket_two_pos_y = 10;

int score_one = 0;
int score_two = 0;
int score_to_win = 2;

int ball_pos_x = 40;
int ball_pos_y = 10;

void keyboard();
void drawing_func();
void ball_moving();

int game_running = 1;

int main() {
    printf("*** press Y key to start ***");

    if (score_to_win == score_one) {
        printf("Player 1 WON !!!");
        game_running = 0;
    } else if (score_to_win == score_two) {
        printf("Player 2 WON !!!");
        game_running = 0;
    } else {
        keyboard();
    }

    return 0;
}

void keyboard() {
    while (game_running) {
        if (kbhit()) {
            key = getch();
            switch (key) {
                case 'y':
                    printf("\n");
                    drawing_func();
                    break;
                case 'a':
                    if (racket_one_pos_y != 1) {
                        racket_one_pos_y--;
                    }
                    system("clear");
                    drawing_func();
                    break;
                case 'z':
                    if (racket_one_pos_y != FIELD_HEIGHT - 4) {
                        racket_one_pos_y++;
                    }
                    system("clear");
                    drawing_func();
                    break;
                case 'k':
                    if (racket_two_pos_y != 1) {
                        racket_two_pos_y--;
                    }
                    system("clear");
                    drawing_func();
                    break;
                case 'm':
                    if (racket_two_pos_y != FIELD_HEIGHT - 4) {
                        racket_two_pos_y++;
                    }
                    system("clear");
                    drawing_func();
                    ball_moving();
                    break;
                    // default:
                    //     printf("hm?");
                    //     break;
            }
        }
    }
}

void drawing_func() {
    ball_moving();
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            if (i == 0 || i == FIELD_HEIGHT - 1) {
                printf("#");
            } else if ((j == racket_one_pos_x && i == racket_one_pos_y) ||
                       (j == racket_one_pos_x && i == racket_one_pos_y + 1) ||
                       (j == racket_one_pos_x && i == racket_one_pos_y + 2)) {
                printf("|");
            } else if ((j == racket_two_pos_x && i == racket_two_pos_y) ||
                       (j == racket_two_pos_x && i == racket_two_pos_y + 1) ||
                       (j == racket_two_pos_x && i == racket_two_pos_y + 2)) {
                printf("|");
            } else if (j == 0 || j == FIELD_WIDTH - 1) {
                printf("|");
            } else if (j == ball_pos_x && i == ball_pos_y) {
                printf("o");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    printf("Score player %d - %d  ", score_one, score_two);
}

// для направления использую флаги
// (1 - флаг работает как название переменной)
// (0 - флаг работает в обратную сторону он названия переменной)
int go_down = 1;
int go_right = 1;

void ball_moving() {
    if (ball_pos_y == FIELD_HEIGHT - 2) {
        go_down = 0;
    }

    if (ball_pos_y == 1) {
        go_down = 1;
    }

    if ((ball_pos_x == racket_two_pos_x - 1) &&
        ((ball_pos_y == racket_two_pos_y) || (ball_pos_y == racket_two_pos_y + 1) ||
         ((ball_pos_y == racket_two_pos_y + 2)))) {
        go_right = 0;
    }

    if ((ball_pos_x == racket_one_pos_x + 1) &&
        ((ball_pos_y == racket_one_pos_y) || (ball_pos_y == racket_one_pos_y + 1) ||
         (ball_pos_y == racket_one_pos_y + 2))) {
        go_right = 1;
    }

    // мячик касается правого края:
    // - возвращаем его в точку старта.
    // - добавляем +1 очко первому
    // - на респауне новый шарик начинает лететь в сторону победителя
    if (ball_pos_x == FIELD_WIDTH) {
        score_one++;
        ball_pos_x = 40;
        ball_pos_y = 10;
        go_down = 0;
        go_right = 0;
    }

    // и наоборот когда касается левого края:
    if (ball_pos_x == 0) {
        score_two++;
        ball_pos_x = 40;
        ball_pos_y = 10;
        go_down = 1;
        go_right = 1;
    }

    if (go_down) {
        ball_pos_y++;
    } else {
        ball_pos_y--;
    }

    if (go_right) {
        ball_pos_x++;
    } else {
        ball_pos_x--;
    }

    printf("Ball position: %d %d\n", ball_pos_x, ball_pos_y);

    // На будущее если захотим вечный двигатель:
    // while (1) {
    //     ball_pos_x++;
    //     ball_pos_y++;
    //     printf("Ball position: %d %d\n", ball_pos_x, ball_pos_y);
    //     Sleep(1000);  // Sleep for 0.5 seconds
    // }
}
