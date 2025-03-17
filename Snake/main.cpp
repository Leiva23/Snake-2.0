
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

    tablero[cabezaPos.x][cabezaPos.y] = 'X';
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


void movimiento(position &cabezaSerpiente, char tablero[FILAS][COLUMNAS]) {
        for (int i = 0; i < FILAS; i++) {
            for (int j = 0; j < COLUMNAS; j++) {
                tablero[i][j] = ' ';
            }
        }

        if (IsWPressed()) cabezaSerpiente.x--;
        else if (IsAPressed()) cabezaSerpiente.y--;
        else if (IsSPressed()) cabezaSerpiente.x++;
        else if (IsDPressed()) cabezaSerpiente.y++;

        tablero[cabezaSerpiente.x][cabezaSerpiente.y] = 'X';
    }

bool margenes(bool &GameOver, position cabezaSerpiente, char tablero[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {

            if (cabezaSerpiente.x < tablero[0][j] ) {
                GameOver = false;
            }
            else if (cabezaSerpiente.y < tablero[i][0]) {
                GameOver = false;
            }    
        }
    }
        return GameOver;
}

int main() {

    bool GameOver = false;
    position cabezaSerpiente;

    char tablero[FILAS][COLUMNAS];
    inicializarTablero(tablero, cabezaSerpiente);


    //While game is not over execute game loop
    while (!GameOver) { 

        system("cls");  
        printTablero(tablero);
        movimiento(cabezaSerpiente, tablero);
        margenes(GameOver, cabezaSerpiente, tablero);
        //Sleep main thread to control game speed execution
        std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_RATE));

    }
    
    return 0;
}
