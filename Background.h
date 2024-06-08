#pragma once
#include <graphics.h>
#include "Basic.h"
#include <iostream>
#include <vector>
#include "tools.h"
using namespace std;

class Background{
public:
	char sceneType[60];
	string sceneTypeName;
	vector<IMAGE> imgBgs;
	vector<int> speed;
	vector<int> x;// �������ֱ�����x
	vector<int> y;// �������ֱ�����y
	int bgImgNum;
	int difficulty;

	Background();
	void setInfo(char sceneType[], string sceneTypeName, int bgImgNum);
	void addYWithSpeed(int y, int speed);
	void move();
	void update();
};

