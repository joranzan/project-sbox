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
double alpha = 0.0; // 전역 변수로 alpha 값을 선언

// 실행 전 ssl 검사 '아니오'로 변경
int main(int argc, char* argv[])
{
	if (argc != 2) {
		cout << "Usage: 프로그램이름.exe alpha_value" << endl;
		return 1;
	}

	alpha = atof(argv[1]); // 문자열을 double 타입으로 변환하여 alpha 값으로 설정
	string alpha_string = string(argv[1]); // 파일 이름을 위한 값

	ofstream fout;
	// alpha 값을 포함한 파일명 생성
	string filename = "data\\fil_data_" + alpha_string + ".csv";
	fout.open(filename);

	// 파일 로드
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