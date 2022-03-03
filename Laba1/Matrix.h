#pragma once
#include"library.h"
class Matrix
{

private:

	enum CountType {
		MinusOne = 1, PlusOne
	};
	int rows; //строки матрицы
	int columns; //столбцы матрицы
	float** Array;//двумерный массив
	fstream FileInfo;//файл для хранение данных
	static streampos Pos;//статичная переменная для хранения позиции в файле
	static int MatrixCount;///статичная переменная для количества созданных объектов
	static void SetFilePos(streampos p);//изменяем позицию статичной переменной
	static void SetCount(CountType type);//ставим количесво созданных объектов Matrix


public:
	void init(int r, int c);//метод для создания матрицы

	Matrix(int r=0, int c=0);//конструктор по умолчанию
	Matrix(const Matrix& copy);//конструктор копирования
	~Matrix();//деструктор 
	static int GetCount();//вывод количества созданных объектов
	Matrix& Multiplication(const Matrix& firts, const Matrix& second);//перемножение матрицы first и second, резельтат записывается в объект, который вызывает 
	Matrix& Sum(const Matrix& firts, const Matrix& second);//Сложение  матрицы first и second, резельтат записывается в объект, который вызывает 
	void EnterMatrixFromKeyboard();//Ввод значений с клавиатуры
	bool IsEmpy();//проверка на заполненность матрицы
	void FillMatrixRandom();//ввод матрицы рандомна
	void PrintMatrix();//Вывести матрицу в консоль
	void WriteMatrixIntoFile();//Записать матрицу в файл
	void ReadMatrixfromFile();//чтение матрицы с файла
	void CleanFile();//отчисть содержимое файла
	void DeleteMatrix();//отчитстка сожержимого Matrix
	
};


