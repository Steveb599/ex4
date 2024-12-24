/******************
Name:
ID:
Assignment:
*******************/
#include <stdio.h>
#include <string.h>

#define MAX_SIZE_BOARD 20

struct SlotDetails
{
    int row;
    int col;
    int length;
    char direction;
};

void checkBuffer(int parenthesis1, int parenthesis2, int parenthesis3, int parenthesis4, int isValid);
int robot_paths();
float calculateTotalWeights(float cheerLeaderWeights[5][5], int i, int j);
void printSolution(int boardSize, int solutionsBoard[MAX_SIZE_BOARD][MAX_SIZE_BOARD]);
void task2_human_pyramid();
void task3_parenthesis_validator();
void task4_queens_battle();
void task5_crossword_generator();

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
                scanf(" %d %d", &col, &row);
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
    if (col == 0 && row == 0)
    {
        return 1;
    }
    if (col < 0 || row < 0)
    {
        return 0;
    }
    return robot_paths(col - 1, row) + robot_paths(col, row - 1);
}

void task2_human_pyramid()
{
    float cheerLeaderWeights[5][5] = {{0}, {0, 0}, {0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0, 0}};
    printf("Please enter the weights of the cheerleaders:\n");

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            scanf(" %f", &cheerLeaderWeights[i][j]);
            if (cheerLeaderWeights[i][j] < 0)
            {
                printf("Negative weights are not supported.\n");
                return;
            }
        }
    }

    printf("The total weight on each cheerleader is:\n");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            printf("%.2f ", calculateTotalWeights(cheerLeaderWeights, i, j));
        }
        printf("\n");
    }
}

float calculateTotalWeights(float cheerLeaderWeights[5][5], int i, int j)
{
    if (j < 0 || i < 0)
        return 0.0f;
    if (i == 0 && j == 0)
        return cheerLeaderWeights[i][j];
    else
    {
        float rightCol = calculateTotalWeights(cheerLeaderWeights, i - 1, j);
        float other = calculateTotalWeights(cheerLeaderWeights, i - 1, j - 1);
        return cheerLeaderWeights[i][j] + 0.5 * (rightCol + other);
    }
}

void task3_parenthesis_validator()
{
    printf("Please enter a term for validation:\n");
    char c;
    scanf("%c", &c); 
    checkBuffer(0, 0, 0, 0, 1);
}

void checkBuffer(int round, int square, int curly, int angle, int isValid)
{
    char c;
    scanf("%c", &c);

    switch (c)
    {
    case '(':
        round++;
        break;
    case '[':
        square++;
        break;
    case '{':
        curly++;
        break;
    case ')':
        if (round <= 0) isValid = 0;
        round--;
        break;
    case ']':
        if (square <= 0) isValid = 0;
        square--;
        break;
    case '}':
        if (curly <= 0) isValid = 0;
        curly--;
        break;
    case '\n':
        if (isValid && round == 0 && square == 0 && curly == 0 && angle == 0)
            printf("The parentheses are balanced correctly.\n");
        else
            printf("The parentheses are not balanced correctly.\n");
        return;
    }

    checkBuffer(round, square, curly, angle, isValid);
}

int isPlaceForQueenPermitted(char board[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int row, int col, int boardSize, int solutionsBoard[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int lettersUsed[256])
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

    if (lettersUsed[(int)board[row][col]] == 1)
    {
        return 0;
    }

    for (int j = 0; j < col; j++)
    {
        if (solutionsBoard[row][j] == 1)
            return 0;
    }

    for (int i = 0; i < row; i++)
    {
        if (solutionsBoard[i][col] == 1)
            return 0;
    }

    return 1;
}

int placeQueens(char board[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int col, int boardSize, int solutionsBoard[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int lettersUsed[256])
{
    if (col >= boardSize)
        return 1;

    for (int row = 0; row < boardSize; row++)
    {
        if (isPlaceForQueenPermitted(board, row, col, boardSize, solutionsBoard, lettersUsed))
        {
            solutionsBoard[row][col] = 1;
            lettersUsed[(int)board[row][col]] = 1;

            if (placeQueens(board, col + 1, boardSize, solutionsBoard, lettersUsed))
                return 1;

            solutionsBoard[row][col] = 0;
            lettersUsed[(int)board[row][col]] = 0;
        }
    }

    return 0;
}

void printSolution(int boardSize, int solutionsBoard[MAX_SIZE_BOARD][MAX_SIZE_BOARD])
{
    printf("Solution:\n");
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            printf("%c ", solutionsBoard[i][j] ? 'X' : '*');
        }
        printf("\n");
    }
}

void task4_queens_battle()
{
    printf("Please enter the board dimensions:\n");
    int boardSize;
    int lettersUsed[256] = {0};
    char board[MAX_SIZE_BOARD][MAX_SIZE_BOARD];
    int solutionsBoard[MAX_SIZE_BOARD][MAX_SIZE_BOARD] = {0};

    scanf("%d", &boardSize);
    printf("Please enter a %d*%d puzzle board:\n", boardSize, boardSize);

    for (int i = 0; i < boardSize; i++)
    {
        char rowLetters[boardSize];
        scanf("%s", rowLetters);
        for (int j = 0; j < boardSize; j++)
        {
            board[i][j] = rowLetters[j];
        }
    }

    if (placeQueens(board, 0, boardSize, solutionsBoard, lettersUsed))
    {
        printSolution(boardSize, solutionsBoard);
    }
    else
    {
        printf("This puzzle cannot be solved.\n");
    }
}

int isValidPlacement(char grid[20][20], int row, int col, char *word, char direction, int length)
{
    for (int i = 0; i < length; i++)
    {
        int currentRow = (direction == 'H') ? row : row + i;
        int currentCol = (direction == 'H') ? col + i : col;

        if (grid[currentRow][currentCol] != '#' &&
            grid[currentRow][currentCol] != word[i])
        {
            return 0;
        }
    }
    return 1;
}

void placeWordInGrid(char grid[20][20], int row, int col, char *word,
                     char direction, int length, char fillChar)
{
    for (int i = 0; i < length; i++)
    {
        int currentRow = (direction == 'H') ? row : row + i;
        int currentCol = (direction == 'H') ? col + i : col;
        grid[currentRow][currentCol] = fillChar == '#' ? '#' : word[i];
    }
}

int placeWord(int currentSlot, char grid[20][20], struct SlotDetails slots[],
              char dictionary[][15], int used[], int slotsNum, int dictSize)
{
    if (currentSlot == slotsNum)
    {
        return 1;
    }

    for (int i = 0; i < dictSize; i++)
    {
        if (!used[i] && (int)strlen(dictionary[i]) == slots[currentSlot].length)
        {
            if (isValidPlacement(grid, slots[currentSlot].row, slots[currentSlot].col,
                                 dictionary[i], slots[currentSlot].direction,
                                 slots[currentSlot].length))
            {
                used[i] = 1;
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

void printGrid(char grid[20][20], int size)
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

    struct SlotDetails slots[100];
    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");

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

    char words[100][15];
    char gridSolution[20][20];
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

    int used[100] = {0};
    if (placeWord(0, gridSolution, slots, words, used, slotsNum, numWordsDictionary))
    {
        printGrid(gridSolution, gridSize);
    }
    else
    {
        printf("This crossword cannot be solved.\n");
    }
}
