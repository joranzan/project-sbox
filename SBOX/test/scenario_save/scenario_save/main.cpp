#define _CRT_SECURE_NO_WARNINGS
#include "serial.h"
#include <stdio.h>
#include <Windows.h>
#include <sstream>
#include <string>
#include "mpu6050.h"
#include <iostream>
#include <fstream>
using namespace std;

// ���� �� ssl �˻� '�ƴϿ�'�� ����
int main()
{
	// ���� �ε�
	ofstream fout;
	fout.open("raw_data.txt");

	// serial init
	Serial* serial = new Serial("COM9", 115200); //�� �κ� ����� �°� ����
	if (!serial->isConnected()) return 0;
	char buf[255];

	printf("\nstart\n");

	mpu6050 my_mpu6050 = { 0 };

	// �� 3000���� ���Ͽ� Write
	for (int i = 0; i < 3000; i++) {
		serial->readLine(buf, 255);

		printf("%s", buf);
		sscanf(buf, "AC:%hd,%hd,%hd,GY:%hd,%hd,%hd", &my_mpu6050.ac_x, &my_mpu6050.ac_y, &my_mpu6050.ac_z, &my_mpu6050.gy_x, &my_mpu6050.gy_y, &my_mpu6050.gy_z);
		fout << my_mpu6050.ac_x << "," << my_mpu6050.ac_y << "," << my_mpu6050.ac_z << "," << my_mpu6050.gy_x << "," << my_mpu6050.gy_y << "," << my_mpu6050.gy_z << endl;
		
	}

	if (fout.is_open() == true) {
		fout.close();
	}

	return 0;
}