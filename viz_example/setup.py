import os
import glob
from setuptools import find_packages, setup

package_name = 'viz_example'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join("share", package_name, "launch"), glob.glob(os.path.join("launch", "*launch.[pxy][yma]*"))),

    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='zolkin',
    maintainer_email='zach.olkin@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "state_publisher = viz_example.state_publisher:main",
        ],
    },
)
