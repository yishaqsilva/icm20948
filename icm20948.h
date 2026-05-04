#ifndef ICM20948_H
#define ICM20948_H
#include <cstdint>

class icm20948 {

    private:
         uint8_t addr;
         int fd;

    public:
        icm20948(const char* i2c_bus, uint8_t addr); //I2C
        icm20948(const char* spi_device); //SPI

        int write_byte(uint8_t reg, uint8_t byte);

        uint8_t read_byte(uint8_t reg);
        uint16_t read_word(uint8_t regA, uint8_t regB);
        accel_data get_accel();
};

#endif
