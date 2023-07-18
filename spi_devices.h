#ifndef SPI_DEVICES_H_
#define SPI_DEVICES_H_


typedef enum{
    PGA_GAIN_1 = 0,
    PGA_GAIN_2,
    PGA_GAIN_5,
    PGA_GAIN_10,
    PGA_GAIN_20,
    PGA_GAIN_50,
    PGA_GAIN_100,
    PGA_GAIN_200,
} pga_gains;

typedef enum{
    PGA_VCAL_CH0 = 0,
    PGA_CH1 = 1,
    PGA_CAL1 = 12,
    PGA_CAL2 = 13,
    PGA_CAL3 = 14,
    PGA_CAL4 = 15,
} pga_channel;


#define PGA_WRITE_COMMAND 0b00101010

void set_pga(pga_gains gain,pga_channel channel);
void set_offset_radj(uint8_t value);
void set_trig_radj(uint8_t value);
void cleanup();
void init_devices();

#endif