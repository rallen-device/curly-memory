/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "sdkconfig.h"
#include "esp_log.h"

/* Can use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO 32

#define MISO   12
#define MOSI   13
#define CLK    14
#define RES_CS 15
#define RES2_CS 16

#define A_MISO   19
#define A_MOSI   23
#define A_CLK    18
#define ADC_CS 5
#define A_SPI_HOST  VSPI_HOST
#define CLK_SPEED   10*1000*1000
#define H_SPI_HOST    HSPI_HOST

#define TRANSFER_SIZE 16

static const char TAG[] = "CMD"; // curly-memory-delay tag

const int wiper0writeAddr = 0b00000000;
const int wiper1writeAddr = 0b00010000;
const int tconwriteAddr = 0b01000000;
const int tcon_0off_1on = 0b11110000;
const int tcon_0on_1off = 0b00001111;
const int tcon_0off_1off = 0b00000000;
const int tcon_0on_1on = 0b11111111;

spi_device_handle_t spi_res1;
spi_device_handle_t spi_res2;
spi_device_handle_t spi_adc;

/*
* Inits the spi line
*/

void init_spi()
{
  ESP_LOGI(TAG, "Initing the SPI bus");
  esp_err_t ret;
  spi_bus_config_t buscfg={
    .miso_io_num=MISO,
    .mosi_io_num=MOSI,
    .sclk_io_num=CLK,
    .quadwp_io_num=-1,
    .quadhd_io_num=-1,
    .max_transfer_sz=TRANSFER_SIZE
  };
  //Initialize the SPI bus
  ret=spi_bus_initialize(H_SPI_HOST, &buscfg, SPI_DMA_CH_AUTO);


  ESP_LOGI(TAG, "Initing the resistor1 spi device");
  spi_device_interface_config_t res1_dev={
    .clock_speed_hz=CLK_SPEED,           //Clock out at 10 MHz
    .mode=0,                                //SPI mode 0
    .spics_io_num=RES_CS,               //CS pin
    .queue_size=7,                          //We want to be able to queue 7 transactions at a time
  };
  ESP_ERROR_CHECK(ret);
  //Attach the LCD to the SPI bus
  ret=spi_bus_add_device(H_SPI_HOST, &res1_dev, &spi_res1);
  ESP_ERROR_CHECK(ret);


  ESP_LOGI(TAG, "Initing the resistor2 spi device");
  spi_device_interface_config_t res2_dev={
    .clock_speed_hz=CLK_SPEED,           //Clock out at 10 MHz
    .mode=0,                                //SPI mode 0
    .spics_io_num=RES2_CS,               //CS pin
    .queue_size=7,                          //We want to be able to queue 7 transactions at a time
  };
  ESP_ERROR_CHECK(ret);
  //Attach the LCD to the SPI bus
  ret=spi_bus_add_device(H_SPI_HOST, &res2_dev, &spi_res2);
  ESP_ERROR_CHECK(ret);


  ESP_LOGI(TAG, "Setting up SPI3 (VSPI)");
  spi_bus_config_t a_buscfg={
    .miso_io_num=A_MISO,
    .mosi_io_num=A_MOSI,
    .sclk_io_num=A_CLK,
    .quadwp_io_num=-1,
    .quadhd_io_num=-1,
    .max_transfer_sz=TRANSFER_SIZE
  };
  //Initialize the SPI bus
  ret=spi_bus_initialize(A_SPI_HOST, &a_buscfg, SPI_DMA_CH_AUTO);


  ESP_LOGI(TAG, "Initing the adc spi device");


  spi_device_interface_config_t adc_dev={
    .clock_speed_hz=CLK_SPEED,           //Clock out at 10 MHz
    .mode=0,                                //SPI mode 0
    .spics_io_num=ADC_CS,               //CS pin
    .queue_size=7,                          //We want to be able to queue 7 transactions at a time
  };
  ESP_ERROR_CHECK(ret);
  //Attach the LCD to the SPI bus
  ret=spi_bus_add_device(A_SPI_HOST, &adc_dev, &spi_adc);
  ESP_ERROR_CHECK(ret);
}

void send_spi(spi_device_handle_t device, uint8_t cmd, uint8_t value)
{
  ESP_LOGI(TAG, "Sending value to spi : %d", value);
  static spi_transaction_t trans;
  memset(&trans, 0, sizeof(spi_transaction_t));
  trans.length = TRANSFER_SIZE;
  trans.flags = SPI_TRANS_USE_TXDATA | SPI_TRANS_USE_RXDATA;
  trans.tx_data[0] = cmd;
  trans.tx_data[1] = value;
  spi_device_transmit(device, &trans);
  ESP_LOGI(TAG, "Rx value from spi : %d %d %d %d %d", trans.rxlength, trans.rx_data[0], trans.rx_data[1], trans.rx_data[2], trans.rx_data[3]);

}

void read_adc(uint8_t single_diff, uint8_t channel)
{
  static spi_transaction_t trans;
  memset(&trans, 0, sizeof(spi_transaction_t));
  trans.length = 3;
  trans.flags = SPI_TRANS_USE_TXDATA | SPI_TRANS_USE_RXDATA;
  trans.tx_data[0] = 1;
  trans.tx_data[1] = (single_diff << 7) | (channel << 4);
  trans.tx_data[3] = 0;
  spi_device_transmit(spi_adc, &trans);
  uint8_t adc = ((trans.rx_data[1] & 3) << 8) + trans.rx_data[2];
  ESP_LOGI(TAG, "Sending value to spi : %d - %d %d %d %d %d", adc, trans.rxlength, trans.rx_data[0], trans.rx_data[1], trans.rx_data[2], trans.rx_data[3]);
}



void app_main(void)
{
  /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
  gpio_reset_pin(BLINK_GPIO);
  /* Set the GPIO as a push/pull output */
  gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

  init_spi();

  uint8_t count1 = 0;
  uint8_t count2 = 0;
  uint8_t value = 0;

  while(1) {
    count1++;
    value = count1;
    if (count1 > 127)
    {
      value = 127 - (count1 - 128);
    }
    send_spi(spi_res2, wiper0writeAddr, value);
    if (count1 == 0)
    {
      vTaskDelay(1);
    }

    read_adc(1, 0);
    vTaskDelay(1000 / portTICK_PERIOD_MS);


  }
}
