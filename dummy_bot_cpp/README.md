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
Source base ROS:
```
source /opt/ros/humble/setup.bash
```
Build, activate Obelisk settings, and source it all using one command:
```
obk
```

In the workspace (i.e. in `obelisk_examples`) build this package:
```
colcon build --symlink-install --parallel-workers $(nproc) --packages-select dummy_bot_cpp
```
Source the generated bash script after building:
```
source install/setup.bash
```
Now we can launch the stack:
```
obk-launch config_file_path="${OBELISK_EXAMPLES_ROOT}/dummy_bot_cpp/dummy_bot_cpp.yaml" device_name=onboard
```
## Dev TODOs
Once `trim-deps` is merged into `main` on `obelisk`, edit this example's Dockerfile accordingly.