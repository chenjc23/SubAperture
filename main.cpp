#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>	// for exit
#include <complex>
#include "fftUtils.h"
#include "fftw3.h"
#pragma warning(disable:6385)
using namespace std;

int main(){
	/*----------------- 数据提取 --------------------*/
	// 读取dat文件
	const char* dataPath = "./test.dat";
	ifstream fin;
	fin.open(dataPath, ios_base::in | ios_base::binary);

	if (!fin.is_open()) {
		cerr << "Can't open " << dataPath << "for read!" << endl;
		exit(EXIT_FAILURE);
	}

	// 读取文件中前7个double型雷达参数
	double frontParams[7];
	fin.read((char*)frontParams, 7*sizeof(double));

	double startFreq, stopFreq, pulseWidth, PRF, channelGain, ADFreq, Va;
	startFreq = frontParams[0] * 1e6;
	stopFreq = frontParams[1] * 1e6;
	pulseWidth = frontParams[2] * 1e-3;
	PRF = frontParams[3];
	channelGain = frontParams[4];
	ADFreq = frontParams[5] * 1e6;
	Va = frontParams[6];
	Va = 0.10;

	// 读取文件中后3个雷达参数
	int samplePerRecord, pulseNum;
	double lamda;
	fin.read((char*)&samplePerRecord, sizeof(int));
	fin.read((char*)&pulseNum, sizeof(int));
	fin.read((char*)&lamda, sizeof(double));

	// 根据上述部分参数提取原始雷达回波数据
	int16_t ** rawData = new int16_t*[pulseNum];
	for (int i = 0; i < pulseNum; i++) {
		int16_t* tempLine = new int16_t[samplePerRecord];
		fin.read((char*)tempLine, samplePerRecord * sizeof(int16_t));
		rawData[i] = tempLine;
	}
	// 已读取所有数据，关闭文件连接
	fin.close();

	/*----------------- 原始数据预处理 --------------------*/
	cMatrix tempData = malloc_matrix<complex<double>>(pulseNum, samplePerRecord);
	fft_c(rawData, pulseNum, samplePerRecord, 1, tempData);
	/*cout << ttt(1, 1);*/
	
	

	return 0;
}