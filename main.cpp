#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "description.h"
using namespace std;

#include <locale>

using std::cout;
using std::cin;


int main()
{
	setlocale(0, "rus");
	cout << "ֲגוהטעו טלÿ פאיכא\n";
	char input[10];
	cin >> input;
		Print(input);
	system("pause");
	return 0;
}