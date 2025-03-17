#include <iostream>
#include <thread>
#include <chrono>
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

        if (IsWPressed()) {
            pressW = true;
            pressA = false;
            pressS = false;
            pressD = false;
        }

        if (IsAPressed()) {
            pressW = false;
            pressA = true;
            pressS = false;
            pressD = false;
        }
        if (IsSPressed()) {
            pressW = false;
            pressA = false;
            pressS = true;
            pressD = false;
        }
        if (IsDPressed()) {
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
                    tablero[i][j] = ' ';
                }
            }

            tablero[cabezaSerpiente.x][cabezaSerpiente.y] = CABEZA_SERPIENTE;
    }

bool margenes(bool &GameOver, position cabezaSerpiente, char tablero[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {

            if (cabezaSerpiente.x == FILAS -1 || 0 ) {
                GameOver = true;
            }
            else if (cabezaSerpiente.y == COLUMNAS -1 || 0) { 
                GameOver = true;
            }    
        }
    }
        return GameOver;
}

int main() {
    bool pressW = false;
    bool pressA = false;
    bool pressS = false;
    bool pressD = false;
    bool GameOver = false;
    position cabezaSerpiente;

    char tablero[FILAS][COLUMNAS];
    inicializarTablero(tablero, cabezaSerpiente);


    //While game is not over execute game loop
    while (!GameOver) { 

        system("cls");  
        printTablero(tablero);
        movimiento(cabezaSerpiente, tablero, pressW, pressA, pressS, pressD);

        //Sleep main thread to control game speed execution
        std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_RATE));

    }
    
    return 0;
}
