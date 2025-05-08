# QMSetup

**QMSetup** is a set of CMake Modules and Basic Libraries for C/C++ projects.

**This project is independent from Qt and other 3rdparty libraries.** Due to the fact that it encompasses some tools that need to be compiled, it's strongly not suggested to be included as a subproject.

## Features

### Helpful Functions
+ Path, Version functions
+ Target configuration functions
+ Qt related functions

### Generators
+ Generate Windows RC files, manifest files
+ Generate MacOS Bundle info files
+ Generate configuration header files
+ Generate Git information header files

### Filesystem Utilities
+ Reorganize header files
+ Copy files and directories after build

### Install Utilities
+ Deploy project dependencies and fix rpaths

### Extended Build Rules
+ Create translations with **Qt Linguist** tools
+ Create source files with **Protobuf** compiler
+ Create documentations with **Doxygen**

## Support Platforms

+ Microsoft Windows
+ Apple Macintosh
+ GNU/Linux

## Dependencies

### Required Packages

#### Windows

Windows deploy command acquires the shared library paths by reading the PE files and searching the specified paths so that it doesn't depend on `dumpbin` tool.

#### Unix

Unix deploy command acquires the shared library paths by running `ldd`/`otool` command and fixes the *rpath*s by runing the `patchelf`/`install_name_tool` command, make sure you have installed them.

```sh
sudo apt install patchelf
```

### Build System

+ C++ 17
+ CMake 3.19

### Open-Source Libraries
+ https://github.com/SineStriker/syscmdline
+ https://github.com/jothepro/doxygen-awesome-css

## Integrate

### Clone

Via Https
```sh
git clone --recursive https://github.com/stdware/qmsetup.git
```
Via SSH
```sh
git clone --recursive git@github.com:stdware/qmsetup.git
```

### Preinstall (Suggested)

#### Build & Install
```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release \
               -DCMAKE_INSTALL_PREFIX=/path/to
cmake -B build --target all
cmake -B build --target install
```

#### Import
```sh
cmake -Dqmsetup_DIR=/path/to/lib/cmake/qmsetup ...
```
```cmake
find_package(qmsetup REQUIRED)
```

### Sub-project

It still needs to be installed, but the installation occurs during the CMake Configure phase and is executed only once.

```cmake
find_package(qmsetup QUIET)

if (NOT TARGET qmsetup::library)
    # Modify this variable according to your project structure
    set(_source_dir ${CMAKE_CURRENT_SOURCE_DIR}/qmsetup)

    # Import install function
    include("${_source_dir}/cmake/modules/private/InstallPackage.cmake")

    # Install package in place
    set(_package_path)
    qm_install_package(qmsetup
        SOURCE_DIR ${_source_dir}
        BUILD_TYPE Release
        RESULT_PATH _package_path
    )

    # Find package again
    find_package(qmsetup REQUIRED PATHS ${_package_path})

    # Update import path
    set(qmsetup_DIR ${_package_path} CACHE PATH "" FORCE)
endif()
```

## Quick Start

### Examples

You can use the functions in this library to greatly simplify several kinds of common build rules.

#### Generate Configuration Header
```cmake
qm_import(Preprocess)

qm_add_definition(FOO false)
qm_add_definition(BAR 114514)
qm_add_definition(BAZ "ABC" STRING_LITERAL)

qm_generate_config(${CMAKE_BINARY_DIR}/conf.h)
```

#### Reorganize Include Directory
```cmake
qm_import(Preprocess)

qm_sync_include(src/core ${CMAKE_BINARY_DIR}/include/MyCore
    INSTALL_DIR ${CMAKE_INSTALL_INCLUDEDIR}/MyCore
)
```

#### Sync Resource Files After Build
```cmake
qm_import(Filesystem)

qm_add_copy_command(${PROJECT_NAME}
    SOURCES
        file.txt
        dir_to_copy
        dir_contents_to_copy/
    DESTINATION .
)
```

#### Deploy Project And All Dependencies
```cmake
qm_import(Deploy)

qm_deploy_directory("${CMAKE_INSTALL_PREFIX}"
    COMMENT "Deploy project spectacularly"
    PLUGINS "iconengines/qsvgicon" "bearer/qgenericbearer"
    QML Qt QtQml
    PLUGIN_DIR share/plugins
    QML_DIR share/qml
)
```

#### Add Qt Translations
```cmake
qm_import(Translate)

qm_find_qt(LinguistTools)
qm_add_translation(${PROJECT_NAME}_translations
    LOCALES ja_JP zh_CN zh_TW
    PREFIX ${PROJECT_NAME}
    TARGETS ${PROJECT_NAME}
    TS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/translations
    QM_DIR ${CMAKE_CURRENT_BINARY_DIR}/translations
)
```

#### Generate Protubuf Source Files
```cmake
qm_import(Protobuf)

find_package(Protobuf REQUIRED)
qm_create_protobuf(_proto_src
    INPUT a.proto b.proto
    INCLUDE_DIRECTORIES src/proto
    OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto
)
target_sources(${PROJECT_NAME} PUBLIC ${_proto_src})
```

#### Generate Doxygen HTML Documentations
```cmake
qm_import(Doxygen)

find_package(Doxygen REQUIRED)
qm_setup_doxygen(${PROJECT_NAME}_RunDoxygen
    NAME ${PROJECT_NAME}
    DESCRIPTION "my project"
    MDFILE "${CMAKE_SOURCE_DIR}/README.md"
    OUTPUT_DIR "${CMAK_BINARY_DIR}/doc"
    INPUT src
    TARGETS ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    NO_EXPAND_MACROS
        Q_OBJECT
        Q_GADGET
        Q_DECLARE_TR_FUNCTIONS
    COMPILE_DEFINITIONS 
        Q_SIGNALS=Q_SIGNALS
        Q_SLOTS=Q_SLOTS
    GENERATE_TAGFILE "${PROJECT_NAME}_tagfile.xml"
    INSTALL_DIR "doc"
)
```

### Find Modules

Use `qm_find_package` to find supported third-party packages.

+ YY-Thunks: https://github.com/Chuyu-Team/YY-Thunks
+ VC-LTL5: https://github.com/Chuyu-Team/VC-LTL5

### Detailed Documentations

+ [Core Command](docs/core-command.md)

The CMake Modules documentations is provided in the comments.

See `examples` to get detailed use cases.

## Contributors

+ [SineStriker](https://github.com/SineStriker)
+ [wangwenx190](https://github.com/wangwenx190)
+ [RigoLigoRLC](https://github.com/RigoLigoRLC)
+ [CrSjimo](https://github.com/CrSjimo)

## License

QMSetup is licensed under the MIT License.