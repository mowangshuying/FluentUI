#!/bin/bash

# MIT License
# Copyright (c) 2023 SineStriker

# Description: This script calls `qmcorecmd` to deploy dependencies on Mac/Linux.

# Show usage
usage() {
    echo "Usage: $(basename $0) -i <dir> -m <path>"
    echo "                   --plugindir <plugin_dir> --libdir <lib_dir> --qmldir <qml_dir>"
    echo "                  [--qmake <qmake_path>] [--extra <extra_path>]..."
    echo "                  [--qml <qml_module>]... [--plugin <plugin>]... [--copy <src> <dest>]..."
    echo "                  [-f] [-s] [-V] [-h]"
    echo "  -i <input_dir>              Directory containing binaries and libraries"
    echo "  -m <corecmd_path>           Path to corecmd"
    echo "  --plugindir <plugin_dir>    Output directory for plugins"
    echo "  --libdir <lib_dir>          Output directory for libraries"
    echo "  --qmldir <qml_dir>          Output directory for QML files"
    echo "  --qmake <qmake_path>        Path to qmake (optional)"
    echo "  --extra <extra_path>        Extra plugin searching path (repeatable)"
    echo "  --qml <qml_module>          Relative path to QML directory (repeatable)"
    echo "  --plugin <plugin>           Specify a Qt plugin to deploy (repeatable)"
    echo "  --copy <src> <dest>         Specify additional binary file to copy and its destination directory (repeatable)"
    echo "  -@                          Add library searching paths from a list file"
    echo "  -L                          Add a library searching path"
    echo "  -f                          Force overwrite existing files"
    echo "  -s                          Ignore C/C++ runtime and system libraries"
    echo "  -V                          Show verbose output"
    echo "  -h                          Show this help message"
}

# Initialize arguments
EXTRA_PLUGIN_PATHS=()
QML_REL_PATHS=()
ARGS=()
VERBOSE=""
PLUGINS=()
FILES=""

# Parse command line
while (( "$#" )); do
    case "$1" in
        -i)            INPUT_DIR="$2"; shift 2;;
        -m)            CORECMD_PATH="$2"; shift 2;;
        -@)            ARGS+=("-@ \"$2\""); shift 2;;
        -L)            ARGS+=("-L \"$2\""); shift 2;;
        --plugindir)   PLUGIN_DIR="$2"; shift 2;;
        --libdir)      LIB_DIR="$2"; shift 2;;
        --qmldir)      QML_DIR="$2"; shift 2;;
        --qmake)       QMAKE_PATH="$2"; shift 2;;
        --extra)       EXTRA_PLUGIN_PATHS+=("$2"); shift 2;;
        --plugin)      PLUGINS+=("$2"); shift 2;;
        --qml)         QML_REL_PATHS+=("$2"); shift 2;;
        --copy)        ARGS+=("-c \"$2\" \"$3\""); shift 3;;
        -f|-s)         ARGS+=("$1"); shift;;
        -V)            VERBOSE="-V"; shift;;
        -h) usage; exit 0;;
        *) echo "Error: Unsupported argument $1"; usage; exit 1;;
    esac
done

# Check required arguments
for arg in INPUT_DIR PLUGIN_DIR LIB_DIR QML_DIR CORECMD_PATH; do
    if [[ -z ${!arg} ]]; then
        echo "Error: Missing required argument '$arg'"
        usage
        exit 1
    fi
done

# Get Qt plugin and QML paths
PLUGIN_PATHS=()
QML_PATH=""
if [[ -n "$QMAKE_PATH" ]]; then
    QMAKE_PLUGIN_PATH=$($QMAKE_PATH -query QT_INSTALL_PLUGINS)
    PLUGIN_PATHS+=("$QMAKE_PLUGIN_PATH")

    QML_PATH=$($QMAKE_PATH -query QT_INSTALL_QML)
fi

# Add extra plugin searching paths
PLUGIN_PATHS+=("${EXTRA_PLUGIN_PATHS[@]}")

# Ensure that the QML search path is not empty 
# when the QML related path is specified (qmake needs to be specified)
if [[ ${#QML_REL_PATHS[@]} -gt 0 && -z "$QML_PATH" ]]; then
    echo "Error: qmake path must be specified when QML paths are provided"
    usage
    exit 1
fi

# Search input directory
search_input_dir() {
    local path="$1"
    for item in "$path"/*; do
        if [ -d "$item" ]; then
            # Check if the directory is mac .framework
            if [[ "OSTYPE" == "darwin"* ]] && [[ "$item" == *.framework ]]; then
                FILES="$FILES \"$item\""
            else
                search_input_dir "$item"
            fi
        elif [ -f "$item" ]; then
            if [[ "$OSTYPE" == "msys"* ]] || [[ "$OSTYPE" == "win32" ]] || [[ "$OSTYPE" == "cygwin"* ]]; then
                # On Windows, search for.exe and.dll files
                FILES="$FILES \"$item\""
            else
                # On Unix, traverse all files, using the file command to
                # check for executable binary files
                file_type=$(file -b "$item")
                if [[ ($file_type == "ELF"* || $file_type == "Mach-O"*) && -x "$item"  ]]; then
                    FILES="$FILES \"$item\""
                fi
            fi
        fi
    done
}

search_input_dir "$INPUT_DIR"

# Find the full path to the Qt plugin
for plugin_path in "${PLUGINS[@]}"; do
    # Check format
    if [[ $plugin_path == */* ]]; then
        IFS='/' read -r -a plugin_parts <<< "$plugin_path"
        
        # Extracts the category and name
        category=${plugin_parts[0]}
        name=${plugin_parts[1]}

        # Calculate destination directory
        dest_dir="${PLUGIN_DIR}/${category}"

        # Initialize an array to store found plugins
        found_plugins=""

        # Traverse the path and find the specific plug-in files
        for search_path in "${PLUGIN_PATHS[@]}"; do
            while IFS= read -r plugin; do
                # Get name
                plugin_name=$(basename "$plugin")

                # Check if the plugin was already found to avoid duplicates
                if [[ ! $found_plugins =~ $plugin_name ]]; then
                    found_plugins+="$plugin_name "
                    ARGS+=("-c \"$plugin\" \"$dest_dir\"")
                fi
            done < <(find "${search_path}/${category}" -name "lib${name}.*" ! -name "*debug*" -print)
        done

        if [ ${#found_plugins[@]} -eq 0 ]; then
            echo "Error: Plugin '${plugin_path}' not found in any search paths."
            exit 1
        fi
    else
        echo "Error: Invalid plugin format '${plugin_path}'. Expected format: <category>/<name>"
        exit 1
    fi
done

# Process QML item
handle_qml_file() {
    local file="$1"
    local rel_path="${file#$QML_PATH/}"

    local target="$QML_DIR/$rel_path"
    local target_dir="$(dirname "$target")"

    # Directory: must be mac framework
    if [ -d "$file" ]; then
        ARGS+=("-c \"$file\" \"$target_dir\"")
        return
    fi

    # Ignore specific files
    if [[ "$OSTYPE" == "msys"* ]] || [[ "$OSTYPE" == "win32" ]] || [[ "$OSTYPE" == "cygwin"* ]]; then
        if [[ "$file" == *.pdb ]] || [[ "$file" == *d.dll ]]; then
            return
        fi
    else
        if [[ "$file" == *_debug.dylib ]] || [[ "$file" == *.so.debug ]]; then
            return
        fi
    fi

    # Determine whether it is an executable binary file and handle it accordingly
    if [[ "$OSTYPE" == "msys"* ]] || [[ "$OSTYPE" == "win32" ]] || [[ "$OSTYPE" == "cygwin"* ]]; then
        if [[ "$file" == *.dll || "$file" == *.exe ]]; then
            ARGS+=("-c \"$file\" \"$target_dir\"")
        else
            mkdir -p "$target_dir"
            cp "$file" "$target"
        fi
    else
        file_type=$(file -b "$file")
        if [[ ($file_type == "ELF"* || $file_type == "Mach-O"*) && -x "$file" ]]; then
            ARGS+=("-c \"$file\" \"$target_dir\"")
        else
            mkdir -p "$target_dir"
            cp "$file" "$target"
        fi
    fi
}

# Search QML directory
search_qml_dir() {
    local path="$1"
    for item in "$path"/*; do
        if [ -d "$item" ]; then
            # Check if the path is mac .framework
            if [[ "OSTYPE" == "darwin"* ]] && [[ "$item" == *.framework ]]; then
                handle_qml_file "$item"
            else
                search_qml_dir "$item"
            fi
        elif [ -f "$item" ]; then
            handle_qml_file "$item"
        fi
    done
}

# Process QML directories
for qml_rel_path in "${QML_REL_PATHS[@]}"; do
    full_path="$QML_PATH/$qml_rel_path"
    if [[ -d "$full_path" ]]; then
        # Directory
        search_qml_dir "$full_path"
    elif [[ -f "$full_path" ]]; then
        # File
        handle_qml_file "$full_path" "$QML_DIR"
    fi
done

# Build and execute the deploy command
DEPLOY_CMD="$CORECMD_PATH deploy $FILES ${ARGS[@]} -o \"$LIB_DIR\" $VERBOSE"
if [[ "$VERBOSE" == "-V" ]]; then
    echo "Executing: $DEPLOY_CMD"
fi
eval $DEPLOY_CMD

# Check the deployment result
if [ $? -ne 0 ]; then
    exit 1
fi