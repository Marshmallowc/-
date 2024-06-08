/*
	������ܿ�����־
	1.	������Ŀ
	2.	�����ز�
	3.	������Ϸ����
		ʵ�ʵĿ�������
		���ڳ�ѧ�ߣ���õķ�ʽ��������û���������
		
		ѡ��ͼ�ο������������
		������ܣ��ǻ��ڡ�easyx��ͼ�ο��
		1��������Ϸ����
		2�������Ϸ����
			a.3�ر�����ͬ���ٶ�ͬʱ�ƶ�����Ϊ������Ķ����ƶ��ÿ��
			b.ѭ������������ʵ��
		3��ʵ����Ϸ����
			a.���ر�����Դ
			b.��Ⱦ������֪ʶ�����꣩
			�������⣺����͸����png��ʽͼƬ����ֺ�ɫ
	4.ʵ����ҵı���
	5.ʵ����ҵ���Ծ
	6.ʵ����ҵĻ���
	7.�Ż�֡Gettickcount����Sleep;
	8.���С�ڹ�ĳ���
	9.��װ�ϰ���
	10.ʵ���ϰ���
	11.ʵ����ײЧ����Ѫ��
	12.ʵ�ֿ��ֽ��桢�������桢ʤ������
	13.�Ż����ֽ��棨���û��ж���ѡ�񣺿�ʼ��Ϸ��������ɫ����ʷ��¼���˳���Ϸ��
		1��Pͼ
		2��¼�����ָ���Ӧ����ѡ��
		3��ʵ�ָ���ѡ��Ĺ���
	14.�ϰ���ṹ���Ż�����
	15.��Ϸ�����Ż�Ϊ��
	16.�Ż���Ϸ���棬��Ҫ���Ľ��棬Ҫ��̬�仯
	17.������Ϸ�Ѷȡ���ɫ���롢��ǰ�ٶ�
	18.�ڽ�ɫ��������ʱ�������ɫ�¶ף��൱�ڿ��ٽ��ͽ�����ٶ�&&�����ɫ�տ�ʼ������ʱ��
	19.��������ݼ�¼���ı��ļ�


*/

#include "Background.h"
#include "Hero.h"
#include "Obstacles.h"
#include "Basic.h"

void initGameInterface();
string toString(int num);
bool lowerFrameRate(int speed);

typedef enum {
	TURTLE, //�ڹ� 0
	LION, // 1
	PILLAR1,
	PILLAR2,
	PILLAR3,
	PILLAR4,
	OBSTACLE_TYPE_COUNT // 6 
}obstacle_type;

LOGFONT f;//�������

//Ӣ��
Hero hero;// ��Ϸ��ɫ
Hero screenHero;// ��Ϸ�����ɫ
Hero magicGirl;
Hero goldHandsome;

//����ͼƬ
IMAGE imgNumbers[10];

//����
Background bg;

//�ϰ���
Obstacles obstacle[OBSTACLE_COUNT];
Obstacles turtle;
Obstacles lion;
Obstacles pillar;

//int update;// ��ʾ�Ƿ���Ҫ����ˢ�»���
int lastObstacleIndex;
bool startGame, GameMenu, thirdInterface, chooseHero;
int interfaceIndex;
int dis;
int maxScore;
int maxDistance;

//��ʼ��
void init() {

	//������Ϸ����
	initgraph(WIN_WIDTH, WIN_HEIGHT);

	//���ر�����Դ
	char name[60];
	sprintf(name, "sunny");
	bg.setInfo(name, "sunny", 3);
	bg.addYWithSpeed(0, 2);
	bg.addYWithSpeed(119, 4);
	bg.addYWithSpeed(330, 7);

	//��ʼ��Ӣ�ۻ�����Ϣ
	sprintf(name, "magicGirl");
	magicGirl.setInfo(name, "magicGirl", 12, 2);
	magicGirl.setSkill("����ħ����Ů���Ҽ��������ָ���Զ��Ҳ���»�������ˣ�");
	magicGirl.setRGB(RGB(255, 183, 12));

	sprintf(name, "jingxiaoshuai");
	goldHandsome.setInfo(name, "jingxiaoshuai", 12, 0);
	goldHandsome.setSkill("���ǽ�С˧��֮���ԡ�С��������Ϊ�Ҳ����»�Ҳ���Զ�����ˣ��ҲŲ���Ҫ���ַ��˵ļ���...");
	goldHandsome.setRGB(RGB(153, 255, 30));

	hero = magicGirl;

	//����Ӣ��ͼƬ
	magicGirl.loadImage();
	goldHandsome.loadImage();

	//�����ϰ���
	sprintf(name, "turtle");
	turtle.setInfo(name, "turtle",1, 1, 0, 9, 1, 0, 0, 0);
	sprintf(name, "lion");
	lion.setInfo(name, "lion", 6, 1, 3, 30, 4, 1, 0, 0);
	sprintf(name, "pillar");
	pillar.setInfo(name, "pillar", 1, 5, 0, 40, 4, 1, 63, 260);

	turtle.loadImage();
	lion.loadImage();
	pillar.loadImage();

	//Ԥ������Ч
	preLoadSound("res/hit.mp3");

	mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
	
	lastObstacleIndex = -1;
	bg.difficulty = 0;

	//��������ͼƬ
	for (int i = 0; i < 10; i++) {
		sprintf(name, "res/sz/%d.png", i);
		loadimage(&imgNumbers[i], name);
	}

	//��ȡ�ı��ļ��е�����
	ifstream ifs("text.txt");
	ifs >> maxScore >> maxDistance;
	ifs.close();

}

void createObstacle() {
	int i;
	for (i = 0; i < OBSTACLE_COUNT; i++) {
		if (obstacle[i].exist == false) {
			break;
		}
	}
	
	if (i >= OBSTACLE_COUNT)
		return;

	int type = (randInt() % OBSTACLE_TYPE_COUNT);
	obstacle[i].bonus = 0;
	int fre[] = { 2, 4, 6 };
	if (type < fre[0]) {
		obstacle[i] = turtle;
	}
	else if (type < fre[1]) {
		obstacle[i] = lion;
	}
	else if (type < fre[2]) {
		obstacle[i] = pillar;
		obstacle[i].typeNum = randInt() % obstacle[i].imgTypeNum;
		obstacle[i].y = 0;
	}

	string finalPillar = "pillar";
	finalPillar += obstacle[i].imgTypeNum + '0';
	if (lastObstacleIndex >= 0 &&
			obstacle[lastObstacleIndex].name >= "pillar1" &&
			obstacle[lastObstacleIndex].name <= finalPillar &&
			obstacle[i].name == "lion" &&
			obstacle[i].x > WIN_WIDTH - 500) {
		obstacle[i] = turtle;
	}


	lastObstacleIndex = i;
}

void checkHit() {
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		if (obstacle[i].exist && !obstacle[i].hited) {

			int a1x, a1y, a2x, a2y;
			int off = 30;// ƫ��

			if (!hero.isSlip) {// ���¶���������ܡ���Ծ
				a1x = hero.x + off;
				a1y = hero.y + off;
				a2x = hero.x + hero.image[hero.imageIndex].getwidth() - off;
				a2y = hero.y + hero.image[hero.imageIndex].getheight();
			}
			else {// �¶�״��
				a1x = hero.x + off;
				a1y = 345 - hero.imageSlip[1].getheight();
				a2x = hero.x + hero.imageSlip[1].getwidth() - off;
				a2y = 345;
			}

			int b1x = obstacle[i].x + off;
			int b1y = obstacle[i].y + off;
			int b2x = obstacle[i].x + obstacle[i].img[obstacle[i].typeNum][obstacle[i].imgIndex].getwidth() - off;
			int b2y = obstacle[i].y + obstacle[i].img[obstacle[i].typeNum][obstacle[i].imgIndex].getheight() - 10;

			if (rectIntersect(a1x, a1y, a2x, a2y, b1x, b1y, b2x, b2y)) {// ��ײ��
				hero.blood -= obstacle[i].power;
				cout << "Ѫ��ʣ��" << hero.blood << endl;
				playSound("res/hit.mp3");
				obstacle[i].hited = true;
			}
		}
	}
}

//�޸��ƶ�����
void updateData() {
	//�����ƶ�
	bg.move();

	//Ӣ���ƶ�
	hero.move();
	
	//�����ϰ���
	static int frameCount = 0;
	static int enermyFre = 100;
	frameCount++;
	if (frameCount > enermyFre) {
		frameCount = 0;
		enermyFre = 100 + (randInt() % 17) * (randInt() % 21);
		createObstacle();
	}
	
	//�����ϰ��������
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		if (obstacle[i].exist) {
			obstacle[i].x -= obstacle[i].speed + bg.speed[2];
			if (obstacle[i].x < -obstacle[i].img[obstacle[i].typeNum][0].getwidth() * 2) {
				obstacle[i].exist = false; 
				
			}
			
			int len = obstacle[i].imgRunNum;
			obstacle[i].imgIndex = (obstacle[i].imgIndex + 1) % len;
		}
	}

	//��ײ���
	checkHit();


}

//�����û�����������
void keyEvent() {

	if (kbhit()) { //����а�������
		char ch;
		ch = getch();// ����Ҫ���»س��Ϳ���ֱ�Ӷ�ȡ
	
		if (ch == ' ' && startGame) {	
			if (hero.isSlip && hero.name != "goldHandsome")	hero.firstSlipThenJump = true;
			hero.isJump = true;
		}
		else if (ch == 's' && startGame) {
			if (!hero.isJump && hero.name == "jingxiaoshuai")	return;
			if (hero.isSlip)	hero.firstSlipThenJump = false;
			hero.isSlip = true;
		}
		else if (ch == '1' && !startGame && interfaceIndex == 1) {// ��ʼ��Ϸ
 			startGame = true;
			GameMenu = false;
		}
		else if (ch == '2' && !startGame && interfaceIndex == 1) {// ѡ��Ӣ��
			GameMenu = false;
			chooseHero = true;
			interfaceIndex = 2;

			Hero hero1 = magicGirl;
			Hero hero2 = goldHandsome;

			while (interfaceIndex == 2) {
				keyEvent();

				char heroname1[] = { "a) ħ����Ů" };
				char heroname2[] = { "b) ��С˧" };

				//LOGFONT f1;
				f.lfHeight = 40;
				f.lfWidth = 19;
				f.lfWeight = 800;
				////setbkmode(TRANSPARENT);
				settextcolor(RGB(26, 20, 31));
				settextstyle(&f);


				bool update = lowerFrameRate(80);

				if (update) {
					BeginBatchDraw();
					loadimage(0, "res/GameMenu.png");
					outtextxy(300 - 40, 230 + 10 + hero1.image[0].getheight() - 90, heroname1);
					outtextxy(600 - 30, 230 + 10 + hero1.image[0].getheight() - 90, heroname2);

					hero1.run();
					hero2.run();
					hero1.update(300, 230 - 100);
					hero2.update(600, 230 - 60);
					EndBatchDraw();
				}
			}
		}
		else if (ch == '3' && !startGame && interfaceIndex == 1) {
			GameMenu = false;
			interfaceIndex = 2;

			while (interfaceIndex == 2) {
				keyEvent();

				char str[] = { "s����ʾ�»����ո����ʾ��Ծ���ɹ����һ���ϰ��ｫ�����Ӧ��������Ϸ�Ѷ���ʱ�����ӣ�����15���о�ϲ" };
				char str1[] = { "s����ʾ�»����ո����ʾ��Ծ��o����������" };
				char str2[] = { "�ɹ����һ���ϰ��ｫ�����Ӧ����" };
				char str3[] = { "��Ϸ�Ѷ���ʱ�����ӣ�����15���о�ϲ" };


				int maxWidth = 600; // ��������Ŀ��
				gettextstyle(&f);
				f.lfHeight = 35;//����߶�(����Ϊ��λ)
				f.lfWidth = 17;//������
				f.lfWeight = 750;
				settextcolor(RGB(177, 232, 5));
				strcpy(f.lfFaceName, "΢���ź�");
				f.lfQuality = ANTIALIASED_QUALITY;//��ĥ���� ʹ�����ø��ӹ⻬
				setbkmode(TRANSPARENT);
				settextstyle(&f);
				string line;
				int x = 80, y = 50;

				loadimage(0, "res/GameMenu.png");
				outtextxy(x, y, str1);
				outtextxy(x, y + 60, str2);
				outtextxy(x, y + 120, str3);
				settextcolor(RGB(26, 20, 31));
				outtextxy(800, 333, "d)  �� ��");

				bool update = lowerFrameRate(60);
				if (update) {
					hero.run();
					hero.update(80, 250);
				}

				Sleep(80);
			}
		}
		else if (ch == '4' && !startGame) {
			exit(0);
		}
		else if (ch == 'a' && !startGame && chooseHero) {// ѡ��ħ����Ů
			hero = magicGirl;
			chooseHero = false;
			interfaceIndex = 1;
		}
		else if (ch == 'b' && !startGame && chooseHero) {// ѡ���С˧
			hero = goldHandsome;
			chooseHero = false;
			interfaceIndex = 1;
		}
		else if (ch == 'd' && !startGame) {
			interfaceIndex = 1;
			chooseHero = false;
		}
		else if (ch == 'o') {
			static int count = 0;
			count++;
			if(count % 2 == 0)	mciSendString("stop res/bg.mp3", 0, 0, 0);
			else mciSendString("play res/bg.mp3 repeat", 0, 0, 0);

}
	}
}

void updateEnermy() {
	//��Ⱦ�ϰ���
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		if (obstacle[i].exist) {
			putimagePNG2(obstacle[i].x, obstacle[i].y, WIN_WIDTH, &obstacle[i].img[obstacle[i].typeNum][obstacle[i].imgIndex]);
		}
	}

}

void updateBloodBar() {
	drawBloodBar(10, 10, 200, 10, 2, BLUE, DARKGRAY, RED, hero.blood / 100.0);
}

void checkGameOver() {
	if (hero.blood <= 0) {
		if (maxScore < hero.score)	maxScore = hero.score;
		if (maxDistance < dis)	maxDistance = dis;

		ofstream ofs("text.txt");
		ofs << maxScore << ' ' << maxDistance;

		ofs.close();

		loadimage(0, "res/over.png");
		FlushBatchDraw();
		mciSendString("stop res/bg.mp3", 0, 0, 0);
		initGameInterface();


		system("pause");

		//��֮ͣ�󣬳�Ǯ����orֱ�ӿ�ʼ��һ��
		hero.blood = 100;
		mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
		hero.score = 0;
		bg.difficulty = 0;
		bg.speed[0] = 2;
		bg.speed[1] = 4;
		bg.speed[2] = 7;
		turtle.bonus = 0;
		lion.bonus = 0;
		pillar.bonus = 0;
		dis = 0;
	}
}

void checkScore() {
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		if (obstacle[i].exist &&
				obstacle[i].pass == false &&
				!obstacle[i].hited &&
				obstacle[i].x + obstacle[i].img[obstacle[i].imgTypeNum][obstacle[i].imgIndex].getwidth() < hero.x) {
			hero.score += obstacle[i].score + obstacle[i].bonus;
			obstacle[i].pass = true;
			cout << "score:" << hero.score << endl;
		}
	}
}

void updateScore() {
	char str[8];
	sprintf(str, "%d", hero.score);

	int x = 20;
	int y = 25;

	for (int i = 0; i < str[i]; i++) {
		int num = str[i] - '0';
		putimagePNG(x, y, &imgNumbers[num]);
		x += imgNumbers[num].getwidth() + 5; 
	}

}

void checkVectory() {
	if (hero.score >= WIN_SCORE) {
		startGame = false;

		if (maxScore < hero.score)	maxScore = hero.score;
		if (maxDistance < dis)	maxDistance = dis;

		ofstream ofs("text.txt");
		ofs << maxScore << ' ' << maxDistance;

		ofs.close();
		
		FlushBatchDraw();
		mciSendString("play res/win.mp3", 0, 0, 0);
		Sleep(1000);
		loadimage(0, "res/win.png");
		FlushBatchDraw();
		mciSendString("stop res/bg.mp3", 0, 0, 0);
		system("pause");

		hero.blood = 100;
		hero.score = 0;
		bg.difficulty = 0;
		bg.speed[0] = 2;
		bg.speed[1] = 4;
		bg.speed[2] = 7;
		turtle.bonus = 0;
		lion.bonus = 0;
		pillar.bonus = 0;
		dis = 0;
		mciSendString("play res/bg.mp3", 0, 0, 0);
	}
}

void setFont()
{
	static int height = 49;
	static int width = 26;
	static bool down = false;

	char str1[] = {"1)  �� ʼ �� Ϸ"};
	char str2[] = {"2)  �� �� �� ɫ"};
	char str3[] = {"3)  ʹ �� ˵ ��"};
	char str4[] = {"4)  �� �� �� Ϸ"};

	gettextstyle(&f);
	f.lfHeight = height;//����߶�(����Ϊ��λ)
	f.lfWidth = width;//������
	f.lfWeight = 700;
	settextcolor(RGB(29, 20, 31));
	strcpy(f.lfFaceName, "΢���ź�");
	f.lfQuality = ANTIALIASED_QUALITY;//��ĥ���� ʹ�����ø��ӹ⻬
	settextstyle(&f);
	setbkmode(TRANSPARENT);

	char skillText[60];
	for (int i = 0; i < hero.skillText.size(); i++) {
		skillText[i] = hero.skillText[i];
	}

	outtextxy(WIN_WIDTH * 2 / 3 - 60, (WIN_HEIGHT / 5) , str1);
	outtextxy(WIN_WIDTH * 2 / 3 - 60, (WIN_HEIGHT / 5) * 2 , str2);
	outtextxy(WIN_WIDTH * 2 / 3 - 60, (WIN_HEIGHT / 5) * 3 , str3);
	outtextxy(WIN_WIDTH * 2 / 3 - 60, (WIN_HEIGHT / 5) * 4 , str4);

	int maxWidth = 200; // ��������Ŀ��
	f.lfWeight = 350;
	f.lfHeight = 25;
	f.lfWidth = 11;
	settextcolor(hero.rgb);
	settextstyle(&f);
	string line;
	int x = 100 + hero.image[0].getwidth() + 10 - 80, y = 180 - 60;
	for (char c : hero.skillText) {
		line += c;
		if (textwidth(line.c_str()) > maxWidth) {
			outtextxy(x, y, line.c_str());
			line = ""; // ��յ�ǰ������
			y += textheight("A"); // ��һ����ʼλ��
		}
	}
	outtextxy(x, y, line.c_str()); // ������һ������


	if (height < 53 && !down)	height++, width++, down = true;
	else if (height > 48) height--, width--;
	else down = false;

}

void initGameInterface() {
	//��������ϰ���
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		obstacle[i].exist = false;
	}

	//��Ϸ��ʼ����
	startGame = false;
	loadimage(0, "res/start.png");
	system("pause");

	//��Ϸ�˵�
	GameMenu = true;
	interfaceIndex = 1;

	while (!startGame) {
		keyEvent();

		if(interfaceIndex == 1){

			BeginBatchDraw();
			loadimage(0, "res/GameMenu.png");
			hero.run();
			hero.update(20, 180);

			string arr1 = "��Զ����" + toString(maxDistance);
			string arr2 = "��ߵ÷�" + toString(maxScore);

			char str1[50], str2[50];
			for (int i = 0; i < arr1.size(); i++) {
				str1[i] = arr1[i];
			}
			str1[arr1.size()] = 'm';
			str1[arr1.size() + 1] = '\0';

			for (int i = 0; i < arr2.size(); i++) {
				str2[i] = arr2[i];
			}
			str2[arr2.size()] = '\0';



			f.lfHeight = 30;
			f.lfWidth = 14;
			f.lfWeight = 500;
			setbkmode(TRANSPARENT);
			settextcolor(RGB(234, 35, 124));
			settextstyle(&f);
			outtextxy(20, 10, str1);
			outtextxy(20, 40, str2);
			
			bool update = lowerFrameRate(80);
			if (update)	setFont();

			Sleep(110);

			EndBatchDraw();
			
		}
	}
	
}

bool lowerFrameRate(int speed) {
	static int timer = 0;
	static bool update = false;

	timer += getDelay();
	if (timer >= speed) {
		timer = 0;
		update = true;
		return true;
	}
	else if (timer == 0) {
		update = false;
	}

	return false;
}

string toString(int num) {
	if (num == 0)	return "0";

	string arr = "";
	while (num) {
		arr += (num % 10) + '0';
		num /= 10;
	}

	reverse(arr.begin(), arr.end());
	return arr;
}

void updateDistance() {
	dis += bg.speed[bg.speed.size() - 1];
	string arr = toString(dis);
	char num[10000];
	for (int i = 0; i < arr.size(); i++) {
		num[i] = arr[i];
	}
	num[arr.size()] = 'm';
	num[arr.size() + 1] = '\0';

	gettextstyle(&f);
	f.lfHeight = 31;
	f.lfWidth = 14;
	f.lfWeight = 580;
	settextcolor(RGB(255, 248, 170));
	settextstyle(&f);
	outtextxy(850, 10, num);
}

void checkGameDifficulty() {
	//������Ϸʱ������ӣ��Ѷ�����
	static long long time = 0;

	int add[] = { 1, 1, 2 };
	if (time >= 500) {
		time = 0;
		bg.difficulty++;

		//���ӱ������ƶ��ٶ�
		for (int i = 0; i < 3; i++) {
			bg.speed[i] += add[i];
		}

		//�����ϰ���Ľ���
		turtle.bonus += bg.difficulty * 2;
		lion.bonus += bg.difficulty * 2;
		pillar.bonus += bg.difficulty * 2;
	}

	time++;
}

void updateSpeed() {
	char num[10000];
	string arr = toString(bg.speed[bg.speed.size() - 1]);

	for (int i = 0; i < arr.size(); i++) {
		num[i] = arr[i];
	}

	num[arr.size()] = 'm';
	num[arr.size() + 1] = '\/';
	num[arr.size() + 2] = 's';
	num[arr.size() + 3] = '\0';

	gettextstyle(&f);
	f.lfHeight = 31;
	f.lfWidth = 14;
	f.lfWeight = 580;
	settextcolor(RGB(255, 248, 170));
	settextstyle(&f);
	outtextxy(850, 46, num);
	
}

int main()
{	
	//��ʼ��
	init();// ��������

	while (1) {
		//��ʼ������
		initGameInterface();

		//��ʼ��Ϸ
		while (startGame) {

			//���̼���
			keyEvent();

			//����ÿһ֡�ĸ����ٶ�
			int rate = 30 - 2 * bg.difficulty;
			if (rate < 20)	rate = 20;
			bool update = lowerFrameRate(rate);

			//������Ϸ��ÿһ֡����
			if (update) {

				//����ÿһ֡ͼƬ
				BeginBatchDraw();
				bg.update();
				hero.update();// ����Ӣ��ͼƬ
				updateEnermy();
				updateBloodBar();// ���±����е�Ѫ����Ϣ
				updateScore();// ���±����еķ�����Ϣ
				updateDistance();// ��������߹��ľ���
				updateSpeed();// ������Ҵ˿̵��ƶ��ٶ�
				EndBatchDraw();

				//����ÿһ֮֡�������
				updateData();

				//��������Ϸ���
				checkVectory();
				checkGameOver();
				checkScore();
				checkGameDifficulty();// ����Ƿ���Ҫ������Ϸ�Ѷ�


			}

				
		}

	}

	
	system("pause");
	return 0;
}