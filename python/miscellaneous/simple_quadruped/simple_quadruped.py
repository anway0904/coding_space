import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation


class Plot:
    def __init__(self):
        self.fig, self.ax = plt.subplots()
        self.ax.set_xlim([-1, 1])
        self.ax.set_ylim([-1, 1])
        self.ax.set_aspect('equal')
        self.line, = self.ax.plot([], [], c='darkorange', linewidth=3)
        self.scatter = self.ax.scatter([], [], c='r')

    def update_robot(self, state, hip_len, knee_len):
        hip_angle, knee_angle = state
        
        # Rotation matrices for hip and knee
        hip_rot_mat = np.array([[np.cos(hip_angle), -np.sin(hip_angle)],
                                [np.sin(hip_angle),  np.cos(hip_angle)]])
        
        knee_rot_mat = np.array([[np.cos(knee_angle), -np.sin(knee_angle)],
                                 [np.sin(knee_angle),  np.cos(knee_angle)]])
        
        # Compute joint positions
        hip_loc = hip_rot_mat @ np.array([0., -hip_len])
        knee_loc = hip_loc + knee_rot_mat @ np.array([0., -knee_len])

        # Update plot elements
        self.line.set_data([0, hip_loc[0], knee_loc[0]], [0, hip_loc[1], knee_loc[1]])
        self.scatter.set_offsets([[0, 0], hip_loc, knee_loc])
        return self.line, self.scatter


class Quadruped:
    def __init__(self):
        self.plot = Plot()
        self.HIP_LEN = 0.5
        self.KNEE_LEN = 0.4
        self.time = 0

    def update(self, frame):
        self.time += 0.05  # Simulate time progression
        hip_angle = 0.8 * np.sin(2 * np.pi * self.time)  # Oscillating hip
        knee_angle = 0.4 * np.cos(2 * np.pi * self.time)  # Oscillating knee
        return self.plot.update_robot((hip_angle, knee_angle), self.HIP_LEN, self.KNEE_LEN)


if __name__ == "__main__":
    quadruped = Quadruped()
    ani = animation.FuncAnimation(quadruped.plot.fig, quadruped.update, frames=10, interval=50, blit=True)
    plt.show()
