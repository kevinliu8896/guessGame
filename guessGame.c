/*
 *  Name: Kevin Liu
 *  Comp1400
 *  Date: 11/18/2019
 *  File name: NineGaps.c
 *  Student Number: 105191861
 */

#include<stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

    int main_board[9]={1,2,3,4,5,6,7,8,9}; // It defines the main board to store all the values from 1-9
    int missing_array[9]; // This line generates an array of size 9 to keep track of missing values
    int game_board[9]; // It defines an array to form the actual game board with random numbers and hidden values
    int temp_board[9]; // It defines an array which is a copy of the game_board and will be displayed to the user and will be updated in each iteration
    int row_results[3] = {0}; // this is an array that stores the results of calculation of each row
    int column_results[3] = {0}; // this is an array that stores the results of calculation of each column
    char operators_array[12]; // this is an array that stores random operations
    int i,j; // these variables will be used for loop indexes
    int rand_num,temp1; // rand_num will be used to store the result of random number generations, temp1 will be used as a temporary variable
    int level; // this variable stores the level of difficulty
    char check_game; // this is a flag variable to determine if the user solves the game correctly
    int play_again; // this is a flag variable to determine if the user wants to play again or not
    int missing_count; // this is a variable that keep track of the number of missing values in the game board.

    int user_row_results[3] = {0}; // this is an array that stores the results of calculation of each row of the game board
    int user_column_results[3] = {0}; // this is an array that stores the results of calculation of each column of the game board

    srand(time(NULL));  // It generates a seed, using current time, for the random generator

    do{
        check_game=1;
        level=0;
        printf("Welcome to Nine-Gaps game!...\n");
        printf("*****************************\n");
        printf("      *****************      \n");
        printf("            *****            \n");
        printf("              *              \n");

        // get the level of difficulty from the user
        do{
            puts("Choose the level of difficulty (1-Beginner, 2-Intermediate, 3-Advanced, 4-Expert):");
            scanf("%d",&level);
            if ((level < 1) || (level > 4))
                puts("The entered value is not valid");
            else{
                switch (level){
                    case 1:
                        puts("You have chosen the Beginner level");
                        break;
                    case 2:
                        puts("You have chosen the Intermediate level");
                        break;
                    case 3:
                        puts("You have chosen the Advanced level");
                        break;
                    case 4:
                        puts("You have chosen the Expert level");
                        break;
                }
                break;
            }
        } while (1);
        //////////////////////////////////////////////////

        // 1- generate a random main board by shuffling the main_board      (COMPLETE THIS PART)
        for(int k = 0; k < 9; k++){ // for loop
            i = rand() % 9; // generate a random number from 1 - 9
            j = rand() % 9; // generate a random number from 1 - 9

            temp1 = main_board[i]; // set the current i index to temp1 variable
            main_board[i] = main_board[j]; // set the number in the i index to a random index from the array
            main_board[j] = temp1; // set temp the empty index
        } // end for loop


        // 2- generate random operators ( + , - , x )      (COMPLETE THIS PART)

        for(i = 0; i < 12; i++){ // for statement whe i = 0, and i less than 12, i increments by 1
            rand_num = rand() % 3 + 1; // generate random number between 1 and 3

            if(rand_num == 1){ // if rand_num has the value 1
                operators_array[i] = '+'; // set operators_array[i] to "+"
            } // end if
            if(rand_num == 2){ //if rand_num has the value 2
                operators_array[i] = '-'; // set operators_array[i] to "-"
            } // end if
            if(rand_num == 3){ // if rand_num has the value 3
                operators_array[i] = '*'; // set operators_array[i] to "*"
            } // end if
        } // end for statement

        // 3- Calculate the results in columns and rows      (COMPLETE THIS PART)
        int k = 0; // declare integer variable called k
        for(i = 0; i < 3; i ++){ // for loop
            row_results[i] = main_board[i*3];
            for(j = 1; j < 3; j++){ // for loop
                if(operators_array[k] == '+'){ // if statement
                    temp1 = row_results[i] + main_board[(i*3) + j];
                } // end if

                if(operators_array[k] == '-'){ // if statement
                    temp1 = row_results[i] - main_board[(i*3) + j];
                } // end if

                if(operators_array[k] == '*'){ // if statement
                    temp1 = row_results[i] * main_board[(i*3) + j];
                } // end if
                row_results[i] = temp1;
                k ++; // increment k by 1 each iteration
            } // end for loop
        } // end for loop

        int m = 6, n = 0; // declare integer variable m and n with m having value of 6 and n value 0
        for(i = 0; i < 3; i ++){ // for loop
            n = m; // set n equal to m
            column_results[i] = main_board[i];
            for(j = 1; j < 3; j++){ // for loop
                if(operators_array[n] == '+'){ // if statement
                    temp1 = column_results[i] + main_board[i + 3*j];
                } // end if

                if(operators_array[n] == '-'){ // if statement
                    temp1 = column_results[i] - main_board[i + 3*j];
                } // end if

                if(operators_array[n] == '*'){ // if statement
                    temp1 = column_results[i] * main_board[i + 3*j];
                } // end if
                column_results[i] = temp1;
                n = m + 3;
            } // end for
            m ++; // increment m by 1 each iteration

        } // end for loop

        // 4- initializing missing array to 0      (COMPLETE THIS PART)
        for(i = 0; i < 9; i ++){ // iterate through the missing array
            missing_array[i] = 0; // set missing_array[i] to allzeros
        } // end for loops

        // 5- copy the main_board into game_board      (COMPLETE THIS PART)
        for(i = 0; i < 9; i ++){ // begin for loop
            game_board[i] = main_board[i]; // copy the main board into the game board (this is done by iterating through each element)
        } // end for loop


        // Based on the selected level, 3 or 5 or 7 board values will be hidden.

        i=0; // initializing i to 0

        while (i < level*2+1){
            int r = rand() % 3;
            int c = rand() % 3;
            if (game_board[3*r+c]!='?'){
                missing_array[game_board[3*r+c]-1]= game_board[3*r+c]; // the hidden values will be added to the set of missing values
                game_board[3*r+c] = '?';
                i++;
            } // end of if
        } // end of while
        /////////////////////////////////////////////////////////

        // 6- Copy the game board into a temporary board      (COMPLETE THIS PART)
        for(i = 0; i < 9; i ++){ // for loop
            temp_board[i] = game_board[i]; // set temp_board[i] to game_board[i]
        } // end for

        // the inner loop to get values from the user
        do{

            // Display the game board after each update

            printf("Game Board:\n");
            printf("---------------------------------------------------\n");
            for (i=0;i<3;i++){
                if (i>0){                   // show the column opertors
                    for (j=0;j<3;j++){
                        printf(" %c\t\t", operators_array[3*(i+1)+ j]);
                    }
                    printf("\n");
                }

                for (j=0;j<3;j++){          // show the rows
                    if (game_board[(i*3)+j]!='?')
                        printf(" %d\t ", temp_board[(i*3)+j]);
                    else if (game_board[(i*3)+j]!=temp_board[(i*3)+j]){
                        printf(" %d?\t ", temp_board[(i*3)+j]);
                    }
                    else
                        printf(" ?\t ");

                    if (j<2)
                        printf(" %c\t", operators_array[(i*2) + j]);
                    else
                        printf("= %d", row_results[i]);       // show the rows results
                }
                printf("\n");
                if (i==2)
                    printf (" =\t\t =\t\t =\n");
            }
            for (i=0;i<3;i++)               // show the columnar results
                printf(" %d\t\t", column_results[i]);
            printf("\n---------------------------------------------------\n");

            ////////////////////////////////////////////////////////

            // 7- Display the missing values and update the missing_count variable      (COMPLETE THIS PART)
            missing_count = 0; // set missing_count to 0
            printf("Missing values: "); // display message saying missing values
            for(i = 0; i < 9; i ++){ // for loop
                if(missing_array[i] > 0){ // if statement to find the value in the array that's not 0
                    printf("%d ",missing_array[i]); // display that value;
                    missing_count ++; // increment of missing_count by 1 each iterations
                } // end if
            } // end for
            printf("\n"); // print new line
            printf("Missing count: %d\n", missing_count); // display missing count

            // 8- break if the missing values are empty      (COMPLETE THIS PART)
            if(missing_count == 0){ // if statement when the missing_count is equal to 0 the code will break
                break; // break
            } // end if

            // Get user's guess (location and value) and check inputs' validity

            printf("Enter a row number (1-3), column(1-3), value(One of the missing values):\n");
            int r, c, v;
            scanf("%d %d %d", &r, &c, &v);
            if (r==0 || c==0 || v==0)
                break;

            if (r < 1 || r > 3 || c < 1 || c > 3){
                puts("Invalid row and/or column numbers. Try again.");
                continue;
            }

            if (v < 1 || v > 9) {
                puts("Invalid cell value. Try again.");
                continue;
            }

            if (missing_array[v-1]<1) {
                puts("This value is already there. Try again.");
                continue;
            }

            // 9- if the selected cell is changeable, add the value into the cell and remove it from the missing values, in other case show an error and repeat the inner loop.
            //       (COMPLETE THIS PART)
            if(game_board[(r - 1) * 3 + (c - 1)] == '?'){ // begin if statement
                if(missing_array[temp_board[(r - 1) * 3 + (c - 1)] - 1] == -1){ // begin if statement
                    missing_array[temp_board[(r - 1) * 3 + (c - 1)] - 1] = temp_board[(r - 1) *3 + (c - 1)];

                } // end if
                temp_board[(r - 1)* 3 + (c - 1)] = v; // update the value in the 1d temp board list
                missing_array[v - 1] = -1; // set missing_array[v-1] to -1
            } // end if
            else{ // else
                puts("Invalid can't change cell try again"); // display message telling user they cant change the cell
                continue; // continue
            } // end else

        } while (1); // end of the inner loop

        //////////////////////////////////////////////////////////

        // 10- check the results      (COMPLETE THIS PART)

        int w = 0; // w is a index for operator array
        for(i = 0; i < 3; i ++){ // for loop
            user_row_results[i] = temp_board[i*3];
            for(j = 1; j < 3; j++){ // for loop
                if(operators_array[w] == '+'){ // if statement
                    temp1 = user_row_results[i] + temp_board[(i*3) + j];
                } // end if

                if(operators_array[w] == '-'){ // if statement
                    temp1 = user_row_results[i] - temp_board[(i*3) + j];
                } // end if

                if(operators_array[w] == '*'){ // if statement
                    temp1 = user_row_results[i] * temp_board[(i*3) + j];
                } // end if
                user_row_results[i] = temp1; // set user_row_results[i] to temp1
                w ++; // increment w by 1 each iteration
            } // end for
        } // end for loop


        int x = 6, p = 0; // x is index for the opperator array, p is set to value 0
        for(i = 0; i < 3; i ++){ // for loop
            p = x; // set p equal to x
            user_column_results[i] = temp_board[i];
            for(j = 1; j < 3; j++){ //  for loop
                if(operators_array[p] == '+'){ // if statement
                    temp1 = user_column_results[i] + temp_board[i + 3*j];
                } // end if

                if(operators_array[p] == '-'){ // if statement
                    temp1 = user_column_results[i] - temp_board[i + 3*j];
                } // end if

                if(operators_array[p] == '*'){ // if statement
                    temp1 = user_column_results[i] * temp_board[i + 3*j];
                } // end if
                user_column_results[i] = temp1;
                p = x + 3; // set p equal to x plus 3
            } // end for loop
            x ++; // increment x by a 1 each iteration

        } // end for

        for(i = 0; i < 3; i ++){ // check if the user results are different from the original results
            if(row_results[i] != user_row_results[i] || column_results[i] != user_column_results[i]){
                check_game = 0; // set check_game flag to false
            } // end if
        } // end for

        //////////////////////////////////////////////////////

        if (check_game)             // display Wining/Losing Message
            printf ("**** Congratulations!!!****\n ***You Won!!!!*** \n");
        else
            printf (":( Sorry it is not correct :( \n");

        printf("#######################################\n");
        printf ("   Do you want to play again? (Yes:1, No:0)\n"); // ask the user to play again
        printf("#######################################\n");
        scanf ("%d", &play_again);

        if (!play_again){
            printf("Bye!");
            break;
        }
    } while (1); // end of the outer loop
}
