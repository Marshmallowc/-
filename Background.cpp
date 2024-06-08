#include "Background.h"

Background::Background() {
}

void Background::setInfo(char sceneType[], string sceneTypeName, int bgImgNum) {
	//��ʼ������
	sprintf(this->sceneType, sceneType);
	this->sceneTypeName = sceneTypeName;
	this->bgImgNum = bgImgNum;

	//������Ϸ������ͼƬ
	char name[60];
	IMAGE img;
	for (int i = 0; i < bgImgNum; i++) {
		sprintf(name, "res/%sBg%d.png", this->sceneTypeName, i + 1);
		loadimage(&img, name, 0, 0, true);
		imgBgs.push_back(img);
	}

	//��ʼ��x
	for (int i = 0; i < this->bgImgNum; i++) {
		this->x.push_back(0);
	}

}

void Background::addYWithSpeed(int y, int speed) {
	this->y.push_back(y);
	this->speed.push_back(speed);
}

void Background::move() {
	for (int i = 0; i < this->bgImgNum; i++) {
		this->x[i] -= this->speed[i];
		if (this->x[i] < -WIN_WIDTH)	this->x[i] = 0;
	}

}

void Background::update() {
	for (int i = 0; i < this->bgImgNum; i++) {
		putimagePNG2(this->x[i], this->y[i], &this->imgBgs[i]);
	}
}