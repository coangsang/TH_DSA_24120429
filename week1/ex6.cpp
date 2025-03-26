#include <iostream>
using namespace std;

#define N 8
int board[N][N] = {0};
int solution = 0;

bool isSafe(int row, int col){
	for(int i = 0;i<row;i++){
		//kiểm tra cột
		if(board[i][col]){
			return false;
		}
		// Kiểm tra đường chéo trái
    	if (col - (row - i) >= 0 && board[i][col - (row - i)] == 1){
    	    return false;
    	}
    	
    	// Kiểm tra đường chéo phải
    	if (col + (row - i) < N && board[i][col + (row - i)] == 1){
        	return false;
    	}
	}
	return true;
}

void solveNQueen(int row){
	if(row == N){
		solution++;
		return;
	}
	for(int col = 0;col<N;col++){
		if(isSafe(row, col)){
			board[row][col] = 1;
			solveNQueen(row+1);
			board[row][col] = 0;
		}
	}
}

int main(){
	solveNQueen(0);
	cout<<solution;
	return 0;
}