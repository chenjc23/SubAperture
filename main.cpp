#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>	// for exit
#include <complex>
#include <cmath>
#include "utils.h"
#include "fftUtils.h"
#include "fftw3.h"

using namespace std;

int main(){
	/*----------------- ������ȡ --------------------*/
	// ��ȡdat�ļ�
	const char* dataPath = "./test.dat";
	ifstream fin;
	fin.open(dataPath, ios_base::in | ios_base::binary);

	if (!fin.is_open()) {
		cerr << "Can't open " << dataPath << "for read!" << endl;
		exit(EXIT_FAILURE);
	}

	// ��ȡ�ļ���ǰ7��double���״����
	double frontParams[7];
	fin.read((char*)frontParams, 7*sizeof(double));

	double startFreq = frontParams[0] * 1e6;
	double stopFreq = frontParams[1] * 1e6;
	double pulseWidth = frontParams[2] * 1e-3;
	double PRF = frontParams[3];
	double channelGain = frontParams[4];
	double ADFreq = frontParams[5] * 1e6;
	double Va = frontParams[6];
	Va = 0.10;

	// ��ȡ�ļ��к�3���״����
	int samplePerRecord, pulseNum;
	double lamda;
	fin.read((char*)&samplePerRecord, sizeof(int));
	fin.read((char*)&pulseNum, sizeof(int));
	fin.read((char*)&lamda, sizeof(double));

	// �����������ֲ�����ȡԭʼ�״�ز����ݣ������ݵ�ʱ��NrΪ��
	int16_t ** rawData = new int16_t*[samplePerRecord];
	for (int i = 0; i < samplePerRecord; i++) {
		int16_t* tempLine = new int16_t[pulseNum];
		fin.read((char*)tempLine, pulseNum * sizeof(int16_t));
		rawData[i] = tempLine;
	}
	// �Ѷ�ȡ�������ݣ��ر��ļ�����
	fin.close();

	/*----------------- ԭʼ����Ԥ���� --------------------*/
	cMatrix tempData = malloc_matrix<complex<double>>(samplePerRecord, pulseNum);
	fft_c(rawData, samplePerRecord, pulseNum, 1, tempData);
	// ȡһ�����Ч������ifft
	cMatrix proData = malloc_matrix<complex<double>>(round(samplePerRecord /2), pulseNum);
	ifft_c(tempData, round(samplePerRecord / 2), pulseNum, 1, proData);
	// �����տ�ʼ�ɼ���һ��ʱ�������


	// ������ת��ΪNaΪ��
	cMatrix transData = transpose(proData, round(samplePerRecord / 2), pulseNum);

	free_matrix(tempData, samplePerRecord, pulseNum);
	free_matrix(proData, round(samplePerRecord / 2), pulseNum);

	/*----------------- �������Ԥ���� --------------------*/
	double Na = pulseNum;
	double Nr = round(samplePerRecord / 2);
	double KFMCW = (stopFreq - startFreq) / pulseWidth;
	double fs = ADFreq / 2;
	double Rmax = 500;
	double Rmin = 50;
	int range_weight = 2;
	int azm_weight = 2;

	// �����ӿ׾������㷨
	SubApertureImaging(transData, Na, Nr, Va, startFreq, PRF, KFMCW, fs, 
						Rmax, Rmin, range_weight, azm_weight);




	
	

	return 0;
}