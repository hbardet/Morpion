# Prerequisites

Before starting, make sure you have the following installed on your machine:

1. **CMake**: [Download here](https://cmake.org/download/)
2. **C++ Compiler**: Ensure you have a compiler installed (GCC, Clang, MSVC, etc.).

## 1. Clone the project

If you haven't cloned the project yet, you can do so via SSH, HTTP, or download the ZIP file.

### Option 1: Clone using SSH

If you have SSH set up, you can clone the project using the following command:

```bash
git clone git@github.com:kevinGLAENTZLIN/R-Type.git
cd R-Type
```

### Option 2: Clone using HTTPS

If you don't have SSH set up, you can clone the project using HTTPS with the following command:

```bash
git clone https://github.com/kevinGLAENTZLIN/R-Type.git
cd R-Type
```

### Option 3: Download ZIP

If you don't have Git installed, you can download the ZIP file by clicking on the green "Code" button on the project page.

## Set Up an SSH Key

If you don't have an SSH key and want to clone the project using SSH, you can follow these guides:

- [Create a GitHub account](https://docs.github.com/en/get-started/start-your-journey/creating-an-account-on-github)
- [Generate a new SSH key](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account)
- [Clone a repository using SSH](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository)

## List of commands

| Command        | Description                                    |
|----------------|------------------------------------------------|
| `setup_vcpkg`  | Set up the path to vcpkg                       |
| `init`         | Initialize the project with CMake              |
| `release`      | Configure the project in Release mode          |
| `debug`        | Configure the project in Debug mode            |
| `build`        | Compile the project                            |
| `test`         | Run the project tests                          |
| `clean`        | Clean generated files                          |
| `reset`        | Reset the project by deleting the `build/` folder |
| `help`         | Display help for the script                    |
| 'full_build'   | Run the full build process                     |


## Example of usage in Linux

```bash
./build.sh setup_vcpkg .
./build.sh init
./build.sh release
./build.sh build
```

Or you can use full build rules

```bash
./build.sh full_build
```

Congratulations! You have successfully built the project. 🎉

If you want to pass in debug mode, you can replace `Release` with `Debug` in the commands above.
Or Reset the project by running the following command:

```bash
./build.sh reset
./build.sh debug
./build.sh build
```

And that's it! You can now use the `build.sh` script to build the project with ease. 🚀

## Example of usage in Windows

If you are using Windows, you can use the `build.bat` script to build the project. Here is an example of how to use it:
The same commands are available in the `build.bat` script as in the `build.sh` script and they do the same thing.
