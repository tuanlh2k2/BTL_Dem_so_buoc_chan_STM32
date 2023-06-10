#ifndef _CTR_MPU6050_
#define _CTR_MPU6050_
#include "i2c.h"
#include "math.h"


#define MPU6050_ADDR 0xD0

#define CTR_WHO	  0x75
#define	CTR_SMPL	0x19
#define CTR_DLPF	0x1A
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_CONFIG_REG_2 0x1D
#define GYRO_CONFIG_REG 0x1B
#define CTR_INT_C	0x37
#define CTR_INT_S	0x3A
#define	CTR_TMP_H	0x41
#define	CTR_TMP_L	0x42
#define	CTR_GX_H	0x43
#define	CTR_GX_L	0x44
#define	CTR_GY_H	0x45
#define	CTR_GY_L	0x46
#define CTR_GZ_H	0x47
#define CTR_GZ_L	0x48
#define CTR_PWR_M	0x6B

#define MPU6050_SMPLRT_DIV   0x19
#define MPU6050_CONFIG       0x1a
#define MPU6050_GYRO_CONFIG  0x1b
#define MPU6050_ACCEL_CONFIG 0x1c
#define MPU6050_WHO_AM_I     0x75
#define MPU6050_PWR_MGMT_1   0x6b
#define MPU6050_TEMP_H       0x41
#define MPU6050_TEMP_L       0x42

#define SMPLRT_DIV_REG 0x19
#define GYRO_CONFIG_REG 0x1B
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_XOUT_H_REG 0x43
#define PWR_MGMT_1_REG 0x6B
#define WHO_AM_I_REG 0x75

#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48

#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40


void I2C_MPU6050_Setup (void);
void I2C_MPU6050_Init (void);
float* CTR_READ_GYRO_MPU6050(void);
float *CTR_READ_ACCEL_MPU6050(void);
void CTR_GYRO_MPU6050_setup (void);

#endif