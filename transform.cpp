#include "Sudoku.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

void Sudoku::changeNum(int a , int b){
	if((a < 1 || 9 < a) || (b < 1 || 9 < b)){
		puts("error : changeNum");
		exit(1);
	}

	for(int i = 0 ; i < 81 ; i++){
		if(Q[i/9][i%9] == a){Q[i/9][i%9] = b;}
		else if(Q[i/9][i%9] == b){Q[i/9][i%9] = a;}
		else{continue;}
	}
}

void Sudoku::changeRow(int a , int b){
	if((a < 0 || 2 < a) || (b < 0 || 2 < b)){
		puts("error : changeRow");
		exit(1);
	}

	int buf[9];

	copy(Q[a*3] , Q[a*3] + 9 , buf);
	copy(Q[b*3] , Q[b*3] + 9 , Q[a*3]);
	copy(buf , buf + 9 , Q[b*3]);

	copy(Q[a*3+1] , Q[a*3+1] + 9 , buf);
	copy(Q[b*3+1] , Q[b*3+1] + 9 , Q[a*3+1]);
	copy(buf , buf + 9 , Q[b*3+1]);

	copy(Q[a*3+2] , Q[a*3+2] + 9 , buf);
	copy(Q[b*3+2] , Q[b*3+2] + 9 , Q[a*3+2]);
	copy(buf , buf + 9 , Q[b*3+2]);
}

void Sudoku::changeCol(int a , int b){
	if((a < 0 || 2 < a) || (b < 0 || 2 < b)){
		puts("error : changeCol");
		exit(1);
	}

	int buf[9][3];

	for(int i = 0 ; i < 9 ; i++){copy(Q[i] + a * 3 , Q[i] + a * 3 + 3 , buf[i]);}
	for(int i = 0 ; i < 9 ; i++){copy(Q[i] + b * 3 , Q[i] + b * 3 + 3 , Q[i] + a * 3);}
	for(int i = 0 ; i < 9 ; i++){copy(buf[i] , buf[i] + 3 , Q[i] + b * 3);}
}

void Sudoku::rotate(int n){
	if(n < 0 || 100 < n){
		puts("error : rotate");
		exit(1);
	}

	int buf[9][9];

	switch(n%4){
		case 0:
			break;
		case 1:
			for(int i = 0 ; i < 81 ; i++){buf[i%9][8-i/9] = Q[i/9][i%9];}
			copy(buf[0] , buf[0] + 81 , Q[0]);
			break;
		case 2:
			for(int i = 0 ; i < 81 ; i++){*(buf[0] + 80 - i) = Q[i/9][i%9];}
			copy(buf[0] , buf[0] + 81 , Q[0]);
			break;
		case 3:
			for(int i = 0 ; i < 81 ; i++){buf[8-i%9][i/9] = Q[i/9][i%9];}
			copy(buf[0] , buf[0] + 81 , Q[0]);
			break;
		default:
			puts("error : rotate");
			exit(1);
	}
}

void Sudoku::flip(int n){
	int buf[9][9];

	copy(Q[0] , Q[0] + 81 , buf[0]);

	switch(n){
		case 0:
			for(int i = 0 ; i < 9 ; i++){
				for(int j = 0 ; j < 9 ; j++){
					Q[i][j] = buf[i][8-j];
				}
			}
			break;
		case 1:
			for(int i = 0 ; i < 9 ; i++){copy(buf[8-i] , buf[8-i] + 9 , Q[i]);}
			break;
		default:
			puts("error : flip");
			exit(1);
	}
}

void Sudoku::transform(){
	srand(time(NULL));

	for(int i = 0 ; i < 7 ; i++){
		changeNum(rand()%9 + 1 , rand()%9 + 1);
		changeRow(rand()%3 , rand()%3);
		changeCol(rand()%3 , rand()%3);
		rotate(rand()%101);
		flip(rand()%2);
	}

	print();
}
