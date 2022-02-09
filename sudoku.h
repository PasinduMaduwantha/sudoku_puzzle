/*
HEADER  : sudoku.h
CONTENT : sudoku generator and solver
*/

#include <iostream>
#include <Windows.h>
using namespace std;
#define size 9
int puzzel[size][size];

class Sudoku
{
    public:
    /*
    Function    : isRowExsist :-chek the value can acceptable along the row
    Iputs       : row, value
    Output      : if value already in a row return true
    */
    bool isRowExsist(int row, int val)
    {
    for (int col = 0; col < size; col++)
        if (puzzel[row][col] == val)
            return true;
    return false;
    }

    /*
    Function    : isColExsist :-chek the value can acceptable along the coloumn
    Iputs       : coloumn, value
    Output      : if value already in a coloumn return true
    */
    bool isColExsist(int col, int val)
    {
        for (int row = 0; row < size; row++)
            if (puzzel[row][col] == val)
                return true;
        return false;
    }

    /*
    Function    : isSubArrayExsist :-chek the value can acceptable with sub array(box)
    Iputs       : row, coloumn and value
    Output      : if value already inside the sub array return true
    */
    bool isSubArrayExsist(int r, int c, int val)
    {
        int boxStartRow = r - r % 3;
        int boxStartCol = c - c % 3;
        for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
                if (puzzel[row+boxStartRow][col+boxStartCol] == val)
                    return true;
        return false;
    }

    /*
    Function    : isSafe :-check all theree conditions are ture
    Iputs       : row, coloumn and value
    Output      : if value apply safely return true
    */
    bool isSafe(int row, int col, int num)
    {
        return !isRowExsist(row, num) && !isColExsist(col, num) && !isSubArrayExsist(row, col, num);
    }

    /*
    Function    : fillDiagonal :-fill diagonal sub matrices
    Iputs       : diagonal coordinate
    Output      : N/A
    */
    void fillDiagonal(int cr, int cc)
    {
        for (int row = 0; row < 3; row++)
            for (int col = 0; col < 3; col++)
            {
                int num;
                do
                {
                    num = 1 + rand() % 9;   //pick a random number between 1 and 9
                } while (isSubArrayExsist(row+cr, col+cc, num));
                puzzel[row+cr][col+cc]=num;
            }
    }
    /*
    Function    : fillRemaining :-  recursive function
    Iputs       :
    Output      :
    */
    bool fillRemaining(int row, int col)
    {

        if (col>=size && row<size-1)
        {
            row++;
            col = 0;
        }
        if (row>=size && col>=size)
            return true;
    
        if (row < 3)
        {
            if (col < 3)
                col = 3;
        }
        else if (row < size-3)
        {
            if (col==(int)(row/3)*3)
                col +=  3;
        }
        else
        {
            if (col == size-3)
            {
                row++;
                col = 0;
                if (row>=size)
                    return true;
            }
        }
    
        for (int num = 1; num<=size; num++)
        {
            if (isSafe(row, col, num))
            {
                puzzel[row][col] = num;
                if (fillRemaining(row, col+1))
                    return true;
    
                puzzel[row][col] = 0;
            }
        }
        return false;
    }
    /*
    Function    : generator
    Iputs       : N/A
    Output      : N/A
    */
    void generator()
    {
        fillDiagonal(0, 0); //diadonal matrix 1
        fillDiagonal(3, 3); //diadonal matrix 2
        fillDiagonal(6, 6); //diadonal matrix 3
        fillRemaining(0, 3);    //fill remainig spaces
    }

    /*
    Function    : removeSomeNumbers :-remove vlue in some cell
    Iputs       : missing cell in each row
    Output      : N/A  
    */
    void removeSomeNumbers(int noOfCells)
    {
        
        for (int row = 0; row < size; row++)
        {
            int count = 0;
            while (count < noOfCells)
            {
                int cell= rand() % 9;
                if(puzzel[row][cell]!=0)
                {
                    puzzel[row][cell] = 0;
                    count++;
                }
            }  
        }
                            
    }
    /*
    Function    : findMissingCells :-update row and column of the mising cells
    Iputs       : current row and coloumn
    Output      : if all cells filled then return false as no emptyplace 
    */
    bool findMissingCells(int &row, int &col)
    { 
    for (row = 0; row < size; row++)
        for (col = 0; col < size; col++)
            if (puzzel[row][col] == 0) //marked with 0 is empty
                return true;
        return false;
    }

    /*
    Function    : solve 
    Iputs       : N/A
    Output      : if all cells filled then return true, if can't to complete work then return false 
      */
    bool solve()
    {
        int row, col;
        if (!findMissingCells(row, col))
            return true; //when all places are filled
        for (int num = 1; num <= 9; num++)
        { 
            // puzzel[row][col] = num; //little trick to indicate worng values
            // printPuzzel();
            // puzzel[row][col] = 0;
            //it take a lot of time to print all wron valuse in the puzzel
            if (isSafe(row, col, num))
            {//if all conditions satisfied 
                puzzel[row][col] = num;
                if (solve())    //solution find using recursive method
                    return true;
                puzzel[row][col] = 0; 
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                cout << "Worng value: " << num << " !Choose an another value\n";
                Sleep(50);
                system("cls");
            }
        }
        return false;
    }

    /*
    Function    : printPuzzel :-print the puzzel
    Iputs       : N/A (use globaly declared 2d array)
    Output      : N/A  
    */
    void printPuzzel()
    {
        for (int row = 0; row < size; row++){
            for (int col = 0; col < size; col++){
                if(col == 3 || col == 6)
                    cout << " | ";
                cout << puzzel[row][col] <<" ";
            }
            if(row == 2 || row == 5){
                cout << endl;
                for(int i = 0; i<size; i++)
                    cout << "---";
            }
            cout << endl;
        }
        cout << "\n\n";
    }

};

