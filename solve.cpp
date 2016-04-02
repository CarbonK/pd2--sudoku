#include "Sudoku.h"
#include <cstdio>
#include <algorithm>
using namespace std;

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
