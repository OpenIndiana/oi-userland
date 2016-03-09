/*
 * Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef	_PSIF_HW_DATA_H
#define	_PSIF_HW_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "psif_api.h"

#define psif_port_flags psif_event
#define string_enum_psif_port_flags(data) string_enum_psif_event((enum psif_event)data)
#include "psif_endian.h"
#if !defined(__KERNEL__)
#include "os_header.h"
#endif

/* Extent of all psif enums */
enum psif_enum_extent {
	PSIF_MMU_TRANSLATION_EXTENT	 = 0x8,
	PSIF_PAGE_SIZE_EXTENT	 = 0xf,
	PSIF_WR_TYPE_EXTENT	 = 0x8f,
	PSIF_PORT_EXTENT	 = 0x2,
	PSIF_USE_AH_EXTENT	 = 0x2,
	PSIF_TSU_QOS_EXTENT	 = 0x2,
	PSIF_WC_OPCODE_EXTENT	 = 0x83,
	PSIF_WC_STATUS_EXTENT	 = 0x16,
	PSIF_TSL_QP_WR_EXTENT	 = 0x10,
	PSIF_TABLE_LEVEL_EXTENT	 = 0x6,
	IB_OPCODE_EXTENT	 = 0xca,
	PSIF_RB_TYPE_EXTENT	 = 0x7,
	PSIF_EPS_A_CORE_EXTENT	 = 0x4,
	PSIF_QP_STATE_EXTENT	 = 0x8,
	PSIF_CMPL_OUTSTANDING_ERROR_EXTENT	 = 0xa,
	PSIF_EXPECTED_OP_EXTENT	 = 0x4,
	PSIF_MIGRATION_EXTENT	 = 0x4,
	PSIF_QP_TRANS_EXTENT	 = 0x8,
	PSIF_BOOL_EXTENT	 = 0x2,
	PSIF_EOIB_TYPE_EXTENT	 = 0x4,
	PSIF_COMM_LIVE_EXTENT	 = 0x2,
	PSIF_PATH_MTU_EXTENT	 = 0x8,
	PSIF_USE_GRH_EXTENT	 = 0x2,
	PSIF_LOOPBACK_EXTENT	 = 0x2,
	PSIF_PORT_SPEED_EXTENT	 = 0x21,
	PSIF_PCIE_WR_OFFS_EXTENT	 = 0x1000,
	PSIF_QP_COMMAND_EXTENT	 = 0x4,
	PSIF_SIBS_MBOX_TYPE_EXTENT	 = 0x2,
	PSIF_MBOX_TYPE_EXTENT	 = 0x6,
	PSIF_DMA_VT_KEY_STATES_EXTENT	 = 0x4,
	PSIF_FLASH_IMAGE_TYPE_EXTENT	 = 0x5,
	PSIF_EVENT_EXTENT	 = 0x11,
	PSIF_TSU_ERROR_TYPES_EXTENT	 = 0x8c,
	PSIF_EPS_CORE_ID_EXTENT	 = 0x5,
	PSIF_EPSC_LOG_MODE_EXTENT	 = 0x11,
	PSIF_EPSC_LOG_LEVEL_EXTENT	 = 0x8,
	PSIF_EPSC_PORT_STATE_EXTENT	 = 0x6,
	PSIF_EPSC_PATH_MTU_EXTENT	 = 0x8,
	PSIF_EPSC_MONITOR_EXTENT	 = 0x5,
	PSIF_EPSC_INTERRUPT_SOURCE_EXTENT	 = 0x15,
	PSIF_EPSC_INTERRUPT_PRI_EXTENT	 = 0x4,
	PSIF_EPSC_ATOMIC_CAP_EXTENT	 = 0x3,
	PSIF_EPSC_CSR_STATUS_EXTENT	 = 0x100,
	PSIF_EPSC_CSR_OPCODE_EXTENT	 = 0x4f,
	PSIF_EPSC_CSR_FLAGS_EXTENT	 = 0x5,
	PSIF_VLINK_STATE_EXTENT	 = 0x11,
	PSIF_EPSC_CSR_MODIFY_DEVICE_FLAGS_EXTENT	 = 0x3,
	PSIF_EPSC_CSR_MODIFY_PORT_FLAGS_EXTENT	 = 0x11,
	PSIF_EPSC_CSR_EPSA_COMMAND_EXTENT	 = 0x4,
	PSIF_EPSA_COMMAND_EXTENT	 = 0xb,
	PSIF_EPSC_QUERY_OP_EXTENT	 = 0x4b,
	PSIF_EPSC_CSR_UPDATE_OPCODE_EXTENT	 = 0x8,
	PSIF_EPSC_FLASH_SLOT_EXTENT	 = 0x6,
	PSIF_EPSC_UPDATE_SET_EXTENT	 = 0x5,
	PSIF_EPSC_CSR_UF_CTRL_OPCODE_EXTENT	 = 0x9,
	PSIF_EPSC_VIMMA_CTRL_OPCODE_EXTENT	 = 0x8,
	PSIF_EPSC_VIMMA_ADMMODE_EXTENT	 = 0x2,
	PSIF_EPSC_CSR_PMA_COUNTERS_ENUM_EXTENT	 = 0x17,
	PSIF_EPSC_CSR_ATOMIC_OP_EXTENT	 = 0x4,
	PSIF_CQ_STATE_EXTENT	 = 0x4,
	PSIF_RSS_HASH_SOURCE_EXTENT	 = 0x2
}; /* enum psif_enum_extent [16 bits] */

/* MMU operation modes. */
enum psif_mmu_translation {
	MMU_PASS_THROUGH0,
	MMU_PASS_THROUGH_PAD,
	MMU_GVA2GPA_MODE,
	MMU_GVA2GPA_MODE_PAD,
	MMU_PRETRANSLATED,
	MMU_PRETRANSLATED_PAD,
	MMU_EPSA_MODE,
	MMU_EPSC_MODE
}; /* enum psif_mmu_translation [ 3 bits] */

/*
 * Enumeration for the different supported page sizes. XXX: Define the page
 * sizes
 */
enum psif_page_size {
	PAGE_SIZE_IA32E_4KB	 = 0,
	PAGE_SIZE_IA32E_2MB	 = 0x1,
	PAGE_SIZE_IA32E_1GB	 = 0x2,
	PAGE_SIZE_S64_8KB	 = 0x8,
	PAGE_SIZE_S64_64KB	 = 0x9,
	PAGE_SIZE_S64_512KB	 = 0xa,
	PAGE_SIZE_S64_4MB	 = 0xb,
	PAGE_SIZE_S64_32MB	 = 0xc,
	PAGE_SIZE_S64_2GB	 = 0xd,
	PAGE_SIZE_S64_16GB	 = 0xe
}; /* enum psif_page_size [ 4 bits] */

/*
 * These are the different work request opcodes supported by PSIF.
 * PSIF_WR_ENTER_SQ_MODE and PSIF_WR_CANCEL_CMD are special opcodes only used
 * when writing to a special offset of the VCBs. RQS must check that the
 * PSIF_WR_SEND_EPS and PSIF_WR_SEND_EPS_DR really comes from the EPS. CBU
 * must report the source of a WR to RQS.
 */
enum psif_wr_type {
	PSIF_WR_SEND,
	PSIF_WR_SEND_IMM,
	PSIF_WR_SPECIAL_QP_SEND,
	PSIF_WR_QP0_SEND_DR_XMIT,
	PSIF_WR_QP0_SEND_DR_LOOPBACK,
	PSIF_WR_EPS_SPECIAL_QP_SEND,
	PSIF_WR_EPS_QP0_SEND_DR_XMIT,
	PSIF_WR_EPS_QP0_SEND_DR_LOOPBACK,
	PSIF_WR_RDMA_WR,
	PSIF_WR_RDMA_WR_IMM,
	PSIF_WR_RDMA_RD,
	PSIF_WR_CMP_SWAP,
	PSIF_WR_FETCH_ADD,
	PSIF_WR_MASK_CMP_SWAP,
	PSIF_WR_MASK_FETCH_ADD,
	PSIF_WR_LSO,
	PSIF_WR_INVALIDATE_RKEY	 = 0x80,
	PSIF_WR_INVALIDATE_LKEY,
	PSIF_WR_INVALIDATE_BOTH_KEYS,
	PSIF_WR_INVALIDATE_TLB,
	PSIF_WR_RESIZE_CQ,
	PSIF_WR_SET_SRQ_LIM,
	PSIF_WR_SET_XRCSRQ_LIM,
	PSIF_WR_REQ_CMPL_NOTIFY,
	PSIF_WR_CMPL_NOTIFY_RCVD,
	PSIF_WR_REARM_CMPL_EVENT,
	PSIF_WR_GENERATE_COMPLETION,
	PSIF_WR_INVALIDATE_RQ,
	PSIF_WR_INVALIDATE_CQ,
	PSIF_WR_INVALIDATE_XRCSRQ,
	PSIF_WR_INVALIDATE_SGL_CACHE
}; /* enum psif_wr_type [ 8 bits] */

/* Port number the IB packet is transimitted on. */
enum psif_port {
	PORT_1	 = 0,
	PORT_2	 = 0x1
}; /* enum psif_port [ 1 bits] */

/*
 * Enumeration for using AHA or not. When set, AHA should be used instead of
 * information from the QP state in appropriate places.
 */
enum psif_use_ah {
	NO_AHA	 = 0,
	USE_AHA	 = 0x1
}; /* enum psif_use_ah [ 1 bits] */

/*
 * Indicating if this QP is configured as a high bandwidth or a low latency
 * QP.
 */
enum psif_tsu_qos {
	QOSL_HIGH_BANDWIDTH	 = 0,
	QOSL_LOW_LATENCY	 = 0x1
}; /* enum psif_tsu_qos [ 1 bits] */

/*
 * Completion entry opcode indicating what type of request this completion
 * entry is completed.
 */
enum psif_wc_opcode {
	PSIF_WC_OPCODE_SEND	 = 0,
	PSIF_WC_OPCODE_RDMA_WR	 = 0x1,
	PSIF_WC_OPCODE_RDMA_READ	 = 0x2,
	PSIF_WC_OPCODE_CMP_SWAP	 = 0x3,
	PSIF_WC_OPCODE_FETCH_ADD	 = 0x4,
	PSIF_WC_OPCODE_LSO	 = 0x6,
	PSIF_WC_OPCODE_MASKED_CMP_SWAP	 = 0x9,
	PSIF_WC_OPCODE_MASKED_FETCH_ADD,
	PSIF_WC_OPCODE_INVALIDATE_RKEY	 = 0x40,
	PSIF_WC_OPCODE_INVALIDATE_LKEY,
	PSIF_WC_OPCODE_INVALIDATE_BOTH_KEYS,
	PSIF_WC_OPCODE_INVALIDATE_TLB,
	PSIF_WC_OPCODE_RESIZE_CQ,
	PSIF_WC_OPCODE_SET_SRQ_LIM,
	PSIF_WC_OPCODE_SET_XRCSRQ_LIM,
	PSIF_WC_OPCODE_REQ_CMPL_NOTIFY,
	PSIF_WC_OPCODE_CMPL_NOTIFY_RCVD,
	PSIF_WC_OPCODE_REARM_CMPL_EVENT,
	PSIF_WC_OPCODE_GENERATE_COMPLETION,
	PSIF_WC_OPCODE_INVALIDATE_RQ,
	PSIF_WC_OPCODE_INVALIDATE_CQ,
	PSIF_WC_OPCODE_INVALIDATE_RB,
	PSIF_WC_OPCODE_INVALIDATE_XRCSRQ,
	PSIF_WC_OPCODE_INVALIDATE_SGL_CACHE,
	PSIF_WC_OPCODE_RECEIVE_SEND	 = 0x80,
	PSIF_WC_OPCODE_RECEIVE_RDMA_WR_IMM,
	PSIF_WC_OPCODE_RECEIVE_CONDITIONAL_WR_IMM
}; /* enum psif_wc_opcode [ 8 bits] */

/* Completion status for this completion. */
enum psif_wc_status {
	PSIF_WC_STATUS_SUCCESS,
	PSIF_WC_STATUS_LOC_LEN_ERR,
	PSIF_WC_STATUS_LOC_QP_OP_ERR,
	PSIF_WC_STATUS_LOC_EEC_OP_ERR,
	PSIF_WC_STATUS_LOC_PROT_ERR,
	PSIF_WC_STATUS_WR_FLUSH_ERR,
	PSIF_WC_STATUS_MW_BIND_ERR,
	PSIF_WC_STATUS_BAD_RESP_ERR,
	PSIF_WC_STATUS_LOC_ACCESS_ERR,
	PSIF_WC_STATUS_REM_INV_REQ_ERR,
	PSIF_WC_STATUS_REM_ACCESS_ERR,
	PSIF_WC_STATUS_REM_OP_ERR,
	PSIF_WC_STATUS_RETRY_EXC_ERR,
	PSIF_WC_STATUS_RNR_RETRY_EXC_ERR,
	PSIF_WC_STATUS_LOC_RDD_VIOL_ERR,
	PSIF_WC_STATUS_REM_INV_RD_REQ_ERR,
	PSIF_WC_STATUS_REM_ABORT_ERR,
	PSIF_WC_STATUS_INV_EECN_ERR,
	PSIF_WC_STATUS_INV_EEC_STATE_ERR,
	PSIF_WC_STATUS_FATAL_ERR,
	PSIF_WC_STATUS_RESP_TIMEOUT_ERR,
	PSIF_WC_STATUS_GENERAL_ERR,
	/* Padding out to required bits allocated */
	PSIF_WC_STATUS_FIELD_MAX	 = 0xff
}; /* enum psif_wc_status [ 8 bits] */

/* TSU Service level required in the QP and WR */
enum psif_tsl_qp_wr {
	/* Dataplane traffic separated in 4 TSLs */
	TSL_DATA,
	TSL_DATA_1,
	TSL_DATA_2,
	TSL_DATA_3,
	/* TSL for privelidge QP */
	TSL_PRIV	 = 0xe,
	/* Strapped down TSL for testing */
	TSL_JUNK	 = 0xf
}; /* enum psif_tsl_qp_wr [ 4 bits] */

/* MMU table level definition
 *  If page level is not applicable it should be set to  PAGE_LEVEL0
 *  Values beyond PAGE_LEVEL4 (5-7) are reserved by HW
 */
enum psif_table_level {
	/* */
	PAGE_LEVEL0	 = 0,
	PAGE_LEVEL1,
	PAGE_LEVEL2,
	PAGE_LEVEL3,
	/* PAGE_LEVEL4 is SPARC only ? */
	PAGE_LEVEL4,
	PAGE_LEVEL_RESERVED
}; /* enum psif_table_level [ 3 bits] */


enum ib_opcode {
	RC_SEND_First	 = 0,
	RC_SEND_Middle	 = 0x1,
	RC_SEND_Last	 = 0x2,
	RC_SEND_Last_Imm	 = 0x3,
	RC_SEND_Only	 = 0x4,
	RC_SEND_Only_Imm	 = 0x5,
	RC_RDMA_WR_First	 = 0x6,
	RC_RDMA_WR_Middle	 = 0x7,
	RC_RDMA_WR_Last	 = 0x8,
	RC_RDMA_WR_Last_Imm	 = 0x9,
	RC_RDMA_WR_Only	 = 0xa,
	RC_RDMA_WR_Only_Imm	 = 0xb,
	RC_RDMA_RD_Req	 = 0xc,
	RC_RDMA_RD_Resp_First	 = 0xd,
	RC_RDMA_RD_Resp_Middle	 = 0xe,
	RC_RDMA_RD_Resp_Last	 = 0xf,
	RC_RDMA_RD_Resp_Only	 = 0x10,
	RC_ACK	 = 0x11,
	RC_Atomic_ACK	 = 0x12,
	RC_CmpSwap	 = 0x13,
	RC_FetchAdd	 = 0x14,
	RC_Reserved	 = 0x15,
	RC_SEND_Last_Invalid	 = 0x16,
	RC_SEND_Only_Invalid	 = 0x17,
	RC_MaskCmpSwap	 = 0x18,
	RC_MaskFetchAdd	 = 0x19,
	UC_SEND_First	 = 0x20,
	UC_SEND_Middle	 = 0x21,
	UC_SEND_Last	 = 0x22,
	UC_SEND_Last_Imm	 = 0x23,
	UC_SEND_Only	 = 0x24,
	UC_SEND_Only_Imm	 = 0x25,
	UC_RDMA_WR_First	 = 0x26,
	UC_RDMA_WR_Middle	 = 0x27,
	UC_RDMA_WR_Last	 = 0x28,
	UC_RDMA_WR_Last_Imm	 = 0x29,
	UC_RDMA_WR_Only	 = 0x2a,
	UC_RDMA_WR_Only_Imm	 = 0x2b,
	RD_SEND_First	 = 0x40,
	RD_SEND_Middle	 = 0x41,
	RD_SEND_Last	 = 0x42,
	RD_SEND_Last_Imm	 = 0x43,
	RD_SEND_Only	 = 0x44,
	RD_SEND_Only_Imm	 = 0x45,
	RD_RDMA_WR_First	 = 0x46,
	RD_RDMA_WR_Middle	 = 0x47,
	RD_RDMA_WR_Last	 = 0x48,
	RD_RDMA_WR_Last_Imm	 = 0x49,
	RD_RDMA_WR_Only	 = 0x4a,
	RD_RDMA_WR_Only_Imm	 = 0x4b,
	RD_RDMA_RD_Req	 = 0x4c,
	RD_RDMA_RD_Resp_First	 = 0x4d,
	RD_RDMA_RD_Resp_Middle	 = 0x4e,
	RD_RDMA_RD_Resp_Last	 = 0x4f,
	RD_RDMA_RD_Resp_Only	 = 0x50,
	RD_ACK	 = 0x51,
	RD_Atomic_ACK	 = 0x52,
	RD_CmpSwap	 = 0x53,
	RD_FetchAdd	 = 0x54,
	RD_RESYNC	 = 0x55,
	UD_SEND_Only	 = 0x64,
	UD_SEND_Only_Imm	 = 0x65,
	CNP	 = 0x80,
	XRC_SEND_First	 = 0xa0,
	XRC_SEND_Middle	 = 0xa1,
	XRC_SEND_Last	 = 0xa2,
	XRC_SEND_Last_Imm	 = 0xa3,
	XRC_SEND_Only	 = 0xa4,
	XRC_SEND_Only_Imm	 = 0xa5,
	XRC_RDMA_WR_First	 = 0xa6,
	XRC_RDMA_WR_Middle	 = 0xa7,
	XRC_RDMA_WR_Last	 = 0xa8,
	XRC_RDMA_WR_Last_Imm	 = 0xa9,
	XRC_RDMA_WR_Only	 = 0xaa,
	XRC_RDMA_WR_Only_Imm	 = 0xab,
	XRC_RDMA_RD_Req	 = 0xac,
	XRC_RDMA_RD_Resp_First	 = 0xad,
	XRC_RDMA_RD_Resp_Middle	 = 0xae,
	XRC_RDMA_RD_Resp_Last	 = 0xaf,
	XRC_RDMA_RD_Resp_Only	 = 0xb0,
	XRC_ACK	 = 0xb1,
	XRC_Atomic_ACK	 = 0xb2,
	XRC_CmpSwap	 = 0xb3,
	XRC_FetchAdd	 = 0xb4,
	XRC_Reserved	 = 0xb5,
	XRC_SEND_Last_Invalid	 = 0xb6,
	XRC_SEND_Only_Invalid	 = 0xb7,
	XRC_MaskCmpSwap	 = 0xb8,
	XRC_MaskFetchAdd	 = 0xb9,
	MANSP1_INVALID	 = 0xc0,
	MANSP1_HOST_READ	 = 0xc1,
	MANSP1_HOST_WRITE	 = 0xc2,
	MANSP1_HOST_READ_NO_DMAVT	 = 0xc3,
	MANSP1_HOST_WRITE_NO_DMAVT	 = 0xc4,
	MANSP1_INTERNAL_TYPE	 = 0xc5,
	MANSP1_INTERNAL_TYPE_MMU_BYPASS	 = 0xc6,
	MANSP1_HOST_CMP_SWAP	 = 0xc7,
	MANSP1_DR_LOOPBACK	 = 0xc8,
	MANSP1_ARP_LOOPBACK	 = 0xc9
}; /* enum ib_opcode [ 8 bits] */

/*
 * This is a ring buffer type defining the type of transaction this
 * represents.
 */
enum psif_rb_type {
	PSIF_RB_TYPE_INVALID,
	PSIF_RB_TYPE_DM_PUT,
	PSIF_RB_TYPE_DM_GET_RESP,
	PSIF_RB_TYPE_RCV_PROXY_COMPLETION,
	PSIF_RB_TYPE_RCV_PROXY_COMPLETION_AND_DATA,
	PSIF_RB_TYPE_SEND_PROXY_COMPLETION,
	PSIF_RB_TYPE_SEND_COMPLETION
}; /* enum psif_rb_type [ 3 bits] */

/*
 * Core number for EPS-A.1 PSIF_EPS_A_1 PSIF_EPS_A_2 PSIF_EPS_A_3
 * PSIF_EPS_A_4
 */
enum psif_eps_a_core {
	PSIF_EPS_A_1,
	PSIF_EPS_A_2,
	PSIF_EPS_A_3,
	PSIF_EPS_A_4
}; /* enum psif_eps_a_core [ 2 bits] */

/* This is the state this QP is in. */
enum psif_qp_state {
	PSIF_QP_STATE_RESET	 = 0,
	PSIF_QP_STATE_INIT	 = 0x1,
	PSIF_QP_STATE_RTR	 = 0x2,
	PSIF_QP_STATE_RTS	 = 0x3,
	PSIF_QP_STATE_SQERR	 = 0x5,
	PSIF_QP_STATE_ERROR	 = 0x6,
	PSIF_QP_STATE_INVALID	 = 0x7
}; /* enum psif_qp_state [ 3 bits] */

/*
 * CMPL_NO_ERROR CMPL_RQS_INVALID_REQUEST_ERR CMPL_RQS_QP_IN_WRONG_STATE_ERR
 * CMPL_RQS_MAX_OUTSTANDING_REACHED_ERR CMPL_RQS_REQUEST_FENCED_ERR
 * CMPL_RQS_CMD_FROM_EPS_ERR CMPL_DMA_SGL_RD_ERR CMPL_DMA_PYLD_RD_ERR
 * CMPL_DMA_SGL_LENGTH_ERR CMPL_DMA_LKEY_ERR
 */
enum psif_cmpl_outstanding_error {
	CMPL_NO_ERROR,
	CMPL_RQS_INVALID_REQUEST_ERR,
	CMPL_RQS_QP_IN_WRONG_STATE_ERR,
	CMPL_RQS_MAX_OUTSTANDING_REACHED_ERR,
	CMPL_RQS_REQUEST_FENCED_ERR,
	CMPL_RQS_CMD_FROM_EPS_ERR,
	CMPL_DMA_SGL_RD_ERR,
	CMPL_DMA_PYLD_RD_ERR,
	CMPL_DMA_SGL_LENGTH_ERR,
	CMPL_DMA_LKEY_ERR
}; /* enum psif_cmpl_outstanding_error [ 4 bits] */

/*
 * 2 bits (next_opcode) 0x0: No operation in progress 0x1: Expect SEND middle
 * or last 0x2: Expect RDMA_WR middle or last 0x3: Expect DM_PUT middle or
 * last
 */
enum psif_expected_op {
	NO_OPERATION_IN_PROGRESS	 = 0,
	EXPECT_SEND_MIDDLE_LAST	 = 0x1,
	EXPECT_RDMA_WR_MIDDLE_LAST	 = 0x2,
	EXPECT_DM_PUT_MIDDLE_LAST	 = 0x3
}; /* enum psif_expected_op [ 2 bits] */

/*
 * Migration state (migrated, re-arm and armed). XXX: Assign values to the
 * states.
 */
enum psif_migration {
	APM_OFF,
	APM_MIGRATED,
	APM_REARM,
	APM_ARMED
}; /* enum psif_migration [ 2 bits] */

/*
 * 3 bits (transport) 0x0: RC - Reliable connection. 0x1: UC - Unreliable
 * connection. 0x2: RD - Reliable datagram - not supported. 0x3: UD -
 * Unreliable datagram. 0x4: RSVD1 0x5: XRC - Extended reliable connection.
 * 0x6: MANSP1 - manufacturer specific opcodes. 0x7: MANSP2 - manufacturer
 * specific opcodes.
 */
enum psif_qp_trans {
	PSIF_QP_TRANSPORT_RC	 = 0,
	PSIF_QP_TRANSPORT_UC	 = 0x1,
	PSIF_QP_TRANSPORT_RD	 = 0x2,
	PSIF_QP_TRANSPORT_UD	 = 0x3,
	PSIF_QP_TRANSPORT_RSVD1	 = 0x4,
	PSIF_QP_TRANSPORT_XRC	 = 0x5,
	PSIF_QP_TRANSPORT_MANSP1	 = 0x6,
	PSIF_QP_TRANSPORT_MANSP2	 = 0x7
}; /* enum psif_qp_trans [ 3 bits] */


enum psif_bool {
	FALSE	 = 0,
	TRUE	 = 0x1
}; /* enum psif_bool [ 1 bits] */

/*
 * EoIB types enumerated type having these enumerations: EOIB_FULL,
 * EOIB_PARTIAL, EOIB_QKEY_ONLY, EOIB_NONE.
 */
enum psif_eoib_type {
	EOIB_FULL,
	EOIB_PARTIAL,
	EOIB_QKEY_ONLY,
	EOIB_NONE
}; /* enum psif_eoib_type [ 2 bits] */

/*
 * Communication established state. This gets set when a packet is received
 * error free when in RTR state.
 */
enum psif_comm_live {
	NO_COMM_ESTABLISHED	 = 0,
	COMM_ESTABLISHED	 = 0x1
}; /* enum psif_comm_live [ 1 bits] */

/* Definitions for the different supported MTU sizes. */
enum psif_path_mtu {
	MTU_INVALID	 = 0,
	MTU_256B	 = 0x1,
	MTU_512B	 = 0x2,
	MTU_1024B	 = 0x3,
	MTU_2048B	 = 0x4,
	MTU_4096B	 = 0x5,
	MTU_10240B	 = 0x6,
	MTU_XXX	 = 0x7
}; /* enum psif_path_mtu [ 3 bits] */

/* Enumeration for using GRH or not. When set GRH should be used. */
enum psif_use_grh {
	NO_GRH	 = 0,
	USE_GRH	 = 0x1
}; /* enum psif_use_grh [ 1 bits] */

/* Enumeration for loopback indication NO_LOOPBACK = 0 LOOPBACK = 1. */
enum psif_loopback {
	NO_LOOPBACK	 = 0,
	LOOPBACK	 = 0x1
}; /* enum psif_loopback [ 1 bits] */

/*
 * Should match definitions in ib_verbs.h
 */
enum psif_port_speed {
	PSIF_SPEED_SDR	 = 0x1,
	PSIF_SPEED_DDR	 = 0x2,
	PSIF_SPEED_QDR	 = 0x4,
	PSIF_SPEED_FDR10	 = 0x8,
	PSIF_SPEED_FDR	 = 0x10,
	PSIF_SPEED_EDR	 = 0x20,
	/* Padding out to required bits allocated */
	PSIF_PORT_SPEED_FIELD_MAX	 = 0xff
}; /* enum psif_port_speed [ 8 bits] */

/* Depricated data type... */
enum psif_pcie_wr_offs {
	WR_CB_START_OFFS	 = 0,
	WR_CB_LAST_OFFS	 = 0x140,
	WR_SQS_DOORBELL_OFFS	 = 0xfc0,
	WR_CB_CLEAR_OFFS	 = 0xff8,
	WR_MAX_BAR_OFFS	 = 0xfff
}; /* enum psif_pcie_wr_offs [12 bits] */

/* Commands used for modify/query QP. */
enum psif_qp_command {
	QP_CMD_INVALID	 = 0,
	QP_CMD_MODIFY	 = 0x1,
	QP_CMD_QUERY	 = 0x2,
	QP_CMD_CHECK_TIMEOUT	 = 0x3
}; /* enum psif_qp_command [ 2 bits] */


enum psif_sibs_mbox_type {
	SIBS_MBOX_EPSC,
	SIBS_MBOX_EPS_MAX,
	/* Padding out to required bits allocated */
	PSIF_SIBS_MBOX_TYPE_FIELD_MAX	 = 0xff
}; /* enum psif_sibs_mbox_type [ 8 bits] */


enum psif_mbox_type {
	MBOX_EPSA0,
	MBOX_EPSA1,
	MBOX_EPSA2,
	MBOX_EPSA3,
	MBOX_EPSC,
	MBOX_EPS_MAX,
	/* Padding out to required bits allocated */
	PSIF_MBOX_TYPE_FIELD_MAX	 = 0xff
}; /* enum psif_mbox_type [ 8 bits] */

/*
 * DMA Validation Key states. The valid states are: PSIF_DMA_KEY_INVALID=0
 * PSIF_DMA_KEY_FREE = 1 PSIF_DMA_KEY_VALID = 2 PSIF_DMA_KEY_MMU_VALID
 */
enum psif_dma_vt_key_states {
	PSIF_DMA_KEY_INVALID	 = 0,
	PSIF_DMA_KEY_FREE	 = 0x1,
	PSIF_DMA_KEY_VALID	 = 0x2,
	PSIF_DMA_KEY_MMU_VALID	 = 0x3
}; /* enum psif_dma_vt_key_states [ 2 bits] */

/**
 * Flash image types. More comming...
 */
enum psif_flash_image_type {
	PSIF_IMAGE_INVALID	 = 0,
	PSIF_IMAGE_BOOT_LOADER	 = 0x1,
	PSIF_IMAGE_EPS_C_APPLICATION	 = 0x2,
	PSIF_IMAGE_EPS_A_APPLICATION	 = 0x3,
	PSIF_IMAGE_DIAGNOSTICS	 = 0x4,
	/* Padding out to required bits allocated */
	PSIF_FLASH_IMAGE_TYPE_FIELD_MAX	 = 0x7fffffff
}; /* enum psif_flash_image_type [32 bits] */

/** \brief SW EQ event type
 *  \details
 *  Software events use `eq_entry::port_flags` for the event type. As this is
 *  limited to 4 bits the special value `PSIF_EVENT_EXTENSION` is used to
 *  indicate that the actual event type is to be found in
 *  `eq_entry::extension_type`. This is done for all enum values larger than
 *  4 bits.
 *
 * \par Width
 *      32 bit
 * \par Used in
 *      struct psif_eq_entry
 * \par Restrictions
 *      none (all UF)
 * \par Classification
 *      driver
 */
enum psif_event {
	/** Event without a reason... */
	PSIF_EVENT_NO_CHANGE	 = 0,
	/** GID table have been updated */
	PSIF_EVENT_SGID_TABLE_CHANGED,
	/** PKEY table have been updated by the SM */
	PSIF_EVENT_PKEY_TABLE_CHANGED,
	/** SM lid have been updated by master SM */
	PSIF_EVENT_MASTER_SM_LID_CHANGED,
	/** The SMs SL have changed */
	PSIF_EVENT_MASTER_SM_SL_CHANGED,
	/** */
	PSIF_EVENT_SUBNET_TIMEOUT_CHANGED,
	/** */
	PSIF_EVENT_IS_SM_DISABLED_CHANGED,
	/** New master SM - client must reregister */
	PSIF_EVENT_CLIENT_REREGISTER,
	/** vHCA have been assigned a new LID */
	PSIF_EVENT_LID_TABLE_CHANGED,
	/** */
	PSIF_EVENT_EPSC_COMPLETION,
	/** Mailbox request handled (only if EPSC_FL_NOTIFY was set in the request) */
	PSIF_EVENT_MAILBOX,
	/** The real event type value is found in `eq_entry::extension_type` */
	PSIF_EVENT_EXTENSION,
	/** Host should retrieve the EPS log for persistent storage */
	PSIF_EVENT_LOG,
	/** */
	PSIF_EVENT_PORT_ACTIVE,
	/** */
	PSIF_EVENT_PORT_ERR,
	/** Event queue full (replaces the actual event) */
	PSIF_EVENT_QUEUE_FULL,
	/** FW entered degraded mode */
	PSIF_EVENT_DEGRADED_MODE,
	/* Padding out to required bits allocated */
	PSIF_EVENT_FIELD_MAX	 = 0x7fffffff
}; /* enum psif_event [32 bits] */

/*
 * Enumerations of error types. The following error types are defined for the
 * TSU: TSU_NO_ERROR = 8'h0 TSU_IBPR_ICRC_ERR TSU_IBPR_INVALID_PKEY_ERR
 * TSU_IBPR_INVALID_QP_ERR TSU_IBPR_VSWITCH_UF_ERR
 * TSU_IBPR_UNDEFINED_OPCODE_ERR TSU_IBPR_MCAST_NO_GRH_ERR
 * TSU_IBPR_MCAST_NO_TARGET_ERR TSU_IBPR_INVALID_DGID_ERR TSU_IBPR_BADPKT_ERR
 * TSU_RCV_QP_INVALID_ERR TSU_RCV_HDR_BTH_TVER_ERR TSU_RCV_HDR_BTH_QP_ERR
 * TSU_RCV_HDR_GRH_ERR TSU_RCV_HDR_PKEY_ERR TSU_RCV_HDR_QKEY_ERR
 * TSU_RCV_HDR_LID_ERR TSU_RCV_HDR_MAD_ERR TSU_RCV_EOIB_MCAST_ERR
 * TSU_RCV_EOIB_BCAST_ERR TSU_RCV_EOIB_UCAST_ERR TSU_RCV_EOIB_FRAGMENT_ERR
 * TSU_RCV_EOIB_RUNTS_ERR TSU_RCV_EOIB_OUTER_VLAN_ERR
 * TSU_RCV_EOIB_VLAN_TAG_ERR TSU_RCV_EOIB_VID_ERR TSU_RCV_MCAST_DUP_ERR
 * TSU_RCV_ECC_ERR TSU_DSCR_RESPONDER_RC_PSN_ERR
 * TSU_DSCR_RESPONDER_RC_DUPLICATE TSU_DSCR_RESPONDER_RC_OPCODE_SEQ_ERR
 * TSU_DSCR_RESPONDER_RC_OPCODE_VAL_ERR TSU_DSCR_RESPONDER_RC_OPCODE_LEN_ERR
 * TSU_DSCR_RESPONDER_RC_DMALEN_ERR TSU_DSCR_RESPONDER_XRC_PSN_ERR
 * TSU_DSCR_RESPONDER_XRC_DUPLICATE TSU_DSCR_RESPONDER_XRC_OPCODE_SEQ_ERR
 * TSU_DSCR_RESPONDER_XRC_OPCODE_VAL_ERR
 * TSU_DSCR_RESPONDER_XRC_OPCODE_LEN_ERR TSU_DSCR_RESPONDER_XRC_DMALEN_ERR
 * TSU_DSCR_RESPONDER_UC_PSN_ERR TSU_DSCR_RESPONDER_UC_OPCODE_SEQ_ERR
 * TSU_DSCR_RESPONDER_UC_OPCODE_VAL_ERR TSU_DSCR_RESPONDER_UC_OPCODE_LEN_ERR
 * TSU_DSCR_RESPONDER_UC_DMALEN_ERR TSU_DSCR_RESPONDER_UD_OPCODE_LEN_ERR
 * TSU_DSCR_RESPONDER_DUPLICATE_WITH_ERR
 * TSU_DSCR_QP_CAP_MASKED_ATOMIC_ENABLE_ERR
 * TSU_DSCR_QP_CAP_RDMA_RD_ENABLE_ERR TSU_DSCR_QP_CAP_RDMA_WR_ENABLE_ERR
 * TSU_DSCR_QP_CAP_ATOMIC_ENABLE_ERR TSU_DSCR_XRC_DOMAIN_VIOLATION_ERR
 * TSU_DSCR_XRCETH_ERR TSU_DSCR_RQ_INVALID_ERR TSU_DSCR_RQ_PD_CHECK_ERR
 * TSU_DSCR_RQ_EMPTY_ERR TSU_DSCR_RQ_IN_ERROR_ERR
 * TSU_DSCR_TRANSLATION_TYPE_ERR TSU_DSCR_RQ_DESCRIPTOR_INCONSISTENT_ERR
 * TSU_DSCR_PCIE_ERR TSU_DSCR_ECC_ERR TSU_RQH_PCIE_ERR TSU_RQH_SGL_LKEY_ERR
 * TSU_RQH_NOT_ENOUGH_RQ_SPACE_ERR TSU_RQH_ECC_ERR TSU_VAL_DUPLICATE_WITH_ERR
 * TSU_VAL_RKEY_VLD_ERR TSU_VAL_RKEY_ADDR_RANGE_ERR TSU_VAL_RKEY_ACCESS_ERR
 * TSU_VAL_RKEY_PD_ERR TSU_VAL_RKEY_RANGE_ERR TSU_VAL_LKEY_VLD_ERR
 * TSU_VAL_LKEY_ADDR_RANGE_ERR TSU_VAL_LKEY_ACCESS_ERR TSU_VAL_LKEY_PD_ERR
 * TSU_VAL_LKEY_RANGE_ERR TSU_VAL_TRANSLATION_TYPE_ERR TSU_VAL_PCIE_ERR
 * TSU_VAL_ECC_ERR TSU_MMU_DUPLICATE_WITH_ERR TSU_MMU_PTW_ERR TSU_MMU_UF_ERR
 * TSU_MMU_AC_ERR TSU_MMU_ECC_ERR TSU_CBLD_CQ_INVALID_ERR
 * TSU_CBLD_CQ_FULL_ERR TSU_CBLD_CQ_IS_PROXY_ERR
 * TSU_CBLD_TRANSLATION_TYPE_ERR TSU_CBLD_CQ_DESCRIPTOR_INCONSISTENT_ERR
 * TSU_CBLD_ECC_ERR TSU_CBLD_QP_ERR TSU_RQS_CHECKSUM_ERR TSU_RQS_SEQNUM_ERR
 * TSU_RQS_INVALID_REQUEST_ERR TSU_RQS_QP_IN_WRONG_STATE_ERR
 * TSU_RQS_STOP_TIMER_ERR TSU_RQS_CMD_FROM_EPS_ERR TSU_RQS_SQ_FLUSH_ERR
 * TSU_RQS_SMP_NOT_AUTH_ERR TSU_RQS_REQUEST_FENCED_ERR
 * TSU_RQS_MAX_OUTSTANDING_REACHED_ERR TSU_RQS_ECC_ERR
 * TSU_RQS_EOIB_QKEY_VIOLATION TSU_RQS_IPOIB_QKEY_VIOLATION
 * TSU_RQS_EOIB_MODE_VIOLATION TSU_RQS_MISCONFIGURED_QP
 * TSU_RQS_PORT_AUTH_VIOLATION TSU_DMA_SGL_RD_ERR TSU_DMA_PYLD_RD_ERR
 * TSU_DMA_SGL_LENGTH_ERR TSU_DMA_LKEY_ERR TSU_DMA_RKEY_ERR
 * TSU_DMA_LSO_PKTLEN_ERR TSU_DMA_LSO_ILLEGAL_CLASSIFICATION_ERR
 * TSU_DMA_PCIE_ERR TSU_DMA_ECC_ERR TSU_CMPL_PCIE_ERR TSU_CMPL_ECC_ERR
 * TSU_CMPL_REQUESTER_PSN_ERR TSU_CMPL_REQUESTER_SYNDROME_ERR
 * TSU_CMPL_REQUESTER_OUTSTANDING_MATCH_ERR TSU_CMPL_REQUESTER_LEN_ERR
 * TSU_CMPL_REQUESTER_UNEXP_OPCODE_ERR TSU_CMPL_REQUESTER_DUPLICATE
 * TSU_CMPL_RC_IN_ERROR_ERR TSU_CMPL_NAK_RNR_ERR TSU_CMPL_NAK_SEQUENCE_ERR
 * TSU_CMPL_NAK_INVALID_REQUEST_ERR TSU_CMPL_NAK_REMOTE_ACCESS_ERR
 * TSU_CMPL_NAK_REMOTE_OPS_ERR TSU_CMPL_NAK_INVALID_RD_REQUEST_ERR
 * TSU_CMPL_TIMEOUT_ERR TSU_CMPL_IMPLIED_NAK TSU_CMPL_GHOST_RESP_ERR
 */
enum psif_tsu_error_types {
	TSU_NO_ERROR	 = 0,
	TSU_IBPR_ICRC_ERR,
	TSU_IBPR_INVALID_PKEY_ERR,
	TSU_IBPR_INVALID_QP_ERR,
	TSU_IBPR_VSWITCH_UF_ERR,
	TSU_IBPR_PKTLEN_ERR,
	TSU_IBPR_UNDEFINED_OPCODE_ERR,
	TSU_IBPR_MCAST_NO_GRH_ERR,
	TSU_IBPR_MCAST_NO_TARGET_ERR,
	TSU_IBPR_INVALID_DGID_ERR,
	TSU_IBPR_BADPKT_ERR,
	TSU_RCV_QP_INVALID_ERR,
	TSU_RCV_HDR_BTH_TVER_ERR,
	TSU_RCV_HDR_BTH_QP_ERR,
	TSU_RCV_HDR_GRH_ERR,
	TSU_RCV_HDR_PKEY_ERR,
	TSU_RCV_HDR_QKEY_ERR,
	TSU_RCV_HDR_LID_ERR,
	TSU_RCV_HDR_MAD_ERR,
	TSU_RCV_EOIB_MCAST_ERR,
	TSU_RCV_EOIB_BCAST_ERR,
	TSU_RCV_EOIB_UCAST_ERR,
	TSU_RCV_EOIB_TCP_PORT_VIOLATION_ERR,
	TSU_RCV_EOIB_RUNTS_ERR,
	TSU_RCV_EOIB_OUTER_VLAN_ERR,
	TSU_RCV_EOIB_VLAN_TAG_ERR,
	TSU_RCV_EOIB_VID_ERR,
	TSU_RCV_IPOIB_TCP_PORT_VIOLATION_ERR,
	TSU_RCV_MCAST_DUP_ERR,
	TSU_RCV_ECC_ERR,
	TSU_DSCR_RESPONDER_RC_PSN_ERR,
	TSU_DSCR_RESPONDER_RC_DUPLICATE,
	TSU_DSCR_RESPONDER_RC_OPCODE_SEQ_ERR,
	TSU_DSCR_RESPONDER_RC_OPCODE_VAL_ERR,
	TSU_DSCR_RESPONDER_RC_OPCODE_LEN_ERR,
	TSU_DSCR_RESPONDER_RC_DMALEN_ERR,
	TSU_DSCR_RESPONDER_XRC_PSN_ERR,
	TSU_DSCR_RESPONDER_XRC_DUPLICATE,
	TSU_DSCR_RESPONDER_XRC_OPCODE_SEQ_ERR,
	TSU_DSCR_RESPONDER_XRC_OPCODE_VAL_ERR,
	TSU_DSCR_RESPONDER_XRC_OPCODE_LEN_ERR,
	TSU_DSCR_RESPONDER_XRC_DMALEN_ERR,
	TSU_DSCR_RESPONDER_UC_PSN_ERR,
	TSU_DSCR_RESPONDER_UC_OPCODE_SEQ_ERR,
	TSU_DSCR_RESPONDER_UC_OPCODE_VAL_ERR,
	TSU_DSCR_RESPONDER_UC_OPCODE_LEN_ERR,
	TSU_DSCR_RESPONDER_UC_DMALEN_ERR,
	TSU_DSCR_RESPONDER_UD_OPCODE_LEN_ERR,
	TSU_DSCR_RESPONDER_DUPLICATE_WITH_ERR,
	TSU_DSCR_QP_CAP_MASKED_ATOMIC_ENABLE_ERR,
	TSU_DSCR_QP_CAP_RDMA_RD_ENABLE_ERR,
	TSU_DSCR_QP_CAP_RDMA_WR_ENABLE_ERR,
	TSU_DSCR_QP_CAP_ATOMIC_ENABLE_ERR,
	TSU_DSCR_XRC_DOMAIN_VIOLATION_ERR,
	TSU_DSCR_XRCETH_ERR,
	TSU_DSCR_RQ_INVALID_ERR,
	TSU_DSCR_RQ_PD_CHECK_ERR,
	TSU_DSCR_RQ_EMPTY_ERR,
	TSU_DSCR_RQ_IN_ERROR_ERR,
	TSU_DSCR_TRANSLATION_TYPE_ERR,
	TSU_DSCR_RQ_DESCRIPTOR_INCONSISTENT_ERR,
	TSU_DSCR_MISALIGNED_ATOMIC_ERR,
	TSU_DSCR_PCIE_ERR,
	TSU_DSCR_ECC_ERR,
	TSU_RQH_PCIE_ERR,
	TSU_RQH_SGL_LKEY_ERR,
	TSU_RQH_NOT_ENOUGH_RQ_SPACE_ERR,
	TSU_RQH_ECC_ERR,
	TSU_VAL_DUPLICATE_WITH_ERR,
	TSU_VAL_RKEY_VLD_ERR,
	TSU_VAL_RKEY_ADDR_RANGE_ERR,
	TSU_VAL_RKEY_ACCESS_ERR,
	TSU_VAL_RKEY_PD_ERR,
	TSU_VAL_RKEY_RANGE_ERR,
	TSU_VAL_LKEY_VLD_ERR,
	TSU_VAL_LKEY_ADDR_RANGE_ERR,
	TSU_VAL_LKEY_ACCESS_ERR,
	TSU_VAL_LKEY_PD_ERR,
	TSU_VAL_LKEY_RANGE_ERR,
	TSU_VAL_TRANSLATION_TYPE_ERR,
	TSU_VAL_PCIE_ERR,
	TSU_VAL_ECC_ERR,
	TSU_MMU_DUPLICATE_WITH_ERR,
	TSU_MMU_PTW_ERR,
	TSU_MMU_UF_ERR,
	TSU_MMU_AC_ERR,
	TSU_MMU_ECC_ERR,
	TSU_CBLD_CQ_INVALID_ERR,
	TSU_CBLD_CQ_FULL_ERR,
	TSU_CBLD_CQ_ALREADY_IN_ERR,
	TSU_CBLD_CQ_IS_PROXY_ERR,
	TSU_CBLD_TRANSLATION_TYPE_ERR,
	TSU_CBLD_CQ_DESCRIPTOR_INCONSISTENT_ERR,
	TSU_CBLD_ECC_ERR,
	TSU_CBLD_PCIE_ERR,
	TSU_CBLD_QP_ERR,
	TSU_RQS_CHECKSUM_ERR,
	TSU_RQS_SEQNUM_ERR,
	TSU_RQS_INVALID_REQUEST_ERR,
	TSU_RQS_QP_IN_WRONG_STATE_ERR,
	TSU_RQS_STOP_TIMER_ERR,
	TSU_RQS_CMD_FROM_EPS_ERR,
	TSU_RQS_SQ_FLUSH_ERR,
	TSU_RQS_SMP_NOT_AUTH_ERR,
	TSU_RQS_REQUEST_FENCED_ERR,
	TSU_RQS_MAX_OUTSTANDING_REACHED_ERR,
	TSU_RQS_ECC_ERR,
	TSU_RQS_EOIB_QKEY_VIOLATION,
	TSU_RQS_IPOIB_QKEY_VIOLATION,
	TSU_RQS_EOIB_MODE_VIOLATION,
	TSU_RQS_MISCONFIGURED_QP,
	TSU_RQS_PORT_AUTH_VIOLATION,
	TSU_DMA_SGL_RD_ERR,
	TSU_DMA_REQ_PYLD_RD_ERR,
	TSU_DMA_RESP_PYLD_RD_ERR,
	TSU_DMA_SGL_LENGTH_ERR,
	TSU_DMA_LKEY_ERR,
	TSU_DMA_RKEY_ERR,
	TSU_DMA_LSO_PKTLEN_ERR,
	TSU_DMA_LSO_ILLEGAL_CLASSIFICATION_ERR,
	TSU_DMA_PCIE_ERR,
	TSU_DMA_ECC_ERR,
	TSU_CMPL_PCIE_ERR,
	TSU_CMPL_ECC_ERR,
	TSU_CMPL_REQUESTER_PSN_ERR,
	TSU_CMPL_REQUESTER_SYNDROME_ERR,
	TSU_CMPL_REQUESTER_OUTSTANDING_MATCH_ERR,
	TSU_CMPL_REQUESTER_LEN_ERR,
	TSU_CMPL_REQUESTER_UNEXP_OPCODE_ERR,
	TSU_CMPL_REQUESTER_DUPLICATE,
	TSU_CMPL_RC_IN_ERROR_ERR,
	TSU_CMPL_NAK_RNR_ERR,
	TSU_CMPL_NAK_SEQUENCE_ERR,
	TSU_CMPL_NAK_INVALID_REQUEST_ERR,
	TSU_CMPL_NAK_REMOTE_ACCESS_ERR,
	TSU_CMPL_NAK_REMOTE_OPS_ERR,
	TSU_CMPL_NAK_INVALID_RD_REQUEST_ERR,
	TSU_CMPL_TIMEOUT_ERR,
	TSU_CMPL_IMPLIED_NAK,
	TSU_CMPL_GHOST_RESP_ERR
}; /* enum psif_tsu_error_types [ 8 bits] */

/*
 * Here are the different EPS core IDs: PSIF_EVENT_EPS_A_1 PSIF_EVENT_EPS_A_2
 * PSIF_EVENT_EPS_A_3 PSIF_EVENT_EPS_A_4 PSIF_EVENT_EPS_C
 */
enum psif_eps_core_id {
	PSIF_EVENT_CORE_EPS_A_1,
	PSIF_EVENT_CORE_EPS_A_2,
	PSIF_EVENT_CORE_EPS_A_3,
	PSIF_EVENT_CORE_EPS_A_4,
	PSIF_EVENT_CORE_EPS_C,
	/* Padding out to required bits allocated */
	PSIF_EPS_CORE_ID_FIELD_MAX	 = 0xf
}; /* enum psif_eps_core_id [ 4 bits] */


enum psif_epsc_log_mode {
/* Logging completely disabled */

	EPSC_LOG_MODE_OFF	 = 0,
/* See epsfw/src/include/logging.h */

	EPSC_LOG_MODE_SCAT	 = 0x1,
	EPSC_LOG_MODE_MALLOC	 = 0x2,
	EPSC_LOG_MODE_LOCAL	 = 0x3,
/* Redirect logging to host (dma) */

	EPSC_LOG_MODE_HOST	 = 0x4,
/* Save the set log mode in the flash */

	EPSC_LOG_MODE_SAVE	 = 0x10,
	/* Padding out to required bits allocated */
	PSIF_EPSC_LOG_MODE_FIELD_MAX	 = 0x7fffffff
}; /* enum psif_epsc_log_mode [32 bits] */

/**
 * EPSC_LOG_CTRL
 */
enum psif_epsc_log_level {
	EPS_LOG_OFF	 = 0,
	EPS_LOG_FATAL	 = 0x1,
	EPS_LOG_ERROR	 = 0x2,
	EPS_LOG_WARN	 = 0x3,
	EPS_LOG_INFO	 = 0x4,
	EPS_LOG_DEBUG	 = 0x5,
	EPS_LOG_TRACE	 = 0x6,
	EPS_LOG_ALL	 = 0x7,
	/* Padding out to required bits allocated */
	PSIF_EPSC_LOG_LEVEL_FIELD_MAX	 = 0x7fffffff
}; /* enum psif_epsc_log_level [32 bits] */

/**
 * \brief Port state
 * \details
 * This enum specifies the state of a UF port's port state machine. It
 * is used to either force a new state or to report the current state
 * (via \ref EPSC_QUERY_PORT_1 and \ref EPSC_QUERY_PORT_2).
 *
 * \par Width
 *      32 bit
 * \par Used in
 *      psif_epsc_port_attr_t
 * \par Classification
 *      driver, internal
 *
 * \todo
 * The externally provided version of the documentation should probably
 * not contain the information about forcing the state as this is only
 * for FW.
 */
enum psif_epsc_port_state {
	/** No change */
	EPSC_PORT_NOP	 = 0,
	/** The port is down. */
	EPSC_PORT_DOWN	 = 0x1,
	/** The port is in init state. */
	EPSC_PORT_INIT	 = 0x2,
	/** The port state is armed. */
	EPSC_PORT_ARMED	 = 0x3,
	/** The port is active. */
	EPSC_PORT_ACTIVE	 = 0x4,
	/** The port is in deferred active state. */
	EPSC_PORT_ACTIVE_DEFER	 = 0x5,
	/* Padding out to required bits allocated */
	PSIF_EPSC_PORT_STATE_FIELD_MAX	 = 0x7fffffff
}; /* enum psif_epsc_port_state [32 bits] */

/**
 * \brief Version fixed copy of psif_path_mtu
 * \details
 * This enum specifies the path MTU values and is the same as `psif_path_mtu`
 * found in `psif_verbs.h`. The difference is the data type. The version in
 * `psif_verbs.h` is smaller!
 *
 * \todo
 * Change version in `psif_verbs.h` to 32b and then drop this one here?
 *
 * \par Width
 *      32 bit
 * \par Used in
 *      psif_epsc_port_attr_t
 * \par Classification
 *      driver
 */
enum psif_epsc_path_mtu {
	/** Not a valid MTU. */
	EPSC_MTU_INVALID	 = 0,
	/** The MTU is 256 bytes. */
	EPSC_MTU_256B	 = 0x1,
	/** The MTU is 512 bytes. */
	EPSC_MTU_512B	 = 0x2,
	/** The MTU is 1024 bytes. */
	EPSC_MTU_1024B	 = 0x3,
	/** The MTU is 2048 bytes. */
	EPSC_MTU_2048B	 = 0x4,
	/** The MTU is 4069 bytes. */
	EPSC_MTU_4096B	 = 0x5,
	/** The MTU is 10240 bytes. */
	EPSC_MTU_10240B	 = 0x6,
	/** Not a specific MTU. */
	EPSC_MTU_XXX	 = 0x7,
	/* Padding out to required bits allocated */
	PSIF_EPSC_PATH_MTU_FIELD_MAX	 = 0x7fffffff
}; /* enum psif_epsc_path_mtu [32 bits] */

/**
 * \brief Monitors handling asynchronous event
 * \details
 * This is only found in a structure definition in EPS-A but not used there.
 *
 * \todo
 * Remove this?
 *
 * \par Width
 *      4 bit
 * \par Used in
 *      N/A
 * \par Classification
 *      unused
 */
enum psif_epsc_monitor {
	PSIF_MONITOR_ARM,
	PSIF_MONITOR_TRIG,
	PSIF_MONITOR_REARM,
	PSIF_MONITOR_INACTIVE,
	PSIF_MONITOR_ERROR,
	/* Padding out to required bits allocated */
	PSIF_EPSC_MONITOR_FIELD_MAX	 = 0xf
}; /* enum psif_epsc_monitor [ 4 bits] */

/**
 * \brief Interrupt sources definitions as bit indexes.
 * \details
 * In a mask the active interrupt sources are represented by set bits
 * `bits[x]=(1 << EPSC_INTR_x)`. These values are defined by hardware.
 *
 * \par Width
 *      5 bit
 * \par Used in
 *      N/A
 * \par Classification
 *      internal, development
 */
enum psif_epsc_interrupt_source {
	/** Interrupt source is LCSR OR_LOW only with own (HI-)pin. */
	EPSC_INTR_LCSR,
	/** Interrupt source is message box OR_LOW only with own (HI-)pin. */
	EPSC_INTR_MBOX,
	/** Interrupt source is XIU OR_LOW only with own (HI-)pin. */
	EPSC_INTR_XIU,
	/** Interrupt source is IBU-0 OR_LOW only with own (HI-)pin. */
	EPSC_INTR_IBU0,
	/** Interrupt source is IBU-1 OR_LOW only with own (HI-)pin. */
	EPSC_INTR_IBU1,
	/** Interrupt source is NCSI. */
	EPSC_INTR_TSU_NCSI,
	/** Interrupt source is IBPB. */
	EPSC_INTR_TSU_IBPB,
	/** Interrupt source is DMA. */
	EPSC_INTR_TSU_DMA,
	/** Interrupt source is RQS. */
	EPSC_INTR_TSU_RQS,
	/** Interrupt source is QPS. */
	EPSC_INTR_TSU_QPS,
	/** Interrupt source is SQS. */
	EPSC_INTR_TSU_SQS,
	/** Interrupt source is ERR. */
	EPSC_INTR_TSU_ERR,
	/** Interrupt source is CMPL. */
	EPSC_INTR_TSU_CMPL,
	/** Interrupt source is VAL. */
	EPSC_INTR_TSU_VAL,
	/** Interrupt source is RQH. */
	EPSC_INTR_TSU_RQH,
	/** Interrupt source is DSCR. */
	EPSC_INTR_TSU_DSCR,
	/** Interrupt source is RCV. */
	EPSC_INTR_TSU_RCV,
	/** Interrupt source is IBPR. */
	EPSC_INTR_TSU_IBPR,
	/** Interrupt source is CBU. */
	EPSC_INTR_TSU_CBU,
	/** Interrupt source is HOST. */
	EPSC_INTR_TSU_HOST,
	/** Interrupt source is MMU. */
	EPSC_INTR_TSU_MMU
}; /* enum psif_epsc_interrupt_source [ 5 bits] */

/**
 * \brief Interrupt severity levels
 * \details
 * This lists the interrupt levels as used by the simulators PRM responder
 * (psifsim) and cosim. They are not in sync with the values used by EPS
 * firmware.
 *
 * \par Width
 *      2 bit
 * \par Used in
 *      N/A
 * \par Classification
 *      development
 */
enum psif_epsc_interrupt_pri {
	/** unknown/invalid interrupt priority */
	EPSC_INTR_RESERVED,
	/** low interrupt priority */
	EPSC_INTR_LOW,
	/** high interrupt priority */
	EPSC_INTR_HIGH,
	/** nonmaskable/fatal interrupt */
	EPSC_INTR_FATAL
}; /* enum psif_epsc_interrupt_pri [ 2 bits] */

/**
 * \brief Query HCA verb response member `atomicity guarantee` values
 * \details
 * This enum specifies values possible for the (masked) atomicity guarantee
 * capability reported in the Query HCA verb (via \ref EPSC_QUERY_DEVICE).
 *
 * \par Width
 *      32 bit
 * \par Used in
 *      psif_epsc_device_attr_t
 * \par Classification
 *      driver
 */
enum psif_epsc_atomic_cap {
	/** no atomicity guarantee */
	EPSC_ATOMIC_NONE,
	/** HCA atomicity guarantee */
	EPSC_ATOMIC_HCA,
	/** global atomicity guarantee */
	EPSC_ATOMIC_GLOB,
	/* Padding out to required bits allocated */
	PSIF_EPSC_ATOMIC_CAP_FIELD_MAX	 = 0x7fffffff
}; /* enum psif_epsc_atomic_cap [32 bits] */

/**
 * \brief The EPS-C FW status return codes
 * \details These error codes are retured from the EPS-C.
 * \par Width
 *      8 bit
 * \par Used in
 *      psif_epsc_csr_rsp member `status`
 * \par Classification
 *      external, driver
 */
enum psif_epsc_csr_status {
	/** Successful exit status. */
	EPSC_SUCCESS	 = 0,
	/** Key was rejected by service. */
	EPSC_EKEYREJECTED	 = 0x1,
	/** Cannot assign requested address. */
	EPSC_EADDRNOTAVAIL	 = 0x2,
	/** Operation not supported on transport endpoint. */
	EPSC_EOPNOTSUPP	 = 0x3,
	/** Out of memory. */
	EPSC_ENOMEM	 = 0x4,
	/** No data available. */
	EPSC_ENODATA	 = 0x5,
	/** Try again. */
	EPSC_EAGAIN	 = 0x6,
	/** Operation canceled. */
	EPSC_ECANCELED	 = 0x7,
	/** Connection reset by peer. */
	EPSC_ECONNRESET	 = 0x8,
	/** CSR operation failed. */
	EPSC_ECSR	 = 0x9,
	/** Modify queue pair error: QP index out of range. */
	EPSC_MODIFY_QP_OUT_OF_RANGE	 = 0xa,
	/** Modify queue pair error: QP is invalid. */
	EPSC_MODIFY_QP_INVALID	 = 0xb,
	/** Modify queue pair error: failed to change QP attribute. */
	EPSC_MODIFY_CANNOT_CHANGE_QP_ATTR	 = 0xc,
	/** Modify queue pair error: failed to change QP due to invalid or not matching state. */
	EPSC_MODIFY_INVALID_QP_STATE	 = 0xd,
	/** Modify queue pair error: failed to change QP due to invalid or not matching migration state. */
	EPSC_MODIFY_INVALID_MIG_STATE	 = 0xe,
	/** Modify queue pair error: the operation timed out. */
	EPSC_MODIFY_TIMEOUT	 = 0xf,
	/** DMA test failure in HEAD. */
	EPSC_ETEST_HEAD	 = 0x10,
	/** DMA test failure in TAIL. */
	EPSC_ETEST_TAIL	 = 0x11,
	/** DMA test failure in PATTERN. */
	EPSC_ETEST_PATTERN	 = 0x12,
	/** Multicast address already exist. */
	EPSC_EADDRINUSE	 = 0x13,
	/** vHCA out of range */
	EPSC_EINVALID_VHCA	 = 0x14,
	/** Port out of range */
	EPSC_EINVALID_PORT	 = 0x15,
	/** Address out of range */
	EPSC_EINVALID_ADDRESS	 = 0x16,
	/** Parameter out of range */
	EPSC_EINVALID_PARAMETER	 = 0x17,
	/** General failure. */
	EPSC_FAIL	 = 0xff
}; /* enum psif_epsc_csr_status [ 8 bits] */

/**
 * \brief Host to EPS operation codes
 * \details
 * These operation codes are sent in the \ref psif_epsc_csr_req::opcode member
 * from the host or a particular core (EPS-Ax/EPS-C) to the mailbox thread in
 * EPS-C or EPS-Ax in order to specify the request. In addition the operation
 * codes are used as a selector for the \ref psif_epsc_csr_req::u member of
 * type \ref psif_epsc_csr_details_t in order to specify the particular
 * structure if the request requires specific arguments. In some cases the
 * selected structure defines an own set of sub-operation codes like for
 * \ref EPSC_QUERY with \ref psif_epsc_query_req_t::op of type
 * \ref psif_epsc_query_op_t.
 * \par
 * Responses are always of type \ref psif_epsc_csr_rsp_t but the meaning of the
 * members of that structure depend on the operation code. The response state
 * is \ref EPSC_EADDRNOTAVAIL for all not supported operation codes.
 *
 * \par Width
 *      8 bit
 * \par Used in
 *      psif_epsc_csr_req_t
 * \par Classification
 *      see each of the operation codes
 *
 * \note
 * - All codes must be unique and fit into a 8 bit number.
 * - In order to provide backward compatibility new codes must start from the
 *   current value of \ref EPSC_LAST_OP and the value of \ref EPSC_LAST_OP
 *   must be incremented by the number of newly inserted codes.
 */
enum psif_epsc_csr_opcode {
	/** Not a valid operation code. */
	EPSC_NOOP	 = 0,
	/** EPS-C ping over mailbox. */
	EPSC_MAILBOX_PING	 = 0x4c,
	/** Host patting of EPS-C SW watch-dog. */
	EPSC_KEEP_ALIVE	 = 0x4d,
	/** Initial configuration request per UF.
	 * This request is transferred from the host to the epsc at driver
	 * attach using an encoding of the physical mailbox register. It
	 * is not a legal request on an operational mailbox communication
	 *
	 * \par Request
	 *      Structure details:
	 *      Member | Content
	 *      -------|-------------------
	 *      u      | \ref psif_epsc_csr_config_t
	 * \par Response
	 *      Structure contents:
	 *      Member | Content
	 *      -------|-------------------
	 *      addr   | number of event queues (EQ) per UF
	 *      data   | PSIF/EPS-C version
	 * \par
	 *      The version is encoded this way:
	 *      Bits  | Version Specifier
	 *      ------|---------
	 *      63-48 | PSIF_MAJOR_VERSION
	 *      47-32 | PSIF_MINOR_VERSION
	 *      31-16 | EPSC_MAJOR_VERSION
	 *      15-0  | EPSC_MINOR_VERSION
	 *
	 * \par Return Codes
	 *      \ref EPSC_SUCCESS
	 * \par Restrictions
	 *      none (all UF)
	 * \par Classification
	 *      driver
	 */
	EPSC_SETUP	 = 0x1,
	/** Final de-configuration request.
	 * This request is sent from the host driver to indicate that it has
	 * cleaned up all queues and flushed caches associated with the current
	 * UF. It is the last command for that UF and the firmware will take down
	 * the associated virtual links and mailbox settings. For further
	 * communication with that UF the mailbox needs to be set up again via
	 * \ref EPSC_SETUP .
	 *
	 * \par Request
	 *      N/A
	 * \par Return Codes
	 *      \ref EPSC_SUCCESS
	 * \par Restrictions
	 *      none (all UF)
	 * \par Classification
	 *      driver
	 */
	EPSC_TEARDOWN	 = 0x36,
	/** Operation code for a general set request.
	 * The request usees the same parameter structure as the \ref EPSC_QUERY
	 * request. Upon recieve the mailbox thread first processes the set request
	 * in \ref psif_epsc_csr_query_t::info and then the request in
	 * \ref psif_epsc_csr_query_t::data. Both members are of type
	 * \ref psif_epsc_query_req_t and have their own sub-operation codes in
	 * \ref psif_epsc_query_req_t::op (of type \ref psif_epsc_query_op_t).
	 * Therefore requests instantiating only one set attribute
	 * (i.e. \ref psif_epsc_csr_query_t::info or \ref psif_epsc_csr_query_t::data)
	 * have to set the sub-operation code of the other member to
	 * \ref EPSC_QUERY_BLANK.
	 *
	 * \par Request
	 *      Structure details:
	 *      Member | Content
	 *      -------|-------------------
	 *      u      | \ref psif_epsc_csr_query_t
	 * \par Return Codes
	 *      \ref EPSC_SUCCESS, \ref EPSC_EOPNOTSUPP, \ref EPSC_FAIL
	 * \par Restrictions
	 *      none (all UF)
	 * \par Classification
	 *      external
	 */
	EPSC_SET	 = 0x46,
	/** Operation code for a single CSR write request.
	 * \note
	 * The request is deprecated and will be removed as soon as all
	 * references to this opcode have been cleaned up.
	 * \par Return Codes
	 *      \ref EPSC_EADDRNOTAVAIL
	 */
	EPSC_SET_SINGLE	 = 0x2,
	/** Operation code for setting an arbitrary CSR.
	 * \note
	 * The request is used mainly for debugging tools and will be either removed
	 * completely or limited to certain register addresses.
	 *
	 * \par Request
	 *      Structure details:
	 *      Member | Content
	 *      -------|-------------------
	 *      addr   | CSR address
	 *      u      | `data[0]` value to write to CSR
	 * \par Response
	 *      Structure contents:
	 *      Member | Content
	 *      -------|----------------------------------------
	 *      addr   | the value `addr` from the request
	 *      data   | the value `data[0]` from the request
	 *
	 * \par Return Codes
	 *      \ref EPSC_SUCCESS, \ref EPSC_FAIL
	 * \par Restrictions
	 *      valid register addresses depend on UF
	 * \par Classification
	 *      driver, development
	 */
	EPSC_SET_ONE_CSR	 = 0x3,
	/** Old operation code to set up a descriptor base address.
	 * \note
	 * The request is deprecated and will be removed as soon as all
	 * references to this opcode have been cleaned up.
	 *
	 * \par Return Codes
	 *      \ref EPSC_EADDRNOTAVAIL
	 * \par Classification
	 *      driver
	 */
	EPSC_SETUP_BASEADDR	 = 0x4,
	/** Operation code to set up a descriptor base address.
	 * With this request the driver configures the descriptor base addresses
	 * of queues, queue pairs and address handles.
	 *
	 * \par Request
	 *      Structure details:
	 *      Member | Content
	 *      -------|-------------------------------------------
	 *      addr   | Descriptor base address setup CSR address
	 *      u      | \ref psif_epsc_csr_base_addr_t
	 *
	 * \par Return Codes
	 *      \ref EPSC_SUCCESS, \ref EPSC_FAIL
	 * \par Restrictions
	 *      none (all UF)
	 * \par Classification
	 *      driver, development
	 */
	EPSC_SET_BASEADDR	 = 0x5,
	/** Operation code to set up an event queue (EQ).
	 * With this request the driver configures an EQ descriptor base address
	 * as well as the associated interrupt.
	 *
	 * \par Request
	 *      Structure details:
	 *      Member | Content
	 *      -------|-------------------------------------------
	 *      addr   | event queue number
	 *      u      | \ref psif_epsc_csr_base_addr_t
	 *
	 * \par Return Codes
	 *      \ref EPSC_SUCCESS, \ref EPSC_FAIL
	 * \par Restrictions
	 *      none (all UF)
	 * \par Classification
	 *      driver
	 */
	EPSC_SET_BASEADDR_EQ	 = 0x6,
	/* Set Local ID for UF (backdoor) */
	EPSC_SET_LID	 = 0x7,
	OBSOLETE_1	 = 0x8,
	OBSOLETE_2	 = 0x9,
	/* Set Global ID for UF (backdoor) */
	EPSC_SET_GID	 = 0xa,
	/* Set EoIB MAC address (backdoor) */
	EPSC_SET_EOIB_MAC	 = 0x40,
	/* Set Vlink state */
	EPSC_SET_VLINK_STATE	 = 0xb,
	/* Get Vlink state */
	EPSC_QUERY_VLINK_STATE	 = 0xc,
	/* Reset UF at startup */
	EPSC_UF_RESET	 = 0xd,
	/* Modify QP complete w/kick */
	EPSC_MODIFY_QP	 = 0xe,
	/* Get single 64bit register - depricated */
	EPSC_GET_SINGLE	 = 0xf,
	/* Get one 64bit register using CSR addr */
	EPSC_GET_ONE_CSR	 = 0x10,
	/* Query QP sub-entry */
	EPSC_QUERY_QP	 = 0x11,
	/** Query HW receive queue. */
	EPSC_QUERY_HW_RQ	 = 0x42,
	/** Query HW SQ. */
	EPSC_QUERY_HW_SQ	 = 0x43,
	/* Non-MAD query device */
	EPSC_QUERY_DEVICE	 = 0x12,
	/* Non-MAD query port */
	EPSC_QUERY_PORT_1	 = 0x13,
	EPSC_QUERY_PORT_2	 = 0x14,
	/* Non-MAD SMA attribute query */
	EPSC_QUERY_PKEY	 = 0x15,
	EPSC_QUERY_GID	 = 0x16,
	/* Non-MAD SMA attribute setting */
	EPSC_MODIFY_DEVICE	 = 0x17,
	EPSC_MODIFY_PORT_1	 = 0x18,
	EPSC_MODIFY_PORT_2	 = 0x19,
	/* Local MC subscription handling */
	EPSC_MC_ATTACH	 = 0x1a,
	EPSC_MC_DETACH	 = 0x1b,
	EPSC_MC_QUERY	 = 0x1c,
	/* Handle asynchronous events */
	EPSC_EVENT_ACK	 = 0x1d,
	EPSC_EVENT_INDEX	 = 0x1e,
	/* Program flash content */
	EPSC_FLASH_START	 = 0x1f,
	EPSC_FLASH_INFO	 = 0x20,
	EPSC_FLASH_ERASE_SECTOR	 = 0x21,
	EPSC_FLASH_RD	 = 0x22,
	EPSC_FLASH_WR	 = 0x23,
	EPSC_FLASH_CHECK	 = 0x24,
	EPSC_FLASH_SCAN	 = 0x25,
	EPSC_FLASH_STOP	 = 0x26,
	/* new update handling */
	EPSC_UPDATE	 = 0x47,
	/* IB packet tracer */
	EPSC_TRACE_STATUS	 = 0x27,
	EPSC_TRACE_SETUP	 = 0x28,
	EPSC_TRACE_START	 = 0x29,
	EPSC_TRACE_STOP	 = 0x2a,
	EPSC_TRACE_ACQUIRE	 = 0x2b,
	/* Test operations */
	EPSC_TEST_HOST_RD	 = 0x2c,
	EPSC_TEST_HOST_WR	 = 0x2d,
	/* Get EPS-C version details */
	EPSC_FW_VERSION	 = 0x2e,
	/* Redirection/configuration of EPSC's internal log subsystem */
	EPSC_LOG_CTRL	 = 0x2f,
	EPSC_LOG_REQ_NOTIFY	 = 0x30,
	/* Force & read back link speed */
	EPSC_LINK_CNTRL	 = 0x31,
	/* EPS-A control & communication (to EPS-C) */
	EPSC_A_CONTROL	 = 0x33,
	/* EPS-A targeted commands (to EPS-A) */
	EPSC_A_COMMAND	 = 0x35,
	/* Exercise mmu with access from epsc */
	EPSC_EXERCISE_MMU	 = 0x34,
	/* Access to EPS-C CLI */
	EPSC_CLI_ACCESS	 = 0x37,
	/* IB packet proxy to/from host */
	EPSC_MAD_PROCESS	 = 0x38,
	EPSC_MAD_SEND_WR	 = 0x39,
	/** Generic query epsc interface. */
	EPSC_QUERY	 = 0x41,
	/* Setup interrupt coalescing etc. */
	EPSC_HOST_INT_COMMON_CTRL	 = 0x44,
	EPSC_HOST_INT_CHANNEL_CTRL	 = 0x45,
	/** UF control depends on \ref psif_epsc_csr_uf_ctrl_t::opcode. */
	EPSC_UF_CTRL	 = 0x48,
	/* Flush MMU and-or PTW Caches */
	EPSC_FLUSH_CACHES	 = 0x49,
	/* Query PMA counters - alternative path to sending MAD's */
	EPSC_PMA_COUNTERS	 = 0x4a,
	/** VIMMA operations depends on \ref psif_epsc_csr_vimma_ctrl_t::opcode. */
	EPSC_VIMMA_CTRL	 = 0x4b,
	/** EOF marker - must be last and highest in this enum type. */
	EPSC_LAST_OP	 = 0x4e,
	/* Padding out to required bits allocated */
	PSIF_EPSC_CSR_OPCODE_FIELD_MAX	 = 0xff
}; /* enum psif_epsc_csr_opcode [ 8 bits] */

/**
 * The eps-c fw csr flags
 */
enum psif_epsc_csr_flags {
	EPSC_FL_NONE	 = 0,
	/* Request notification (interrupt) when completion is ready */
	EPSC_FL_NOTIFY	 = 0x1,
	/* Privileged QP indicator only valid for query and modify QP */
	EPSC_FL_PQP	 = 0x2,
	/* Allways report opertion success */
	EPSC_FL_IGNORE_ERROR	 = 0x4,
	/* Padding out to required bits allocated */
	PSIF_EPSC_CSR_FLAGS_FIELD_MAX	 = 0xff
}; /* enum psif_epsc_csr_flags [ 8 bits] */

/*
 * Link states for the virtual HCA and switch. The following onehot encoded
 * states exist: PSIF_LINK_DISABLED = 1 PSIF_LINK_DOWN = 2 PSIF_LINK_INIT = 4
 * PSIF_LINK_ARM = 8 PSIF_LINK_ACTIVE = 16
 */
enum psif_vlink_state {
	PSIF_LINK_DISABLED	 = 0x1,
	PSIF_LINK_DOWN	 = 0x2,
	PSIF_LINK_INIT	 = 0x4,
	PSIF_LINK_ARM	 = 0x8,
	PSIF_LINK_ACTIVE	 = 0x10
}; /* enum psif_vlink_state [ 5 bits] */

/**
 * EPSC_MODIFY_DEVICE operations
 */
enum psif_epsc_csr_modify_device_flags {
	PSIF_DEVICE_MODIFY_SYS_IMAGE_GUID	 = 0x1,
	PSIF_DEVICE_MODIFY_NODE_DESC	 = 0x2,
	/* Padding out to required bits allocated */
	PSIF_EPSC_CSR_MODIFY_DEVICE_FLAGS_FIELD_MAX	 = 0xffff
}; /* enum psif_epsc_csr_modify_device_flags [16 bits] */

/**
 * EPSC_MODIFY_PORT_{1,2} operations
 */
enum psif_epsc_csr_modify_port_flags {
	PSIF_PORT_SHUTDOWN	 = 0x1,
	PSIF_PORT_INIT_TYPE	 = 0x4,
	PSIF_PORT_RESET_QKEY_CNTR	 = 0x8,
	PSIF_PORT_RESET_PKEY_CNTR	 = 0x10,
	/* Padding out to required bits allocated */
	PSIF_EPSC_CSR_MODIFY_PORT_FLAGS_FIELD_MAX	 = 0xffff
}; /* enum psif_epsc_csr_modify_port_flags [16 bits] */


enum psif_epsc_csr_epsa_command {
	EPSC_A_LOAD,
	EPSC_A_START,
	EPSC_A_STOP,
	EPSC_A_STATUS,
	/* Padding out to required bits allocated */
	PSIF_EPSC_CSR_EPSA_COMMAND_FIELD_MAX	 = 0x7fffffff
}; /* enum psif_epsc_csr_epsa_command [32 bits] */

/*
 */
enum psif_epsa_command {
	EPSA_DYNAMIC_LOAD,
	EPSA_TEST_FABOUT,
	EPSA_TEST_FABIN,
	EPSA_TEST_FABIN_FABOUT,
	EPSA_TEST_SKJM_MEMREAD,
	EPSA_TEST_SKJM_MEMWRITE,
	EPSA_TEST_SKJM_MEMLOCK,
	EPSA_SKJM_LOAD,
	EPSA_SKJM_ACC,
	EPSA_SKJM_MEMACC,
	EPSA_GET_PROXY_QP_SQ_KEY,
	/* Padding out to required bits allocated */
	PSIF_EPSA_COMMAND_FIELD_MAX	 = 0x7fffffff
}; /* enum psif_epsa_command [32 bits] */

/**
 * \brief Sub-operation codes as used by EPSC_QUERY and EPSC_SET requests.
 * \details
 * \par Width
 *      32 bit
 * \par Used in
 *      psif_epsc_query_req member `op`
 * \par Classification
 *      internal, development
 */
enum psif_epsc_query_op {
	/** If initiated from a EPSC_QUERY this operation code will always return zero and report success.
	 *  In case of a intended set request (EPSC_SET) this operation code ignore the request and return success.
	 */
	EPSC_QUERY_BLANK	 = 0,
	/* Obsolete - use EPSC_QUERY_CAP_VCB_{LO HI} */
	EPSC_QUERY_CAP_VCB	 = 0x1,
	/* Obsolete - use EPSC_QUERY_CAP_PCB_{LO HI} */
	EPSC_QUERY_CAP_PCB	 = 0x2,
	EPSC_QUERY_NUM_UF	 = 0x3,
	EPSC_QUERY_GID_HI	 = 0x4,
	EPSC_QUERY_GID_LO	 = 0x5,
	EPSC_QUERY_P_KEY	 = 0x6,
	EPSC_QUERY_Q_KEY	 = 0x7,
	EPSC_QUERY_UF	 = 0x8,
	EPSC_QUERY_LINK_STATE	 = 0x9,
	EPSC_QUERY_VHCA_STATE	 = 0xa,
	/* Corresponds to register TSU_HOST_INT_CTRL_ADDR */
	EPSC_QUERY_INT_COMMON	 = 0xb,
	/* Corresponds to register TSU_HOST_INT_CHAN_CTRL_0 */
	EPSC_QUERY_INT_CHAN_RATE	 = 0xc,
	/* Corresponds to register TSU_HOST_INT_CHAN_CTRL_1 */
	EPSC_QUERY_INT_CHAN_AUSEC	 = 0xd,
	/* Corresponds to register TSU_HOST_INT_CHAN_CTRL_2 */
	EPSC_QUERY_INT_CHAN_PUSEC	 = 0xe,
	/* Number of VCBs in PCI lo BAR */
	EPSC_QUERY_CAP_VCB_LO	 = 0xf,
	/* Number of VCBs in PCI hi BAR */
	EPSC_QUERY_CAP_VCB_HI	 = 0x10,
	/* Number of PCBs mapped to lo BAR VCBs */
	EPSC_QUERY_CAP_PCB_LO	 = 0x11,
	/* Number of PCBs mapped to hi BAR VCBs */
	EPSC_QUERY_CAP_PCB_HI	 = 0x12,
	/* psif_epsc_query_req.index = IB port number [1 2] */
	EPSC_QUERY_PMA_REDIRECT_QP	 = 0x13,
	/* uptime in seconds */
	EPSC_QUERY_FW_UPTIME	 = 0x14,
	/* date the firmware was programmed in epoch time */
	EPSC_QUERY_FW_PROG_DATE	 = 0x15,
	/* date the firmware was built in epoch time */
	EPSC_QUERY_FW_BUILD_DATE	 = 0x16,
	/* current firmware image number (flash slot) */
	EPSC_QUERY_FW_CURR_IMG	 = 0x17,
	/* oneshot firmware image number (flash slot) */
	EPSC_QUERY_FW_ONESHOT_IMG	 = 0x18,
	/* autostart firmware image number (flash slot) */
	EPSC_QUERY_FW_AUTOSTART_IMG	 = 0x19,
	/* bit field encoding why the FW image was booted */
	EPSC_QUERY_FW_START_CAUSE	 = 0x1a,
	/* firmware version */
	EPSC_QUERY_FW_VERSION	 = 0x1b,
	/* Requester - number of bad response errors. */
	EPSC_QUERY_SQ_NUM_BRE	 = 0x1c,
	/* Requester - number of bad response errors. */
	EPSC_QUERY_NUM_CQOVF	 = 0x1d,
	/* Requester - number of CQEs with status flushed in error. */
	EPSC_QUERY_SQ_NUM_WRFE	 = 0x1e,
	/* Responder - number of CQEs with status flushed in error. */
	EPSC_QUERY_RQ_NUM_WRFE	 = 0x1f,
	/* Responder - number of local access errors. */
	EPSC_QUERY_RQ_NUM_LAE	 = 0x20,
	/* Responder - number of local protection errors. */
	EPSC_QUERY_RQ_NUM_LPE	 = 0x21,
	/* Requester - number of local length errors. */
	EPSC_QUERY_SQ_NUM_LLE	 = 0x22,
	/* Responder - number of local length errors. */
	EPSC_QUERY_RQ_NUM_LLE	 = 0x23,
	/* Requester - number local QP operation error. */
	EPSC_QUERY_SQ_NUM_LQPOE	 = 0x24,
	/* Responder - number local QP operation error. */
	EPSC_QUERY_RQ_NUM_LQPOE	 = 0x25,
	/* Requester - number of NAK-Sequence Error received. */
	EPSC_QUERY_SQ_NUM_OOS	 = 0x26,
	/* Responder - number of NAK-Sequence Error sent. */
	EPSC_QUERY_RQ_NUM_OOS	 = 0x27,
	/* Requester - number of RNR nak retries exceeded errors. */
	EPSC_QUERY_SQ_NUM_RREE	 = 0x28,
	/* Requester - number of transport retries exceeded errors. */
	EPSC_QUERY_SQ_NUM_TREE	 = 0x29,
	/* Requester - number of NAK-Remote Access Error received. */
	EPSC_QUERY_SQ_NUM_ROE	 = 0x2a,
	/*
	 * Responder - number of NAK-Remote Access Error sent. NAK-Remote Operation
	 * Error on: 1. Malformed WQE: Responder detected a malformed Receive Queue
	 * WQE while processing the packet. 2. Remote Operation Error: Responder
	 * encountered an error, (local to the responder), which prevented it from
	 * completing the request.
	 */
	EPSC_QUERY_RQ_NUM_ROE	 = 0x2b,
	/*
	 * Requester - number of NAK-Remote Access Error received. R_Key Violation:
	 * Responder detected an invalid R_Key while executing an RDMA Request.
	 */
	EPSC_QUERY_SQ_NUM_RAE	 = 0x2c,
	/*
	 * Responder - number of NAK-Remote Access Error sent. R_Key Violation
	 * Responder detected an R_Key violation while executing an RDMA request.
	 */
	EPSC_QUERY_RQ_NUM_RAE	 = 0x2d,
	/*
	 * The number of UD packets silently discarded on the receive queue due to
	 * lack of receive descriptor.
	 */
	EPSC_QUERY_RQ_NUM_UDSDPRD	 = 0x2e,
	/*
	 * The number of UC packets silently discarded on the receive queue due to
	 * lack of receive descriptor.
	 */
	EPSC_QUERY_RQ_NUM_UCSDPRD	 = 0x2f,
	/*
	 * Requester - number of remote invalid request errors NAK-Invalid Request
	 * on: 1. Unsupported OpCode: Responder detected an unsupported OpCode. 2.
	 * Unexpected OpCode: Responder detected an error in the sequence of OpCodes,
	 * such as a missing Last packet.
	 */
	EPSC_QUERY_SQ_NUM_RIRE	 = 0x30,
	/*
	 * Responder - number of remote invalid request errors. NAK may or may not be
	 * sent. 1. QP Async Affiliated Error: Unsupported or Reserved OpCode (RC,RD
	 * only): Inbound request OpCode was either reserved, or was for a function
	 * not supported by thisQP. (E.g. RDMA or ATOMIC on QP not set up for this).
	 * 2. Misaligned ATOMIC: VA does not point to an aligned address on an atomic
	 * operation. 3. Too many RDMA READ or ATOMIC Requests: There were more
	 * requests received and not ACKed than allowed for the connection. 4. Out of
	 * Sequence OpCode, current packet is First or Only: The Responder detected
	 * an error in the sequence of OpCodes; a missing Last packet. 5. Out of
	 * Sequence OpCode, current packet is not First or Only: The Responder
	 * detected an error in the sequence of OpCodes; a missing First packet. 6.
	 * Local Length Error: Inbound Send request message exceeded the responder's
	 * available buffer space. 7. Length error: RDMA WRITE request message
	 * contained too much or too little pay-load data compared to the DMA length
	 * advertised in the first or only packet. 8. Length error: Payload length
	 * was not consistent with the opcode: a: only is between 0 and PMTU bytes b:
	 * (first or middle) equals PMTU bytes c: last is between 1 byte and PMTU
	 * bytes 9. Length error: Inbound message exceeded the size supported by the
	 * CA port.
	 */
	EPSC_QUERY_RQ_NUM_RIRE	 = 0x31,
	/* Requester - the number of RNR Naks received. */
	EPSC_QUERY_SQ_NUM_RNR	 = 0x32,
	/* Responder - the number of RNR Naks sent. */
	EPSC_QUERY_RQ_NUM_RNR	 = 0x33,
	/* twoshot firmware image number (flash slot) */
	EPSC_QUERY_FW_TWOSHOT_IMG	 = 0x34,
	/* firmware type */
	EPSC_QUERY_FW_TYPE	 = 0x35,
	/* firmware size */
	EPSC_QUERY_FW_SIZE	 = 0x36,
	/* firmware slot size (available space for an image) */
	EPSC_QUERY_FW_SLOT_SIZE	 = 0x37,
	/* version of boot loader that has started the application */
	EPSC_QUERY_BL_VERSION	 = 0x38,
	/* boot loader build date in epoch time format */
	EPSC_QUERY_BL_BUILD_DATE	 = 0x39,
	/* only used by EPSC_SET mark a PQP CQ ID as clean (WA bug 3769) */
	EPSC_QUERY_CLEAN_CQ_ID	 = 0x3a,
	/* Number of TSL supported by FW */
	EPSC_QUERY_CAP_TSL_TX	 = 0x3b,
	EPSC_QUERY_CAP_TSL_RX	 = 0x3c,
	/* Reset CBLD Diag counters. Only used by EPSC_SET */
	EPSC_QUERY_RESET_CBLD_DIAG_COUNTERS	 = 0x3d,
	/* Max QP index used since power-on or host reset - to optimize WA for HW bug 3251 */
	EPSC_QUERY_MAX_QP_USED	 = 0x3e,
	/** the UF and QP where modify QP timed out ((uf << 32) | (qp)) */
	EPSC_QUERY_MODQP_TO_SOURCE	 = 0x3f,
	/** the debug register when modify QP timed out */
	EPSC_QUERY_MODQP_TO_DEBUG	 = 0x40,
	/** the bit vector containing the reasons for entering degraded mode */
	EPSC_QUERY_DEGRADED_CAUSE	 = 0x41,
	/** CMPL spin set mode (safe = 1 fast = 0) */
	EPSC_QUERY_SPIN_SET_CONTROL	 = 0x42,
	/** VPD MAC address */
	EPSC_QUERY_VPD_MAC	 = 0x43,
	/** VPD part number */
	EPSC_QUERY_VPD_PART_NUMBER	 = 0x44,
	/** VPD revision */
	EPSC_QUERY_VPD_REVISION	 = 0x45,
	/** VPD serial number (big endian sub-string) - 8 byte offset in query index */
	EPSC_QUERY_VPD_SERIAL_NUMBER	 = 0x46,
	/** VPD manufacturer = = Oracle Corporation - 8 byte offset in query index */
	EPSC_QUERY_VPD_MANUFACTURER	 = 0x47,
	/** PSIF TSU SL and QoS mapping for priv QP - port number in query index */
	EPSC_QUERY_MAP_PQP_TO_TSL	 = 0x48,
	/** PSIF TSU SL and QoS mapping for IB SL 0-7 - port number in query index */
	EPSC_QUERY_MAP_SL_TO_TSL_LO	 = 0x49,
	/** PSIF TSU SL and QoS mapping for IB SL 8-15 - port number in query index */
	EPSC_QUERY_MAP_SL_TO_TSL_HI	 = 0x4a,
	/** VPD Product Name - 8 byte offset in query index */
	EPSC_QUERY_VPD_PRODUCT_NAME	 = 0x4b,
	/* Padding out to required bits allocated */
	PSIF_EPSC_QUERY_OP_FIELD_MAX	 = 0x7fffffff
}; /* enum psif_epsc_query_op [32 bits] */

/**
 * Valid values for struct psif_epsc_csr_update::opcode
 */
enum psif_epsc_csr_update_opcode {
	EPSC_UPDATE_OP_POLL	 = 0,
	EPSC_UPDATE_OP_START,
	EPSC_UPDATE_OP_ERASE,
	EPSC_UPDATE_OP_WRITE,
	EPSC_UPDATE_OP_READ,
	EPSC_UPDATE_OP_STOP,
	EPSC_UPDATE_OP_SET,
	EPSC_UPDATE_OP_MAX,
	/* Padding out to required bits allocated */
	PSIF_EPSC_CSR_UPDATE_OPCODE_FIELD_MAX	 = 0xffff
}; /* enum psif_epsc_csr_update_opcode [16 bits] */

/**
 * Flash slot numbers used by e.g. EPSC_QUERY::EPSC_QUERY_FW_CURR_IMG
 */
enum psif_epsc_flash_slot {
	EPSC_FLASH_SLOT_INVALID,
	EPSC_FLASH_SLOT_EPS_C_IMG_1,
	EPSC_FLASH_SLOT_EPS_C_IMG_2,
	EPSC_FLASH_SLOT_EPS_A_IMG,
	EPSC_FLASH_SLOT_BOOT_IMG,
	/* always last */
	EPSC_FLASH_SLOT_COUNT,
	/* Padding out to required bits allocated */
	PSIF_EPSC_FLASH_SLOT_FIELD_MAX	 = 0xffff
}; /* enum psif_epsc_flash_slot [16 bits] */

/**
 * Valid values for struct psif_epsc_csr_update::u::set
 */
enum psif_epsc_update_set {
	EPSC_UPDATE_SET_INVALID,
	EPSC_UPDATE_SET_AUTOSTART_IMG,
	EPSC_UPDATE_SET_ONESHOT_IMG,
	EPSC_UPDATE_SET_TWOSHOT_IMG,
	EPSC_UPDATE_SET_IMG_VALID,
	/* Padding out to required bits allocated */
	PSIF_EPSC_UPDATE_SET_FIELD_MAX	 = 0x7fffffff
}; /* enum psif_epsc_update_set [32 bits] */

/**
 * Opcodes for psif_epsc_csr_uf_ctrl_t::opcode
 */
enum psif_epsc_csr_uf_ctrl_opcode {
	EPSC_UF_CTRL_MMU_FLUSH,
	EPSC_UF_CTRL_GET_UF_USED_QP,
	EPSC_UF_CTRL_CLEAR_UF_USED_QP,
	/** For SMP {en dis}able is the flag param a bitvector for which ports to update 0x6 hence indicate P1 and P2. */
	EPSC_UF_CTRL_SMP_ENABLE,
	EPSC_UF_CTRL_SMP_DISABLE,
	/** For Vlink {dis }connect is the flag param a bitvector for which ports to update 0x6 hence indicate P1 and P2. */
	EPSC_UF_CTRL_VLINK_CONNECT,
	EPSC_UF_CTRL_VLINK_DISCONNECT,
	/** Retrieve the highest QP number used by the given UF */
	EPSC_UF_CTRL_GET_HIGHEST_QP_IDX,
	/** Reset the highest QP number cache for the given UF */
	EPSC_UF_CTRL_RESET_HIGHEST_QP_IDX,
	/* Padding out to required bits allocated */
	PSIF_EPSC_CSR_UF_CTRL_OPCODE_FIELD_MAX	 = 0x7fffffff
}; /* enum psif_epsc_csr_uf_ctrl_opcode [32 bits] */

/**
 * \brief Host to VIMMA operation codes
 * \details
 * These operation codes are sent in the
 * \ref psif_epsc_csr_vimma_ctrl_t::opcode member
 * from the host to the mailbox thread in EPS-C in order to specify the
 * VIMMA request. In addition the operation
 * codes are used as a selector for the
 * \ref psif_epsc_csr_vimma_ctrl_t::u member of
 * psif_epsc_csr_vimma_ctrl_t in order to specify a particular
 * set of arguments if the request requires specific arguments.
 * \par
 * User of the VIMMA operation codes is the "PSIF SRIOV control API" library
 * running in Dom0 in user space. This library uses libsif to access the
 * mailbox. Requests are formed by using the VIMMA operation codes. Response
 * status is always delivered "inline" as return codes when the libsif API
 * returns from the mailbox operations.
 * Additional information retrieval can either be delivered "inline" as long
 * as space permits inside the mailbox response, OR responses
 * can also be extended by DMA-ing back response structures to pinned memory
 * in the library.
 * The DMA memory is prepared by the library before executing an opcode
 * that requires DMA for requested data.
 * \par
 * INLINE responses: Response data from VIMMA operation codes are delivered
 * via libsif to the "PSIF SRIOV control API" as two u64
 * parameters: "data" and "info".
 * These are carried by \ref psif_epsc_csr_rsp_t as part of mailbox response.
 * The encoding of the "data" and "info" responses depend on the VIMMA operation
 * code. For code using libsif library, the two u64 response codes "data"
 * and "info" is overlayed with the union
 * \ref psif_epsc_csr_vimma_ctrl_resp_inline_u,
 * and by using the opcode as a selector for the union members, the correct info
 * from the operation will be found.
 * \par
 * DMA responses: The requested data using DMA is delivered back to caller in
 * pinned memory of appropriate size. A pinned memory block of the maximum sized
 * response structure will do, and this can be obtained as
 * sizeof(psif_epsc_csr_vimma_ctrl_resp_dma_u) + appropriate extension for
 * for some variable arrays if those extend outside of
 * psif_epsc_csr_vimma_ctrl_resp_dma_uend of some union members.
 * The opcode just executed will be the selector for the union members.
 *
 * \par Width
 *      32 bit
 * \par Used in
 *      psif_epsc_csr_vimma_ctrl_t
 * \par Classification
 *      external
 *
 * \note
 * - In order to provide backward compatibility new codes must be added
 *   at the end of the enum. Deprecated codes can not be removed, but will instead
 *   be responded to with error codes if not supported anymore.
 */
enum psif_epsc_vimma_ctrl_opcode {
	/* no DMA.*/
	EPSC_VIMMA_CTRL_GET_VER_AND_COMPAT,
	/* DMA for resp. */
	EPSC_VIMMA_CTRL_GET_MISC_INFO,
	/* DMA for resp. */
	EPSC_VIMMA_CTRL_GET_GUIDS,
	/* DMA for resp. */
	EPSC_VIMMA_CTRL_GET_REG_INFO,
	/* DMA for resp. */
	EPSC_VIMMA_CTRL_GET_VHCA_STATS,
	/* no DMA. */
	EPSC_VIMMA_CTRL_SET_VFP_VHCA_REGISTER,
	/* no DMA. */
	EPSC_VIMMA_CTRL_SET_VFP_VHCA_DEREGISTER,
	/* no DMA or DMA if multiple UFs */
	EPSC_VIMMA_CTRL_SET_ADMIN_MODE,
	/* Padding out to required bits allocated */
	PSIF_EPSC_VIMMA_CTRL_OPCODE_FIELD_MAX	 = 0x7fffffff
}; /* enum psif_epsc_vimma_ctrl_opcode [32 bits] */


enum psif_epsc_vimma_admmode {
	EPSC_VIMMA_CTRL_IB_ADM_MODE_SM_STANDARD,
	/* VFP used as short for VM Fabric Profile */
	EPSC_VIMMA_CTRL_IB_ADM_MODE_VM_FABRIC_PROFILE,
	/* Padding out to required bits allocated */
	PSIF_EPSC_VIMMA_ADMMODE_FIELD_MAX	 = 0xffff
}; /* enum psif_epsc_vimma_admmode [16 bits] */

/**
 * For response structure to EPSC_PMA_COUNTERS Op.
 * Common PMA counters for TSU and IBU layers.
 */
enum psif_epsc_csr_pma_counters_enum {
	/** Regular counters - IB Spec chapter 16.1.3.5 */
	EPSC_PMA_SYMBOL_ERR_CNTR	 = 0,
	EPSC_PMA_LINK_ERR_RECOVERY_CNTR,
	EPSC_PMA_LINK_DOWNED_CNTR,
	EPSC_PMA_PORT_RCV_ERR,
	EPSC_PMA_PORT_RCV_REMOTE_PHYSICAL_ERR,
	EPSC_PMA_PORT_RCV_SWITCH_RELAY_ERR,
	EPSC_PMA_PORT_XMIT_DISCARD,
	EPSC_PMA_PORT_XMIT_CONSTRAINT_ERR,
	EPSC_PMA_PORT_RCV_CONSTRAINT_ERR,
	EPSC_PMA_LOCAL_LINK_INTEGRITY_ERR,
	EPSC_PMA_EXCESS_BUFF_OVERRUN_ERR,
	EPSC_PMA_VL15_DROPPED,
	/** Extended counters if Extended Width supported Regular otherwise */
	EPSC_PMA_PORT_XMIT_DATA,
	EPSC_PMA_PORT_RCV_DATA,
	EPSC_PMA_PORT_XMIT_PKTS,
	EPSC_PMA_PORT_RCV_PKTS,
	/**
	 * If ClassPortInfo:CapabilityMask.PortCountersXmitWaitSupported
	 * set to 1. IB Spec chapter 16.1.3.5
	 */
	EPSC_PMA_PORT_XMIT_WAIT,
	/** Strictly Extended counters - IB Spec Chapter 16.1.4.11 */
	EPSC_PMA_PORT_UNICAST_XMIT_PKTS,
	EPSC_PMA_PORT_UNICAST_RCV_PKTS,
	EPSC_PMA_PORT_MULTICAST_XMIT_PKTS,
	EPSC_PMA_PORT_MULTICAST_RCV_PKTS,
	/* IB Spec Chapter 16.1.4.1 */
	EPSC_PMA_PORT_LOCAL_PHYSICAL_ERR,
	/* Keep this in End */
	EPSC_PMA_COUNTERS_TOTAL,
	/* Padding out to required bits allocated */
	PSIF_EPSC_CSR_PMA_COUNTERS_ENUM_FIELD_MAX	 = 0x7fffffff
}; /* enum psif_epsc_csr_pma_counters_enum [32 bits] */

/**
 * \brief PSIF atomic op requester config values.
 * \details
 * \par Width
 *      2 bit
 * \par Used in
 *      psif_epsc_csr_config member `atomic_support`
 * \par Classification
 *      driver
 */
enum psif_epsc_csr_atomic_op {
	/** PSIF requests atomic operations for IB and SQS. */
	PSIF_PCIE_ATOMIC_OP_BOTH	 = 0,
	/** PSIF requests atomic operations for IB. */
	PSIF_PCIE_ATOMIC_OP_IB,
	/** PSIF requests atomic operations for SQS. */
	PSIF_PCIE_ATOMIC_OP_SQS,
	/** PSIF doesn't request atomic operations. */
	PSIF_PCIE_ATOMIC_OP_NONE
}; /* enum psif_epsc_csr_atomic_op [ 2 bits] */

/*
 * Completion notification states. Could take any of these values:
 * PSIF_CQ_UNARMED PSIF_CQ_ARMED_SE PSIF_CQ_ARMED_ALL PSIF_CQ_TRIGGERED
 */
enum psif_cq_state {
	PSIF_CQ_UNARMED,
	PSIF_CQ_ARMED_SE,
	PSIF_CQ_ARMED_ALL,
	PSIF_CQ_TRIGGERED
}; /* enum psif_cq_state [ 2 bits] */

/*
 * This is an indication if the RSS hash was generated with port inputs or
 * not.
 */
enum psif_rss_hash_source {
	RSS_WITHOUT_PORT,
	RSS_WITH_PORT
}; /* enum psif_rss_hash_source [ 1 bits] */

#if defined (HOST_LITTLE_ENDIAN)
#include "psif_hw_data_le.h"
#elif defined (HOST_BIG_ENDIAN)
#include "psif_hw_data_be.h"
#else
#error "Could not determine byte order in psif_hw_data.h !?"
#endif


#ifdef __cplusplus
}
#endif


#endif	/* _PSIF_HW_DATA_H */
