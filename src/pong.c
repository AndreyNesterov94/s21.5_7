#include <stdio.h>

void clear();
void draw_field(int ball_x, int ball_y, int left_racket_pos, int right_racket_pos, int player1_score,
                int player2_score);

int main() {
    int racket1 = 12, racket2 = 10, ball_x = 40, ball_y = 16, score1 = 0, score2 = 0, vector1 = -1,
        vector2 = 1, height = 25;
    char k1, k2;

    draw_field(ball_x, ball_y, racket1, racket2, score1, score2);

    while ((score1 < 21 && score2 < 21)) {
        while (1) {
            k1 = getchar();
            if (k1 == '\n') {
                printf("Неправильное введение комнад\n");
                continue;
            } else if (k1 != 'a' && k1 != 'A' && k1 != 'z' && k1 != 'Z' && k1 != ' ') {
                printf("Неправильное введение комнад\n");
                while (getchar() != '\n')
                    ;
                continue;
            } else if (k1 == 'a' || k1 == 'A') {
                racket1 -= 1;
            } else if (k1 == 'z' || k1 == 'Z') {
                racket1 += 1;
            }

            char probel = getchar();
            if (probel == '\n') {
                printf("Неправильное введение комнад\n");
                continue;
            } else if (probel != ' ') {
                printf("Неправильное введение комнад\n");
                while (getchar() != '\n')
                    ;
                continue;
            }

            k2 = getchar();
            if (k2 == '\n') {
                printf("Неправильное введение комнад\n");
                continue;
            } else if (k2 != 'k' && k2 != 'K' && k2 != 'm' && k2 != 'M' && k2 != ' ') {
                printf("Неправильное введение комнад\n");
                while (getchar() != '\n')
                    ;
                continue;
            } else if (k2 == 'k' || k2 == 'K') {
                racket2 -= 1;
            } else if (k2 == 'm' || k2 == 'M') {
                racket2 += 1;
            }
            while (getchar() != '\n')
                ;
            if (racket1 < 1) {
                racket1 = 1;
            }
            if (racket1 > 21) {
                racket1 = 21;
            }
            if (racket2 < 1) {
                racket2 = 1;
            }
            if (racket2 > 21) {
                racket2 = 21;
            }

            if (ball_y >= height - 1 || ball_y <= 1) {
                vector2 *= -1;
            }

            if ((ball_x > 74) && (ball_y > racket2 - 1 && ball_y < racket2 + 1)) {
                vector1 *= -1;
            } else if ((ball_x < 4) && (ball_y > racket1 - 1 && ball_y < racket1 + 1)) {
                vector1 *= -1;
            }

            if ((ball_x < 4) && (ball_y < racket1 - 1 || ball_y > racket1 + 1)) {
                score2 += 1;
                ball_x = 40;
                ball_y = 12;
                vector1 *= -1;

            } else if ((ball_x > 74) && (ball_y < racket2 - 1 || ball_y > racket2 + 1)) {
                score1 += 1;
                ball_x = 40;
                ball_y = 12;
                vector1 *= -1;
            }

            ball_x += 2 * vector1;
            ball_y += 2 * vector2;
            //   }
            break;
        }
        draw_field(ball_x, ball_y, racket1, racket2, score1, score2);
    }
}
void draw_field(int ball_x, int ball_y, int left_racket_pos, int right_racket_pos, int player1_score,
                int player2_score) {
    int left_racket_y = left_racket_pos;
    int right_racket_y = right_racket_pos;

    int FIELD_WIDTH = 80;
    int FIELD_HEIGHT = 25;
    clear();
    // рисуем поле для игры?
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            if ((i == 0 || i == FIELD_HEIGHT - 1) && !(ball_y == i && ball_x == j)) {
                putchar('-');
            } else if ((j == 0 || j == FIELD_WIDTH - 1) && !(ball_y == i && ball_x == j)) {
                putchar('|');
            } else if (ball_y == i && ball_x == j) {
                putchar('O');
            } else if (j == 1 && left_racket_y == i) {
                putchar('#');
            } else if (j == 1 && left_racket_y + 1 == i) {
                putchar('#');
            } else if (j == 1 && left_racket_y + 2 == i) {
                putchar('#');
            } else if (j == FIELD_WIDTH - 2 && right_racket_y == i) {
                putchar('#');
            } else if (j == FIELD_WIDTH - 2 && right_racket_y + 1 == i) {
                putchar('#');
            } else if (j == FIELD_WIDTH - 2 && right_racket_y + 2 == i) {
                putchar('#');
            } else {
                putchar(' ');
            }
        }
        putchar('\n');
    }

    // Выполняем форматированный вывод строки с очками
    if (player1_score >= 21 && player1_score > player2_score) {
        int result_1 = player1_score - player2_score;
        if ((result_1 > 0 && result_1 < 2) || result_1 == 21) {
            printf(
                "*****************************************************************"
                "**************\n"
                "************* Player_1 победил Player_2 с отрывом в %d балл! "
                "*****************\n"
                "*****************************************************************"
                "**************\n",
                result_1);
        } else {
            printf(
                "*****************************************************************"
                "**************\n"
                "************* Player_1 победил Player_2 с отрывом в %d баллов! "
                "*****************\n"
                "*****************************************************************"
                "**************\n",
                result_1);
        }

    } else if (player2_score >= 21 && player2_score > player1_score) {
        int result_2 = player2_score - player1_score;
        if ((result_2 > 0 && result_2 < 2) || result_2 == 21) {
            printf(
                "*****************************************************************"
                "**************\n"
                "************* Player_2 победил Player_1 с отрывом в %d балл! "
                "*****************\n"
                "*****************************************************************"
                "**************\n",
                result_2);
        } else {
            printf(
                "*****************************************************************"
                "**************\n"
                "************* Player_2 победил Player_1 с отрывом в %d баллов! "
                "*****************\n"
                "*****************************************************************"
                "**************\n",
                result_2);
        }
    } else {
        printf(
            "*****************************************************************"
            "*****"
            "*********\n"
            "*********************  Player_1-->%d:%d<--Player2 "
            "***********************\n"
            "*****************************************************************"
            "*****"
            "*********\n",
            player1_score, player2_score);
    }
    printf("\n\n");
}

// Очистка консоли
void clear(void) {
    printf("\033[2j");
    printf("\033[0;f");
}
