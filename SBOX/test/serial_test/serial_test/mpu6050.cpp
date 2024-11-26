#include "mpu6050.h"
#include <stdint.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

float gyro_change_unit_factor = 131.0;

uint32_t timer;


void GetAngle(mpu6050* __my_mpu6050, double ALPHA, ofstream& FOUT)
{
	int accelZ_valid = 1;


	/*X축 방향 회전 각도*/
	double roll;
	double roll_sqrt = sqrt((uint32_t)__my_mpu6050->ac_x * __my_mpu6050->ac_x + (uint32_t)__my_mpu6050->ac_z * __my_mpu6050->ac_z);
	if (roll_sqrt != 0.0)
	{
		roll = atan(__my_mpu6050->ac_y / roll_sqrt) * RAD_TO_DEG;
	}
	else
	{
		roll = 0.0;
	}

	/*Y축 방향 회전 각도*/
	double pitch = 0.0;
	double pitch_sqrt = sqrt((uint32_t)__my_mpu6050->ac_y * __my_mpu6050->ac_y + (uint32_t)__my_mpu6050->ac_z * __my_mpu6050->ac_z);
	if (pitch_sqrt != 0.0)
	{
		pitch = atan2(-1 * __my_mpu6050->ac_x, pitch_sqrt) * RAD_TO_DEG;
	}
	else
	{
		pitch = 0.0;
	}
	/*가속도 센서로는 Z축 방향 회전 각도 계산 힘듬*/
	double yaw_sqrt = sqrt((uint32_t)__my_mpu6050->ac_x * __my_mpu6050->ac_x + (uint32_t)__my_mpu6050->ac_y * __my_mpu6050->ac_y);
	double yaw = 0.0;
	if (__my_mpu6050->ac_z <= 0.01f) {
		accelZ_valid = 0;
		yaw = 0.0;
	}
	else {
		yaw = atan2(yaw_sqrt, __my_mpu6050->ac_z) * RAD_TO_DEG;
		__my_mpu6050->ac_z_angle = yaw;
	}

	//printf("roll : %lf, pitch : %lf , yaw : %lf\n", roll, pitch, yaw);
	__my_mpu6050->ac_x_angle = roll;
	__my_mpu6050->ac_y_angle = pitch;


	double dt = (double)(clock() - timer) / 1000;
	timer = clock();

	double gy_angle_vx = (double)__my_mpu6050->gy_x / gyro_change_unit_factor;
	double gy_angle_vy = (double)__my_mpu6050->gy_y / gyro_change_unit_factor;
	double gy_angle_vz = (double)__my_mpu6050->gy_z / gyro_change_unit_factor;

	//printf("%lf, %lf, %lf\n", gy_angle_vx, gy_angle_vy, gy_angle_vz);
	double temp_x, temp_y, temp_z;

	__my_mpu6050->gy_x_angle += gy_angle_vx * dt;
	__my_mpu6050->gy_y_angle += gy_angle_vy * dt;
	__my_mpu6050->gy_z_angle += gy_angle_vz * dt;

	temp_x = __my_mpu6050->filtered_x_angle + gy_angle_vx * dt;
	temp_y = __my_mpu6050->filtered_y_angle + gy_angle_vy * dt;
	temp_z = __my_mpu6050->filtered_z_angle + gy_angle_vz * dt;

	//printf("\n\r[temp] %3.2f, %3.2f, %3.2f\n\r", temp_x, temp_y, temp_z);

	__my_mpu6050->filtered_x_angle = ALPHA * temp_x + (1 - ALPHA) * __my_mpu6050->ac_x_angle;
	__my_mpu6050->filtered_y_angle = ALPHA * temp_y + (1 - ALPHA) * __my_mpu6050->ac_y_angle;

	if (!accelZ_valid) {
		if (__my_mpu6050->filtered_z_angle > temp_z) __my_mpu6050->filtered_z_angle = temp_z + 0.001;
		else if (__my_mpu6050->filtered_z_angle < temp_z) __my_mpu6050->filtered_z_angle = temp_z - 0.001;
	}
	else {
		__my_mpu6050->filtered_z_angle = 0.9995 * temp_z + (1 - 0.9995) * __my_mpu6050->ac_z_angle;
		/*printf("\r\nfilteredANGLE : %.2f\r\n", __my_mpu6050->filtered_z_angle);*/
	}

	printf("#ACC:%3.2f,%3.2f,%3.2f#GYR:%3.2f,%3.2f,%3.2f#FIL:%3.2f,%3.2f,%3.2f\r\n", __my_mpu6050->ac_x_angle, __my_mpu6050->ac_y_angle, __my_mpu6050->ac_z_angle, __my_mpu6050->gy_x_angle, __my_mpu6050->gy_y_angle, __my_mpu6050->gy_z_angle, __my_mpu6050->filtered_x_angle, __my_mpu6050->filtered_y_angle, __my_mpu6050->filtered_z_angle);

	FOUT << __my_mpu6050->filtered_x_angle << "," << __my_mpu6050->filtered_y_angle << "," << __my_mpu6050->filtered_z_angle << endl;
	//printf("#FIL:%3.2f,%3.2f,%3.2f\r\n", __my_mpu6050->filtered_x_angle, __my_mpu6050->filtered_y_angle, __my_mpu6050->filtered_z_angle);

}