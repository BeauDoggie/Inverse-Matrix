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
	Matrix* operator*(float a)
	{
		Matrix* r = new Matrix(maxcol, maxrow);
		for (int i = 0; i < maxcol; i++)
		{
			for (int j = 0; j < maxrow; j++)
			{
				r->matrixdata[i][j] = matrixdata[i][j] * a;
			}
		}
		return r;
	}
	Matrix* operator=(Matrix* m)
	{
		Matrix* r = new Matrix(maxcol, maxrow);
		for (int i = 0; i < maxcol; i++)
		{
			for (int j = 0; j < maxrow; j++)
			{
				r->matrixdata[i][j] = m->matrixdata[i][j];
			}
		}
		return r;
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
	void getCofactor(Matrix* A, Matrix* temp, int p, int q, int n)
	{
		int i = 0, j = 0;

		for (int row = 0; row < n; row++)
		{
			for (int col = 0; col < n; col++)
			{
				if (row != p && col != q)
				{
					temp->matrixdata[i][j++] = A->matrixdata[row][col];
					if (j == n - 1)
					{
						j = 0;
						i++;
					}
				}
			}
		}
	}
	int determ(Matrix* a, int n) 
	{
		int det = 0, p, h, k, i, j;
		Matrix* temp = new Matrix(n, n);
		if (n == 1) 
		{
			return a->matrixdata[0][0];
		}
		else if (n == 2) 
		{
			det = (a->matrixdata[0][0] * a->matrixdata[1][1] - a->matrixdata[0][1] * a->matrixdata[1][0]);
			return det;
		}
		else 
		{
			for (p = 0; p < n; p++) 
			{
				h = 0;
				k = 0;
				for (i = 1; i < n; i++) 
				{
					for (j = 0; j < n; j++) 
					{
						if (j == p) 
						{
							continue;
						}
						temp->matrixdata[h][k] = a->matrixdata[i][j];
						k++;
						if (k == n - 1) 
						{
							h++;
							k = 0;
						}
					}
				}
				det = det + a->matrixdata[0][p] * pow(-1, p) * determ(temp, n - 1);
			}
			return det;
		}
	}

	void adjoint(Matrix* A, Matrix* adj)
	{
		// temp is used to store cofactors of A[][] 
		int sign = 1;
		Matrix* temp = new Matrix(A->maxcol, A->maxrow);

		for (int i = 0; i < A->maxcol; i++)
		{
			for (int j = 0; j < A->maxrow; j++)
			{
				// Get cofactor of A[i][j] 
				getCofactor(A, temp, i, j, A->maxcol);

				// sign of adj[j][i] positive if sum of row 
				// and column indexes is even. 
				sign = ((i + j) % 2 == 0) ? 1 : -1;

				// Interchanging rows and columns to get the 
				// transpose of the cofactor matrix 
				adj->matrixdata[i][j] = (sign) * (determ(temp, A->maxcol - 1));
			}
		}
	}
	Matrix* Linearequation()
	{
		//for i = x,y,z ��
	}
};

void MatrixMultiplyprogram()
{
	Manager MNG;
	//�Է°� �޾ƿ;���
	//cout << "������� ���� ���α׷���" << endl << endl;

	//cout << "������� �ڵ����� 2�� ��������Ŷ�~!��" << endl << endl;
	//cout << "��1��° ����� ���� ũ�⸦ �Է��϶�~!��" << endl;

	int hang = 0, yull = 0;

	cin >> yull;
	//cout << "��1��° ����� ���� ũ�⸦ �Է��϶�~!��" << endl;

	cin >> hang;

	Matrix* matrix1 = new Matrix(yull, hang);

	//cout << "������� ���Ҹ� 1,1 ���� 1,2 ������� �ʰ� �Է��� ũ�⸸ŭ���� �Է��ҰŶ�~!��" << endl;
	int inputdata = 0;

	for (int i = 0; i < yull; i++)
	{
		for (int j = 0; j < hang; j++)
		{
			cin >> inputdata;
			matrix1->InputMatrix(i, j, inputdata);
			cout << endl;
			matrix1->OuptPutAll();
		}
	}
	float det = (float)MNG.determ(matrix1, yull);

	MNG.MatrixTranspos(matrix1);
	//matrix1->OuptPutAll();

	Matrix* adj = new Matrix(matrix1->maxcol, matrix1->maxrow);
	MNG.adjoint(matrix1, adj);
	//adj->OuptPutAll();

	Matrix* r = new Matrix(matrix1->maxcol, matrix1->maxrow);
	
	//r = adj * (1 / det);
	for (int i = 0; i < adj->maxcol; i++)
	{
		for (int j = 0; j < adj->maxrow; j++)
		{
			adj->matrixdata[i][j] *= (1 / det);
		}
	}
	r = adj;
	r->OuptPutAll();
	//cout << "�ڴ� �ߴ�? ���� 2��° ����� ���� ������~��" << endl;

	//int hang2 = 0, yull2 = 0;
	//cin >> yull2;
	//cout << "������ 2��° ����� ���� ������~��" << endl;
	//cin >> hang2;
	//Matrix* matrix2 = new Matrix(yull2, hang2);

	//cout << "������� ���Ҹ� 1,1 ���� 1,2 ������� �ʰ� �Է��� ũ�⸸ŭ���� �Է��ҰŶ�~!��" << endl;


	//int inputdata2 = 0;
	//for (int i = 0; i < yull2; i++)
	//{
	//	for (int j = 0; j < hang2; j++)
	//	{
	//		cin >> inputdata2;
	//		matrix2->InputMatrix(i, j, inputdata2);
	//		cout << endl;
	//		matrix2->OuptPutAll();
	//	}
	//}

	//cout << endl << endl;

	//cout << "�ڵ� ����� ���� ����!��" << endl << endl;

	/*Matrix* result = new Matrix(yull2, hang);

	result = MNG.MatrixMultiply(result, matrix1, matrix2);

	result->OuptPutAll();*/

	//���� ����� ������¡?

	int a = 0;
	for (int i = 0; i < 1; i++)
	{
		cin >> a;
	}
}

int main(void)
{
	MatrixMultiplyprogram();
}