#include<iostream>
#include<ctime>
#include <cstdlib> // for rand(), srand() 
#include<fstream>   // file management(creates,reads & writes to files)
#include<string>   //for getline() etc.


//**********************************************************
//**********                                    ************
//**********    STUDENT NAME: Ayşem Akşit       ************
//**********    STUDENT NUMBER :      ************
//**********           *            ************
//**********                                    ************
//**********************************************************


struct Coordinate {
    int row;
    int col;
}random_coord;

int N, q, x;
char** board = nullptr;  //to avoid garbage pointer situation


void showMenu();
void createBoardMenu();
void showOutputMenu();

char** createMatrix(int N);           // to create board w type char
void deleteBoard(char** myArray, int N);


void coordinates_of_Queens(char** board,int n);
void coordinates_of_Obstacles(char** board,int N);


void file_management(char** board, int N);    //writes board to input.txt
void reader();    //reads to input.txt


void OneDirection(char** board, bool** reachable, int N, int qRow, int qCol, int rowStep, int colStep);
void findQueenMoves(char** board, bool** reachable, int N, int r, int c);
void totalReachableSquares(bool** reachable, int N);
void reachableCoordinates(bool** reachable, int N);
void printFinalBoard(char** board, bool** reachable, int N);

int choice;
int main() {
    srand(time(NULL));
    do {
        
        showMenu();
        switch (choice) {
        case 1:
            createBoardMenu();
            break;
        case 2:
            showOutputMenu();
            break;
        case 3:
            std::cout << "The program is terminating... " << std::endl;
            break;
        default:
            std::cout << "Invalid selection. Please enter 1, 2, or 3." << std::endl;
        }
    } while (!(choice == 3));

    //  to cleanup before exit
    if (board != nullptr) {
        deleteBoard(board, N);
    }

    return 0;
}

//***********************************************************************
//********************      MENU FUNCTIONS        ***********************
//***********************************************************************

void showMenu() {
    std::cout << "Welcome To Chess Board Configuration Program ! " << std::endl;
    std::cout << "1 : Create board " << std::endl;
    std::cout << "2 : Show Output " << std::endl;
    std::cout << "3 : Exit " << std::endl;
    std::cout << "Enter your choice as a number :) " << std::endl;
    std::cin >> choice;
}

//creating a chess board          
void createBoardMenu() {

    std::cout << "Let's create new chess board! " << std::endl << std::endl;

    // If a board has been created previously,delete it
    if (board != nullptr) {
        deleteBoard(board, N);
        board = nullptr;
    }

    //learned it from here -->https://www.boardinfinity.com/blog/rand-function-in-c/ (title:1. Generating Random Numbers in a Specific Range)

    //for N(board size)                       
    N = rand() % (30 - 5 + 1) + 5;             //rand() % (max - min + 1) + min → including min and max
    // Board Size(N): 5 ≤ 𝑁 ≤ 30

//for q(number of queens)
    int max_q = 2 * N;
    q = rand() % (max_q - 1 + 1) + 1;                    //Number of Queens(q): 1 ≤ 𝑞 ≤ 2 ∗ N

    //for x(number of obstacles)
    int max_intervealofObstacles = N - q;
    x = rand() % (max_intervealofObstacles + 1);            //Number of Obstacles(x): 0 ≤ 𝑥 ≤ 𝑁 − 𝑞

    //create new board
    board = createMatrix(N);
    file_management(board, N);

    std::cout << "The transaction was completed successfully  :)" << std::endl;
}          

void showOutputMenu() {

    reader();

    if (board == nullptr) return;

    std::cout << "Board Size : " << N << "x" << N << std::endl;
    std::cout << "Number of Queens : " << q << std::endl;
    std::cout << "Number of Obstacles : " << x << std::endl;

    // (to be able to follow without damaging the main board) a boolean matrix to track the queen's movements
    bool** reachable = new bool* [N];                   //true → The Queen can come here
    for (int i = 0; i < N; i++) {
        reachable[i] = new bool[N];
        for (int j = 0; j < N; j++)
            reachable[i][j] = false;
    }

    // Finding the queen on the board
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 'Q') {
                findQueenMoves(board, reachable, N, i, j);
            }
        }
    }

    std::cout << "Queen Positions : " << std::endl;
    coordinates_of_Queens(board, N);

    std::cout << "Obstacle Positions : " << std::endl;
    coordinates_of_Obstacles(board, N);


    std::cout << "Total Reachable Squeares : ";
    totalReachableSquares(reachable, N);
    std::cout << std::endl;

    std::cout << "Reachable Points : ";
    reachableCoordinates(reachable, N);


    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "CHESS BOARD" << std::endl;
    std::cout << "Q - Queens " << std::endl;
    std::cout << "X - Obstacles " << std::endl;
    std::cout << "+ - Possible Movemenets " << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    printFinalBoard(board, reachable, N);
    std::cout << std::endl;
    std::cout << "-----------------------------------------" << std::endl;

    // clear memory
    for (int i = 0; i < N; i++)
        delete[] reachable[i];
    delete[] reachable;
}




// create 2D dynamic array((filled with '0', Q and X placed randomly)
char** createMatrix(int N) {
    char** myArray = new char* [N];
    // Initialize elements with 0 (Empty Squares)
    for (int i = 0; i < N; ++i) {
        myArray[i] = new char[N];
        for (int j = 0; j < N; j++)
            myArray[i][j] = '0';
    }
    //random Queen placement
    int placed_Q = 0;        
    while (placed_Q < q) {
        random_coord.row = rand() % N;                    //the struct was used
        random_coord.col = rand() % N;

        if (myArray[random_coord.row][random_coord.col] == '0') {
            myArray[random_coord.row][random_coord.col] = 'Q';
            placed_Q++; //counter
        }
    }

    //random Obstacle placement
    int placed_X = 0;
    while (placed_X < x) {
        random_coord.row = rand() % N;
        random_coord.col = rand() % N;

        if (myArray[random_coord.row][random_coord.col] == '0') {
            if (!(myArray[random_coord.row][random_coord.col] == 'Q')) {
                myArray[random_coord.row][random_coord.col] = 'X';
                placed_X++;
            }
        }
    }
    return myArray;
}

//Free the memory after the use of array
void deleteBoard(char** myArray, int N) {
    if (myArray == nullptr) return;

    for (int i = 0; i < N; i++) {
        delete[] myArray[i];
    }
    delete[] myArray;
}
    

 //******************************************************************
 //**************     CREATE & READ AN INPUT.TXT     ****************
 //******************************************************************

 void file_management(char** board ,int N) {
     std::ofstream saver("input.txt");   //creates and writes 
     if (saver.is_open()) {                             //https://www.youtube.com/watch?v=u-seOESMJA0 (learned in the 12th minute)
         for (int row = 0; row < N; ++row) {
             for (int col = 0; col < N; ++col) {
                 saver << board[row][col];                   //to print
             }
             saver << std::endl;
         }
         saver.close();  //to avoid taking up unnecessary space in memory
     }
     else {
         std::cout << "An error occurred while creating/opening the file :( " << std::endl;
         return;
     }
 }
 
 void reader(){
     std::ifstream file("input.txt");     //reads to the file
     if (!file.is_open()) {
         std::cout << "There is no such file  :(" << std::endl;
         return;
     }
     //**    to find board size(N)  **
         std::string matrix_line;    //A string where each line is temporarily stored
         int findSize=0;

         while (std::getline(file, matrix_line)) {
                 int count = 0;
             for (int i = 0; i < matrix_line.length(); i++) {
                 if (matrix_line[i] == '0' || matrix_line[i] == 'Q' || matrix_line[i] == 'X') {
                     count++;
                 }
             }
             findSize = count;
         }
         file.close();

         if (board != nullptr) {          //to avoid memory leak
             for (int i = 0; i < N; i++)
                 delete[] board[i];
             delete[] board;
             board = nullptr;
         }

         N =findSize ;    // N is the size of board

         //create new board  (To load the board from input.txt into memory)
         board = new char* [N];
         for (int i = 0; i < N; i++)
             board[i] = new char[N];

         // open the file again and fill in the matrix   
         std::ifstream fileAgain("input.txt");
         if (fileAgain.is_open()) {
             int row = 0;
             q = 0;
             x = 0;
             while (std::getline(fileAgain, matrix_line) && (row<N)) {
                 if ((int)matrix_line.length() < N) continue;

                 for (int col = 0; col < N; col++) {
                     char hr = matrix_line[col];      //Because from now on it will be read character by character.
                     board[row][col] = hr;                 //https://www.youtube.com/watch?v=u-seOESMJA0 (learned in the 23th minute)

                     if (hr == 'Q')
                         q++;
                     if (hr == 'X')
                         x++;
                 }
                 row++;
             }

             fileAgain.close();
         }
 }


 //**************************************************************************
//****************       IDENTIFY THE COORDINATES            ****************
//****************   AND FUNCTIONS OF QUEEN MOVEMENT RULES   ****************
//***************************************************************************


 void OneDirection(char** board, bool** reachable,int N, int qRow, int qCol,int rowStep, int colStep)
 {
     int r = qRow + rowStep;
     int c = qCol + colStep;

     while (r >= 0 && r < N && c >= 0 && c < N)
     {
         // to stop if there is an obstacle or another queen
         if (board[r][c] == 'X' || board[r][c] == 'Q')
             break;

         // empty square
         reachable[r][c] = true;

         r =r+ rowStep;
         c =c +colStep;
     }
 }
 

 void findQueenMoves(char** board, bool** reachable, int N, int r, int c)
 {
     OneDirection(board, reachable, N, r, c, 0, 1);
     OneDirection(board, reachable, N, r, c, 0, -1);
     OneDirection(board, reachable, N, r, c, 1, 0);
     OneDirection(board, reachable, N, r, c, -1, 0);
     OneDirection(board, reachable, N, r, c, 1, 1);
     OneDirection(board, reachable, N, r, c, 1, -1);
     OneDirection(board, reachable, N, r, c, -1, 1);
     OneDirection(board, reachable, N, r, c, -1, -1);
 }

 //identify the coordinates of Queens and Obstacles
 void coordinates_of_Queens(char** board, int N) {
     int counter = 0;
     for (int row = 0; row < N; ++row) {
         for (int col = 0; col < N; ++col) {   
             if (board[row][col] == 'Q') {
                 std::cout << " ( " << (row) << " , " << (col) << " ) , ";
                 counter++;
                 if (counter % 10 == 0) std::cout << std::endl; //New line breaks every 10 coordinates (I added this to ensure the program fits on the screen when run)
             }
         }
     }
     std::cout << std::endl;
 }
 void coordinates_of_Obstacles(char** board, int N) {
     int counter = 0;
     for (int i = 0; i < N; ++i) {
         for (int j = 0; j < N; ++j) {
             if (board[i][j] == 'X') {
                 std::cout << " ( " << (i) << " , " << (j) << " ) , ";
                 counter++;
                 if (counter % 10 == 0) std::cout << std::endl; //New line breaks every 10 coordinates
             }
         }
     }
     std::cout << std::endl;

 }



 void totalReachableSquares(bool** reachable, int N) {
     int total = 0; for (int i = 0; i < N; i++) {
         for (int j = 0; j < N; j++) {
             if (reachable[i][j] == true) {
                 total++;
             }
         }
     }
     std::cout << total;
 }

 void reachableCoordinates(bool** reachable, int N) {   //to print reachable coordinates of queens
     int counter = 0;
     for (int i = 0; i < N; i++) {
         for (int j = 0; j < N; j++) {
             if (reachable[i][j] == true) {
                 std::cout << "(" << i << "," << j << ") ";
                 counter++;

                 if (counter % 8 == 0) {
                     std::cout << std::endl;
                 }
             }
         }
         std::cout << std::endl;
     }
 }

 
 void printFinalBoard(char** board, bool** reachable, int N){   //chess board with 'X' , 'Q' , '0' , '+'
     for (int i = 0; i < N; i++) {
         for (int j = 0; j < N; j++) {

             if (board[i][j] == 'Q')
                 std::cout << 'Q';
             else if (board[i][j] == 'X')
                 std::cout << 'X';
             else if (reachable[i][j]==true)
                 std::cout << '+';
             else
                 std::cout << '0';

         }
         std::cout << std::endl;
     }
 }

