#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//функция для определения количества строк в файле
int get_file_lines(string& file)
{
	int count = 0;
	ifstream f(file);
	if (!f.good())
	{
		return 0;
	}
	while (!f.eof()) //открываем файл
	{
		string v;
		getline(f, v); //считываем строку
		count++; //увеличиваем счётчик
	}
	f.close();
	return count;
}

//функция считывает матрицу matrix из lines строк из файла file
void read_file(string& file, int** matrix, int lines)
{
	ifstream f(file);
	f.peek(); //пробуем считать хоть что-нибудь, не сдвигаясь по файлу
	for (int i = 0; i < lines; ++i)
	{
		matrix[i] = new int[15]; //создаём строку матрицы
		for (int j = 0; j < 15; ++j)
		{
			int t;
			if (f.eof())
			{
				cout << "Ошибка при считывании участника " << i << ", неожиданный конец файла\n";
				return;
			}
			f >> t;
			if (t <= 0 || t > 3)
			{
				cout << "Ошибка при считывании участника " << i << ", неверное значение\n";
			}
			matrix[i][j] = t; //считываем 15 чисел в матрицу
		}
	}
	f.close();
}

//функция добавляет в файл file строку line из 15 чисел
void append_file(string& file, int* line)
{
	ofstream f(file, ios::app); //открываем файл в режиме append (ios::app)
	for (int i = 0; i < 15; ++i)
	{
		f << line[i] << " "; //вписываем число
	}
	f << "\n"; //перенос строки в самом конце
	f.close();
}

//функция находит сумму очков участника line
int find_sum(int** matrix, int line)
{
	int sum = 0;
	for (int j = 0; j < 15; ++j)
	{
		if (matrix[line][j] == 1) //если 1 - очень понравился
		{
			sum += 2;
		}
		else if (matrix[line][j] == 2) //если 2 - не очень понравился 
		{
			sum += 6;
		}
		else if (matrix[line][j] == 3) //если 3 - очень не понравился
		{
			sum += 8;
		}
	}
	return sum;
}

//функция находит лучшего участника в matrix из lines участников
int find_best_index(int** matrix, int lines)
{
	int max_sum = 0;
	int max_sum_index = -1;
	for (int i = 0; i < lines; ++i)
	{
		int sum = find_sum(matrix, i); //поиск суммы очков
		if (sum > max_sum)
		{
			max_sum = sum;
			max_sum_index = i;
		}
	}
	return max_sum_index;
}

int main()
{
	setlocale(LC_ALL, "russian");

	cout << "Программу сделала Игнаткина Валерия студент группы УТН-111" << "\n";
	cout << "Программа оценки соревнований Царевны Несмеяны" << endl;

	string today_file = "t.txt"; //файл текущих соревнований
	string history_file = "h.txt"; //файл многолетней истории

	int total_lines = get_file_lines(today_file); //количество участников

	if (total_lines == 0)
	{
		cout << "Файл текущих соревнований не найден, либо пуст!\n";
	}

	int** matrix = new int*[total_lines]; //матрица (указатель на строки)
	read_file(today_file, matrix, total_lines); //читаем файл

	int best_index = find_best_index(matrix, total_lines); // ищем лучшего участника
	if (best_index == -1)
	{
		cout << "Произошла ошибка при поиске лучшего участника!\n";
	}
	else
	{
		append_file(history_file, matrix[best_index]); // добавляем лучший результат в историю
		cout << "Лучший участник найден и записан в историю!\n";
	}

	system("pause");

	return 0;
}
