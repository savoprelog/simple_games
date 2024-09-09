#include<stdio.h>
 #include<stdlib.h>
 #include<time.h>
 #include <assert.h>

/* Returns an integer in the range [0, n).
 *
 * Uses rand(), and so is affected-by/affects the same seed.
 */
int randint(int n) {
    
  if ((n - 1) == RAND_MAX) { //maximum vaklzue that can be returned by the rand funcion
    return rand();
  } else {
    // Supporting larger values for n would requires an even more
    // elaborate implementation that combines multiple calls to rand()
    assert (n <= RAND_MAX); //Therefore, the assert is protecting against a logic error where n might exceed the range that rand() can cover.
    //If n > RAND_MAX, this assertion will fail, stopping the program with an error message. This is a safeguard to catch logic errors during development.

    // Chop off all of the values that would cause skew...
    int end = RAND_MAX / n; // truncate skew, The purpose of this line is to handle the skew or bias problem that occurs when RAND_MAX + 1 (the total number of possible outputs from rand()) is not evenly divisible by n.
    //RAND_MAX / n computes how many complete groups of n (i.e., 11) fit into RAND_MAX + 1 (i.e., 32768).
    assert (end > 0); 
    end *= n;

    // ... and ignore results from rand() that fall above that limit.
    // (Worst case the loop condition should succeed 50% of the time,
    // so we can expect to bail out of this loop pretty quickly.)
    int r;
    while ((r = rand()) >= end);

    return r % n;
  }
}

int overcheck(char grid[9], int over){
    
        
    return over;
}




int check_over(char grid[9], int *over) {


    // Check rows
    for (int i = 0; i < 9; i += 3) {
        if (grid[i] == grid[i + 1] && grid[i] == grid[i + 2]) {
            *over=1;
            char c= grid[i];
            printf("player %c has won", c);
            return *over; // Player has won
        }
    }
    
    // Check columns
    for (int i = 0; i < 3; i++) {
        if (grid[i] == grid[i + 3] && grid[i] == grid[i + 6]) {
            *over=1;
            char c= grid[i];
            printf("player %c has won", c);
            return *over; // Player has won
        }
    }
    
    // Check diagonals
    if (grid[0] == grid[4] && grid[0] == grid[8]) {
        *over=1;
        char c= grid[0];
        printf("player %c has won", c);
        return *over; // Player has won
    }
    
    if (grid[2] == grid[4] && grid[2] == grid[6]) {
        *over=1;
        char c= grid[2];
        printf("player %c has won", c);
        return *over; // Player has won
    }

        //Check if draw
    int cnt=0;
    for(int i=0;i<9;i++){

        if(grid[i]=='x' || grid[i]=='o'){
            cnt+=1;
            if(cnt==9){
                printf("DRAW!");
                *over=1;
                return *over;
        }
        }
    }
    
    // No winner
    return *over;
}

int *get_avail_pos(char grid[], int *size){
        int cnt=0;
        for(int i=0;i<9;i++){

            if(!(grid[i]=='x' || grid[i]=='o')){
                cnt+=1;
            }
        }
        
        int *arr=(int *)malloc(cnt*sizeof(int));
        int idx = 0;
        for(int i = 0; i < 9; i++){
            if(grid[i] != 'x' && grid[i] != 'o'){
                arr[idx] = i;
                idx++;
        }
    }
    *size=cnt;
    return arr;



}


void board(char grid[9]) {
    int i, j, position=0;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (j == 1 || j == 3) {
                // Print vertical lines at columns 1 and 3
                printf("|");
            }
            else if ((i == 1 || i == 3) && (j != 1 && j != 3)) {
                // Print horizontal lines at rows 1 and 3
                printf("---");  // Make horizontal lines wider
            }
            else if(i%2==0 && j%2==0){
                printf(" %c ", grid[position]);
                position++;

            }
            else {
                // Print spaces in the rest of the grid
                printf("   ");  // Empty space
            }
        }
        printf("\n");
    }
}





int main() {
    int over=0;
    char grid[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    board(grid);
    char player;
    
    do {
        printf("Choose your side, X or O: ");
        // Adding space before %c to handle newlines correctly
        scanf(" %c", &player);

        // Check if input is not 'x', 'X', 'o', or 'O'
        if (!(player == 'x' || player == 'o')) {
            printf("You have to type in either X or O.\n");
        }

    // Continue asking until valid input is provided
    } while (!(player == 'x' || player == 'o'));

    printf("You chose: %c\n", player);
    char computer = (player == 'x') ? ('o') : ('x');

    while(!over){
        board(grid);
        int size;
        int *available_positions = get_avail_pos(grid, &size);
        printf("Available positions: ");
        for(int i = 0; i < size; i++){
            printf("%d ", available_positions[i]+1);
        }

//se validacija poteze
        int pos;
        printf("enter position: ");
        scanf(" %d", &pos);
        pos--;

        int valid_move = 0;
        for (int i = 0; i < size; i++) {
            if (pos == available_positions[i]) {
                valid_move = 1;
                
                break;
            }
        }
        if (!valid_move) {
            printf("Invalid position. Try again.\n");
            free(available_positions);
            continue;
        }
        grid[pos]=player;
        
        free(available_positions);
        board(grid);
        check_over(grid, &over);
        if(over){
            break;
        }

        available_positions = get_avail_pos(grid, &size);

        if(size>0){
                srand(time(NULL));
                int comp_pos = randint(size);
                grid[available_positions[comp_pos]]=computer;

        }

        free(available_positions);
        board(grid);
        check_over(grid, &over);
        

    
    }

    



    return 0;
}
