#include"Matrix.h"
#include"Header.h"


int main() {
	setlocale(0, "RUS");
	srand(time(NULL));
	Matrix first;
	while (true) {
		MenuOperator(first);
		system("cls");
	}
	return 0;
}


