#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;
struct Matrix
{
public:
	int maxrow;
	int maxcol;
	vector<vector<double>> matrixdata;
	Matrix(int row, int col)
	{
		//matrixdata�� ���θ� num�� ������� �缳���ϸ�, 0���� �ʱ�ȭ��
		matrixdata.resize(col, vector<double>(row, 0));
		maxrow = row;
		maxcol = col;
	}

	void OutputMatrix(int rownum, int colnum)
	{
		if (rownum > maxrow || colnum > maxcol)
			return;
		for (int i = 0; i < maxrow; i++)
		{
			for (int j = 0; j < maxcol; j++)
			{
				if (rownum - 1 == i && colnum - 1 == j)
					cout << matrixdata[i][j];
			}
			cout << "\n";
		}
	}

	void InputMatrix(int rownum, int colnum, int data)
	{
		//rownum�� �ƽ����� �� �۾����ÿ��� �����ؾ���
		if (rownum > maxrow || colnum > maxcol || rownum < 0 || colnum < 0)
		{
			cout << "NO! " << data << endl;
			return;
		}

		matrixdata[colnum][rownum] = data;
	}

	void InputMatrix2(int rownum, int colnum, int data)
	{
		//rownum�� �ƽ����� �� �۾����ÿ��� �����ؾ���
		if (rownum > maxrow || colnum > maxcol || rownum <= 0 || colnum <= 0)
		{
			cout << "NO! " << data << endl;
			return;
		}

		matrixdata[colnum-1][rownum-1] = data;
	}

	void OuptPutAll()
	{
		for (int i = 0; i < maxrow; i++)
		{
			for (int j = 0; j < maxcol; j++)
			{
				cout << matrixdata[j][i] << " ";
			}
			cout << endl;
			cout << endl;
		}
		cout << endl;
		cout << endl;
		cout << endl;
	}
};
struct Manager
{
	Matrix* MatrixMultiply(Matrix* out, Matrix* a, Matrix* b)
	{
		if (a->maxcol != b->maxrow)
		{
			cout << "NO MATCH!" << endl;
		}

		for (int i = 0; i < a->maxcol; i++)
		{
			for (int j = 0; j < b->maxrow; j++)
			{
				double t = 0;
				for (int k = 0; k < b->maxcol; k++)
				{
					t = t + a->matrixdata[j][k] * b->matrixdata[k][i];
					//cout << i << " " << j << " " << k << " " << t << " " << endl;
				}
				out->matrixdata[j][i] = t;
			}
		}

		return out;
	}

	Matrix* MatrixTranspos(Matrix* out)
	{
		Matrix* tempMatrix = new Matrix(out->maxrow, out->maxcol);
		for (int i = 0; i < tempMatrix->maxrow; i++)
		{
			for (int j = 0; j < tempMatrix->maxcol; j++)
			{
				tempMatrix->matrixdata[i][j] = out->matrixdata[i][j];
			}
		}
		for (int i = 0; i < tempMatrix->maxrow; i++)
		{
			for (int j = 0; j < tempMatrix->maxcol; j++)
			{
				out->matrixdata[j][i] = tempMatrix->matrixdata[i][j];
			}
		}

		return out;
	}

	Matrix* MatrixInverse(Matrix* out)
	{

		return out;
	}
};
int main(void)
{
	Manager MNG;
	//�Է°� �޾ƿ;���
	cout << "������� ���� ���α׷���" << endl << endl;

	cout << "������� �ڵ����� 2�� ��������Ŷ�~!��" << endl << endl;
	cout << "��2��° ����� ���� ũ�⸦ �Է��϶�~!��" << endl;

	int hang = 0, yull = 0;

	cin >> hang;
	cout << "��1��° ����� ���� ũ�⸦ �Է��϶�~!��" << endl;

	cin >> yull;
	
	Matrix* matrix1 = new Matrix(yull, hang);

	cout << "������� ���Ҹ� 1,1 ���� 1,2 ������� �ʰ� �Է��� ũ�⸸ŭ���� �Է��ҰŶ�~!��" << endl;
	int inputdata = 0;
	
	for (int i = 0; i < yull ; i++)
	{
		for (int j = 0; j < hang; j++)
		{
			cin >> inputdata;
			matrix1->InputMatrix(i, j, inputdata);
			cout << endl;
			matrix1->OuptPutAll();
		}
	}
	cout << "�ڴ� �ߴ�? ���� 2��° ����� ���� ������~��" << endl;

	int hang2 = 0, yull2 = 0;
	cin >> hang2;
	cout << "������ 2��° ����� ���� ������~��" << endl;
	cin >> yull2;
	Matrix* matrix2 = new Matrix(yull2, hang2);

	cout << "������� ���Ҹ� 1,1 ���� 1,2 ������� �ʰ� �Է��� ũ�⸸ŭ���� �Է��ҰŶ�~!��" << endl;


	int inputdata2 = 0;
	for (int i = 0; i < yull2; i++)
	{
		for (int j = 0; j < hang2; j++)
		{
			cin >> inputdata2;
			matrix2->InputMatrix(i, j, inputdata2);
			cout << endl;
			matrix2->OuptPutAll();
		}
	}

	cout << endl << endl;

	cout << "�ڵ� ����� ���� ����!��" << endl << endl;

	Matrix* result = new Matrix(yull2 , hang);

	result = MNG.MatrixMultiply(result, matrix1, matrix2);

	result->OuptPutAll();

	/*Matrix* mat = new Matrix(2, 3);
	mat->InputMatrix2(1, 1, 1);
	mat->InputMatrix2(1, 2, 2);
	mat->InputMatrix2(1, 3, 3);
	mat->InputMatrix2(2, 1, 4);
	mat->InputMatrix2(2, 2, 5);
	mat->InputMatrix2(2, 3, 6);
	Matrix* mat2 = new Matrix(3, 2);
	mat2->InputMatrix2(1, 1, 1);
	mat2->InputMatrix2(1, 2, 2);
	mat2->InputMatrix2(2, 1, 3);
	mat2->InputMatrix2(2, 2, 4);
	mat2->InputMatrix2(3, 1, 5);
	mat2->InputMatrix2(3, 2, 6);
	mat->OuptPutAll();
	mat2->OuptPutAll();
	Matrix* result = new Matrix(3, 3);
	result = MNG.MatrixMultiply(result, mat, mat2);
	result->OuptPutAll();
	MNG.MatrixTranspos(result);
	result->OuptPutAll();*/
	return 0;
}