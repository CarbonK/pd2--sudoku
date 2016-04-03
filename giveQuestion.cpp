#include "Sudoku.h"
#include <cstdio>
#include <ctime>
#include <algorithm>
using namespace std;

void Sudoku::giveQuestion(){
	clear();
	srand(time(NULL));

	transform();
}
