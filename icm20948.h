#ifndef ICM20948_H
#define ICM20948_H
#include <cstdint>

typedef struct {

    float x;
    float y;
    float z;

} accel_data;

typedef struct {

    float x;
    float y;
    float z;

} gyro_data;

class icm20948 {

    private:
         int fd;
         uint8_t addr;
         uint8_t accel_fs_sel;

    public:
        icm20948(const char* i2c_bus, uint8_t addr); //I2C
        void set_bank(uint8_t bank);
        int write_byte(uint8_t reg, uint8_t byte);

        uint8_t read_byte(uint8_t reg);
        int16_t read_word(uint8_t regA, uint8_t regB);
        uint8_t get_accel_fs_sel();
        void set_accel_fs_sel(uint8_t fs_sel);
        accel_data get_accel_data();
        gyro_data get_gyro_data();
};

#endif
