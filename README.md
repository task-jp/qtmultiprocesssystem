# QtMultiProcessSystem

A Qt module for building multi-process application systems with flexible architecture support.

[![Qt 5 on Linux](https://github.com/task-jp/qtmultiprocesssystem/actions/workflows/linux-5.yml/badge.svg)](https://github.com/task-jp/qtmultiprocesssystem/actions/workflows/linux-5.yml)
[![Qt 5 on Windows](https://github.com/task-jp/qtmultiprocesssystem/actions/workflows/windows-5.yml/badge.svg)](https://github.com/task-jp/qtmultiprocesssystem/actions/workflows/windows-5.yml)
[![Qt 5 on macOS](https://github.com/task-jp/qtmultiprocesssystem/actions/workflows/macos-5.yml/badge.svg)](https://github.com/task-jp/qtmultiprocesssystem/actions/workflows/macos-5.yml)

[![Qt 6 on Linux](https://github.com/task-jp/qtmultiprocesssystem/actions/workflows/linux-6.yml/badge.svg)](https://github.com/task-jp/qtmultiprocesssystem/actions/workflows/linux-6.yml)
[![Qt 6 on Windows](https://github.com/task-jp/qtmultiprocesssystem/actions/workflows/windows-6.yml/badge.svg)](https://github.com/task-jp/qtmultiprocesssystem/actions/workflows/windows-6.yml)
[![Qt 6 on macOS](https://github.com/task-jp/qtmultiprocesssystem/actions/workflows/macos-6.yml/badge.svg)](https://github.com/task-jp/qtmultiprocesssystem/actions/workflows/macos-6.yml)

## Overview

QtMultiProcessSystem provides a framework for creating systems where multiple applications run either in separate processes (multi-process) or within a single process (in-process). It supports:

- **Application Manager**: Manages application lifecycle (start, stop, status)
- **Window Manager**: Handles window composition (monolithic or Wayland-based)
- **Plugin Architecture**: Applications are loaded as Qt plugins

## Supported Qt Versions

| Qt Version | Status |
|------------|--------|
| Qt 5.15.x | Supported |
| Qt 6.8.x | Supported |
| Qt 6.10.x | Supported |

## Build

### Prerequisites

- Qt 5.15+ or Qt 6.8+
- CMake 3.16+
- C++17 compiler

### Qt 6

```bash
mkdir build && cd build
qt-configure-module ..
cmake --build .
```

### Qt 5

```bash
mkdir build && cd build
qmake ..
make
```

## Usage

### Running the Launcher

```bash
# Single-process mode (in-process)
./bin/qmpslauncher -a inprocess -w monolithic -c example

# Multi-process mode (separate processes)
./bin/qmpslauncher -a qprocess -w monolithic -c example

# Wayland compositor mode (Linux only, Qt 6)
./bin/qmpslauncher -a wayland -w wayland -c example
```

### Options

- `-a, --application-manager`: Application manager backend (`inprocess`, `qprocess`, `wayland`, `systemd`)
- `-w, --window-manager`: Window manager backend (`monolithic`, `wayland`)
- `-c, --category`: Application category to load

## License

LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only
