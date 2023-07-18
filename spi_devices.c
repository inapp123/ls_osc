#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include "config.h"
#include "stdint.h"
#include "assert.h"
#include "spi_devices.h"


#ifndef	CONSUMER
#define	CONSUMER	"LS_OSC_SPI"
#endif

struct gpiod_chip *chip;

struct gpiod_line *line_sck;
struct gpiod_line *line_sio;
struct gpiod_line *line_pga_cs;
struct gpiod_line *line_offset_radj_cs;
struct gpiod_line *line_trigger_radj_cs; 
struct gpiod_line *line_couple_mode; 
struct gpiod_line *line_atten_mode; 

int ret;
#define PGA_CS(value) do{ \
    ret = gpiod_line_set_value(line_pga_cs, value); \
    if (ret < 0) { \
        perror("Set line output failed\n"); \
        assert(0); \
    } \
} while(0);

#define OFFSET_CS(value) do { \
    ret = gpiod_line_set_value(line_offset_radj_cs, value); \
    if (ret < 0) { \
        perror("Set line output failed\n"); \
        assert(0); \
    } \
} while(0);

#define TRIGGER_CS(value) do { \
    ret = gpiod_line_set_value(line_trigger_radj_cs, value); \
    if (ret < 0) { \
        perror("Set line output failed\n"); \
        assert(0); \
    } \
} while(0);

#define SCK(value) do { \
    ret = gpiod_line_set_value(line_sck, value); \
    if (ret < 0) { \
        perror("Set line output failed\n"); \
        assert(0); \
    } \
} while(0);

#define SIO(value) do { \
    ret = gpiod_line_set_value(line_sio, value); \
    if (ret < 0) { \
        perror("Set line output failed\n"); \
        assert(0); \
    } \
} while(0);


void set_pga(pga_gains gain,pga_channel channel){
    uint16_t pga_cmd = (PGA_WRITE_COMMAND << 8) | ((uint16_t)gain << 4) | (uint16_t)channel;
    PGA_CS(0);
    for(int i = 0; i < 16; i++){
        SCK(0);
        SIO((pga_cmd >> (15-i)) & 0x1);
        SCK(1);
    }
    SCK(0);
    PGA_CS(1);
}

void set_offset_radj(uint8_t value){
    uint16_t offset_cmd = (0b00010011 << 8) | value; // Write Data , Command executed on both Potentiometers.
    // printf("0x%x\n",offset_cmd);
    SCK(1);
    OFFSET_CS(0);
    for(int i = 0; i < 16; i++){
        SCK(0);
        SIO((offset_cmd >> (15-i)) & 0x1);
        SCK(1);
    }
    SCK(0);
    OFFSET_CS(1);
}

void set_trig_radj(uint8_t value){
    uint16_t trig_cmd = (0b00010011 << 8) | value; // Write Data , Command executed on both Potentiometers.
    SCK(1);
    TRIGGER_CS(0);
    for(int i = 0; i < 16; i++){
        SCK(0);
        SIO((trig_cmd >> (15-i)) & 0x1);
        SCK(1);
    }
    SCK(0);
    TRIGGER_CS(1);
}

void init_devices(){
    char *chipname = "gpiochip0";
    unsigned int val;


    int i;

    chip = gpiod_chip_open_by_name(chipname);
    if (!chip) {
        perror("Open chip failed\n");
        goto end;
    }


#if 1 // getting lines
    line_sck = gpiod_chip_get_line(chip, SPI_SCK_GPIO);
    if (!line_sck) {
        perror("Get sck line failed\n");
        goto close_chip;
    }

    line_sio = gpiod_chip_get_line(chip, SPI_SIO_GPIO);
	if (!line_sio) {
		perror("Get sio line failed\n");
		goto close_chip;
	}

    line_pga_cs = gpiod_chip_get_line(chip, SPI_PGA_CS_GPIO);
	if (!line_pga_cs) {
		perror("Get pga cs line failed\n");
		goto close_chip;
	}

    line_offset_radj_cs = gpiod_chip_get_line(chip, SPI_OFFSET_RADJ_CS_GPIO);
    if (!line_offset_radj_cs) {
        perror("Get offset radj cs line failed\n");
        goto close_chip;
    }

    line_trigger_radj_cs = gpiod_chip_get_line(chip, SPI_TRIGGER_RADJ_CS_GPIO);
    if (!line_trigger_radj_cs) {
        perror("Get trigger radj cs line failed\n");
        goto close_chip;
    }

    
#endif
    

#if 1 // setting lines as output
    ret = gpiod_line_request_output(line_sck, CONSUMER, 0);
    if (ret < 0) {
        perror("Request sck line as output failed\n");
        goto release_line;
    }

    ret = gpiod_line_request_output(line_sio, CONSUMER, 0);
    if (ret < 0) {
        perror("Request sio line as output failed\n");
        goto release_line;
    }

    ret = gpiod_line_request_output(line_pga_cs, CONSUMER, 0);
    if (ret < 0) {
        perror("Request pga cs line as output failed\n");
        goto release_line;
    }

    ret = gpiod_line_request_output(line_offset_radj_cs, CONSUMER, 0);
    if (ret < 0) {
        perror("Request offset radj cs line as output failed\n");
        goto release_line;
    }

    ret = gpiod_line_request_output(line_trigger_radj_cs, CONSUMER, 0);
    if (ret < 0) {
        perror("Request trigger radj cs line as output failed\n");
        goto release_line;
    }
#endif

#if 1// initial condition
    PGA_CS(1);
    OFFSET_CS(1);
    TRIGGER_CS(1);
    SCK(0);
    SIO(0);
#endif

    // sleep(1);

    return;

release_line:
close_chip:
    cleanup();
end:
    return;
}

void cleanup(){
    if(line_sck){
        gpiod_line_release(line_sck);
    }
    if(line_sio){
        gpiod_line_release(line_sio);
    }
    if(line_pga_cs){
        gpiod_line_release(line_pga_cs);
    }
    if(line_offset_radj_cs){
        gpiod_line_release(line_offset_radj_cs);
    }
    if(line_trigger_radj_cs){
        gpiod_line_release(line_trigger_radj_cs);
    }
    gpiod_chip_close(chip);
    return;
}



int main(int argc, char **argv){
    init_devices();
    set_pga(PGA_GAIN_2,PGA_CH1);
    set_offset_radj(0x7f); // middle
    set_trig_radj(0xcf); // middle
    cleanup();
    return 0;
}
