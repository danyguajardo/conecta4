/*
 Daniela Guajardo Ibarra
 A00823050
 
 Proyecto Integrador
 Fundamentos de Programación
 
 
 Este programa simula un juego de conecta 4 en un tablero de 7 por 7. Se juega con dos jugadores, uno representado con la X y otro con la O. Se van alternando turnos hasta que uno gane o se llene el tablero o ellos decidan no seguir jugando. Se puede ganar de manera vertical, horizontal o diagonal
 
 */

#include <iostream>
using namespace std;

// esta función se encarga de validar si el usuario desea seguir jugando. No recibe nada como parametro y regresa un valor de tipo bool, el falso representa que ya no quiere jugar, y el verdadero representa que sí desean continuar.
bool seguirJugando (){
    bool validar = false;
    char jugar;
    
  do {
        cout << "¿Deseas seguir jugando? (s/n)";
        cin >> jugar;
        jugar = tolower(jugar);
    }
    while (jugar != 's'  &&  jugar != 'n');
    
    if (jugar == 's')
        validar = true;
    else if (jugar == 'n'){
        validar = false;
        cout << "El juego ha terminado, nadie ganó" << endl;
    }
    
    return validar;
    
}

// esta función imprime el tablero para que el usuario lo pueda ver. Recibe un arreglo de 7 por 7 como parametro y no regresa nada.
void imprimirTablero(char tablero[7][7]){
    
    for (int num = 0; num < 7; num++)
        cout << num + 1 << " ";
    cout << endl;
    
    for (int r = 0; r < 7; r++){
        for (int c = 0; c < 7; c++){
            cout << tablero [r][c] << " ";
        }
        cout << endl;
    }
    cout << endl;

    
}

// esta función recibe como parametro un arreglo de 7 por 7, que en este caso es el tablero y verifica si algún jugador ha ganado de manera horizontal. Regresa verdadero si el jugador sí ganó.
bool ganadorHorizontal (char tablero [7][7]){
    bool ganador = false;
    for (int row = 0; row < 7; row++){
        for (int col = 0; col < 4; col ++){
            if ( (tablero [row][col] != '-') &&
                (tablero [row][col] == tablero [row][col + 1])  &&
                (tablero [row][col] == tablero [row][col + 2]) &&
                (tablero [row][col] == tablero [row][col + 3]))
                        ganador = true;
        }
    }
    return ganador;
}

// esta función recibe como parametro un arreglo de 7 por 7, que en este caso es el tablero y verifica si algún jugador ha ganado de manera vertical. Regresa verdadero si el jugador sí ganó.
bool ganadorVertical (char tablero [7][7]){
    bool ganador = false;
    for (int row = 0; row < 7; row++){
        for (int col = 0; col < 4; col ++){
            if ( (tablero [row][col] != '-') &&
                (tablero [row][col] == tablero [row + 1][col])  &&
                (tablero [row][col] == tablero [row + 2][col]) &&
                (tablero [row][col] == tablero [row + 3][col]))
                ganador = true;
        }
    }
    return ganador;
}

// esta función recibe como parametro un arreglo de 7 por 7, que en este caso es el tablero y verifica si algún jugador ha ganado con una diagonal hacia la derecha. Regresa verdadero si el jugador sí ganó.
bool ganadorDiagonalDerecha (char tablero [7][7]){
    bool ganador = false;
    for (int row = 0; row < 4; row++){
        for (int col = 0; col < 4; col ++){
            if ( (tablero [row][col] != '-') &&
                (tablero [row][col] == tablero [row + 1][col + 1])  &&
                (tablero [row][col] == tablero [row + 2][col + 2]) &&
                (tablero [row][col] == tablero [row + 3][col + 3]))
                ganador = true;
        }
    }
    return ganador;
}

// esta función recibe como parametro un arreglo de 7 por 7, que en este caso es el tablero y verifica si algún jugador ha ganado con una diagonal hacia la izquierda. Regresa verdadero si el jugador sí ganó.
bool ganadorDiagonalIzquierda (char tablero [7][7]){
    bool ganador = false;
    for (int row = 0; row < 4; row++){
        for (int col = 0; col < 4; col ++){
            if ( (tablero [row][col] != '-') &&
                (tablero [row][col] == tablero [row + 1][col - 1])  &&
                (tablero [row][col] == tablero [row + 2][col - 2]) &&
                (tablero [row][col] == tablero [row + 3][col - 3]))
                ganador = true;
        }
    }
    return ganador;
}

// Esta función recibe como parametro un arreglo y un contador de turnos. La función se encarga de pedirle al usuario la columna en la que quiere insertar la ficha, verificar que esta existe, y modificar el tablero. Esta misma función después llama a imprimeTablero para que el usuario vea los cambios. Cuando los cambios se hacen, también se encarga de alternar los turnos entre participantes. Finalmente llama a las funciones que verifican si algún jugador ha ganado, y si esto no es cierto, verifica si el jugador desea seguir jugando. Claro, siempre manejando el contadorTurnos cómo parametro por referencia porque este tiene que ser utilizado por varias funciones.
void modificarTablero(char tablero [7][7], int &contadorTurnos, int &contadorCasillas){
    int colFicha;
    contadorTurnos ++;
    
    do {
        cout << "¿En qué columna quieres poner la ficha";
        
        if (contadorTurnos % 2 == 1)
            cout << " X?" << endl;
        else if (contadorTurnos % 2 == 0)
            cout << " O?" << endl;
        
        cin >> colFicha;
        
    }
    while (colFicha < 1  ||  colFicha > 7);
   
    colFicha --;
    
    int row = 7;
    
    while (tablero [row][colFicha] != '-' && row > 0)
        row --;
    
    //contadorTurnos ++;

    if (tablero [0][colFicha] != '-')
        tablero [row][colFicha] =  tablero [row][colFicha];
    else if (contadorTurnos % 2 == 1){
        tablero [row][colFicha] = 'X';
        contadorCasillas ++;
        
    }
    else if (contadorTurnos % 2 == 0){
        tablero [row][colFicha] = 'O';
        contadorCasillas ++;
    }
    
    imprimirTablero(tablero);
    if ( ganadorHorizontal(tablero) || ganadorVertical(tablero) ||
         ganadorDiagonalDerecha(tablero) || ganadorDiagonalIzquierda(tablero) ){
        
        if (contadorTurnos % 2 == 1)
            cout << "Felicidades, el jugador X ha ganado" << endl;
        else
            cout << "Felicidades, el jugador O ha ganado" << endl;
    }
    
    else if (contadorCasillas == 49)
        cout << "El juego ha terminado, nadie ganó" << endl;
    
    else if (seguirJugando())
        modificarTablero(tablero, contadorTurnos, contadorCasillas);
    
}

// Esta función crea el estado incial del tablero. Recibe como parametro un arreglo de 7 por 7 todo en blanco y lo llena de '-', para que después pueda ser mostrado al usuario. No regresa nada.
void mostrarTablero(char tablero [7][7]){
    for (int r = 0; r < 7; r++){
        for (int c = 0; c < 7; c++)
                tablero[r][c] =  '-';
    }
    
    imprimirTablero(tablero);
}


int main() {
    
    char tablero [7][7];
    int contadorTurnos = 0;
    int contadorCasillas = 0;
    mostrarTablero(tablero);
    modificarTablero(tablero, contadorTurnos, contadorCasillas);
    
}

