#include "Sudoku.h"
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
using namespace std;

Sudoku::Sudoku(){clear();}

void Sudoku::readIn(){
	clear();

	for(int i = 0 ; i < 81 ; i++){scanf("%d" , Q[0] + i);}
}

void Sudoku::print(){
	for(int i = 0 ; i < 81 ; i++){
		printf("%d" , Q[i/9][i%9]);
		if(i%9 != 8){printf(" ");}
		else{puts("");}
	}
}

void Sudoku::clear(){
	fill(Q[0] , Q[0] + 81  , 0);
	fill(Map[0][0] , Map[0][0] + 729 , false);
}

void Sudoku::initMap(){
	fill(Map[0][0] , Map[0][0] + 729 , false);
	for(int i = 0 ; i < 81 ; i++){if(Q[i/9][i%9] != 0){modifyMap(Q[i/9][i%9]-1 , i / 9 , i % 9);}}
}

void Sudoku::modifyQ(){
	int i , j , k , count;

	for(i = 0 ; i < 9 ; i++){
		for(j = 0 ; j < 9 ; j++){
			count = 0;
			for(k = 0 ; k < 9 && count <= 1 ; k++){if(!Map[i][j][k]){count++;}}
			if(count == 1){
				for(k = 0 ; k < 9 ; k++){
					if(!Map[i][j][k]){
						Q[j][k] = i + 1;
						modifyMap(i , j , k);
						break;
					}
				}
			}
			count = 0;
			for(k = 0 ; k < 9 && count <= 1; k++){if(!Map[i][k][j]){count++;}}
			if(count == 1){
				for(k = 0 ; k < 9 ; k++){
					if(!Map[i][k][j]){
						Q[k][j] = i + 1;
						modifyMap(i , k , j);
						break;
					}
				}
			}
			count = 0;
			for(k = 0 ; k < 9 && count <= 1; k++){if(!Map[i][j/3*3+k/3][j%3*3+k%3]){count++;}}
			if(count == 1){
				for(k = 0 ; k < 9 ; k++){
					if(!Map[i][j/3*3+k/3][j%3*3+k%3]){
						Q[j/3*3+k/3][j%3*3+k%3] = i + 1;
						modifyMap(i , j/3*3+k/3 , j%3*3+k%3);
						break;
					}
				}
			}
			if(Q[i][j] == 0){
				count = 0;
				for(k = 0 ; k < 9 && count <=1 ; k++){if(!Map[k][i][j]){count++;}}
				if(count == 1){
					for(k = 0 ; k < 9 ; k++){
						if(!Map[k][i][j]){
							Q[i][j] = k + 1;
							modifyMap(k , i , j);
							break;
						}
					}
				}
			}
		}
	}
}

void Sudoku::modifyMap(int x , int y , int z){
	int i , j , k , l;

	for(i = 0 ; i < 9 ; i++){
		Map[x][y][i] = true;
		Map[x][i][z] = true;
		Map[i][y][z] = true;
	}

	for(i = y / 3 * 3 ; i < y / 3 * 3 + 3 ; i++){
		for(j = z / 3 * 3 ; j < z / 3 * 3 + 3 ; j++){
			Map[x][i][j] = true;
		}
	}

	for(i = 0 ; i < 9 ; i++){
		for(j = 0 ; j < 9 ; j++){
			for(k = 0 ; k < 9 ; k++){
				if(!Map[i][j/3*3+k/3][j%3*3+k%3]){
					for(l = (k / 3 + 1) * 3 ; l < 9 ; l++){if(!Map[i][j/3*3+l/3][j%3*3+l%3]){break;}}
					if(l == 9){for(l = 0 ; l < 9 ; l++){if(l / 3 != (j%3*3+k%3) / 3){Map[i][j/3*3+k/3][l] = true;}}}
					break;
				}
				if(!Map[i][j%3*3+k%3][j/3*3+k/3]){
					for((l = k / 3 + 1) * 3 ; l < 9 ; l++){if(!Map[i][j%3*3+l%3][j/3*3+l/3]){break;}}
					if(l == 9){for(l = 0 ; l < 9 ; l++){if(l / 3 != (j%3*3+k%3) / 3){Map[i][l][j/3*3+k/3] = true;}}}
					break;
				}
			}
		}
	}
}

bool Sudoku::solutionCheck(){
	int i , j;

	for(i = 0 ; i < 81 ; i++){
		if(Q[i/9][i%9] != 0){
			for(j = 0 ; j < 9 ; j++){
				if(Q[i/9][j] == Q[i/9][i%9] && j != i % 9){return false;}
				if(Q[j][i%9] == Q[i/9][i%9] && j != i / 9){return false;}
				if(Q[i/9/3*3+j/3][i%9/3*3+j%3] == Q[i/9][i%9] && (i/9/3*3+j/3!=i/9||i%9/3*3+j%3!=i%9)){return false;}
			}
		}
		else{
			for(j = 0 ; j < 9 ; j++){if(!Map[j][i/9][i%9]){break;}}
			if(j == 9){return false;}
		}
	}

	return true;
}

int Sudoku::spaceCheck(){
	int space = 0;
	for(int i = 0 ; i < 81 ; i++){if(Q[i/9][i%9] == 0){space++;}}
	return space;
}

int Sudoku::recur(int pos){
	int i , j;
	int Qs[9][9];
	bool Ms[9][9][9];
	static int count , ans[9][9];

	if(pos == 0){count = 0;};

	copy(Q[0] , Q[0] + 81 , Qs[0]);
	copy(Map[0][0] , Map[0][0] + 729 , Ms[0][0]);

	if(pos == 81){
		copy(Q[0] , Q[0] + 81 , ans[0]);
		count++;
		if(count == 1){return 1;}
		else{return 2;}
	}
	else if(Q[pos/9][pos%9] != 0){
		return recur(pos + 1);
	}
	else{
		for(i = 0 ; i < 9 ; i++){
			if(!Map[i][pos/9][pos%9]){
				Q[pos/9][pos%9] = i + 1;
				modifyMap(i , pos / 9 , pos % 9);
				modifyQ();
				if(solutionCheck()){
					switch(recur(pos + 1)){
						case 0:
							break;
						case 1:
							break;
						case 2:
							return 2;
							break;
						default:
							puts("error : recur");
							exit(1);
					}
				}
				copy(Qs[0] , Qs[0] + 81 , Q[0]);
				copy(Ms[0][0] , Ms[0][0] + 729 , Map[0][0]);
			}
		}
	}

	if(count == 1){
		copy(ans[0] , ans[0] + 81 , Q[0]);
		return 1;
	}
	else{return 0;}
}

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

void Sudoku::giveQuestion(){
	int exam[9][9] = 
	{{0,0,0,0,5,0,0,9,0},
	{4,0,0,0,0,0,0,0,2},
	{0,0,6,7,0,0,0,0,0},
	{2,0,0,0,0,0,0,0,0},
	{9,5,0,0,0,0,0,1,0},
	{0,0,0,6,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,3},
	{0,8,0,0,0,0,7,0,6},
	{0,0,0,0,1,3,0,0,0}};

	copy(exam[0] , exam[0] + 81 , Q[0]);
	print();
}

void Sudoku::solve(){
	int prespace = 81;

	if(!solutionCheck()){puts("0");}
	else if(solutionCheck() > 64){puts("2");}
	else{
		initMap();
		while(1){
			modifyQ();
			if(spaceCheck() == prespace){break;}
			else{prespace = spaceCheck();}
		}
		switch(recur(0)){
			case 0:
				puts("0");
				break;
			case 1:
				puts("1");
				print();
				break;
			case 2:
				puts("2");
				break;
			default:
				puts("error : recur");
				exit(1);
		}
	}
}

