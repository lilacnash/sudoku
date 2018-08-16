#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "console_user_interface.h"
#include "game_logic.h"


const char *all_commands[] = {"solve", "edit", "print_board", "set", "validate", "generate", "undo", "redo",
                                    "save", "num_solutions", "autofill", "hint", "mark_errors", "reset", "exit", NULL};

const char *edit_commands[] = {"solve", "edit", "print_board", "set", "validate", "generate", "undo", "redo",
                                     "save", "num_solutions", "reset", "exit", NULL};
const char *solve_commands[] = {"solve", "edit", "mark_errors", "print_board", "set", "validate", "undo", "redo",
                                      "save", "hint", "num_solutions", "autofill", "reset", "exit", NULL};
const char *init_commands[] = {"solve", "edit", NULL};

int execute_command(char *command, char *parameters) {
    /* TODO: write documentation */
    if (strcmp(all_commands[0], command) == 0) {
        execute_solve(parameters);
    } else if (strcmp(all_commands[1], command) == 0) {
        execute_edit(parameters);
    } else if (strcmp(all_commands[2], command) == 0) {
        //print_board(); // should pass our board as argument here
    } else if ((strcmp(all_commands[3], command) == 0)) {
        execute_set_cell(parameters);
    } else if ((strcmp(all_commands[4], command) == 0)) {
        validate_solution();
    } else if ((strcmp(all_commands[5], command) == 0)) {
        execute_generate(parameters);
    } else if ((strcmp(all_commands[6], command) == 0)) {
        undo();
    } else if ((strcmp(all_commands[7], command) == 0)) {
        redo();
    } else if ((strcmp(all_commands[8], command) == 0)) {
        execute_save_board(parameters);
    } else if ((strcmp(all_commands[9], command) == 0)) {
        num_solutions();
    } else if ((strcmp(all_commands[10], command) == 0)) {
        autofill();
    } else if ((strcmp(all_commands[11], command) == 0)) {
        execute_get_hint(parameters);
    } else if ((strcmp(all_commands[12], command) == 0)) {
        execute_mark_errors(parameters);
    }
    else if (strcmp(all_commands[13], command) == 0) {
        restart_game();
    } else if ((strcmp(all_commands[14], command) == 0)) {
        return 0;
    } else {
        // TODO: check what else might cause an invalid command
        printf("Error: invalid command\n");
    }
    fflush(stdin); // TODO: remove this
    return 1;
}


int check_if_suitable_command(const char *commands[], char *command) {
    int i;
    i = 0;
    // TODO: should fix this strlen
    while (commands[i]!=NULL) {
        if (strcmp(command, commands[i]) == 0) {
            return 1;
        }
        i++;
    }
    return 0;
}

void play_game() {
    char *command_and_parameters;
    char *command;
    char *parameters;
    int command_max_length;
    command_max_length = COMMAND_AND_PARAMS_SIZE;
    command_and_parameters = (char *) malloc(sizeof(char) * command_max_length);
    if (!command_and_parameters) {
        printf("Error: play_game() has failed\n");
        exit(-1);
    }
    fflush(stdin); // TODO: remove it after testing
    while (fgets(command_and_parameters, command_max_length, stdin) != NULL) {
        if (command == NULL) {
            fflush(stdin); // TODO: also should be deleted
            continue;
        }
        command = strtok(command_and_parameters, " \t\r\n");
        parameters = strtok(NULL, "\t\r\n");
        // checking if the command is allowed in the current mode
        if (GAME_MODE == 0) {
            if (!check_if_suitable_command(init_commands, command)) {
                printf("ERROR: invalid command\n");
                continue;
            }
        } else if (GAME_MODE == 1) {
            if (!check_if_suitable_command(edit_commands, command)) {
                printf("ERROR: invalid command\n");
                continue;
            }
        } else if (GAME_MODE == 2) {
            if (!check_if_suitable_command(solve_commands, command)) {
                printf("ERROR: invalid command\n");
                continue;
            }
        }
        if (!execute_command(command, parameters)){
            // means that an exit command was given
            break;
        }
        fflush(stdin); // TODO: should be deleted after testing

    }
    // TODO: check if we should free more stuff here
    free(command_and_parameters);
    printf("Exiting...\n");
}

void print_board(int board[ROWS_NUM][COLUMNS_NUM]){
    int i;
    int j;
    int z;
    int rows_counter;
    int columns_counter;
    rows_counter = 0;
    for (i = 0; i < ROWS_NUM + 4; i++) {
        if ((i % 4) == 0) {
            for (z = 0; z < (COLUMNS_NUM / 3) * 11; z++) {
                printf("-");
            }
            printf("-\n");
            rows_counter++;
        } else {
            columns_counter = 0;
            for (j = 0; j < COLUMNS_NUM + 4; j++) {
                if ((j % 4) == 0) {
                    if (j == 0) {
                        printf("|");
                    } else if (j == COLUMNS_NUM + 3) {
                        printf(" |\n");
                    } else {
                        printf(" |");
                    }
                    columns_counter++;
                } else {
                    if (fixed_numbers_board[i - rows_counter][j - columns_counter] == 1) {
                        printf(" .");
                    } else {
                        printf("  ");
                    }
                    if (board[i - rows_counter][j - columns_counter] == 0) {
                        printf(" ");
                    } else {
                        printf("%d", board[i - rows_counter][j - columns_counter]);
                    }
                }
            }
        }
    }
}
*/