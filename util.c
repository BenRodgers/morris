#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
*   Function for printing the error codes
*
*
*/
void print_error_codes(int code){
    switch(code) {
        case 1:
            fprintf(stderr, "Incorrect argument numbers\n");
            exit(1);
        case 2:
            fprintf(stderr, "Incorrect player types\n");
            exit(2);
        case 3:
            fprintf(stderr, "Placement File doesn't exist\n");
            exit(3);
        case 4:
            fprintf(stderr, "Invalid Placement File contents\n");
            exit(4);
        case 5:
            fprintf(stderr, "Save File doesn't exist\n");
            exit(5);
        case 6:
            fprintf(stderr, "Invalid Save File contents\n");
            exit(6);
        case 7:
            fprintf(stderr, "End of Input from User");
            exit(7);
    }
}

/**
*   Function for checking the player type 
*
*
*/
void check_player_types(char** argv) {
    if(argv[2][0] != 'h' && argv[2][0] != 'a') {
        print_error_codes(2);
    } 
    if(argv[3][0] != 'a' && argv[3][0] != 'h'){
        print_error_codes(2);
    }
    if(argv[2][1] != '\0' || argv[3][1] != '\0'){
        print_error_codes(2);
    }

}

/**
*   Function for checking a save game is valid
*
*
*/
void check_save_game(int argc, char** argv) {
    FILE* saveFile = fopen(argv[1], "r");
    char c;
    while((c = fgetc(saveFile)) != EOF){
        if(!isdigit(c) && c != '\n' && !isalpha(c)){
            print_error_codes(6);
        }
    }
    
}

/**
*   Function for checking a new game is valid
*
*
*/
void check_new_game(int argc, char** argv) {
    check_placement_file(argv);
    check_player_types(argv);
}

/**
*   Function for checking the args
*
*
*/
void check_args(int argc, char** argv) {
    if(argc != 4 && argc != 2){
        print_error_codes(1);
    }
    //Validate a new game
    if(argc == 4) {
        check_new_game(argc, argv);
    } else {
        check_save_game(argc, argv);
    }
}

/**
*   Function for checking if EOF is received
*
*
*/
void handle_eof() {
    //Exit if ctrl-d recieved
    if(feof(stdin)) {
        print_error_codes(7);
    }
}