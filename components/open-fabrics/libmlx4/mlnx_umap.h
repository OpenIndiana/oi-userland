/*
 * Copyright (c) 2009, 2015, Oracle and/or its affiliates. All rights reserved.
 */

#ifndef	_SYS_IB_ADAPTERS_MLNX_UMAP_H
#define	_SYS_IB_ADAPTERS_MLNX_UMAP_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * mlnx_umap.h
 *	Contains all of the definions necessary for communicating the data
 *	needed for direct userland access to resources on Mellanox HCAs.
 */

/*
 * Note: The structs in this file are used in the interface(s)
 *	between kernel service drivers, e.g. daplt, and the libraries
 *	on top of them, e.g. udapl_tavor.so.1.  When any of the
 *	structs in this file change, any version control between the
 *	kernel service driver and the library will need to change.
 *
 * There is a version control on the structs defined here.  The library
 * (consumer of structs from ibt_ci_data_out()) must verify a version
 * field to correctly read the data provided by the kernel driver
 * (tavor, arbel, and hermon).
 */

#define	MLNX_UMAP_IF_VERSION	3

/*
 * The following defines are used in the database type field for each database
 * entry.  They specify the type of object (UAR pages, PIDs, CQ, QP, and MR
 * umemcookie) that corresponds to the database key value.  On database queries,
 * this type value must match the search criterion.
 */
#define	MLNX_UMAP_UARPG_RSRC		0x11
#define	MLNX_UMAP_BLUEFLAMEPG_RSRC	0x12
#define	MLNX_UMAP_PID_RSRC		0x22
#define	MLNX_UMAP_CQMEM_RSRC		0x33
#define	MLNX_UMAP_QPMEM_RSRC		0x44
#define	MLNX_UMAP_MRMEM_RSRC		0x55
#define	MLNX_UMAP_SRQMEM_RSRC		0x66
#define	MLNX_UMAP_DBRMEM_RSRC		0x77
#define	MLNX_UMAP_MRMEM_MAHDL		0x88
#define	MLNX_UMAP_RSRC_TYPE_MASK	0xFF
#define	MLNX_UMAP_RSRC_TYPE_SHIFT	8

/* umap structures */

typedef struct mlnx_umap_cq_data_out_s {
	uint32_t	mcq_rev;
	uint32_t	mcq_cqnum;
	uint64_t	mcq_mapoffset;
	uint64_t	mcq_maplen;
	uint32_t	mcq_numcqe;
	uint32_t	mcq_cqesz;

	/* Arbel/Hermon doorbell records */
	uint64_t	mcq_armdbr_mapoffset;
	uint64_t	mcq_armdbr_maplen;
	uint64_t	mcq_polldbr_mapoffset;
	uint64_t	mcq_polldbr_maplen;
	uint32_t	mcq_armdbr_offset;
	uint32_t	mcq_polldbr_offset;
} mlnx_umap_cq_data_out_t;

typedef struct mlnx_umap_qp_data_out_s {
	uint32_t	mqp_rev;
	uint32_t	mqp_qpnum;
	uint64_t	mqp_mapoffset;
	uint64_t	mqp_maplen;

	uint32_t	mqp_rq_off;
	uint32_t	mqp_rq_desc_addr;
	uint32_t	mqp_rq_numwqe;
	uint32_t	mqp_rq_wqesz;

	uint32_t	mqp_sq_off;
	uint32_t	mqp_sq_desc_addr;
	uint32_t	mqp_sq_numwqe;
	uint32_t	mqp_sq_wqesz;

	/* Arbel/Hermon doorbell records */
	uint64_t	mqp_sdbr_mapoffset;
	uint64_t	mqp_sdbr_maplen;
	uint64_t	mqp_rdbr_mapoffset;
	uint64_t	mqp_rdbr_maplen;
	uint32_t	mqp_sdbr_offset;
	uint32_t	mqp_rdbr_offset;

	/* Hermon send queue headroom, in units of wqes */
	uint32_t	mqp_sq_headroomwqes;
	uint32_t	mqp_reserved;
} mlnx_umap_qp_data_out_t;

typedef struct mlnx_umap_srq_data_out_s {
	uint32_t	msrq_rev;
	uint32_t	msrq_srqnum;
	uint64_t	msrq_mapoffset;
	uint64_t	msrq_maplen;
	uint32_t	msrq_desc_addr;
	uint32_t	msrq_numwqe;
	uint32_t	msrq_wqesz;
	uint32_t	msrq_pad1;	/* reserved */

	/* Arbel/Hermon doorbell records */
	uint64_t	msrq_rdbr_mapoffset;
	uint64_t	msrq_rdbr_maplen;
	uint32_t	msrq_rdbr_offset;
	uint32_t	msrq_reserved;
} mlnx_umap_srq_data_out_t;

typedef struct mlnx_umap_pd_data_out_s {
	uint32_t	mpd_pdnum;
	uint32_t	mpd_rev;
} mlnx_umap_pd_data_out_t;

/*
 * The following structure is used currently to pass data back to
 * libmlx4 on user allocation context.
 */
typedef struct mlnx_umap_ucontext_data_out_s {
	uint32_t	muc_qp_tab_size;
	uint16_t	muc_bf_reg_size;
	uint16_t	muc_bf_regs_per_page;
	uint32_t	muc_rev;
	uint32_t	muc_reserved;
} mlnx_umap_ucontext_data_out_t;

/*
 * Information for ibt_ci_data_in() for memory regions.
 *
 * MLNX_UMAP_MMR_DATA_IN_IF_VERSION is the value used in the mmr_rev member.
 * mmr_func is the callback handler.  mmr_arg1 and mmr_arg2 are its arguments.
 */
#define	MLNX_UMAP_MMR_DATA_IN_IF_VERSION	1
typedef struct mlnx_umap_mr_data_in_s {
	uint32_t  mmr_rev;
	uint32_t  mmr_reserved;
	void    (*mmr_func)(void *, void *);
	void    *mmr_arg1;
	void    *mmr_arg2;
} mlnx_umap_mr_data_in_t;

#ifdef __cplusplus
}
#endif

#endif	/* _SYS_IB_ADAPTERS_MLNX_UMAP_H */
