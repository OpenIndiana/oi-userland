/*
 * Copyright (c) 2006, 2013, Oracle and/or its affiliates. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/*
 * Copyright (c) 2012 Intel Corporation.  All rights reserved.
 */

#ifndef __DRM_SUN_PCI_H__
#define __DRM_SUN_PCI_H__

#include <sys/sunddi.h>
#include "drm_linux.h"
#define PCI_CONFIG_REGION_NUMS 6

struct pci_config_region {
	unsigned long start;
	unsigned long size;
};

struct pci_dev {
	struct drm_device *dev;
	ddi_acc_handle_t pci_cfg_acc_handle;

	uint16_t vendor;
	uint16_t device;
	struct pci_config_region regions[PCI_CONFIG_REGION_NUMS];
	int domain;
	int bus;
	int slot;
	int func;
	int irq;

	ddi_iblock_cookie_t intr_block;

	int msi_enabled;
	ddi_intr_handle_t *msi_handle;
	int msi_size;
	int msi_actual;
	uint_t msi_pri;
	int msi_flag;
};

#define pci_resource_start(pdev, bar) ((pdev)->regions[(bar)].start)
#define pci_resource_len(pdev, bar) ((pdev)->regions[(bar)].size)
#define pci_resource_end(pdev, bar)                    \
	((pci_resource_len((pdev), (bar)) == 0 &&      \
	pci_resource_start((pdev), (bar)) == 0) ? 0 :  \
	(pci_resource_start((pdev), (bar)) +           \
	pci_resource_len((pdev), (bar)) - 1))

extern uint8_t* pci_map_rom(struct pci_dev *pdev, size_t *size);
extern void pci_unmap_rom(struct pci_dev *pdev, uint8_t *base);
extern void pci_read_config_byte(struct pci_dev *dev, int where, u8 *val);
extern void pci_read_config_word(struct pci_dev *dev, int where, u16 *val);
extern void pci_read_config_dword(struct pci_dev *dev, int where, u32 *val);
extern void pci_write_config_byte(struct pci_dev *dev, int where, u8 val);
extern void pci_write_config_word(struct pci_dev *dev, int where, u16 val);
extern void pci_write_config_dword(struct pci_dev *dev, int where, u32 val);

extern int pci_find_capability(struct pci_dev *pdev, int capid);
extern struct pci_dev * pci_dev_create(struct drm_device *dev);
extern void pci_dev_destroy(struct pci_dev *pdev);

#endif /* __DRM_SUN_PCI_H__ */
