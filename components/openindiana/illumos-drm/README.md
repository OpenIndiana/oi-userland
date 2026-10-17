This component builds and packages illumos-drm v0.0.2 natively on amd64
illumos: drmadm, drm_core, virtio_gpu, linuxkpi, drm_helpers, drm_kms and
i915n with display support. It installs beside gfx-drm without selecting
the new stack; both hardware drivers have no PCI aliases. The optional legacy-core dependency
requires gfx-drm component revision 104 or newer when that stack is installed.

The fixed release assets for illumos-drm v0.0.2 (ab02009) and illumos-ddi
v0.0.1 (e82e75d406) are SHA-256 pinned, as are the Linux 7.2 release archive,
libdrm 2.4.134 uAPI headers and canonical illumos-gate DDI mapfile. Registry
crates use Cargo.lock checksums, and the DDI git dependency is vendored from
its pinned release asset. Download populates these inputs; subsequent builds
use Cargo's offline, locked directory sources and upstream licence checks.

OpenIndiana's developer/lang/rustc supplies stable Rust 1.98.0, cargo and
rust-src under /usr/lib/rustlib/src/rust/library. RUSTC_BOOTSTRAP=1 enables
-Zbuild-std=core,alloc for the custom kernel target without rustup. RUSTC,
CARGO and RUST_SRC can be overridden together for a staged OI toolchain.
The C builds use GCC 14 and the onbld ctfconvert, with a disk-backed TMPDIR.

Loading the modules and checking their kernel symbol resolution needs a
global zone.
