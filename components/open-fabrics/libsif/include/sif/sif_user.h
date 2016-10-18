/*
 * Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Userspace library for Oracle SIF Infiniband PCI Express
 * host channel adapter (HCA)
 *
 * sif_user.h: This file defines sif specific verbs extension request/response.
 *   This file is included both from user space and kernel space so
 *   it must not contain any kernel/user specific header file includes.
 */

#ifndef _SIF_USER_H
#define	_SIF_USER_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Binary interface control:
 *   Major version difference indicate backward incompatible changes
 *   Minor version difference indicate that only a common subset of
 *   features are available.
 *
 */
#define	SIF_UVERBS_ABI_MAJOR_VERSION	4
#define	SIF_UVERBS_ABI_MINOR_VERSION	0

/* Bw comp */
#define	SIF_UVERBS_VERSION(x, y) ((x) << 8 | (y))
#define	SIF_UVERBS_ABI_VERSION \
	SIF_UVERBS_VERSION(SIF_UVERBS_ABI_MAJOR_VERSION, \
	SIF_UVERBS_ABI_MINOR_VERSION)

/*
 * Bit 5 is not used by the PSIF_WC_OPCODE_FOO_BAR enums. Hence, using
 * it to indicate if QP has been destroyed before the CQE has been
 * polled
 */
#define	SIF_WC_QP_DESTROYED (1<<5)

/*
 * This struct will be amended to an un-polled cqe, in case the QP has
 * been destroyed before the CQEs are polled. The information is
 * needed in order to handle flushing of SRQs and generation of Last
 * WQE Reached event.
 *
 * The information amended to the CQE is _only_ valid if the CQE has
 * been marked with SIF_WC_QP_DESTROYED.
 */
struct sif_post_mortem_qp_info_in_cqe {
	int was_srq;
	int srq_idx;
	int qpn; /* Could be useful for de-bugging/logging */
};

#ifndef __u32
#define	__u32	uint32_t
#endif

/*
 * These definitions must be kept in sync with
 * the ones in libsif's sif.h
 */
typedef enum sif_vendor_flags {
	/*
	 * Use special mmu setup in associated mappings
	 * NB! Modifies input to ibv_reg_mr!
	 */
	MMU_special	= 0x1,
	/* Trigger send queue mode instead of using VCBs */
	SQ_mode		= 0x2,
	/* Enable EPS-A proxying - requires the eps_a field to be set */
	proxy_mode	= 0x4,
	/* Enable kernel mode - default is direct user mode */
	SVF_kernel_mode	= 0x8,
	/* Value to use for the qosl bit in the qp state */
	tsu_qosl	= 0x10
} sif_vendor_flags_t;

typedef enum sif_mem_type {
	SIFMT_BYPASS,	/* Use MMU bypass in associated mmu contexts */
	SIFMT_UMEM,	/* Normal default umem based user level mapping */
	/* Mapping of user memory based on the process' own page table */
	SIFMT_UMEM_SPT,
	/*
	 * A large (sparsely populated) SIF only vaddr mapping
	 * (used for a.o.SQ CMPL)
	 */
	SIFMT_CS,
	/* Special mapping of a vaddr range to a single page (see #1931) */
	SIFMT_ZERO,
	/* MMU bypass mapped read only for device (requires IOMMU enabled) */
	SIFMT_BYPASS_RO,
	/* GVA2GPA mapped read only for device (requires IOMMU enabled) */
	SIFMT_UMEM_RO,
	/* Use GVA2GPA but input is based on a phys_buf array instead of umem */
	SIFMT_PHYS,
	/*
	 * Use GVA2GPA but input is based on a page address array instead
	 * of umem
	 */
	SIFMT_FMR,
	/* Similar to FMR but input pages are 2M instead of 4K */
	SIFMT_2M,
	/* Bypass mode - special kernel mappings with no memory allocated */
	SIFMT_NOMEM,
	/* sif_kmem based 4K page allocation - mostly for test purposes */
	SIFMT_4K,
	SIFMT_RDMA,
	SIFMT_PTONLY,
	SIFMT_CTRL_PT,
	SIFMT_MAX
} sif_mem_type_t;

typedef enum sif_proxy_type {
	SIFPX_OFF, /* Default value - no proxying */
	SIFPX_EPSA_1,
	SIFPX_EPSA_2,
	SIFPX_EPSA_3,
	SIFPX_EPSA_4
} sif_proxy_type_t;


typedef enum sif_flush_type {
	NO_FLUSH,
	FLUSH_SQ,
	FLUSH_RQ
} sif_flush_type_t;

/* These should be multiple of 64 bytes and densely packed: */

typedef struct sif_get_context_ext {
	uint32_t abi_version;
	uint32_t reserved;
} sif_get_context_ext_t;

typedef struct sif_get_context_resp_ext {
	/* Distance in bytes between descriptor elements */
	uint32_t sq_sw_ext_sz;
	uint32_t rq_ext_sz;
	uint32_t cq_ext_sz;
	/* Number of entries per block of descriptors */
	uint32_t sq_entry_per_block;
	uint32_t rq_entry_per_block;
	uint32_t cq_entry_per_block;
	/* Dist between sq hw descriptor elms, from >= v.3.3 */
	uint32_t sq_hw_ext_sz;
	uint32_t reserved;
} sif_get_context_resp_ext_t;

typedef struct sif_alloc_pd_resp_ext {
	/* The virtual collect buffer to use by this protection domain */
	int cb_idx;
	uint32_t reserved;
} sif_alloc_pd_resp_ext_t;

typedef struct sif_share_pd_resp_ext {
	/* The virtual collect buffer to use by this shared protection domain */
	__u32 cb_idx;
	__u32 reserved;
} sif_share_pd_resp_ext_t;


typedef struct sif_create_cq_ext {
	enum sif_vendor_flags flags;
	enum sif_proxy_type proxy;
} sif_create_cq_ext_t;

typedef struct sif_create_cq_resp_ext {
	uint32_t cq_idx;
	uint32_t reserved;
	uint32_t cq_entries;
} sif_create_cq_resp_ext_t;


typedef struct sif_create_qp_ext {
	enum sif_vendor_flags flags;
	enum sif_proxy_type proxy;
} sif_create_qp_ext_t;

typedef struct sif_create_qp_resp_ext {
	uint32_t qp_idx;
	uint32_t rq_idx;
	uint32_t magic;
	uint32_t sq_extent;
	uint32_t rq_extent;
	uint32_t sq_sgl_offset;
	uint32_t sq_mr_idx;
	uint32_t reserved;
	uint64_t sq_dma_handle;
} sif_create_qp_resp_ext_t;

typedef struct sif_modify_qp_ext
{
	enum sif_flush_type flush;
	uint32_t  reserved;
} sif_modify_qp_ext_t;


typedef struct sif_reg_mr_ext {
	enum sif_vendor_flags flags;
	enum sif_mem_type mem_type;
	/* Used by gva_type SIFGT_ZERO - indicates psif vmap length */
	uint64_t map_length;
	/* Used by gva_type SIFGT_ZERO - indicates valid memory length */
	uint64_t phys_length;
} sif_reg_mr_ext_t;

typedef struct sif_reg_mr_resp_ext {
	uint64_t uv2dma;  /* Used to support bypass mode */
} sif_reg_mr_resp_ext_t;

typedef struct sif_create_srq_ext {
	enum sif_vendor_flags flags;
	uint32_t res1;
} sif_create_srq_ext_t;

typedef struct sif_create_srq_resp_ext {
	uint32_t index;
	uint32_t extent;
} sif_create_srq_resp_ext_t;

typedef struct sif_create_ah_resp_ext {
	uint32_t index;
	uint32_t reserved;
} sif_create_ah_resp_ext_t;

/* mmap offset encoding */

enum sif_mmap_cmd {
	SIF_MAP_NONE,	/* No mapping */
	/* Map a collect buffer - cb index as argument */
	SIF_MAP_CB,
	/* Map an SQ, RQ or CQ (entries) - queue index as argument */
	SIF_MAP_SQ,
	SIF_MAP_RQ,
	SIF_MAP_CQ,
	/*
	 * Map a block of SQ, RQ or CQ software descriptors -
	 * block index as argument
	 */
	SIF_MAP_SQ_SW,
	SIF_MAP_RQ_SW,
	SIF_MAP_CQ_SW,
	/* These are safe to map read-only (so far only sq_hw in use) */
	/* Map a block of qp descriptors - block index as argument */
	SIF_MAP_QP,
	/*
	 * Map a block of SQ, RQ or CQ hardware descriptors -
	 * block index as argument
	 */
	SIF_MAP_SQ_HW,
	SIF_MAP_RQ_HW,
	SIF_MAP_CQ_HW,
	SIF_MAP_MAX
};

static inline uint64_t mmap_set_cmd(enum sif_mmap_cmd cmd, uint32_t index)
{
	return ((uint64_t)cmd << 44) | ((uint64_t)index << 13);
}

static inline void mmap_get_cmd(uint64_t offset, enum sif_mmap_cmd *cmdp,
    uint32_t *idxp)
{
	*cmdp = (offset >> 44) & 0xff;
	*idxp = (offset >> 13) & 0x7fffffff;
}

#ifdef __cplusplus
}
#endif

#endif /* _SIF_USER_H */
