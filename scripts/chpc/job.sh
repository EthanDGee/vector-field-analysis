#!/usr/bin/env bash
# SLURM batch worker -- submitted by enqueue.sh and benchmark.sh, do not run directly.
# Expects these env vars (set via sbatch --export):
#   GPU_LABEL        - human label for this run (e.g. "a100")
#   SM_ARCH          - CUDA SM arch the binaries were compiled for (e.g. "sm_80")
#   PROJECT_DIR      - absolute path to the project root
#   JOB_BIN          - binary name (arch suffix appended automatically)
#   JOB_INPUT        - input file path (relative to project root)
#   JOB_OUTPUT       - output file path (relative to project root, _<gpu_label> inserted before extension)
#   CUDA_MODULE      - CUDA module to load (e.g. cuda/12.1.0)

set -euo pipefail

# Initialize LMOD so the module command is available and functional.
# SLURM batch jobs run in a non-login, non-interactive shell that does not source
# /etc/profile, so the module function is not set up by default.
# shellcheck source=/dev/null
source /etc/profile.d/lmod.sh 2>/dev/null || true

module load "$CUDA_MODULE"

cd "$PROJECT_DIR"

# Derive per-GPU output: output/gc_life.raw -> output/gc_life_a100.raw
base="${JOB_OUTPUT%.*}"
ext="${JOB_OUTPUT##*.}"
gpu_output="${base}_${GPU_LABEL}.${ext}"

echo "=== job info ==="
date
echo "host: $(hostname)"
echo "gpu:  $GPU_LABEL ($SM_ARCH)"

echo ""
echo "=== nvidia-smi ==="
nvidia-smi

echo ""
echo "=== $JOB_BIN ==="
mkdir -p "$(dirname "$gpu_output")"
"./${JOB_BIN}_${SM_ARCH}" "$JOB_INPUT" "$gpu_output"
