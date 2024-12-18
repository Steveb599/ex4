/******************
Name:
ID:
Assignment:
*******************/
#include <stdio.h>
#include <string.h>

void checkBuffer();
int robot_paths();
float calculateTotalWeights(float cheerLeaderWeights[5][5], int i, int j);
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
                    printf("The total number of paths the robot can take to reach home is: 0.\n");
                    break;
                }

                int numberofPaths = robot_paths(col, row);
                printf("The total number of paths the robot can take to reach home is: %d.\n", numberofPaths);
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

int numberOfPaths = 0;
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
        }
    }

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
    char inputValidation;
    printf("Please enter a term for validation:\n");
    scanf(" %c", &inputValidation);
    checkBuffer();
}

void checkBuffer()
{
    char c;
    scanf("%c", &c);
    printf("%c\n", c);
    if (c == '\n')
        return;
    checkBuffer();
}

void task4_queens_battle()
{
    // Todo
}

void task5_crossword_generator()
{
    // Todo
}
