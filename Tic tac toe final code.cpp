#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define SIZE 3
#define X -1
#define O 1
#define EMPTY 0

FILE *fp=fopen("tic-tac-toe-log.txt","a");

int board1[SIZE][SIZE]; //board for PvC
char board2[SIZE][SIZE]; //board for PvP

// Function to initialize the board for player vs Computer
void initializeBoardPvC() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board1[i][j] = EMPTY;
        }
    }
}

//Function to initialize the board for player vs player

void initializeBoardPvP() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board2[i][j] = ' ';
        }
    }
}

// Function to print the board for PvC
void showBoard1() {
	system("cls");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board1[i][j] == EMPTY ? ' ' : (board1[i][j] == X ? 'X' : 'O'));
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("-----------\n");
    }
    printf("\n");
}

//Function to show the board for PvP
void showBoard2() {
	system("cls");
    printf("\t\t 1   2   3\n\n");
    for (int i = 0; i < SIZE; i++) {
    	int m=i+1;
    	printf("\t%d\t",m);
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board2[i][j]);
            if (j < SIZE - 1) {
                printf("|");
            }
        }
        printf("\n");
        if (i < SIZE - 1) {
        	printf("\t\t");
            printf("-----------\n");
        }
    }
    printf("\n");
}

//Funciton to print the board to the log for PvP
void printBoard2(){
	for (int i = 0; i < SIZE; i++) {
	for (int j = 0; j < SIZE; j++){
		fprintf(fp," %c ", board2[i][j]);
		if (j < SIZE - 1) {
		    fprintf(fp,"|");
		}
	}
	fprintf(fp,"\n");
	if (i < SIZE - 1) {
	fprintf(fp,"-----------\n");
    }
    }
}

//Funciton to print the board to the log for PvC
void printBoard1(){
	for (int i = 0; i < SIZE; i++) {
	for (int j = 0; j < SIZE; j++){
		fprintf(fp," %c ", board1[i][j] == EMPTY ? ' ' : (board1[i][j] == X ? 'X' : 'O'));
		if (j < SIZE - 1) {
		    fprintf(fp,"|");
		}
	}
	fprintf(fp,"\n");
	if (i < SIZE - 1) {
	fprintf(fp,"-----------\n");
    }
    }
}
//Function to check winner for PvP
int checkWinner() {
    for (int i = 0; i < SIZE; i++) {
        if (board2[i][0] == board2[i][1] && board2[i][1] == board2[i][2] && board2[i][0] != ' ') {
            return board2[i][0] == 'X' ? 1 : 2; // Player 1 or 2 wins
        }
        if (board2[0][i] == board2[1][i] && board2[1][i] == board2[2][i] && board2[0][i] != ' ') {
            return board2[0][i] == 'X' ? 1 : 2; // Player 1 or 2 wins
        }
    }
    if (board2[0][0] == board2[1][1] && board2[1][1] == board2[2][2] && board2[0][0] != ' ') {
        return board2[0][0] == 'X' ? 1 : 2; // Player 1 or 2 wins
    }
    if (board2[0][2] == board2[1][1] && board2[1][1] == board2[2][0] && board2[0][2] != ' ') {
        return board2[0][2] == 'X' ? 1 : 2; // Player 1 or 2 wins
    }
    return 0; // No winner yet
}

// Function to check if the board is full
int isBoardFull() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board1[i][j] == EMPTY) return 0;
        }
    }
    return 1;
}

// Function to check if the current player has won in PvC
int isWin(int player) {
    for (int i = 0; i < SIZE; i++) {
        if (board1[i][0] == player && board1[i][1] == player && board1[i][2] == player) return 1;
        if (board1[0][i] == player && board1[1][i] == player && board1[2][i] == player) return 1;
    }
    if (board1[0][0] == player && board1[1][1] == player && board1[2][2] == player) return 1;
    if (board1[0][2] == player && board1[1][1] == player && board1[2][0] == player) return 1;
    return 0;
}

// Function to evaluate the current state of the board
int evaluateBoard() {
    if (isWin(X)) return -1;
    if (isWin(O)) return 1;
    if (isBoardFull()) return 0;
    return -2; // Game still in progress
}

// Minimax algorithm with alpha-beta pruning
int minimax(int depth, int player, int alpha, int beta) {
    int score = evaluateBoard();

    if (score != -2) return score;

    if (player == O) { // Maximizing player
        int bestScore = -1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board1[i][j] == EMPTY) {
                    board1[i][j] = player;
                    int currentScore = minimax(depth + 1, X, alpha, beta);
                    board1[i][j] = EMPTY;
                    bestScore = (currentScore > bestScore) ? currentScore : bestScore;
                    alpha = (alpha > bestScore) ? alpha : bestScore;
                    if (beta <= alpha) break;
                }
            }
        }
        return bestScore;
    } else { // Minimizing player
        int bestScore = 1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board1[i][j] == EMPTY) {
                    board1[i][j] = player;
                    int currentScore = minimax(depth + 1, O, alpha, beta);
                    board1[i][j] = EMPTY;
                    bestScore = (currentScore < bestScore) ? currentScore : bestScore;
                    beta = (beta < bestScore) ? beta : bestScore;
                    if (beta <= alpha) break;
                }
            }
        }
        return bestScore;
    }
}

// Function to find the best move using Minimax algorithm
void findBestMove() {
    int bestScore = -1000;
    int bestMoveRow = -1;
    int bestMoveCol = -1;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board1[i][j] == EMPTY) {
                board1[i][j] = O;
                int moveScore = minimax(0, X, -1000, 1000);
                board1[i][j] = EMPTY;
                if (moveScore > bestScore) {
                    bestScore = moveScore;
                    bestMoveRow = i;
                    bestMoveCol = j;
                }
            }
        }
    }

    board1[bestMoveRow][bestMoveCol] = O;
}

// Function for the user's move
void userMove() {
    int row, col;
    printf("Player's turn-(X).Enter row and column (1-3): ");
    scanf("%d %d", &row, &col);
    row--;
    col--;
    while (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board1[row][col] != EMPTY) {
        printf("Invalid move.\nPlayer's turn-(X).Enter row and column (1-3): ");
        scanf("%d %d", &row, &col);
        row--;
        col--;
    }
    board1[row][col] = X;
}

void playerVsComputer_Hard(){
	initializeBoardPvC();
	int currentPlayer = 0; // 0 for player, 1 for computer
    int moveCount = 0;
    time_t curtime;
   struct tm *loc_time;
   //Getting current time of system
   curtime = time (NULL);
   // Converting current time to local time
   loc_time = localtime (&curtime);
    showBoard1();
    while (!isWin(X) && !isWin(O) && !isBoardFull()) {
        findBestMove();
        showBoard1();
        if (isWin(O)) {
            printf("Computer wins!\n");
            fprintf(fp,"\nPlayer vs Computer\n");
            fprintf(fp,"\n%s", asctime (loc_time));
            fprintf(fp,"Computer wins!\n");
			fprintf(fp,"Final Board: \n\n");
			printBoard1();            
			break;
        }
        if (isBoardFull()) {
            printf("It's a draw!\n");
            fprintf(fp,"\nPlayer vs Computer\n");
            fprintf(fp,"\n%s", asctime (loc_time));
            fprintf(fp,"Draw!\n");
			fprintf(fp,"Final Board: \n\n");
			printBoard1();  
            break;
        }

        userMove();
        showBoard1();
        if (isWin(X)) {
            printf("Congratulations! You win!\n");
            fprintf(fp,"\nPlayer vs Computer\n");
            fprintf(fp,"\n%s", asctime (loc_time));
            fprintf(fp,"Player wins!\n");
			fprintf(fp,"Final Board: \n\n");
			printBoard1();  
            break;
        }
    }
}

void computerMove() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board2[i][j] == ' ') {
                board2[i][j] = 'O';
                return;
            }
        }
    }
}
void playerVsComputer_Easy(){
	initializeBoardPvP();
	int currentPlayer = 0; // 0 for player, 1 for computer
    int moveCount = 0;
    time_t curtime;
   struct tm *loc_time;
   //Getting current time of system
   curtime = time (NULL);
   // Converting current time to local time
   loc_time = localtime (&curtime);

    while (moveCount <= SIZE * SIZE) {
        showBoard2();
        if (currentPlayer == 0) {
            int row, col;
            printf("Player's turn-(X).Enter row and column (1-3): ");
            scanf("%d %d", &row, &col);
            row--;
            col--;
            if (board2[row][col] == ' ') {
                board2[row][col] = 'X';
                currentPlayer = 1;
                moveCount++;
            } else {
                printf("Invalid move. Try again.\n");
                getch();
            }
        } else {
            computerMove();
            currentPlayer = 0;
            moveCount++;
        }
        int winner = checkWinner();
        if (winner != 0) {
        	fprintf(fp,"\n%s", asctime (loc_time));
            showBoard2();
            if (winner == 1) {
                printf("Player wins!\n");
                fprintf(fp,"Player wins!\n");
            } else if (winner == 2) {
                printf("Computer wins!\n");
                fprintf(fp,"Computer wins!\n");
            }
            getch();
   			fprintf(fp,"Final Board: \n\n");
			printBoard2();
            break;
        }else if (moveCount == SIZE * SIZE) {
    	showBoard2();       	
		printf("It's a draw!\n");
    }
}
}

void playerVsComputer(){
	start:
	system("cls");
	printf("Difficulty Level:\n");
	printf("Easy-1\nHard-2\n");
	int choice;
	printf("Choose Your Difficulty:");
	scanf("%d",&choice);
	if(choice==1){
		playerVsComputer_Easy();
	}else if(choice==2){
		playerVsComputer_Hard();
	}else{
		printf("Invalid Input.\n");
		getch();
		goto start;
	}
}
void playerVsplayer(){
	initializeBoardPvP();
	int currentPlayer = 0; // 0 for player1, 1 for player2
    int moveCount = 0;
    FILE *fp;
    fp=fopen("tic-tac-toe-log.txt","a");
    time_t curtime;
   struct tm *loc_time;
   //Getting current time of system
   curtime = time (NULL);
   // Converting current time to local time
   loc_time = localtime (&curtime);
   char player1[20],player2[20];
   system("cls");
   printf("Enter name for Player 1:");
   scanf("%s",player1);
   printf("Enter name for Player 2:");
   scanf("%s",player2);
   int row, col;

    while (moveCount <= SIZE * SIZE) {
        showBoard2();
        if (currentPlayer == 0) {
            printf("%s's turn-(X).Enter row and column (1-3): ",player1);
            scanf("%d %d", &row, &col);
            row--;
            col--;
            if (board2[row][col] == ' ') {
                board2[row][col] = 'X';
                currentPlayer = 1;
                moveCount++;
            } else {
                printf("Invalid move. Try again.\n");
                getch();
            }
        } else {
            printf("%s's turn-(O).Enter row and column (1-3): ",player2);
            scanf("%d %d", &row, &col);
            row--;
            col--;
            if (board2[row][col] == ' ') {
                board2[row][col] = 'O';
                currentPlayer = 0;
                moveCount++;
            } else {
                printf("Invalid move. Try again.\n");
                getch();
            }
        }
        int winner = checkWinner();
        if (winner != 0) {
        	fprintf(fp,"\n%s", asctime (loc_time));
        	fprintf(fp,"\nPlayer vs Player\n");
            showBoard2();
            if (winner == 1) {
                printf("%s wins!\n",player1);
                fprintf(fp,"%s wins!\n",player1);
            } else if (winner == 2) {
                printf("%s wins!\n",player2);
                fprintf(fp,"%s wins!\n",player2);
            }
            getch();
   			fprintf(fp,"Final Board: \n\n");
			printBoard2();
            break;
        }else if (moveCount == SIZE * SIZE) {
    	showBoard2();       	
		printf("It's a draw!\n");
        getch();
        fprintf(fp,"\n%s", asctime (loc_time));
        fprintf(fp,"\nPlayer vs Player");
   		fprintf(fp,"Final Board: \n\n");
		printBoard2();
	}
    }
    fclose(fp);
};

int main() {
	start:
	system("cls");
	printf("\n\t\t\t\t\t\t\tTic Tac Toe\n\t\t\t\t\t\tGet three in a row to win!!\n");	printf("\n\t\t\t\t\t\tPlay VS. Computer - 1");
    printf("\n\t\t\t\t\t\tPlay VS. Friend - 2\n");
    printf("\n\t\t\t\t\t\tEnter your Choice (1/2):");
    int choice;
    scanf("%d",&choice);
    if(choice==1){
    	playerVsComputer();
	}else if(choice==2){
		playerVsplayer();
	}else{
		printf("\nInvalid Option!!");
		getch();
		goto start;
	}
	fclose(fp);
    return 0;
}
