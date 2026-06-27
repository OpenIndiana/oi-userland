# oi-userland Maintainer Areas

This file divides the ~2,700 components under `components/` into responsibility
areas, each sized to be sustainable for **one person**. It is advisory: owners
review and merge PRs in their area, drive version bumps, and own breakage there.

Two cross-cutting **roles** (PR triage, build infrastructure) are not tied to a
category — they support every area.

How to read an entry:

- **Scope** — what the area covers.
- **Paths** — glob patterns under the repo root that belong to the area.
- **Owner** — GitHub/Forgejo handle, or `_unassigned_`.
- **Load** — relative effort and the nature of the work (deep vs. churn).

Sizing principle: package *count* is not load. The big categories (`python/` 699,
`perl/` 466, `library/` 384) are mostly mechanical, automatable version bumps
("wide and shallow"); the small ones (toolchain, crypto, installer) are
expertise-heavy and high blast-radius ("narrow and deep"). Areas below balance
the two. Adjacent seats marked *(mergeable)* can be held by one person if you
have fewer volunteers.

---

## Cross-cutting roles

### PR triage / release coordination
- **Scope**: First-pass triage of incoming userland PRs, label/route to the
  area owner, keep the merge queue moving, coordinate releases. Not an area —
  a coordination role across the whole repo.
- **Paths**: `*` (repo-wide)
- **Owner**: Toasterson
- **Load**: Steady, interrupt-driven. Keep separate from a heavy build area.

### Build infrastructure
- **Scope**: The framework every component depends on — make-rules, transforms,
  shared tooling, CI. Changes here ripple to all areas.
- **Paths**: `make-rules/*`, `transforms/*`, `tools/*`, `ci/*`, `components.mk`,
  `components/Makefile`
- **Owner**: Toasterson
- **Load**: Bursty but high-leverage. Do not stack onto a content area.

---

## Areas

### 1. Toolchain & developer tools
- **Scope**: Compilers, debuggers, linkers, and the build-tool/VCS userland.
- **Paths**: `components/developer/*`, `components/rust/*`
  - Core: `gcc-*`, `gcc3`, `clang-*`, `llvm*`, `gdb`, `binutils`, `golang-*`,
    Rust toolchain
  - Build tools: `autoconf*`, `automake*`, `cmake*`, `bison*`, `flex`, `meson`,
    `ninja`, `pkg-config`; VCS: `git`, `cvs`, `fossil`
- **Owner**: Bill-Sommerfeld
- **Load**: High / deep. The gcc + clang version matrix alone is a real job.
  Consider handing the **Go + Rust toolchains** to the language-runtimes owner.

### 2. X11 — server, Mesa & drivers
- **Scope**: The X server (Xorg / Xlibre), Mesa/GL, and DDX video/input drivers.
- **Paths**: `components/x11/xorg-server*`, `components/x11/xlibre*`,
  `components/x11/xserver*`, `components/x11/mesa*`, `components/x11/xwayland*`,
  `components/x11/xf86-video-*`, `components/x11/xf86-input-*`,
  `components/openindiana/gfx-drm`, `components/openindiana/nvidia*`
- **Owner**: _unassigned_
- **Load**: High / deep. The real X11 work lives here.

### 3. X11 — libraries & protocol *(mergeable with #2 or #13)*
- **Scope**: Client libraries, XCB, protocol headers, X bitmap fonts.
- **Paths**: `components/x11/lib*`, `components/x11/xcb*`, `components/x11/*proto*`,
  `components/x11/xtrans`, and the remaining `components/x11/*`
- **Owner**: _unassigned_
- **Load**: Medium / churn. Mostly tracking xorg releases.

### 4. Core libraries (GLib/GTK stack & general C/C++)
- **Scope**: The shared-library substrate under desktop and everything else —
  glib/gtk, boost, cairo, pango, imaging libs, scientific libs.
- **Paths**: `components/library/*` (everything **except** the crypto libs in
  area #5), `components/image/*`, `components/scientific/*`
- **Owner**: _unassigned_
- **Load**: High / mixed. 380+ libs; glib/gtk churn drives desktop rebuilds.

### 5. Crypto & security libraries  ⚠️ owns the OpenSSL cleanup
- **Scope**: TLS/crypto libraries and the trust store.
- **Paths**: `components/library/openssl*`, `components/library/gnutls`,
  `components/library/libsodium`, `components/library/botan`,
  `components/library/cryptopp`, `components/library/nettle`,
  `components/library/libgcrypt*`, `components/library/libgpg-error`,
  `components/library/heimdal`, `components/sysutils/gnupg`,
  `components/sysutils/gpgme`, `components/sysutils/argon2`,
  `components/sysutils/ccrypt`, `components/openindiana/ca-certificates`
- **Owner**: _unassigned_
- **Load**: Medium / deep + security-on-call.

### 6. Network & web services
- **Scope**: Network daemons, VPN/SSH, and web servers/app stacks.
- **Paths**: `components/network/*`, `components/web/*`
- **Owner**: _unassigned_
- **Load**: High / churn + security. samba, bind/unbound, openssh, openvpn,
  tor, freeradius, apache/tomcat/squid. Pairs naturally with #5.

### 7. Language runtimes & module ecosystems
- **Scope**: Non-C language runtimes and their (largely automatable) module sets.
- **Paths**: `components/runtime/*`, `components/python/*`, `components/perl/*`,
  `components/ruby/*`, `components/ocaml/*`, `components/common-lisp/*`,
  `components/prolog/*`, `components/tcl/*`
- **Owner**: _unassigned_
- **Load**: Wide / shallow. ~1,200 dirs but dominated by mechanical bumps —
  ideal for someone who invests in automation. Runtimes (node/openjdk/erlang)
  are the deep part.

### 8. Databases
- **Scope**: RDBMS, KV stores, and their extensions/connectors.
- **Paths**: `components/database/*`
- **Owner**: _unassigned_
- **Load**: Medium / deep. postgres 14–16 + extensions, mariadb/mysql, redis,
  mongodb, sqlite.

### 9. Desktop environments
- **Scope**: MATE/GNOME and desktop apps, input methods, games.
- **Paths**: `components/desktop/*`, `components/inputmethod/*`,
  `components/games/*`
- **Owner**: _unassigned_
- **Load**: High / finicky. Sensitive to GTK/glib churn from #4. Consider
  splitting MATE from the rest if it gets heavy.

### 10. Media & codecs (encumbered)
- **Scope**: Audio/video codecs, GStreamer, players. Includes the patent/
  license-encumbered tree — owner must know its distribution rules.
- **Paths**: `components/encumbered/*`, `components/multimedia/*`
- **Owner**: _unassigned_
- **Load**: Medium / specialized. ffmpeg 6/7, gstreamer, vlc, x264/x265, dav1d.

### 11. Core system, virtualization & install media
- **Scope**: Distro plumbing — IPS (`pkg`), bhyve/kvm/qemu, the installer,
  release/ISO build, meta-packages, closed bits. The seat closest to
  illumos-gate.
- **Paths**: `components/openindiana/*` (except gfx-drm/nvidia → #2,
  ca-certificates → #5), `components/cluster/*`,
  `components/meta-packages/*`, `components/closed/*`
- **Owner**: Toasterson
- **Load**: High / deep. Natural home for the **create + boot-test install
  media** task.

### 12. CLI userland & sysutils  *(onboarding seat)*
- **Scope**: The command-line GNU/POSIX userland, shells, archivers, text tools,
  editors, MUAs.
- **Paths**: `components/sysutils/*` (except crypto utils → #5),
  `components/shell/*`, `components/archiver/*`, `components/text/*`,
  `components/editor/*`, `components/mail/*`
- **Owner**: _unassigned_
- **Load**: Wide / shallow, low individual risk. Best first seat for a new
  maintainer.

### 13. Fonts, printing & docs  *(light seat)*
- **Scope**: Font packaging, the print stack, doc toolchains.
- **Paths**: `components/fonts/*`, `components/print/*`, `components/foomatic/*`,
  `components/docbook/*`
- **Owner**: _unassigned_
- **Load**: Low / self-contained. Good for a lighter-availability volunteer.

---

## Package Maintainers
- iigs: Firefox, Thunderbird, Libreoffice
- fkink: php, Samba
- grzemba: SAMQFS

## Category coverage

Every top-level `components/` category maps to exactly one area:

| Category | Area |
|---|---|
| developer, rust | 1 |
| x11 (server/mesa/drivers) | 2 |
| x11 (libs/proto) | 3 |
| library (general), image, scientific | 4 |
| library (crypto subset) | 5 |
| network, web | 6 |
| runtime, python, perl, ruby, ocaml, common-lisp, prolog, tcl | 7 |
| database | 8 |
| desktop, inputmethod, games | 9 |
| encumbered, multimedia | 10 |
| openindiana, cluster, meta-packages, closed | 11 |
| sysutils, shell, archiver, text, editor, mail | 12 |
| fonts, print, foomatic, docbook | 13 |
