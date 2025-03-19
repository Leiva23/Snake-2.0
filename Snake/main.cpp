#include <iostream>
#include <thread>
#include <chrono>
#include <time.h>
#include <vector>
#include "const.h"
#include "keyboard.h"
using namespace std;


struct position {
    int x;
    int y;

};

void inicializarTablero(char tablero[FILAS][COLUMNAS], position &cabezaPos) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            tablero[i][j] = ' ';
        }
    }

    cabezaPos.x = FILAS / 2;
    cabezaPos.y = COLUMNAS / 2;

    tablero[cabezaPos.x][cabezaPos.y] = CABEZA_SERPIENTE;
}
void printTablero(char tablero[FILAS][COLUMNAS]) {

    for (int i = 0; i < COLUMNAS + 2; i++) {
        cout << LIN_VERT;
    }
    cout << endl;

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {

            if (j == 0) {
                cout << LIN_HOR; 
            }
            cout << tablero[i][j];

            if (j == COLUMNAS - 1) {
                 cout << LIN_HOR; 
            }
        }
        cout << endl;
    }

    for (int i = 0; i < COLUMNAS + 2; i++) {
        cout << LIN_VERT;
    }
    cout << endl;
}


void movimiento(position &cabezaSerpiente, char tablero[FILAS][COLUMNAS], bool &pressW, bool &pressA, bool &pressS, bool &pressD) {

        if (IsWPressed() && !pressS) {
            pressW = true;
            pressA = false;
            pressS = false;
            pressD = false;
        }

        if (IsAPressed() && !pressD) {
            pressW = false;
            pressA = true;
            pressS = false;
            pressD = false;
        }
        if (IsSPressed() && !pressW) {
            pressW = false;
            pressA = false;
            pressS = true;
            pressD = false;
        }
        if (IsDPressed() && !pressA) {
            pressW = false;
            pressA = false;
            pressS = false;
            pressD = true;
        }

        if (pressW){
            cabezaSerpiente.x--;
        }
        if (pressA){
            cabezaSerpiente.y--;
        }
        if (pressS){
            cabezaSerpiente.x++;
        }
        if (pressD){
            cabezaSerpiente.y++;
        }
    
        for (int i = 0; i < FILAS; i++) {
            for (int j = 0; j < COLUMNAS; j++) {

                if (tablero[i][j] == MANZANA) {
                    cout << tablero[i][j];
                }
                else {
                    tablero[i][j] = ' ';
                }
            }
        }
    }

bool margenes( position cabezaSerpiente) {

            if (cabezaSerpiente.x < 0) {
                return true;
            }
            
            else if (cabezaSerpiente.y < 0) { 
                return true;
            }    
            
            else if (cabezaSerpiente.x >= FILAS) {
                return true;
            }
            else if (cabezaSerpiente.y >= COLUMNAS) { 
                return true;
            }
        
    
        return false;
}

void generarManzana(position &manzanaRand, char tablero[FILAS][COLUMNAS]) { 
    bool manzana = false;
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {

            if (tablero[i][j] == MANZANA) {
                cout << tablero[i][j];
                manzana = true;
            }
        }
    }
            if (!manzana) {        
                manzanaRand.x = rand() % 20;
                manzanaRand.y = rand() % 10;

                tablero[manzanaRand.x][manzanaRand.y] = MANZANA;
            }
}

void cuerpoSerpiente(position cabezaSerpiente, position manzana, char tablero[FILAS][COLUMNAS]) {
    vector <char> cuerpoSerpiente;
    if (cabezaSerpiente.x == manzana.x && cabezaSerpiente.y == manzana.y) {

        cuerpoSerpiente.push_back(CUERPO_SERPIENTE);
        tablero[cabezaSerpiente.x][cabezaSerpiente.y] = CUERPO_SERPIENTE;

    }

}

int main() {
    srand(time(NULL));

    bool pressW = false;
    bool pressA = false;
    bool pressS = false;
    bool pressD = false;
    bool GameOver = false;
    position cabezaSerpiente;
    position manzana;
    char tablero[FILAS][COLUMNAS];
    inicializarTablero(tablero, cabezaSerpiente);


    //While game is not over execute game loop
    while (!GameOver) { 

        system("cls");  
        printTablero(tablero);
        generarManzana(manzana, tablero);
        movimiento(cabezaSerpiente, tablero, pressW, pressA, pressS, pressD);
        
        GameOver = margenes(cabezaSerpiente);

        if (!GameOver) tablero[cabezaSerpiente.x][cabezaSerpiente.y] = CABEZA_SERPIENTE;
       
        cuerpoSerpiente(cabezaSerpiente, manzana, tablero);
    
        //Sleep main thread to control game speed execution
        std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_RATE));

    }
    
    return 0;
}
