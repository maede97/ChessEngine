# ChessEngine
[![Build](https://img.shields.io/github/workflow/status/maede97/ChessEngine/Check%20Unittests)](https://github.com/maede97/ChessEngine)
[![Documentation](https://img.shields.io/github/workflow/status/maede97/ChessEngine/Creates%20and%20deploys%20Documentation?label=Documentation)](https://maede97.github.io/ChessEngine)

My try in creating a chess engine from scratch.

We shall see how far this goes...

## Features (Work in Progress)
- Chess Engine
- Unit tests
- GUI frontend

## GUI-Frontend
In order to build the frontend, you need to enable the CMake flag `BUILD_GUI`:
```
cmake .. -DBUILD_GUI=ON
make
./gui/ChessEngineGui
```
If the build process fails, make sure that you have `mesa-common-dev` installed:
```
sudo apt-get install mesa-common-dev
```

## Unit tests
Build the project and run the `unittests` binary:
```
cmake ..
make
./tests/unittests
```
