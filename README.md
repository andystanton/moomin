# moomin [![Build Status](https://travis-ci.org/andystanton/moomin.svg?branch=master)](https://travis-ci.org/andystanton/moomin)

A C++11 graphics/physics experiment. With unit tests and everything.

## Requirements

- Clang >= 3.4
- CMake >= 2.8
- Rake >= 10

## Quick Start

```
git clone https://github.com/andystanton/moomin.git --recursive
cd moomin
rake
bin/moomin
```

## Build Tools

### CMake

CMake is used to generate makefiles for building and testing the application.

The build process is as follows:

```
mkdir -p build && cd build >/dev/null 2>&1 && cmake .. "$@"
cd ..
make -C build
make -C build test
cat build/Testing/Temporary/LastTest.log
```

CMake can also be used to [generate project files for IDEs](https://github.com/andystanton/moomin/wiki/Generating%20Xcode%20Project%20Files).


### Rake

Rake is used to provide an easy way to invoke CMake and make tasks.

| Command        | Operation                                                        |
| -------------- | ---------------------------------------------------------------- |
| rake clean     | Erases all files listed in .gitignore.                           |
| rake configure | Generates makefiles using CMake.                                 |
| rake compile   | Executes the generated makefiles to build application and tests. |
| rake test      | Executes the unit tests.                                         |
| rake start     | Starts the application.                                          |
| rake all       | Alias for ```rake clean configure compile test```                |
| rake           | Alias for ```rake configure compile test```                      |
