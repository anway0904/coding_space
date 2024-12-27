import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import convolve2d

# Define the grid size
GRID_SIZE = (100, 100)

# Initialize a random grid
def initialize_grid(size):
    return np.random.choice([0, 1], size=size, p=[0.8, 0.2])  # 80% dead, 20% alive

# Calculate the next generation using convolution
def get_next_generation(grid):
    # Define the convolution kernel
    kernel = np.array([[1, 1, 1],
                       [1, 0, 1],
                       [1, 1, 1]])

    # Count neighbors using 2D convolution
    neighbor_count = convolve2d(grid, kernel, mode='same', boundary='wrap')

    # Apply the rules of Conway's Game of Life
    new_grid = (neighbor_count == 3) | ((grid == 1) & (neighbor_count == 2))

    return new_grid.astype(int)

# Main function to run the game
def run_game_of_life(grid_size, generations, interval=0.1):
    grid = initialize_grid(grid_size)

    # Setup the plot
    fig, ax = plt.subplots()
    matrix = ax.imshow(grid, cmap="binary")
    plt.title("Conway's Game of Life")
    plt.axis('off')
    plt.ion()

    # Iterate through generations
    for _ in range(generations):
        matrix.set_data(grid)  # Update the plot with the current grid
        plt.pause(interval)  # Pause for visualization

        grid = get_next_generation(grid)  # Compute the next generation

    plt.ioff()
    plt.show()

# Run the game
if __name__ == "__main__":
    run_game_of_life(grid_size=GRID_SIZE, generations=1000, interval=0.05)
