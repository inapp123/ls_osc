
#ifndef CONFIG_H_
#define CONFIG_H_

#define AD_CLK 47

const static int AD_DATAS[] = {48,49,50,51 ,56,57,58,59 ,60,61,62,63};
#define AD_DATAPIN_COUNT 12
#define GPIO_IN_ADDR 0x1fe00520
#define GPIO_OUT_ADDR 0x1fe00510
#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

#define SPI_SIO_GPIO 46
#define SPI_SCK_GPIO 45
#define SPI_PGA_CS_GPIO 44
#define SPI_OFFSET_RADJ_CS_GPIO 41
#define SPI_TRIGGER_RADJ_CS_GPIO 40

#define COUPLE_MODE_GPIO 38
#define ATTEN_MODE_GPIO 37


#endif




