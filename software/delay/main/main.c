/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "driver/spi_master.h"
#include "sdkconfig.h"
#include "esp_log.h"


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
#define CLK_SPEED   1*1000*1000
#define H_SPI_HOST    HSPI_HOST

#define TRANSFER_SIZE 16

static const char TAG[] = "CMD"; // curly-memory-delay tag

spi_device_handle_t spi_dac;
spi_device_handle_t spi_adc;

#define BUF_SIZE  sizeof(uint16_t)

uint16_t buf[BUF_SIZE];
uint16_t buf_head;
uint16_t buf_tail;

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
  spi_device_interface_config_t dac_dev={
    .clock_speed_hz=CLK_SPEED,           //Clock out at 10 MHz
    .mode=0,                                //SPI mode 0
    .spics_io_num=RES_CS,               //CS pin
    .queue_size=7,                          //We want to be able to queue 7 transactions at a time
  };
  ESP_ERROR_CHECK(ret);
  //Attach the LCD to the SPI bus
  ret=spi_bus_add_device(H_SPI_HOST, &dac_dev, &spi_dac);
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
    .mode=1,                                //SPI mode 0
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

uint16_t read_adc(uint8_t single_diff, uint8_t channel)
{
  static spi_transaction_t trans;
//   memset(&trans, 0, sizeof(spi_transaction_t));
  trans.length = 24;
  trans.flags = SPI_TRANS_USE_TXDATA | SPI_TRANS_USE_RXDATA;
  trans.tx_data[0] = 1;
  trans.tx_data[1] = (single_diff << 7) | (channel << 4);
  trans.tx_data[3] = 0;
//   ESP_LOGI(TAG, "Sending value to spi : %d %d %d %d", trans.tx_data[0], trans.tx_data[1], trans.tx_data[2], trans.tx_data[3]);
  spi_device_transmit(spi_adc, &trans);
  uint16_t adc = ((trans.rx_data[1] & 3) << 8) + trans.rx_data[2];
//   ESP_LOGI(TAG, "Receiving value from spi : %d - %d %d %d %d", adc, trans.rx_data[0], trans.rx_data[1], trans.rx_data[2], trans.rx_data[3]);
  return adc;
}

void send_dac(uint8_t A_B, uint8_t gain, uint8_t shdn, uint16_t data)
{
//   ESP_LOGI(TAG, "Sending value to spi : %d", data);
  static spi_transaction_t trans;
//   memset(&trans, 0, sizeof(spi_transaction_t));
  trans.length = 16;
  trans.flags = SPI_TRANS_USE_TXDATA;
  trans.tx_data[0] = (A_B << 7) | (gain << 5) | (shdn << 4) | (data >> 4);
  trans.tx_data[1] = data << 4;
  spi_device_transmit(spi_dac, &trans);
//   ESP_LOGI(TAG, "Rx value from spi : %d %X %X", trans.rxlength, trans.tx_data[0], trans.tx_data[1]);

}

void buf_add(uint16_t value)
{
  buf[buf_head++] = value;
  if (buf_head == BUF_SIZE)
  {
    buf_head = 0;
  }
}

uint16_t buf_pop()
{
  uint16_t value = buf[buf_tail++];
  if (buf_tail == BUF_SIZE)
  {
    buf_tail = 0;
  }
  return value;
}


void buf_add_delay(uint16_t value, uint16_t delay, uint8_t decay)
{
  uint16_t delay_value = value / decay;
  uint16_t delay_index = buf_head - delay;
  buf[delay_index] = delay_value;
}



void app_main(void)
{
  init_spi();

  uint8_t count1 = 0;
  uint8_t value = 0;

  memset(&buf, 0, sizeof(buf));
  buf_head = 0;
  buf_tail = BUF_SIZE - (BUF_SIZE / 2);

  while(1) {
    count1++;

    // read value from adc as 12 bit value
    value = read_adc(1, 0);

    buf_add(value);
    buf_add_delay(value, BUF_SIZE / 4, 1);

    // send value from adc to dac as 12 bit value
    send_dac(0, 0, 1, buf_pop());

  }
}
