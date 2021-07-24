#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	int a;
	cout << "Введите целочисленное значение: ";
	while (!(cin >> a))
	{
		cerr << "Ошибка ввода" << endl;
		cout << "Введите целочисленное значение: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	cout << a;
	return 0;
}