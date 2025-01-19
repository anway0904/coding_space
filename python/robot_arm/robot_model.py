from dataclasses import dataclass
from enum import Enum
from typing import List, Dict
from math import pi
import matplotlib.pyplot as plt
from scipy.spatial.transform import Rotation as R
import numpy as np

@dataclass
class Joint():
    name : str
    axis : str          # "x y z"
    limits : str        # "upper lower"
    parent : str        # name of parent joint
    xyz : str           # "x y z" translation wrt parent (in meters)
    rpy : str           # "r p y" rotation wrt parent (in radians)
    state : float = 0.  # current rotation angle in radians

@dataclass
class TFInfo():
    parent : str
    child : str
    R : np.ndarray  # 3x3 matrix
    T : np.ndarray  # 3x1 vector
    H : np.ndarray  # 4x4 matrix (homogeneous)
    P : np.ndarray  # 3x4 matric (R and T)

class TF():
    @staticmethod
    def get_info(joint : Joint):
        roll, pitch, yaw = map(float, joint.rpy.split())
        tx, ty, tz = map(float, joint.xyz.split())

        curr_angle = joint.state
        joint_rotation = np.array([[np.cos(curr_angle), -np.sin(curr_angle), 0],
                                   [np.sin(curr_angle),  np.cos(curr_angle), 0],
                                   [        0,                    0,         1]])
        
        rotation_matrix =  np.array(R.from_euler('xyz', [roll, pitch, yaw]).as_matrix()) @ joint_rotation

        transformation_matrix = np.eye(4)
        transformation_matrix[:3, :3] = rotation_matrix  # Top-left 3x3 is rotation
        transformation_matrix[:3, 3] = [tx, ty, tz]      # Top-right 3x1 is translation

        translation_vector = np.array([[tx], [ty], [tz]])
        print(transformation_matrix)

        return TFInfo(parent = joint.parent,
                      child = joint.name,
                      R = rotation_matrix,
                      T = translation_vector,
                      H = transformation_matrix,
                      P = transformation_matrix[:3,:])

class Plot():
    def __init__(self):
        self.fig = plt.figure()
        self.ax = self.fig.add_subplot(111, projection='3d')
        self.ax.set_xlabel('X axis')
        self.ax.set_ylabel('Y axis')
        self.ax.set_zlabel('Z axis')
        self.ax.set_xlim(-2, 2)
        self.ax.set_ylim(-2, 2)
        self.ax.set_zlim(0, 2)

    def joint_frames(self, joints: Dict[str, Joint]):
        # Identity rotation, translation
        H_wrt_I = []  # To store homogeneous transforms relative to the base frame
        x_axis = np.array([0.2, 0, 0, 0])  # Homogeneous coordinate
        y_axis = np.array([0, 0.2, 0, 0])
        z_axis = np.array([0, 0, 0.2, 0])

        for idx, joint in enumerate(joints.values()):
            joint_tf = TF.get_info(joint)
            prev_tf = H_wrt_I[-1] if H_wrt_I else np.eye(4)
            current_tf = prev_tf @ joint_tf.H  # Forward transformation
            H_wrt_I.append(current_tf)

            # Extract the position of the joint
            joint_position = current_tf[:3, 3]

            # Scatter plot for joint position
            self.ax.scatter(*joint_position, color="black", s=20, label=joint.name if idx == 0 else "")

            # Transform and visualize axes
            x_axis_tf = current_tf @ x_axis
            y_axis_tf = current_tf @ y_axis
            z_axis_tf = current_tf @ z_axis

            self.ax.quiver(*joint_position, *x_axis_tf[:3], color='r', arrow_length_ratio=0.1)
            self.ax.quiver(*joint_position, *y_axis_tf[:3], color='g', arrow_length_ratio=0.1)
            self.ax.quiver(*joint_position, *z_axis_tf[:3], color='b', arrow_length_ratio=0.1)
            self.ax.text(*joint_position + 0.01, joint.name, color='black')


class RobotArm():
    def __init__(self) -> None:
        self.joints : Dict[str, Joint] = {}

    def add_joint(self, joint : Joint) -> None:
        self.joints[joint.name] = joint

    def get_joint(self, name : str) -> Joint:
        joint = self.joints.get(name, False)
        if not joint:
            raise NameError(f"{name} joint not found!")
        
        return joint
    
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
    
    # Initial Plot
    print("Initial Plot with Joint States:")
    plot = Plot()
    plot.joint_frames(ur5.joints)

    # Home position
    ur5.get_joint("base").state     = np.pi/2
    ur5.get_joint("shoulder").state = np.pi/2
    # ur5.get_joint("elbow").state    = 3*np.pi
    # ur5.get_joint("wrist1").state   = 3*np.pi
    # ur5.get_joint("wrist2").state   = np.pi/2
    # ur5.get_joint("wrist3").state   = 0


    print("Updated Plot with Changed Joint States:")
    plot = Plot()
    plot.joint_frames(ur5.joints)
    plt.show()