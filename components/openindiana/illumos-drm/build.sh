#!/usr/bin/bash
#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2026 Till Wegmueller
#

set -euo pipefail
out=$1
export PATH=/usr/bin:/usr/sbin:/usr/gnu/bin LC_ALL=C RUSTC_BOOTSTRAP=1
export RUSTFLAGS='-C symbol-mangling-version=v0 -C force-frame-pointers=yes'
"$RUSTC" -Vv
"$CARGO" -V
# Acceptance probe: no rustup, custom target parsed by the stable compiler.
"$RUSTC" -Zunstable-options --print target-spec-json \
    --target targets/x86_64-illumos-kmod.json > "$out/accepted-target.json"
"$CARGO" build --offline --locked --release -j 2 \
    -p drm-module -p virtio_gpu --target targets/x86_64-illumos-kmod.json \
    -Zjson-target-spec -Zbuild-std=core,alloc \
    -Zbuild-std-features=compiler-builtins-mem
archives=$CARGO_TARGET_DIR/x86_64-illumos-kmod/release
OUT=$out modules/drm_core/ctf/build-ctf.sh
"$LD" -ztype=kmod -N fs/specfs -B reduce -M modules/drm_core/drm_core.mapfile \
    -z allextract "$archives/drm_module.a" -z defaultextract \
    "$out/drm_facade_ctf.o" -o "$out/drm_core"
/usr/bin/nm "$out/drm_core" | awk -F'|' \
    '$5 ~ /GLOB/ && $7 !~ /UNDEF/ {gsub(/ /,"",$8); print $8}' | sort > "$out/drm_core.globals"
awk '/global:/ {g=1; next} /local:/ {g=0} g && /;/ {gsub(/[;\t ]/, ""); print}' \
    modules/drm_core/drm_core.mapfile | sort > "$out/drm_core.want"
diff "$out/drm_core.want" "$out/drm_core.globals"
echo "drm_core: globals match mapfile ($(wc -l < "$out/drm_core.globals"))"
"$LD" -ztype=kmod -N misc/virtio -N fs/specfs -N misc/drm_core \
    -z allextract "$archives/virtio_gpu.a" -o "$out/virtio_gpu"
OUT=$out/linuxkpi linuxkpi/build.sh all
export LKPI_MAPFILE=$out/linuxkpi/linuxkpi.mapfile
OUT=$out/carried sh carried/build.sh
OUT=$out/drm_kms carried/drm_kms/build.sh all
I915_DISPLAY=1 OUT=$out/i915 drivers/i915/build.sh all
drivers/i915/gen-license.sh "$LINUX" "$out/LICENSE.i915n" "$out/i915/linux-inputs.txt"
MODULE=drm_kms drivers/i915/gen-license.sh "$LINUX" "$out/LICENSE.drm_kms" "$out/drm_kms/linux-inputs.txt"
# Assert each module's dependency graph, in addition to upstream -z defs
# and symbol-scope checks. NEEDED must match the reference build.
check_needed() {
    local module=$1; shift
    /usr/bin/elfdump -d "$module" | awk '$2 == "NEEDED" {print $4}' | sort > "$out/needed.actual"
    printf '%s\n' "$@" | sort > "$out/needed.expected"
    diff "$out/needed.expected" "$out/needed.actual"
    echo "NEEDED $module: $(tr '\n' ' ' < "$out/needed.actual")"
}
check_needed "$out/drm_core" fs/specfs
check_needed "$out/virtio_gpu" misc/virtio fs/specfs misc/drm_core
check_needed "$out/linuxkpi/linuxkpi" misc/drm_core
check_needed "$out/carried/drm_helpers" misc/linuxkpi
check_needed "$out/drm_kms/drm_kms" misc/drm_core misc/linuxkpi misc/drm_helpers
check_needed "$out/i915/i915n" misc/drm_core misc/linuxkpi misc/drm_helpers misc/drm_kms misc/gfx_private
/usr/sbin/svccfg validate packaging/drm-perms.xml
