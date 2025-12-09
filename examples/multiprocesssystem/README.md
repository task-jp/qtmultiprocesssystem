# QtMultiProcessSystem Examples

## Build

### Qt 6 (CMake)

```bash
mkdir build && cd build
qt-cmake .. -G Ninja -DQT_BUILD_EXAMPLES=ON
ninja
```

### Qt 5 (qmake)

```bash
mkdir build && cd build
qmake ..
make
```

## Run

After building, copy the plugins to the `bin/multiprocesssystem/` directory:

```bash
cd build
mkdir -p bin/multiprocesssystem/application
mkdir -p bin/multiprocesssystem/applicationmanager
mkdir -p bin/multiprocesssystem/windowmanager
mkdir -p bin/multiprocesssystem/watchdogmanager

cp plugins/multiprocesssystem/applicationmanager/*.so bin/multiprocesssystem/applicationmanager/
cp plugins/multiprocesssystem/windowmanager/*.so bin/multiprocesssystem/windowmanager/
cp plugins/multiprocesssystem/watchdogmanager/*.so bin/multiprocesssystem/watchdogmanager/
cp examples/multiprocesssystem/*/lib*.so bin/multiprocesssystem/application/
```

### Single Process Mode (inprocess)

All applications run in the same process with the monolithic window manager:

**Qt 6:**
```bash
LD_LIBRARY_PATH=$PWD/lib:$LD_LIBRARY_PATH \
QML_IMPORT_PATH=$PWD/qml:$QML_IMPORT_PATH \
./bin/qmpslauncher -a inprocess -w monolithic
```

**Qt 5:**
```bash
LD_LIBRARY_PATH=$PWD/lib:$LD_LIBRARY_PATH \
QML2_IMPORT_PATH=$PWD/qml:$QML2_IMPORT_PATH \
./bin/qmpslauncher -a inprocess -w monolithic
```

### Multi Process Mode (qprocess)

Each application runs in a separate process. This mode requires the wayland window manager:

**Qt 6:**
```bash
LD_LIBRARY_PATH=$PWD/lib:$LD_LIBRARY_PATH \
QML_IMPORT_PATH=$PWD/qml:$QML_IMPORT_PATH \
./bin/qmpslauncher -a qprocess -w wayland
```

**Qt 5:**
```bash
LD_LIBRARY_PATH=$PWD/lib:$LD_LIBRARY_PATH \
QML2_IMPORT_PATH=$PWD/qml:$QML2_IMPORT_PATH \
./bin/qmpslauncher -a qprocess -w wayland
```

In multi-process mode:
- The server (system) runs as a Wayland compositor
- Each client application (header, footer, menu, etc.) runs in a separate process
- Applications communicate via D-Bus IPC

Note: For proper window rendering, a Wayland session is recommended. On X11, the IPC works but window compositing may show EGL warnings.

## Command Line Options

- `-a, --application-manager <backend>`: Application Manager backend (default: inprocess)
  - `inprocess`: Single process mode
  - `qprocess`: Multi process mode
  - `systemd`: Systemd service mode
- `-w, --window-manager <backend>`: Window Manager backend (default: monolithic)
- `-d, --watchdog-manager <backend>`: WatchDog Manager backend (default: none)
- `-c, --application-category <category>`: Application category (default: example)
