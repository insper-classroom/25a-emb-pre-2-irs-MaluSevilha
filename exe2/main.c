#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int LED_PIN = 4;
const int BTN_PIN = 28;
volatile int g_but_flag = 0;

void btn_callback(uint gpio, uint32_t events) {
  g_but_flag = 1;
}

int main() {
  int led_status = 0;
  stdio_init_all();

  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);

  gpio_init(BTN_PIN);
  gpio_set_dir(BTN_PIN, GPIO_IN);
  gpio_pull_up(BTN_PIN);
  gpio_set_irq_enabled_with_callback(
    BTN_PIN, GPIO_IRQ_EDGE_RISE, true, &btn_callback);

  while (true) {
    if(g_but_flag){
      led_status = !led_status;
      gpio_put(LED_PIN, led_status);
      g_but_flag = 0;
    }
  }
}
