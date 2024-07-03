
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include <cctype>
#include <string.h>
#include <algorithm>
using namespace std;


struct input
{
    char sign = 'x';
    char PrevSign = 'x';
    char PrevSign2 = 'x';
    int NextLine = 0;

};


struct Game
{
    bool x = 0;
    bool y = 0;
    int r_count = 0;
    int b_count = 0;
    int BoardSize = 0;
    char array[11][11];
    char pawns[2] = { 'b' , 'r' };
};

namespace Commands {
    const char* c1 = "BOARD_SIZE";
    const char* c2 = "PAWNS_NUMBER";
    const char* c3 = "IS_BOARD_CORRECT";
    const char* c4 = "IS_GAME_OVER";
    const char* c5 = "IS_BOARD_POSSIBLE";
    const char* c6 = "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT";
    const char* c7 = "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT";
    const char* c8 = "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT";
    const char* c9 = "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT";
    const char* c10 = "CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT";
    const char* c11 = "CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT";
    const char* c12 = "CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT";
    const char* c13 = "CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT";

};


int BoardCounter(input& in) {

    int whitespace = 0;

    while ((in.sign = getchar()) != '-')
    {
        // cout << sign << " ff ";
        if (in.sign == EOF) exit(EXIT_SUCCESS);
        if (isspace(in.sign))
        {
            whitespace++;
        }
    }
    //cout << whitespace <<" l " << endl;
    int size = (whitespace + 1) / 3 + 1;
    if (size == 0) return 1;
    else return size;
}


void SaveToArray(Game& game, input& in)
{

    int i = 0, j = 0;
    int underMid = 0; // gdy jest już za środkiem planszy
    cin >> in.PrevSign;
    // cout <<"hh " << in.PrevSign << endl;
    cin >> in.PrevSign;
    //  cout << "hh " << in.PrevSign << endl;


    if (game.BoardSize > 1)
    {

        cin >> in.PrevSign;
        //  cout << "hh " << in.PrevSign << endl;

        in.PrevSign = 'x';

        while (in.NextLine < game.BoardSize * 2 - 1) {


            cin >> in.sign;


            if (in.sign == 'r' || in.sign == 'b')
            {
                game.array[i][j] = in.sign;
                j--;
                i++;
                if (in.sign == 'r') game.r_count++;
                else game.b_count++;

            }
            else if (in.PrevSign2 == '>' && in.PrevSign == '-' && in.sign == '-')
            {

                in.NextLine++;

                // cout << "nextline " << in.NextLine << endl;
                j = in.NextLine;
                in.PrevSign2 = 'x';
                in.PrevSign = 'x';
                in.sign = 'x';

                if (in.NextLine >= game.BoardSize)
                {
                    underMid++;
                    j = game.BoardSize - 1;
                }
                i = underMid;
            }
            else if (in.PrevSign == '<' && in.sign == '>')
            {
                game.array[i][j] = ' ';
                j--;
                i++;
            }

            in.PrevSign2 = in.PrevSign;
            in.PrevSign = in.sign;

        }
    }
    else
    {
        cin >> in.PrevSign;
        cin >> in.sign;

        //cout << "sss " << in.sign << "  " << in.PrevSign << endl;


        if (in.sign == 'r')
        {
            game.array[0][0] = 'r';
            game.r_count++;
            cin >> in.sign;
        }
        else if (in.sign == 'b')
        {
            game.array[0][0] = 'b';
            game.b_count++;
            cin >> in.sign;
        }
        else if (in.sign == '>')
        {
            game.array[0][0] = ' ';
            game.r_count = 0;
            game.b_count = 0;
        }



    }

    //cout << "last 3 "<< endl;
    cin >> in.sign;
    // cout << in.sign << endl;
    cin >> in.sign;
    // cout << in.sign << endl;
    cin >> in.sign;
    // cout << in.sign << endl;



}

void cleanArr(input& in, Game& game) {

    in.NextLine = 0;
    in.PrevSign = 'x';
    in.PrevSign2 = 'x';
    in.sign = 'x';
    game.r_count = 0;
    game.b_count = 0;


}

void createCommad(char token[100], char& sign)
{
    int i = 0;
    do {
        token[i++] = sign;

    } while ((sign = getchar()) != '\n' && sign != EOF); // Also check for EOF to avoid infinite loop
    token[i] = '\0';
}

bool Comparision(char token[500], const char* c) {
    int i = 0;
    while (token[i] != '\0')
    {
        if (token[i] != c[i]) return false;
        i++;
    }
    return true;

}



bool F_is_board_correct(Game& game)
{
    if (game.b_count == game.r_count) return 1;
    else if (game.b_count + 1 == game.r_count) return 1;
    else return 0;
}

struct neighboor
{
    int x;
    int y;
};

void dfs_rec(int x, int y, bool visited[11][11], Game& game, int& head, char pawn, neighboor neighbors[])
{
    visited[x][y] = 1;

    neighbors[head].x = x;
    neighbors[head].y = y;
    head++;


    if (x - 1 >= 0 && visited[x - 1][y] == 0 && game.array[x - 1][y] == pawn)
    {
        dfs_rec(x - 1, y, visited, game, head, pawn, neighbors);

    }
    if (x + 1 < game.BoardSize && visited[x + 1][y] == 0 && game.array[x + 1][y] == pawn)
    {
        dfs_rec(x + 1, y, visited, game, head, pawn, neighbors);
    }
    if (y - 1 >= 0 && visited[x][y - 1] == 0 && game.array[x][y - 1] == pawn )
    {
        dfs_rec(x, y - 1, visited, game, head, pawn, neighbors);
    }
    if (y + 1 < game.BoardSize && visited[x][y + 1] == 0 && game.array[x][y + 1] == pawn )
    {
        dfs_rec(x, y + 1, visited, game, head, pawn, neighbors);
    }
    if (x - 1 >= 0 && y - 1 >= 0 && y - 1 < game.BoardSize && visited[x - 1][y - 1] == 0 && game.array[x - 1][y - 1] == pawn )
    {
        dfs_rec(x - 1, y - 1, visited, game, head, pawn, neighbors);
    }
    if (x + 1 < game.BoardSize && y + 1 < game.BoardSize && visited[x + 1][y + 1] == 0 && game.array[x + 1][y + 1] == pawn )
    {
        dfs_rec(x + 1, y + 1, visited, game, head, pawn, neighbors);
    }
}



bool dfs(Game& game, char pawn) {
    bool visited[11][11] = { 0 };
    neighboor neighbors[121];
    int head = 0;

    for (int j = 0; j < game.BoardSize; j++) {
        for (int i = 0; i < game.BoardSize; i++) {
            if (visited[i][j] == 0) {
                head = 0;
                if ((game.array[i][j] == pawn ) && visited[i][j] == 0)
                {
                    dfs_rec(i, j, visited, game, head, pawn, neighbors);
                    bool start = false, end = false;
                    for (int k = 0; k < head; k++) {
                        if (pawn == 'b') {
                            if (neighbors[k].y == 0) start = true;
                            if (neighbors[k].y == game.BoardSize - 1) end = true;
                        }
                        else {
                            if (neighbors[k].x == 0) start = true;
                            if (neighbors[k].x == game.BoardSize - 1) end = true;
                        }
                    }

                    if (start && end) return true;
                }
            }
        }
    }
    return false;
}




bool F_is_game_over(Game& game, char pawn)
{
    char red = false;
    char blue = false;

    if (dfs(game, pawn)) return 1;
    else return 0;

}


char lastMovement(Game& game)
{
    if (game.r_count - game.b_count == 0) return 'b';
    else return 'r';
}


bool F_is_game_possible(Game& game)
{
    if (F_is_board_correct(game))
    {
        char lastMove = lastMovement(game);

        bool blueWon = F_is_game_over(game, 'b');
        bool redWon = F_is_game_over(game, 'r');

        if (lastMove == 'b' && redWon) return false;
        if (lastMove == 'r' && blueWon)return false;

        if (!(blueWon || redWon)) return true;

        for (int i = 0; i < game.BoardSize; i++)
        {
            for (int j = 0; j < game.BoardSize; j++) {
                if (game.array[i][j] == lastMove) {
                    game.array[i][j] = ' ';
                    if (!F_is_game_over(game, lastMove)) {
                        game.array[i][j] = lastMove;
                        return true;
                    }
                    game.array[i][j] = lastMove;

                }
            }
        }
        return false;
    }
    else return false;
}



bool enoughtSpace(Game& game, int depth, char pawn)
{
    int emptySpace = game.BoardSize * game.BoardSize - game.r_count - game.b_count;
    if (emptySpace >= depth) return true; //głebokosc to ilosc pionków jakie trzeba postawić . jak nie ma na nie miejsc to ciao
    return false;
}


bool addPawn(Game& game, int moveCount, char pawn, int currentMove)
{
    if (moveCount <= currentMove) return false;
    for (int i = 0; i < game.BoardSize; i++)
    {
        for (int j = 0; j < game.BoardSize; j++)
        {
            if (game.array[i][j] == ' ')
            {
                game.array[i][j] = pawn;
                if (F_is_game_over(game, pawn))
                {
                    game.array[i][j] = ' ';
                    return true;

                }
                if (addPawn(game, moveCount, pawn, currentMove + 1))
                {
                    game.array[i][j] = ' ';
                    return true;
                }
                game.array[i][j] = ' ';
            }
            else if ((pawn == 'r' && game.r_count == 0 || pawn == 'b' && game.b_count == 0) && game.BoardSize <= 2) //gdy nie ma twoich pionków to doda
            {
                if (game.array[i][j] == ' ')
                {
                    currentMove++;
                    game.array[i][j] = pawn;
                    if (pawn == 'r') game.r_count++;
                    else game.b_count++;
                    if (F_is_game_over(game, pawn) || addPawn(game, moveCount, pawn, currentMove))
                    {
                        game.array[i][j] = ' ';
                        if (pawn == 'r') game.r_count--;
                        else game.b_count--;
                        return true;
                    }
                    else
                    {
                        game.array[i][j] = ' ';
                        if (pawn == 'r') game.r_count--;
                        else game.b_count--;
                        currentMove--;
                    }
                }
            }

        }
    }return false;
}






bool F_can_win_with_naive_opponent(Game& game, int maxDepth, char pawn, int moveCount)
{
    if (enoughtSpace(game, maxDepth, pawn))
    {
        if (addPawn(game, moveCount, pawn, 0)) return true;
        else return false;
    }
    else return false;

}

int depthCheck(int command, Game& game)
{
    switch (command)
    {
    case 6: //red in one
        if (game.r_count - game.b_count == 0)
            return 1;
        else
            return 2;
    case 7: //blue in one
        if (game.r_count - game.b_count == 0)
            return 2;
        else
            return 1;
    case 8: //red in 2
        if (game.r_count - game.b_count == 0)
            return 3;
        else
            return 4;
    case 9: //blue in 2
        if (game.r_count - game.b_count == 0)
            return 4;
        else
            return 3;
    }
    return 0;
}
bool heuristicEvaluation(Game& game, char pawn, char pawn2)
{
    if (F_is_game_over(game, pawn)) return true;
    else if (F_is_game_over(game, pawn2)) return false;
    else return false;
}

bool minimax(int depth, char pawn, char pawn2, Game& game, bool maximizingPlayer, bool alpha, bool beta)
{
    if (depth == 0) {
        return heuristicEvaluation(game, pawn, pawn2);
    }
    else if (depth != 0)
    {
        if (heuristicEvaluation(game, pawn, pawn2))
        {
            return false;
        }
    }

    if (maximizingPlayer)
    {
        bool maxEval = false;
        for (int i = 0; i < game.BoardSize; i++) {
            for (int j = 0; j < game.BoardSize; j++)
            {
                if (game.array[i][j] == ' ')
                {
                    game.array[i][j] = pawn;
                    bool eval = minimax(depth - 1, pawn, pawn2, game, false, alpha, beta);
                    maxEval = max(maxEval, eval);
                    alpha = max(alpha, eval);
                    game.array[i][j] = ' ';
                    if (beta <= alpha) break;
                }
            }
            if (beta <= alpha) break;
        }
        return maxEval;
    }
    else
    {
        bool minEval = true;
        for (int i = 0; i < game.BoardSize; i++) {
            for (int j = 0; j < game.BoardSize; j++)
            {
                if (game.array[i][j] == ' ')
                {
                    game.array[i][j] = pawn2;
                    bool eval = minimax(depth - 1, pawn, pawn2, game, true, alpha, beta);
                    minEval = min(minEval, eval);
                    beta = min(beta, eval);
                    game.array[i][j] = ' ';
                    if (beta <= alpha) break;
                }
            }
            if (beta <= alpha) break;
        }
        return minEval;
    }
}

bool F_can_win_with_perfect_opponent(Game& game, int maxDepth, char pawn, int moveCount)
{
    char pawn2;
    bool result = false;
    if (pawn == 'r') {
        pawn2 = 'b';
    }
    else
    {
        pawn2 = 'r';
    }
    if (game.BoardSize == 2 && game.b_count + game.b_count == 0)
    {
        game.array[0][0] = pawn;

        result = minimax(maxDepth - 1, pawn, pawn2, game, false, false, true);
        game.array[0][0] = ' ';
    }
    else {

        if (lastMovement(game) == 'b' && pawn == 'b')
        {
            result = minimax(maxDepth, pawn, pawn2, game, false, 0, 1);
        }
        else if (lastMovement(game) == 'r' && pawn == 'r')
        {
            result = minimax(maxDepth, pawn, pawn2, game, false, 0, 1);
        }
        else if (lastMovement(game) == 'r' && pawn == 'b')
        {
            result = minimax(maxDepth, pawn, pawn2, game, true, 0, 1);
        }
        else if (lastMovement(game) == 'b' && pawn == 'r')
        {
            result = minimax(maxDepth, pawn, pawn2, game, true, 0, 1);
        }
    }

    return result;
}


void ExecuteCommand(char token[50], Game& game)
{

    if (strcmp(token, Commands::c1) == 0) printf("%d\n", game.BoardSize);
    else if (strcmp(token, Commands::c2) == 0) printf("%d\n", game.b_count + game.r_count);
    else if (strcmp(token, Commands::c3) == 0)
    {
        if (F_is_board_correct(game)) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    else if (strcmp(token, Commands::c4) == 0)
    {
        if (F_is_board_correct(game)) {
            if (F_is_game_over(game, 'r'))cout << "YES RED" << endl;
            else if (F_is_game_over(game, 'b')) cout << "YES BLUE" << endl;
            else cout << "NO" << endl;
        }
        else cout << "NO" << endl;
    }
    else if (strcmp(token, Commands::c5) == 0)
    {
        if (game.b_count + game.r_count == 0) cout << "YES" << endl << endl;
        else
        {
            if (F_is_board_correct(game))
            {
                if (F_is_game_possible(game)) cout << "YES" << endl << endl;
                else cout << "NO" << endl << endl;
            }
            else cout << "NO" << endl << endl;
        }

    }
    else if (strcmp(token, Commands::c6) == 0)
    {
        if (F_is_game_over(game, 'r') || F_is_game_over(game, 'b')) cout << "NO" << endl;
        else
        {
            if (F_is_board_correct(game))
            {
                int depth = depthCheck(6, game);
                int moveCount = 1;
                if (F_can_win_with_naive_opponent(game, depth, 'r', moveCount)) cout << "YES" << endl;
                else cout << "NO" << endl;
            }
            else cout << "NO" << endl;
        }
    }
    else if (strcmp(token, Commands::c7) == 0)
    {
        if (F_is_game_over(game, 'r') || F_is_game_over(game, 'b')) cout << "NO" << endl;
        else
        {
            if (F_is_board_correct(game))
            {
                int depth = depthCheck(7, game);
                int moveCount = 1;
                if (F_can_win_with_naive_opponent(game, depth, 'b', moveCount)) cout << "YES" << endl;
                else cout << "NO" << endl;
            }
            else cout << "NO" << endl;
        }
    }
    else if (strcmp(token, Commands::c8) == 0)
    {
        if (game.x == 0) {
            cout << "NO" << endl << endl;
            game.x = 1;
        }
        else
        {
            if (game.BoardSize == 1)
            {
                cout << "NO" << endl;
            }
            else if (F_is_game_over(game, 'r') || F_is_game_over(game, 'b')) cout << "NO" << endl;
            else
            {
                if (game.BoardSize == 1) {
                    cout << "NO" << endl;
                }
                else
                {
                    if (F_is_board_correct(game))
                    {
                        int depth = depthCheck(8, game);
                        int moveCount = 2;
                        if (F_can_win_with_naive_opponent(game, depth, 'r', moveCount)) cout << "YES" << endl;
                        else cout << "NO" << endl;
                    }
                    else cout << "NO" << endl;
                }
            }
        }
    }


    else if (strcmp(token, Commands::c9) == 0)
    {
        if (F_is_game_over(game, 'r') || F_is_game_over(game, 'b')) cout << "NO" << endl << endl;
        else
        {
            if (F_is_board_correct(game))
            {
                int depth = depthCheck(9, game);
                int moveCount = 2;
                if (F_can_win_with_naive_opponent(game, depth, 'b', moveCount)) cout << "YES" << endl << endl;
                else cout << "NO" << endl << endl;
            }
            else cout << "NO" << endl << endl;
        }
    }


    else if (strcmp(token, Commands::c10) == 0)
    {

        if (F_is_game_over(game, 'r') || F_is_game_over(game, 'b')) cout << "NO" << endl;
        else
        {
            if (F_is_board_correct(game))
            {
                int depth = depthCheck(6, game);
                int moveCount = 1;
                if (F_can_win_with_naive_opponent(game, depth, 'r', moveCount))
                {
                    if (F_can_win_with_perfect_opponent(game, depth, 'r', moveCount)) cout << "YES" << endl;
                    else cout << "NO" << endl;
                }
                else cout << "NO" << endl;

            }
            else cout << "NO" << endl;
        }
    }


    else if (strcmp(token, Commands::c11) == 0)
    {
        if (F_is_game_over(game, 'r') || F_is_game_over(game, 'b')) cout << "NO" << endl;
        else
        {
            if (F_is_board_correct(game))
            {
                int depth = depthCheck(7, game);
                int moveCount = 1;
                if (F_can_win_with_naive_opponent(game, depth, 'b', moveCount))
                {
                    if (F_can_win_with_perfect_opponent(game, depth, 'b', moveCount)) cout << "YES" << endl;
                    else cout << "NO" << endl;
                }
                else cout << "NO" << endl;
            }
            else cout << "NO" << endl;
        }
    }


    else if (strcmp(token, Commands::c12) == 0)
    {

        if (F_is_game_over(game, 'r') || F_is_game_over(game, 'b')) cout << "NO" << endl;
        else
        {
            if (game.BoardSize == 1) {
                cout << "NO" << endl;
            }
            else
            {
                if (F_is_board_correct(game))
                {
                    int depth = depthCheck(8, game);
                    int moveCount = 2;
                    if (F_can_win_with_naive_opponent(game, depth, 'r', moveCount))
                    {
                        if (F_can_win_with_perfect_opponent(game, depth, 'r', moveCount)) cout << "YES" << endl;
                        else cout << "NO" << endl;
                    }
                    else cout << "NO" << endl;
                }
                else cout << "NO" << endl;
            }
        }
    }


    else if (strcmp(token, Commands::c13) == 0)
    {
        if (F_is_game_over(game, 'r') || F_is_game_over(game, 'b')) cout << "NO" << endl << endl;
        else
        {
            if (F_is_board_correct(game))
            {
                int depth = depthCheck(9, game);
                int moveCount = 2;
                if (F_can_win_with_naive_opponent(game, depth, 'b', moveCount))
                {
                    if (F_can_win_with_perfect_opponent(game, depth, 'b', moveCount)) cout << "YES" << endl << endl;
                    else cout << "NO" << endl << endl;
                }
                else cout << "NO" << endl << endl;

            }
            else cout << "NO" << endl << endl;
        }
    }

    else cout << "ERROR" << endl << endl;

}

int main()
{

    struct Game game;
    input in;

    char token[50];

    while ((in.sign = getchar()) != EOF)
    {
        switch (in.sign)
        {
        case ' ':
            cleanArr(in, game);
            game.BoardSize = BoardCounter(in);
            SaveToArray(game, in);
        case '\n':
            continue;
        default:
            if (in.sign > 65 && in.sign < 90)
            {
                createCommad(token, in.sign);
                ExecuteCommand(token, game);
            }

        }
    }

    return 0;
}



