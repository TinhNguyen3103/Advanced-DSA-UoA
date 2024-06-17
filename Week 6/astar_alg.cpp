#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <map>
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
    int board[BOARD_AREA]; // The puzzle board configuration, represented as an array of integers.
    int blank_tile;        // The index of the blank tile in the puzzle.
    int md;                // The Manhattan distance heuristic value for this puzzle configuration.
    int cost;              // The cost (number of steps) to reach this configuration from the initial state.

    // Operator overload for comparing two Puzzle structs.
    // It is used for keeping track of visited states in the search process.
    bool operator<(const Puzzle &p) const
    {
        for (int i = 0; i < BOARD_AREA; i++)
        {
            if (board[i] == p.board[i])
                continue;
            return board[i] < p.board[i];
        }
        return false;
    }
};

struct State
{
    Puzzle puzzle; // The current puzzle configuration.
    int estimated; // The estimated cost (heuristic + actual cost) to reach the goal from this state.

    // Operator overload for comparing two State structs.
    // It is used for maintaining the priority queue during the A* search.
    bool operator<(const State &s) const
    {
        return estimated > s.estimated;
    }
};

int manhattan_distance[BOARD_AREA][BOARD_AREA]; // 2D array to store Manhattan distances between tiles.
priority_queue<State> pqueue;                   // Priority queue to manage states during the A* search.
map<Puzzle, bool> puzzle_map;                   // Map to keep track of visited puzzle configurations.

void initMahattantDistance()
{
    // Calculate and store the Manhattan distance between all pairs of tiles
    for (int i = 0; i < BOARD_AREA; i++)
    {
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

int astar(Puzzle &current_puzzle)
{
    current_puzzle.md = getMahattantDistance(current_puzzle); // Calculate the initial heuristic value for the input puzzle.
    current_puzzle.cost = 0; // Initialize the cost to reach this state from the initial state.

    State initial_state;
    initial_state.puzzle = current_puzzle;
    initial_state.estimated = current_puzzle.md; // The estimated cost is the heuristic cost at the beginning.
    pqueue.push(initial_state); // Push the initial state into the priority queue.

    while (!pqueue.empty())
    {
        State current_state = pqueue.top(); // Get the state with the lowest estimated cost from the priority queue.
        pqueue.pop();

        if (current_state.puzzle.md == 0)
            return current_state.puzzle.cost; // If the heuristic is zero, the goal state is reached, return the cost.

        int current_x, current_y, target_x, target_y;
        current_x = current_state.puzzle.blank_tile / BOARD_SIZE; // Get the x-coordinate of the blank tile.
        current_y = current_state.puzzle.blank_tile % BOARD_SIZE; // Get the y-coordinate of the blank tile.

        // Try moving the blank tile in all four directions (u, l, d, r)
        for (int dir = 0; dir < 4; dir++)
        {
            target_x = current_x + dx[dir]; // Calculate the new x-coordinate after the move in the current direction.
            target_y = current_y + dy[dir]; // Calculate the new y-coordinate after the move in the current direction.

            // Check if the new position is within the puzzle boundaries.
            if (target_x < 0 || target_x >= BOARD_SIZE || target_y < 0 || target_y >= BOARD_SIZE)
                continue;

            Puzzle new_puzzle = current_state.puzzle; // Create a copy of the current puzzle configuration.
            
            // Update the Manhattan distance heuristic after the tile swap.
            new_puzzle.md -= manhattan_distance[target_x * BOARD_SIZE + target_y][new_puzzle.board[target_x * BOARD_SIZE + target_y] - 1];
            new_puzzle.md += manhattan_distance[current_x * BOARD_SIZE + current_y][new_puzzle.board[target_x * BOARD_SIZE + target_y] - 1];

            // Swap the tiles and update the position of the blank tile.
            swap(new_puzzle.board[target_x * BOARD_SIZE + target_y], new_puzzle.board[current_x * BOARD_SIZE + current_y]);
            new_puzzle.blank_tile = target_x * BOARD_SIZE + target_y;

            // If the resulting puzzle configuration is not visited before, proceed with it.
            if (!puzzle_map[new_puzzle])
            {
                puzzle_map[current_state.puzzle] = true; // Mark the current puzzle configuration as visited.
                new_puzzle.cost++; // Increment the cost to reach this new configuration.
                State new_state;
                new_state.puzzle = new_puzzle; // Create a new state with the updated puzzle.
                new_state.estimated = new_puzzle.cost + new_puzzle.md; // Update the estimated cost for the new state.
                pqueue.push(new_state); // Push the new state into the priority queue.
            }
        }
    }

    return -1; // If the queue is empty and no solution is found, return -1.
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

    initMahattantDistance(); 
    cout << astar(initial_puzzle) << endl; 

    return 0;
}
