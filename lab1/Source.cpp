#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Program for matrix multiplication using Strassen algorithm.
// Note that understanding of Strassen algorithm is necessary for understanding this code.
// Matrix sizes should not exceed 100.

short int** allocate_for_matrix(short int size_1, short int size_2)
{
	short int** generic_matrix = new short int*[size_1];
	for (short int i = 0; i < size_1; i++)
		generic_matrix[i] = new short int[size_2];
	return generic_matrix;
} 

short int** allocate_for_square_matrix(short int size_of_square) // rename
{
	return allocate_for_matrix(size_of_square, size_of_square);
}

void fill_matrix(short int** matrix_to_fill, short int size_1, short int size_2,
	short int input_type)
{
	if (input_type == 1) // manual input
	{
		for (short int i = 0; i < size_1; i++)
			for (short int j = 0; j < size_2; j++)
				cin >> matrix_to_fill[i][j];
	} 
	else // rand()
	{
		for (short int i = 0; i < size_1; i++)
			for (short int j = 0; j < size_2; j++)
				matrix_to_fill[i][j] = rand() % 10;
	}
}

void print_matrix(short int** matrix, short int size_1, short int size_2)
{
	for (short int i = 0; i < size_1; i++)
	{
		for (short int j = 0; j < size_2; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
}

void move_matrix(short int** matrix_to_copy, short int** matrix_to_copy_to,
	short int size_1, short int size_2)
	// copies content of one short int** matrix (or part of it) into another
{
	for (short int i = 0; i < size_1; i++)
		for (short int j = 0; j < size_2; j++)
			matrix_to_copy_to[i][j] = matrix_to_copy[i][j];
}

short int** create_square_matrix_with_zeros(short int size_of_square)
{
	short int** square_matrix = allocate_for_square_matrix(size_of_square);
	for (short int i = 0; i < size_of_square; i++)
		for (short int j = 0; j < size_of_square; j++)
			square_matrix[i][j] = 0;
	return square_matrix;
}

void main()
{
	srand(time(NULL));
	short int size_of_A_1, size_of_A_2, size_of_B_1, size_of_B_2, input_type,
		expanded_matrix_size, half_expanded_size;
	system("chcp 1251");		//
	cout << "Вас приветствует программа" << endl <<
		"быстрого перемножения матриц методом Штрассена\n\n";

	//
	// Ввод размеров матрицы пользователем

	do
	{
		cout << "Введите размеры первой матрицы\n";
		cin >> size_of_A_1 >> size_of_A_2;
	} while (size_of_A_1 <= 0 || size_of_A_2 <= 0); // can technically be more 100
	do
	{
		cout << "\nВведите размеры второй матрицы\n";
		cin >> size_of_B_1 >> size_of_B_2;
	} while (size_of_B_1 <= 0 || size_of_B_2 <= 0);

	short int** matrix_A = allocate_for_matrix(size_of_A_1, size_of_A_2);
	short int** matrix_B = allocate_for_matrix(size_of_B_1, size_of_B_2);
	// we can use expanded version from the beginning, though
	
	//
	// Выбор способа заполнения и заполнение матриц

	do
	{
		cout << "\nВыберите способ заполнения матриц\n" <<
			"1 - Вручную \n2 - Случайным образом\n";
		cin >> input_type;
	} while (input_type < 1 || input_type > 2);

	fill_matrix(matrix_A, size_of_A_1, size_of_A_2, input_type);
	fill_matrix(matrix_B, size_of_B_1, size_of_B_2, input_type);
	cout << "\nМатрица 1\n\n";
	print_matrix(matrix_A, size_of_A_1, size_of_A_2);
	cout << "\nМатрица 2\n\n";
	print_matrix(matrix_B, size_of_B_1, size_of_B_2);

	//
	// Приведение матриц к требуемому размеру

	expanded_matrix_size = 2;
	while (expanded_matrix_size <= size_of_A_1 || expanded_matrix_size <= size_of_A_2
		|| expanded_matrix_size <= size_of_B_1 || expanded_matrix_size <= size_of_B_2) 
		// can just use variable with max
		expanded_matrix_size *= 2;
	half_expanded_size = expanded_matrix_size / 2;
	
	short int** expanded_matrix_A = create_square_matrix_with_zeros(expanded_matrix_size);
	short int** expanded_matrix_B = create_square_matrix_with_zeros(expanded_matrix_size);
	// creating expanded ones and filling them with zeros
	// technically, only part of them need to be filled like that

	move_matrix(matrix_A, expanded_matrix_A, size_of_A_1, size_of_A_2);
	move_matrix(matrix_B, expanded_matrix_B, size_of_B_1, size_of_B_2);
	// copying matrix_A in the begginning of expanded one, same for B

	cout << "\nРасширенные матрицы:\n";
	cout << "\nМатрица 1\n\n";
	print_matrix(expanded_matrix_A, expanded_matrix_size, expanded_matrix_size);
	cout << "\nМатрица 2\n\n";
	print_matrix(expanded_matrix_B, expanded_matrix_size, expanded_matrix_size);
	
	//
	// Разбиение матриц на подматрицы и их заполнение

	// partition A and B into equally sized block matrices
	short int** expanded_matrix_A_1_1 = allocate_for_square_matrix(half_expanded_size);
	short int** expanded_matrix_A_1_2 = allocate_for_square_matrix(half_expanded_size);
	short int** expanded_matrix_A_2_1 = allocate_for_square_matrix(half_expanded_size);
	short int** expanded_matrix_A_2_2 = allocate_for_square_matrix(half_expanded_size);
	for (short int i = 0; i < half_expanded_size; i++)
		for (short int j = 0; j < half_expanded_size; j++)
		{
			expanded_matrix_A_1_1[i][j] = expanded_matrix_A[i][j];
			expanded_matrix_A_1_2[i][j] = expanded_matrix_A[i][j + half_expanded_size];
			expanded_matrix_A_2_1[i][j] = expanded_matrix_A[i + half_expanded_size][j];
			expanded_matrix_A_2_2[i][j] = expanded_matrix_A[i + half_expanded_size][j + half_expanded_size];
		}
	short int** expanded_matrix_B_1_1 = allocate_for_square_matrix(half_expanded_size);
	short int** expanded_matrix_B_1_2 = allocate_for_square_matrix(half_expanded_size);
	short int** expanded_matrix_B_2_1 = allocate_for_square_matrix(half_expanded_size);
	short int** expanded_matrix_B_2_2 = allocate_for_square_matrix(half_expanded_size);
	for (short int i = 0; i < half_expanded_size; i++)
		for (short int j = 0; j < half_expanded_size; j++)
		{
			expanded_matrix_B_1_1[i][j] = expanded_matrix_B[i][j];
			expanded_matrix_B_1_2[i][j] = expanded_matrix_B[i][j + half_expanded_size];
			expanded_matrix_B_2_1[i][j] = expanded_matrix_B[i + half_expanded_size][j];
			expanded_matrix_B_2_2[i][j] = expanded_matrix_B[i + half_expanded_size][j + half_expanded_size];
		}

	//
	// Создание и вычисление значений промежуточных матриц

	short int*** p = new short int** [8];
	// 8 pointers, so P_N in math can correspond to p[N] in code
	p[0] = NULL;
	for (short int i = 1; i < 8; i++)
		p[i] = create_square_matrix_with_zeros(half_expanded_size);
	for (short int i = 0; i < half_expanded_size; i++)
		for (short int j = 0; j < half_expanded_size; j++)
			for (short int z = 0; z < half_expanded_size; z++)
			{
				p[1][i][j] += (expanded_matrix_A_1_1[i][z] + expanded_matrix_A_2_2[i][z]) *
					(expanded_matrix_B_1_1[z][j] + expanded_matrix_B_2_2[z][j]);
				p[2][i][j] += (expanded_matrix_A_2_1[i][z] + expanded_matrix_A_2_2[i][z]) *
					expanded_matrix_B_1_1[z][j];
				p[3][i][j] += expanded_matrix_A_1_1[i][z] * 
					(expanded_matrix_B_1_2[z][j] - expanded_matrix_B_2_2[z][j]);
				p[4][i][j] += expanded_matrix_A_2_2[i][z] * 
					(expanded_matrix_B_2_1[z][j] - expanded_matrix_B_1_1[z][j]);
				p[5][i][j] += (expanded_matrix_A_1_1[i][z] + expanded_matrix_A_1_2[i][z]) *
					expanded_matrix_B_2_2[z][j];
				p[6][i][j] += (expanded_matrix_A_2_1[i][z] - expanded_matrix_A_1_1[i][z]) *
					(expanded_matrix_B_1_1[z][j] + expanded_matrix_B_1_2[z][j]);
				p[7][i][j] += (expanded_matrix_A_1_2[i][z] - expanded_matrix_A_2_2[i][z]) *
					(expanded_matrix_B_2_1[z][j] + expanded_matrix_B_2_2[z][j]);
			}

	//
	// Создание вспомогательных матриц

	short int** extended_matrix_C_1_1 = allocate_for_square_matrix(half_expanded_size);
	short int** extended_matrix_C_1_2 = allocate_for_square_matrix(half_expanded_size);
	short int** extended_matrix_C_2_1 = allocate_for_square_matrix(half_expanded_size);
	short int** extended_matrix_C_2_2 = allocate_for_square_matrix(half_expanded_size);

	//
	// Подсчет значений вспомогательных матриц из промежуточных

	for (short int i = 0; i < half_expanded_size; i++)
		for (short int j = 0; j < half_expanded_size; j++)
		{
			extended_matrix_C_1_1[i][j] = p[1][i][j] + p[4][i][j] - p[5][i][j] + p[7][i][j];
			extended_matrix_C_1_2[i][j] = p[3][i][j] + p[5][i][j];
			extended_matrix_C_2_1[i][j] = p[2][i][j] + p[4][i][j];
			extended_matrix_C_2_2[i][j] = p[1][i][j] - p[2][i][j] + p[3][i][j] + p[6][i][j];
		}

	//
	// Перенос информации из вспомогательных матриц в результирующую

	short int** extended_matrix_C = allocate_for_square_matrix(expanded_matrix_size);
	for (short int i = 0; i < half_expanded_size; i++)
		for (short int j = 0; j < half_expanded_size; j++)
		{
			extended_matrix_C[i][j] = extended_matrix_C_1_1[i][j];
			extended_matrix_C[i][j + half_expanded_size] = extended_matrix_C_1_2[i][j];
			extended_matrix_C[i + half_expanded_size][j] = extended_matrix_C_2_1[i][j];
			extended_matrix_C[i + half_expanded_size][j + half_expanded_size] = extended_matrix_C_2_2[i][j];
		}

	//
	// Выравнивание границ результирующей матрицы

	short int how_many_are_not_zeros = 0, right_border = 100, down_border = 100;
	for (short int i = 0; i < expanded_matrix_size; i++)
	{
		how_many_are_not_zeros = 0;
		for (short int j = 0; j < expanded_matrix_size; j++)
			if (extended_matrix_C[i][j] != 0)
			{
				how_many_are_not_zeros++;
				right_border = 100;
			}
		if (how_many_are_not_zeros == 0 && i < right_border)
			right_border = i;
	}
	for (short int i = 0; i < expanded_matrix_size; i++)
	{
		how_many_are_not_zeros = 0;
		for (short int j = 0; j < expanded_matrix_size; j++)
			if (extended_matrix_C[j][i] != 0)
			{
				how_many_are_not_zeros++;
				down_border = 100;
			}
		if (how_many_are_not_zeros == 0 && i < down_border)
			down_border = i;
	}
	short int** matrix_C = allocate_for_matrix(right_border, down_border);
	move_matrix(extended_matrix_C, matrix_C, right_border, down_border);

	//
	// Вывод результирующей матрицы
	
	cout << "\nРезультирующая матрица\n\n";
	print_matrix(matrix_C, right_border, down_border);
	cout << endl;
	system("pause");

	//
	// Очистка динамической памяти

	// some of it can be cleared after it's no longer used, lessening maximum memory usage
	// but putting it all in one place lessen the chance of memory leak due to programming mistake
	for (short int i = 0; i < size_of_A_1; i++)
		delete[] matrix_A[i];
	for (short int i = 0; i < size_of_B_1; i++)
		delete[] matrix_B[i];
	for (short int i = 0; i < expanded_matrix_size; i++)
		delete[] expanded_matrix_A[i], expanded_matrix_B[i], extended_matrix_C[i];
	for (short int i = 0; i < right_border; i++)
		delete[] matrix_C[i];
	for (short int i = 0; i < half_expanded_size; i++)
	{
		delete[] expanded_matrix_A_1_1[i], expanded_matrix_A_1_2[i],
			expanded_matrix_A_2_1[i], expanded_matrix_A_2_2[i],
			expanded_matrix_B_1_1[i], expanded_matrix_B_1_2[i],
			expanded_matrix_B_2_1[i], expanded_matrix_B_2_2[i],
			extended_matrix_C_1_1[i], extended_matrix_C_1_2[i],
			extended_matrix_C_2_1[i], extended_matrix_C_2_2[i];
		for (short int j = 1; j < 8; j++)
			delete[] p[j][i];
	}
	for (short int i = 1; i < 8; i++)
		delete[] p[i];
	delete[] matrix_A, matrix_B, matrix_C,
		expanded_matrix_A, expanded_matrix_B, extended_matrix_C,
		expanded_matrix_A_1_1, expanded_matrix_A_1_2, 
		expanded_matrix_A_2_1, expanded_matrix_A_2_2,
		expanded_matrix_B_1_1, expanded_matrix_B_1_2, 
		expanded_matrix_B_2_1, expanded_matrix_B_2_2,
		extended_matrix_C_1_1, extended_matrix_C_1_2, 
		extended_matrix_C_2_1, extended_matrix_C_2_2,
		p;
}
// refacroring:
// variables renamed (becoming more self-explanatory)
// repeating parts of code moved to functions
// types changed (int -> short int, int** p1-p7 -> short int*** p)
// necessary commentaries added
