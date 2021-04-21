#include<iostream>
#include<windows.h>
using namespace std;

int solutionCounter = 0;

bool isSafe(int row, int col, int arr[100][100], int n) //mengecek collision dengan queen lain
{														// 0 -> kosong
	//diagonal kanan bawah								// 2 -> ada queen
	if (col != n - 1 && row != n - 1)
		for (int i = row, j = col; i < n; i++, j++)
			if (arr[i + 1][j + 1] == 2)
				return false;

	//diagonal kiri bawah
	if (col != 0 && row != n)
		for (int i = row, j = col; i < n; i++, j--)
			if (arr[i + 1][j - 1] == 2)
				return false;

	//diagonal kiri atas
	if (row != 0 && col != 0)
		for (int i = row, j = col; i > 0; i--, j--)
			if (arr[i - 1][j - 1] == 2)
				return false;

	//diagonal kanan atas
	if (row != 0 && col != n - 1)
		for (int i = row, j = col; i > 0; i--, j++)
			if (arr[i - 1][j + 1] == 2)
				return false;

	//kanan
	if (col != n - 1)
		for (int j = col, i = row; j < n; j++)
			if (arr[i][j + 1] == 2)
				return false;

	//kiri
	if (col != 0)
		for (int j = col, i = row; j > 0; j--)
			if (arr[i][j - 1] == 2)
				return false;

	//atas
	if (row != 0)
		for (int j = col, i = row; i > 0; i--)
			if (arr[i - 1][j] == 2)
				return false;

	//bawah
	if (row != n - 1)
		for (int j = col, i = row; i < n; i++)
			if (arr[i + 1][j] == 2)
				return false;

	return true;
}

void initBoard(int arr[][100], int n) { //inisialisasi board agar semua kotak kosong (kosong = 0)
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			arr[i][j] = 0; //set cell empty
}

void displayBoard(int arr[][100], int n) { //display board
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j] == 0) {
				cout << "- ";
			}
			else if (arr[i][j] == 2) {
				cout << "Q ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

void placeQueen(int i, int j, int arr[100][100], int& queenCounter) {
	arr[i][j] = 2;  //meletakkan queen
	queenCounter++; //add queen counter
}
void removeQueen(int i, int j, int arr[100][100], int& queenCounter) {
	arr[i][j] = 0;  //menghapus queen
	queenCounter--; //subtract queen counter
}

void run(int arr[][100], int n, int col, int& queenCounter, int& mode) {

	for (int row = 0; row < n; row++) { //row counter
		if (isSafe(row, col, arr, n)) { //check if cell is safe to put queen

			placeQueen(row, col, arr, queenCounter);

			if (mode == 0) { //animation
				displayBoard(arr, n);
				Sleep(1000);
				system("cls");
			}
			else { //display all solution
				if (queenCounter == n) { //if queen on board == board size
					solutionCounter++;   //add solution counter
					cout << "Solution #" << solutionCounter << endl;
					displayBoard(arr, n);
				}
			}

			run(arr, n, col + 1, queenCounter, mode); //recursion to put next queen
			removeQueen(row, col, arr, queenCounter); //backtrack
		}
	}
}

void main()
{
	int n = 4;
	int arr[100][100];
	int queenCounter = 0, col = 0, mode;

	//initialize board
	initBoard(arr, n);

	//animation
	mode = 0;
	run(arr, n, col, queenCounter, mode);

	//display solution
	mode = 1;
	run(arr, n, col, queenCounter, mode);

	if (solutionCounter == 0)
		cout << "No solution found for " << n << "x" << n << " size board" << endl;
	else
		cout << "Solutions found : " << solutionCounter << endl;
}