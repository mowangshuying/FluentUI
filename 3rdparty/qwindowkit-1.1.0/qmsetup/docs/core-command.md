# Core Command

`qmcorecmd` is an executable written by C++. It is designed to provide a set of solutions that are fixed in form and that CMake scripts cannot implement due to insufficient features or inefficiencies.

`qmcorecmd` uses `syscmdline` to parse command line arguments and have multiple subcommands.

You can refer to the help message of each command to acquire more usage information, since this document provides only a brief introduction.

## Filesystem Commands

### Copy

Copies a file or folder. If the given folder path ends with the separator, copies the contents of the folder.

+ Read timestamp to determine whether to overwrite an existing object file. 
+ Support ignoring specific files specified by regular expressions.

### Rmdir

Recursively deletes all empty directories. 

Since CMake copies all directories unconditionally when executing the `install(DIRECTORY ...)` command, even if the directory is empty. This command can be used to fix this unreasonable phenomenon.

### Touch

Since Microsoft Windows does not provide a native command for handling file timestamps, this command is designed to copy or update a file's time stamp.

Only some of the functionality of Unix `touch` command is implemented.

## Buildsystem Commands

### Configure

Generates configuration header files.

It allows users to add macro definitions via the `-D` option, which are directly written into the generated header file. Additionally, users can specify a warning file with the `-w` option, the contents of which are added as comments at the top of the header file.

A key feature of this command is its ability to compute the SHA-256 hash of the definitions and embed it in the generated file, facilitating the tracking of configuration changes.

### Incsync

Reorganizes header files in include directories.

It supports defining path patterns and corresponding subdirectories through the `-i` option, reorganizing header files by writing relative reference statement or copying directly. The `-e` option can be used to exclude files matching certain patterns.

While processing header files, `incsync` considers the last modified time to determine whether to copy or update files.

### Deploy

Resolves and deploys a binary's shared library dependencies.

It analyzes dependencies of specified files and copies these dependencies to a designated output directory. Moreover, it handles details like fixing RPATH or dealing with Windows-specific library search paths.

The `-s` option is provided to ignore standard C/C++ runtime and system libraries, reducing unnecessary dependency copying.

All shared libraries that are deployed must have different file names.