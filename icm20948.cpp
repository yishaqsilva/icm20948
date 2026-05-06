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

   accel_fs = 0;
   gyro_fs = 0;
   bank = 21; //random value

   set_bank(0);

   write_byte(PWR_MGMT_1, 0x01);
   write_byte(PWR_MGMT_2, 0x00);
   usleep(100);
}

uint8_t icm20948::who_am_i(){

    return read_byte(WHO_AM_I);
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

int16_t icm20948::read_word(uint8_t regA, uint8_t regB){
    
    int16_t word = read_byte(regA);

    return word << 8 | read_byte(regB);
}

void icm20948::set_bank(uint8_t bank){
    if (this->bank != bank){
        write_byte(0x7F, bank << 4);
    }
}

void icm20948::set_accel_fs(uint8_t fs){

    set_bank(2);
    uint8_t old = read_byte(ACCEL_CONFIG);
    old &= ~0x06;
    write_byte(ACCEL_CONFIG, old | (fs << 1));

    float scale_ranges[4] = {16384.0f, 8192.0f, 4096.0f, 2048.0f};
    accel_fs = scale_ranges[fs];
}

accel_data icm20948::get_accel_data(){

    set_bank(0);

    accel_data dat = {
 
        .x = read_word(0x2D, 0x2E) / accel_fs,
        .y = read_word(0x2F, 0x30) / accel_fs,
        .z = read_word(0x31, 0x32) / accel_fs
    };

    return dat;
}

void icm20948::set_gyro_fs(uint8_t fs){

    set_bank(2);
    uint8_t old = read_byte(GYRO_CONFIG_1);
    old &= ~0x06;
    write_byte(GYRO_CONFIG_1, old | (fs << 1));

    float scale_ranges[4] = {131.0f, 65.5f, 32.8f, 16.4f};
    gyro_fs = scale_ranges[fs];
}

gyro_data icm20948::get_gyro_data(){
    
    set_bank(0);
    
    gyro_data dat = {
        .x = read_word(0x33, 0x34) / gyro_fs,
        .y = read_word(0x35, 0x36) / gyro_fs,
        .z = read_word(0x37, 0x38) / gyro_fs
    };

    return dat;
}

float icm20948::get_temp(){

    set_bank(0);
    int16_t raw = read_word(0x39, 0x3A);
    float temp = ((raw - ICM20948_ROOM_TEMP_OFFSET) / ICM20948_TEMPERATURE_SENSITIVITY) + ICM20948_TEMPERATURE_DEGREES_OFFSET;

    return temp;
}
