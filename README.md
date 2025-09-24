# Progress Bar with Observer Pattern - SFML Demo

This project implements a resource loading system with a progress bar visualization using the Observer design pattern and SFML graphics library.

## Features

- **Observer Pattern Implementation**: Clean separation between resource loading logic and UI visualization
- **Resource Loader**: Loads multiple files with progress tracking
- **SFML Progress Bar**: Real-time visual progress bar with status updates
- **Thread-Safe**: Resource loading runs in separate thread while UI remains responsive

## Components

### Observer Pattern (`Observer.h`)
- `IObserver`: Interface for objects that want to receive progress notifications
- `ISubject`: Interface for objects that notify observers about progress

### Resource Loader (`ResourceLoader.h/.cpp`)
- Implements `ISubject` interface
- Manages a list of resource files to load
- Simulates loading process with progress updates
- Notifies all attached observers about progress changes

### Progress Bar Visualizer (`ProgressBarVisualizer.h/.cpp`)
- Implements `IObserver` interface
- Uses SFML to render a graphical progress bar
- Updates visual representation based on loading progress
- Displays progress percentage and status text

### Main Application (`main.cpp`)
- Creates SFML window
- Sets up observer relationships
- Demonstrates the complete loading process
- Handles user input (ESC to exit)

## Building and Running

### Requirements
- C++17 compiler
- SFML 2.6+ development libraries
- CMake 3.10+

### Build Instructions
```bash
mkdir build
cd build
cmake ..
make
```

### Run
```bash
./progress_bar_demo
```

### Console Test
A console-only test is also available:
```bash
g++ -std=c++17 -I. test_console.cpp ResourceLoader.cpp -o test_console
./test_console
```

## Design Patterns Used

### Observer Pattern
- **Subject**: `ResourceLoader` notifies observers about progress changes
- **Observer**: `ProgressBarVisualizer` receives and reacts to progress updates
- **Benefits**: Loose coupling between loading logic and UI, easy to add new observers

## Demo Functionality

1. Application creates 5 dummy resource files
2. ResourceLoader loads each file with simulated processing time
3. Progress bar updates in real-time showing:
   - Current file being loaded
   - Overall progress percentage
   - Visual progress bar fill
4. Application automatically closes when loading completes (or ESC key pressed)

## Key Features Demonstrated

- Real-time progress updates using Observer pattern
- Multi-threaded resource loading
- SFML graphics rendering
- Clean separation of concerns
- Professional progress bar UI with status text
