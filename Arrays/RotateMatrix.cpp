#include <iostream>
#include <vector>
using namespace std;

// Iterative Approach
// Time Complexity: O(N^2)
// Space Complexity: O(1)

void rotateMatrix(vector<vector<int>> &mat, int n, int m) {
    int rowStart = 0; int rowEnd = n-1; int colStart = 0; int colEnd = m-1;

    while(rowStart < rowEnd && colStart < colEnd){
        int temp = mat[rowStart][colStart];
        for(int c = colStart+1; c <= colEnd; c++){
            swap(mat[rowStart][c], temp);
        }
        rowStart++;

        for(int r = rowStart; r <= rowEnd; r++){
            swap(mat[r][colEnd], temp);
        }
        colEnd--;

        for(int c = colEnd; c >= colStart; c--){
            swap(mat[rowEnd][c], temp);
        }
        rowEnd--;

        for(int r = rowEnd; r >= rowStart; r--){
            swap(mat[r][colStart], temp);
        }
        colStart++;

        mat[rowStart-1][colStart-1] = temp;
    }
}

// Recursive Approach
// Time Complexity: O(N^2)
// Space Complexity: O(max(N, M))

void rotateMatrixHelper(vector<vector<int>> &mat, int rowStart, int colStart, int rowEnd, int colEnd)
{
    // Base Condition
    if(rowStart >= rowEnd or colStart >= colEnd)
    {
        return; 
    }

    if (rowStart >= rowEnd - 1 || colStart >= colEnd - 1)
    { 
        return; 
    }

    int previous = mat[rowStart + 1][colStart]; 
    int current;
        
    // Move elements of first row from the remaining rows
    for (int i = colStart; i < colEnd; i++) 
    { 
        current = mat[rowStart][i]; 
        mat[rowStart][i] = previous; 
        previous = current; 
    } 

    rowStart++; 

    // Move elements of last column from the remaining columns 
    for (int i = rowStart; i < rowEnd; i++) 
    { 
        current = mat[i][colEnd-1]; 
        mat[i][colEnd-1] = previous; 
        previous = current; 
    } 
    colEnd--; 

    // Move elements of last row from the remaining rows 
    if (rowStart < rowEnd) 
    { 
        for (int i = colEnd - 1; i >= colStart; i--) 
        { 
            current = mat[rowEnd-1][i]; 
            mat[rowEnd-1][i] = previous; 
            previous = current; 
        } 
    } 
    rowEnd--; 

    // Move elements of first column from the remaining rows 
    if (colStart < colEnd) 
    { 
        for (int i = rowEnd-1; i >= rowStart; i--) 
        { 
            current = mat[i][colStart]; 
            mat[i][colStart] = previous; 
            previous = current; 
        } 
    } 
    colStart++; 

    // Recursively rotate inner rings
    rotateMatrixHelper(mat, rowStart, colStart, rowEnd, colEnd);

}

void rotateMatrix(vector<vector<int>> &mat, int n, int m)
{
    // Recursive function to rotate the matrix
	rotateMatrixHelper(mat, 0, 0, n, m);
} 