#include "Matrix.h"
int Matrix::MatrixCount = 0;

streampos Matrix:: Pos = 0;

void Matrix::SetCount(CountType type)
{
	if (type == MinusOne)
		MatrixCount--;
	else if (type == PlusOne) {
		MatrixCount++;
	}
		
}

void Matrix::SetFilePos(streampos p)
{
	Pos = p;
}

void Matrix::init(int r, int c)
{
	if (!(r <= 0 || c<= 0)) {
		if (Array != nullptr) {
			DeleteMatrix();
		}
		this->rows = r;
		this->columns = c;
		Array = new float* [rows];
		for (int i = 0; i < rows; i++) {
			Array[i] = new float[columns];
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				Array[i][j] = 0;
			}
		}
	}
	else
		Array = nullptr;

}

Matrix::Matrix(int r, int c)
{

	Matrix::init(r, c);
		SetCount(PlusOne);


}

Matrix::Matrix(const Matrix& copy)
{ 
	init(copy.rows, copy.columns);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			Array[i][j] = copy.Array[i][j];
		}
	}
}

Matrix::~Matrix()
{
	Matrix::DeleteMatrix();
}

int Matrix::GetCount()
{
	return MatrixCount;
}

Matrix& Matrix::Multiplication(const Matrix& firts, const Matrix& second)
{
	if (firts.columns == second.rows) {
		Matrix::DeleteMatrix();
		Matrix::init(firts.rows, second.columns);
		for (int i = 0; i < firts.rows; i++) {
			for (int j = 0; j < second.columns; j++) {
				this->Array[i][j] = 0;
				for (int k = 0; k < second.rows; k++) {
					this->Array[i][j] += firts.Array[i][k] * second.Array[k][j];
				}


			}
		}
		cout << "Результат записан в исходную матрицу!" << endl;
	}
	else
	{
		cout << "Нельзя перемножить данные матрицы!" << endl;
	}
	return *this;
}

Matrix& Matrix::Sum(const Matrix& firts, const Matrix& second)
{
	Matrix::DeleteMatrix();
	if ((firts.columns == second.columns) && (firts.rows == second.rows)) {
		Matrix::init(firts.rows, firts.columns);
		for (int i = 0; i < firts.rows; i++) {
			for (int j = 0; j < firts.columns; j++) {
				this->Array[i][j] = firts.Array[i][j] + second.Array[i][j];
			}
		}
		cout << "Результат записан в исходную матрицу!" << endl;
	}

	else
	{
		cout << "Нельзя сложить матрицы одинановой размерности!"<<endl;
	}
	return *this;
}

void Matrix::EnterMatrixFromKeyboard()
{
	if (Array != nullptr) {

		for (int i = 0; i < this->rows; i++) {
			for (int j = 0; j < this->columns; j++) {
				cout << "Введите Matrix[" << i + 1 << "][" << j + 1 << "] :";
				cin >> Array[i][j];
				cout << endl;
			}
		}
		cout << "Ввод завершён!" << endl;
	}
	else
		cout << "Массив пуст, запись невозможна!" << endl;
}

bool Matrix::IsEmpy()
{
	if (this->Array == nullptr) {
		return true;
	}
	int flag = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (Array[i][j] != 0)
				flag++;
		}
	}
	if (flag == 0)
		return true;
	return false;
}

void Matrix::FillMatrixRandom()
{
	if (Array != nullptr) {

		for (int i = 0; i < this->rows; i++) {
			for (int j = 0; j < this->columns; j++) {
				Array[i][j] = ((float)(-5000 + rand() % 10000))/100;
			}
		}
		cout << "Ввод завершён!" << endl;
	}
	else
		cout << "Массив пуст, запись невозможна!" << endl;
}

void Matrix::PrintMatrix()
{
	if (Array!=nullptr) {

		for (int i = 0; i < this->rows; i++) {
			for (int j = 0; j < this->columns; j++) {
				cout.width(10);
				cout << fixed;
				cout.precision(2);

				cout << Array[i][j] << " ";

			}
			cout << endl;
		}
	}
	else
		cout << "Массив пуст, вывод невозможен!" << endl;
}

void Matrix::WriteMatrixIntoFile()
{
	string FileName = "max.dat";
	FileInfo.open(FileName, ios::binary | ios::app);
	if (FileInfo.is_open()) {
		if (Array != nullptr) {
			FileInfo.write((char*)&rows, sizeof(rows));
			FileInfo.write((char*)&columns, sizeof(columns));
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					FileInfo.write((char*)&(Array[i][j]), sizeof(Array[i][j]));
				}
			}

			FileInfo.close();
			cout << "Запись успешно завершена!" << endl;
		}
		else {
			FileInfo.close();
			cout << "Зачем записывать пустой массив!?";
		}
	}
	else cout << "Данный файл не может быть открыт" << endl;
}

void Matrix::DeleteMatrix()
{
	if (Array != nullptr) {
		for (int i = 0; i < this->rows; i++) {
			delete[] Array[i];
		}
		delete[] Array;
		Array = nullptr;
		this->rows = this->columns = 0;
		SetCount(MinusOne);
	}

}

void Matrix::ReadMatrixfromFile() 
{
	
		string FileName = "max.dat";
		FileInfo.open(FileName, ios::binary | ios::in);

		if (FileInfo.is_open()) {
			FileInfo.seekg(0, ios::end);
			streampos current = FileInfo.tellg();
			FileInfo.seekg(Pos, ios::beg);

			if (FileInfo.tellg() != current) {
				int r = 0, c = 0;
				FileInfo.read((char*)&r, sizeof(r));
				FileInfo.read((char*)&c, sizeof(c));
				init(r, c);
				for (int i = 0; i < rows; i++) {
					for (int j = 0; j < columns; j++) {
						FileInfo.read((char*)&(Array[i][j]), sizeof(Array[i][j]));
					}
				}
				SetFilePos(FileInfo.tellg());
				cout << "Чтение завершено успешно!" << endl;
			}
			else {
				cout << "В данном файле не осталось больше несчитанных матриц!" << endl;
				system("pause");
				FileInfo.close();
				return;
			}
		}
		else cout << "Данный файл не найден!" << endl;
		FileInfo.close();
		system("pause");
	
}

void Matrix::CleanFile() {
	remove("max.dat");
	SetFilePos(0);
	cout << "Файл успешно отчисчен!" << endl;
}

