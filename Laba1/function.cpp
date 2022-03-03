#include"library.h"
#include"Matrix.h"
#include"Header.h"
static int menu() {
	int field;
	valarray<string>MainMenu{
		"Умножение матриц",
		"Сложение матриц",
		"Записать исходную матрицу в файл",
		"Ввывод матрицы",
		"Пустая ли матрица?",
		"Отчистить содержимое матрицы",
		"Удалить содержимое файла",
		"Инициализировать матрицу",
		"Количество уже созданных матриц, во время выполнения программы",
		"Завершить работу"
	};
	for (int i = 0; i < MainMenu.size(); i++) {
		cout << i + 1 << ")" << MainMenu[i] << endl;
	}
	cout << endl;
	cout << "Выберете операцию: ";
	int n = 0;
	cin >> n;
	return n;
}
static int FileMatrixMenu()
{
	valarray<string> menuMatrix{
		"Считать данные с файла",
		"Рандомный ввод матрицы",
		"Ввод с клавиатуры каждого элемента матрицы"
	};
	for (int i = 0; i < menuMatrix.size(); i++) {
		cout << i + 1 << ")" << menuMatrix[i] << endl;
	}
	cout << endl;
	cout << "Выберете способ ввода: ";
	int n = 0;
	cin >> n;
	return n;
}
extern void FillMatrix(Matrix& copy) {
	while (copy.IsEmpy()) {
		system("cls");
		MenuForChoiceWayToFill(copy);

	}
}
extern void MenuOperator(Matrix& copy) {
	Matrix one;
	Matrix two;
	switch (menu())
	{

	case 1:
		cout << "Cначало введём 1 матрицу для умножения" << endl;
		system("pause");
		FillMatrix(one);
		cout << "Теперь введём 2 матрицу для умножения" << endl;
		system("pause");
		FillMatrix(two);
		copy.Multiplication(one, two);
		system("pause");
		break;
	case 2:
		cout << "Cначало введём 1 матрицу для умножения" << endl;
		system("pause");
		FillMatrix(one);
		cout << "Теперь введём 2 матрицу для умножения" << endl;
		system("pause");
		FillMatrix(two);
		copy.Sum(one, two);
		system("pause");
		break;
	case 3:
		copy.WriteMatrixIntoFile();
		system("pause");
		break;
	case 4:
		copy.PrintMatrix();
		system("pause");
		break;
	case 5:
		if (copy.IsEmpy())
			cout << "Данная матрица пуста!" << endl;
		else
			cout << "Данная матрица заполнена!" << endl;
		system("pause");
		break;
	case 6:
		copy.DeleteMatrix();
		cout << "Матрица отчистена!" << endl;
		system("pause");
		break;
	case 7:
		copy.CleanFile();
		break;
	case 8:
		copy.DeleteMatrix();
		FillMatrix(copy);
		system("pause");
		break;
	case 9:
		cout << "Количество созданных матриц: " << copy.GetCount() << endl;
		system("pause");
		break;
	case 10:
		exit(0);
		break;
	default:
		cout << "Неверно выбранное поле!" << endl;
		break;
	}
}
extern void MenuForChoiceWayToFill(Matrix& copy)
{
	int r, c;
	switch (FileMatrixMenu())
	{
	case 1:
		copy.ReadMatrixfromFile();
		break;
	case 2:
		cout << "Введите количество строк в матрице: ";
		cin >> r;

		cout << endl << "Введите количество сьолбцов в матрице: ";
		cin >> c;
		copy.init(r, c);
		copy.FillMatrixRandom();
		break;
	case 3:
		cout << "Введите количество строк в матрице: ";
		cin >> r;

		cout << endl << "Введите количество сьолбцов в матрице: ";
		cin >> c;
		copy.init(r, c);
		copy.EnterMatrixFromKeyboard();
		break;

	default:
		break;
	}
}

