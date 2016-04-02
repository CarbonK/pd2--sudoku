#include "Sudoku.h"
#include <cstdio>
#include <cstdlib>
#include <algorithm>
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
	int count1 = 0 , count2 = 0;
	int Qs[9][9];
	bool Ms[9][9][9];

	copy(Q[0] , Q[0] + 81 , Qs[0]);
	copy(Map[0][0] , Map[0][0] + 729 , Ms[0][0]);

	if(pos == 81){return 1;}
	else if(Q[pos/9][pos%9] != 0){
		return recur(pos + 1);
	}
	else{
		for(int i = 0 ; i < 9 ; i++){
			if(!Map[i][pos/9][pos%9]){
				Q[pos/9][pos%9] = i + 1;
				modifyMap(i , pos / 9 , pos % 9);
				modifyQ();
				if(solutionCheck()){
					switch(recur(pos + 1)){
						case 0:
							break;
						case 1:
							count1++;
							break;
						case 2:
							count2++;
							break;
						default:
							puts("error : recur");
							exit(1);
					}
				}
				copy(Qs[0] , Qs[0] + 81 , Q[0]);
				copy(Ms[0][0] , Ms[0][0] + 729 , Map[0][0]);
			}
			if(count1 > 1){break;}
		}
		switch(count1){
			case 0:
				if(count2 == 0){return 0;}
				else{return 2;}
				break;
			case 1:
				return 1;
				break;
			default:
				return 2;
		}
	}

	return 1;
}
