#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h> /*for system()*/
#include <math.h>

int main()
{
    /* 2D array */
    int grids[3][3] = {0};
    int rowLength;
    int columnLength;

    /* Check winner func */
    int checkWinner() {
        /* check row */
        for (int i = 0; i < rowLength; i++) {
            int playerPin = 0;
            for (int j = 0; j < columnLength; j++) {
                if (grids[i][j] == 1) {
                    playerPin+=1;
                } else if (grids[i][j] == -1) {
                    playerPin-=1;
                }
            }
            if (playerPin == rowLength) {
                return 1;
            } else if (playerPin == -1 * rowLength) {
                return -1;
            }
        }

        /* Check column */
        for (int i = 0; i < columnLength; i++) {
            int playerPin = 0;
            for (int j = 0; j < rowLength; j++) {
                if (grids[j][i] == 1) {
                    playerPin+=1;
                } else if (grids[j][i] == -1) {
                    playerPin-=1;
                }
            }
            if (playerPin == rowLength) {
                return 1;
            } else if (playerPin == -1 * rowLength) {
                return -1;
            }
        }

        /* Check diagonal */
        int playerPin = 0;
        int playerPin2 = 0;
        for (int i = 0; i < rowLength; i++) {
            /* Check left -> right */
            if (grids[i][i] == 1) {
                playerPin+=1;
            } else if (grids[i][i] == -1) {
                playerPin-=1;
            }

            if (playerPin == rowLength) {
                return 1;
            } else if (playerPin == -1 * rowLength) {
                return -1;
            }

            /* Check right -> left */
            if (grids[i][-i + rowLength -1] == 1) {
                playerPin2+=1;
            } else if (grids[i][-i + rowLength -1] == -1) {
                playerPin2-=1;
            }

            if (playerPin2 == rowLength) {
                return 1;
            } else if (playerPin2 == -1 * rowLength) {
                return -1;
            }
        }
    }


    /* Check available*/
    int checkAvailable(){
        int availableSlots[9][2] = {NULL};
        int availableSlotsLen;
        availableSlotsLen = sizeof availableSlots / sizeof *availableSlots;

        /* check row */
        for (int i = 0; i < rowLength; i++) {
            for (int j = 0; j < columnLength; j++) {
                /* If empty */
                if (grids[i][j] == 0) {
                    /* Find a empty index for availableSlots and append the data */
                    for (int k = 0; k < availableSlotsLen; k++) {
                        if (availableSlots[k][0] == NULL) {
                            availableSlots[k][0] = i + 1;
                            availableSlots[k][1] = j + 1;
                            break;
                        }
                    }
                }
            }
        }

        int emptySlotsLen = 0;
        for (int k = 0; k < availableSlotsLen; k++) {
            if (availableSlots[k][0] - 1 != -1) {
                emptySlotsLen++;
            }
        }

        if (emptySlotsLen != 0) {
            /* Tie */
            return 1;
        } else {
            /* Still have spots */
            return -1;
        }
    }


    /* Bot move func */
    void botMove(){
        /* I know this is very bad reusing code but i'm lazy so yeeeaaaaa */
        int availableSlots[9][2] = {NULL};
        int availableSlotsLen;
        availableSlotsLen = sizeof availableSlots / sizeof *availableSlots;

        /* check row */
        for (int i = 0; i < rowLength; i++) {
            for (int j = 0; j < columnLength; j++) {
                /* If empty */
                if (grids[i][j] == 0) {
                    /* Find a empty index for availableSlots and append the data */
                    for (int k = 0; k < availableSlotsLen; k++) {
                        if (availableSlots[k][0] == NULL) {
                            availableSlots[k][0] = i + 1;
                            availableSlots[k][1] = j + 1;
                            break;
                        }
                    }
                }
            }
        }

        int emptySlotsLen = 0;
        for (int k = 0; k < availableSlotsLen; k++) {
            if (availableSlots[k][0] - 1 != -1) {
                emptySlotsLen++;
            }
        }

        /* Counter User */
        int countered = 0;
        for (int i = 0; i < emptySlotsLen; i++) {
            /* Find win */
            grids[availableSlots[i][0] - 1][availableSlots[i][1] - 1] = -1;
            if (checkWinner() == -1) {
                countered = 1;
                break;
            } else {
                grids[availableSlots[i][0] - 1][availableSlots[i][1] - 1] = 0;
            }

            if (countered != 1) {
                /* counter user */
                grids[availableSlots[i][0] - 1][availableSlots[i][1] - 1] = 1;
                if (checkWinner() == 1) {
                    grids[availableSlots[i][0] - 1][availableSlots[i][1] - 1] = -1;
                    countered = 1;
                    break;
                } else {
                    grids[availableSlots[i][0] - 1][availableSlots[i][1] - 1] = 0;
                }
            }
        }

        if (countered != 1){
            time_t t;
            /* Intialize random number generator */
            srand((unsigned) time(&t));
            /* Print 5 random numbers from 0 to ? */
            int ranNum = rand() % emptySlotsLen;

            grids[availableSlots[ranNum][0] - 1][availableSlots[ranNum][1] - 1] = -1;
        }
    }


    /* Game */
    while (1) {
        int row;
        int col;

        printf("\n");
        rowLength = sizeof grids / sizeof *grids;
        for (int i = 0; i < rowLength; i++) {
            columnLength = sizeof grids[i] / sizeof *grids[i];
            for (int j = 0; j < columnLength; j++) {
                if (grids[i][j] == 1) {
                    printf("|O|");
                } else if (grids[i][j] == 0) {
                    printf("|-|");
                } else {
                    printf("|X|");
                }
            }
            printf("\n");
        }

        printf("Enter row: ");
        scanf("%i", &row);

        while(row > rowLength - 1){
            printf("Out of index!\nEnter row: ");
            scanf("%i", &row);
        }

        printf("Enter column: ");
        scanf("%i", &col);

        while(col > columnLength - 1){
            printf("Out of index!\nEnter column: ");
            scanf("%i", &col);
        }

        /*system("cls");*/
        system("cls");

        if (grids[row][col] == 0) {
            grids[row][col] = 1;
            int winnerResult = checkWinner();

            if (winnerResult == 1) {
                printf("User won!\n");
                break;
            } else if (winnerResult == -1) {
                printf("User lost!\n");
                break;
            } else {
                int availableResult = checkAvailable();
                if (availableResult == -1) {
                    printf("Tie!\n");
                    break;
                } else {
                    botMove();
                    int winnerResult = checkWinner();

                    if (winnerResult == 1) {
                        printf("User won!\n");
                        break;
                    } else if (winnerResult == -1) {
                        printf("User lost!\n");
                        break;
                    } else {
                        int availableResult = checkAvailable();
                        if (availableResult == -1) {
                            printf("Tie!\n");
                            break;
                        }
                    }
                }
            }

        } else {
            printf("Invalid input!\n");
        }
    }

    printf("\n");
    rowLength = sizeof grids / sizeof *grids;
    for (int i = 0; i < rowLength; i++) {
        columnLength = sizeof grids[i] / sizeof *grids[i];
        for (int j = 0; j < columnLength; j++) {
            if (grids[i][j] == 1) {
                printf("|O|");
            } else if (grids[i][j] == 0) {
                printf("|-|");
            } else {
                printf("|X|");
            }
        }
        printf("\n");
    }

    return 0;
}

