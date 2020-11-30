#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <algorithm>
#include <fstream>
#include <array>


#define Field_h 15
#define Field_l 41
#define scrLink_am 3
#define scrLink_len 30
#define lvlfile_h 99
#define lvlfile_l 12

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4



class WelcomeScreen;
class Field;
class Box;
class Finish;
class Character;


class ObjectOnMap {
protected:
	int p_x;
	int p_y;
public:
	ObjectOnMap();
	ObjectOnMap(const int x, const int y);
	~ObjectOnMap();
	void StartPos(const int x, const int y);
	int ShowPosX();
	int ShowPosY();
	bool ChangePos(const int ofs_x, const int ofs_y);
	void InitPos(const int x, const int y);
	void MoveInDir(const char mode);
};

class Character :public ObjectOnMap {
private:
public:
	Character(const int x, const int y);
	Character();
	~Character();
	void Move(const unsigned char mode, Field* field, Box* box_array, const int box_amount);
	void MoveBox(const int pos_x, const int pos_y, Box* box_array, const unsigned box_amount,const unsigned char mode);

};
class Box:public ObjectOnMap {
private:
public:
	Box();
	Box(const int x, const int y);
	~Box();
	bool CmpPos(const int x, const int y);
	void Move(const unsigned char mode);

};
class Finish :public ObjectOnMap {
private:
public:
	Finish();
	Finish(const int x, const int y);
	~Finish();
};
class Field {
private:
	unsigned char points;
	std::array<std::array<char, lvlfile_l>, lvlfile_h> lvlf;
	std::array<std::array<char, Field_l>, Field_h>map;
	int box_amount;
	unsigned int total_lvl;
	Character character;
	Box* box_array;
	Finish* finish_array;
	unsigned int lvl;
	std::array<std::array<char, Field_l>, Field_h> screen_text;
	std::array<std::array<char, scrLink_len>, scrLink_am> scrLink = { "face/launch_screen","face/scr_change","face/final_screen" };
	void ShowScreen(const unsigned int i);
public:
	Field();
	~Field();
	void LoadLevel(const int lvl);
	unsigned char WinCheck();
	void Show();
	void Game();
	bool SetC(const unsigned char dir);
};
