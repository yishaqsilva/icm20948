#include "icm20948.h"
#include "pybind11/pybind11.h"

PYBIND11_MODULE(icm20948, m, pybind11::mod_gil_not_used()) {
    pybind11::class_<icm20948>(m, "icm20948")
        .def(pybind11::init<const char*, uint8_t>())
        .def("read_byte", &icm20948::read_byte)
        .def("write_byte", &icm20948::write_byte)
        .def("read_word", &icm20948::read_word)
        .def("get_accel_data", &icm20948::get_accel_data);

    pybind11::class_<accel_data>(m, "accel_data")
        .def_readwrite("x", &accel_data::x)
        .def_readwrite("y", &accel_data::y)
        .def_readwrite("z", &accel_data::z);

}
