from dataclasses import dataclass
from enum import Enum
from typing import List, Dict
from math import pi
import matplotlib.pyplot as plt
from scipy.spatial.transform import Rotation as R
import numpy as np

# # For future expansion
# class JointType(Enum):
#     REVOLUTE = 0
#     PRISMATIC = 1
#     CONTINUOUS = 2

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

        rotation_matrix = np.array(R.from_euler('xyz', [roll, pitch, yaw]).as_matrix())

        transformation_matrix = np.eye(4)
        transformation_matrix[:3, :3] = rotation_matrix  # Top-left 3x3 is rotation
        transformation_matrix[:3, 3] = [tx, ty, tz]      # Top-right 3x1 is translation

        translation_vector = np.array([[tx], [ty], [tz]])

        return TFInfo(parent = joint.parent,
                      child = joint.name,
                      R = rotation_matrix,
                      T = translation_vector,
                      H = transformation_matrix,
                      P = transformation_matrix[:3,:])

class Plot():
    def __init__(self):
        self.fig = plt.figure()
        self.ax  = self.fig.add_subplot(111, projection='3d')
        self.ax.set_xlabel('X axis')
        self.ax.set_ylabel('Y axis')
        self.ax.set_zlabel('Z axis')

    def joint_frames(self, joints : Dict[str,Joint]):

        # Identity rotation, translation 
        T = np.zeros([3, 1])
        R = np.eye(3)

        H_wrt_I = []

        for idx, joint in enumerate(joints.values()):
            joint_tf = TF.get_info(joint)
            prev_tf = H_wrt_I[idx-1] if H_wrt_I else np.eye(4)
            H_wrt_I.append(prev_tf @ joint_tf.H)
            self.ax.scatter(*np.linalg.inv(H_wrt_I[idx])[:3,3])

            print(np.linalg.inv(H_wrt_I[idx])[:3,3])
            

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
    
    # print(TF.get_info(ur5.get_joint("shoulder")))

    plot = Plot()
    plot.joint_frames(ur5.joints)
    plt.show()