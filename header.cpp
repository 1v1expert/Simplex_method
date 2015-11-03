#include "description.h"
#include "stdio.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using std::cout;


void Print(char *file_name){
	cout.precision(2);
		FILE *pF;
		char simv, simvPr[2];
		
		double** data;
		int* free;
		int* depended;
		int n;
		int m;

		pF = fopen(file_name, "r");
		simv = fgetc(pF);
			while (simv != '\n') // ��������� ����������� �������
			{
				int k = 0;
				if ((simv != ' ') && (simv != '.') && (k==0)){simvPr[0] = simv; n = atoi(simvPr); ++k;};
				if ((simv != ' ') && (simv != '.') && (k==1)){simvPr[0] = simv; m = atoi(simvPr); ++k;};
			 simv = fgetc(pF);
			 }; 
		simv = fgetc(pF);
	
	//std::cout << n << std :: endl;
	//std::cout << m << std :: endl;



	data = new double*[m + 1]; /*������� ������ (m+1) x (n+1), �.�. ����� �����
	�������� ����� ������� ��������� ������ � ������ ������� �������*/
	
	for (int i = 0; i < m + 1; i++) {
		data[i] = new double[n + 1];
	}

	//�������� ������ �������� ������� ������� �� �����
		int j = 0;
		while ((simv != '\n') || (j < n)){
		if ((simv != ' ') && (simv != '.')) {
			simvPr[0] = simv; 
			data[m][j + 1] = atoi(simvPr);
			++j;
		}
		simv = fgetc(pF);
		}
		j = 0;
		simv = fgetc(pF);

	//��������� ������� �������� �� �����
	
	int i = 0;
	while (i < m){
		while (simv != '\n'){
		if ((simv != ' ') && (simv != '.')) {
			simvPr[0] = simv; 
			data[i][j + 1] = atoi(simvPr);
			++j;
		}
		simv = fgetc(pF);
		}
		++i;
		j = 0;
		simv = fgetc(pF);}
		data[2][2] = 0.5;
		data[2][3] = 2;
		
		
	//�������� ������ �������� ��������� ������

	i = 0;
	while ((simv != '\n') && (i < m)) {
		if ((simv != ' ') && (simv != '.')) 
		{
			simvPr[0] = simv; 
			data[i][0] = atoi(simvPr);
			++i;
		};
		simv = fgetc(pF);
	};
	data[m][0] = 0;
	//������ - ��������
	for (int q=0; q < m+1; ++q){
			for (int p=0; p < n+1; ++p){
				std::cout << data[q][p] << ' ';};
			cout << ' ' << std :: endl;
	}

	
	
	fclose(pF);

	free = new int[n]; //��������� ����������
	for (int i = 0; i < n; i++) {
		free[i] = i + 1;
	}

	depended = new int[m]; //�������� ����������
	for (int i = 0; i < m; i++) {
		depended[i] = n + i + 1;
	};

	Solve(data, free, depended, m, n);
	};

	//-----------------------------------------------------------------
void Solve(double **data, int *free, int *depended, int m, int n) {
	bool is_solve = true;
	//����� �������� �������
	int iter = 1;
	bool loop = true;
	cout << "����� �������� �������\n";
	while (loop) {
		loop = false;

		// ����� i0 ������, � ������������� ��������� (������������ �������)
		for (int i0 = 0; i0 < m; i0++) {
			if (data[i0][0] < 0) {
				int k = 0;
				// ����� k �������, � ������ ������������� ��������� (����������� �������)
				for (int j = 1; j < n + 1 && !k; j++) { 
					if (data[i0][j] < 0) {
						k = j;
					}
				}
				if (k) {
					loop = true;
					float min = FLT_MAX;
					int r = 0;
					// ����� r ������, 
					for (int i = 0; i < m; i++) { 
						if (data[i][0] / data[i][k] < min && data[i][0] / data[i][k] > 0) {
							r = i;
							min = data[i][0] / data[i][k];
						}
					}
					swap(r, k, data, free, depended, m, n);
					break;
				}
				else {
					std::cout << "��� �������\n";

				}
			}
		}
		if (!loop) break;
		cout << "\n" << iter++ << " ��������\n" << "\n";

		//������ - ��������
	for (int q=0; q < m+1; ++q){
			for (int p=0; p < n+1; ++p){
				std::cout << data[q][p] << ' ';};
			cout << ' ' << std :: endl;};
	}

	//����� ������������ �������
	loop = true;
	iter = 1;
	cout << "����� ������������ �������\n";
	while (loop) {
		loop = false;
		int r = 0, k = 0;
		for (int j = 1; j < n + 1; j++) { //����� k �������
			if (data[m][j] > 0)  {
				k = j;
				float minimum = FLT_MAX;
				for (int i = 0; i < 3; i++) { //����� r ������
					if (data[i][j] > 0 && data[i][0] / data[i][k] < minimum) {
						r = i;
						minimum = data[i][0] / data[i][k];
					}
				}

				if (minimum < FLT_MAX) {
					loop = true;
					swap(r, k, data, free, depended, m, n);
					break;
				}
				else {
					is_solve = false;
					break;
				}
			}
		}
		if (!loop) break;
		cout << "\n" << iter++ << " ��������\n" << "\n";
		//������ - ��������
		cout << "     ";
		for (int y = 0; y < n; y ++)
			cout << "X" << free[y] << ' ';
		cout << "\n" ;

	for (int q=0; q < m+1; ++q)
	{ 
		if (q < m)  
			cout << "X" << depended[q] << ' ' ;

			for (int p=0; p < n+1; ++p)
				cout << data[q][p] << ' ';
			cout << ' ' <<  "\n";
	}
	cout << "\n";
	}

	//����� ����������
	if (!is_solve) cout << "��� �������\n";
	else {
		for (int i = 0; i < m; i++) {
			cout << "X" << i + 1 << " = ";
			for (int j = 0; j < n; j++) {
				if (free[j] == i + 1) {
					cout << "0\n";
				}
				if (depended[j] == i + 1) {
					cout << data[j][0] << "\n";
				}
			}
		}
		std::cout << "F  = " << data[m][0] << "\n";
	}

};

void swap(int r, int k, double **data, int *free, int *depended, int m, int n) {

	for (int i = 0; i < m + 1; i++) {
		for (int j = 0; j < n + 1; j++) {
			if (i != r && j != k) {
				data[i][j] = data[i][j] - data[i][k] * data[r][j] / data[r][k];
			}
		}
	}

	for (int i = 0; i < m + 1; i++) {
		if (i != r) {
			data[i][k] = -data[i][k] / data[r][k];
		}
	}

	for (int j = 0; j < n + 1; j++) {
		if (j != k) {
			data[r][j] = data[r][j] / data[r][k];
		}
	}

	data[r][k] = 1.0 / data[r][k];

	int i = free[k - 1];
	free[k - 1] = depended[r];
	depended[r] = i;
};