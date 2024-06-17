#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define BOARD_SIZE 4
#define BOARD_AREA 16
#define BLANK_TILE 0
#define STEP_LIMIT 100

static const int dx[4] = {0, -1, 0, 1};
static const int dy[4] = {1, 0, -1, 0};
static const char direction[4] = {'u', 'l', 'd', 'r'};

struct Puzzle
{
    int board[BOARD_AREA];
    int blank_tile;
    int md; // Manhattan distance heuristic
};

int manhattan_distance[BOARD_AREA][BOARD_AREA];
Puzzle currentPuzzle;
int depthLimit;
int solutionPath[STEP_LIMIT];

void initmanhattan_distance()
{
    for (int i = 0; i < BOARD_AREA; i++)
    {
        // Calculate and store the Manhattan distance between all pairs of tiles.
        for (int j = 0; j < BOARD_AREA; j++)
        {
            manhattan_distance[i][j] = abs(i / BOARD_SIZE - j / BOARD_SIZE) + abs(i % BOARD_SIZE - j % BOARD_SIZE);
        }
    }
}

int getMahattantDistance(Puzzle p)
{
    // Calculate the Manhattan distance heuristic value for the given puzzle configuration.
    int cost = 0;
    for (int i = 0; i < BOARD_AREA; i++)
    {
        if (p.board[i] == BOARD_AREA)
            continue;
        cost += manhattan_distance[i][p.board[i] - 1];
    }

    return cost;
}

// Depth-limited search with A* heuristic using IDA* algorithm
bool depthLimitedSearch(int depth, int prev)
{
    // If the current state is the goal state, return true
    if (currentPuzzle.md == 0)
        return true;

    // Add a heuristic to the current depth and cut a branch if the limit is exceeded
    if (depth + currentPuzzle.md > depthLimit)
        return false;

    int current_x, current_y, target_x, target_y;
    Puzzle tempPuzzle;

    current_x = currentPuzzle.blank_tile / BOARD_SIZE;
    current_y = currentPuzzle.blank_tile % BOARD_SIZE;

    // Try moving the blank tile in all four directions (u, l, d, r)
    for (int dir = 0; dir < 4; dir++)
    {
        target_x = current_x + dx[dir];
        target_y = current_y + dy[dir];
        // Check if the new position is within the puzzle boundaries
        if (target_x < 0 || target_x >= BOARD_SIZE || target_y < 0 || target_y >= BOARD_SIZE)
            continue;
        // Skip moves that undo the previous move (opposite direction)
        if (max(prev, dir) - min(prev, dir) == 2)
            continue;

        tempPuzzle = currentPuzzle;

        // Update the Manhattan distance heuristic after the tile swap.
        currentPuzzle.md -= manhattan_distance[target_x * BOARD_SIZE + target_y][currentPuzzle.board[target_x * BOARD_SIZE + target_y] - 1];
        currentPuzzle.md += manhattan_distance[current_x * BOARD_SIZE + current_y][currentPuzzle.board[target_x * BOARD_SIZE + target_y] - 1];

        // Swap the tiles and update the position of the blank tile.
        swap(currentPuzzle.board[target_x * BOARD_SIZE + target_y], currentPuzzle.board[current_x * BOARD_SIZE + current_y]);
        currentPuzzle.blank_tile = target_x * BOARD_SIZE + target_y;

        // Recursively explore the next state
        if (depthLimitedSearch(depth + 1, dir))
        {
            // If a solution is found, store the direction and return true
            solutionPath[depth] = dir;
            return true;
        }
        // If the current move did not lead to a solution, backtrack
        currentPuzzle = tempPuzzle;
    }
    // If no solution is found for the current depth, return false
    return false;
}

// Main function to perform iterative deepening
string iterativeDeepening(Puzzle initialPuzzle)
{
    // Calculate the Manhattan distance for the initial puzzle state
    initialPuzzle.md = getMahattantDistance(initialPuzzle);

    // Start the depth limit from the Manhattan distance and increment it
    // until the STEP_LIMIT is reached (maximum depth allowed)
    for (depthLimit = initialPuzzle.md; depthLimit < STEP_LIMIT; depthLimit++)
    {
        currentPuzzle = initialPuzzle;

        // Perform depth-limited DFS using IDA*
        if (depthLimitedSearch(0, -100))
        {
            string result = "";
            // If a solution is found, construct the solution string
            for (int i = 0; i < depthLimit; i++)
            {
                result += direction[solutionPath[i]];
            }
            return result;
        }
    }
    // If no solution is found within the depth limit, return "no answer"
    return "no answer";
}

int main()
{
    Puzzle initial_puzzle;

    // Read the initial puzzle configuration from the input.
    for (int i = 0; i < BOARD_AREA; i++)
    {
        cin >> initial_puzzle.board[i];
        if (initial_puzzle.board[i] == BLANK_TILE)
        {
            initial_puzzle.board[i] = BOARD_AREA;
            initial_puzzle.blank_tile = i;
        }
    }

    initmanhattan_distance();
    string result = iterativeDeepening(initial_puzzle);
    cout << result.size() << endl;
    return 0;
}

