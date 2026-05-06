#ifndef ICM20948_H
#define ICM20948_H
#include <cstdint>

#define WHO_AM_I 0x00
#define PWR_MGMT_1 0x06
#define PWR_MGMT_2 0x07

#define ACCEL_CONFIG 0x14
#define GYRO_CONFIG_1 0x01
#define GYRO_CONFIG_2 0x02

#define ICM20948_TEMPERATURE_DEGREES_OFFSET 21.0f
#define ICM20948_TEMPERATURE_SENSITIVITY 333.87f
#define ICM20948_ROOM_TEMP_OFFSET 21.0f

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
         float accel_fs;
         float gyro_fs;
         uint8_t addr;
         uint8_t bank;

    public:
        icm20948(const char* i2c_bus, uint8_t addr); //I2C
        void set_bank(uint8_t bank);
        uint8_t who_am_i();

        int write_byte(uint8_t reg, uint8_t byte);
        uint8_t read_byte(uint8_t reg);
        int16_t read_word(uint8_t regA, uint8_t regB);

        void set_accel_fs(uint8_t fs);
        void set_gyro_fs(uint8_t fs);

        accel_data get_accel_data();
        gyro_data get_gyro_data();
        float get_temp();
};

#endif
