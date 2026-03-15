#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define HEIGHT 20
#define WIDTH 40

int snakeTailX[100], snakeTailY[100];
int snakeTailLen;
int gameover, key, score;
int x, y, fruitx, fruity;

// Function to move cursor to (0,0) to prevent flickering
void goToXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setup() {
    srand(time(NULL));
    gameover = 0;
    score = 0;
    snakeTailLen = 0;
    
    // Initial snake position
    x = WIDTH / 2;
    y = HEIGHT / 2;
    
    // Initial direction (0 = stopped)
    key = 0; 

    // Initial fruit position
    fruitx = rand() % (WIDTH - 2) + 1;
    fruity = rand() % (HEIGHT - 2) + 1;
}

void draw() {
    goToXY(0, 0); // Reset cursor instead of system("cls")

    for (int i = 0; i < WIDTH + 2; i++) printf("-");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j <= WIDTH; j++) {
            if (j == 0 || j == WIDTH) {
                printf("#");
            }
            if (i == y && j == x) {
                printf("O"); // Head
            } else if (i == fruity && j == fruitx) {
                printf("*"); // Fruit
            } else {
                int prTail = 0;
                for (int k = 0; k < snakeTailLen; k++) {
                    if (snakeTailX[k] == j && snakeTailY[k] == i) {
                        printf("o"); // Body
                        prTail = 1;
                        break;
                    }
                }
                if (!prTail) printf(" ");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) printf("-");
    printf("\nScore: %d\n", score);
    printf("Controls: W, A, S, D | X to Quit\n");
}

void input() {
    if (_kbhit()) {
        switch (tolower(_getch())) {
            case 'a': if(key != 2) key = 1; break;
            case 'd': if(key != 1) key = 2; break;
            case 'w': if(key != 4) key = 3; break;
            case 's': if(key != 3) key = 4; break;
            case 'x': gameover = 1; break;
        }
    }
}

void logic() {
    // 1. Logic for tail following
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;
    snakeTailX[0] = x;
    snakeTailY[0] = y;

    for (int i = 1; i < snakeTailLen; i++) {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // 2. Direction movement
    switch (key) {
        case 1: x--; break;
        case 2: x++; break;
        case 3: y--; break;
        case 4: y++; break;
    }

    // 3. Wall Collision
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        gameover = 1;

    // 4. Tail Collision
    for (int i = 0; i < snakeTailLen; i++) {
        if (snakeTailX[i] == x && snakeTailY[i] == y)
            gameover = 1;
    }

    // 5. Eating Fruit
    if (x == fruitx && y == fruity) {
        score += 10;
        snakeTailLen++;
        fruitx = rand() % (WIDTH - 2) + 1;
        fruity = rand() % (HEIGHT - 2) + 1;
    }
}

int main() {
    // Clear screen once at the start
    system("cls");
    setup();

    while (!gameover) {
        draw();
        input();
        logic();
        Sleep(40); // Controls game speed
    }
    
    _getch(); // Wait for user input before closing window
    return 0;
}