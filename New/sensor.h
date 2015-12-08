/*
        This program  reads the angles from the acceleromter and gyrscope
        on a BerryIMU connected to a Raspberry Pi.
        http://ozzmaker.com/


    Copyright (C) 2014  Mark Williams

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.
    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
    Library General Public License for more details.
    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
    MA 02111-1307, USA
*/
#ifndef SENSOR_H_
#define SENSOR_H_








#define MAG_ADDRESS            0x1D
#define ACC_ADDRESS            0x1D
#define GYR_ADDRESS            0x6B



/** LSM9DS0 Gyro Registers **/
#define WHO_AM_I_G			0x0F
#define CTRL_REG1_G			0x20
#define CTRL_REG2_G			0x21
#define CTRL_REG3_G			0x22
#define CTRL_REG4_G			0x23
#define CTRL_REG5_G			0x24
#define REFERENCE_G			0x25
#define STATUS_REG_G			0x27
#define OUT_X_L_G			0x28
#define OUT_X_H_G			0x29
#define OUT_Y_L_G			0x2A
#define OUT_Y_H_G			0x2B
#define OUT_Z_L_G			0x2C
#define OUT_Z_H_G			0x2D
#define FIFO_CTRL_REG_G			0x2E
#define FIFO_SRC_REG_G			0x2F
#define INT1_CFG_G			0x30
#define INT1_SRC_G			0x31
#define INT1_THS_XH_G			0x32
#define INT1_THS_XL_G			0x33
#define INT1_THS_YH_G			0x34
#define INT1_THS_YL_G			0x35
#define INT1_THS_ZH_G			0x36
#define INT1_THS_ZL_G			0x37
#define INT1_DURATION_G			0x38

//////////////////////////////////////////
// LSM9DS0 Accel/Magneto (XM) Registers //
//////////////////////////////////////////
#define OUT_TEMP_L_XM			0x05
#define OUT_TEMP_H_XM			0x06
#define STATUS_REG_M			0x07
#define OUT_X_L_M			0x08
#define OUT_X_H_M			0x09
#define OUT_Y_L_M			0x0A
#define OUT_Y_H_M			0x0B
#define OUT_Z_L_M			0x0C
#define OUT_Z_H_M			0x0D
#define WHO_AM_I_XM			0x0F
#define INT_CTRL_REG_M			0x12
#define INT_SRC_REG_M			0x13
#define INT_THS_L_M			0x14
#define INT_THS_H_M			0x15
#define OFFSET_X_L_M			0x16
#define OFFSET_X_H_M			0x17
#define OFFSET_Y_L_M			0x18
#define OFFSET_Y_H_M			0x19
#define OFFSET_Z_L_M			0x1A
#define OFFSET_Z_H_M			0x1B
#define REFERENCE_X			0x1C
#define REFERENCE_Y			0x1D
#define REFERENCE_Z			0x1E
#define CTRL_REG0_XM			0x1F
#define CTRL_REG1_XM			0x20
#define CTRL_REG2_XM			0x21
#define CTRL_REG3_XM			0x22
#define CTRL_REG4_XM			0x23
#define CTRL_REG5_XM			0x24
#define CTRL_REG6_XM			0x25
#define CTRL_REG7_XM			0x26
#define STATUS_REG_A			0x27
#define OUT_X_L_A			0x28
#define OUT_X_H_A			0x29
#define OUT_Y_L_A			0x2A
#define OUT_Y_H_A			0x2B
#define OUT_Z_L_A			0x2C
#define OUT_Z_H_A			0x2D
#define FIFO_CTRL_REG			0x2E
#define FIFO_SRC_REG			0x2F
#define INT_GEN_1_REG			0x30
#define INT_GEN_1_SRC			0x31
#define INT_GEN_1_THS			0x32
#define INT_GEN_1_DURATION		0x33
#define INT_GEN_2_REG			0x34
#define INT_GEN_2_SRC			0x35
#define INT_GEN_2_THS			0x36
#define INT_GEN_2_DURATION		0x37
#define CLICK_CFG			0x38
#define CLICK_SRC			0x39
#define CLICK_THS			0x3A
#define TIME_LIMIT			0x3B
#define TIME_LATENCY			0x3C
#define TIME_WINDOW			0x3D






#include <stdint.h>
#include "linux/i2c-dev.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
int file;

void  readBlock(uint8_t command, uint8_t size, uint8_t *data)
{
    int result = i2c_smbus_read_i2c_block_data(file, command, size, data);
    if (result != size)
    {
        printf("Failed to read block from I2C.");
        exit(1);
    }
}

void selectDevice(int file, int addr)
{
        if (ioctl(file, I2C_SLAVE, addr) < 0) {
		 printf("Failed to select I2C device.");
        }
}


void readACC(int  *a)
{
        uint8_t block[6];
        selectDevice(file,ACC_ADDRESS);
        readBlock(0x80 | OUT_X_L_A, sizeof(block), block);

        *a = (int16_t)(block[0] | block[1] << 8);
        *(a+1) = (int16_t)(block[2] | block[3] << 8);
        *(a+2) = (int16_t)(block[4] | block[5] << 8);

}


void readMAG(int  *m)
{
        uint8_t block[6];
        selectDevice(file,MAG_ADDRESS);
        readBlock(0x80 | OUT_X_L_M, sizeof(block), block);

        *m = (int16_t)(block[0] | block[1] << 8);
        *(m+1) = (int16_t)(block[2] | block[3] << 8);
        *(m+2) = (int16_t)(block[4] | block[5] << 8);

}

void readGYR(int *g)
{
	uint8_t block[6];
        selectDevice(file,GYR_ADDRESS);
	readBlock(0x80 | OUT_X_L_G, sizeof(block), block);

        *g = (int16_t)(block[0] | block[1] << 8);
        *(g+1) = (int16_t)(block[2] | block[3] << 8);
        *(g+2) = (int16_t)(block[4] | block[5] << 8);
}


void writeAccReg(uint8_t reg, uint8_t value)
{
    selectDevice(file,ACC_ADDRESS);
  int result = i2c_smbus_write_byte_data(file, reg, value);
    if (result == -1)
    {
        printf ("Failed to write byte to I2C Acc.");
        exit(1);
    }
}

void writeMagReg(uint8_t reg, uint8_t value)
{
    selectDevice(file,MAG_ADDRESS);
  int result = i2c_smbus_write_byte_data(file, reg, value);
    if (result == -1)
    {
        printf("Failed to write byte to I2C Mag.");
        exit(1);
    }
}


void writeGyrReg(uint8_t reg, uint8_t value)
{
    selectDevice(file,GYR_ADDRESS);
  int result = i2c_smbus_write_byte_data(file, reg, value);
    if (result == -1)
    {
        printf("Failed to write byte to I2C Gyr.");
        exit(1);
    }
}


void enableIMU()
{

	__u16 block[I2C_SMBUS_BLOCK_MAX];

        int res, bus,  size;


        char filename[20];
        sprintf(filename, "/dev/i2c-%d", 1);
        file = open(filename, O_RDWR);
        if (file<0) {
		printf("Unable to open I2C bus!");
                exit(1);
        }

        // Enable accelerometer.
        writeAccReg(CTRL_REG1_XM, 0b01100111); //  z,y,x axis enabled, continuos update,  100Hz data rate
        writeAccReg(CTRL_REG2_XM, 0b00100000); // +/- 16G full scale

        //Enable the magnetometer
        writeMagReg( CTRL_REG5_XM, 0b11110000);   // Temp enable, M data rate = 50Hz
        writeMagReg( CTRL_REG6_XM, 0b01100000);   // +/-12gauss
        writeMagReg( CTRL_REG7_XM, 0b00000000);   // Continuous-conversion mode

	 // Enable Gyro
        writeGyrReg(CTRL_REG1_G, 0b00001111); // Normal power mode, all axes enabled
        writeGyrReg(CTRL_REG4_G, 0b00110000); // Continuos update, 2000 dps full scale

}


#endif



