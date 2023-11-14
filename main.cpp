#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery.h"
#include <type_traits>

#define TAMPER_BUTTON_PIN GPIO_PIN_11

bool b1;

DigitalOut led1(LED1);
InterruptIn button(PI_11);
//InterruptIn button2(PI_11);
//DigitalOut flash(LED4);

// https://os.mbed.com/docs/mbed-os/v6.16/apis/thread.html
// https://os.mbed.com/questions/80722/Using-Multiple-Thread/

Thread thread_led;
Thread thread_lcd_text;
Thread thread_button;


void led_thread(DigitalOut *led1) {
  while (true) {
    *led1 = !*led1;

    ThisThread::sleep_for(1s);
  }
}

void lcd_thread() {
  while (true) {
    BSP_LCD_DisplayStringAt(0, 0, (uint8_t *)"0100 0110 1001 1011 0100 1111 0110 1010 0101 1101 1010 0101", CENTER_MODE);
    //BSP_LCD_DisplayStringAt(0, 25, (uint8_t *)"How do you define real?", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 25, (uint8_t *)button.read(), CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 50, (uint8_t *)"0101 1101 1010 0101 0100 0110 1001 1011 0100 1111 0110 1010", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 75, (uint8_t *)"They are watching.", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 100, (uint8_t *)"1111 0110 1010 0101 1101 1010 0101 0100 0110 1001 1011 0100", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 125, (uint8_t *)"Follow the bunny.", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 150, (uint8_t *)"0100 0110 1001 1011 0100 1111 0110 1010 0101 1101 1010 0101", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 175, (uint8_t *)"Knock knock...", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 200, (uint8_t *)"1010 0101 1101 1010 0101 0100 0110 1001 1011 0100 1111 0110", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 225, (uint8_t *)"Neo", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 250, (uint8_t *)"0100 0110 1001 1011 1101 1010 0101 0100 1111 0110 1010 0101", CENTER_MODE);

    ThisThread::sleep_for(1s);
    BSP_LCD_Clear(LCD_COLOR_BLACK);
    ThisThread::sleep_for(1s);
  }
}

void button_thread() { 
    /*
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
    BSP_LCD_Clear(LCD_COLOR_BLACK);
    BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGREEN);
    */
        BSP_LCD_Clear(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAt(0, 125, (uint8_t *)"Tlacitko zmacknuto...", CENTER_MODE);
        led1 = true;
        
        
    }

int main() {
  thread_led.start(callback(led_thread, &led1));
  thread_lcd_text.start(lcd_thread);
  //thread_button.start(callback(button_thread, &button));

    button.rise(&button_thread);

    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
    BSP_LCD_Clear(LCD_COLOR_BLACK);
    BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGREEN);
      

  while (true) {

  }
}
