#include <ansi_c.h>
#include "sudokuV2.h"

/*
board[row][column]
board template:
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0}

Sample Boards:

  Easy - Complete							
{0,0,0,2,6,0,7,0,1},		
{6,8,0,0,7,0,0,9,0},		
{1,9,0,0,0,4,5,0,0},		
{8,2,0,1,0,0,0,4,0},	
{0,0,4,6,0,2,9,0,0},		
{0,5,0,0,0,3,0,2,8},		
{0,0,9,3,0,0,0,7,4},		
{0,4,0,0,5,0,0,3,6},		
{7,0,3,0,1,8,0,0,0}			 

Intermediate - Complete
{0,2,0,6,0,8,0,0,0},
{5,8,0,0,0,9,7,0,0},
{0,0,0,0,4,0,0,0,0},
{3,7,0,0,0,0,5,0,0},
{6,0,0,0,0,0,0,0,4},
{0,0,8,0,0,0,0,1,3},
{0,0,0,0,2,0,0,0,0},
{0,0,9,8,0,0,0,3,6},
{0,0,0,3,0,6,0,9,0}

Difficult - Complete
{0,0,0,6,0,0,4,0,0},
{7,0,0,0,0,3,6,0,0},
{0,0,0,0,9,1,0,8,0},
{0,0,0,0,0,0,0,0,0},
{0,5,0,1,8,0,0,0,3},
{0,0,0,3,0,6,0,4,5},
{0,4,0,2,0,0,0,6,0},
{9,0,3,0,0,0,0,0,0},
{0,2,0,0,0,0,1,0,0}

Difficult 2 - Complete
{2,0,0,3,0,0,0,0,0},
{8,0,4,0,6,2,0,0,3},
{0,1,3,8,0,0,2,0,0},
{0,0,0,0,2,0,3,9,0},
{5,0,7,0,0,0,6,2,1},
{0,3,2,0,0,6,0,0,0},
{0,2,0,0,0,9,1,4,0},
{6,0,1,2,5,0,8,0,9},
{0,0,0,0,0,1,0,0,2}

Not Fun - Complete
{0,2,0,0,0,0,0,0,0},
{0,0,0,6,0,0,0,0,3},
{0,7,4,0,8,0,0,0,0},
{0,0,0,0,0,3,0,0,2},
{0,8,0,0,4,0,0,1,0},
{6,0,0,5,0,0,0,0,0},
{0,0,0,0,1,0,7,8,0},
{5,0,0,0,0,9,0,0,0},
{0,0,0,0,0,0,0,4,0}

World's Hardest
{8,0,0,0,0,0,0,0,0},
{0,0,3,6,0,0,0,0,0},
{0,7,0,0,9,0,2,0,0},
{0,5,0,0,0,7,0,0,0},
{0,0,0,0,4,5,7,0,0},
{0,0,0,1,0,0,0,3,0},
{0,0,1,0,0,0,0,6,8},
{0,0,8,5,0,0,0,1,0},
{0,9,0,0,0,0,4,0,0}



*/

int board[9][9] = 
{
{0,2,0,0,0,0,0,0,0},
{0,0,0,6,0,0,0,0,3},
{0,7,4,0,8,0,0,0,0},
{0,0,0,0,0,3,0,0,2},
{0,8,0,0,4,0,0,1,0},
{6,0,0,5,0,0,0,0,0},
{0,0,0,0,1,0,7,8,0},
{5,0,0,0,0,9,0,0,0},
{0,0,0,0,0,0,0,4,0}

};

int solCheck = 0;
int solution[9][9] = 
{
{1,2,6,4,3,7,9,5,8},
{8,9,5,6,2,1,4,7,3},
{3,7,4,9,8,5,1,2,6},
{4,5,7,1,9,3,8,6,2},
{9,8,3,2,4,6,5,1,7},
{6,1,2,5,7,8,3,9,4},
{2,6,9,3,1,4,7,8,5},
{5,4,8,7,6,9,2,3,1},
{7,3,1,8,5,2,6,4,9}


};

FILE *logFile;									//used to open and read a text file
char logFileName[] = "boardOutput.txt";	//The name of the text file from which the dll takes variables

int main()
{
	logFile = fopen(logFileName,"w");
	
	int blocksFilled = 0;
	int poss[9][9][9] = {0};
	int newBoard[9][9] = {0};
	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<9; j++)
		{ 
			newBoard[i][j] = board[i][j];
			solutionCheck(newBoard,solution);
		}
	}
	////////////////////////////////
	dispBoard(newBoard);
	////////////////////////////////
	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<9; j++)
		{  
			int row = i;
			int column = j;
			//count non-zero blocks. If 81, puzzle is complete
			if (newBoard[i][j] !=0)
			{
				blocksFilled++;
			}
			if (newBoard[i][j] == 0)
			{
				//checkBlocks(board,i,j);
				int blockNumbers[27] = {0};
				int k = 0; 
				//Get numbers from row
				for (int col = 0; col<9; col++)
				{
					if (newBoard[i][col] != 0)
					{
						blockNumbers[k] = newBoard[i][col];
						k++;
					}
				}
				//Get numbers from column
				for (int rownum = 0; rownum<9; rownum++)
				{
					if (newBoard[rownum][j] != 0)
					{
						blockNumbers[k] = newBoard[rownum][j];
						k++;
					}
				}
				//Get Block Indexes
				row = getBlockIndex(row);
				column = getBlockIndex(column);
				
				//Get numbers from block
				for (int m = row; m<row+3; m++)
				{
					for (int n = column; n<column+3; n++)
					{
						if (newBoard[m][n] != 0)
						{
							blockNumbers[k] = newBoard[m][n];
							k++;
						}
					}
				}
				//check the number of possibilities for a blocks value. 
				//If there's only one possibility, set the block to that value
				if (blockNumbers[0] != 0)//make sure array is not empty 
				{
					int numPossibilities = 0;
					int num = 1;
					while (num < 10)
					{
						int match = 0;
						for (int indx = 0; indx<27; indx++)
						{
							if (num == blockNumbers[indx])
							{
								match = 1;
								break;
							}
						}
						if (match == 0)
						{
							numPossibilities++;
							poss[i][j][numPossibilities-1] = num;
						}
						num++;
					}
					if (numPossibilities == 1)
					{
						newBoard[i][j] = poss[i][j][0];
						solutionCheck(newBoard,solution);
						blocksFilled++;
						int rnum = poss[i][j][0];
						removeFromPossibilities(poss,i,j,rnum);
						removeFromPossibilities(poss,9,j,rnum);
						removeFromPossibilities(poss,i,9,rnum);
					}
				}
			}
		}
	}
	int revert = 0;
	int tryNum = 0;
	int tryNumHolder = 0;
	int successCount = 0;
	int noChange = 0;
	int try = 0;
	int backupPoss[9][9][9] = {0};
	int trySquare[2] = {10,10};
	int trySquare2[2] = {10,10};
	int backupBoard[9][9] = {0};
	int blocksFilledHolder = 0;
	int backupPoss2[9][9][9] = {0};
	int backupBoard2[9][9] = {0};
	int blocksFilledHolder2 = 0;
	int biggest[5] = {0};
	int xBiggest = biggest[0];
	int yBiggest = biggest[1];
	int backupRowCount[9][9] = {0};
	int backupColCount[9][9] = {0};
	int backupBlockCount[9][9] = {0};
	int backupRowCount2[9][9] = {0};
	int backupColCount2[9][9] = {0};
	int backupBlockCount2[9][9] = {0};
	
	while (blocksFilled != 81)
	{
		int tryCount = 0;
		int numPoss = 0;
		int lastPoss = 0;
		noChange++;
		
		for (int i = 0; i<9; i++)
		{
			for (int j = 0; j<9; j++)
			{
				numPoss = 0;
				for (int k = 0; k < 9; k++)
				{
					if (poss[i][j][k] != 0)
					{
						//get the number of possibilities for each number in each square
						lastPoss = poss[i][j][k];
						numPoss++;
					}
				}
				//printf("%d ",numPoss);
				if (numPoss == 1)
				{
					newBoard[i][j] = lastPoss;
					dispBoard(newBoard);
					solutionCheck(newBoard,solution);
					noChange = 0;
					blocksFilled++;
					removeFromPossibilities(poss,i,j,lastPoss);
					removeFromPossibilities(poss,9,j,lastPoss);
					removeFromPossibilities(poss,i,9,lastPoss);

				}
			}
			//printf("\n");
		}
		//printf("\n");
		//organize numbers from least to greatest. also remove non-trailing zeros
		for (int i = 0; i<9; i++)
		{
			for (int j = 0; j<9; j++)
			{ 
				for (int q = 0; q < 5; q++)
				{
					for (int r = 0; r < 8; r++)
					{
						if (poss[i][j][r] > poss[i][j][r+1])
						{
							int holder = poss[i][j][r];
							poss[i][j][r] = poss[i][j][r+1];
							poss[i][j][r+1] = holder;
						}
						if (poss[i][j][r] == 0 && poss[i][j][8] == 0)
						{
							for (int t = r; t < 8; t++)
							{
								poss[i][j][t] = poss[i][j][t+1];
							}
						}
					}
				}
			}
		}
		/*
		dispPoss(newBoard,poss);
		*/
		
		//assign value to any tile that is the only one able to hold that number for it's group
		int rowPoss[9][9][9] = {0};
		int colPoss[9][9][9] = {0};
		int blockPoss[9][9][9] = {0};
		int rowArrayCount[9][9] = {0};
		int colArrayCount[9][9] = {0};
		int blockArrayCount[9][9] = {0};		
		
		for (int i = 0; i<9; i++)
		{
			for (int j = 0; j<9; j++)
			{
				for (int k = 0; k < 9; k++)
				{
					rowPoss[i][j][k] = poss[i][j][k];
					colPoss[j][i][k] = poss[i][j][k];
					blockPoss[i][j][k] = poss[3*(i/3)+j/3][3*(i-3*(i/3))+(j-3*(j/3))][k];
					if (poss[i][j][k] != 0)
					{
						//get the number of possibilities for each number in each row/column/block
						for (int p = 0; p < 9; p++)
						{
							if (poss[i][j][k] == p+1)
							{
								rowArrayCount[i][p]++;
								colArrayCount[j][p]++;
								blockArrayCount[3*(i/3)+(j/3)][p]++;
							}
						}
					}
				}
			}
		}
		evaluateSection(rowPoss);
		evaluateSection(colPoss);
		evaluateSection(blockPoss);
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				for (int k = 0;k < 9;k++)
				{
					if (poss[i][j][k] != 0)
					{
						int found = 0;
						for (int num = 0; num < 9; num++)
						{
							if (rowPoss[i][j][num] == poss[i][j][k])
							{
								found++;
							}
							if (colPoss[j][i][num] == poss[i][j][k])
							{
								found++;
							}
							if (blockPoss[3*(i/3)+j/3][3*(i-3*(i/3))+(j-3*(j/3))][num] == poss[i][j][k])
							{
								found++;
							}
						}
						if (found != 3)
						{
							poss[i][j][k] = 0;
						}
					}
				}
			}
		} 
			
		int pairCount[9] = {0};
		for (int i = 0; i<9; i++)
		{
			for (int j = 0; j<9; j++)
			{
				for (int k = 0; k < 9; k++)
				{
					for (int m = 0; m < 9; m++)
					{
						if (poss[i][j][k] == m+1)
						{
							if ((rowArrayCount[i][m] == 1 || colArrayCount[j][m] == 1 || blockArrayCount[3*(i/3)+(j/3)][m] == 1) && newBoard[i][j] == 0)
							{
								newBoard[i][j] = m+1;
								solutionCheck(newBoard,solution);
								noChange = 0;
								blocksFilled++;
								for(int p = 0; p<9; p++)
								{
									poss[i][j][p] = 0;
								}
								removeFromPossibilities(poss,i,j,m+1);
								removeFromPossibilities(poss,9,j,m+1);
								removeFromPossibilities(poss,i,9,m+1);
							}
							//find sections that only have two areas which can hold a given number and 
							//see if they are both also in a second section. If so, the value can be removed
							//from all possibilities in the second section
							if (rowArrayCount[i][m] == 2)
							{
								pairCount[m]++;
								int rowMatch[6] = {10,10,10,10,10,10};
								getNumberIndex(poss,i,9,m+1,rowMatch);
								if (rowMatch[0] != 10 && rowMatch[1] != 10)
								{
									int col1 = getBlockIndex(rowMatch[0]);
									int col2 = getBlockIndex(rowMatch[1]);
									if (col1 == col2)
									{
										removeFromPossibilities(poss,i,rowMatch[0],m+1);
										for (int g = 0; g < 9; g++)
										{
											if (poss[i][rowMatch[0]][g] == 0 && poss[i][rowMatch[1]][g] == 0)
											{
												poss[i][rowMatch[0]][g] = m+1;
												poss[i][rowMatch[1]][g] = m+1;
												g = 9;
											}
										}
									}
								}
							}
							if (rowArrayCount[i][m] == 3)
							{
								int rowMatch[6] = {10,10,10,10,10,10};
								getNumberIndex(poss,i,9,m+1,rowMatch);
								if (rowMatch[0] != 10 && rowMatch[2] != 10)
								{
									int col1 = getBlockIndex(rowMatch[0]);
									int col2 = getBlockIndex(rowMatch[1]);
									int col3 = getBlockIndex(rowMatch[2]);
									if (col1 == col2 && col1 == col3)
									{
										removeFromPossibilities(poss,i,rowMatch[0],m+1);
										for (int g = 0; g < 9; g++)
										{
											if (poss[i][rowMatch[0]][g] == 0 && poss[i][rowMatch[1]][g] == 0 && poss[i][rowMatch[2]][g] == 0)
											{
												poss[i][rowMatch[0]][g] = m+1;
												poss[i][rowMatch[1]][g] = m+1;
												poss[i][rowMatch[2]][g] = m+1;
												g = 9;
											}
										}
									}
								}
							}
							if (colArrayCount[j][m] == 2)
							{
								pairCount[m]++;
								int colMatch[6] = {10,10,10,10,10,10};
								getNumberIndex(poss,9,j,m+1,colMatch);
								if (colMatch[0] != 10 && colMatch[1] != 10)
								{
									int row1 = getBlockIndex(colMatch[0]);
									int row2 = getBlockIndex(colMatch[1]);
									if (row1 == row2)
									{
										removeFromPossibilities(poss,colMatch[0],j,m+1);
										for (int g = 0; g < 9; g++)
										{
											if (poss[colMatch[0]][j][g] == 0 && poss[colMatch[1]][j][g] == 0)
											{
												poss[colMatch[0]][j][g] = m+1;
												poss[colMatch[1]][j][g] = m+1;
												g = 9;
											}
										}
									}
								}
							}
							if (colArrayCount[j][m] == 3)
							{
								pairCount[m]++;
								int colMatch[6] = {10,10,10,10,10,10};
								getNumberIndex(poss,9,j,m+1,colMatch);
								if (colMatch[0] != 10 && colMatch[2] != 10)
								{
									int row1 = getBlockIndex(colMatch[0]);
									int row2 = getBlockIndex(colMatch[1]);
									int row3 = getBlockIndex(colMatch[2]);
									if (row1 == row2 && row1 == row3)
									{
										removeFromPossibilities(poss,colMatch[0],j,m+1);
										for (int g = 0; g < 9; g++)
										{
											if (poss[colMatch[0]][j][g] == 0 && poss[colMatch[1]][j][g] == 0 && poss[colMatch[2]][j][g] == 0)
											{
												poss[colMatch[0]][j][g] = m+1;
												poss[colMatch[1]][j][g] = m+1;
												poss[colMatch[2]][j][g] = m+1;
												g = 9;
											}
										}
									}
								}
							}
							if (blockArrayCount[3*(i/3)+(j/3)][m] == 2)
							{ 
								pairCount[m]++;
								int secMatch[6] = {10,10,10,10,10,10};
								getNumberIndex(poss,i,j,m+1,secMatch);
								if (secMatch[0] != 10 && secMatch[1] != 10)
								{
									if (secMatch[0] == secMatch[1])
									{
										removeFromPossibilities(poss,secMatch[0],9,m+1);
										for (int g = 0; g < 9; g++)
										{
											if (poss[secMatch[0]][secMatch[3]][g] == 0 && poss[secMatch[1]][secMatch[4]][g] == 0)
											{
												poss[secMatch[0]][secMatch[3]][g] = m+1;
												poss[secMatch[1]][secMatch[4]][g] = m+1;
												g = 9;
											}
										}
									}
								}
								if (secMatch[3] != 10 && secMatch[4] != 10)
								{
									if (secMatch[3] == secMatch[4])
										{
										removeFromPossibilities(poss,9,secMatch[3],m+1);
										for (int g = 0; g < 9; g++)
										{
											if (poss[secMatch[0]][secMatch[3]][g] == 0 && poss[secMatch[1]][secMatch[4]][g] == 0)
											{
												poss[secMatch[0]][secMatch[3]][g] = m+1;
												poss[secMatch[1]][secMatch[4]][g] = m+1;
												g = 9;
											}
										}
									}
								}
							}
							if (blockArrayCount[3*(i/3)+(j/3)][m] == 3)
							{ 
								int secMatch[6] = {10,10,10,10,10,10};
								getNumberIndex(poss,i,j,m+1,secMatch);
								if (secMatch[0] != 10)
								{
									if (secMatch[0] == secMatch[1] && secMatch[0] == secMatch[2])
									{
										removeFromPossibilities(poss,secMatch[0],9,m+1);
										for (int g = 0; g < 9; g++)
										{
											if (poss[secMatch[0]][secMatch[3]][g] == 0 && poss[secMatch[1]][secMatch[4]][g] == 0 && poss[secMatch[2]][secMatch[5]][g] == 0)
											{
												poss[secMatch[0]][secMatch[3]][g] = m+1;
												poss[secMatch[1]][secMatch[4]][g] = m+1;
												poss[secMatch[2]][secMatch[5]][g] = m+1;
												g = 9;
											}
										}
									}
									if (secMatch[3] == secMatch[4] && secMatch[3] == secMatch[5])
									{
										removeFromPossibilities(poss,9,secMatch[3],m+1);
										for (int g = 0; g < 9; g++)
										{
											if (poss[secMatch[0]][secMatch[3]][g] == 0 && poss[secMatch[1]][secMatch[4]][g] == 0 && poss[secMatch[2]][secMatch[5]][g] == 0)
											{
												poss[secMatch[0]][secMatch[3]][g] = m+1;
												poss[secMatch[1]][secMatch[4]][g] = m+1;
												poss[secMatch[2]][secMatch[5]][g] = m+1;
												g = 9;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		
		//dispPoss(newBoard,poss); 
		
		//try a variable if no changes have been made in 3 iterations
		if (noChange > 1 || blocksFilled == 81)
		{
			if (try == 0)
			{
				try = 1;
				if(tryNum == 0)
				{
					blocksFilledHolder = blocksFilled;
					for (int i = 0; i<9; i++)
					{
						for (int j = 0; j<9; j++)
						{
							backupBoard[i][j] = newBoard[i][j];
							backupRowCount[i][j] = rowArrayCount[i][j];
							backupColCount[i][j] = colArrayCount[i][j];
							backupBlockCount[i][j] = blockArrayCount[i][j];
							for (int k = 0;k < 9;k++)
							{
								backupPoss[i][j][k] = poss[i][j][k];
							}
						}
					}
					//get most common 2
					for (int i = 0; i < 9;i++)
					{
						if (biggest[0] == 0 || pairCount[i] > pairCount[biggest[0] - 1])
						{
							biggest[4] = biggest[3]; 
							biggest[3] = biggest[2];
							biggest[2] = biggest[1];
							biggest[1] = biggest[0];
							biggest[0] = i + 1;
						}
						else if (biggest[1] == 0 || pairCount[i] > pairCount[biggest[1]-1])
						{
							biggest[4] = biggest[3]; 
							biggest[3] = biggest[2];
							biggest[2] = biggest[1];
							biggest[1] = i + 1;
						}
						else if (biggest[2] == 0 || pairCount[i] > pairCount[biggest[2]-1])
						{
							biggest[4] = biggest[3]; 
							biggest[3] = biggest[2];
							biggest[2] = i + 1;
						}
						else if (biggest[3] == 0 || pairCount[i] > pairCount[biggest[3]-1])
						{
							biggest[4] = biggest[3];
							biggest[3] = i + 1;
						}
						else if (biggest[4] == 0 || pairCount[i] > pairCount[biggest[4]-1])
						{
							biggest[4] = i + 1;
						}
					}
				}
				//find a square with two "2poss" numbers
				int notFoundCount = 0;
				xBiggest = biggest[0];
				if (biggest[0] == 0)
				{
					printf("stop");
				}
				yBiggest = biggest[1];
				for (int i = 0; i < 9; i++)
				{
					if (successCount == 0)
					{
						for (int j = 0; j < 9; j++)
						{
							rowArrayCount[i][j] = backupRowCount[i][j];
							colArrayCount[i][j] = backupColCount[i][j];
							blockArrayCount[i][j] = backupBlockCount[i][j];
						}
					}
					else if (successCount == 1)
					{
						for (int j = 0; j < 9; j++)
						{
							rowArrayCount[i][j] = backupRowCount2[i][j];
							colArrayCount[i][j] = backupColCount2[i][j];
							blockArrayCount[i][j] = backupBlockCount2[i][j];
						}
					}
				}
				int wideSearch = 0;
				for (int i = 0; i < 9;i++)
				{
					int match[6] = {10,10,10,10,10,10}; 
					int found = 0;
					if (wideSearch == 0)
					{	
						if (rowArrayCount[i][xBiggest-1] == 2 && rowArrayCount[i][yBiggest-1] == 2 && xBiggest != yBiggest)
						{
							match[1] = 10;
							getNumberIndex(poss,i,9,xBiggest,match);
							int big1 = match[0];
							int big2 = match[1];
							match[1] = 10;
							getNumberIndex(poss,i,9,yBiggest,match);
							int sbig1 = match[0];
							int sbig2 = match[1];
							if(big2 != 10)
							{
								if (big1 == sbig1 || big1 == sbig2)
								{
									trySquare[1] = big1;
									trySquare[0] = i;
									if (tryCount >= tryNum)
									{
										found = 1;
									}
									tryCount++;
								}
								else if (big2 == sbig1 || big2 == sbig2)
								{
									trySquare[1] = big2;
									trySquare[0] = i;
									if (tryCount >= tryNum)
									{
										found = 1;
									}
									tryCount++;
								}
							}
						
						}
						if (found == 0 && colArrayCount[i][xBiggest-1] == 2 && colArrayCount[i][yBiggest-1] == 2)
						{
							match[1] = 10;
							getNumberIndex(poss,9,i,xBiggest,match);
							int big1 = match[0];
							int big2 = match[1];
							match[1] = 10;
							getNumberIndex(poss,9,i,yBiggest,match);
							int sbig1 = match[0];
							int sbig2 = match[1];
							if(big2 != 10)
							{
								if (big1 == sbig1 || big1 == sbig2)
								{
									trySquare[0] = big1;
									trySquare[1] = i;
									if (tryCount >= tryNum && xBiggest != yBiggest)
									{
										found = 1;
									}
									tryCount++;
								}
								else if (big2 == sbig1 || big2 == sbig2)
								{
									trySquare[0] = big2;
									trySquare[1] = i;
									if (tryCount >= tryNum && xBiggest != yBiggest)
									{
										found = 1;
									}
									tryCount++;
								}
							}
						}
					}
					else if (wideSearch == 1 && notFoundCount < 3)
					{
						if (rowArrayCount[i][yBiggest-1] == 2)
						{
							match[1] = 10;
							getNumberIndex(poss,i,9,yBiggest,match);
							int big1 = match[0];
							int big2 = match[1];
							if(big2 != 10)
							{
								if (tryCount >= tryNum)
								{
									trySquare[1] = big1;
									trySquare[0] = i;
									found = 1; 
								}
								else if (tryCount+1 >= tryNum)
								{
									trySquare[1] = big2;
									trySquare[0] = i;
									found = 1;
								}
								tryCount++;
								tryCount++;
							}
						}
						if (found == 0 && colArrayCount[i][yBiggest-1] == 2)
						{
							match[1] = 10;
							getNumberIndex(poss,9,i,yBiggest,match);
							int big1 = match[0];
							int big2 = match[1];
							if(big2 != 10)
							{
								if (tryCount >= tryNum)
								{
									trySquare[1] = big1;
									trySquare[0] = i;
									found = 1; 
								}
								else if (tryCount+1 >= tryNum)
								{
									trySquare[1] = big2;
									trySquare[0] = i;
									found = 1;
								}
								tryCount++;
								tryCount++;
							}
						}
					}
					else 
					{
						notFoundCount == 10;
					}
					if (found == 1)
					{
						i = 9;
						notFoundCount = 0;
					}
					else if(found == 0 && i == 8 && notFoundCount == 0 && wideSearch == 1 && yBiggest != biggest[1])
					{
						yBiggest = biggest[1];
						i = 0;
					}
					else if(found == 0 && i == 8 && notFoundCount == 0)
					{
						yBiggest = biggest[2];
						i = 0;
						notFoundCount++;
					}
					else if(found == 0 && i == 8 && notFoundCount == 1)
					{
						yBiggest = biggest[3];
						i = 0;
						notFoundCount++;
					}
					else if(found == 0 && i == 8 && notFoundCount == 2)
					{
						yBiggest = biggest[4];
						i = 0;
						notFoundCount++;
					}
					else if(found == 0 && i == 8 && notFoundCount == 3)
					{
						xBiggest = biggest[1];
						yBiggest = biggest[2];
						i = 0;
						notFoundCount++;
					}
					else if(found == 0 && i == 8 && notFoundCount == 4)
					{
						yBiggest = biggest[3];
						i = 0;
						notFoundCount++;
					}
					else if(found == 0 && i == 8 && notFoundCount == 5)
					{
						yBiggest = biggest[4];
						i = 0;
						notFoundCount++;
					}
					else if(found == 0 && i == 8 && notFoundCount == 6)
					{
						xBiggest = biggest[2];
						yBiggest = biggest[3];
						i = 0;
						notFoundCount++;
					}
					/*else if(found == 0 && i == 8 && notFoundCount == 7)
					{
						yBiggest = biggest[4];
						i = 0;
						notFoundCount++;
					}
					else if(found == 0 && i == 8 && notFoundCount == 8)
					{
						xBiggest = biggest[3];
						yBiggest = biggest[4];
						i = 0;
						notFoundCount++;
					}
					else if (notFoundCount == 9)
					{
						wideSearch = 1;
						notFoundCount = 0;
						xBiggest = biggest[0];
						yBiggest = biggest[1];
						
					}*/
					else if (notFoundCount == 9 && i == 8)///notFoudCount is 10  when above line un-commented
					{
						revert = 1;
						if (tryNum == 150)
						{
							printf("stop");
						}
						printf("not found\n");
					}
				}
				if (trySquare[0] != 10 && trySquare[1] != 10)
				{
					poss[trySquare[0]][trySquare[1]][0] = xBiggest;
					for (int j = 1; j < 9; j++)
					{
						poss[trySquare[0]][trySquare[1]][j] = 0;
					}
				}
			}
			else if(try > 0)
			{
				int contradiction = 0;
				for (int num =  0; num < 9; num++)
				{
					for (int i = 0; i < 9; i++)
					{
						int rowOK = 0;
						int colOK = 0;
						int blockOK = 0;
						for (int j = 0; j < 9; j++)
						{
							if (newBoard[i][j] == num)
							{
								rowOK = 1;
							}
							if (newBoard[j][i] == num)
							{
								colOK = 1;
							}
							if (newBoard[3*(i/3)+j/3][3*(i-3*(i/3))+(j-3*(j/3))] == num)
							{
								blockOK = 1;
							}
							for (int k = 0; k < 9; k++)
							{
								if (poss[i][j][k] == num)
								{
									rowOK = 1;
								}
								if (poss[j][i][k] == num)
								{
									colOK = 1;
								}
								if (poss[3*(i/3)+j/3][3*(i-3*(i/3))+(j-3*(j/3))][k] == num)
								{
									blockOK = 1;
								}
							}
						}
						if (rowOK == 0 || colOK == 0 || blockOK == 0)
						{
							num = 9;
							i = 9;
							contradiction = 1;
						}
					}
				}
				if ((trySquare[0] == 10 || trySquare[1] == 10 || revert == 1) && successCount > 0)
				{
					printf("Reverted square %d,%d and square %d,%d \n",trySquare2[0],trySquare2[1],trySquare[0],trySquare[1]);
					blocksFilled = blocksFilledHolder2;
					
					successCount = 0;
					revert = 0;
					tryNum = tryNumHolder + 1;
					for (int i = 0; i < 9; i++)
					{
						for (int j = 0; j < 9; j++)
						{
							newBoard[i][j] = backupBoard2[i][j];
							backupRowCount[i][j] = backupRowCount2[i][j];
							backupColCount[i][j] = backupColCount2[i][j];
							backupBlockCount[i][j] = backupBlockCount2[i][j];
							for (int k = 0;k < 9;k++)
							{
								poss[i][j][k] = backupPoss2[i][j][k];
							}
						}
					}
				}
				////!!!!!!!!!!!!!!!!!!!!!!!!!!!!////
				else if ((trySquare[0] == 10 || trySquare[1] == 10) && successCount == 0)
				{
					//printf("Reverted square %d,%d and square %d,%d \n",trySquare2[0],trySquare2[1],trySquare[0],trySquare[1]);
					tryNum = tryNumHolder + 1;
					blocksFilled = blocksFilledHolder;
					for (int i = 0; i < 9; i++)
					{
						for (int j = 0; j < 9; j++)
						{
							newBoard[i][j] = backupBoard[i][j];
							for (int k = 0;k < 9;k++)
							{
								poss[i][j][k] = backupPoss[i][j][k];
							}
						}
					}
				}
				else if (contradiction == 1 && tryNum > 10 && successCount > 0)
				{
					//printf("Reverted square %d,%d and square %d,%d",trySquare2[0],trySquare2[1],trySquare[0],trySquare[1]);
					blocksFilled = blocksFilledHolder2;
					successCount = 0;
					tryNum = tryNumHolder + 1;
					for (int i = 0; i < 9; i++)
					{
						for (int j = 0; j < 9; j++)
						{
							newBoard[i][j] = backupBoard2[i][j];
							backupRowCount[i][j] = backupRowCount2[i][j];
							backupColCount[i][j] = backupColCount2[i][j];
							backupBlockCount[i][j] = backupBlockCount2[i][j];
							for (int k = 0;k < 9;k++)
							{
								poss[i][j][k] = backupPoss2[i][j][k];
							}
						}
					}
				}
				else if (contradiction == 1)
				{
					//contradiction found
					blocksFilled = blocksFilledHolder;
					for (int i = 0; i < 9; i++)
					{
						for (int j = 0; j < 9; j++)
						{
							newBoard[i][j] = backupBoard[i][j];
							for (int k = 0;k < 9;k++)
							{
								poss[i][j][k] = backupPoss[i][j][k];
							}
						}
					}
					if(try == 1)
					{
						poss[trySquare[0]][trySquare[1]][0] = yBiggest;
						for (int j = 1; j < 9; j++)
						{
							poss[trySquare[0]][trySquare[1]][j] = 0;
						}
						try = 2;
					}
					else if(try == 2)
					{
						//printf("neither worked\n");
						tryNum++;
						trySquare[0] = 10;
						trySquare[1] = 10;
						try = 0;
						noChange = 2;
						xBiggest = 0;
						yBiggest = 0;
					}
				}
				else if (successCount == 0)
				{
					//printf("Set square %d,%d \n",trySquare[0],trySquare[1]);
					successCount++;
					trySquare2[0] = trySquare[0];
					trySquare2[1] = trySquare[1];
					blocksFilledHolder2 = blocksFilledHolder;
					for (int i = 0; i<9; i++)
					{
						for (int j = 0; j<9; j++)
						{
							backupBoard2[i][j] = backupBoard[i][j];
							backupRowCount2[i][j] = backupRowCount[i][j];
							backupColCount2[i][j] = backupColCount[i][j];
							backupBlockCount2[i][j] = backupBlockCount[i][j];
							for (int k = 0;k < 9;k++)
							{
								backupPoss2[i][j][k] = backupPoss[i][j][k];
							}
						}
					}
					tryNumHolder = tryNum;
					tryCount = 0;
					trySquare[0] = 10;
					trySquare[1] = 10;
					try = 0;
					noChange = 0;
				}
				else
				{
					//printf("Set square %d,%d",trySquare[0],trySquare[1]);
					solCheck = 1;
					solutionCheck(newBoard,solution);
					solCheck = 0;
					tryNumHolder = 0;
					successCount = 0;
					tryNum = 0;
					tryCount = 0;
					trySquare[0] = 10;
					trySquare[1] = 10;
					trySquare2[0] = 10;
					trySquare2[1] = 10;
					try = 0;
					noChange = 0;
					xBiggest = 0;
					yBiggest = 0;
					biggest[3] = 0;
					biggest[2] = 0;
					biggest[1] = 0;
					biggest[0] = 0;
				}
			}
		}
		
		///Print board and possibility array for each iteration/////
		
	    //dispPoss(newBoard, poss);  
		//dispBoard(newBoard);
	}

	dispPoss(newBoard, poss);
	fputs("Finished Board\n",logFile);
	for (int i = 0; i<9; i++)
	{
		fprintf(logFile,"{");
		for (int j = 0; j<9; j++)
		{ 
			fprintf(logFile,"%d",newBoard[i][j]);
			if (j < 8)
			{
				fprintf(logFile,",");
			}
			printf("%d ",newBoard[i][j]);
		}
		fprintf(logFile,"}"); 
		fprintf(logFile,"\n");
		printf("\n");
	}
	fclose(logFile);//close the file
	return 0;
};
	

int getBlockIndex(int x)
{
	if (x<3)
		x = 0;
	else if (x<6)
		x = 3;
	else 
		x=6;
	return x;
};

void getNumberIndex(int array[9][9][9],int row, int col, int num,int secMatch[6])
{
	int count = 0;
	int row1 = getBlockIndex(row);
	int col1 = getBlockIndex(col);
	for(int i = 0; i < 9; i++)
	{
		if (row < 9 && col <9)
		{
			for (int m = row1; m < row1+3; m++)
			{
				for (int n = col1; n < col1+3; n++)
				{
					if (array[m][n][i] == num)
					{
						secMatch[count] = m;//row
						secMatch[count+3] = n;//column
						count++;	
					}
				}
			}
		}
		else
		{
			for(int j = 0; j < 9; j++)
			{
				if (row < 9 && col == 9)
				{
					if (array[row][i][j] == num)
					{
						secMatch[count] = i;
						count++;
					}
				}
				if (col < 9 && row == 9)
				{
					if (array[i][col][j] == num)
					{
						secMatch[count] = i;
						count++;
					}
				}
			}
		}
	}
};
	
void removeFromPossibilities(int array[9][9][9],int row,int col,int num)
{
	for (int i = 0; i<9; i++)
	{
		if (row < 9 && col <9)
		{
			int row1 = getBlockIndex(row);
			int col1 = getBlockIndex(col);
			for (int m = row1; m < row1+3; m++)
			{
				for (int n = col1; n < col1+3; n++)
				{
					if (array[m][n][i] == num)
					{
						array[m][n][i] = 0;	
					}
				}
			}
		} 
		if(row < 9 && col == 9)
		{
			for (int j = 0; j <9; j++)
			{
				if (array[row][i][j] == num)
				{
					array[row][i][j] = 0;
				}
			}
		}
		if (col < 9 && row == 9)
		{
			for (int j = 0; j <9; j++)
			{
				if (array[i][col][j] == num)
				{
					array[i][col][j] = 0;
				}
			}
		}
	}
};

//evaluate row, column or block to eliminate possibilities. **requires possibilities for each square to be ordered least to greatest 
void evaluateSection(int possArray[9][9][9])
{
	for (int group = 0; group < 9; group++)
	{
		int possNum = 0;
		int possNumArray[9][9] = {0};
		int possCount[9] = {0};
		for (int i = 0; i < 9; i++)
		{
			possNum = 0;
			for (int r = 0; r < 8; r++)
			{
				if (possArray[group][i][r] == 0 && possArray[group][i][8] == 0)
				{
					for (int t = r; t < 8; t++)
					{
						possArray[group][i][t] = possArray[group][i][t+1];
					}
				}
			}
			for (int j = 0; j < 9; j++)
			{
				if (possArray[group][i][j] != 0)
				{
					possNumArray[i][possNum] = possArray[group][i][j];
					possNum++;
				}
			}
			possCount[i] = possNum;
		}
		
		for (int i = 0; i < 9; i++)
		{
			if (possCount[i] == 2)
			{
				for (int j = i+1; j < 9; j++)
				{
					if (possCount[j] == 2)
					{
						if (possNumArray[i][0] == possNumArray[j][0] && possNumArray[i][1] == possNumArray[j][1])
						{
							for (int square = 0; square < 9; square++)
							{
								if (square != i && square != j)
								{
									for (int num = 0; num < 9; num++)
									{
										if (possArray[group][square][num] == possNumArray[i][0] || possArray[group][square][num] == possNumArray[i][1])
										{
											possArray[group][square][num] = 0;
										}
									}
								}
							}
						}
					}
				}
			}
			if (possCount[i] == 3)
			{
				for (int j = i+1; j < 9; j++)
				{
					if (possCount[j] == 3)
					{
						if(possNumArray[i][0] == possNumArray[j][0] && possNumArray[i][1] == possNumArray[j][1] && possNumArray[i][2] == possNumArray[j][2])
						{
							for (int k = j+1; k < 9; k++)
							{
								if (possCount[k] == 3)
								{
									if(possNumArray[i][0] == possNumArray[k][0] && possNumArray[i][1] == possNumArray[k][1] && possNumArray[i][2] == possNumArray[k][2])
									{
										for (int square = 0; square < 9; square++)
										{
											if (square != i && square != j && square != k)
											{
												for (int num = 0; num < 9; num++)
												{
													if (possArray[group][square][num] == possNumArray[i][0] || possArray[group][square][num] == possNumArray[i][1] || possArray[group][square][num] == possNumArray[i][2])
													{
														possArray[group][square][num] = 0;
													}
												}
											}
										}
									}
								}
							}
							for (int m = 0; m < 9; m++)
							{
								if (possCount[m] == 2)
								{
									if(possNumArray[i][0] == possNumArray[m][0] && (possNumArray[i][1] == possNumArray[m][1] || possNumArray[i][2] == possNumArray[m][2]))
									{
										for (int square = 0; square < 9; square++)
										{
											if (square != i && square != j && square != m)
											{
												for (int num = 0; num < 9; num++)
												{
													if (possArray[group][square][num] == possNumArray[i][0] || possArray[group][square][num] == possNumArray[i][1] || possArray[group][square][num] == possNumArray[i][2])
													{
														possArray[group][square][num] = 0;
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}; 

void solutionCheck(int board[9][9],int solution[9][9])
{
	if (solCheck == 1)
	{
		for (int i = 0; i<9; i++)
		{
			for (int j = 0; j<9; j++)
			{ 
				if (board[i][j] != 0 && board[i][j] != solution[i][j])
				{
					printf("error found");
				}
			}
		}
	}
};

void dispBoard(int board[9][9])
{
	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<9; j++)
		{ 
			printf("%d ",board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
};

void dispPoss(int board[9][9], int poss[9][9][9])
{
	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<9; j++)
		{ 
			printf("[");
			for (int k = 0; k<5; k++)
			{
				if(poss[i][j][0] == 0 && poss[i][j][1] == 0)
				{
					printf("%d",board[i][j]);
				}
				else
				printf("%d",poss[i][j][k]);
			}
			printf("]");
		}
		printf("\n");
	}
	printf("\n");
};
