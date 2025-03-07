#!/bin/bash
###############################################################################
# run_all_simulations.sh
# ----------------------
# Run all simulation binaries in `./bin`.
#
# Usage:
# ------
# $ ./run_all_simulations.sh
#
# Positional Arguments:
#   NA
#
# Optional Arguments:
#   NA
# 
# Notes:
# ------
# Ensure this script has executable permission before use.
#
###############################################################################
# Author: M. De Santis
# Date: 2025/03/07
###############################################################################

set -e

SCRIPT=$(readlink -f "$0")
SCRIPT_DIR=$(dirname ${SCRIPT})

echo -e "EXECUTING $SCRIPT..."

# Run all simulations
SIMULATION_DIR=${PWD}/bin
for BINARY in "${SIMULATION_DIR}"/*;
do
    if [[ -x "${BINARY}" && -f "${BINARY}" ]]; then
        echo -e "Executing simulation binary: $(basename ${BINARY})"
        "${BINARY}" 
    else
        echo "Skipping non-executable file: ${BINARY}"
    fi
done

echo -e "--- YOU EXECUTED ---"

