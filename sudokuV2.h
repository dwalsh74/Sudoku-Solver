int main();
int getBlockIndex(int x);
void removeFromPossibilities(int array[9][9][9],int row,int col,int num);
void getNumberIndex(int array[9][9][9],int row, int col, int num,int secMatch[6]);
void evaluateSection(int possArray[9][9][9]);
void solutionCheck(int board[9][9],int solution[9][9]);
void dispBoard(int board[9][9]);
void dispPoss(int board[9][9], int poss[9][9][9]);
