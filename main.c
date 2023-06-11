#include "stm32f10x.h"
#include "GPIO.h"
#include "interrupt.h"
#include "delay.h"
#include "stdio.h"
#include "i2c_lcd.h"
#include "i2c_mpu6050.h"

// =====================================================================================================

static uint16_t STAGE = 0;
uint32_t i = 0;
float *CTR_MPU6050_getvalue;
char CTR_datasend[32];
int count = 0;
float gtb_X = 0;
float G_sum = 0, Gx = 0, Gz = 0, Gy = 0, Gx_stop,Gy_stop, Gz_stop;
int start = 0;
uint32_t time_change_state = 0;

// =====================================================================================================

void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void Blink_LED_Green(void);


// =====================================================================================================

int main() {
	//config led.
	init_GP(PC,13,OUT50, O_GP_PP); // cf output.
	init_GP(PC,14,OUT50, O_GP_PP); // cf output.
	init_GP(PA,0,IN,I_PP); // cf input.
	init_GP(PA,1,IN,I_PP); // cf input.
	// init interrupt.
	EXTI0_Init();
	EXTI1_Init();
	
	delay_init();
	
	// khoi tao cam bien.
	I2C_MPU6050_Setup();
  I2C_MPU6050_Init();
	
	// Init LCD.
	I2C_LCD_Setup();
	I2C_LCD_Init();
	I2C_LCD_BackLight(1);
	// Xoa LCD.
	I2C_LCD_Clear();
	// Tao mot chuoi ky tu -> dua vao CTR_datasend.
	sprintf(CTR_datasend,"Buoc chan : %d", count);
	// Hien thi chuoi ky tu len man hinh LCD.
	I2C_LCD_Puts(CTR_datasend);
	
	while(1) {
		if(STAGE == 1) {
			I2C_MPU6050_Setup();
			CTR_MPU6050_getvalue = CTR_READ_ACCEL_MPU6050();

			Gx = (CTR_MPU6050_getvalue[0] < 2) ? CTR_MPU6050_getvalue[0] : Gx;
			Gy = (CTR_MPU6050_getvalue[1] < 2) ? CTR_MPU6050_getvalue[1] : Gx;
			Gz = (CTR_MPU6050_getvalue[2] < 2) ? CTR_MPU6050_getvalue[2] : Gz;

			G_sum = pow(Gx, 2) + pow(Gz, 2) + pow(Gy, 2);

		if (start == 0) {
			if (G_sum < 0.96) {
        Gx_stop = CTR_MPU6050_getvalue[0];
        Gy_stop = CTR_MPU6050_getvalue[1];
        Gz_stop = CTR_MPU6050_getvalue[2];
    } else if (0.97 <= G_sum) {
        start = 1;
    }
		} else if (start == 1 && 0.97 <= G_sum) {
				time_change_state++;
				gtb_X = sqrt(pow(Gx - Gx_stop, 2) + pow(Gz - Gz_stop, 2) + pow(Gy - Gy_stop, 2)) + gtb_X;
		} else if (start == 1 && G_sum <= 0.97) {
				gtb_X = gtb_X / time_change_state;
				if (gtb_X >= 0.2 && time_change_state >= 45) {
					count++;
					I2C_LCD_Setup();
					I2C_LCD_Clear();
					//I2C_LCD_NewLine();
					//sprintf(CTR_datasend, "G_tb =  %.3f", gtb_X);
					sprintf(CTR_datasend,"Buoc chan : %d", count);
					I2C_LCD_Puts(CTR_datasend);
				}

				time_change_state = 0;
				gtb_X = 0;
				start = 0;
		}

		i++;
		Delay_Ms(1);

		if (i == 500) {
    // Sang den.
				GPIOC->BSRR |= (1 << 13);
		} else if (i == 1000) {
    // Tat den.
				GPIOC->BSRR |= (1 << 29);
				i = 0;
		}
		} else if(STAGE == 0){
			if(count != 0) {
				count = 0;
				I2C_LCD_Setup();
				I2C_LCD_Clear();
				sprintf(CTR_datasend,"Buoc chan : 0");
				I2C_LCD_Puts(CTR_datasend);
			}
				count = 0;
				GPIOC -> BSRR |= (1 << 29); // Tat den xanh.
				GPIOC -> BSRR |= (1 << 14); // Bat den do.
		}
	}
}
// ngat doi trang thai.
void EXTI0_IRQHandler(void){
	if(EXTI -> PR & (1 << 0)) {
		//GPIOC -> ODR ^= (1 << 13);
		if(STAGE == 1) {
			STAGE = 2;
			GPIOC -> BSRR |= (1 << 29); // Tat den xanh.
			GPIOC -> BSRR |= (1 << 14); // Bat den do.
		} else {
			STAGE = 1;
			// Tat den do.
			GPIOC -> BSRR |= (1 << 30);
		}
		EXTI -> PR |= (1 << 0);
	}
}
// Ngat reset.
void EXTI1_IRQHandler(void) {
	if(EXTI -> PR & (1 << 1)) {
		GPIOC -> ODR |= (1 << 14);
		STAGE = 0;
		EXTI -> PR |= (1 << 1);
	}
}