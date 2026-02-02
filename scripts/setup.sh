#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# DOWNLOAD GLFW
git clone -b 3.3-stable https://github.com/glfw/glfw.git "$SCRIPT_DIR/../Feldespato/vendor/glfw/glfw/"

mkdir -p "${SCRIPT_DIR}/../build"

cmake -S "${SCRIPT_DIR}/.." -B "${SCRIPT_DIR}/../build"

make -C "${SCRIPT_DIR}/../build"
