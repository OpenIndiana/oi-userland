#!/bin/sh
# List component directories that do not have a package.kdl file.
# A "component directory" is defined here as any directory under
#   components/ that contains a Makefile (case-sensitive name Makefile).
# Output:
#   - Prints each component directory (relative path) missing package.kdl
#   - At the end prints a summary count
# Exit code:
#   - Always 0 (for easy piping/consumption)

set -eu

# Move to repo root if invoked from elsewhere
ROOT_DIR=$(cd "$(dirname "$0")/.." && pwd)
cd "$ROOT_DIR"

# Collect component root directories (heuristic):
# Only consider Makefiles that include ips.mk or common.mk (via either path),
# to avoid matching nested helper Makefiles (e.g., src/ or files/).
TMP_DIRS=$(mktemp)
{
  for mf in $(find components -type f -name Makefile); do
    if /usr/bin/grep -q 'include $(WS_MAKE_RULES)/ips.mk' "$mf" || \
       /usr/bin/grep -q 'include $(WS_MAKE_RULES)/common.mk' "$mf" || \
       /usr/bin/grep -q 'include $(WS_TOP)/make-rules/common.mk' "$mf"; then
      dirname "$mf"
    fi
  done
} | sort -u > "$TMP_DIRS"

missing=0
while IFS= read -r dir; do
  # Skip if the directory has package.kdl
  if [ ! -f "$dir/package.kdl" ]; then
    printf "%s\n" "$dir"
    missing=$((missing+1))
  fi
done < "$TMP_DIRS"
rm -f "$TMP_DIRS"

echo "---"
echo "Missing package.kdl count: $missing"

# Always succeed
exit 0
