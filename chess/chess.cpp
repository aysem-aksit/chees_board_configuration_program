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
}random;

int N, q, x;
char** board = nullptr;  //to avoid garbage pointer situation


void showMenu();
void createBoardMenu();
void showOutputMenu();

char** createMatrix(int N);           // char tipiyle tahta oluşturma
void deleteBoard(char** myArray, int N);


void coordinates_of_Queens(char** board,int n);
void coordinates_of_Obstacles(char** board,int N);


void file_management(char** board, int N);    //writes board to input.txt
void reader();    //reads to input.txt
int choice;

int main() {
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

    // cleanup before exit
    /*if (board != nullptr) {
        deleteBoard(board, N);
        board = nullptr;
    }*/


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
        random.row = rand() % N;                    //the struct was used
        random.col = rand() % N;

        if (myArray[random.row][random.col] == '0') {
            myArray[random.row][random.col] = 'Q';
            placed_Q++; //counter
        }
    }
    //random Obstacle placement
    int placed_X = 0;
    while (placed_X < x) {
        random.row = rand() % N;
        random.col = rand() % N;

        if (myArray[random.row][random.col] == '0') {
            if (!(myArray[random.row][random.col] == 'Q')) {
                myArray[random.row][random.col] = 'X';
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


//board oluşturma
void createBoardMenu(){

    std::cout << "Let's create new chess board! " << std::endl;

    // Eğer daha önce bir board oluşturulduysa onu sil
    if (board != nullptr) {
        deleteBoard(board, N);
        board = nullptr;
    }

    //for N(board size)
    N = rand() % (30 - 5 + 1) + 5;             //rand() % (max - min + 1) + min → including min and max
                                                // Board Size(N): 5 ≤ 𝑁 ≤ 30
    //std::cout << "Randomly Selected Board Size (N): " << N << std::endl;
 
    //for q(number of queens)
    int max_q = 2 * N;
    q = rand() % (max_q - 1 + 1) + 1;                    //Number of Queens(q): 1 ≤ 𝑞 ≤ 2 ∗ N

    //for x(number of obstacles)
    int max_intervealofObstacles = N - q;
    x = rand() % (max_intervealofObstacles + 1);            //Number of Obstacles(x): 0 ≤ 𝑥 ≤ 𝑁 − 𝑞

    //yeni board oluştur
    board = createMatrix(N);
    file_management(board,N);

    showMenu();
}
    




//**************************************************************************
//****************       IDENTIFY THE COORDINATES          *****************
//****************     AND FUNCTIONS OF MOVEMENT RULES     *****************
//**************************************************************************


//identify the coordinates of Queens
void coordinates_of_Queens(char** board,int N) {
    for(int row=0;row<N;++row){
        for (int col = 0; col < N; ++col) {   //if else ekle , icin
            if (board[row][col] == 'Q') {
                std::cout << " ( " << (row) << " , " << (col) << " ) , ";// , işini düzenle
            }
        }
    }
}
void coordinates_of_Obstacles(char** board,int N) {
    for(int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j] == 'X') {
                std::cout << " ( " << (i) << " , " << (j) << " ) , ";// , işini düzenle
            }
        }
    }
}

    
 void showOutputMenu() {

     reader();
     std::cout << "Board Size : " << N << std::endl;
     std::cout << "Number of Queens : " << q << std::endl;
     std::cout << "Number of Obstacles : " << x << std::endl;

     std::cout << "Queen Positions : " << std::endl;
     coordinates_of_Queens(board, N);
     std::cout << std::endl;
     std::cout << "Obstacle Positions : " << std::endl;
     coordinates_of_Obstacles(board, N);
     std::cout<< std::endl;
     std::cout << "Total Reachable Squeares : " << std::endl;                //EKLE
     std::cout << "Reachable Points : " << std::endl;                         //EKLE

     std::cout << "-----------------------------------------" << std::endl;
     std::cout << "CHESS BOARD" << std::endl;
     std::cout << "Q - Queens " << std::endl;
     std::cout << "X - Obstacles " << std::endl;
     std::cout << "-----------------------------------------" << std::endl;

     //     DOSYA OKUMA KODU VE ULAŞABİLECEĞİ YERE + YAZMA
     std::cout << "-----------------------------------------" << std::endl;
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
     std::ifstream file("input.txt");     //reads

     //******************     to find size       *******************
     if (file.is_open()) {
         int findSıze=0;
         std::string matrix;    //A string where each line is temporarily stored
         while (std::getline(file, matrix)) {
             if (matrix != "")
                 findSıze++;
         }
         file.close();

         N = findSıze;    // N is the size of board

         if (board != nullptr) {          //to avoid memory leak
             for (int i = 0; i < N; i++)
                 delete[] board[i];
             delete[] board;
         }
         //create new board
         board = new char* [N];
         for (int i = 0; i < N; i++)
             board[i] = new char[N];

         // *****  open the file again and fill in the matrix    *****     
         file.open("input.txt");

         int row = 0;
         int q= 0;
         int x = 0;
         while (std::getline(file, matrix)) {
             for (int col = 0; col < N; col++) {
                 char hr = matrix[col];
                 hr = board[row][col];

                 if (hr == 'Q')
                     q++;
                 if (hr == 'X') 
                     x++;
             }
             row++;
         }
        
         file.close();

     }
     else {
         std::cout << "There is no such file " << "\n";
     }
 }




