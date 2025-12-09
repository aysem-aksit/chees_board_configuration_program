#include<iostream>
#include<ctime>
#include <cstdlib> // for rand(), srand() için

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
}position;

int N, q, x;
char** board = nullptr;  //to avoid garbage pointer situation


void showMenu();
void createBoardMenu();
void showOutputMenu();

char** createMatrix(int N);           // char tipiyle tahta oluşturma
void deleteBoard(char** myArray, int N);


int coordinates_of_Queens(char** board,int n);
int coordinates_of_Obstacles(char** board,int N);
//void  identify_coordinates();




int choice;

int main() {
    srand(time(NULL));
    do {
        
        showMenu();
        /* if (!(std::cin >> choice))          //if user's input not invalid
             std::cout << "ERROR! Please enter numbers only.  ";
         while
         continue;     //loop returned to the beginning to try again     */

         //when user's input is valid
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


// create 2D dynamic array
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
        int random_row = rand() % N;
        int random_column = rand() % N;

        if (myArray[random_row][random_column] == '0') {
            myArray[random_row][random_column] = 'Q';
            placed_Q++; //counter
        }
    }

    //random Obstacle placement
    int placed_X = 0;
    while (placed_X < x) {
        int random_row = rand() % N;
        int random_column = rand() % N;

        if (myArray[random_row][random_column] == '0') {
            if (!(myArray[random_row][random_column] == 'Q')) {
                myArray[random_row][random_column] = 'X';
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
    std::cout << "Randomly Selected Board Size (N): " << N << std::endl;

    //for q(number of queens)
    int max_q = 2 * N;
    q = rand() % (max_q - 1 + 1) + 1;                    //Number of Queens(q): 1 ≤ 𝑞 ≤ 2 ∗ N
    std::cout << "The number of queen(s): " << q << std::endl;

    //for x(number of obstacles)
    int max_intervealofObstacles = N - q;
    x = rand() % (max_intervealofObstacles + 1);            //Number of Obstacles(x): 0 ≤ 𝑥 ≤ 𝑁 − 𝑞
    std::cout << "Randomly Selected Obstacle Number: " << x << std::endl;

    //yeni board oluştur
    board = createMatrix(N);
    // EKRANA MATRİSİ YAZDIR
    for (int i = 0; i < N; i++) {
        std::cout << "| ";
        for (int j = 0; j < N; j++) {
            std::cout << board[i][j] << ' ';
        }
        std::cout << "|\n";
    }
    std::cout << std::endl;

    showOutputMenu();
}
    




//**************************************************************************
//****************       IDENTIFY THE COORDINATES          *****************
//****************     AND FUNCTIONS OF MOVEMENT RULES     *****************
//**************************************************************************

int coordinates_of_Queens(char** board,int N) {
    int counter_Q = 0;
    for(int i=0;i<N;++i){
        for (int j = 0; j < N; ++j) {
            if (board[i][j] == 'Q') {
                std::cout << " ( " << i << " , " << j << " ) , ";// , işini düzenle
                counter_Q++;
            }
        }
    }
    return counter_Q;
}
int coordinates_of_Obstacles(char** board,int N) {
    int counter_X = 0;
    for(int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j] == 'X') {
                std::cout << " ( " << i << " , " << j << " ) , ";// , işini düzenle
                counter_X++;
            }
        }
    }
    return counter_X;
}

//identify the coordinates of Queens
//void  identify_coordinates(char** board, int N) {}
    

 void showOutputMenu() {
     std::cout << "Board Size : " << N << std::endl;
     std::cout << "Number of Queens : " << q << std::endl;
     std::cout << "Number of Obstacles : " << x << std::endl<<std::endl;
     std::cout << "Queen Positions : " <<coordinates_of_Queens(board,N)<< std::endl<<std::endl;                        
     std::cout << "Obstacle Positions : "<<coordinates_of_Obstacles(board,N)<<std::endl;                          
     std::cout << "Total Reachable Squeares : " << std::endl;                //EKLE
     std::cout << "Reachable Points : " << std::endl;                         //EKLE

     std::cout << "-----------------------------------------" << std::endl;
     std::cout << "CHESS BOARD" << std::endl;
     std::cout << "Q - Queens " << std::endl;
     std::cout << "X - Obstacles " << std::endl;

 }
