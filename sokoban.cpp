#define _CRT_SECURE_NO_WARNINGS
#include "sokoban.h"

ObjectOnMap::ObjectOnMap() {
	InitPos(0,0);
}
ObjectOnMap::~ObjectOnMap() {
}
ObjectOnMap::ObjectOnMap(const int x, const int y) {
	InitPos(x,y);
}

int ObjectOnMap::ShowPosX() {
	return p_x;
}
int ObjectOnMap::ShowPosY() {
	return p_y;
}
Character::Character(const int x, const int y) {
	InitPos(x, y);
	
}
void ObjectOnMap::StartPos(const int x, const int y) {
	InitPos(x, y);
}
Character::Character() {
	InitPos(0,0);
}
bool ObjectOnMap::ChangePos(const int ofs_x, const int ofs_y) {
	p_x += ofs_x;
	p_y += ofs_y;
	return true;
}
void ObjectOnMap::InitPos(const int x, const int y) {
	p_x = x;
	p_y = y;
}
void Character::Move(const unsigned char mode, Box* box_array, Finish* finish_array, std::array<std::array<char, Field_l>, Field_h>& map , const int box_amount){
	int hy = ShowPosY();
	int hx = ShowPosX();
	switch (mode) {
	case 1://up
		switch (map[hy - 1][hx]) {
		case '#':
			return;
		case 'B':
			if ((map[hy - 2][hx] == '#') || (map[hy - 2][hx] == 'B')) {
				return;
			}
			else {
				MoveBox(hy - 1, hx, box_array, box_amount, mode);
				map[hy - 2][hx] = 'B';
			}

		default:
			map[hy - 1][hx] = 'H';
			map[hy][hx] = ' ';
			hy = hy - 1;
		}
		ChangePos(0, -1);
		break;
	case 2://down
		switch (map[hy + 1][hx]) {
		case '#':
			return;
		case 'B':
			if ((map[hy + 2][hx] == '#') || (map[hy + 2][hx] == 'B')) {
				return;
			}
			else {
				map[hy + 2][hx] = 'B';
			}

		default:
			map[hy + 1][hx] = 'H';
			map[hy][hx] = ' ';
			hy = hy + 1;
		}
		ChangePos(0, 1);
		break;
	case 3://left
		switch (map[hy][hx - 1]) {
		case '#':
			return;
		case 'B':
			if ((map[hy][hx - 2] == '#') || (map[hy][hx - 2] == 'B')) {
				return;
			}
			else {
				map[hy][hx - 2] = 'B';
			}
		default:
			map[hy][hx - 1] = 'H';
			map[hy][hx] = ' ';
			hx = hx - 1;
		}
		ChangePos(-1, 0);
		break;
	case 4:
		switch (map[hy][hx + 1]) {
		case '#':
			return;
		case 'B':
			if ((map[hy][hx + 2] == '#') || (map[hy][hx + 2] == 'B')) {
				return;
			}
			else {
				map[hy][hx + 2] = 'B';
			}

		default:
			map[hy][hx + 1] = 'H';
			map[hy][hx] = ' ';
			hx = hx + 1;
		}
		ChangePos(1, 0);
		break;
	}
}

void Character::MoveBox(const int pos_x, const int pos_y, Box* box_array, const unsigned box_amount, unsigned char mode) {
	unsigned int box_num = 0;
	for (box_num = 0; box_num < box_amount; box_num++) {
		if (!(box_array[box_num].CmpPos(pos_x, pos_y))) {
			box_array[box_num].Move(mode);
		}
	}
}


Character::~Character() {
}
Box::Box() {
	InitPos(0, 0);

}
Box::Box(const int x, const int y) {
	InitPos(x, y);
}
bool Box::CmpPos(const int x, const int y){
	if (x == ShowPosX() && y == ShowPosY()) {
		return FALSE;
	}
	return TRUE;
}


void Box::Move(const unsigned char mode) {
	switch (mode) {
	case 1://up
		ChangePos(0, -1);
		break;
	case 2://down
		ChangePos(0, 1);
		break;
	case 3://left
		ChangePos(-1, 0);
		break;
	case 4://right
		ChangePos(1, 0);
		break;
	}
}
Box::~Box() {

}
Finish::Finish() {
	InitPos(0, 0);

}
Finish::Finish(const int x, const int y) {
	InitPos(x, y);

}
Finish::~Finish() {

}

Field::Field() {
	box_amount = 0;
	points = 0;
	lvl = 0;
	total_lvl = 0;
	box_array=nullptr;
	finish_array=nullptr;
	int count;
	lvlf[lvlfile_h-1][lvlfile_l-1] = { 0 };
	map[Field_h-1][Field_l-1] = { 0 };
	std::array<std::array<char, lvlfile_l - 4>, lvlfile_h> temp;
	int result=0;
	system("del lvl_file");
	system("dir /B map >> lvl_file");

	std::ifstream lvlfile("lvl_file");
	for (int i = 0; i < lvlfile_h-1; i++) {
		//result=fscanf(lvlfile, "%6[^\n]\n", temp[i]);
		lvlfile.getline(temp[i].data(), lvlfile_l - 4, '\n');
	}
	for (int i = 0; i < lvlfile_h-1; i++) {
		if (!(temp[i][0] == 'L')) {
			count = i;
			break;
		}
	}
	for (int i = 0; i < count; i++) {
		lvlf[i][0] = 'm';
		lvlf[i][1] = 'a';
		lvlf[i][2] = 'p';
		lvlf[i][3] = '/';
		lvlf[i][4] = temp[i][0];//l
		lvlf[i][5] = temp[i][1];//e
		lvlf[i][6] = temp[i][2];//v
		lvlf[i][7] = temp[i][3];//e
		lvlf[i][8] = temp[i][4];//l
		lvlf[i][9] = temp[i][5];//0
		lvlf[i][10] = temp[i][6];//0
	}
	total_lvl = count;
	lvlfile.close();
}
Field::~Field() {
	delete[]box_array;
	delete[]finish_array;
}
void Field::LoadLevel(const int level) {
	int result = 0;
	if(box_amount!=0){
		delete[]box_array;
		delete[]finish_array;
		box_amount = 0;
	}
	lvl = level;
	std::ifstream fin(lvlf[lvl].data());
	points = 0;
	for (int y = 0; y < Field_h; y++) {
		fin.getline(map[y].data(), Field_l, '\n');
		for (int x = 0; x < Field_l-1; x++) {
			if (map[y][x]=='B') {
				box_amount++;
			}
		}
	}
	finish_array = new Finish [box_amount];
	box_array = new Box [box_amount];
	unsigned char Box_i=0;
	unsigned char Fin_i = 0;
	for (int y = 0; y < Field_h; y++) {
		for (int x = 0; x < Field_l-1; x++) {
			switch (map[y][x]) {
			case 'H'://персонаж
				character.StartPos(x,y);
			break;
			case 'o'://финиши
				finish_array[Fin_i++].StartPos(x, y);
			break;
			case 'B'://коробки
				box_array[Box_i++].StartPos(x, y);
			break;
			}
		}
	}
	fin.close();
}
void Field::Show() {
	//Initialize the coordinates
	COORD coord = { 0,0 };
	//Set the position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for (int y = 0; y < Field_h; y++) {
		std::cout << map[y].data()<<std::endl;
	}
	std::cout << "X-Exit          Level:"<< lvl <<"        R-restart" << std::endl;

}
unsigned int Field::ShowLvl() {
	return lvl;
}
unsigned char Field:: WinCheck() {
	int points=0;
	for (int i = 0; i < box_amount; i++) {
		int py = finish_array[i].ShowPosY();
		int px = finish_array[i].ShowPosX();
		switch (map[py][px]) {
		case ' ':
			map[py][px] = 'o';
			break;
		case 'B':
			points++;
			break;
		}
	}
	return points;
}
void Field::Game() {
	ShowScreen(0);
	//тут игра
	ShowScreen(1);
	char key=0;
	while (key != 'x') {
		Show();
		switch (_getch()) {
		case 'w':
			character.Move(1, box_array, finish_array,map,box_amount);
			break;
		case 's':
			character.Move(2, box_array, finish_array, map, box_amount);
			break;
		case 'a':
			character.Move(3, box_array, finish_array, map, box_amount);
			break;
		case 'd':
			character.Move(4, box_array, finish_array, map, box_amount);
			break;
		case 'r':
			LoadLevel(lvl);
			break;
		case 'x':
			key = 'x';
			break;
		}
		if (WinCheck() == box_amount) {
			if (lvl < total_lvl) {
				lvl++;
				LoadLevel(lvl);
				ShowScreen(1);
				continue;
			}
		}
		Show();
	}
}

void Field::ShowScreen(const unsigned int mode) {
	int result;
	std::ifstream fin(scrLink[mode].data());
	//Initialize the coordinates
	COORD coord = { 0,0 };
	//Set the position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	for (int i = 0; i < Field_h; i++) {
		fin.getline(screen_text[i].data(), Field_l,'\n');
	}
	for (int i = 0; i < Field_h; i++) {
		std::cout << screen_text[i].data() << std::endl;
		if (mode == 1 && i == Field_h / 2) {
			std::cout << "*               Level:" << lvl << "                *" << std::endl;
			i++;
		}
	}
	fin.close();
	std::cout << "	     Press any key..." << std::endl;
	result = _getch();
}
