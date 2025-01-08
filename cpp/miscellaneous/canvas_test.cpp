#include <cmath>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <string>

class Canvas {
    private:
        std::vector<std::string> grid;
        const int WIDTH;
        const int HEIGHT;

    public:
        Canvas(int width, int height) : WIDTH(width), HEIGHT(height), grid(height, std::string(width, '.')){
            std::cout << "Initializing Canvas with width = " << WIDTH << ", height = " << HEIGHT << '\n';
        }

        std::pair<int, int> shape(){
            return {HEIGHT, WIDTH};
        }

        void clear() {
            for (int x=0 ; x<HEIGHT ; x++){
                for (int y=0 ; y<WIDTH ; y++) {
                    grid[x][y] = '.';
                }
            }
        }

        void render(){
            // std::cout << "\033[2J"; // Clear the screen
            std::cout << "\x1b[H";  // Move cursor to home position (top left)
            for (int x=0 ; x<HEIGHT ; x++){
                for (int y=0 ; y<WIDTH ; y++) {
                    std::cout << grid[x][y] << " ";
                }
                std::cout << '\n';
            }
        }

        void setPixel(int x, int y, char c){
            grid[y][x] = c;
        }
};

int main() {

    Canvas canvas(50, 50);
    canvas.render();
    auto [canvasY, canvasX] = canvas.shape();

    for (int x=0 ; x<canvasX ; x++){
        for (int y=0 ; y<canvasY ; y++) {
            canvas.setPixel(x, y,'A');          
            canvas.render();
            std::this_thread::sleep_for(std::chrono::milliseconds(15));
        }
    }

    return 0;
}