#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;
const int LED_PIN_R = 4;
const int LED_PIN_G = 6;

volatile int red_flag = 0;
volatile int green_flag = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    if (gpio == BTN_PIN_R){
      red_flag = 1;
    }
    else if (gpio == BTN_PIN_G){
      green_flag = 1;
    }
  }
}

int main() {
  int led_r_status = 0;
  int led_g_status = 0;

  stdio_init_all();

  gpio_init(LED_PIN_G);
  gpio_set_dir(LED_PIN_G, GPIO_OUT);
  gpio_init(LED_PIN_R);
  gpio_set_dir(LED_PIN_R, GPIO_OUT);

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);
  gpio_set_irq_enabled_with_callback(
    BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);
  gpio_set_irq_enabled(BTN_PIN_G, GPIO_IRQ_EDGE_RISE, true);
  
  while (true) {
    if(red_flag){
      red_flag = 0;
      led_r_status = !led_r_status;
      gpio_put(LED_PIN_R, led_r_status);
    }

    if(green_flag){
      green_flag = 0;
      led_g_status = !led_g_status;
      gpio_put(LED_PIN_G, led_g_status);
    }
  }
}
