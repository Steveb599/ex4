/******************
Name:
ID:
Assignment:
*******************/
#include <stdio.h>
#include <string.h>

#define MAX_SIZE_BOARD 20
#define TRUE 1
#define FALSE 0
#define MAX_LETTERS_USED 256
#define MAX_GRID_SIZE 20
#define MAXIMAL_WORD_LENGTH 15
#define MAXIMAL_SLOTS_NUMBER 100
#define CHEERLEADERS_NUMBER_PYRAMID 5
struct SlotDetails
{
    int row;
    int col;
    int length;
    char direction;
};

int validateParentheses(char current, char expected);
int robot_paths(int col, int row);
float calculateTotalWeights(float cheerLeaderWeights[CHEERLEADERS_NUMBER_PYRAMID][CHEERLEADERS_NUMBER_PYRAMID], int i, int j);
void printSolution(int boardSize, int solutionsBoard[MAX_SIZE_BOARD][MAX_SIZE_BOARD]);
int placeQueens(char board[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int col, int boardSize,
                int solutionsBoard[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int lettersUsed[MAX_LETTERS_USED]);
int isValidPlacement(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], int row, int col,
                     char word[MAXIMAL_WORD_LENGTH], char direction, int length);
void placeWordInGrid(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], int row, int col,
                     char word[MAXIMAL_WORD_LENGTH], char direction, int length, char fillChar);
int placeWord(int currentSlot, char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], struct SlotDetails slots[],
              char dictionary[][MAXIMAL_WORD_LENGTH], int used[], int slotsNum, int dictSize);
void printGrid(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], int size);
void task2_human_pyramid();
void task3_parenthesis_validator();
void task4_queens_battle();
void task5_crossword_generator();
int isPlaceForQueenPermitted(char board[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int row, int col, int boardSize,
                             int solutionsBoard[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int lettersUsed[MAX_LETTERS_USED]);

int main()
{
    int task = -1;
    do
    {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");

        if (scanf("%d", &task))
        {
            switch (task)
            {
            case 6:
                printf("Goodbye!\n");
                break;
            case 1:
                int col, row;
                printf("Please enter the coordinates of the robot (column, row):\n");
                // getting coordinates from user
                scanf(" %d %d", &col, &row);
                // if the coordinates are negative, there is no path
                if (col < 0 || row < 0)
                {
                    printf("The total number of paths the robot can take to reach home is: 0\n");
                    break;
                }

                int numberofPaths = robot_paths(col, row);
                printf("The total number of paths the robot can take to reach home is: %d\n", numberofPaths);
                break;
            case 2:
                task2_human_pyramid();
                break;
            case 3:
                task3_parenthesis_validator();
                break;
            case 4:
                task4_queens_battle();
                break;
            case 5:
                task5_crossword_generator();
                break;
            default:
                printf("Please choose a task number from the list.\n");
                break;
            }
        }
        else
        {
            scanf("%*s");
        }

    } while (task != 6);
}

int robot_paths(int col, int row)
{
    // if the robot is at home
    if (col == 0 && row == 0)
    {
        return 1;
    }
    // if the robot is out of bounds
    if (col < 0 || row < 0)
    {
        return 0;
    }
    // recursive call to find the number of paths
    return robot_paths(col - 1, row) + robot_paths(col, row - 1);
}

void task2_human_pyramid()
{
    // 2D array to initalize the weights of the cheerleaders
    float cheerLeaderWeights[CHEERLEADERS_NUMBER_PYRAMID][CHEERLEADERS_NUMBER_PYRAMID] = {{0}, {0, 0}, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0, 0}};
    printf("Please enter the weights of the cheerleaders:\n");

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            // getting the weights from the user
            scanf(" %f", &cheerLeaderWeights[i][j]);
            if (cheerLeaderWeights[i][j] < 0)
            {
                // if the weight is negative, print an error message and return
                printf("Negative weights are not supported.\n");
                return;
            }
        }
    }

    printf("The total weight on each cheerleader is:\n");
    // printing the total weight on each cheerleader
    for (int i = 0; i < CHEERLEADERS_NUMBER_PYRAMID; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            printf("%.2f ", calculateTotalWeights(cheerLeaderWeights, i, j));
        }
        printf("\n");
    }
}

float calculateTotalWeights(float cheerLeaderWeights[CHEERLEADERS_NUMBER_PYRAMID][CHEERLEADERS_NUMBER_PYRAMID], int i, int j)
{
    // if the indexes are out of bounds, return 0
    if (j < 0 || i < 0)
        return 0.0f;
    if (i == 0 && j == 0)
        // if the cheerleader is at the top of the pyramid, return her weight
        return cheerLeaderWeights[i][j];
    else
    {
        // calculate the total weight of the cheerleader in the right side (same row, no change in j so only the weight of its row on top of her)
        float rightCol = calculateTotalWeights(cheerLeaderWeights, i - 1, j);
        // calculate the total weight of the cheerleader at the other side
        float other = calculateTotalWeights(cheerLeaderWeights, i - 1, j - 1);
        return cheerLeaderWeights[i][j] + 0.5 * (rightCol + other);
    }
}

void task3_parenthesis_validator()
{
    printf("Please enter a term for validation:\n");
    char firstChar;
    scanf(" %c", &firstChar);
    int isBalanced = validateParentheses(firstChar, ' ');

    if (isBalanced == TRUE)
    {
        printf("The parentheses are balanced correctly.\n");
    }
    else
    {
        printf("The parentheses are not balanced correctly.\n");
    }
}
int validateParentheses(char current, char expected)
{
    // If current is a space, get next character
    if (current == ' ')
    {
        char nextChar;
        scanf("%c", &nextChar);
        return validateParentheses(nextChar, expected);
    }

    // end of line
    if (current == '\n')
    {
        return expected == ' ';
    }

    // Handle opening brackets
    switch (current)
    {
    case '(':
        return validateParentheses(' ', ')') &&
               validateParentheses(' ', expected);
    case '{':
        return validateParentheses(' ', '}') &&
               validateParentheses(' ', expected);
    case '[':
        return validateParentheses(' ', ']') &&
               validateParentheses(' ', expected);
    case '<':
        return validateParentheses(' ', '>') &&
               validateParentheses(' ', expected);
    }

    // if we found what we are expecting return true, its sucess
    if (current == expected)
    {
        return TRUE;
    }

    // If we found a closing bracket when we didnt expect one, return failure = not parenthesis balanced
    if (current == ')' || current == '}' ||
        current == ']' || current == '>')
    {
        return FALSE;
    }

    // Continue checking in recursive manner
    return validateParentheses(' ', expected);
}
int isPlaceForQueenPermitted(char board[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int row, int col, int boardSize, int solutionsBoard[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int lettersUsed[MAX_LETTERS_USED])
{
    // Check for adjacent queens
    if ((row > 0 && solutionsBoard[row - 1][col] == 1) ||
        (row < boardSize - 1 && solutionsBoard[row + 1][col] == 1) ||
        (col > 0 && solutionsBoard[row][col - 1] == 1) ||
        (col < boardSize - 1 && solutionsBoard[row][col + 1] == 1) ||
        (row > 0 && col > 0 && solutionsBoard[row - 1][col - 1] == 1) ||
        (row > 0 && col < boardSize - 1 && solutionsBoard[row - 1][col + 1] == 1) ||
        (row < boardSize - 1 && col > 0 && solutionsBoard[row + 1][col - 1] == 1) ||
        (row < boardSize - 1 && col < boardSize - 1 && solutionsBoard[row + 1][col + 1] == 1))
    {
        return 0;
    }

    // Check if the letter is already used
    if (lettersUsed[(int)board[row][col]] == 1)
    {
        return 0;
    }

    // Check if there are queens in the same row or column
    for (int j = 0; j < col; j++)
    {
        if (solutionsBoard[row][j] == 1)
            return 0;
    }

    // Check if there are queens in the same column
    for (int i = 0; i < row; i++)
    {
        if (solutionsBoard[i][col] == 1)
            return 0;
    }

    return 1;
}

int placeQueens(char board[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int col, int boardSize, int solutionsBoard[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int lettersUsed[MAX_LETTERS_USED])
{
    // If all queens are placed, return 1
    if (col >= boardSize)
        return 1;

    for (int row = 0; row < boardSize; row++)
    {
        // Check if the queen can be placed in the current cell
        if (isPlaceForQueenPermitted(board, row, col, boardSize, solutionsBoard, lettersUsed))
        {
            // Place the queen
            solutionsBoard[row][col] = 1;
            lettersUsed[(int)board[row][col]] = 1;

            // recursive to place rest of the queens
            if (placeQueens(board, col + 1, boardSize, solutionsBoard, lettersUsed))
                return 1;

            // Backtrack
            solutionsBoard[row][col] = 0;
            lettersUsed[(int)board[row][col]] = 0;
        }
    }

    return 0;
}

void printSolution(int boardSize, int solutionsBoard[MAX_SIZE_BOARD][MAX_SIZE_BOARD])
{
    // Print the solution by the boardsize sizes
    printf("Solution:\n");
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            // Print 'X' if there is a queen, '*' otherwise
            printf("%c ", solutionsBoard[i][j] ? 'X' : '*');
        }
        printf("\n");
    }
}

void task4_queens_battle()
{
    printf("Please enter the board dimensions:\n");
    int boardSize;
    int lettersUsed[MAX_LETTERS_USED] = {0};
    char board[MAX_SIZE_BOARD][MAX_SIZE_BOARD];
    int solutionsBoard[MAX_SIZE_BOARD][MAX_SIZE_BOARD] = {0};

    scanf("%d", &boardSize);
    printf("Please enter a %d*%d puzzle board:\n", boardSize, boardSize);

    // Get the board from the user
    for (int i = 0; i < boardSize; i++)
    {
        char rowLetters[boardSize];
        scanf("%s", rowLetters);
        for (int j = 0; j < boardSize; j++)
        {
            board[i][j] = rowLetters[j];
        }
    }

    // Solve the puzzle and place queens
    if (placeQueens(board, 0, boardSize, solutionsBoard, lettersUsed))
    {
        printSolution(boardSize, solutionsBoard);
    }
    else
    {
        // If there is no solution
        printf("This puzzle cannot be solved.\n");
    }
}

int isValidPlacement(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], int row, int col,
                     char word[MAXIMAL_WORD_LENGTH], char direction, int length)
{
    int currentRow, currentCol;

    for (int i = 0; i < length; i++)
    {
        // Calculate current position based on direction
        currentRow = (direction == 'H') ? row : row + i;
        currentCol = (direction == 'H') ? col + i : col;

        // Check if position is within grid bounds
        if (currentRow >= MAX_GRID_SIZE || currentCol >= MAX_GRID_SIZE)
        {
            return 0;
        }

        // Check if current position is empty or matches word letter
        if (grid[currentRow][currentCol] != '#' &&
            grid[currentRow][currentCol] != word[i])
        {
            return 0;
        }
    }
    return 1;
}

void placeWordInGrid(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], int row, int col,
                     char word[MAXIMAL_WORD_LENGTH], char direction, int length, char fillChar)
{
    int currentRow, currentCol;

    for (int i = 0; i < length; i++)
    {
        currentRow = (direction == 'H') ? row : row + i;
        currentCol = (direction == 'H') ? col + i : col;

        if (fillChar == '#')
        {
            grid[currentRow][currentCol] = '#';
        }
        else
        {
            grid[currentRow][currentCol] = word[i];
        }
    }
}

int placeWord(int currentSlot, char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], struct SlotDetails slots[],
              char dictionary[][MAXIMAL_WORD_LENGTH], int used[], int slotsNum, int dictSize)
{
    // If all slots are filled, return 1
    if (currentSlot == slotsNum)
    {
        return 1;
    }

    for (int i = 0; i < dictSize; i++)
    {
        // Check if the word is not used and has the same length as the slot
        if (!used[i] && (int)strlen(dictionary[i]) == slots[currentSlot].length)
        {
            // Check if the word can be placed in the grid
            if (isValidPlacement(grid, slots[currentSlot].row, slots[currentSlot].col,
                                 dictionary[i], slots[currentSlot].direction,
                                 slots[currentSlot].length))
            {
                used[i] = 1;
                // Place the word in the grid
                placeWordInGrid(grid, slots[currentSlot].row, slots[currentSlot].col,
                                dictionary[i], slots[currentSlot].direction,
                                slots[currentSlot].length, 'X');

                if (placeWord(currentSlot + 1, grid, slots, dictionary, used,
                              slotsNum, dictSize))
                {
                    return 1;
                }

                used[i] = 0;
                placeWordInGrid(grid, slots[currentSlot].row, slots[currentSlot].col,
                                dictionary[i], slots[currentSlot].direction,
                                slots[currentSlot].length, '#');
            }
        }
    }
    return 0;
}

void printGrid(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("| %c ", grid[i][j]);
        }
        printf("|\n");
    }
}

void task5_crossword_generator()
{
    printf("Please enter the dimensions of the crossword grid:\n");
    int gridSize;
    scanf("%d", &gridSize);
    printf("Please enter the number of slots in the crossword:\n");
    int slotsNum;
    scanf("%d", &slotsNum);
    struct SlotDetails slots[MAXIMAL_SLOTS_NUMBER];
    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");

    // Get the slots from the user
    for (int i = 0; i < slotsNum; i++)
    {
        scanf("%d %d %d", &slots[i].row, &slots[i].col, &slots[i].length);
        scanf(" %c", &slots[i].direction);
    }

    int numWordsDictionary;
    printf("Please enter the number of words in the dictionary:\n");
    scanf("%d", &numWordsDictionary);
    while (numWordsDictionary < slotsNum)
    {
        printf("The dictionary must contain at least %d words. Please enter a valid dictionary size:\n", slotsNum);
        scanf("%d", &numWordsDictionary);
    }

    char words[MAXIMAL_SLOTS_NUMBER][MAXIMAL_WORD_LENGTH];
    char gridSolution[MAX_GRID_SIZE][MAX_GRID_SIZE];
    printf("Please enter the words for the dictionary:\n");
    for (int i = 0; i < numWordsDictionary; i++)
    {
        scanf("%s", words[i]);
    }

    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            gridSolution[i][j] = '#';
        }
    }

    int used[MAXIMAL_SLOTS_NUMBER] = {0};
    // Solve the crossword
    if (placeWord(0, gridSolution, slots, words, used, slotsNum, numWordsDictionary))
    {
        // print grid if solved
        printGrid(gridSolution, gridSize);
    }
    else
    {
        // print if not solved
        printf("This crossword cannot be solved.\n");
    }
}
