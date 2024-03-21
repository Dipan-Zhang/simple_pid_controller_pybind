#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

source ./build/activate.sh
source ./build/activate_run.sh
export PYTHONPATH=$SCRIPT_DIR/build/interfaces/:$PYTHONPATH

jupyter-lab
