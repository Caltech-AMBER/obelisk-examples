# Running the dummy bot C++ example
Make sure Obelisk is sourced:
```
source $OBELISK_ROOT/obelisk_ws/install/setup.sh
```

In the workspace (i.e. in `obelisk-examples`) build this package:
```
colcon build --symlink-install --parallel-workers $(nproc) --packages-select dummy_bot_cpp
```
Or you can build all the example packages:
```
colcon build --symlink-install --parallel-workers $(nproc)
```

Now we can launch the stack:
```
obk-launch config_file_path=dummy_cpp.yaml device_name=onboard
```