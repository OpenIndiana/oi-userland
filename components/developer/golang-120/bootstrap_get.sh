#!/usr/bin/bash

GOLANG_ARCHIVE="go1.19.5.illumos-amd64.tar.gz"

if ! [ -f "${GOLANG_ARCHIVE}" ]; then
	wget "https://illumos.org/downloads/${GOLANG_ARCHIVE}" -O ${GOLANG_ARCHIVE}
fi

mkdir -p go_bootstrap

if ! [ -f "go_bootstrap/bin" ]; then
	gtar -C go_bootstrap -xzf ${GOLANG_ARCHIVE}
fi

