//JUEGO DEL GUSANO PARA PODER PROBAR EL CODIGO DEL MAKEY CON ARDUINO LEONARDO


#include <iostream>
#include <conio.h>
#include <windows.h> // Librería utilizada para funciones de sistema específicas de Windows

using namespace std;

bool gameOver; // Variable que indica si el juego ha terminado
const int width = 20; // Ancho del tablero de juego
const int height = 20; // Alto del tablero de juego
int x, y, fruitX, fruitY, score; // Variables para la posición de la serpiente, la fruta y la puntuación
int tailX[100], tailY[100]; // Arrays para almacenar las posiciones de la cola de la serpiente
int nTail; // Longitud de la cola de la serpiente
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; // Enumeración para las direcciones de movimiento
eDirection dir; // Variable para almacenar la dirección actual de la serpiente

const int velocidad = 150; // Velocidad del juego

// Configuración inicial del juego
void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
}

// Dibuja el tablero de juego y la serpiente
void Draw() {
    system("cls"); // Limpia la pantalla
    for (int i = 0; i < width + 2; i++)
        cout << "#"; // Dibuja el borde superior del tablero
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#"; // Dibuja el borde izquierdo del tablero
            if (i == y && j == x)
                cout << "O"; // Dibuja la cabeza de la serpiente
            else if (i == fruitY && j == fruitX)
                cout << "F"; // Dibuja la fruta
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // Dibuja una parte del cuerpo de la serpiente
                        print = true;
                    }
                }
                if (!print)
                    cout << " "; // Espacio vacío si no hay nada que dibujar en esa posición
            }
            if (j == width - 1)
                cout << "#"; // Dibuja el borde derecho del tablero
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#"; // Dibuja el borde inferior del tablero
    cout << endl;
    cout << "Puntuacion:" << score << endl; // Muestra la puntuación
}

// Captura la entrada del jugador
void Input() {
    if (_kbhit()) { // Verifica si se ha presionado una tecla
        switch (_getch()) {
        case 'a':
            dir = LEFT; // Mueve la serpiente hacia la izquierda
            break;
        case 'd':
            dir = RIGHT; // Mueve la serpiente hacia la derecha
            break;
        case 'w':
            dir = UP; // Mueve la serpiente hacia arriba
            break;
        case 's':
            dir = DOWN; // Mueve la serpiente hacia abajo
            break;
        case 'q':
            cout << "LA PAUSA SE QUITARA EN 5 SEGUNDOS" << endl; // Muestra el tiempo de la pausa
            cout << "Vas bien, tu puntaje actual es: " << score << endl; // Muestra el mensaje de puntaje actual
            Sleep(5000); // Espera 5 segundos
            break;
        }
    }
}

// Actualiza la lógica del juego
void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if (x >= width || x < 0 || y >= height || y < 0) { // Si la serpiente toca la pared, pierde una parte de su cola
        if (nTail > 0) {
            nTail--; // Pierde una parte de la cola
            if (nTail == 0) {
                // Si la serpiente ya no tiene ninguna parte de su cuerpo, juego termina
                gameOver = true;
            }
            else {
                // La cabeza de la serpiente se coloca en la posicion anterior de la cola
                x = tailX[0];
                y = tailY[0];
            }
        }
        else {
            // Si la serpiente no tiene cola, juego termina
            gameOver = true;
        }
    }

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y) // Si la serpiente toca su propia cola, juego termina
            gameOver = true;

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

// Muestra el mensaje de fin del juego
void GameOverMessage() {
    cout << "Fin del juego! Tu puntuacion final es: " << score << endl;
}

// Función principal del juego
int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        if (!gameOver) {
            Logic();
            Sleep(velocidad); // Pausa el juego para controlar la velocidad
        }
    }
    GameOverMessage(); // Mostrar mensaje de fin del juego
    return 0;
}
