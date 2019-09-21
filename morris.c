#include<stdio.h>
#include<stdlib.h>
#include "util.h"
#include <string.h>
#include <ctype.h>

struct Game {
    int currentPlayer;
    char** occupiedBoard;
    char p1type;
    char p2type;
    char winner;
    int p1tokens; 
    int p2tokens;
    char p1colour;
    char p2colour;
};

typedef struct Game Game;

/**
*   Function for outputting the winner of the game
*
*
*/
void handle_winner(Game* g, int argc, char** argv) {
    //0 -> Player 1, 1 -> Player 2
    if(g->p1tokens > g->p2tokens) {
        g->winner = 'W';
    } else {
        g->winner = 'B';
    }

    printf("Winner is Player %c\n", g->winner);
    fflush(stdout);
}

/**
*   Function for checking if the game is over
*
*
*/
int game_is_over(Game* g) {
    //Player has less than 3 tokens
    if(g->p1tokens < 3 || g->p2tokens < 3){
        return 1;
    }
    return 0;
}

/**
*   Function for printing the current state of the board
*
*
*/
void print_board(Game* g){
    //Top line
    printf("%c", g->occupiedBoard[0][0]);
    printf("---------------");
    printf("%c", g->occupiedBoard[1][0]);
    printf("---------------");
    printf("%c\n", g->occupiedBoard[2][0]);
    printf("|\t\t|\t\t|\n");
    printf("|\t%c-------%c-------%c\t|\n", g->occupiedBoard[0][1], g->occupiedBoard[1][1], g->occupiedBoard[2][1]);
    printf("|\t|\t|\t|\t|\n"); 
    fflush(stdout);
    printf("|\t|     %c %c %c     |\t|\n", g->occupiedBoard[0][2], g->occupiedBoard[1][2], g->occupiedBoard[2][2]);
    printf("%c-------%c-----%c   %c-----%c-------%c\n", g->occupiedBoard[7][0], g->occupiedBoard[7][1], 
    g->occupiedBoard[7][2], g->occupiedBoard[3][2], g->occupiedBoard[3][1], g->occupiedBoard[3][0]);
    printf("|\t|     %c %c %c     |\t|\n", g->occupiedBoard[6][2], g->occupiedBoard[5][2], g->occupiedBoard[4][2]);
    fflush(stdout);
    printf("|\t|\t|\t|\t|\n");
    printf("|\t%c-------%c-------%c\t|\n", g->occupiedBoard[6][1], g->occupiedBoard[5][1], g->occupiedBoard[4][1]);
    printf("|\t\t|\t\t|\n");
    printf("|\t\t|\t\t|\n");
    printf("%c", g->occupiedBoard[6][0]);
    printf("---------------");
    printf("%c", g->occupiedBoard[5][0]);
    printf("---------------");
    printf("%c\n", g->occupiedBoard[4][0]);
    printf("\n");
    fflush(stdout);
}

/**
*   Function for checking if a valid move is correct
*
*
*/
int validate_move(Game* g, char* move){
    if(!strstr(move, "to")){
        return 0;
    }

    char buffer[80];
    char firstMoveLetter, secondMoveLetter, firstMoveDigit, secondMoveDigit;
    strcpy(buffer, move);
    
    if(sscanf(buffer, "%c%cto%c%c", &firstMoveLetter, &firstMoveDigit, 
    &secondMoveLetter, &secondMoveDigit) != 4){
        printf("Error with args");
        return 0;
    }
    
    if(!isalpha(firstMoveLetter) && !isdigit(firstMoveDigit) ){
        printf("Wrong word and number");
        return 0;
    }   
    
    if(!isalpha(secondMoveLetter) && !isdigit(secondMoveDigit)){
        printf("Wrong word and number");
        return 0;
    }

    firstMoveLetter -= 17;
    int firstRow =  firstMoveLetter -'0';
    int firstColumn = firstMoveDigit -'0';

    secondMoveLetter -= 17;
    int secondRow = secondMoveLetter - '0';
    int secondColumn = secondMoveDigit - '0'; 

    if(g->currentPlayer == 0 && g->occupiedBoard[firstRow][firstColumn] != 'W') {
        printf("Colour W");
        return 0;
    }

    if(g->currentPlayer == 1 && g->occupiedBoard[firstRow][firstColumn] != 'B') {
        printf("Colour B");
        return 0;
    }

    if(g->occupiedBoard[secondRow][secondColumn] != 'O') {
        printf("no blank space");
        return 0;
    }

    return 1;
}

/**
*   Function for checking if a valid token can be removed
*
*
*/
int validate_removal(Game* g, char* move){
    char rowChar = move[0] - 17;
    int row =  rowChar -'0';
    int column = move[1] -'0';  

    if((g->occupiedBoard[row][column] == 'B' && g->currentPlayer != 0) ||
        (g->occupiedBoard[row][column] == 'W' && g->currentPlayer != 1)) {
        return 0;
    }

    if((g->occupiedBoard[row][column] == 'O')){
        return 0;
    }

    return 1;
}

/**
*   Function for updating the placement of tokens on the board 
*
*
*/
void update_placement_board(Game* g, char letter, char digit, char player) {
    //Change ascii value to a number ('A' - > 0)
    letter -= 17;
    int row =  letter -'0';
    int column = digit -'0';
    //Update location
    g->occupiedBoard[row][column] = player;
}

/**
*   Function for updating the board during gameplay
*
*
*/
void update_board(Game* g, char* move){
    char buffer[80];
    char firstMoveLetter, secondMoveLetter, firstMoveDigit, secondMoveDigit;
    strcpy(buffer, move);
    
    sscanf(buffer, "%c%cto%c%c", &firstMoveLetter, &firstMoveDigit, 
    &secondMoveLetter, &secondMoveDigit);
    
    firstMoveLetter -= 17;
    int firstRow =  firstMoveLetter -'0';
    int firstColumn = firstMoveDigit -'0';

    secondMoveLetter -= 17;
    int row =  secondMoveLetter -'0';
    int column = secondMoveDigit -'0';
    
    g->occupiedBoard[firstRow][firstColumn] = 'O';

    if(g->currentPlayer == 0) {
        g->occupiedBoard[row][column] = 'W';
    } else {
        g->occupiedBoard[row][column] = 'B';
    }
}

/**
*   Function for checking if the current player is human
*
*
*/
int current_player_human(Game* g) {
    if((g->currentPlayer == 0 && g->p1type == 'h') ||
        (g->currentPlayer == 1 && g->p2type == 'h')){
        return 1;
    } else {
        return 0;
    }
} 

/**
*   Function for getting automatic player moves
*
*
*/
void get_automatic_move(Game* g, int argc, char** argv) {
}

/**
*   Function for checking if the board location is available
*
*
*/
int board_location_available(Game* g, char* move){
    //Convert player coordinates to memory address locations
    char letter = move[0];
    char digit = move[1];
    letter -= 17;
    int row =  letter -'0';
    int column = digit -'0';

    if(g->occupiedBoard[row][column] != 'O'){
        printf("Try a different location\n");
        return 0;
    }
    return 1;
}

/**
*   Function for checking if a token location is valid
*
*
*/
int validate_token_location(Game* g, char* move){
    //Check 0th element a letter, 1st a number 
    if(!isalpha(move[0]) && !isdigit(move[1]) && move[2] != '\0'){
        return 0;
    }
    //Between A-G
    if(move[0] < 65 && move[0] > 72) {
        return 0;
    }
    //Between 0 and 2
    if(((move[1] - '0') > 2) || ((move[1] - '0') < 0)) {
        return 0;
    }
    //Check available board position
    if(!board_location_available(g, move)){
        return 0;
    }
    //Successful move
    return 1;
}

/**
*   Function for incrementing the player number
*
*
*/
void increment_player(Game* g) {
    g->currentPlayer++;
    g->currentPlayer %= 2;
}

/**
*   Function for prompting the player
*
*
*/
void prompt_player(Game* g){
    if(g->currentPlayer == 0){
        printf("Player W Move=> ");
        fflush(stdout);
    } else {
        printf("Player B Move=> ");
        fflush(stdout);        
    }

}

/**
*   Function for detecting three in a row
*
*
*/
int detect_three_in_a_row(Game* g){
    //Detect vertical line
    for(int i = 0; i < 5; i++) {
        if(g->occupiedBoard[i][0] == g->occupiedBoard[i+1][0] &&
        g->occupiedBoard[i][0] == g->occupiedBoard[i+2][0] &&
        (g->occupiedBoard[i][0] == 'W' || g->occupiedBoard[i][0] == 'B')) {
            printf("Horizontal detected");
            return 1;
        }
    }
    
    //Detect vertical line
    for(int j = 0; j < 3; j++){
        for(int k = 0; k < 8; k++) {
            if(g->occupiedBoard[j][k%8] == g->occupiedBoard[j][(k+1)%8] &&
            g->occupiedBoard[j][k] == g->occupiedBoard[j][(k+2)%8] &&
            (g->occupiedBoard[j][k%8] == 'W' || g->occupiedBoard[k%8][0] == 'B')) {
                printf("Vertical detected");
                return 1;
            }
        }
    }

    return 0;
}

/**
*   Function for prompting which piece to remove when there is 3 in a row
*
*
*/
void prompt_piece(Game* g){
    if(g->currentPlayer == 0){
        printf("Choose a B token to remove => ");
    } else {
        printf("Choose a W token to remove => ");
    }
}

/**
*   Function for decrementing the player tokens
*
*
*/
void decrement_player_tokens(Game* g) {
    if(g->currentPlayer == 0){
        g->p2tokens--;
    } else {
        g->p1tokens--;
    }
}

/**
*   Function for removing a piece from a board
*
*
*/
void remove_piece(Game* g, char* piece){
    char rowChar = piece[0] - 17;
    int row =  rowChar -'0';
    int column = piece[1] -'0';

    g->occupiedBoard[row][column] = 'O';     
}

/**
*   Function for selecting which piece should be removed
*
*
*/
void select_players_piece_to_remove(Game* g) {
    prompt_piece(g);
    char buffer[80];
    fgets(buffer, sizeof(buffer), stdin);
    if(validate_removal(g, buffer)){
        remove_piece(g, buffer);
    } else {
        while(1){
            prompt_piece(g);
            fgets(buffer, sizeof(buffer), stdin);
            if(validate_removal(g, buffer)){
                remove_piece(g, buffer); 
            }
        }
    }
}

/**
*   Function for writing a game to a save file
*
*
*/
void write_save_file(Game* g, char* path){
    path[strlen(path)-1] = '\0';
    FILE* newSaveFile = fopen(path, "w");
    fprintf(newSaveFile, "%d %d %d %c %c\n", g->currentPlayer, g->p1tokens, 
    g->p2tokens, g->p1type, g->p2type);
    for(int i =0; i< 8; i++){
        for(int j =0; j<3; j++){
            fprintf(newSaveFile, "%c", g->occupiedBoard[i][j]);
        }
        fprintf(newSaveFile, "\n");
    }
    fclose(newSaveFile);
    exit(0);
}

/**
*   Function for detecting if a game is being saved
*
*
*/
void detect_save(Game* g, char* savePath){
    if(strstr(savePath, "save")){
        int pathLength = strlen(savePath) - 4;
        char* path = malloc(pathLength);
        strncpy(path, savePath+4, pathLength);
        write_save_file(g, path);
    }
}

/**
*   Function for prompting 
*
*
*/
void get_player_move(Game* g){
    char buffer[80];
    fgets(buffer, sizeof(buffer), stdin);
    //Get a valid move
    detect_save(g, buffer);
    if(validate_move(g, buffer)){
        update_board(g, buffer);
        if(detect_three_in_a_row(g)){
            //Remove piece from other player
            select_players_piece_to_remove(g);
            decrement_player_tokens(g);
        }
    } else {
        //Prompt until a valid response
        while(1) {
            prompt_player(g);
            fgets(buffer, sizeof(buffer), stdin);
            if(validate_move(g, buffer)){
                update_board(g, buffer);
                if(detect_three_in_a_row(g)){
                    //Remove piece from other player
                    select_players_piece_to_remove(g);
                    decrement_player_tokens(g);

                }
                break;
            }
        }
    }
    
}

/**
*   Function for playing a game
*
*
*/
void play_game(Game* g, int argc, char** argv) {
    while(1) {
        //Exit if game is over
        if(game_is_over(g)) {
            handle_winner(g, argc, argv);
            break;
        }
        //Game is in progress
        print_board(g);
        //handle eof
        handle_eof();
        //Get human move
        if(current_player_human(g)) {
            prompt_player(g);
            get_player_move(g);
            increment_player(g);             
        } else {
            //Get the automatic player move
            get_automatic_move(g, argc, argv);
            //Handle three in a row
            if(detect_three_in_a_row(g)){
                //Remove piece from other player
                select_players_piece_to_remove(g);
            }
        }
    }
}

/**
*   Function for getting placement for W
*
*
*/
void get_white_placement(Game* g) {
    //Get W player input
    char tokenLocation[10];
    printf("Player W placement: ");
    fflush(stdout);  
    fgets(tokenLocation, sizeof(tokenLocation), stdin);
    
    //Valid board location chosen on first attempt
    if(validate_token_location(g, tokenLocation)){
        update_placement_board(g, tokenLocation[0], tokenLocation[1], 'W');
    } else {
        //Prompt again
        while(1) {
            //Get player W input 
            char tokenLocation[10];
            printf("Player W placement: ");
            fflush(stdout);  
            fgets(tokenLocation, sizeof(tokenLocation), stdin);
            //Valid board location chosen
            if (validate_token_location(g, tokenLocation)){
                update_placement_board(g, tokenLocation[0], tokenLocation[1], 'W');
                break;
            }
        } 
    } 
}

/**
*   Function for getting placement for B 
*
*
*/
void get_black_placement(Game* g) {
   //Get B player input
    char tokenLocation[10];
    printf("Player B placement: ");
    fflush(stdout);  
    fgets(tokenLocation, sizeof(tokenLocation), stdin);
    
    //Valid board location chosen on first attempt
    if(validate_token_location(g, tokenLocation)){
        update_placement_board(g, tokenLocation[0], tokenLocation[1], 'B');
    } else {
        //Continually check until valid board location chosen
        while(1) {
            char tokenLocation[10];
            printf("Player B placement: ");
            fflush(stdout);  
            fgets(tokenLocation, sizeof(tokenLocation), stdin);
            //Valid board location chosen
            if(validate_token_location(g, tokenLocation)){
                update_placement_board(g, tokenLocation[0], tokenLocation[1], 'B');
                break;
            }
        } 
    } 
}

/**
*   Function for placing tokens on the board
*
*
*/
void place_tokens(Game* g, int argc, char** argv) {
    FILE* fp = fopen(argv[1], "r");
    char buffer[10];
    while(fgets(buffer, sizeof(buffer), fp)){
        if(strstr(buffer, "W")) {
            g->p1tokens+=1;
            print_board(g);
            get_white_placement(g);
        } else {
            g->p2tokens+=1;
            print_board(g);
            get_black_placement(g);
        }
    }
    fclose(fp);
}

/**
*   Function for initialising the board
*
*
*/
void initialise_occupied_board(Game* g, int argc, char** argv) {
    g->occupiedBoard = (char**) malloc(sizeof(char*) * 8);   
    for(int i = 0; i < 8; i++){
        g->occupiedBoard[i] = (char*) malloc(sizeof(char) * 3);
    }
    //Occupied board
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 3; j++) {
            g->occupiedBoard[i][j] = 'O';
        }
    }
}

/**
*   Function for initialising a new game
*
*
*/
void initialise_new_game(Game* g, int argc, char** argv) {
    g->currentPlayer = 0;
    g->p1type = argv[2][0];
    g->p2type = argv[3][0];
    g->winner = 0;
    g->p1tokens = 0;
    g->p2tokens = 0;
}

/**
*   Function for reading a saved game
*
*
*/
void read_save_file(Game* g, int argc, char** argv) {
    char buffer[80];
    FILE* saveFile = fopen(argv[1], "r'");
    fgets(buffer, sizeof(buffer), saveFile);
    sscanf(buffer, "%d %d %d %c %c", &g->currentPlayer, &g->p1tokens, &g->p2tokens, &g->p1type, &g->p2type);
    int row = 0;
    while(fgets(buffer, sizeof(buffer), saveFile) != NULL){
        char firstColumn, secondColumn, thirdColumn;
        sscanf(buffer, "%c%c%c", &firstColumn, &secondColumn, &thirdColumn);
        g->occupiedBoard[row][0] = firstColumn;
        g->occupiedBoard[row][1] = secondColumn;
        g->occupiedBoard[row][2] = thirdColumn;
        row+=1;
    }

    fclose(saveFile);
}

/**
*   Function for initialising a saved game
*
*
*/
void initialise_save_game(Game* g, int argc, char** argv) {
    initialise_occupied_board(g, argc, argv);
    read_save_file(g, argc, argv);
}

/**
*   Function for starting a new game
*
*
*/
void new_game(Game* g, int argc, char** argv) {
    if(argc == 4){
        initialise_new_game(g, argc, argv);
        initialise_occupied_board(g, argc, argv);
        place_tokens(g, argc, argv);
        play_game(g, argc, argv);
    }
}

/**
*   Function for loading a game
*
*
*/
void load_game(Game* g, int argc, char** argv){
    if(argc == 2){
        initialise_save_game(g, argc, argv);
        play_game(g, argc, argv);
    }
}

/**
*   Main function for moss
*
*
*/
int main(int argc, char** argv){
    check_args(argc, argv);
    Game* g = malloc(sizeof(Game));
    new_game(g, argc, argv);
    load_game(g, argc, argv);
    return 0;
}