#include "icm20948.h"
#include "pybind11/pybind11.h"

PYBIND11_MODULE(icm29048, m, pybind11::mod_gil_not_used()) {
    pybind11::class_<icm20948>(m, "icm20948")
        .def(pybind11::init<const char*, uint8_t>())
        .def("read_byte", &icm20948::read_byte)
        .def("write_byte", &icm20948::write_byte);
}
