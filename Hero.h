#pragma once
#include<iostream>
#include<vector>
#include<graphics.h>
#include "tools.h"
#include "Basic.h"
using namespace std;

class Hero {
public:

	vector<IMAGE> image;
	vector<IMAGE> imageSlip;
	char cname[60];
	string name;
	int x, y;// ����
	int speed;// �ٶ�
	int imageIndex;// ��ǰ��������Ƭ
	int imageNum;// ��ɫ�ܲ���Ƭ��
	int imageSlipNum;// ��ɫ�»���Ƭ��
	int blood;// Ѫ��
	int score;
	bool firstSlipThenJump;
	bool isJump;
	bool isSlip;
	bool jumpDown;
	COLORREF rgb;
	string skillText;

	Hero();
	void setInfo(char cname[], string name, int imageNum, int SlipNum);
	void setSkill(string skill);
	void setRGB(COLORREF rgb);
	void loadImage();
	void move();
	void mixMove();// ��϶���
	void run();// һ֡һ֡�ܲ�
	void jump();// һ֡һ֡��Ծ
	void slip();// һ֡һ֡�»�
	void normalizeY();// ��׼����ɫY����
	void update();// ���½�ɫͼƬ
	void update(int x, int y);
};