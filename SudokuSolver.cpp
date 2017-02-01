#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <math.h>

using namespace std;

//Functions
bool EmptyFinder(int **sudoku, int &row, int &col, int size);
bool ProperToUse(int **sudoku, int row, int col, int num, int size);
bool Check(int **sudoku, int size);
void Print(int **sudoku,int **color, int size);
bool Solve(int **sudoku, int size);
bool Row(int **sudoku, int row, int num, int size);
bool Col(int **sudoku, int col, int num, int size);
bool Box(int **sudoku, int SR, int SC, int num, int size);
void SetColor(unsigned short color);


int main()
{
	//introduction
	SetColor (10);
	cout << "#AmirHossein SamadiPour\n\n\n";
	SetColor (7);
	int fill=0,x,y,value,size;	
	cout << "Hello. Welcome to my Sudoku Solver Program \n\n";
    
    //defining Sudoko Size (4,9,16)
    cout << "Please enter your Desire Sudoku Size:(4,9,16)\n\n";
    cin >> size;
    while (size!=4 && size!=9 && size!=16 )
    {
    	SetColor (12);
		cout << "\nWrong Size. Enter another one:\n\n";
    	SetColor (7);
		cin >> size;
	}
	
	system("CLS");

	//defining entering method (two ways)
	cout << "Please enter your desire entering method:\n\n" << "1. Entering all Tables\n" << "2. Entering certain Tables\n\n";
	cin >> fill;
	while (fill!=1 && fill!=2)
	{
		SetColor (12);
		cout << "\nWrong Method. Enter Another One:\n\n";
		SetColor (7);
		cin >> fill;
	}

	system("CLS");
	
	//creating Sudoku and Coloring table
	int ** sudoku = new int*[size];
    for(int i = 0; i < size; i++)
    {
        sudoku[i] = new int[size];
    }
	
	int ** color = new int*[size];
    for(int i = 0; i < size; i++)
    {
        color[i] = new int[size];
    }
	
	for (int i=0;i<size;i++)
		for (int j=0;j<size;j++)
			sudoku[i][j]=0;

	//filling SIZExSIZE Sudoku (Entering all Tables)
    if (fill==1)
	{
	cout << "Enter Numbers and hit enter after everyone:\n\n";
    for(int i=0;i<size;i++)
        {
		for(int j=0;j<size;j++)
            {
            cout << "i=" << i+1 << "\tj=" << j+1 << "\tValue=";
			cin >> value;
			while (value>size)
			{
				SetColor (12);
				cout << "\nValue is Wrong. Enter Another One:\n\n";
				SetColor (7);
				cout << "i=" << i+1 << "\tj=" << j+1 << "\tValue=";
				cin >> value;
			}
				sudoku[i][j]=value;
			}
		}
    system ("CLS");
	}
    
    //filling SIZExSIZE Sudoku (Entering certain Tables)
    else if (fill==2)
    {
    	SetColor(10);
		cout << "NOTE1: Enter 0 0 0 to EXIT\n";
		cout << "NOTE2: Example: 1 1 2 (it means i=1 j=1 and value=2)\n";
		cout << "NOTE3: Table Start for 1 to " << size << "\n\n";
    	SetColor(7);
		cout << "Enter i j and it's value:\n";
		while (1)
    	{
			cin >> x >> y >> value;
			if (x==0 && y==0 && value==0)
				{system ("CLS");
				break;}
			if (x>size || y>size || value>size || x==0 || y==0)
			{
				SetColor(12);
				cout << "it's bigger than your matrix size or the value is wrong. enter another one:\n";
				SetColor(7);
			}
			else sudoku[x-1][y-1]=value;
		}
	}

	//filling color table with datas that has been given by user
	for (int i=0;i<size;i++)
		for (int j=0;j<size;j++)
			color[i][j]=sudoku[i][j];
		
	//solving sudoku (in case that it is right)
	if (Check(sudoku,size))
		if (Solve(sudoku,size) == true) Print(sudoku,color,size);
    	else
        	{SetColor(12);
			cout<<"UNSOLVABLE"<<endl;
			SetColor (7);}
	else
        	{SetColor(12);
			cout<<"UNSOLVABLE"<<endl;
			SetColor (7);}

    //pausing program
    cout << endl;
    system("pause");
}
	

bool Solve(int **sudoku, int size)
{
    int row, col;
    if (!EmptyFinder(sudoku, row, col, size))
       return true;
    for (int num = 1; num <= size; num++)
    {
    	if (ProperToUse(sudoku, row, col, num, size))
    	{
    	  	sudoku[row][col] = num;
    	   	if (Solve(sudoku,size))
    	        return true;
    	    sudoku[row][col] = 0;
    	}
    }
    return false;
}


bool EmptyFinder(int **sudoku, int &row, int &col, int size)
{
    for (row = 0; row < size; row++)
        for (col = 0; col < size; col++)
            if (sudoku[row][col] == 0)
                return true;
    return false;
}

bool Check(int **sudoku, int size)
{
	for (int row=0;row<size;row++)
		for (int col=0;col<size;col++)
			if (sudoku[row][col]!=0)
				if (!ProperToUse (sudoku,row,col,sudoku[row][col],size))
					return false;
	return true;
}


bool ProperToUse(int **sudoku, int row, int col, int num, int size)
{
    return !Row(sudoku, row, num, size) && !Col(sudoku, col, num, size) &&
       !Box(sudoku, row - row % (int)sqrt(size) , col - col % (int)sqrt(size), num, size);
}


bool Row(int **sudoku, int row, int num, int size)
{
    for (int col = 0; col < size; col++)
    if (sudoku[row][col] == num)
        return true;
    return false;
}


bool Col(int **sudoku, int col, int num, int size)
{
    for (int row = 0; row < size; row++)
        if (sudoku[row][col] == num)
            return true;
    return false;
}


bool Box(int **sudoku, int SR, int SC, int num, int size)
{
    for (int row = 0; row < sqrt(size); row++)
        for (int col = 0; col < sqrt(size); col++)
            if (sudoku[row+SR][col+SC] == num)
                return true;
    return false;
}


void SetColor(unsigned short color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon,color);
}

void Print(int **sudoku,int **color, int size)
{
    if (size==4)
	{
	cout <<"+-----+-----+"<<endl;
	for (int i=0;i<4;i++){
		cout << "| ";
		for (int j=0;j<4;j++){
			if(color[i][j] != 0) 
              {
                SetColor(12);
                cout << sudoku[i][j] << " ";
                SetColor(7);
              }
              else cout << sudoku[i][j] << " ";
			if (j && j%(2)==1)
				cout <<"| ";
		}
		cout <<endl;
		if (i && i%(2)==1)
			cout <<"+-----+-----+"<<endl;
	}
	}
	
	if (size==9)
	{
	cout <<"+-------+-------+-------+"<<endl;
	for (unsigned i=0;i<9;i++){
		cout << "| ";
		for (unsigned j=0;j<9;j++){
			if(color[i][j] != 0) 
              {
                SetColor(12);
                cout << sudoku[i][j] << " ";
                SetColor(7);
              }
              else cout << sudoku[i][j] << " ";

			if (j && j%(3)==2)
				cout <<"| ";
		}
		cout <<endl;
		if (i && i%(3)==2)
			cout <<"+-------+-------+-------+"<<endl;
	}
	}
	
	if (size==16)
    {
	cout <<"+---------+---------+---------+---------+"<<endl;
	for (unsigned i=0;i<16;i++){
		cout << "| ";
		for (unsigned j=0;j<16;j++){
		 	if(color[i][j] != 0) 
            {
                SetColor(12);
                if (sudoku[i][j]<10) cout <<sudoku[i][j]<<" ";
				switch (sudoku[i][j])
				{
				case 10:cout<<"A"<<" "; break;
				case 11:cout<<"B"<<" "; break;
				case 12:cout<<"C"<<" "; break;
				case 13:cout<<"D"<<" "; break;
				case 14:cout<<"E"<<" "; break;
				case 15:cout<<"F"<<" "; break;
				case 16:cout<<"G"<<" "; break;
				}
            SetColor(7);
            }
            else {
			if (sudoku[i][j]<10) cout <<sudoku[i][j]<<" ";
			switch (sudoku[i][j])
			{
				case 10:cout<<"A"<<" "; break;
				case 11:cout<<"B"<<" "; break;
				case 12:cout<<"C"<<" "; break;
				case 13:cout<<"D"<<" "; break;
				case 14:cout<<"E"<<" "; break;
				case 15:cout<<"F"<<" "; break;
				case 16:cout<<"G"<<" "; break;
			}
			}
			 
			
			if (j && j%(4)==3)
				cout <<"| ";
		}
		cout <<endl;
		if (i && i%(4)==3)
			cout <<"+---------+---------+---------+---------+"<<endl;
	}
	}
}
