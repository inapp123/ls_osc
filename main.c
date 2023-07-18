#include <gpiod.h>
#include <stdint.h>
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/mman.h>

#ifndef    CONSUMER
#define    CONSUMER    "SHIROGANE"
#endif 



int main(int argc, char **argv)
{
    char *chipname = "gpiochip0";
    int val;
    struct gpiod_chip *chip;
    struct gpiod_line * line[AD_DATAPIN_COUNT];
    int  ret;

    chip = gpiod_chip_open_by_name(chipname);
    if (!chip) {
        perror("Open chip failed\n");
        goto end;
    }
    printf("chip oK!\n");

    

    int mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (mem_fd < 0){
        perror("devmem open failed\n");
        goto end;
    }

    void *map_base = mmap(NULL,
        MAP_SIZE,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        mem_fd,
        GPIO_OUT_ADDR & ~MAP_MASK);

    if(map_base == (void *) -1) {
        perror("mmap failed\n");
        goto end;
    }
    printf("gpio in register mapped at address %p.\n", map_base); 
    volatile uint64_t * gpio_in_ptr = (volatile uint64_t *) (map_base + (GPIO_IN_ADDR & MAP_MASK));
    volatile uint64_t * gpio_out_ptr = (volatile uint64_t *) (map_base + (GPIO_OUT_ADDR & MAP_MASK));
    

    // config data pins(input)
    for(uint8_t i = 0 ; i < AD_DATAPIN_COUNT ; i++){        
        line[i] = gpiod_chip_get_line(chip,AD_DATAS[i]);
        if (line[i] == NULL) {
            printf("Get line failed at %d\n",i);
            goto close_chip;
        }

        printf("get line!\n");

        ret = gpiod_line_request_input(line[i], CONSUMER);
        if (ret < 0) {
            perror("Request line as input failed\n");
            goto release_line;
        }
        printf("req input!\n");
    }

    // config clk pin(output)
    
    struct gpiod_line * clkline = gpiod_chip_get_line(chip,AD_CLK);
    if (clkline == NULL) {
        printf("Get clk line failed\n");
        goto close_chip;
    }

    printf("get line!\n");

    ret = gpiod_line_request_output(clkline, CONSUMER, 0);
    if (ret < 0) {
        perror("Request line as output failed\n");
        goto release_line;
    }
    printf("req output!\n");


    // open file to write result;
    FILE *fp;
    fp = fopen("result.txt","w");

    uint64_t gpio_out_reg_now = *gpio_out_ptr;
    uint64_t clk_high_reg = gpio_out_reg_now | (1ULL << AD_CLK);
    uint64_t clk_low_reg = gpio_out_reg_now & !(1ULL << AD_CLK);
    printf("START READING NOW!\n");

    /* Read input 20 times */
    for (uint32_t i = 10000000; i > 0; i--) {
        // ret = gpiod_line_set_value(clkline,0);
        // if (ret < 0) {
        //     perror("out clk failed\n");
        //     goto release_line;
        // }
        // ret = gpiod_line_set_value(clkline,1);
        // if (ret < 0) {
        //     perror("out clk failed\n");
        //     goto release_line;
        // }
        *gpio_out_ptr = clk_low_reg;
        *gpio_out_ptr = clk_high_reg;

        uint64_t invalues = *gpio_in_ptr;
        int ad_result = (invalues >> 56) & 0b11111111;
        // for(uint8_t i = 0; i < AD_DATAPIN_COUNT; i++){
        //     val = gpiod_line_get_value(line[AD_DATAPIN_COUNT - i - 1]);
        //     if (val < 0) {
        //         perror("Read line input failed\n");
        //         goto release_line;
        //     }
        //     ad_result = (ad_result << 1) | (val == 1); 
                
        //     // printf("Intput %d on line #%u\n", val, i);
        // }

        // printf("so it is %d\n",ad_result);
        //sleep(1);
        fprintf(fp,"%d\n",ad_result);
    }

    fclose(fp);

release_line:
    // gpiod_line_release(line);

    for(uint8_t i = 0 ; i < AD_DATAPIN_COUNT ; i++){        
        if (line[i] != NULL) {
            gpiod_line_release(line[i]);
        }
        else{
            printf("pin %d not release as it is null.\n",i);
        }
    }

    if (clkline != NULL){
        gpiod_line_release(clkline);
    }
close_chip:
    gpiod_chip_close(chip);
end:
    return 0;
}
