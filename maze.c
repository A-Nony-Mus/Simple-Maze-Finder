/*A-Nony-Mus
 17 Apr. 2012
 This program finds its way through a maze
 Completed on 20 Apr. 2012
 To use, create a file called maze.txt in the same directory
 o is an open space and x is an obstacle
 Ex:
 oxoooooo
 ooxooooo
 oxxooooo
 oooxoxxo
 xxxxoxoo
 oooxoxoo
 ooooxoox
 xooooooo*/

#include <stdio.h>
#include <string.h>

void fill_maze(char maze[][9], FILE *inp);
int find_path(char maze[][9], int row, int column);
void print_maze(char maze[][9]);

int main(void)
{
    char maze[8][9];    //This is an 8x8 matrix, the ninth element in the second dimension is for the null character
    int x,
        error;
    FILE *mazep;
    
    mazep = fopen("maze.txt", "r");
	printf("rows across, columns down\n\n");
    
    fill_maze(maze, mazep); //fill the maze
    
    //print what the maze was originally
    printf("maze before:\n");
    print_maze(maze);
    printf("\n");
    
    error = find_path(maze, 0, 1);
    //print the solution to the maze if there is one
    if (error != 2){
    printf("maze after:\n");
    print_maze(maze);
    }
    else
        printf("That is an impossible maze\n");
    
    return(0);
}
//Inputs: A two dimensional array and a file with a maze
//Outputs: A two dimensional array filled with the maze
void fill_maze(char maze[][9], FILE *inp)
{
    int x;
    
    x = 0;
    while (x < 8) {
        fscanf(inp, "%s", maze[x]);
        x++;
        }
}

//Inputs: A two dimensional array filled with the maze
//Outputs: Prints the maze
void print_maze(char maze[][9])
{
    int x;
    
    x = 0;
    while (x < 8) {
        printf("%s\n", maze[x]);
        x++;
    }
}

//Inputs: A two dimensional array filled with the maze, a row number, and a column number
//Outputs: A two dimensional array filled with a solution to the maze
int find_path(char maze[][9], int row, int column)
{
    int error;
    
    error = 0;
    maze[row][column] = '?';    //fill the current position with a marker
    
    if (maze[7][6] == 'x') //if this space is marked with an x, update the error
        error++;
    if (maze[6][7] == 'x')  //if this space is marked with an x, update the error
        error++;
    
    if (error != 2){
        if (row != 7 && row >= 0) { //as long as we are within the rows limits
            if (column != 7 && column >= 0){   //as long as we are within the columns limits
                if (maze[row + 1][column] != 'x' && maze[row + 1][column] != '?'){ 
                    find_path(maze, row + 1, column);
					printf("1\n");
                }
    
                else if (maze[row][column + 1] != 'x' && maze[row][column + 1] != '?'){ 
                    find_path(maze, row, column + 1);
					printf("2\n");
                }
    
                else if (maze[row][column - 1] != 'x'){ 
                    find_path(maze, row, column - 1);
					printf("3\n");
                }
    
                else if (maze[row - 1][column] != 'x'){ 
                    find_path(maze, row - 1, column);
					printf("4\n");
                }
            }
            else if (column == 7 || column == 0) {  //if we are at the columns edges
			printf("reached\n");
                if (maze[row + 1][column] != 'x' && maze[row + 1][column] != '?'){ 
                    find_path(maze, row + 1, column);
					printf("1.1\n");
                }
                
                else if (maze[row][column - 1] != 'x' && column != 0){ 
                    find_path(maze, row, column - 1);
					printf("3.1\n");
				}
				
				else if (maze[row][column + 1] != 'x' && column != 7){ 
                    find_path(maze, row, column + 1);
					printf("3.5\n");
				}
                
                else if (maze[row - 1][column] != 'x'){ 
                    find_path(maze, row - 1, column);
					printf("2.1\n");
                }
        }
    }
        else if (row == 7) {    //if we are at the rows edges
            if (column != 7 && column >= 0){    //as long as we are within the columns limits
                if (maze[row][column + 1] != 'x' && maze[row][column + 1] != '?') 
                    find_path(maze, row, column + 1);
            
                else if (maze[row][column - 1] != 'x') 
                    find_path(maze, row, column - 1);
            
                else if (maze[row - 1][column] != 'x' && row != 0) 
                    find_path(maze, row - 1, column);
					
				else if (maze[row + 1][column] != 'x' && row != 7) 
                    find_path(maze, row + 1, column);
            }
            else    //if we have reached our goal
                maze[row][column] = '?';
    }
    }
    
    return(error);
}
