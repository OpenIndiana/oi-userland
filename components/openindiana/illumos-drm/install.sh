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
source=$1 out=$2 proto=$3
mkdir -p "$proto/kernel/misc/amd64" "$proto/kernel/drv/amd64" \
    "$proto/usr/sbin" "$proto/usr/share/man/man8" \
    "$proto/usr/share/drmadm" "$proto/lib/svc/manifest/system"
cp "$out/drm_core" "$out/linuxkpi/linuxkpi" "$out/carried/drm_helpers" \
    "$out/drm_kms/drm_kms" "$proto/kernel/misc/amd64/"
cp "$out/virtio_gpu" "$out/i915/i915n" "$proto/kernel/drv/amd64/"
cp "$source/tools/drmadm/drmadm" "$proto/usr/sbin/"
cp "$source/tools/drmadm/drmadm.8" "$proto/usr/share/man/man8/"
cp "$source/packaging/drm-perms.xml" "$proto/lib/svc/manifest/system/"
cp "$source/packaging/20-modesetting.conf" "$source/packaging/virtio-gpu.aliases" \
    "$proto/usr/share/drmadm/"
cp "$out/LICENSE.i915n" "$out/LICENSE.drm_kms" "$proto/"
