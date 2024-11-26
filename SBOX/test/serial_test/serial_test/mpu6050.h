#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <fstream>

#define RAD_TO_DEG 57.295779513082320876798154814105   //180 / pi

using namespace std;

typedef struct
{
	int16_t gy_x;	
	int16_t gy_y;
	int16_t gy_z;
	int16_t ac_x;
	int16_t ac_y;
	int16_t ac_z;

	double gy_x_angle;
	double gy_y_angle;
	double gy_z_angle;


	double ac_x_angle;
	double ac_y_angle;
	double ac_z_angle;

	double filtered_x_angle;
	double filtered_y_angle;
	double filtered_z_angle;

}mpu6050;


void GetAngle(mpu6050* __my_mpu6050, double ALPHA, ofstream& FOUT);
