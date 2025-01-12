from dataclasses import dataclass
from enum import Enum
from typing import List, Dict
from math import pi
import matplotlib.pyplot as plt
from scipy.spatial.transform import Rotation as R
import numpy as np

# For future expansion
class JointType(Enum):
    REVOLUTE = 0
    PRISMATIC = 1
    CONTINUOUS = 2

@dataclass
class Joint():
    name : str
    axis : str          # "x y z"
    limits : str        # "upper lower"
    parent : str        # name of parent joint
    xyz : str           # "x y z" translation wrt parent (in meters)
    rpy : str           # "r p y" rotation wrt parent (in radians)
    state : float = 0.  # current rotation angle in radians


class PlotHelper():
    @staticmethod
    def get_static_tf(joint : Joint):
        roll, pitch, yaw = map(float, joint.rpy.split())
        tx, ty, tz = map(float, joint.xyz.split())

        rotation_matrix = R.from_euler('xyz', [roll, pitch, yaw]).as_matrix()

        transformation_matrix = np.eye(4)
        transformation_matrix[:3, :3] = rotation_matrix  # Top-left 3x3 is rotation
        transformation_matrix[:3, 3] = [tx, ty, tz]      # Top-right 3x1 is translation

        return transformation_matrix

    @staticmethod
    def get_rotation_translation(joint : Joint):
        roll, pitch, yaw = map(float, joint.rpy.split())
        translation_vector = np.array(list(map(float, joint.xyz.split())))

        rotation_matrix = np.array(R.from_euler('xyz', [roll, pitch, yaw]).as_matrix())

        return rotation_matrix, translation_vector

    @staticmethod
    def render_joints(joints : Dict[str,Joint]):
        fig = plt.figure()
        ax  = fig.add_subplot(111, projection='3d')
        ax.set_xlabel('X axis')
        ax.set_ylabel('Y axis')
        ax.set_zlabel('Z axis')

        cumulative_R = np.eye(3)
        frame_center = np.array([0,0,0,1])

        for joint in joints.values():
            R, t = PlotHelper.get_rotation_translation(joint)
            # curr_tf = static_tf @ curr_tf
            # frame_center = curr_tf @ frame_center
            # frame_center/=frame_center[-1]
            R = cumulative_R @ R
            frame_center = R.T @ -t

            # x_axis = static_tf @ np.array([1, 0, 0, 1])
            # y_axis = static_tf @ np.array([0, 1, 0, 1])
            # z_axis = static_tf @ np.array([0, 0, 1, 1])
            x_axis = R.T @ np.array([1, 0, 0])
            y_axis = R.T @ np.array([0, 1, 0])
            z_axis = R.T @ np.array([0, 0, 1])  

            # x_axis/=x_axis[-1]
            # y_axis/=y_axis[-1]
            # z_axis/=z_axis[-1]

            # ax.scatter(frame_center[0], frame_center[1], frame_center[2])

            # ax.quiver(*frame_center[:3], *x_axis[:3], color='r', arrow_length_ratio=0.01)
            # ax.quiver(*frame_center[:3], *y_axis[:3], color='g', arrow_length_ratio=0.01)
            # ax.quiver(*frame_center[:3], *z_axis[:3], color='b', arrow_length_ratio=0.01)

            # Plot the camera origin
            ax.scatter(*frame_center, c='r', marker='o')
            ax.text(*frame_center + 0.1, f"{joint.name}", color='blue')

            # Plot the axes
            ax.quiver(*frame_center, *x_axis, color='r', arrow_length_ratio=0.00001)
            ax.quiver(*frame_center, *y_axis, color='g', arrow_length_ratio=0.00001)
            ax.quiver(*frame_center, *z_axis, color='b', arrow_length_ratio=0.00001)

            limits = np.array([ax.get_xlim3d(),
                               ax.get_ylim3d(),
                               ax.get_zlim3d(),])

            origin = np.mean(limits, axis=1)
            radius =  1 * np.max(np.abs(limits[:, 1] - limits[:, 0]))

            ax.set_xlim3d([origin[0] - radius, origin[0] + radius])
            ax.set_ylim3d([origin[1] - radius, origin[1] + radius])
            ax.set_zlim3d([origin[2] - radius, origin[2] + radius])

        plt.show()


class RobotArm():
    def __init__(self):
        self.joints : Dict[str, Joint] = {}

    def add_joint(self, joint : Joint):
        self.joints[joint.name] = joint

    def view_joints(self):
        PlotHelper.render_joints(self.joints)        
    
    def get_joint_states(self):
        print("Joint States (degrees)\n--------------")
        for joint in self.joints.values():
            print(f"{joint.name} : {joint.state * 180/pi}")

if __name__ == "__main__":
    ur5 = RobotArm()
    ur5.add_joint(Joint(name="base",
                        axis="0 0 1",
                        limits=f"{2*pi} -{2*pi}",
                        parent="",
                        xyz="0 0 0",
                        rpy="0 0 0"))
    
    ur5.add_joint(Joint(name="shoulder",
                        axis="0 0 1",
                        limits=f"{2*pi} -{2*pi}",
                        parent="base",
                        xyz="0 0 0",
                        rpy=f"{pi/2} 0 0"))
    
    ur5.add_joint(Joint(name="elbow",
                        axis="0 0 1",
                        limits=f"{2*pi} -{2*pi}",
                        parent="shoulder",
                        xyz="-0.425 0 0",
                        rpy="0 0 0"))
    
    ur5.add_joint(Joint(name="wrist1",
                        axis="0 0 1",
                        limits=f"{2*pi} -{2*pi}",
                        parent="elbow",
                        xyz="-0.3922 0 0.1333",
                        rpy="0 0 0"))
    
    ur5.add_joint(Joint(name="wrist2",
                        axis="0 0 1",
                        limits=f"{2*pi} -{2*pi}",
                        parent="wrist1",
                        xyz="0 -0.0997 0",
                        rpy=f"{pi/2} 0 0"))
    
    ur5.add_joint(Joint(name="wrist3",
                        axis="0 0 1",
                        limits=f"{2*pi} -{2*pi}",
                        parent="wrist2",
                        xyz="0 -0.0997 0",
                        rpy=f"{pi/2} {2*pi} {2*pi}"))
    
    ur5.view_joints()