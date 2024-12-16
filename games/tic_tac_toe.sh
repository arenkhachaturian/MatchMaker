#!/bin/bash
set +x # disable echo

SCRIPT_DIR=$(dirname "$(readlink -f "$0")")

python3 -u "$SCRIPT_DIR/tic_tac_toe.py" "$@"
