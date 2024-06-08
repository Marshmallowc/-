#pragma once
#include <iostream>
#include <graphics.h>
#include <vector>
#include "Basic.h"
using namespace std;

class Obstacles{
public:
	vector<vector<IMAGE>> img;
	char type[60];// �ϰ��������
	int typeNum;
	string name;
	int imgIndex;
	int imgRunNum;
	int imgTypeNum;
	int imgWidth;
	int imgHeight;
	int x, y;
	int speed;
	int power;
	int score;
	int bonus;// �����Ѷ������з�������
	bool exist;
	bool hited;// ��ʾ�Ƿ��Ѿ�������ײ
	bool pass;// ��ʾ�Ƿ��Ѿ���ͨ��

	Obstacles();
	void setInfo(char type[], string name, int imgNum, int imgTypeNum, int speed, int power, int score, int typeNum, int imgWidth, int imgHeight);
	void loadImage();

};

