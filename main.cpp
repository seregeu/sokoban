#include "sokoban.h"

int main(void) {
	//Character character(0, 0);
	Field field;
	field.LoadLevel(0);
	WelcomeScreen welcome_screen(&field);
	field.Game(welcome_screen);
	return 0;
}