#!/usr/bin/env python3
"""Exercise the actual patched capability probes with read-only device fixtures."""
import os
from pathlib import Path
import subprocess
import sys
import tempfile

source = Path(sys.argv[1]).read_text()
start = source.index("static Bool\nsunKmsDevice(void)")
end = source.index("\nstatic void\nlistPossibleVideoDrivers", start)
probes = source[start:end].rsplit("#endif", 1)[0]
fixture = r'''
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int Bool;
#define TRUE 1
#define FALSE 0
#define XSERVER_LIBPCIACCESS 1
#define O_RDONLY 0
#define O_RDWR 2
#define X_PROBED 0
#define VIS_GETIDENTIFIER 1
#define DRM_IOCTL_MODE_GETRESOURCES 2
#define SYSCALL(x) do { x; } while (0)
struct vis_identifier { char name[128]; };
struct drm_mode_card_res { unsigned count_connectors; };
struct pci_device { int unused; } device;
struct pci_device_iterator { int index; } iterator;
static struct { int consoleFd; } xf86Info = { -1 };
static char *xf86SolarisFbDev = "/dev/fb";
static unsigned char ivt[4096], rom[0x40000];
static int primary, fail_ivt, fail_rom, maps, unmaps, kms_open, kms_result;
static unsigned connectors;
static int bitmap = 1;
static struct pci_device_iterator *pci_slot_match_iterator_create(void *p) {
    iterator.index=0; return &iterator;
}
static struct pci_device *pci_device_next(struct pci_device_iterator *i) {
    return i->index++ == 0 ? &device : NULL;
}
static int xf86IsPrimaryPci(struct pci_device *p) { return primary; }
static void pci_iterator_destroy(struct pci_device_iterator *i) {}
static int pci_device_map_legacy(struct pci_device *p, unsigned base,
    unsigned size, unsigned flags, void **out) {
    assert(flags==0);
    if (base==0) { assert(size==4096); if(fail_ivt) return -1; *out=ivt; }
    else { assert(base==0xc0000 && size==0x40000); if(fail_rom) return -1; *out=rom; }
    maps++; return 0;
}
static int pci_device_unmap_legacy(struct pci_device *p, void *m,unsigned n) {
    unmaps++; return 0;
}
static int fixture_open(const char *path,int flags) {
    if (!strcmp(path,"/dev/fb")) return 9;
    return kms_open ? 10 : -1;
}
static int fixture_close(int fd) { return 0; }
static int fixture_ioctl(int fd,int cmd,void *out) {
    if(cmd==VIS_GETIDENTIFIER) {
        strcpy(((struct vis_identifier *)out)->name,bitmap?"illumos_fb":"SUNWtext"); return 0;
    }
    assert(cmd==DRM_IOCTL_MODE_GETRESOURCES);
    ((struct drm_mode_card_res *)out)->count_connectors=connectors;
    return kms_result;
}
static void xf86Msg(int level,const char *fmt,const char *value) {}
#define open fixture_open
#define close fixture_close
#define ioctl fixture_ioctl
'''
checks = r'''
static void reset(void) {
    memset(ivt,0,sizeof ivt); memset(rom,0,sizeof rom);
    primary=1; fail_ivt=fail_rom=maps=unmaps=kms_open=0;
    kms_result=-1;connectors=0;bitmap=1;
}
static void vector(unsigned addr,unsigned segment) {
    ivt[addr]=segment & 255;ivt[addr+1]=segment >> 8;
}
static void header(unsigned offset,unsigned size) {
    rom[offset]=0x55;rom[offset+1]=0xaa;rom[offset+2]=size;
}
int main(void) {
    reset();assert(sunLegacyVbios()==0);assert(maps==unmaps);
    reset();vector(0x42,0xc000);header(0,128);
    assert(sunLegacyVbios()==1);assert(maps==unmaps);
    assert(!sunUseIllumosFb()); /* BIOS, or EFI with an initialized CSM */
    reset();assert(sunUseIllumosFb()); /* pure GOP */
    reset();bitmap=0;assert(!sunUseIllumosFb());assert(maps==0);
    reset();primary=0;assert(sunLegacyVbios()==-1);assert(!sunUseIllumosFb());
    reset();fail_ivt=1;assert(sunLegacyVbios()==-1);assert(!sunUseIllumosFb());
    reset();vector(0x42,0xc000);fail_rom=1;assert(sunLegacyVbios()==-1);assert(maps==unmaps);
    reset();vector(0x42,0xc020);vector(0x10a,0xc000);header(0,128);
    assert(sunLegacyVbios()==1); /* INT42 fallback */
    reset();vector(0x42,0xc020);vector(0x10a,0xc040);header(0,128);
    assert(sunLegacyVbios()==1); /* C0000 fallback */
    reset();header(0,128);assert(sunLegacyVbios()==0); /* uninitialized vector */
    reset();vector(0x42,0xffe0);header(0x3fe00,2);
    assert(sunLegacyVbios()==0);assert(maps==unmaps); /* overrun rejected */
    reset();assert(!sunKmsDevice());
    kms_open=1;assert(!sunKmsDevice()); /* node is not KMS */
    kms_result=0;assert(!sunKmsDevice()); /* headless DRM is not a display */
    connectors=1;assert(sunKmsDevice());
    puts("PASS: legacy BIOS, CSM, GOP, text console, UNKNOWN, ROM bounds, KMS capability");
    return 0;
}
'''
with tempfile.TemporaryDirectory(prefix="xorg-autodetect-") as directory:
    c = Path(directory) / "probe.c"
    c.write_text(fixture + probes + checks)
    binary = Path(directory) / "probe"
    subprocess.run([os.environ.get("CC", "cc"), "-std=c99", "-Wall", "-Wextra",
                    "-Wno-unused-parameter", str(c), "-o", str(binary)], check=True)
    subprocess.run([str(binary)], check=True)
