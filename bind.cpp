#include "icm20948.h"
#include "pybind11/pybind11.h"

PYBIND11_MODULE(icm20948, m, pybind11::mod_gil_not_used()) {
    pybind11::class_<icm20948>(m, "icm20948")
        .def(pybind11::init<const char*, uint8_t>())
        .def("set_bank", &icm20948::set_bank)
        .def("who_am_i", &icm20948::who_am_i)

        .def("read_byte", &icm20948::read_byte)
        .def("write_byte", &icm20948::write_byte)
        .def("read_word", &icm20948::read_word)

        .def("get_accel_data", &icm20948::get_accel_data)
        .def("set_accel_fs", &icm20948::set_accel_fs)

        .def("get_gyro_data", &icm20948::get_gyro_data)
        .def("set_gyro_fs", &icm20948::set_gyro_fs)
        ;

    pybind11::class_<accel_data>(m, "accel_data")
        .def(pybind11::init<>())
        .def_readwrite("x", &accel_data::x)
        .def_readwrite("y", &accel_data::y)
        .def_readwrite("z", &accel_data::z);

    pybind11::class_<gyro_data>(m, "gyro_data")
        .def(pybind11::init<>())
        .def_readwrite("x", &gyro_data::x)
        .def_readwrite("y", &gyro_data::y)
        .def_readwrite("z", &gyro_data::z);

}
