import matplotlib.pyplot as plt
import numpy as np
from enum import Enum

class Plot():
	def __init__(self):
		self.fig, self.ax = plt.subplots()
		self.ax.set_xlim([-1, 1])
		self.ax.set_ylim([-1, 1])
		self.ax.set_aspect('equal')

	def robot(self, points, state):
		center = state[:2]
		points = np.vstack([points, points[0]])
		self.ax.plot(points[:,0], points[:,1], c = 'darkorange', linewidth = 3)
		self.ax.scatter(*center, c='r')

class Robot():
	def __init__(self):
		self.state = None
		self.robot_body_points = None
		self.plot = Plot()
		self.dt = 1.

	def show(self):
		self.plot.robot(self.robot_body_points, self.state)

	def reset(self):
		self.state = np.array([0., 0., 0.]) # x, y, theta
		self.robot_body_points = np.array([[-0.1, 0.1], [-0.1, -0.1], [0.2, 0]])

	def step(self, velocity):
		assert len(velocity) == 3
		
		d_theta = velocity[2]*self.dt
		rot_mat = np.array([[np.cos(d_theta), -np.sin(d_theta)],
					 		[np.sin(d_theta),  np.cos(d_theta)]])
		
		self.state[:2] = (rot_mat @ (self.state[:2] + velocity[:2]))
		self.state[2] += velocity[2]*self.dt 

		self.robot_body_points[0] = (rot_mat @ (self.robot_body_points[0] + velocity[:2]))
		self.robot_body_points[1] = (rot_mat @ (self.robot_body_points[1] + velocity[:2]))
		self.robot_body_points[2] = (rot_mat @ (self.robot_body_points[2] + velocity[:2]))


if __name__ == "__main__":
    robot = Robot()
    robot.reset()
    for _ in range(20):
        robot.step([0.1, 0., 0.2])
        robot.show()
		
    plt.show()


