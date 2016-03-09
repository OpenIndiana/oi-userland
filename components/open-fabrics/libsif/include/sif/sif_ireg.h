/*
 * Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * Driver for Oracle PSIF Infiniband PCI Express host channel adapter (HCA)
 *
 * sif_ireg.h: Functions to interface with IBTF
 */


#ifndef _PSIF_IREG_H
#define	_PSIF_IREG_H

#include <sif.h>

#ifdef __cplusplus
extern "C" {
#endif




/* IB Device Registration */
int psif_register_ib_device(psif_t *psifp);
int psif_unregister_ib_device(psif_t *psifp);

/* Agent handling Registration */
int psif_agent_handlers_init(psif_t *psifp);
int psif_agent_handlers_fini(psif_t *psifp);

/* HCA and port related operations */
ibt_status_t psif_ci_query_hca_ports(ibc_hca_hdl_t, uint8_t,
    ibt_hca_portinfo_t *);
ibt_status_t psif_ci_modify_ports(ibc_hca_hdl_t, uint8_t,
    ibt_port_modify_flags_t, uint8_t);
ibt_status_t psif_ci_modify_system_image(ibc_hca_hdl_t, ib_guid_t);


/* Reliable Datagram Domains */
ibt_status_t psif_ci_alloc_rdd(ibc_hca_hdl_t, ibc_rdd_flags_t,
    ibc_rdd_hdl_t *);
ibt_status_t psif_ci_free_rdd(ibc_hca_hdl_t, ibc_rdd_hdl_t);

/* EE Contexts */
ibt_status_t psif_ci_alloc_eec(ibc_hca_hdl_t, ibc_eec_flags_t,
    ibt_eec_hdl_t, ibc_rdd_hdl_t, ibc_eec_hdl_t *);
ibt_status_t psif_ci_free_eec(ibc_hca_hdl_t, ibc_eec_hdl_t);
ibt_status_t psif_ci_query_eec(ibc_hca_hdl_t, ibc_eec_hdl_t,
    ibt_eec_query_attr_t *);
ibt_status_t psif_ci_modify_eec(ibc_hca_hdl_t, ibc_eec_hdl_t,
    ibt_cep_modify_flags_t, ibt_eec_info_t *);

/* Memory Windows */
ibt_status_t psif_ci_alloc_mw(ibc_hca_hdl_t, ibc_pd_hdl_t,
    ibt_mw_flags_t, ibc_mw_hdl_t *, ibt_rkey_t *);
ibt_status_t psif_ci_free_mw(ibc_hca_hdl_t, ibc_mw_hdl_t);
ibt_status_t psif_ci_query_mw(ibc_hca_hdl_t, ibc_mw_hdl_t,
    ibt_mw_query_attr_t *);

/* Multicast Groups */
ibt_status_t psif_ci_attach_mcg(ibc_hca_hdl_t, ibc_qp_hdl_t,
    ib_gid_t, ib_lid_t);
ibt_status_t psif_ci_detach_mcg(ibc_hca_hdl_t, ibc_qp_hdl_t,
    ib_gid_t, ib_lid_t);

/* Work Request and Completion Processing */
ibt_status_t psif_ci_post_send(ibc_hca_hdl_t, ibc_qp_hdl_t,
    ibt_send_wr_t *, uint_t, uint_t *);
ibt_status_t psif_ci_post_recv(ibc_hca_hdl_t, ibc_qp_hdl_t,
    ibt_recv_wr_t *, uint_t, uint_t *);
ibt_status_t psif_ci_poll_cq(ibc_hca_hdl_t, ibc_cq_hdl_t,
    ibt_wc_t *, uint_t, uint_t *);
ibt_status_t psif_ci_notify_cq(ibc_hca_hdl_t, ibc_cq_hdl_t,
    ibt_cq_notify_flags_t);

/* CI Object Private Data */
ibt_status_t psif_ci_ci_data_in(ibc_hca_hdl_t, ibt_ci_data_flags_t,
    ibt_object_type_t, void *, void *, size_t);

/* CI Object Private Data */
ibt_status_t psif_ci_ci_data_out(ibc_hca_hdl_t, ibt_ci_data_flags_t,
    ibt_object_type_t, void *, void *, size_t);


/* Address translation */
ibt_status_t psif_ci_map_mem_area(ibc_hca_hdl_t, ibt_va_attr_t *,
    void *, uint_t, ibt_reg_req_t *, ibc_ma_hdl_t *);
ibt_status_t psif_ci_unmap_mem_area(ibc_hca_hdl_t, ibc_ma_hdl_t);
ibt_status_t psif_ci_map_mem_iov(ibc_hca_hdl_t, ibt_iov_attr_t *,
    ibt_all_wr_t *, ibc_mi_hdl_t *);
ibt_status_t psif_ci_unmap_mem_iov(ibc_hca_hdl_t, ibc_mi_hdl_t);

/* Allocate L_Key */
ibt_status_t psif_ci_alloc_lkey(ibc_hca_hdl_t, ibc_pd_hdl_t,
    ibt_lkey_flags_t, uint_t, ibc_mr_hdl_t *, ibt_pmr_desc_t *);

/* Physical Register Memory Region */
ibt_status_t psif_ci_register_physical_mr(ibc_hca_hdl_t, ibc_pd_hdl_t,
    ibt_pmr_attr_t *, void *, ibc_mr_hdl_t *, ibt_pmr_desc_t *);
ibt_status_t psif_ci_reregister_physical_mr(ibc_hca_hdl_t,
    ibc_mr_hdl_t, ibc_pd_hdl_t, ibt_pmr_attr_t *, void *, ibc_mr_hdl_t *,
    ibt_pmr_desc_t *);

/* Mellanox FMR */
ibt_status_t psif_ci_create_fmr_pool(ibc_hca_hdl_t, ibc_pd_hdl_t,
    ibt_fmr_pool_attr_t *, ibc_fmr_pool_hdl_t *);
ibt_status_t psif_ci_destroy_fmr_pool(ibc_hca_hdl_t,
    ibc_fmr_pool_hdl_t);
ibt_status_t psif_ci_flush_fmr_pool(ibc_hca_hdl_t, ibc_fmr_pool_hdl_t);
ibt_status_t psif_ci_register_physical_fmr(ibc_hca_hdl_t,
    ibc_fmr_pool_hdl_t, ibt_pmr_attr_t *, void *, ibc_mr_hdl_t *,
    ibt_pmr_desc_t *);
ibt_status_t psif_ci_deregister_fmr(ibc_hca_hdl_t hca, ibc_mr_hdl_t mr);

/* Memory Allocation/Deallocation */

ibt_status_t
psif_ci_alloc_io_mem(ibc_hca_hdl_t, size_t, ibt_mr_flags_t, caddr_t *,
    ibt_mem_alloc_hdl_t);

ibt_status_t
psif_ci_get_hca_port_counters(ibc_hca_hdl_t, uint8_t,
    ibt_hca_port_cntr_flags_t, ibt_hca_port_counters_t *);

ibt_status_t
psif_ci_set_ibtl_private(ibc_hca_hdl_t, ibt_object_type_t, void *, void *);
ibt_status_t
psif_ci_get_ibtl_private(ibc_hca_hdl_t, ibt_object_type_t, void *, void **);

ibt_status_t
psif_ci_get_hca_resource_counters(ibc_hca_hdl_t,
    ibt_hca_resource_counters_t *);

ibt_status_t
psif_ci_alloc_counter(ibc_hca_hdl_t, ibt_ci_counter_type_t,
    ibc_counter_hdl_t *);
ibt_status_t
psif_ci_free_counter(ibc_hca_hdl_t, ibc_counter_hdl_t);
ibt_status_t
psif_ci_query_counter(ibc_hca_hdl_t, ibc_counter_hdl_t,
    ibt_ci_counters_t *);
ibt_status_t
psif_ci_reset_counter(ibc_hca_hdl_t, ibc_counter_hdl_t);
ibt_status_t
psif_ci_set_qp_counter(ibc_hca_hdl_t, ibc_counter_hdl_t,
ibc_qp_hdl_t *, uint_t);
ibt_status_t
psif_ci_get_qp_counter(ibc_hca_hdl_t, ibc_qp_hdl_t *,
    ibc_counter_hdl_t *, uint_t);
ibt_status_t psif_ci_not_supported();


/* Dma handle struct for the kmem cache */
typedef struct psif_dmahdl_cache_s {
	ddi_dma_handle_t h_dmahdl;
} psif_dmahdl_cache_t;
_NOTE(SCHEME_PROTECTS_DATA("safe sharing", psif_dmahdl_cache_s::h_dmahdl))

/* Address translation */
struct ibc_ma_s {
	int			h_ma_addr_list_len;
	void			*h_ma_addr_list;
	psif_dmahdl_cache_t	*h_ma_dmahdlp;  /* not FRWR */
	ddi_dma_handle_t	h_ma_dmahdl;	/* FRWR-only */
	ddi_dma_handle_t	h_ma_list_hdl;
	ddi_acc_handle_t	h_ma_list_acc_hdl;
	size_t			h_ma_real_len;
	caddr_t			h_ma_kaddr;
	ibt_phys_addr_t		h_ma_list_cookie;
	ddi_umem_cookie_t	h_ma_umem_cookie;
	ibc_mr_hdl_t		h_ma_mr_hdl;    /* used for umem callback */
};
_NOTE(SCHEME_PROTECTS_DATA("protected via umapdb scheme",
    ibc_ma_s::h_ma_mr_hdl))

extern uint32_t psif_max_cq_size;
extern uint32_t psif_max_srq_size;
extern uint32_t psif_max_sq_size;

#ifdef __cplusplus
}
#endif

#endif /* _PSIF_IREG_H */
