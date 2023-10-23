#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

void clear();
void draw_field(int ball_x, int ball_y, int left_racket_pos, int right_racket_pos, const char *player1_name,
                const char *player2_name, int player1_score, int player2_score, char *time);
int keyboard_capture(int *racket_1, int *racket_2);

int main() {
    int racket1 = 12, racket2 = 10, ball_x = 40, ball_y = 16, score1 = 0, score2 = 0, vector1 = -1,
        vector2 = 1, height = 25;
    time_t start_time = time(NULL);

    while ((score1 < 21 && score2 < 21)) {
        time_t current_time = time(NULL);
        int elapsed_time = current_time - start_time;

        int hours = elapsed_time / 3600;           // количество часов
        int minutes = (elapsed_time % 3600) / 60;  // количество минут
        int seconds = elapsed_time % 60;           // количество секунд

        char buffer[80];
        sprintf(buffer, "%02d:%02d:%02d", hours, minutes,
                seconds);  // форматирование строки
        draw_field(ball_x, ball_y, racket1, racket2, "Player_1", "Player_2", score1, score2, buffer);

        if (ball_y >= height - 1 || ball_y <= 1) {
            vector2 *= -1;
        }

        if ((ball_x > 74) && (ball_y > racket2 - 1 && ball_y < racket2 + 1)) {
            vector1 *= -1;
        } else if ((ball_x < 4) && (ball_y > racket1 - 1 && ball_y < racket1 + 1)) {
            vector1 *= -1;
        }

        if ((ball_x < 2) && (ball_y < racket1 - 1 || ball_y > racket1 + 1)) {
            score2 += 1;
            ball_x = 40;
            ball_y = 12;
            vector1 *= -1;

        } else if ((ball_x > 78) && (ball_y < racket2 - 1 || ball_y > racket2 + 1)) {
            score1 += 1;
            ball_x = 40;
            ball_y = 12;
            vector1 *= -1;
        }

        ball_x += 2 * vector1;
        ball_y += 2 * vector2;

        keyboard_capture(&racket1, &racket2);
    }
    // draw_field(ball_x, ball_y, racket1, racket2, "Player_1", "Player_2",
    // score1,
    //    score2, buffer);
}

void draw_field(int ball_x, int ball_y, int left_racket_pos, int right_racket_pos, const char *player1_name,
                const char *player2_name, int player1_score, int player2_score, char *time) {
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
                "************************* %s **********************************"
                "**************\n",
                result_1, time);
        } else {
            printf(
                "*****************************************************************"
                "**************\n"
                "************* Player_1 победил Player_2 с отрывом в %d баллов! "
                "*****************\n"
                "\n************************ %s ******************************"
                "********\n",
                result_1, time);
        }

    } else if (player2_score >= 21 && player2_score > player1_score) {
        int result_2 = player2_score - player1_score;
        if ((result_2 > 0 && result_2 < 2) || result_2 == 21) {
            printf(
                "*****************************************************************"
                "**************\n"
                "************* Player_2 победил Player_1 с отрывом в %d балл! "
                "*****************\n"
                "************************* %s **********************************"
                "**************\n",
                result_2, time);
        } else {
            printf(
                "*****************************************************************"
                "**************\n"
                "************* Player_2 победил Player_1 с отрывом в %d баллов! "
                "*****************\n"
                "************************* %s **********************************"
                "***********\n",
                result_2, time);
        }
    } else {
        printf(
            "**********************************************************************"
            "*********\n"
            "*********************  %s-->%d:%d<--%s  ***********************\n"
            "************************* %s ****************************"
            "**\n",
            player1_name, player1_score, player2_score, player2_name, time);
    }
    printf("\n\n");
}
// очистка консоли
void clear(void) {
    printf("\033[2j");
    printf("\033[0;f");
}

int keyboard_capture(int *racket_1, int *racket_2) {
    struct termios old_attr, new_attr;

    // сохраняем текущие настройки терминала
    tcgetattr(STDIN_FILENO, &old_attr);
    new_attr = old_attr;

    // отключаем вывод символов на экран
    new_attr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_attr);

    // ждем нажатия клавиши
    char ch = getchar();

    // возвращаем настройки терминала обратно
    tcsetattr(STDIN_FILENO, TCSANOW, &old_attr);

    // обработка нажатий?
    printf("You pressed the '%d' key.\n", ch);

    if (ch == 97 || ch == 65) {
        *racket_1 -= 1;
        // return 1; //a
    } else if (ch == 122 || ch == 90) {
        *racket_1 += 1;
        // return 2; //z
    } else if (ch == 107 || ch == 75) {
        *racket_2 -= 1;
        // return 3; //k
    } else if (ch == 109 || ch == 77) {
        *racket_2 += 1;
        // return 4; //m
    } else if (ch == 10) {
    } else {
        printf(
            "Ошибка ввода! используйте клавиши: \n'A' и 'Z' - Player_1 \n'K' и "
            "'M' - Player_2 ");
        keyboard_capture(&*racket_2, &*racket_1);
    }

    if (*racket_1 < 1) {
        *racket_1 = 1;
    }
    if (*racket_1 > 21) {
        *racket_1 = 21;
    }
    if (*racket_2 < 1) {
        *racket_2 = 1;
    }
    if (*racket_2 > 21) {
        *racket_2 = 21;
    }

    return 0;
}