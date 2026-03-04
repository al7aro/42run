#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# DOWNLOAD GLFW
git clone -b 3.3-stable https://github.com/glfw/glfw.git "$SCRIPT_DIR/../vendor/glfw"
git clone https://github.com/al7aro/stb.git "$SCRIPT_DIR/../vendor/stb"
git clone -b 4.1 https://github.com/al7aro/glad.git "$SCRIPT_DIR/../vendor/glad"

mkdir -p "${SCRIPT_DIR}/../build"
cmake -S "${SCRIPT_DIR}/.." -B "${SCRIPT_DIR}/../build"
make -C "${SCRIPT_DIR}/../build"
