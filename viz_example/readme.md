# Running the example
This example is currently only half-baked, but nonetheless shows the robots moving.

Make sure Obelisk is sourced:
```
source $OBELISK_ROOT/obelisk_ws/install/setup.sh
```

In the workspace (i.e. in `obelisk-examples`) build this package:
```
colcon build --symlink-install --parallel-workers $(nproc) --packages-select viz_example
```
Or you can build all the example packages:
```
colcon build --symlink-install --parallel-workers $(nproc)
```
Source the generated bash script after building:
```
source install/setup.bash
```
Now we can launch the stack (this will use a config file in the main Obelisk repo):
```
obk-launch config_file_path=dummy_cpp_viz.yaml device_name=onboard
```

Now in another terminal we need to boot up the node that will give us our fake data.

Make sure Obelisk is sourced:
```
source $OBELISK_ROOT/obelisk_ws/install/setup.sh
```

Source the generated bash script:
```
source install/setup.bash
```

Launch the node: 
```
ros2 launch viz_example viz_bringup.launch.py
```

Now we need to make sure Rviz is configured properly. Make sure the following is true:
- There need to be two `RobotModel`s
- One robot should have a "Description topic" of "/robot_description" and a "tf_prefix" of "g1" 
- The other robot should have a "Description topic" of "/go2_description" and a "tf_prefix" of "go2"

You should now see the robots moving. If you don't see them moving, then verify that the fixed frame is `world`.