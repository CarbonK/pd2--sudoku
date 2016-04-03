#ifndef SUDOKU
#define SUDOKU
class Sudoku{
	public:
		Sudoku();
		void giveQuestion();
		void readIn();
		void solve();
		void changeNum(int , int);
		void changeRow(int , int);
		void changeCol(int , int);
		void rotate(int);
		void flip(int);
		void transform();
		void print();
	private:
		int Q[9][9];
		bool Map[9][9][9];
		void clear();
		void initMap();
		void modifyQ();
		void modifyMap(int , int , int);
		bool solutionCheck();
		int spaceCheck();
		int recur(int);
		void dug(int);
};
#endif
