#!/usr/bin/bash
#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2025 Till Wegmueller
#

set -ex

PROTO_DIR=$1
SOURCE_DIR=$2
pkgname=helix

runtime_dir="${PROTO_DIR}/usr/lib/$pkgname/runtime"
mkdir -p "$runtime_dir/grammars"

cd ${SOURCE_DIR}

gcp -r "runtime/queries" "$runtime_dir"
gcp -r "runtime/themes" "$runtime_dir"
find "runtime/grammars" -type f -name '*.so' -exec \
  ginstall -Dm 755 {} -t "$runtime_dir/grammars" \;
ginstall -Dm 644 runtime/tutor -t "$runtime_dir"

ginstall -Dm 644 "contrib/completion/hx.bash" "${PROTO_DIR}/usr/share/bash-completion/completions/$pkgname"
ginstall -Dm 644 "contrib/completion/hx.fish" "${PROTO_DIR}/usr/share/fish/vendor_completions.d/$pkgname.fish"
ginstall -Dm 644 "contrib/completion/hx.zsh" "${PROTO_DIR}/usr/share/zsh/site-functions/_$pkgname"
ginstall -Dm 644 "contrib/Helix.desktop" "${PROTO_DIR}/usr/share/applications/$pkgname.desktop"
ginstall -Dm 644 "contrib/$pkgname.png" -t "${PROTO_DIR}/usr/share/icons/hicolor/256x256/apps"

