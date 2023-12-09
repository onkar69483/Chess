/*
Chess Game using Linked List
*/
#include <iostream>
#include <Windows.h>
#include "animation.h"
using namespace std; 

struct Node {
    char data;
    Node* right; // Pointer to the next node in the same row
    Node* down;  // Pointer to the next node in the same column

    // Constructor
    Node(int val) : data(val), right(nullptr), down(nullptr) {}
};

class Chess {
public:
    Chess(){}
    Chess(int rows, int cols) : rows_(rows), cols_(cols), head_(nullptr) {
        // Create the 2D linked board with all values initialized to 0
        initBoard();

        // Initialize row labels (12345678)
        for (int row = 0; row <= 8; row++) {
            board(8-row,0,'0'+row);
        }

        // Initialize column labels (abcdefgh)
        for (int col = 0; col < 8; col++) {
            board(8,col+1,'a'+col);
        }
        
        // Initialize pawn positions
        for (int col = 1; col < 9; col++) {
            board(6,col,'P'); // white pawns
            board(1,col,'p'); // black pawns
        }
        
        board(8,0,' ');
        // Initializing pieces
        board(0,1,'r'); // black rooks
        board(0,8,'r');
        board(7,1,'R'); // white rooks
        board(7,8,'R');

        board(0, 2, 'n'); // black knights
        board(0, 7, 'n');
        board(7, 2, 'N'); // white knights
        board(7, 7, 'N');

        board(0, 3, 'b'); // black bishops
        board(0, 6, 'b');
        board(7, 3, 'B'); // white bishops
        board(7, 6, 'B');

        board(0, 4, 'q'); // black queen
        board(7, 4, 'Q'); // white queen

        board(0, 5, 'k'); // black king
        board(7, 5, 'K'); // white king
    }

    // Function to board a value at a specific row and column
    void board(int row, int col, int value) {
        if (row >= 0 && row < rows_ && col >= 0 && col < cols_) {
            Node* newNode = new Node(value);
            Node* current = head_;

            // Traverse to the specified row
            for (int i = 0; i < row; i++) {
                current = current->down;
            }

            // Traverse to the specified column
            for (int j = 0; j < col; j++) {
                current = current->right;
            }

            // Update the value
            current->data = value;
        } else {
            Sleep(1000);
            cout << "Invalid row or column index." << endl;
        }
    }

    // Function to print the 2D linked board
    void display() {
        Node* currentRow = head_;
        for (int i = 0; i < rows_; i++) {
            Node* currentCol = currentRow;
            for (int j = 0; j < cols_; j++) {
            if(currentCol->data>'a' && currentCol->data<'z'){
                changeColour(RED);
            }
            if(currentCol->data>'A' && currentCol->data<'Z' ){
                changeColour(BLUE);
            }
            if(i==8 || j==0){
                changeColour(yellow);
            }
                cout << currentCol->data << " ";
                currentCol = currentCol->right;
                changeColour(WHITE);
            }
            cout << endl;
            currentRow = currentRow->down;
        }
    }

    int board(int row, int col) {
    if (row >= 0 && row < rows_ && col >= 0 && col < cols_) {
        Node* current = head_;

        // Traverse to the specified row
        for (int i = 0; i < row; i++) {
            current = current->down;
        }

        // Traverse to the specified column
        for (int j = 0; j < col; j++) {
            current = current->right;
        }

        // Return the value
        return current->data;
    } else {
        Sleep(1000);
        cout << "Invalid row or column index." << endl;
        return -1; // Return a default value or signal an error
    }
}

    void makeMove(int fromRow, int fromCol, int toRow, int toCol) {
        board(toRow,toCol,board(fromRow,fromCol));
        board(fromRow,fromCol,'#');
    }

    void readMove(const char move[]) {
        int fcol = (move[0] - 'a') + 1;
        int frow = 8 - (move[1] - '0');
        int tcol = (move[6] - 'a') + 1;
        int trow = 8 - (move[7] - '0');
        
        if(move[0] =='q'){
            return;
        }

        if (isValidMove(frow, fcol, trow, tcol)) {
            makeMove(frow, fcol, trow, tcol);
        } else {
            cout << "Invalid move!" << endl;
        }
    }

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol) {
        if (fromRow < 0 || fromRow > 8 || fromCol < 1 || fromCol > 8 ||
            toRow < 1 || toRow > 8 || toCol < 1 || toCol > 8) {
            return false; // Check if coordinates are within bounds
        }

        char piece = board(fromRow,fromCol);
        char targetPiece = board(toRow,toCol);

        if ((piece == 'P' || piece == 'p') && isValidPawnMove(fromRow, fromCol, toRow, toCol)) {
            return true;
        } else if ((piece == 'N' || piece == 'n') && isValidKnightMove(fromRow, fromCol, toRow, toCol)) {
            return true;
        }
        else if((piece == 'R' || piece == 'r') && isValidRookMove(fromRow, fromCol, toRow, toCol)){
            return true;
        }
        else if((piece == 'B' || piece == 'b') && isValidBishopMove(fromRow, fromCol, toRow, toCol)){
            return true;
        }
        // Add cases for other pieces as needed
        // ...

        // Default case: invalid piece or unknown piece
        return false;
    }

    bool isValidPawnMove(int fromRow, int fromCol, int toRow, int toCol) {
        if (board(fromRow,fromCol) == 'P') {
            // White Pawn
            if ((fromRow - toRow) == 1 && fromCol == toCol && board(toRow,toCol) == '#') {
                return true; // Valid one-step forward move
            } else if (fromRow == 6 && (fromRow - toRow) == 2 && fromCol == toCol && board(toRow,toCol) == '#' && board(fromRow-1,fromCol) == '#') {
                return true; // Valid two-step forward move from the starting position
            } else if ((fromRow - toRow) == 1 && abs(fromCol - toCol) == 1 && islower(board(toRow,toCol))) {
                return true; // Valid capture move
            }
        } else if (board(fromRow,fromCol) == 'p') {
            // Black Pawn
            if ((toRow - fromRow) == 1 && fromCol == toCol && board(toRow,toCol) == '#') {
                return true; // Valid one-step forward move
            } else if (fromRow == 1 && (toRow - fromRow) == 2 && fromCol == toCol && board(toRow,toCol) == '#' && board(fromRow+1,fromCol) == '#') {
                return true; // Valid two-step forward move from the starting position
            } else if ((toRow - fromRow) == 1 && abs(toCol - fromCol) == 1 && isupper(board(toRow,toCol))) {
                return true; // Valid capture move
            }
        }

        return false;
    }

    bool isValidKnightMove(int fromRow, int fromCol, int toRow, int toCol){
        int dx = abs(toCol - fromCol);
        int dy = abs(toRow - fromRow);
        if(board(fromRow,fromCol) == 'K'){
            if ((dx == 1 && dy == 2) || (dx == 2 && dy == 1) && board(toRow,toCol) == '#' ) {
             return true;
            }else if((dx == 1 && dy == 2) || (dx == 2 && dy == 1) && islower(board(toRow,toCol))) {
            return true;
            }//these code check that attacking knight is larger(white)
        }
        else if (board(fromRow,fromCol) == 'k'){
            if ((dx == 1 && dy == 2) || (dx == 2 && dy == 1) && board(toRow,toCol) == '#' ) {
             return true;
            }
            else if((dx == 1 && dy == 2) || (dx == 2 && dy == 1) && isupper(board(toRow,toCol))) {
            return true; //these code check that attacking knight is smaller(black)
            }
        }
        return false;
    }
    
    bool isValidRookMove(int fromRow, int fromCol, int toRow, int toCol){
        if(board(fromRow,fromCol) == 'K'){
            if((fromCol == toCol) || (fromRow == toRow) && board(toRow,toCol) == '#'){
                return true;
            }else if((fromCol == toCol) || (fromRow == toRow) && islower(board(toRow,toCol))) {
            return true;  //these code check that attacking knight is larger(white)
            }
        }else if (board(fromRow,fromCol) == 'k'){
            if((fromCol == toCol) || (fromRow == toRow) && board(toRow,toCol) == '#'){
                return true;
            }
            else if((fromCol == toCol) || (fromRow == toRow) && isupper(board(toRow,toCol))) {
            return true; //these code check that attacking knight is smaller(black)
            }
        }
            return false;
    }
    
    bool isValidBishopMove(int fromRow, int fromCol, int toRow, int toCol){
        int dx = abs(toCol - fromCol);
        int dy = abs(toRow - fromRow);
        char piece = board(fromRow,fromCol);
        char targetPiece = board(toRow,toCol);
        if(board(fromRow,fromCol) == 'B'){
            if(((dy == 1) || (dy==2) || (dy==3) || (dy==4) || (dy==5)) && targetPiece != '#' && islower(piece) && isupper(targetPiece)){
            return true;  //these code check that attacking knight is larger(white)
            }
        }else if(board(fromRow,fromCol) == 'b'){
           if(((dy == 1) || (dy==2) || (dy==3) || (dy==4) || (dy==5)) && targetPiece != '#' && islower(targetPiece) && isupper(piece)){
            return true; //these code check that attacking knight is smaller(black)
            }
        }
            return false;
    }

    void resetGame(Chess*& board){
        delete board;
        board = new Chess(9,9);
        cout<<endl<<"Restarting Game!..."<<endl;
        Sleep(2000);
    }
private:
    int rows_;
    int cols_;
    Node* head_;

    // Helper function to create the 2D linked board
    void initBoard() {
        if (rows_ <= 0 || cols_ <= 0) {
            cout << "Invalid dimensions for the 2D linked board." << endl;
            return;
        }

        // Create the first row
        head_ = new Node('#');
        Node* currentRow = head_;

        // Create the first column
        Node* currentCol = head_;

        for (int j = 1; j < cols_; j++) {
            currentCol->right = new Node('#');
            currentCol = currentCol->right;
        }

        // Create the remaining rows
        for (int i = 1; i < rows_; i++) {
            currentRow->down = new Node('#');
            currentRow = currentRow->down;

            // Create the columns for the new row
            currentCol = currentRow;
            for (int j = 1; j < cols_; j++) {
                currentCol->right = new Node('#');
                currentCol = currentCol->right;
            }
        }
    }
};

int main() {
    // Create a 2D linked board with 3 rows and 4 columns
    char move[10]={' '};
    Chess *board = new Chess(9,9);
    Sleep(2000);
    chessAnimation();
    loading();
    cout<<"Game has Started!\n"<<endl;
    while(move[0]!='q'){
        // Display the 2D linked board
        board->display();
        cout << "\nEnter Move: ";
        cin.getline(move, sizeof(move));
        if(move[0]=='r'){
            board->resetGame(board);
        }
        board->readMove(move);
        system("cls");
    }
    quitting();
    return 0;
}
