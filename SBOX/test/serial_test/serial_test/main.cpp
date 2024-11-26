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
double alpha = 0.0; // ���� ������ alpha ���� ����

// ���� �� ssl �˻� '�ƴϿ�'�� ����
int main(int argc, char* argv[])
{
	if (argc != 2) {
		cout << "Usage: ���α׷��̸�.exe alpha_value" << endl;
		return 1;
	}

	alpha = atof(argv[1]); // ���ڿ��� double Ÿ������ ��ȯ�Ͽ� alpha ������ ����
	string alpha_string = string(argv[1]); // ���� �̸��� ���� ��

	ofstream fout;
	// alpha ���� ������ ���ϸ� ����
	string filename = "data\\fil_data_" + alpha_string + ".csv";
	fout.open(filename);

	// ���� �ε�
	ifstream fin;
	fin.open("raw_data.txt");

	printf("\nstart\n");

	// 1: start, 2: end, 3: recoil
	//serial->write("1", 1); 
	//serial->write("3", 1);

	mpu6050 my_mpu6050 = { 0 };

	double alpha = 0.97;

	char buf[256];
	if (fin.is_open() == false) {
		cout << "??" << endl;
	}
	else {
		int cnt = 0;
		cout << "?" << endl;
		while (1) {

			cout << cnt << endl;
			fin >> buf;
			sscanf(buf, "%hd,%hd,%hd,%hd,%hd,%hd", &my_mpu6050.ac_x, &my_mpu6050.ac_y, &my_mpu6050.ac_z, &my_mpu6050.gy_x, &my_mpu6050.gy_y, &my_mpu6050.gy_z);
			GetAngle(&my_mpu6050, alpha, fout);
			cnt++;
			if (fin.eof())
			{
				cout << "[End]" << endl;
				break;
			}
		}

	}
	if (fout.is_open() == true) {
		fout.close();
	}
	if (fin.is_open() == true) {
		fin.close();
	}

	return 0;
}