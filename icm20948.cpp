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
   ioctl(fd, I2C_SLAVE, addr); //hi kernel, we have a slave!
   this->addr = addr;
}

uint8_t icm20948::read_byte(uint8_t reg){

    uint8_t response;

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

accel_data icm20948::get_accel(){
        
    accel_data dat;
    
    return dat;
}
