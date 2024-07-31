# Running the dummy bot C++ example
Do initial setup of environment variables exposed to Docker:
```
bash setup.sh
```
Start the docker container:
```
cd docker
docker compose -f docker-compose.yml run --build obelisk_examples
```
Source base ROS, build Obelisk, activate Obelisk settings, and source Obelisk using one command:
```
obk
```

In the workspace (i.e. in `obelisk_examples`) build this package:
```
# build only 1 package
colcon build --symlink-install --parallel-workers $(nproc) --packages-select dummy_bot_cpp

# build all dummy packages
colcon build --symlink-install --parallel-workers $(nproc)
```
Source the generated bash script after building:
```
source install/setup.bash
```
Now we can launch the stack:
```
obk-launch config_file_path="${OBELISK_EXAMPLES_ROOT}/dummy_bot_cpp/dummy_bot_cpp.yaml" device_name=onboard
```
DEBUG:
```
# window 1
obk-launch config_file_path=dummy_cpp_zed.yaml device_name=onboard

# different window (custom ros2 topic hz node just to verify that hz isn't running very slowly)
ros2 run dummy_utils message_counter --ros-args -p topic:=/obelisk/dummy/zed2
```
