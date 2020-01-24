// counthar.cpp
// Chaweinta Hale
// 2019-10-08
//
// For CS 311 Fall 2019
// Source for countHAR Functions

#include "counthar.h"       // For Counthar prototypes

//countHAR
// Does not throw any exceptions
// Returns the int number of holey ant runs on a given board, with specified hole, start and finish tiles.
// Bulk of the work finding solutions is handed off to countHAR_recurse by passing it partial solutions.
// Pre:
//      0 <= hole_x < dim_x
//      start_x, finish_x, must be non-negative and <= to dim_x
//      start_y, finish_y, must be non-negative and <= to dim_y
int countHAR(int dim_x, int dim_y, int hole_x, int hole_y, int start_x, int start_y, int finish_x, int finish_y){
    int total = 0;
    vector<vector<int>> board(dim_x, vector<int>(dim_y, 0));
    board[hole_x][hole_y] = 1;
    board[start_x][start_y] = 1;
    int squaresLeft = (dim_x*dim_y)-2;
    total += countHAR_recurse(board, dim_x, dim_y, finish_x, finish_y, start_x, start_y, squaresLeft);
    return total;
}

// countHAR_recurse
// Does not throw any exceptions
// Given a partial solution to the HAR Problem,
// determine whether the ant's current position on the board has any possible runs to
// finish tile. If there is no possible movement, then the return value is
// 0.
// Pre:
//      board represents a dim_x times dim_y board
//      curr_x, finish_x, must be non-negative and <= to dim_x
//      curr_y, finish_y, must be non-negative and <= to dim_y
//      0 <= squaresLeft <= (dim_x times dim_y).
int countHAR_recurse(vector<vector<int>> & board,int dim_x, int dim_y,
                    int finish_x, int finish_y,
                    int curr_x, int curr_y, int squaresLeft){
    if (squaresLeft == 0 && curr_x == finish_x && curr_y == finish_y){  //All tiles visited AND ant is at the finish tile = complete solution
        return 1;
    }
    int total = 0;
    //checks movement northward from current position
    int northMov = curr_y+1;
    if(northMov < dim_y && northMov >= 0 ){ //Checks if tile attempting to move to is on the board
            if(board[curr_x][northMov] == 0){//Checks if tile attempting to move to has already been used
                curr_y = northMov;
                board[curr_x][curr_y] = 1;
                squaresLeft--;
                total += countHAR_recurse(board, dim_x, dim_y, finish_x, finish_y, curr_x, curr_y, squaresLeft);
                //Restores all changes, except changes to total.
                board[curr_x][curr_y] = 0;
                curr_y--;
                squaresLeft++;
            }
    }
    //repeats movement check, this time for eastward from current position
    int eastMov = curr_x+1;
    if(eastMov < dim_x && eastMov >= 0 ){
            if(board[eastMov][curr_y] == 0){
                curr_x = eastMov;
                board[curr_x][curr_y] = 1;
                squaresLeft--;
                total += countHAR_recurse(board, dim_x, dim_y, finish_x, finish_y, curr_x, curr_y, squaresLeft);
                board[curr_x][curr_y] = 0;
                curr_x--;
                squaresLeft++;
            }
    }
    //repeats movement check, this time for southward from current position
    int southMov = curr_y-1;
    if(southMov < dim_y && southMov >= 0 ){
            if(board[curr_x][southMov] == 0){
                curr_y = southMov;
                board[curr_x][curr_y] = 1;
                squaresLeft--;
                total += countHAR_recurse(board, dim_x, dim_y, finish_x, finish_y, curr_x, curr_y, squaresLeft);
                board[curr_x][curr_y] = 0;
                curr_y++;
                squaresLeft++;
            }
    }
    //repeats movement check, this time for westward from current position
    int westMov = curr_x-1;
    if(westMov < dim_x && westMov >= 0 ){
            if(board[westMov][curr_y] == 0){
                curr_x = westMov;
                board[curr_x][curr_y] = 1;
                squaresLeft--;
                total += countHAR_recurse(board, dim_x, dim_y, finish_x, finish_y, curr_x, curr_y, squaresLeft);
                board[curr_x][curr_y] = 0;
                curr_x++;
                squaresLeft++;
            }
    }
    return total;
}
