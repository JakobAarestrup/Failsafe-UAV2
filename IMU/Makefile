#
# Makefile:
#################################################################################


#DEBUG  = -g -O0
DEBUG   = -O3
CC      = gcc
INCLUDE = -I/usr/local/include
CFLAGS  = $(DEBUG) -Wall $(INCLUDE) -Winline -pipe

LDFLAGS = -L/usr/local/lib
LDLIBS    = -lwiringPi -lpthread -lm

# Should not alter anything below this line
###############################################################################

SRC     =       main.cpp IMU.cpp I2C.cpp                                               \