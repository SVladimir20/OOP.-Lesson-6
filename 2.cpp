#include <iostream>
using namespace std;
ostream &endll(ostream &stream)
{
	cout << endl << endl;
	return stream;
}
int main()
{
	setlocale(LC_ALL, "Russian");
	cout << endll << "Практическое задание №2" << endll;
	return 0;
}