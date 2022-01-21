#include <lcd_wrapper.h>
#include <mastermind.h>

int main() {
  init();
  
  Serial.begin(9600);
  randomSeed(analogRead(1));
  lcd_init();
  lcd_clear();       
  

  pinMode(LED_BLUE_1, OUTPUT);
  pinMode(LED_BLUE_2, OUTPUT);
  pinMode(LED_BLUE_3, OUTPUT);
  pinMode(LED_BLUE_4, OUTPUT);
  pinMode(LED_RED_1, OUTPUT);
  pinMode(LED_RED_2, OUTPUT);
  pinMode(LED_RED_3, OUTPUT);
  pinMode(LED_RED_4, OUTPUT);
  
  pinMode(BTN_1_PIN , INPUT_PULLUP);
  pinMode(BTN_2_PIN , INPUT_PULLUP);
  pinMode(BTN_3_PIN , INPUT_PULLUP);
  pinMode(BTN_4_PIN , INPUT_PULLUP);

  char* secret = generate_code(false, 4);
  play_game(secret);
  free(secret);
  return 0;
}
