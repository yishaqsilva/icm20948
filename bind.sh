#!/bin/bash

c++ -O3 -Wall -shared -std=c++11 -fPIC \
$(python3 -m pybind11 --includes) \
bind.cpp icm20948.cpp \
-o icm20948$(python3 -m pybind11 --extension-suffix)
