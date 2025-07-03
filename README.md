# C++ Sort

This code was a way for me to practice writing modern C++ code by implementing common sorting algorithms using [what I created with Typescript](https://github.com/richardwalenga/typescriptsort) as a guide. I have logging in [main.cpp](main.cpp) which times the implementations against the same large array of random ints.

## First Steps

This project requires version 3.19 or greater of the cross-platform build tool CMake in order for CMakePresets.json to be available. This command, if it returns something, will tell one which version is installed:
```
cmake --version
```

For a tool like VSCode, it would be a good idea to specify the path to your C++ compiler in your user's settings.json under the key: "C_Cpp.default.compilerPath".

Create a CMakeUserPresets.json like this to customize the build for your machine. It would look something like this:
```
{
    "version": 8,
    "configurePresets": [
        {
            "name": "mydefault",
            "inherits": "default",
            "generator": "MinGW Makefiles",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Debug",
                "CMAKE_C_COMPILER": "path to gcc.exe",
                "CMAKE_CXX_COMPILER": "path to g++.exe"
            }
        }
    ]
}
```

For VSCode, one now needs to select the preset mydefault which is in CMakeUserPresets.json [following these instructions](https://code.visualstudio.com/docs/cpp/cmake-linux#_configure-using-cmake-presets).

A normal build involves running:
```
mkdir build
mkdir build/mydefault
cd build/mydefault
cmake ../.. --preset mydefault
cmake --build . --target all
```

For Visual Studio Code users, there are tasks to build and clean which can only be effective if the [CMake Tools extension is installed](https://github.com/microsoft/vscode-cmake-tools/blob/main/docs/build.md). [Visual Studio users should follow these directions for building](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170).

## Running

To run it, just execute this:
```
cd build/mydefault
./cppsort
```

For convenience I added a VSCode task called "run" which effectively does the same thing.