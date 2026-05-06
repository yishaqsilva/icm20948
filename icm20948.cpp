#include "icm20948.h"
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <stdio.h>

icm20948::icm20948(const char* filename, uint8_t addr){ 
        
   fd = open(filename, O_RDWR);
   this->addr = addr;

   if (fd < 0){
        printf("Unable to open file %s\n", filename);
   }
   if (ioctl(fd, I2C_SLAVE, addr) < 0){
        printf("Unable to set slave address %x\n", this->addr);
   }

   accel_fs_sel = 0;
}

uint8_t icm20948::read_byte(uint8_t reg){

    uint8_t response = 0x00;

    struct i2c_msg msgs[2] = {
    
    {.addr = addr, .flags = 0, .len = 1, .buf = &reg},
    {.addr = addr, .flags = I2C_M_RD, .len = 1, .buf = &response}

    };
    
    struct i2c_rdwr_ioctl_data data = {
    
    .msgs = msgs, .nmsgs = 2

   };

    ioctl(fd, I2C_RDWR, &data);

    return response;
}

int icm20948::write_byte(uint8_t reg, uint8_t byte){
    
    uint8_t msg[2] = {reg, byte}; 

    return write(fd, msg, 2);
}

uint16_t icm20948::read_word(uint8_t regA, uint8_t regB){
    
    uint16_t word = read_byte(regA);

    return word << 8 | read_byte(regB);
}

void icm20948::set_bank(uint8_t bank){
    write_byte(0x7F, bank << 4);
}

uint8_t icm20948::get_accel_fs_sel(){
    
    return accel_fs_sel;
}

void icm20948::set_accel_fs_sel(uint8_t fs_sel){

    set_bank(2);
    uint8_t byte = read_byte(0x14) | (fs_sel << 1);
    write_byte(0x14, byte);

    accel_fs_sel = fs_sel;
}

accel_data icm20948::get_accel_data(){
    

    float scale_ranges[4] = {16384.0f, 8192.0f, 4096.0f, 2048.0f};
    float fs = scale_ranges[accel_fs_sel];

    set_bank(0);

    accel_data dat = {
        
        .x = read_word(0x2D, 0x2E) / fs,
        .y = read_word(0x2F, 0x30) / fs,
        .z = read_word(0x31, 0x32) / fs
    };
    
    return dat;
}

gyro_data icm20948::get_gyro_data(){

    gyro_data dat = {};

    return dat;
}
