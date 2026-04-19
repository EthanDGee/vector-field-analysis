#!/usr/bin/env bash
# Monitor running pipeline jobs and tail their logs.
# Run on the CHPC login node.
#
# Usage:
#   ./scripts/chpc/monitor.sh            # show queue + last 20 lines of all logs
#   ./scripts/chpc/monitor.sh karman     # tail a specific stem's log live

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"
LOG_DIR="$PROJECT_DIR/logs"

# -- Live tail for a specific stem --------------------------------------------

if [[ $# -eq 1 ]]; then
  log="$LOG_DIR/$1/stdout.log"
  if [[ ! -f "$log" ]]; then
    echo "error: no log found at $log" >&2
    exit 1
  fi
  echo "==> tailing $log (Ctrl-C to stop)"
  tail -f "$log"
  exit 0
fi

# -- Queue status -------------------------------------------------------------

echo "==> jobs"
squeue -u "$USER" --format="%.10i %.20j %.8T %.10M %.6D %R" 2>/dev/null \
  || echo "  (none)"

# -- Recent log tails ---------------------------------------------------------

echo ""
echo "==> logs"
for log in "$LOG_DIR"/*/stdout.log; do
  [[ -f "$log" ]] || continue
  stem="$(basename "$(dirname "$log")")"
  printf "\n--- %s ---\n" "$stem"
  tail -n 20 "$log"
done
