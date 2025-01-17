#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>

struct Node
{
    int row;
    int col;
    Node* pred = nullptr;
};

bool isNeighbor(const std::vector<std::vector<char>> &maze, int row, int col){
    int rows = maze.size();
    int cols = maze[0].size();
    return row >= 0 && row < rows && col >= 0 && col < cols && maze[row][col] == '.';
}

void printMaze(const std::vector<std::vector<char>> &maze){
    const int rows = maze.size();
    const int cols = maze[0].size();

    for (int row =0 ; row < rows ; row++){
        for (int col = 0 ; col < cols ; col++){
            std::cout << maze[row][col] << " ";
        }
        std::cout << '\n';
    }
}

const std::map<std::pair<int,int>, char> dirMap = {{{-1, 0}, 'U'},  // up
                                                   {{+1, 0}, 'D'},  // down
                                                   {{ 0,-1}, 'L'},  // left
                                                   {{ 0,+1}, 'R'}}; // right

int main(){
    std::vector<std::vector<char>> maze = {
        {'.', '.', '.', '.', '.', '|', '.', '.', '.', '.', '.'},
        {'.', '.', '|', '.', '.', '|', '.', '.', '|', '.', '.'},
        {'.', '.', '|', '.', '.', '|', '.', '.', '|', '.', '.'},
        {'.', '.', '.', '.', '.', '|', '.', '.', '|', '.', '.'},
        {'|', '.', '.', '.', '|', '|', '.', '.', '|', '.', '.'},
        {'|', '.', '.', '.', '.', '.', '|', '.', '|', '.', '.'},
        {'.', '.', '|', '.', '.', '|', '.', '.', '|', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '|', '.', '.'}
    };
    
    int rows = maze.size();
    int cols = maze[0].size();

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::queue<Node*> q;

    Node* start_node = new Node{0, 0};
    Node* goal_node  = new Node{rows-1, cols-1};

    q.push(start_node);
    visited[start_node->row][start_node->col] = true;

    while (!q.empty()){
        Node* curr_node = q.front();
        q.pop();

        // std::cout << "{ " << curr_node->row << "," << curr_node->col << "} --- ";

        if (curr_node->row == goal_node->row &&
            curr_node->col == goal_node->col){

            std::cout << "GOAL REACHED!" << '\n';
            maze[curr_node->row][curr_node->col] = 'X';

            while (curr_node != nullptr){                
                if (curr_node->pred){
                    int d_row = curr_node->row - curr_node->pred->row; // change in row
                    int d_col = curr_node->col - curr_node->pred->col; // change in col
                    maze[curr_node->pred->row][curr_node->pred->col] = dirMap.find({d_row, d_col})->second;
                }
                curr_node = curr_node->pred;
            }
            printMaze(maze);
            return 0;
        }

        for (const auto &d : dirMap){
            int new_row = curr_node->row + d.first.first;
            int new_col = curr_node->col + d.first.second;

            if (isNeighbor(maze, new_row, new_col) && !visited[new_row][new_col]){

                Node* new_node = new Node{new_row, new_col, curr_node};
                q.push(new_node);
                visited[new_row][new_col] = true;
                // std::cout << "{ " << new_row << "," << new_col << "} | ";
            }
        }
        // std::cout <<  std::endl;
    }

    std::cout << "NO VALID PATH FOUND!" << '\n';
    return 0;

}