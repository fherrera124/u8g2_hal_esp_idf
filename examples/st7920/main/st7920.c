#include "u8g2.h"
#include "u8g2_esp32_hal.h"
#include <esp_log.h>
#include <stdio.h>

static const char* TAG = "st7920_example";

void app_main()
{
    u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT();
    u8g2_esp32_hal.bus.spi.clk = GPIO_NUM_14;
    u8g2_esp32_hal.bus.spi.mosi = GPIO_NUM_13;
    u8g2_esp32_hal.bus.spi.cs = GPIO_NUM_15;
    u8g2_esp32_hal.bus.spi.flags = SPI_DEVICE_POSITIVE_CS; // https://www.esp32.com/viewtopic.php?p=88613#p88613
    u8g2_esp32_hal.bus.spi.clock_speed_hz = 100000;
    u8g2_esp32_hal_init(u8g2_esp32_hal);

    u8g2_t u8g2; // a structure which will contain all the data for one display
    u8g2_Setup_st7920_s_128x64_f(&u8g2, U8G2_R0, u8g2_esp32_spi_byte_cb,
        u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure

    ESP_LOGI(TAG, "u8g2_InitDisplay");
    u8g2_InitDisplay(&u8g2); // send init sequence to the display, display is in
                             // sleep mode after this,

    u8g2_SetPowerSave(&u8g2, 0); // wake up display
    u8g2_ClearBuffer(&u8g2);

    u8g2_SetFont(&u8g2, u8g2_font_ncenB14_tr);

    const char* text = "Hello World!";
    uint16_t    text_width = u8g2_GetStrWidth(&u8g2, text);
    uint16_t    text_height = u8g2_GetMaxCharHeight(&u8g2);

    uint16_t x = (128 - text_width) / 2;
    uint16_t y = (64 + text_height) / 2;

    u8g2_DrawFrame(&u8g2, x - 2, y - text_height - 2, text_width + 4, text_height + 4);
    u8g2_DrawStr(&u8g2, x, y, text);
    u8g2_SendBuffer(&u8g2);
    ESP_LOGI(TAG, "All done!");
}