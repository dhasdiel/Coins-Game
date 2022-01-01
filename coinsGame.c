#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//-------------------------------------------------------------
// Coines Game.
//-------------------------------------------------------------
// General : The program perform a game of coins.
//
// Input : Operator and then the operands for the game.
//
// Process : The program activates a function to perform the
// operation according to the play.
//
// Output : Print the results of the actoin of the user.
//
//-------------------------------------------------------------
// Programmer : Daniel Hasdiel.
//-------------------------------------------------------------
// Const definition
// -----------------------
#define MIN_CELLS 10
#define MAX_CELLS 25
#define COINS 4
//-------------------------------------------------------------
// Function prototype
// -----------------------
int get_cellNum();
void draw_board(int coins[], int cellNum);
void draw_line(int length);
void draw_cols(int coins[], int cellNum);
void print_welcome_message();
void place_coins(int coins[], int cellNum);
int gameover(int coins[]);
void make_move(int coins[], int player_num);
int max_steps(int coins[], int nIndexCoins);
void summary_game_print(int player_num);
//-------------------------------------------------------------
int main()
{
    // Variable definition
    int player_num = 1;
    int coins[COINS] = {0};
    int cellNum;
    // Code Section
    print_welcome_message();
    cellNum = get_cellNum();
    place_coins(coins, cellNum);
    draw_board(coins, cellNum);
    while (!gameover(coins))
    {
        make_move(coins, player_num);
        draw_board(coins, cellNum);
        player_num = 3 - player_num;
    }
    summary_game_print(3 - player_num);
    return 0;
}
//-------------------------------------------------------------
// Functions
//-------------------------------------------------------------
// Get cellNum
// -----------------------
//
// General : Perform Drawing of the board according to user choice
//
// Parameters : None.
//
// Return value : int.
//
//-------------------------------------------------------------
int get_cellNum()
{
    // Variable definition
    int nSize;
    // Code Section
    printf("Enter the size of the board:\n");
    scanf("%d", &nSize);
    while (nSize < MIN_CELLS || nSize > MAX_CELLS)
    {
        printf("Worng input!\nEnter again the size of the board:\n");
        scanf("%d", &nSize);
    }
    return nSize;
}
//-------------------------------------------------------------
// Draw The Board & line & Cols
// -----------------------
//
// General : The function prints the game board and the coins in it
//
// Parameters :
// cellNum  - An int variable that has the size of a game board
// coins[] – An int array that stores the position of the coins
// in the game board
//
// Return value : None.
//
//-------------------------------------------------------------
void draw_board(int coins[], int cellNum)
{
    // Code Section
    draw_line(cellNum);
    printf("\n");
    draw_cols(coins, cellNum);
    printf("\n");
    draw_cols(coins, cellNum);
    printf("\n");
    draw_line(cellNum);
    printf("\n");
}
void draw_line(int length)
{
    // Variable definition
    int nLine;
    // Code Section
    printf("-");
    for (nLine = 0; nLine < length * 3; nLine++)
    {
        printf("-");
    }
}
void draw_cols(int coins[], int cellNum)
{
    // Variable definition
    int nPlace;
    int nIndexCoins = 0;
    // Code Section
    printf("|");
    for (nPlace = 1; nPlace <= cellNum; nPlace++)
    {
        if (coins[nIndexCoins] == nPlace)
        {
            printf("**|");
            nIndexCoins++;
        }
        else
        {
            printf("  |");
        }
    }
}
//-------------------------------------------------------------
// Print Welcome Message
// -----------------------
//
// General : Perform a print message.
//
// Parameters : None.
//
// Return value : None.
//
//-------------------------------------------------------------
void print_welcome_message()
{
    printf("Hello!\nThe game is starting!\n");
}
//-------------------------------------------------------------
// Place Coins on the board
// -----------------------
//
// General : Perform Drawing of the board according to user choice
//
// Parameters :
// cellNum  - the operator that have the value of the size array
// coins[] – An int array that stores the position of the coins
// in the game board
//
// Return value : None.
//
//-------------------------------------------------------------
void place_coins(int coins[], int cellNum)
{
    // Variable definition
    int nIndexCoins, nPlace = 0;
    // Code Section
    for (nIndexCoins = 0; nIndexCoins < COINS; nIndexCoins++)
    {
        printf("Enter the place of coin %d:\n", nIndexCoins + 1);
        scanf("%d", &nPlace);
        while (nPlace > cellNum || nPlace < 1 || nPlace < coins[nIndexCoins - 1] || coins[nIndexCoins - 1] == nPlace)
        {
            printf("Worng input!\nEnter again the place of coin %d:\n", nIndexCoins + 1);
            scanf("%d", &nPlace);
        }
        coins[nIndexCoins] = nPlace;
    }
}
//-------------------------------------------------------------
// Make Move
// -----------------------
//
// General : The function makes a move according to the user
// and checks whether it is a correct move.
//
// Parameters :
// coins[] – An int array that stores the position of the coins
// in the game board
// player_num - In this variable is given the number of the player.
//
// Return value : None.
//
//-------------------------------------------------------------
void make_move(int coins[], int player_num)
{
    // Variable definition
    int nIndexCoins, nNumOfSteps;
    // Code Section
    printf("|player #%d|\nEnter which coin your want to move:\n", player_num);
    scanf("%d", &nIndexCoins);
    while (nIndexCoins > COINS || nIndexCoins < 0 || coins[nIndexCoins - 1] == nIndexCoins || coins[nIndexCoins - 2] + 1 == coins[nIndexCoins - 1])
    {
        printf("|player #%d|\nWorng input!\a\nEnter again which coin your want to move:\n", player_num);
        scanf("%d", &nIndexCoins);
    }
    nIndexCoins--;
    printf("|player #%d|\nEnter how much steps your want to move coin #%d:\n", player_num, nIndexCoins + 1);
    printf("The max steps with this coin is: %d-->\n", max_steps(coins, nIndexCoins));
    scanf("%d", &nNumOfSteps);
    while (coins[nIndexCoins] - nNumOfSteps < 0 || coins[nIndexCoins] - nNumOfSteps <= coins[nIndexCoins - 1])
    {
        printf("|player #%d|\nWorng input!\a\nEnter again how much steps your want to move coin #%d :\n", player_num, nIndexCoins + 1);
        printf("The max steps with this coin is: %d-->\n", max_steps(coins, nIndexCoins));
        scanf("%d", &nNumOfSteps);
    }
    coins[nIndexCoins] -= nNumOfSteps;
    player_num++;
}
//-------------------------------------------------------------
// Max Steps
// -----------------------
//
// General : The function gets from the user which coin he wants
// to move and returns to him how many steps he can move the coin.
//
// Parameters :
// coins[] – An int array that stores the position of the coins
// in the game board
// nIndexCoins - An int variable that stores the coin
// selected by the user
//
// Return value : An int variable that stores within it the
// maximum number of steps
//
//-------------------------------------------------------------
int max_steps(int coins[], int nIndexCoins)
{
    // Variable definition
    int nNumOfSteps = 0;
    // Code Section
    switch (nIndexCoins)
    {
    case 0:
        nNumOfSteps = coins[nIndexCoins] - nIndexCoins - 1;
        break;
    case 1:
    case 2:
    case 3:
        nNumOfSteps = coins[nIndexCoins] - coins[nIndexCoins - 1] - 1;
        break;
    default:
        break;
    }
    return nNumOfSteps;
}
//-------------------------------------------------------------
// Game Over
// -----------------------
//
// General : The function checks if the game is over.
//
// Parameters :
// coins[] - An int array that stores the position of the coins
// in the game board
//
// Return value : 1 or 0.
//
//-------------------------------------------------------------
int gameover(int coins[])
{
    // Variable definition
    int nIndexCoins;
    // Code Section
    for (nIndexCoins = 0; nIndexCoins < COINS; nIndexCoins++)
    {
        if (coins[nIndexCoins] - 1 != nIndexCoins)
        {
            return 0;
        }
    }
    return 1;
}
//-------------------------------------------------------------
// Print Summary Game Message
// -----------------------
//
// General : Perform a print message.
//
// Parameters : player_num - In this variable is given
// the number of the player.
//
// Return value : None.
//
//-------------------------------------------------------------
void summary_game_print(int player_num)
{
    printf("The winner player is player #%d!!!\n", player_num);
}