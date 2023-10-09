#include <iostream>
#include <windows.h>

using namespace std;

const int BLUE = 1;
const int GREEN = 2;
const int RED = 4;
const int WHITE = 15;
const int yellow = RED|GREEN;
const int purple = BLUE|RED;

void changeColour(int colour) {
	HANDLE hConsole;
	
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colour);
}

void loading(){
    int totalFrames = 20; // Total number of animation frames

    for (int frame = 0; frame < totalFrames; frame++) {
        // Clear the screen
        system("cls");

        // Display the loading animation
        std::cout << "Loading: [";
        for (int i = 0; i < frame; i++) {
            if(i<7) changeColour(RED);
            if(i>=7&&i<14) changeColour(BLUE);
            if(i>=14&&i<20) changeColour(GREEN);
            std::cout << "=";
        }
        for (int i = frame; i < totalFrames - 1; i++) {
            std::cout << " ";
        }
        changeColour(WHITE);
        std::cout << "] " << (frame + 1) * 5 << "%";

        // Sleep for a short duration to control the animation speed
        Sleep(50); // Adjust the sleep duration for the desired speed
    }

    // Print a message when the loading is complete
    system("cls");
    std::cout << "Loading complete!" << std::endl;
    Sleep(500);
    system("cls");
}

void quitting(){
    int animationDuration = 2; // Number of seconds for the animation
    int frameDuration = 200;   // Duration of each frame in milliseconds
    int framesPerSecond = 1000 / frameDuration;
    int totalFrames = animationDuration * framesPerSecond;

    for (int frame = 0; frame < totalFrames; frame++) {
        system("cls"); // Clear the screen

        if(frame%2==0){
            changeColour(purple);
        }
        if(frame%2!=0){
            changeColour(RED);
        }

        // Display a funny quitting message
        std::cout << "Quitting in progress";
        for (int i = 0; i < frame % 5; i++) {
            std::cout << ".";
        }

        // Add some built-in funny characters
        if (frame % 2 == 0) {
            std::cout << "  (^_^)";
        } else {
            std::cout << "  (-_-)";
        }

        // Sleep for the frame duration
        Sleep(frameDuration);
    }

    // Print a humorous final message
    system("cls");
    changeColour(WHITE);
    std::cout << "Goodbye, and remember to have a laugh! (^_^)" << std::endl;
    Sleep(1000);
}

void clearScreen() {
    system("cls");
}

void delay(int milliseconds) {
    Sleep(milliseconds);
}


void chessAnimation() {
    int animationDuration = 2; // Number of seconds for the animation
    int frameDuration = 200;   // Duration of each frame in milliseconds
    int framesPerSecond = 1000 / frameDuration;
    int totalFrames = animationDuration * framesPerSecond;

    for (int frame = 0; frame < totalFrames; frame++) {
        system("cls"); // Clear the screen
        if(frame%2==0){
            changeColour(purple);
        }
        if(frame%2!=0){
            changeColour(RED);
        }
        if (frame % 2 == 0) {
            std::cout << "(x_x)         (+_+) ";
        }
        else{
            std::cout << "(-_-)         (-_-) ";
        }

        std::cout << "\n{Classic C H E S S}";
        for (int i = 0; i < frame % 5; i++) {
            std::cout << ".";
        }
        changeColour(WHITE);
        // Sleep for the frame duration
        Sleep(frameDuration);
    }

    // Print a humorous final message
    system("cls");
    std::cout << "Enjoy your game! (^_^)" << std::endl;
    Sleep(500);
}


    

