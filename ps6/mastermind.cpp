#include <Arduino.h>
#include "mastermind.h"
#include "lcd_wrapper.h"

void get_score(const char* secret, const char* guess, int* peg_a, int* peg_b) {

    int help_secret = 0;
    int help_guess = 0;

    for (int index = 0; index < strlen(secret); index++) {
        if (secret[index] == guess[index]) *peg_a += 1;
    }
    for (int numbers = 0; numbers < 10; numbers++) {
        for (int index = 0; index < strlen(secret); index++) {
            if (secret[index] == numbers + 48) help_secret++;
            if (guess[index] == numbers + 48) help_guess++;
        }
        *peg_b += (help_guess > help_secret) ? help_secret : help_guess;
        help_secret = 0;
        help_guess = 0;
    }
    *peg_b -= *peg_a;
}

char* generate_code(bool repeat, int length) {

    if (length < 1) {
        return 0;
    }
    if (length > 10 && repeat == 0) {
        return 0;
    }
    char* result = (char*)calloc(length + 1, sizeof(char));
    if (repeat) {
        for (int i = 0; i < length; i++) {
            result[i] = random(0, 10) + 48;
            result[i + 1] = '\0';
        }
    }
    else {
        int help = 0;
        for (int i = 0; i < length; i++) {
            help = random(0, 10) + 48;
            int j = 0;
            for (j = 0; j < i; j++) {
                if (help == (int)result[j]) break;
            }
            if (j == i) {
                result[i] = (int)help;
                result[i + 1] = '\0';
            }
            else i--;
        }
    }
    return result;
}
void render_history(char* secret, char** history, const int entry_nr) {
    lcd_print_at(4, 0, history[entry_nr]);

    int a = 0;
    int b = 0;
    get_score(secret, history[entry_nr], &a, &b);
    char score[3];
    score[0] = 65;
    score[1] = a + 48;
    score[2] = 66;
    score[3] = b + 48;
    score[4] = '\0';
    lcd_print_at(9, 0, score);
}

void render_leds(const int peg_a, const int peg_b) {
    char leds[8] = { LED_RED_1, LED_RED_2 , LED_RED_3 , LED_RED_4, LED_BLUE_1, LED_BLUE_2, LED_BLUE_3 , LED_BLUE_4 };

    if (peg_a > 0) {
        for (int i = 0; i < peg_a; i++) {
            analogWrite(leds[i], 255);
        }
    }
    if (peg_b > 0) {
        for (int i = 4 + peg_a; i < peg_b + 4 + peg_a; i++) {
            analogWrite(leds[i], 255);
        }
    }
}
void turn_off_leds() {
    analogWrite(LED_BLUE_1, 0);
    analogWrite(LED_RED_1, 0);
    analogWrite(LED_BLUE_2, 0);
    analogWrite(LED_RED_2, 0);
    analogWrite(LED_BLUE_3, 0);
    analogWrite(LED_RED_3, 0);
    analogWrite(LED_BLUE_4, 0);
    analogWrite(LED_RED_4, 0);
}

void play_game(char* secret) {

    lcd_clear();
    lcd_print_at(0, 0, "Welcome to");
    lcd_print_at(3, 1, "MasterMind!!!");
    delay(2000);
    lcd_clear();
    lcd_print_at(0, 0, "You have to");
    lcd_print_at(0, 1, "guess my code");
    delay(2000);
    lcd_clear();
    lcd_print_at(0, 0, "My code: ");
    //delay(2000);
    //lcd_clear();
    //lcd_print_at(0, 0, secret);

    char* guess = (char*)calloc(5, sizeof(char));
    char** history = malloc(sizeof(char*) * 11);
    for (int i = 0; i < 11; i++) {
        history[i] = malloc(5 * sizeof(char));
    }

    char* help = (char*)calloc(5, sizeof(char));
    int millis_time = 0;
    int index_history = 0;
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 4; j++) {
            guess[j] = 48;
            help[j] = 0;
        }
        lcd_print_at(0, 1, "Your guess:");
        lcd_print_at(11, 1, "0000");
        while (digitalRead(BTN_ENTER_PIN) == LOW) {
            for (int j = 0; j < 4; j++) {
                if (digitalRead(BTN_1_PIN + j) == HIGH && help[j] == 0 && millis() - millis_time > 250) {
                    help[j] = 1;
                    if (j == 1 && digitalRead(BTN_1_PIN) == HIGH) {
                        if (i + index_history > 0) {
                            index_history--;
                            lcd_clear();
                            render_history(secret, history, i + index_history);
                            lcd_print_at(0, 1, "Your guess:");
                            lcd_print_at(11, 1, guess);
                        }
                    }
                    else if (j == 2 && digitalRead(BTN_1_PIN) == HIGH) {
                        if (i + index_history < i) {
                            index_history++;
                            lcd_clear();
                            if (i + index_history < i) render_history(secret, history, i + index_history);
                            else lcd_print_at(0, 0, "My code: ");
                            lcd_print_at(0, 1, "Your guess:");
                            lcd_print_at(11, 1, guess);
                        }
                    }
                    else {
                        millis_time = millis();
                        guess[j] = (guess[j] != 57) ? guess[j] + 1 : 48;
                        lcd_print_at(11, 1, guess);
                    }
                }
                if (digitalRead(BTN_1_PIN + j) == LOW && help[j] == 1) {
                    help[j] = 0;
                }
            }
        }
        strcpy(history[i], guess);
        int a = 0;
        int b = 0;
        turn_off_leds();
        get_score(secret, guess, &a, &b);
        render_leds(a, b);
        if (a == 4) {
            lcd_clear();
            lcd_print_at(0, 0, "Congratulations ");
            lcd_print_at(0, 1, "you won > <");
            for (int j = 0; j < 10; j++) {
                turn_off_leds();
                analogWrite(LED_RED_1, 255);
                delay(200);
                analogWrite(LED_RED_1, 0);
                analogWrite(LED_RED_2, 255);
                delay(200);
                analogWrite(LED_RED_2, 0);
                analogWrite(LED_RED_3, 255);
                delay(200);
                analogWrite(LED_RED_3, 0);
                analogWrite(LED_RED_4, 255);
                delay(200);
                analogWrite(LED_RED_4, 0);
                lcd_print_at(10, 1, "-");
                turn_off_leds();
                analogWrite(LED_BLUE_4, 255);
                delay(200);
                analogWrite(LED_BLUE_4, 0);
                analogWrite(LED_BLUE_3, 255);
                delay(200);
                analogWrite(LED_BLUE_3, 0);
                analogWrite(LED_BLUE_2, 255);
                delay(200);
                analogWrite(LED_BLUE_2, 0);
                analogWrite(LED_BLUE_1, 255);
                delay(200);
                analogWrite(LED_BLUE_1, 0);
                lcd_print_at(10, 1, "<");
            }
            free(guess);
            free(history);
            return;
        }
        delay(300);
    }
    lcd_clear();
    lcd_print_at(0, 0, "You lose :(");
    lcd_print_at(0, 1, "my code:");
    lcd_print_at(10, 1, secret);
    turn_off_leds();
    free(guess);
    free(history);
}
