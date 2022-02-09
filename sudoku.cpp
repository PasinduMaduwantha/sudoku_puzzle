/*
* DATE       : 06-09-2021
* COURSE     : PROGRAMMING QUEST (CO2210)
* TITLE      : QUEST 01- SUDOKU PUZZEL AND SOLVER
* AUTHOR     : MADHUWANTHA A.P.
* INDEX NO   : 19/ENG/121
*/
#include "sudoku.h"

int main()
{
    for (int row = 0; row < size; row++)
        for (int col; col < size; col++)
            puzzel[row][col] = 0;   //intialize the puzzel with 0

    int missing;    //missing cells
    do
    {
        cout << "Select How many missing cells(2 to 4) in one row/coloumn : ";
        cin >> missing;
    } while (missing<2 || missing>4);

    Sudoku s;   //define sudoku class type variable s
    s.generator();    //call puzzel generator
    s.removeSomeNumbers(missing);
    s.printPuzzel(); //print the sudoku
    
    cout<<"wait 3s before start to solve :-)\n";
    Sleep(3000); //wait 3s before start to solve :-)
    
    cout << "\n\nLets Slove the Puzzel\n\n";
    if (s.solve())   //call solve to slove the puzzel
        s.printPuzzel();
    else
        cout << "No solution exists";

    return 0;
}