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

#ifndef	_PSIF_FW_ADDR_H
#define	_PSIF_FW_ADDR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "psif_api.h"


	/*
	 * TSU VL mapping table for requests. Inputs/addressing to this table are
	 * {UF(35 UFs), tsu_qosl (High/Low BAR), tsu_sl, port}.
	 */
#define TSU_HOST_TVL_TABLE_ADDR   0x00100000L
#define TSU_HOST_TVL_TABLE_STRIDE 1
#define TSU_HOST_TVL_TABLE_DEPTH  2240

	/* Per TVL register.Maximum global credits a particular TVL can get. */
#define TSU_HOST_MAX_GLOBAL_TVL_CRDTS_ADDR   0x00101000L
#define TSU_HOST_MAX_GLOBAL_TVL_CRDTS_STRIDE 1
#define TSU_HOST_MAX_GLOBAL_TVL_CRDTS_DEPTH  128

	/*
	 * Per TVL register.Maximum private credits a particular TVL can get. The
	 * amount of credits dedicated to this TVL.
	 */
#define TSU_HOST_PRIVATE_TVL_CRDTS_ADDR   0x00101080L
#define TSU_HOST_PRIVATE_TVL_CRDTS_STRIDE 1
#define TSU_HOST_PRIVATE_TVL_CRDTS_DEPTH  128

	/* Total number of global credits assign to TVLs. */
#define TSU_HOST_TOTAL_GLOBAL_TVL_CRDTS_ADDR   0x00101100L
#define TSU_HOST_TOTAL_GLOBAL_TVL_CRDTS_STRIDE 1
#define TSU_HOST_TOTAL_GLOBAL_TVL_CRDTS_DEPTH  1

	/* weight given for round robin arbitration for xiu commands. */
#define TSU_HOST_XIU_ARBITER_ADDR   0x00101101L
#define TSU_HOST_XIU_ARBITER_STRIDE 1
#define TSU_HOST_XIU_ARBITER_DEPTH  1

	/* weight given for round robin arbitration for eps commands. */
#define TSU_HOST_EPS_ARBITER_ADDR   0x00101102L
#define TSU_HOST_EPS_ARBITER_STRIDE 1
#define TSU_HOST_EPS_ARBITER_DEPTH  1

	/* Data Latency skew from all clients to tsu_host. */
#define TSU_HOST_DATA_LATENCY_ADDR   0x00101104L
#define TSU_HOST_DATA_LATENCY_STRIDE 1
#define TSU_HOST_DATA_LATENCY_DEPTH  1

	/*
	 * Per TVL register. The amount of private and global credits used to this
	 * TVL.
	 */
#define TSU_HOST_TVL_CRDTS_USED_ADDR   0x00101108L
#define TSU_HOST_TVL_CRDTS_USED_STRIDE 1
#define TSU_HOST_TVL_CRDTS_USED_DEPTH  128

	/* Amount of global credits used shared among all TVLs. */
#define TSU_HOST_GLOBAL_CRDTS_USED_ADDR   0x00101188L
#define TSU_HOST_GLOBAL_CRDTS_USED_STRIDE 1
#define TSU_HOST_GLOBAL_CRDTS_USED_DEPTH  1

	/* when set puts the tsu_host in hca mode for Atomics. */
#define TSU_HOST_HCA_MODE_ADDR   0x0010118aL
#define TSU_HOST_HCA_MODE_STRIDE 1
#define TSU_HOST_HCA_MODE_DEPTH  1

	/*
	 * when set flips the compare and swap field in xiu meta_data bus in PCIe
	 * mode.
	 */
#define TSU_HOST_ENABLE_PCIE_SWAP_ADDR   0x0010118bL
#define TSU_HOST_ENABLE_PCIE_SWAP_STRIDE 1
#define TSU_HOST_ENABLE_PCIE_SWAP_DEPTH  1

	/* Handling Endianness of host Processor. */
#define TSU_HOST_LITTLE_ENDIAN_MODE_ADDR   0x0010118cL
#define TSU_HOST_LITTLE_ENDIAN_MODE_STRIDE 1
#define TSU_HOST_LITTLE_ENDIAN_MODE_DEPTH  1

	/* allocating global credits to llq in XIU */
#define TSU_HOST_XIU_LLQ_GLOBAL_CREDITS_ADDR   0x0010118dL
#define TSU_HOST_XIU_LLQ_GLOBAL_CREDITS_STRIDE 1
#define TSU_HOST_XIU_LLQ_GLOBAL_CREDITS_DEPTH  1

#define TSU_HOST_QP_BASE_ADDR_0_ADDR   0x00101194L
#define TSU_HOST_QP_BASE_ADDR_0_STRIDE 1
#define TSU_HOST_QP_BASE_ADDR_0_DEPTH  34

#define TSU_HOST_QP_BASE_ADDR_1_ADDR   0x001011d4L
#define TSU_HOST_QP_BASE_ADDR_1_STRIDE 1
#define TSU_HOST_QP_BASE_ADDR_1_DEPTH  34

#define TSU_HOST_QP_BASE_ADDR_2_ADDR   0x00101214L
#define TSU_HOST_QP_BASE_ADDR_2_STRIDE 1
#define TSU_HOST_QP_BASE_ADDR_2_DEPTH  34

	/* MRS credit debug counter. */
#define TSU_HOST_MRS_CREDIT_CNT_ADDR   0x00101256L
#define TSU_HOST_MRS_CREDIT_CNT_STRIDE 1
#define TSU_HOST_MRS_CREDIT_CNT_DEPTH  1

	/* ERR credit debug counter. */
#define TSU_HOST_ERR_CREDIT_CNT_ADDR   0x00101257L
#define TSU_HOST_ERR_CREDIT_CNT_STRIDE 1
#define TSU_HOST_ERR_CREDIT_CNT_DEPTH  1

	/* LLQ debug counter. */
#define TSU_HOST_LLQ_CNT_ADDR   0x00101258L
#define TSU_HOST_LLQ_CNT_STRIDE 1
#define TSU_HOST_LLQ_CNT_DEPTH  1

	/* Interrupt status register. 1b per source (1 = int triggered). */
#define TSU_HOST_INT_STATUS_ADDR   0x00101259L
#define TSU_HOST_INT_STATUS_STRIDE 1
#define TSU_HOST_INT_STATUS_DEPTH  1

	/* Interrupt mask register. 1b per source (1 = masked). */
#define TSU_HOST_INT_MASK_ADDR   0x0010125aL
#define TSU_HOST_INT_MASK_STRIDE 1
#define TSU_HOST_INT_MASK_DEPTH  1

	/* Interrupt priority register. 1b per source (1 = high 0 = low). */
#define TSU_HOST_INT_PRI_ADDR   0x0010125bL
#define TSU_HOST_INT_PRI_STRIDE 1
#define TSU_HOST_INT_PRI_DEPTH  1

	/*
	 * Interrupt status clear register. 1b per source (1=source will be cleared
	 * from int_status register when kick is called).
	 */
#define TSU_HOST_INT_STATUS_CLEAR_ADDR   0x0010125cL
#define TSU_HOST_INT_STATUS_CLEAR_STRIDE 1
#define TSU_HOST_INT_STATUS_CLEAR_DEPTH  1

	/* Trigger the int_status clear operation. */
#define TSU_HOST_INT_STATUS_CLEAR_KICK_ADDR   0x0010125dL
#define TSU_HOST_INT_STATUS_CLEAR_KICK_STRIDE 1
#define TSU_HOST_INT_STATUS_CLEAR_KICK_DEPTH  1

	/*
	 * Set when an MMU translation error occur for a write. This feeds into the
	 * interrupt status register.
	 */
#define TSU_HOST_MMU_TRANSLATION_ERROR_ADDR   0x0010125eL
#define TSU_HOST_MMU_TRANSLATION_ERROR_STRIDE 1
#define TSU_HOST_MMU_TRANSLATION_ERROR_DEPTH  1

	/* Used to clear bits in the mmu_translation_error register. */
#define TSU_HOST_MMU_TRANSLATION_ERROR_CLEAR_ADDR   0x0010125fL
#define TSU_HOST_MMU_TRANSLATION_ERROR_CLEAR_STRIDE 1
#define TSU_HOST_MMU_TRANSLATION_ERROR_CLEAR_DEPTH  1

	/* . This feeds into the interrupt status register. */
#define TSU_HOST_ATOMIC_ERROR_ADDR   0x00101260L
#define TSU_HOST_ATOMIC_ERROR_STRIDE 1
#define TSU_HOST_ATOMIC_ERROR_DEPTH  1

	/* Used to clear bits in the atomic_error register. */
#define TSU_HOST_ATOMIC_ERROR_CLEAR_ADDR   0x00101261L
#define TSU_HOST_ATOMIC_ERROR_CLEAR_STRIDE 1
#define TSU_HOST_ATOMIC_ERROR_CLEAR_DEPTH  1

	/*
	 * EPS address which caused the int_status.eps_address_invalid to get set.
	 */
#define TSU_HOST_EPS_ADDRESS_ADDR   0x00101400L
#define TSU_HOST_EPS_ADDRESS_STRIDE 1
#define TSU_HOST_EPS_ADDRESS_DEPTH  2

	/* ECC and Parity Errors status register. */
#define TSU_HOST_ECC_ERRS_ADDR   0x00101440L
#define TSU_HOST_ECC_ERRS_STRIDE 1
#define TSU_HOST_ECC_ERRS_DEPTH  2

	/* Setting tsu_host in memory Dynamic Reconfiguration. */
#define TSU_HOST_DR_MODE_ADDR   0x00101442L
#define TSU_HOST_DR_MODE_STRIDE 1
#define TSU_HOST_DR_MODE_DEPTH  1

	/* UF where memory Dynamic Reconfiguration is being performed. */
#define TSU_HOST_RELOC_UF_ADDR   0x00101443L
#define TSU_HOST_RELOC_UF_STRIDE 1
#define TSU_HOST_RELOC_UF_DEPTH  1

	/* Base address[51:12] where current data is being stored. */
#define TSU_HOST_RELOC_BASE_ADDR   0x00101444L
#define TSU_HOST_RELOC_BASE_STRIDE 1
#define TSU_HOST_RELOC_BASE_DEPTH  1

	/*
	 * relocation bound pointer[51:12] to enable translation for addresses
	 * between reloc_base and reloc_bound1.Stalls commands between reloc_bound1
	 * and reloc_bound2.
	 */
#define TSU_HOST_RELOC_BOUND1_ADDR   0x00101445L
#define TSU_HOST_RELOC_BOUND1_STRIDE 1
#define TSU_HOST_RELOC_BOUND1_DEPTH  1

	/*
	 * relocation bound pointer[51:12] to stall commands between reloc_bound1 and
	 * reloc_bound2.
	 */
#define TSU_HOST_RELOC_BOUND2_ADDR   0x00101446L
#define TSU_HOST_RELOC_BOUND2_STRIDE 1
#define TSU_HOST_RELOC_BOUND2_DEPTH  1

	/* Base address[51:12] where data is being relocated to when dr_mode is set. */
#define TSU_HOST_RELOC_NEW_ADDR   0x00101447L
#define TSU_HOST_RELOC_NEW_STRIDE 1
#define TSU_HOST_RELOC_NEW_DEPTH  1

	/*
	 * Page size enable bits[31:12].This is to set the corresponding bits in the
	 * address starting at address[12]. If all bits are zero the page size is
	 * 4KBytes. If all bits set page size is 4GBytes.
	 */
#define TSU_HOST_PAGE_SIZE_BITS_ENBL_ADDR   0x00101448L
#define TSU_HOST_PAGE_SIZE_BITS_ENBL_STRIDE 1
#define TSU_HOST_PAGE_SIZE_BITS_ENBL_DEPTH  1

	/* Provides information when a region is being stalled when dr_mode is set. */
#define TSU_HOST_SEND_MESSAGE_ADDR   0x00101449L
#define TSU_HOST_SEND_MESSAGE_STRIDE 1
#define TSU_HOST_SEND_MESSAGE_DEPTH  1

	/*
	 * This is the data sent when send_message is sent in the send_message
	 * completion command.
	 */
#define TSU_HOST_RELOC_SEND_MSG_DATA_ADDR   0x0010144aL
#define TSU_HOST_RELOC_SEND_MSG_DATA_STRIDE 1
#define TSU_HOST_RELOC_SEND_MSG_DATA_DEPTH  4

	/* This is the address where the send_message needs to go. */
#define TSU_HOST_RELOC_SEND_MSG_ADD_ADDR   0x0010144eL
#define TSU_HOST_RELOC_SEND_MSG_ADD_STRIDE 1
#define TSU_HOST_RELOC_SEND_MSG_ADD_DEPTH  1

	/*
	 * This is to use the same llq index in XIU for commands being sent to the
	 * relocation region.
	 */
#define TSU_HOST_RELOC_XIU_INDEX_ADDR   0x0010144fL
#define TSU_HOST_RELOC_XIU_INDEX_STRIDE 1
#define TSU_HOST_RELOC_XIU_INDEX_DEPTH  1

	/* This is to set the value for tph ns ro st. */
#define TSU_HOST_PCIE_BITS_ADDR   0x00101450L
#define TSU_HOST_PCIE_BITS_STRIDE 1
#define TSU_HOST_PCIE_BITS_DEPTH  1

	/* Configuration bits when putting the chip in sonoma mode. */
#define TSU_HOST_SONOMA_CONFIG_ADDR   0x00101451L
#define TSU_HOST_SONOMA_CONFIG_STRIDE 1
#define TSU_HOST_SONOMA_CONFIG_DEPTH  1

	/*
	 * Fatal Interrupt and Stop Mask register1b per source. stop-masks: 1=error
	 * does not cause host to stop processing) ECC, or CAM Parity error if
	 * enabled, will cause a fatal interrupt. Decide whether or not to stop all
	 * host processing when this error occurs.
	 */
#define TSU_HOST_FATAL_INT_MASK_ADDR   0x00101480L
#define TSU_HOST_FATAL_INT_MASK_STRIDE 1
#define TSU_HOST_FATAL_INT_MASK_DEPTH  1

	/* Received count per UF for completions and events. */
#define TSU_HOST_EVENT_CQ_RECEIVED_ADDR   0x001014c0L
#define TSU_HOST_EVENT_CQ_RECEIVED_STRIDE 1
#define TSU_HOST_EVENT_CQ_RECEIVED_DEPTH  34

	/* Interrupt Total Moderation */
#define TSU_HOST_INT_CTRL_ADDR   0x00102000L
#define TSU_HOST_INT_CTRL_STRIDE 1
#define TSU_HOST_INT_CTRL_DEPTH  1

	/* Interrupt Channel Control 0 */
#define TSU_HOST_INT_CHAN_CTRL_0_ADDR   0x00102100L
#define TSU_HOST_INT_CHAN_CTRL_0_STRIDE 1
#define TSU_HOST_INT_CHAN_CTRL_0_DEPTH  128

	/* Interrupt Channel Control 1 */
#define TSU_HOST_INT_CHAN_CTRL_1_ADDR   0x00102180L
#define TSU_HOST_INT_CHAN_CTRL_1_STRIDE 1
#define TSU_HOST_INT_CHAN_CTRL_1_DEPTH  128

	/* Interrupt Channel Control 2 */
#define TSU_HOST_INT_CHAN_CTRL_2_ADDR   0x00102200L
#define TSU_HOST_INT_CHAN_CTRL_2_STRIDE 1
#define TSU_HOST_INT_CHAN_CTRL_2_DEPTH  128

	/* MMU context per UF - containing the failing MMU context */
#define TSU_HOST_MMU_TRANSLATION_ERROR_MMU_CONTEXT_ADDR   0x00104000L
#define TSU_HOST_MMU_TRANSLATION_ERROR_MMU_CONTEXT_STRIDE 1
#define TSU_HOST_MMU_TRANSLATION_ERROR_MMU_CONTEXT_DEPTH  34

	/* Address per UF - containing the failing address. */
#define TSU_HOST_MMU_TRANSLATION_ERROR_ADDRESS_ADDR   0x00104040L
#define TSU_HOST_MMU_TRANSLATION_ERROR_ADDRESS_STRIDE 1
#define TSU_HOST_MMU_TRANSLATION_ERROR_ADDRESS_DEPTH  34

	/* MMU Static-Configuration and Status */
#define TSU_MMU_MMU_CONFIG_ADDR   0x00200000L
#define TSU_MMU_MMU_CONFIG_STRIDE 1
#define TSU_MMU_MMU_CONFIG_DEPTH  1

	/* MMU Credit Configuration */
#define TSU_MMU_CREDIT_CONFIG_ADDR   0x00200001L
#define TSU_MMU_CREDIT_CONFIG_STRIDE 1
#define TSU_MMU_CREDIT_CONFIG_DEPTH  1

	/* PA Address Size Configuration */
#define TSU_MMU_PA_MASK_ADDR   0x00200002L
#define TSU_MMU_PA_MASK_STRIDE 1
#define TSU_MMU_PA_MASK_DEPTH  1

	/* Flush MMU and-or PTW Caches. */
#define TSU_MMU_FLUSH_CACHES_ADDR   0x00200003L
#define TSU_MMU_FLUSH_CACHES_STRIDE 1
#define TSU_MMU_FLUSH_CACHES_DEPTH  1

	/* Statistic Counters. */
#define TSU_MMU_STAT_COUNTERS_ADDR   0x00200004L
#define TSU_MMU_STAT_COUNTERS_STRIDE 1
#define TSU_MMU_STAT_COUNTERS_DEPTH  1

	/* ECC and Parity Errors. */
#define TSU_MMU_ECC_PARITY_ERRS_ADDR   0x00200008L
#define TSU_MMU_ECC_PARITY_ERRS_STRIDE 1
#define TSU_MMU_ECC_PARITY_ERRS_DEPTH  2

	/*
	 * This register must be set and the kick register is written in order to
	 * start the operation.
	 */
#define TSU_MMU_UF_CONTROL_ADDR   0x00200040L
#define TSU_MMU_UF_CONTROL_STRIDE 1
#define TSU_MMU_UF_CONTROL_DEPTH  1

	/* Starts operation defined in uf_control. */
#define TSU_MMU_UF_CONTROL_KICK_ADDR   0x00200041L
#define TSU_MMU_UF_CONTROL_KICK_STRIDE 1
#define TSU_MMU_UF_CONTROL_KICK_DEPTH  1

	/* Interrupt status register. 1b per source (1 = int triggered). */
#define TSU_MMU_INT_STATUS_ADDR   0x00200042L
#define TSU_MMU_INT_STATUS_STRIDE 1
#define TSU_MMU_INT_STATUS_DEPTH  1

	/* Interrupt mask register. 1b per source (1 = masked). */
#define TSU_MMU_INT_MASK_ADDR   0x00200043L
#define TSU_MMU_INT_MASK_STRIDE 1
#define TSU_MMU_INT_MASK_DEPTH  1

	/* Interrupt priority register. 1b per source (1 = high 0 = low). */
#define TSU_MMU_INT_PRI_ADDR   0x00200044L
#define TSU_MMU_INT_PRI_STRIDE 1
#define TSU_MMU_INT_PRI_DEPTH  1

	/*
	 * Interrupt status clear register. 1b per source (1=source will be cleared
	 * from int_status register when kick is called).
	 */
#define TSU_MMU_INT_STATUS_CLEAR_ADDR   0x00200045L
#define TSU_MMU_INT_STATUS_CLEAR_STRIDE 1
#define TSU_MMU_INT_STATUS_CLEAR_DEPTH  1

	/* Trigger the int_status clear operation. */
#define TSU_MMU_INT_STATUS_CLEAR_KICK_ADDR   0x00200046L
#define TSU_MMU_INT_STATUS_CLEAR_KICK_STRIDE 1
#define TSU_MMU_INT_STATUS_CLEAR_KICK_DEPTH  1

	/* Uncorrectable-Fatal Error Mask */
#define TSU_MMU_UNCOR_ERR_MASK_ADDR   0x00200047L
#define TSU_MMU_UNCOR_ERR_MASK_STRIDE 1
#define TSU_MMU_UNCOR_ERR_MASK_DEPTH  1

	/* MMU Cache VA Address Mask */
#define TSU_MMU_MMUC_VA_MASK_ADDR   0x00200048L
#define TSU_MMU_MMUC_VA_MASK_STRIDE 1
#define TSU_MMU_MMUC_VA_MASK_DEPTH  1

	/* tsu_mmu_llq Debug Signals */
#define TSU_MMU_MMU_LLQ_MOD_DEBUG_ADDR   0x00200049L
#define TSU_MMU_MMU_LLQ_MOD_DEBUG_STRIDE 1
#define TSU_MMU_MMU_LLQ_MOD_DEBUG_DEPTH  1

	/* tsu_mmu_cache Debug Signals */
#define TSU_MMU_MMU_CACHE_MOD_DEBUG_ADDR   0x0020004aL
#define TSU_MMU_MMU_CACHE_MOD_DEBUG_STRIDE 1
#define TSU_MMU_MMU_CACHE_MOD_DEBUG_DEPTH  1

	/* tsu_mmu_ptw Debug Signals */
#define TSU_MMU_MMU_PTW_MOD_DEBUG_ADDR   0x0020004bL
#define TSU_MMU_MMU_PTW_MOD_DEBUG_STRIDE 1
#define TSU_MMU_MMU_PTW_MOD_DEBUG_DEPTH  1

	/* Page Table Walk Error Debug State Reg0 */
#define TSU_MMU_PTW_ERROR_DEBUG_REG0_ADDR   0x0020004cL
#define TSU_MMU_PTW_ERROR_DEBUG_REG0_STRIDE 1
#define TSU_MMU_PTW_ERROR_DEBUG_REG0_DEPTH  1

	/* Page Table Walk Error Debug State Reg1 */
#define TSU_MMU_PTW_ERROR_DEBUG_REG1_ADDR   0x0020004dL
#define TSU_MMU_PTW_ERROR_DEBUG_REG1_STRIDE 1
#define TSU_MMU_PTW_ERROR_DEBUG_REG1_DEPTH  1

	/* Page Table Walk Error Debug State Reg2 */
#define TSU_MMU_PTW_ERROR_DEBUG_REG2_ADDR   0x0020004eL
#define TSU_MMU_PTW_ERROR_DEBUG_REG2_STRIDE 1
#define TSU_MMU_PTW_ERROR_DEBUG_REG2_DEPTH  1

	/* Clear the PTW debug error registers. */
#define TSU_MMU_PTW_DEBUG_CLEAR_KICK_ADDR   0x0020004fL
#define TSU_MMU_PTW_DEBUG_CLEAR_KICK_STRIDE 1
#define TSU_MMU_PTW_DEBUG_CLEAR_KICK_DEPTH  1

	/*
	 * TSU VL mapping table for requests. Inputs/addressing to this table are
	 * {UF, tsu_qosl (High/Low BAR), tsu_sl}.
	 */
#define TSU_CBU_TVL_TABLE_ADDR   0x00300000L
#define TSU_CBU_TVL_TABLE_STRIDE 1
#define TSU_CBU_TVL_TABLE_DEPTH  1120

	/*
	 * Below dcb_bar address is a write to the VCB, else write to the DCB.
	 * dcb_bar = 0 applies no VCB. Below this qosl_bar address is low BAR, else
	 * is high BAR. Inputs/addressing to this table is UF.
	 */
#define TSU_CBU_SUB_BAR_ADDR_ADDR   0x00300800L
#define TSU_CBU_SUB_BAR_ADDR_STRIDE 1
#define TSU_CBU_SUB_BAR_ADDR_DEPTH  33

	/*
	 * Virtual collect buffer start offset. VCB#=vcb_start_offset + pio
	 * address[25:12]. Inputs/addressing to this table is UF.
	 */
#define TSU_CBU_VCB_START_OFFSET_ADDR   0x00300840L
#define TSU_CBU_VCB_START_OFFSET_STRIDE 1
#define TSU_CBU_VCB_START_OFFSET_DEPTH  33

	/*
	 * How many physical collect buffers are allocated to the high BAR.
	 * Inputs/addressing to this table is UF.
	 */
#define TSU_CBU_PCB_ALLOC_HIGH_ADDR   0x00300880L
#define TSU_CBU_PCB_ALLOC_HIGH_STRIDE 1
#define TSU_CBU_PCB_ALLOC_HIGH_DEPTH  33

	/*
	 * How many physical collect buffers are allocated to the low BAR.
	 * Inputs/addressing to this table is UF.
	 */
#define TSU_CBU_PCB_ALLOC_LOW_ADDR   0x003008c0L
#define TSU_CBU_PCB_ALLOC_LOW_STRIDE 1
#define TSU_CBU_PCB_ALLOC_LOW_DEPTH  33

	/*
	 * How many physical collect buffers are available. Inputs/addressing to this
	 * table is UF.
	 */
#define TSU_CBU_PCB_AVAILABLE_ADDR   0x00300900L
#define TSU_CBU_PCB_AVAILABLE_STRIDE 1
#define TSU_CBU_PCB_AVAILABLE_DEPTH  33

	/*
	 * How many physical collect buffers are used in high BAR. Inputs/addressing
	 * to this table is UF.
	 */
#define TSU_CBU_PCB_HIGH_USED_ADDR   0x00300940L
#define TSU_CBU_PCB_HIGH_USED_STRIDE 1
#define TSU_CBU_PCB_HIGH_USED_DEPTH  33

	/*
	 * How many physical collect buffers are used in low BAR. Inputs/addressing
	 * to this table is UF.
	 */
#define TSU_CBU_PCB_LOW_USED_ADDR   0x00300980L
#define TSU_CBU_PCB_LOW_USED_STRIDE 1
#define TSU_CBU_PCB_LOW_USED_DEPTH  33

	/* scoreboard init. */
#define TSU_CBU_SCBD_INIT_ADDR   0x003009c0L
#define TSU_CBU_SCBD_INIT_STRIDE 1
#define TSU_CBU_SCBD_INIT_DEPTH  1

	/* scoreboard init done status. */
#define TSU_CBU_SCBD_INIT_DONE_ADDR   0x003009c1L
#define TSU_CBU_SCBD_INIT_DONE_STRIDE 1
#define TSU_CBU_SCBD_INIT_DONE_DEPTH  1

	/* Start offset of dedicated collect buffers number for the host driver. */
#define TSU_CBU_DCB_START_OFFSET_HOST_ADDR   0x003009c2L
#define TSU_CBU_DCB_START_OFFSET_HOST_STRIDE 1
#define TSU_CBU_DCB_START_OFFSET_HOST_DEPTH  1

	/* Start offset of dedicated collect buffers number for the eps. */
#define TSU_CBU_DCB_START_OFFSET_EPS_ADDR   0x003009c3L
#define TSU_CBU_DCB_START_OFFSET_EPS_STRIDE 1
#define TSU_CBU_DCB_START_OFFSET_EPS_DEPTH  1

	/*
	 * Start offset of dedicated collect buffers number for the send queue
	 * scheduler.
	 */
#define TSU_CBU_DCB_START_OFFSET_SQS_ADDR   0x003009c4L
#define TSU_CBU_DCB_START_OFFSET_SQS_STRIDE 1
#define TSU_CBU_DCB_START_OFFSET_SQS_DEPTH  1

	/* Collect length round up to 64B for scoreboard. */
#define TSU_CBU_COLLECT_LEN_ROUNDUP_ADDR   0x003009c5L
#define TSU_CBU_COLLECT_LEN_ROUNDUP_STRIDE 1
#define TSU_CBU_COLLECT_LEN_ROUNDUP_DEPTH  1

	/* ECC error control */
#define TSU_CBU_ECC_ERR_CTRL_ADDR   0x003009c6L
#define TSU_CBU_ECC_ERR_CTRL_STRIDE 1
#define TSU_CBU_ECC_ERR_CTRL_DEPTH  1

	/* ECC status */
#define TSU_CBU_ECC_ERR_STATUS_ADDR   0x003009c7L
#define TSU_CBU_ECC_ERR_STATUS_STRIDE 1
#define TSU_CBU_ECC_ERR_STATUS_DEPTH  1

	/* ECC status */
#define TSU_CBU_ECC_ERR_STATUS_CLEAR_ADDR   0x003009c8L
#define TSU_CBU_ECC_ERR_STATUS_CLEAR_STRIDE 1
#define TSU_CBU_ECC_ERR_STATUS_CLEAR_DEPTH  1

	/* Number of VCB checksum Error */
#define TSU_CBU_NUM_VCB_CHECKSUM_ERR_ADDR   0x003009c9L
#define TSU_CBU_NUM_VCB_CHECKSUM_ERR_STRIDE 1
#define TSU_CBU_NUM_VCB_CHECKSUM_ERR_DEPTH  1

	/* Number of VCB checksum Error */
#define TSU_CBU_NUM_VCB_CHECKSUM_LOCKED_ADDR   0x003009caL
#define TSU_CBU_NUM_VCB_CHECKSUM_LOCKED_STRIDE 1
#define TSU_CBU_NUM_VCB_CHECKSUM_LOCKED_DEPTH  1

	/* Number of VCB checksum Error */
#define TSU_CBU_NUM_DCB_CHECKSUM_ERR_ADDR   0x003009cbL
#define TSU_CBU_NUM_DCB_CHECKSUM_ERR_STRIDE 1
#define TSU_CBU_NUM_DCB_CHECKSUM_ERR_DEPTH  1

	/* Number of VCB checksum Error */
#define TSU_CBU_NUM_DCB_CHECKSUM_LOCKED_ADDR   0x003009ccL
#define TSU_CBU_NUM_DCB_CHECKSUM_LOCKED_STRIDE 1
#define TSU_CBU_NUM_DCB_CHECKSUM_LOCKED_DEPTH  1

	/* Interrupt status register. 1b per source (1 = int triggered). */
#define TSU_CBU_INT_STATUS_ADDR   0x003009cdL
#define TSU_CBU_INT_STATUS_STRIDE 1
#define TSU_CBU_INT_STATUS_DEPTH  1

	/* Interrupt mask register. 1b per source (1 = masked). */
#define TSU_CBU_INT_MASK_ADDR   0x003009ceL
#define TSU_CBU_INT_MASK_STRIDE 1
#define TSU_CBU_INT_MASK_DEPTH  1

	/* Interrupt priority register. 1b per source (1 = high 0 = low). */
#define TSU_CBU_INT_PRI_ADDR   0x003009cfL
#define TSU_CBU_INT_PRI_STRIDE 1
#define TSU_CBU_INT_PRI_DEPTH  1

	/*
	 * Interrupt status clear register. 1b per source (1=source will be cleared
	 * from int_status register when kick is called).
	 */
#define TSU_CBU_INT_STATUS_CLEAR_ADDR   0x003009d0L
#define TSU_CBU_INT_STATUS_CLEAR_STRIDE 1
#define TSU_CBU_INT_STATUS_CLEAR_DEPTH  1

	/* Trigger the int_status clear operation. */
#define TSU_CBU_INT_STATUS_CLEAR_KICK_ADDR   0x003009d1L
#define TSU_CBU_INT_STATUS_CLEAR_KICK_STRIDE 1
#define TSU_CBU_INT_STATUS_CLEAR_KICK_DEPTH  1

	/* kick counter and dcb list ready for 64 to 69 */
#define TSU_CBU_KICK_COUNTER_ADDR   0x003009d2L
#define TSU_CBU_KICK_COUNTER_STRIDE 1
#define TSU_CBU_KICK_COUNTER_DEPTH  1

	/* dcb list ready for 0 to 63. */
#define TSU_CBU_DCB_LIST_READY_ADDR   0x003009d3L
#define TSU_CBU_DCB_LIST_READY_STRIDE 1
#define TSU_CBU_DCB_LIST_READY_DEPTH  1

	/* Per UF to drop PIO. Inputs/addressing to this table is UF. */
#define TSU_CBU_CHOKE_ADDR   0x00300a00L
#define TSU_CBU_CHOKE_STRIDE 1
#define TSU_CBU_CHOKE_DEPTH  33

	/* UF choke status. Inputs/addressing to this table is UF. */
#define TSU_CBU_UF_STATUS_ADDR   0x00300a40L
#define TSU_CBU_UF_STATUS_STRIDE 1
#define TSU_CBU_UF_STATUS_DEPTH  33

	/* PIO DCB start_offset. Inputs/addressing to this table is UF. */
#define TSU_CBU_DCB_START_OFFSET_ADDR   0x00300b00L
#define TSU_CBU_DCB_START_OFFSET_STRIDE 1
#define TSU_CBU_DCB_START_OFFSET_DEPTH  33

	/*
	 * Table to contain UF number for each DCB. EPS/Host drive has to write UF #
	 * to this table before it writes to the DCB. Inputs/addressing to this table
	 * is DCB#
	 */
#define TSU_CBU_DCB_UF_TABLE_ADDR   0x00301000L
#define TSU_CBU_DCB_UF_TABLE_STRIDE 1
#define TSU_CBU_DCB_UF_TABLE_DEPTH  256

	/*
	 * Status state of each DCB. The EPS/Host drive has to read this table to
	 * claim a DCB. Inputs/addressing to this table is DCB#
	 */
#define TSU_CBU_DCB_STATUS_HW_LOCK_ADDR   0x00301100L
#define TSU_CBU_DCB_STATUS_HW_LOCK_STRIDE 1
#define TSU_CBU_DCB_STATUS_HW_LOCK_DEPTH  256

	/* Status state of each DCB. Inputs/addressing to this table is DCB# */
#define TSU_CBU_DCB_STATUS_ADDR   0x00301200L
#define TSU_CBU_DCB_STATUS_STRIDE 1
#define TSU_CBU_DCB_STATUS_DEPTH  256

	/* dcb clear. Inputs/addressing to this table is scoreboard table. */
#define TSU_CBU_DCB_CLEAR_ADDR   0x00301300L
#define TSU_CBU_DCB_CLEAR_STRIDE 1
#define TSU_CBU_DCB_CLEAR_DEPTH  256

	/*
	 * DCB doorbell header/payload memory from EPS-C. Address[13:6] = DCB number
	 * and Address[5:0] = 8 bytes offset into the DCB.
	 */
#define TSU_CBU_DCB_DOORBELL_ADDR   0x00304000L
#define TSU_CBU_DCB_DOORBELL_STRIDE 1
#define TSU_CBU_DCB_DOORBELL_DEPTH  16384

	/*
	 * vcb clear. Inputs/addressing to this table is scoreboard table. Write to
	 * clear VCB, Read to get the scoreboard status
	 */
#define TSU_CBU_VCB_CLEAR_ADDR   0x00308000L
#define TSU_CBU_VCB_CLEAR_STRIDE 1
#define TSU_CBU_VCB_CLEAR_DEPTH  16384

	/*
	 * Initial completion credit per TVL. This is private credit for the
	 * particular TVL and can only be used by this TVL. The private completion
	 * credit indicates how many entries in tsu_cmpl are reserved for requests on
	 * this TVL.
	 */
#define TSU_RQS_PRIVATE_CMPL_CREDIT_ADDR   0x00400000L
#define TSU_RQS_PRIVATE_CMPL_CREDIT_STRIDE 1
#define TSU_RQS_PRIVATE_CMPL_CREDIT_DEPTH  128

	/*
	 * Current completion credits used per TVL. This is credit currently used by
	 * a particular TVL. This register is updated by hardware and can be read by
	 * software.
	 */
#define TSU_RQS_TVL_CMPL_CREDIT_CONSUMED_ADDR   0x00400080L
#define TSU_RQS_TVL_CMPL_CREDIT_CONSUMED_STRIDE 1
#define TSU_RQS_TVL_CMPL_CREDIT_CONSUMED_DEPTH  128

	/*
	 * Initial completion credit for the free pool. The free pool can be used by
	 * anyone being set up to use common credits. This is additional credits
	 * which can be used in addition to the private TVL completion credit. The
	 * common completion credit indicates how many entries in tsu_cmpl can be
	 * used by any TVL. It is a restriction that the TVL is set up to use common
	 * credit.
	 */
#define TSU_RQS_COMMON_CMPL_CREDIT_ADDR   0x00400100L
#define TSU_RQS_COMMON_CMPL_CREDIT_STRIDE 1
#define TSU_RQS_COMMON_CMPL_CREDIT_DEPTH  1

	/*
	 * This is register contain the number of currently consumed common
	 * completion credits. This register is updated by hardware and can be read
	 * from software.
	 */
#define TSU_RQS_COMMON_CMPL_CREDIT_CONSUMED_ADDR   0x00400101L
#define TSU_RQS_COMMON_CMPL_CREDIT_CONSUMED_STRIDE 1
#define TSU_RQS_COMMON_CMPL_CREDIT_CONSUMED_DEPTH  1

#define TSU_RQS_COMMON_CMPL_CREDIT_ENABLE_0_ADDR   0x00400102L
#define TSU_RQS_COMMON_CMPL_CREDIT_ENABLE_0_STRIDE 2
#define TSU_RQS_COMMON_CMPL_CREDIT_ENABLE_0_DEPTH  1

#define TSU_RQS_COMMON_CMPL_CREDIT_ENABLE_1_ADDR   0x00400103L
#define TSU_RQS_COMMON_CMPL_CREDIT_ENABLE_1_STRIDE 2
#define TSU_RQS_COMMON_CMPL_CREDIT_ENABLE_1_DEPTH  1

	/*
	 * Initial execution credit per TVL. This is private credit for the
	 * particular TVL and can only be used by this TVL. The credit indicates how
	 * many DMA contexts are reserved for this particular TVL
	 */
#define TSU_RQS_PRIVATE_EXEC_CREDIT_ADDR   0x00400200L
#define TSU_RQS_PRIVATE_EXEC_CREDIT_STRIDE 1
#define TSU_RQS_PRIVATE_EXEC_CREDIT_DEPTH  128

	/*
	 * Current execution credit used per TVL. This is credit used by a particular
	 * TVL. This register is updated by hardware and can be read by software.
	 */
#define TSU_RQS_TVL_EXEC_CREDIT_CONSUMED_ADDR   0x00400280L
#define TSU_RQS_TVL_EXEC_CREDIT_CONSUMED_STRIDE 1
#define TSU_RQS_TVL_EXEC_CREDIT_CONSUMED_DEPTH  128

	/*
	 * Initial execution credit for the free pool. The free pool can be used by
	 * anyone being set up to use common credits. This is additional credits
	 * which can be used in addition to the private TVL execution credit. The
	 * common execution credit indicates how many DMA contexts can be used by any
	 * TVL. It is a restriction that the TVL is set up to use common credit.
	 */
#define TSU_RQS_COMMON_EXEC_CREDIT_ADDR   0x00400300L
#define TSU_RQS_COMMON_EXEC_CREDIT_STRIDE 1
#define TSU_RQS_COMMON_EXEC_CREDIT_DEPTH  1

	/*
	 * This register contain the number of currently consumed common execution
	 * credits. The register is updated by hardware and can be read from
	 * software.
	 */
#define TSU_RQS_COMMON_EXEC_CREDIT_CONSUMED_ADDR   0x00400301L
#define TSU_RQS_COMMON_EXEC_CREDIT_CONSUMED_STRIDE 1
#define TSU_RQS_COMMON_EXEC_CREDIT_CONSUMED_DEPTH  1

#define TSU_RQS_COMMON_EXEC_CREDIT_ENABLE_0_ADDR   0x00400302L
#define TSU_RQS_COMMON_EXEC_CREDIT_ENABLE_0_STRIDE 2
#define TSU_RQS_COMMON_EXEC_CREDIT_ENABLE_0_DEPTH  1

#define TSU_RQS_COMMON_EXEC_CREDIT_ENABLE_1_ADDR   0x00400303L
#define TSU_RQS_COMMON_EXEC_CREDIT_ENABLE_1_STRIDE 2
#define TSU_RQS_COMMON_EXEC_CREDIT_ENABLE_1_DEPTH  1

	/*
	 * Port1 SL to VL mapping tables. One entry in this table is the SL to VL
	 * mapping table for one UF.
	 */
#define TSU_RQS_P1_SL2VL_ADDR   0x00400400L
#define TSU_RQS_P1_SL2VL_STRIDE 1
#define TSU_RQS_P1_SL2VL_DEPTH  34

	/*
	 * Port2 SL to VL mapping tables. There is one table per UF. The table is
	 * implemented as one register.
	 */
#define TSU_RQS_P2_SL2VL_ADDR   0x00400440L
#define TSU_RQS_P2_SL2VL_STRIDE 1
#define TSU_RQS_P2_SL2VL_DEPTH  34

	/*
	 * Jumbo frame enabled CSR. One register for the device indicating if jumbo
	 * frames are allowed or not.
	 */
#define TSU_RQS_JUMBO_FRAME_ENABLED_ADDR   0x00400600L
#define TSU_RQS_JUMBO_FRAME_ENABLED_STRIDE 1
#define TSU_RQS_JUMBO_FRAME_ENABLED_DEPTH  1

	/*
	 * Own LIDs base and LMC. Potentially all own LID bits come from the QP state
	 * entry. The number of bits to use is based on the LMC. Per UF register.
	 */
#define TSU_RQS_P1_OWN_LID_BASE_ADDR   0x00400800L
#define TSU_RQS_P1_OWN_LID_BASE_STRIDE 1
#define TSU_RQS_P1_OWN_LID_BASE_DEPTH  34

	/*
	 * Own LIDs base and LMC. Potentially all own LID bits come from the QP state
	 * entry. The number of bits to use is based on the LMC. Per UF register.
	 */
#define TSU_RQS_P2_OWN_LID_BASE_ADDR   0x00400840L
#define TSU_RQS_P2_OWN_LID_BASE_STRIDE 1
#define TSU_RQS_P2_OWN_LID_BASE_DEPTH  34

	/*
	 * Port1 enable bits per UF. If bit is set, the corresponding GID and LID
	 * table entries are valid.
	 */
#define TSU_RQS_P1_PORT_ENABLE_ADDR   0x00400880L
#define TSU_RQS_P1_PORT_ENABLE_STRIDE 1
#define TSU_RQS_P1_PORT_ENABLE_DEPTH  1

	/*
	 * Port2 enable bits per UF. If bit is set, the corresponding GID and LID
	 * table entries are valid.
	 */
#define TSU_RQS_P2_PORT_ENABLE_ADDR   0x00400881L
#define TSU_RQS_P2_PORT_ENABLE_STRIDE 1
#define TSU_RQS_P2_PORT_ENABLE_DEPTH  1

	/*
	 * Register with a bit per UF/VHCA indicating if the UF/VHCA is allowed to
	 * send SMPs.
	 */
#define TSU_RQS_P1_SMP_ALLOWED_ADDR   0x00400882L
#define TSU_RQS_P1_SMP_ALLOWED_STRIDE 1
#define TSU_RQS_P1_SMP_ALLOWED_DEPTH  1

	/*
	 * Register with a bit per UF/VHCA indicating if the UF/VHCA is allowed to
	 * send SMPs.
	 */
#define TSU_RQS_P2_SMP_ALLOWED_ADDR   0x00400883L
#define TSU_RQS_P2_SMP_ALLOWED_STRIDE 1
#define TSU_RQS_P2_SMP_ALLOWED_DEPTH  1

	/* Kick FIFO entries in use per UF */
#define TSU_RQS_KICK_FIFO_UF_INUSE_ADDR   0x00400884L
#define TSU_RQS_KICK_FIFO_UF_INUSE_STRIDE 1
#define TSU_RQS_KICK_FIFO_UF_INUSE_DEPTH  34

	/* Base Q-Key for EoIB range of Q-Keys. */
#define TSU_RQS_EOIB_QKEY_BASE_ADDR   0x004008c4L
#define TSU_RQS_EOIB_QKEY_BASE_STRIDE 1
#define TSU_RQS_EOIB_QKEY_BASE_DEPTH  1

	/* Mask Q-Key for EoIB range of Q-Keys. */
#define TSU_RQS_EOIB_QKEY_MASK_ADDR   0x004008c5L
#define TSU_RQS_EOIB_QKEY_MASK_STRIDE 1
#define TSU_RQS_EOIB_QKEY_MASK_DEPTH  1

	/* Q-Key used for IPoIB. */
#define TSU_RQS_IPOIB_QKEY_BASE_ADDR   0x004008c6L
#define TSU_RQS_IPOIB_QKEY_BASE_STRIDE 1
#define TSU_RQS_IPOIB_QKEY_BASE_DEPTH  1

	/* Range select register - defining the start bit for Q-Key (N+3:N). */
#define TSU_RQS_QKEY_RANGE_SELECT_ADDR   0x004008c7L
#define TSU_RQS_QKEY_RANGE_SELECT_STRIDE 1
#define TSU_RQS_QKEY_RANGE_SELECT_DEPTH  1

	/* Per UF EoIB enforcement definitions. */
#define TSU_RQS_EOIB_ENFORCEMENT_ALLOWED_ADDR   0x00400a00L
#define TSU_RQS_EOIB_ENFORCEMENT_ALLOWED_STRIDE 1
#define TSU_RQS_EOIB_ENFORCEMENT_ALLOWED_DEPTH  34

	/*
	 * 16 entries per UF. The table is addressed with {UF, index}. There are four
	 * entries per table entry. Because of a bug, each vNIC table entry could not
	 * be defined as a struct, but it could be cast to
	 * psif_verbs_pk::vnic_table_entry_t.
	 */
#define TSU_RQS_VNIC_TABLE_ADDR   0x00400c00L
#define TSU_RQS_VNIC_TABLE_STRIDE 1
#define TSU_RQS_VNIC_TABLE_DEPTH  136

	/*
	 * GID forwarding table. The forwarding table is used to figure out if a
	 * packet should be sent in loopback or not. There are (2 * NUM_VHCA + 1) 67
	 * GIDs per physical IB port.
	 */
#define TSU_RQS_P1_GID_FORWARDING_TABLE_ADDR   0x00402000L
#define TSU_RQS_P1_GID_FORWARDING_TABLE_STRIDE 1
#define TSU_RQS_P1_GID_FORWARDING_TABLE_DEPTH  67

	/*
	 * GID forwarding table. The forwarding table is used to figure out if a
	 * packet should be sent in loopback or not. There are (2 * NUM_VHCA + 1) 67
	 * GIDs per physical IB port.
	 */
#define TSU_RQS_P2_GID_FORWARDING_TABLE_ADDR   0x00402400L
#define TSU_RQS_P2_GID_FORWARDING_TABLE_STRIDE 1
#define TSU_RQS_P2_GID_FORWARDING_TABLE_DEPTH  67

	/*
	 * Per VL register (0-7: Port 0 VL0-7, 8: Port 0 VL15, 9: Port0 loopback.
	 * 10-19: Port 1). Maximum global buffer a particular VL can get.
	 */
#define TSU_DMA_MAX_ALLOC_VL_BUFF_ADDR   0x00500000L
#define TSU_DMA_MAX_ALLOC_VL_BUFF_STRIDE 1
#define TSU_DMA_MAX_ALLOC_VL_BUFF_DEPTH  20

	/*
	 * Per VL register (0-7: Port0 VL0-7, 8: Port0 VL15, 9: Port0 loopback.
	 * 10-19: Port 1). The amount of buffer dedicated to this VL.
	 */
#define TSU_DMA_PRIVATE_VL_BUFF_ADDR   0x00500020L
#define TSU_DMA_PRIVATE_VL_BUFF_STRIDE 1
#define TSU_DMA_PRIVATE_VL_BUFF_DEPTH  20

	/*
	 * Per VL register (0-7: Port0 VL0-7, 8: Port0 VL15, 9: Port0 loopback.
	 * 10-19: Port 1). The amount of dedicated and global buffer used to this VL.
	 */
#define TSU_DMA_VL_BUFF_USED_ADDR   0x00500040L
#define TSU_DMA_VL_BUFF_USED_STRIDE 1
#define TSU_DMA_VL_BUFF_USED_DEPTH  20

	/* Amount of global buffer used shared among all VLs. */
#define TSU_DMA_GLOBAL_BUFF_USED_ADDR   0x00500054L
#define TSU_DMA_GLOBAL_BUFF_USED_STRIDE 1
#define TSU_DMA_GLOBAL_BUFF_USED_DEPTH  1

	/* Num of 256B block DMA buffer check-out */
#define TSU_DMA_NUM_OF_BUF_CO_ADDR   0x00500055L
#define TSU_DMA_NUM_OF_BUF_CO_STRIDE 1
#define TSU_DMA_NUM_OF_BUF_CO_DEPTH  1

	/* Num of 256B block DMA buffer check-in */
#define TSU_DMA_NUM_OF_BUF_CI_ADDR   0x00500056L
#define TSU_DMA_NUM_OF_BUF_CI_STRIDE 1
#define TSU_DMA_NUM_OF_BUF_CI_DEPTH  1

	/* Number of RQS command to DMA */
#define TSU_DMA_NUM_OF_CNTXTLLQ_INBUN_ADDR   0x00500057L
#define TSU_DMA_NUM_OF_CNTXTLLQ_INBUN_STRIDE 1
#define TSU_DMA_NUM_OF_CNTXTLLQ_INBUN_DEPTH  1

	/* Number of Context LLQ pop */
#define TSU_DMA_NUM_OF_CNTXTLLQ_POP_ADDR   0x00500058L
#define TSU_DMA_NUM_OF_CNTXTLLQ_POP_STRIDE 1
#define TSU_DMA_NUM_OF_CNTXTLLQ_POP_DEPTH  1

	/* Number of Context LLQ ready to go set */
#define TSU_DMA_NUM_OF_CNTXTLLQ_R2G_ADDR   0x00500059L
#define TSU_DMA_NUM_OF_CNTXTLLQ_R2G_STRIDE 1
#define TSU_DMA_NUM_OF_CNTXTLLQ_R2G_DEPTH  1

	/* Number of IBPB command from DMA */
#define TSU_DMA_NUM_OF_IBPB_CMD_ADDR   0x0050005aL
#define TSU_DMA_NUM_OF_IBPB_CMD_STRIDE 1
#define TSU_DMA_NUM_OF_IBPB_CMD_DEPTH  1

	/* Number of CMPL command from DMA */
#define TSU_DMA_NUM_OF_CMPL_CMD_ADDR   0x0050005bL
#define TSU_DMA_NUM_OF_CMPL_CMD_STRIDE 1
#define TSU_DMA_NUM_OF_CMPL_CMD_DEPTH  1

	/* Number of QPS RD command from DMA */
#define TSU_DMA_NUM_OF_QPS_RD_CMD_ADDR   0x0050005cL
#define TSU_DMA_NUM_OF_QPS_RD_CMD_STRIDE 1
#define TSU_DMA_NUM_OF_QPS_RD_CMD_DEPTH  1

	/* Number of QPS RD response from QPS */
#define TSU_DMA_NUM_OF_QPS_RD_RSP_ADDR   0x0050005dL
#define TSU_DMA_NUM_OF_QPS_RD_RSP_STRIDE 1
#define TSU_DMA_NUM_OF_QPS_RD_RSP_DEPTH  1

	/* Number of QPS WR command from DMA */
#define TSU_DMA_NUM_OF_QPS_WR_CMD_ADDR   0x0050005eL
#define TSU_DMA_NUM_OF_QPS_WR_CMD_STRIDE 1
#define TSU_DMA_NUM_OF_QPS_WR_CMD_DEPTH  1

	/* Number of QPS WR response from QPS */
#define TSU_DMA_NUM_OF_QPS_WR_RSP_ADDR   0x0050005fL
#define TSU_DMA_NUM_OF_QPS_WR_RSP_STRIDE 1
#define TSU_DMA_NUM_OF_QPS_WR_RSP_DEPTH  1

	/* Number of packet in the packet LLQ */
#define TSU_DMA_NUM_OF_PKTLLQ_INBUN_ADDR   0x00500060L
#define TSU_DMA_NUM_OF_PKTLLQ_INBUN_STRIDE 1
#define TSU_DMA_NUM_OF_PKTLLQ_INBUN_DEPTH  1

	/* Number of Packet LLQ pop */
#define TSU_DMA_NUM_OF_PKTLLQ_POP_ADDR   0x00500061L
#define TSU_DMA_NUM_OF_PKTLLQ_POP_STRIDE 1
#define TSU_DMA_NUM_OF_PKTLLQ_POP_DEPTH  1

	/* Number of Packet LLQ ready to go set */
#define TSU_DMA_NUM_OF_PKTLLQ_R2G_ADDR   0x00500062L
#define TSU_DMA_NUM_OF_PKTLLQ_R2G_STRIDE 1
#define TSU_DMA_NUM_OF_PKTLLQ_R2G_DEPTH  1

	/* Num of payload DMA command */
#define TSU_DMA_NUM_OF_PYLD_CMD_ADDR   0x00500063L
#define TSU_DMA_NUM_OF_PYLD_CMD_STRIDE 1
#define TSU_DMA_NUM_OF_PYLD_CMD_DEPTH  1

	/* Num of payload DMA response */
#define TSU_DMA_NUM_OF_PYLD_RSP_ADDR   0x00500064L
#define TSU_DMA_NUM_OF_PYLD_RSP_STRIDE 1
#define TSU_DMA_NUM_OF_PYLD_RSP_DEPTH  1

	/* Num of sge DMA command */
#define TSU_DMA_NUM_OF_SGE_CMD_ADDR   0x00500065L
#define TSU_DMA_NUM_OF_SGE_CMD_STRIDE 1
#define TSU_DMA_NUM_OF_SGE_CMD_DEPTH  1

	/* Num of sge DMA response */
#define TSU_DMA_NUM_OF_SGE_RSP_ADDR   0x00500066L
#define TSU_DMA_NUM_OF_SGE_RSP_STRIDE 1
#define TSU_DMA_NUM_OF_SGE_RSP_DEPTH  1

	/* Num of LSO buffer used */
#define TSU_DMA_LSO_BUF_USED_ADDR   0x00500067L
#define TSU_DMA_LSO_BUF_USED_STRIDE 1
#define TSU_DMA_LSO_BUF_USED_DEPTH  1

	/* ECC error control */
#define TSU_DMA_ECC_ERR_CTRL_ADDR   0x00500068L
#define TSU_DMA_ECC_ERR_CTRL_STRIDE 1
#define TSU_DMA_ECC_ERR_CTRL_DEPTH  1

	/* ECC status */
#define TSU_DMA_ECC_ERR_STATUS_ADDR   0x00500069L
#define TSU_DMA_ECC_ERR_STATUS_STRIDE 1
#define TSU_DMA_ECC_ERR_STATUS_DEPTH  1

	/* ECC status */
#define TSU_DMA_ECC_ERR_STATUS_CLEAR_ADDR   0x0050006aL
#define TSU_DMA_ECC_ERR_STATUS_CLEAR_STRIDE 1
#define TSU_DMA_ECC_ERR_STATUS_CLEAR_DEPTH  1

	/* Num of 32B IB header size to be calculated in SR */
#define TSU_DMA_SR_IB_HEADER_SIZE_ADDR   0x0050006bL
#define TSU_DMA_SR_IB_HEADER_SIZE_STRIDE 1
#define TSU_DMA_SR_IB_HEADER_SIZE_DEPTH  1

	/*
	 * Timer scale for congestion control and static rate: 12 bits interval
	 * counter 8.192us, 18 bits wrap counter
	 */
#define TSU_DMA_TIMER_SCALE_ADDR   0x0050006cL
#define TSU_DMA_TIMER_SCALE_STRIDE 1
#define TSU_DMA_TIMER_SCALE_DEPTH  1

	/*
	 * IB link speed per port. 0=EDR, 1=QDR, 2=DDR, 3=SDR. 4=FDR Address to the
	 * Register Table: {uf, port}
	 */
#define TSU_DMA_LINK_SPEED_ADDR   0x00500080L
#define TSU_DMA_LINK_SPEED_STRIDE 1
#define TSU_DMA_LINK_SPEED_DEPTH  70

	/*
	 * IB link width per port. 0=X4 and 1=X1. Address to the Register Table: {uf,
	 * port}
	 */
#define TSU_DMA_LINK_WIDTH_ADDR   0x00500100L
#define TSU_DMA_LINK_WIDTH_STRIDE 1
#define TSU_DMA_LINK_WIDTH_DEPTH  70

	/*
	 * Maximum number of payload read 256B buffer per UF. Address to the Register
	 * Table:uf
	 */
#define TSU_DMA_UF_TRANS_MAX_ADDR   0x00500180L
#define TSU_DMA_UF_TRANS_MAX_STRIDE 1
#define TSU_DMA_UF_TRANS_MAX_DEPTH  35

	/* Number of payload read transaction per UF. Address to the Register Table:uf */
#define TSU_DMA_UF_TRANS_USED_ADDR   0x005001c0L
#define TSU_DMA_UF_TRANS_USED_STRIDE 1
#define TSU_DMA_UF_TRANS_USED_DEPTH  35

	/* MAC control per port per UF 0-33. Address to the Register Table: {uf port} */
#define TSU_DMA_MAC_CTRL_ADDR   0x00500600L
#define TSU_DMA_MAC_CTRL_STRIDE 1
#define TSU_DMA_MAC_CTRL_DEPTH  68

	/* Size of the EoIB and IPoIB header */
#define TSU_DMA_PPTY_HDR_LENGTH_ADDR   0x00500680L
#define TSU_DMA_PPTY_HDR_LENGTH_STRIDE 1
#define TSU_DMA_PPTY_HDR_LENGTH_DEPTH  1

	/* Mask bit to the TCP flags for the LSO segments */
#define TSU_DMA_TCP_FLAGS_MASK_ADDR   0x00500682L
#define TSU_DMA_TCP_FLAGS_MASK_STRIDE 1
#define TSU_DMA_TCP_FLAGS_MASK_DEPTH  1

	/* Control for ip checksum tcp checksum udp checksum and ethernet padding */
#define TSU_DMA_OFFLOAD_CTRL_ADDR   0x00500683L
#define TSU_DMA_OFFLOAD_CTRL_STRIDE 1
#define TSU_DMA_OFFLOAD_CTRL_DEPTH  1

	/* This register is defined as JUMBO MTU allowed to transmit when MTU_10240B */
#define TSU_DMA_JUMBO_MTU_ADDR   0x00500684L
#define TSU_DMA_JUMBO_MTU_STRIDE 1
#define TSU_DMA_JUMBO_MTU_DEPTH  1

	/*
	 * VLAN membership table per UF 0-33. Inputs/addressing to this table is {UF,
	 * vid[11:6}}.
	 */
#define TSU_DMA_VLAN_MEMBER_TABLE_ADDR   0x00501000L
#define TSU_DMA_VLAN_MEMBER_TABLE_STRIDE 1
#define TSU_DMA_VLAN_MEMBER_TABLE_DEPTH  2176

	/* Outer VLAN Ethernet type */
#define TSU_DMA_OUTER_VLAN_TYPE_ADDR   0x00502000L
#define TSU_DMA_OUTER_VLAN_TYPE_STRIDE 1
#define TSU_DMA_OUTER_VLAN_TYPE_DEPTH  34

	/* Outer VLAN Ethernet type */
#define TSU_DMA_INNER_VLAN_TYPE_ADDR   0x00502040L
#define TSU_DMA_INNER_VLAN_TYPE_STRIDE 1
#define TSU_DMA_INNER_VLAN_TYPE_DEPTH  34

	/*
	 * Q key enforcement VNIC VID table for uf 0-33. Inputs/addressing to this
	 * table are {UF, index}.
	 */
#define TSU_DMA_VNIC_VID_TABLE_ADDR   0x00502400L
#define TSU_DMA_VNIC_VID_TABLE_STRIDE 1
#define TSU_DMA_VNIC_VID_TABLE_DEPTH  544

	/*
	 * Q key enforcement MAC address for uf 0-33. Inputs/addressing to this table
	 * are {UF, index}.
	 */
#define TSU_DMA_VNIC_MAC_ADDR_TABLE_ADDR   0x00502800L
#define TSU_DMA_VNIC_MAC_ADDR_TABLE_STRIDE 1
#define TSU_DMA_VNIC_MAC_ADDR_TABLE_DEPTH  544

	/*
	 * Q key table - Inputs/addressing to this table are {UF, index}. There are
	 * 16 entries per UF.
	 */
#define TSU_DMA_QKEY_TABLE_ADDR   0x00502c00L
#define TSU_DMA_QKEY_TABLE_STRIDE 1
#define TSU_DMA_QKEY_TABLE_DEPTH  544

	/*
	 * Congestion control DLID CAM table. Inputs/addressing to this table are
	 * {port, CAM entry number}.
	 */
#define TSU_DMA_CC_DLID_TABLE_ADDR   0x00503000L
#define TSU_DMA_CC_DLID_TABLE_STRIDE 1
#define TSU_DMA_CC_DLID_TABLE_DEPTH  64

	/*
	 * Shared P-Key table for all UFs on this port. Number of entries valid per
	 * UF is defined by the p1_pkey_uf_stride register.
	 */
#define TSU_IBPB_P1_PKEY_TABLE_ADDR   0x00600000L
#define TSU_IBPB_P1_PKEY_TABLE_STRIDE 1
#define TSU_IBPB_P1_PKEY_TABLE_DEPTH  272

	/*
	 * Upper 64 bits of GID for port1. There are (2 * NUM_VHCA + 1) 67 GIDs per
	 * physical IB port.
	 */
#define TSU_IBPB_P1_GID_UPPER_ADDR   0x00600200L
#define TSU_IBPB_P1_GID_UPPER_STRIDE 1
#define TSU_IBPB_P1_GID_UPPER_DEPTH  67

	/*
	 * Lower 64 bits of GID for port1. There are (2 * NUM_VHCA + 1) 67 GIDs per
	 * physical IB port.
	 */
#define TSU_IBPB_P1_GID_LOWER_ADDR   0x00600300L
#define TSU_IBPB_P1_GID_LOWER_STRIDE 1
#define TSU_IBPB_P1_GID_LOWER_DEPTH  67

	/*
	 * Own LIDs base and LMC. Potentially all own LID bits come from the QP state
	 * entry. The number of bits to use is based on the LMC. Per UF register.
	 */
#define TSU_IBPB_P1_OWN_LID_BASE_ADDR   0x00600400L
#define TSU_IBPB_P1_OWN_LID_BASE_STRIDE 1
#define TSU_IBPB_P1_OWN_LID_BASE_DEPTH  34

	/*
	 * Size of individual P-Key tables per UF. All UFs have the same size or if
	 * set to 0, it means one common table.
	 */
#define TSU_IBPB_P1_PKEY_UF_STRIDE_ADDR   0x00600440L
#define TSU_IBPB_P1_PKEY_UF_STRIDE_STRIDE 1
#define TSU_IBPB_P1_PKEY_UF_STRIDE_DEPTH  1

	/*
	 * Shared P-Key table for all UFs on this port. Number of entries valid per
	 * UF is defined by the p2_pkey_uf_stride register.
	 */
#define TSU_IBPB_P2_PKEY_TABLE_ADDR   0x00600800L
#define TSU_IBPB_P2_PKEY_TABLE_STRIDE 1
#define TSU_IBPB_P2_PKEY_TABLE_DEPTH  272

	/*
	 * Upper 64 bits of GID for port2. There are (2 * NUM_VHCA + 1) 67 GIDs per
	 * physical IB port.
	 */
#define TSU_IBPB_P2_GID_UPPER_ADDR   0x00600a00L
#define TSU_IBPB_P2_GID_UPPER_STRIDE 1
#define TSU_IBPB_P2_GID_UPPER_DEPTH  67

	/* Lower 64 bits of GID for port2. The table is per UF. */
#define TSU_IBPB_P2_GID_LOWER_ADDR   0x00600b00L
#define TSU_IBPB_P2_GID_LOWER_STRIDE 1
#define TSU_IBPB_P2_GID_LOWER_DEPTH  67

	/*
	 * Own LIDs base and LMC. Potentially all own LID bits come from the QP state
	 * entry. The number of bits to use is based on the LMC. Per UF register.
	 */
#define TSU_IBPB_P2_OWN_LID_BASE_ADDR   0x00600c00L
#define TSU_IBPB_P2_OWN_LID_BASE_STRIDE 1
#define TSU_IBPB_P2_OWN_LID_BASE_DEPTH  34

	/*
	 * Size of individual P-Key tables per UF. All UFs have the same size or if
	 * set to 0, it means one common table.
	 */
#define TSU_IBPB_P2_PKEY_UF_STRIDE_ADDR   0x00600c40L
#define TSU_IBPB_P2_PKEY_UF_STRIDE_STRIDE 1
#define TSU_IBPB_P2_PKEY_UF_STRIDE_DEPTH  1

	/* Mask of fatal error stall input */
#define TSU_IBPB_MASK_CRB_IBPB_FATAL_ERR_STALL_ADDR   0x00600cc0L
#define TSU_IBPB_MASK_CRB_IBPB_FATAL_ERR_STALL_STRIDE 1
#define TSU_IBPB_MASK_CRB_IBPB_FATAL_ERR_STALL_DEPTH  1

	/* Misc IBPB debug signals */
#define TSU_IBPB_IBPB_DEBUG_ADDR   0x00600d40L
#define TSU_IBPB_IBPB_DEBUG_STRIDE 1
#define TSU_IBPB_IBPB_DEBUG_DEPTH  1

#define TSU_QPS_AHA_BASE_ADDR_0_ADDR   0x00700000L
#define TSU_QPS_AHA_BASE_ADDR_0_STRIDE 1
#define TSU_QPS_AHA_BASE_ADDR_0_DEPTH  34

#define TSU_QPS_AHA_BASE_ADDR_1_ADDR   0x00700040L
#define TSU_QPS_AHA_BASE_ADDR_1_STRIDE 1
#define TSU_QPS_AHA_BASE_ADDR_1_DEPTH  34

#define TSU_QPS_AHA_BASE_ADDR_2_ADDR   0x00700080L
#define TSU_QPS_AHA_BASE_ADDR_2_STRIDE 1
#define TSU_QPS_AHA_BASE_ADDR_2_DEPTH  34

#define TSU_QPS_QP_BASE_ADDR_0_ADDR   0x00700100L
#define TSU_QPS_QP_BASE_ADDR_0_STRIDE 1
#define TSU_QPS_QP_BASE_ADDR_0_DEPTH  34

#define TSU_QPS_QP_BASE_ADDR_1_ADDR   0x00700140L
#define TSU_QPS_QP_BASE_ADDR_1_STRIDE 1
#define TSU_QPS_QP_BASE_ADDR_1_DEPTH  34

#define TSU_QPS_QP_BASE_ADDR_2_ADDR   0x00700180L
#define TSU_QPS_QP_BASE_ADDR_2_STRIDE 1
#define TSU_QPS_QP_BASE_ADDR_2_DEPTH  34

	/*
	 * This register must be set and the kick register is written in order to
	 * start the UF invalidate operation.
	 */
#define TSU_QPS_UF_CONTROL_ADDR   0x00700200L
#define TSU_QPS_UF_CONTROL_STRIDE 1
#define TSU_QPS_UF_CONTROL_DEPTH  1

	/*
	 * Starts operation defined in uf_control. Now only UF invalidate is
	 * supported.
	 */
#define TSU_QPS_UF_CONTROL_KICK_ADDR   0x00700201L
#define TSU_QPS_UF_CONTROL_KICK_STRIDE 1
#define TSU_QPS_UF_CONTROL_KICK_DEPTH  1

	/*
	 * Bitvector indicating (one bit per UF) if a UF has entries in tsu_qps or
	 * not. This could be used to verify that a UF flush/invalidate has happened.
	 */
#define TSU_QPS_UF_EMPTY_ADDR   0x00700202L
#define TSU_QPS_UF_EMPTY_STRIDE 1
#define TSU_QPS_UF_EMPTY_DEPTH  1

	/* Interrupt status register. 1b per source (1 = int triggered). */
#define TSU_QPS_INT_STATUS_ADDR   0x00700203L
#define TSU_QPS_INT_STATUS_STRIDE 1
#define TSU_QPS_INT_STATUS_DEPTH  1

	/* Interrupt mask register. 1b per source (1 = masked). */
#define TSU_QPS_INT_MASK_ADDR   0x00700204L
#define TSU_QPS_INT_MASK_STRIDE 1
#define TSU_QPS_INT_MASK_DEPTH  1

	/* Interrupt priority register. 1b per source (1 = high 0 = low). */
#define TSU_QPS_INT_PRI_ADDR   0x00700205L
#define TSU_QPS_INT_PRI_STRIDE 1
#define TSU_QPS_INT_PRI_DEPTH  1

	/*
	 * Interrupt status clear register. 1b per source (1=source will be cleared
	 * from int_status register when kick is called).
	 */
#define TSU_QPS_INT_STATUS_CLEAR_ADDR   0x00700206L
#define TSU_QPS_INT_STATUS_CLEAR_STRIDE 1
#define TSU_QPS_INT_STATUS_CLEAR_DEPTH  1

	/* Trigger the int_status clear operation. */
#define TSU_QPS_INT_STATUS_CLEAR_KICK_ADDR   0x00700207L
#define TSU_QPS_INT_STATUS_CLEAR_KICK_STRIDE 1
#define TSU_QPS_INT_STATUS_CLEAR_KICK_DEPTH  1

	/*
	 * Stops timeout checking for UF in the uf_control register. This register
	 * must be kicked in order to make sure refcounts are not incremented for the
	 * UF to be flushed/invalidated.
	 */
#define TSU_QPS_UF_STOP_TIMEOUT_KICK_ADDR   0x00700240L
#define TSU_QPS_UF_STOP_TIMEOUT_KICK_STRIDE 1
#define TSU_QPS_UF_STOP_TIMEOUT_KICK_DEPTH  1

	/*
	 * Per UF modify/query QP command/attribute register. Only one register is
	 * implemented in hardware - one at a time. EPS implements one register per
	 * UF. When one is written, the modify data is written to modify_qp_data
	 * register before this register is written. The Modify or Query QP command
	 * is autmatically kicked when this register is written. Is one outstanding
	 * modify/query QP per UF ok, or do we need more?
	 */
#define TSU_QPS_MODIFY_QP_CTRL_ADDR   0x00700400L
#define TSU_QPS_MODIFY_QP_CTRL_STRIDE 1
#define TSU_QPS_MODIFY_QP_CTRL_DEPTH  1

#define TSU_QPS_MODIFY_QP_DATA_0_ADDR   0x00700440L
#define TSU_QPS_MODIFY_QP_DATA_0_STRIDE 10
#define TSU_QPS_MODIFY_QP_DATA_0_DEPTH  1

#define TSU_QPS_MODIFY_QP_DATA_1_ADDR   0x00700441L
#define TSU_QPS_MODIFY_QP_DATA_1_STRIDE 10
#define TSU_QPS_MODIFY_QP_DATA_1_DEPTH  1

#define TSU_QPS_MODIFY_QP_DATA_2_ADDR   0x00700442L
#define TSU_QPS_MODIFY_QP_DATA_2_STRIDE 10
#define TSU_QPS_MODIFY_QP_DATA_2_DEPTH  1

#define TSU_QPS_MODIFY_QP_DATA_3_ADDR   0x00700443L
#define TSU_QPS_MODIFY_QP_DATA_3_STRIDE 10
#define TSU_QPS_MODIFY_QP_DATA_3_DEPTH  1

#define TSU_QPS_MODIFY_QP_DATA_4_ADDR   0x00700444L
#define TSU_QPS_MODIFY_QP_DATA_4_STRIDE 10
#define TSU_QPS_MODIFY_QP_DATA_4_DEPTH  1

#define TSU_QPS_MODIFY_QP_DATA_5_ADDR   0x00700445L
#define TSU_QPS_MODIFY_QP_DATA_5_STRIDE 10
#define TSU_QPS_MODIFY_QP_DATA_5_DEPTH  1

#define TSU_QPS_MODIFY_QP_DATA_6_ADDR   0x00700446L
#define TSU_QPS_MODIFY_QP_DATA_6_STRIDE 10
#define TSU_QPS_MODIFY_QP_DATA_6_DEPTH  1

#define TSU_QPS_MODIFY_QP_DATA_7_ADDR   0x00700447L
#define TSU_QPS_MODIFY_QP_DATA_7_STRIDE 10
#define TSU_QPS_MODIFY_QP_DATA_7_DEPTH  1

#define TSU_QPS_MODIFY_QP_DATA_8_ADDR   0x00700448L
#define TSU_QPS_MODIFY_QP_DATA_8_STRIDE 10
#define TSU_QPS_MODIFY_QP_DATA_8_DEPTH  1

#define TSU_QPS_MODIFY_QP_DATA_9_ADDR   0x00700449L
#define TSU_QPS_MODIFY_QP_DATA_9_STRIDE 10
#define TSU_QPS_MODIFY_QP_DATA_9_DEPTH  1

	/*
	 * Kick register to start a new modify or query command. This register is
	 * written by EPS.
	 */
#define TSU_QPS_MODIFY_QP_KICK_ADDR   0x00700480L
#define TSU_QPS_MODIFY_QP_KICK_STRIDE 1
#define TSU_QPS_MODIFY_QP_KICK_DEPTH  1

	/*
	 * Status register indicating status of modify QP and query QP commands. This
	 * register is read by the EPS only.
	 */
#define TSU_QPS_MODIFY_QP_STATUS_ADDR   0x00700481L
#define TSU_QPS_MODIFY_QP_STATUS_STRIDE 1
#define TSU_QPS_MODIFY_QP_STATUS_DEPTH  1

	/*
	 * Data register containing data for the query QP command. This is read by
	 * the EPS only. The register is laid out to contain QP, primary_path and
	 * alternate path - same as it is in host memory. This is only a data bus,
	 * not using the structure psif_verbs_pkg::query_qp_t. When data is queried,
	 * and written to this register the psif_verbs_pkg::query_qp_t is cast to
	 * this structure. Please look at psif_verbs_pkg::query_qp_t for details.
	 */
#define TSU_QPS_QUERY_QP_DATA_ADDR   0x00700482L
#define TSU_QPS_QUERY_QP_DATA_STRIDE 1
#define TSU_QPS_QUERY_QP_DATA_DEPTH  24

	/*
	 * QP data register - see psif_verbs_pkg::qp_t for details on layout. This
	 * register contain the QP data information to write to QP index (HW cache
	 * index) given by the wr_qp_index CSR. This register is used to initialize
	 * QP 0/1, and is not accessible from user space. It could also be used for
	 * diagnostics.
	 */
#define TSU_QPS_WR_QP_DATA_ADDR   0x00700500L
#define TSU_QPS_WR_QP_DATA_STRIDE 1
#define TSU_QPS_WR_QP_DATA_DEPTH  16

	/*
	 * QP data register - see psif_verbs_pkg::path_info_t for details on layout.
	 * This register contain the path data to write to QP index (HW cache index)
	 * given by the wr_qp_index CSR. This register is used to initialize QP 0/1,
	 * and is not accessible from user space.
	 */
#define TSU_QPS_WR_QP_PATH_ADDR   0x00700514L
#define TSU_QPS_WR_QP_PATH_STRIDE 1
#define TSU_QPS_WR_QP_PATH_DEPTH  4

	/*
	 * QP index register. This register contain the QP index where the QP
	 * information is written to. This register is used to initialize QP 0/1, and
	 * is not accessible from user space. Set this to 0 for QP0 and 1 for QP1.
	 */
#define TSU_QPS_WR_QP_INDEX_ADDR   0x00700540L
#define TSU_QPS_WR_QP_INDEX_STRIDE 1
#define TSU_QPS_WR_QP_INDEX_DEPTH  1

	/*
	 * Kick register to start a new writing the QP information in wr_qp_data and
	 * wr_qp_path to QP index given in wr_qp_index CSR. This register is .
	 */
#define TSU_QPS_WR_QP_KICK_ADDR   0x00700541L
#define TSU_QPS_WR_QP_KICK_STRIDE 1
#define TSU_QPS_WR_QP_KICK_DEPTH  1

	/*
	 * DO NOT USE!! This register gives the option to change fields which can be
	 * changed in a QP modify command. It is not to be accessed by users, and is
	 * only here for flexibility. The register contain legal attribute masks for
	 * QP modification for state transition INIT to RTR.
	 */
#define TSU_QPS_MODIFY_ATTR_MASK_INIT_RTR_ADDR   0x00700800L
#define TSU_QPS_MODIFY_ATTR_MASK_INIT_RTR_STRIDE 1
#define TSU_QPS_MODIFY_ATTR_MASK_INIT_RTR_DEPTH  2

	/*
	 * DO NOT USE!! This register gives the option to change fields which can be
	 * changed in a QP modify command. It is not to be accessed by users, and is
	 * only here for flexibility. The register contain legal attribute masks for
	 * QP modification for state transition RTR to RTS.
	 */
#define TSU_QPS_MODIFY_ATTR_MASK_RTR_RTS_ADDR   0x00700802L
#define TSU_QPS_MODIFY_ATTR_MASK_RTR_RTS_STRIDE 1
#define TSU_QPS_MODIFY_ATTR_MASK_RTR_RTS_DEPTH  2

	/*
	 * DO NOT USE!! This register gives the option to change fields which can be
	 * changed in a QP modify command. It is not to be accessed by users, and is
	 * only here for flexibility. The register contain legal attribute masks for
	 * QP modification for state transition RTS to RTS.
	 */
#define TSU_QPS_MODIFY_ATTR_MASK_RTS_RTS_ADDR   0x00700804L
#define TSU_QPS_MODIFY_ATTR_MASK_RTS_RTS_STRIDE 1
#define TSU_QPS_MODIFY_ATTR_MASK_RTS_RTS_DEPTH  2

	/*
	 * DO NOT USE!! This register gives the option to change fields which can be
	 * changed in a QP modify command. It is not to be accessed by users, and is
	 * only here for flexibility. The register contain legal attribute masks for
	 * QP modification for state transition from any state to RESET or ERROR.
	 */
#define TSU_QPS_MODIFY_ATTR_MASK_ANY_ERR_RESET_ADDR   0x00700806L
#define TSU_QPS_MODIFY_ATTR_MASK_ANY_ERR_RESET_STRIDE 1
#define TSU_QPS_MODIFY_ATTR_MASK_ANY_ERR_RESET_DEPTH  2

	/*
	 * DO NOT USE!! This register gives the option to change fields which can be
	 * changed in a QP modify command. It is not to be accessed by users, and is
	 * only here for flexibility. Legal attribute masks for QP modification for
	 * state transition from SQERR to RTS.
	 */
#define TSU_QPS_MODIFY_ATTR_MASK_SQERR_RTS_ADDR   0x00700808L
#define TSU_QPS_MODIFY_ATTR_MASK_SQERR_RTS_STRIDE 1
#define TSU_QPS_MODIFY_ATTR_MASK_SQERR_RTS_DEPTH  2

	/*
	 * Status register indicating that the refcount hit zero after the qp_index
	 * was armed. There is one bit per QP index. This register is read by the EPS
	 * only.
	 */
#define TSU_QPS_REFCOUNT_ZERO_STATUS_ADDR   0x00701000L
#define TSU_QPS_REFCOUNT_ZERO_STATUS_STRIDE 1
#define TSU_QPS_REFCOUNT_ZERO_STATUS_DEPTH  32

	/* Mask CAM parity errors such that they do not cause FATAL errors. */
#define TSU_QPS_CAM_PAR_ERR_MASK_ADDR   0x00701020L
#define TSU_QPS_CAM_PAR_ERR_MASK_STRIDE 1
#define TSU_QPS_CAM_PAR_ERR_MASK_DEPTH  1

	/* Per UF refcount register. This is used for UF flushing. */
#define TSU_QPS_REF_COUNT_ADDR   0x00702000L
#define TSU_QPS_REF_COUNT_STRIDE 1
#define TSU_QPS_REF_COUNT_DEPTH  33

	/* Debug register for the modify block. */
#define TSU_QPS_MODIFY_QP_DEBUG_ADDR   0x00702040L
#define TSU_QPS_MODIFY_QP_DEBUG_STRIDE 1
#define TSU_QPS_MODIFY_QP_DEBUG_DEPTH  1

	/*
	 * Status register indicating that the refcount hit zero after the qp_index
	 * was armed. There is one bit per QP index. This register is read by the EPS
	 * only.
	 */
#define TSU_QPS_REFCOUNT_ZERO_STATUS_CLEAR_ADDR   0x00704000L
#define TSU_QPS_REFCOUNT_ZERO_STATUS_CLEAR_STRIDE 1
#define TSU_QPS_REFCOUNT_ZERO_STATUS_CLEAR_DEPTH  2048

	/*
	 * This register must be set and the kick register is written in order to
	 * start the operation.
	 */
#define TSU_CMPL_UF_CONTROL_ADDR   0x00800000L
#define TSU_CMPL_UF_CONTROL_STRIDE 1
#define TSU_CMPL_UF_CONTROL_DEPTH  1

	/* Starts operation defined in uf_control. */
#define TSU_CMPL_UF_CONTROL_KICK_ADDR   0x00800001L
#define TSU_CMPL_UF_CONTROL_KICK_STRIDE 1
#define TSU_CMPL_UF_CONTROL_KICK_DEPTH  1

	/* Interrupt status register. 1b per source (1 = int triggered). */
#define TSU_CMPL_INT_STATUS_ADDR   0x00800002L
#define TSU_CMPL_INT_STATUS_STRIDE 1
#define TSU_CMPL_INT_STATUS_DEPTH  1

	/* Interrupt mask register. 1b per source (1 = masked). */
#define TSU_CMPL_INT_MASK_ADDR   0x00800003L
#define TSU_CMPL_INT_MASK_STRIDE 1
#define TSU_CMPL_INT_MASK_DEPTH  1

	/* Interrupt priority register. 1b per source (1 = high 0 = low). */
#define TSU_CMPL_INT_PRI_ADDR   0x00800004L
#define TSU_CMPL_INT_PRI_STRIDE 1
#define TSU_CMPL_INT_PRI_DEPTH  1

	/*
	 * Interrupt status clear register. 1b per source (1=source will be cleared
	 * from int_status register when kick is called).
	 */
#define TSU_CMPL_INT_STATUS_CLEAR_ADDR   0x00800005L
#define TSU_CMPL_INT_STATUS_CLEAR_STRIDE 1
#define TSU_CMPL_INT_STATUS_CLEAR_DEPTH  1

	/* Trigger the int_status clear operation. */
#define TSU_CMPL_INT_STATUS_CLEAR_KICK_ADDR   0x00800006L
#define TSU_CMPL_INT_STATUS_CLEAR_KICK_STRIDE 1
#define TSU_CMPL_INT_STATUS_CLEAR_KICK_DEPTH  1

	/* CAM PERR detected status register. */
#define TSU_CMPL_PERR_STATUS_ADDR   0x00800007L
#define TSU_CMPL_PERR_STATUS_STRIDE 1
#define TSU_CMPL_PERR_STATUS_DEPTH  1

	/* Mask PERR interrupt. */
#define TSU_CMPL_PERR_MASK_ADDR   0x00800008L
#define TSU_CMPL_PERR_MASK_STRIDE 1
#define TSU_CMPL_PERR_MASK_DEPTH  1

	/* Mask packet stall on PERR interrupt. */
#define TSU_CMPL_PERR_STALL_MASK_ADDR   0x00800009L
#define TSU_CMPL_PERR_STALL_MASK_STRIDE 1
#define TSU_CMPL_PERR_STALL_MASK_DEPTH  1

	/* Spin set size used when handling max spin set response. */
#define TSU_CMPL_DEBUG_SPIN_SET_SIZE_ADDR   0x0080000aL
#define TSU_CMPL_DEBUG_SPIN_SET_SIZE_STRIDE 1
#define TSU_CMPL_DEBUG_SPIN_SET_SIZE_DEPTH  1

	/* UF QPN and MSN of max spin set response. */
#define TSU_CMPL_DEBUG_RESPONSE_INFO_ADDR   0x0080000bL
#define TSU_CMPL_DEBUG_RESPONSE_INFO_STRIDE 1
#define TSU_CMPL_DEBUG_RESPONSE_INFO_DEPTH  1

	/* Spin set mode (safe = 1 fast = 0). Default is fast mode. */
#define TSU_CMPL_SPIN_SET_CONTROL_ADDR   0x0080000cL
#define TSU_CMPL_SPIN_SET_CONTROL_STRIDE 1
#define TSU_CMPL_SPIN_SET_CONTROL_DEPTH  1

	/* Base address. */
#define TSU_CMPL_SQ_BASE_ADDR_0_ADDR   0x00800040L
#define TSU_CMPL_SQ_BASE_ADDR_0_STRIDE 1
#define TSU_CMPL_SQ_BASE_ADDR_0_DEPTH  34

	/* MMU context. */
#define TSU_CMPL_SQ_BASE_ADDR_1_ADDR   0x00800080L
#define TSU_CMPL_SQ_BASE_ADDR_1_STRIDE 1
#define TSU_CMPL_SQ_BASE_ADDR_1_DEPTH  34

	/* Num entries and extent. */
#define TSU_CMPL_SQ_BASE_ADDR_2_ADDR   0x008000c0L
#define TSU_CMPL_SQ_BASE_ADDR_2_STRIDE 1
#define TSU_CMPL_SQ_BASE_ADDR_2_DEPTH  34

#define TSU_VAL_KEY_BASE_ADDR_0_ADDR   0x00900000L
#define TSU_VAL_KEY_BASE_ADDR_0_STRIDE 1
#define TSU_VAL_KEY_BASE_ADDR_0_DEPTH  34

#define TSU_VAL_KEY_BASE_ADDR_1_ADDR   0x00900040L
#define TSU_VAL_KEY_BASE_ADDR_1_STRIDE 1
#define TSU_VAL_KEY_BASE_ADDR_1_DEPTH  34

#define TSU_VAL_KEY_BASE_ADDR_2_ADDR   0x00900080L
#define TSU_VAL_KEY_BASE_ADDR_2_STRIDE 1
#define TSU_VAL_KEY_BASE_ADDR_2_DEPTH  34

	/*
	 * This register must be set and the kick register is written in order to
	 * start the operation.
	 */
#define TSU_VAL_UF_CONTROL_ADDR   0x00900100L
#define TSU_VAL_UF_CONTROL_STRIDE 1
#define TSU_VAL_UF_CONTROL_DEPTH  1

	/* Starts operation defined in uf_control. */
#define TSU_VAL_UF_CONTROL_KICK_ADDR   0x00900101L
#define TSU_VAL_UF_CONTROL_KICK_STRIDE 1
#define TSU_VAL_UF_CONTROL_KICK_DEPTH  1

	/* Interrupt status register. 1b per source (1 = int triggered). */
#define TSU_VAL_INT_STATUS_ADDR   0x00900102L
#define TSU_VAL_INT_STATUS_STRIDE 1
#define TSU_VAL_INT_STATUS_DEPTH  1

	/* Interrupt mask register. 1b per source (1 = masked). */
#define TSU_VAL_INT_MASK_ADDR   0x00900103L
#define TSU_VAL_INT_MASK_STRIDE 1
#define TSU_VAL_INT_MASK_DEPTH  1

	/* Interrupt priority register. 1b per source (1 = high 0 = low). */
#define TSU_VAL_INT_PRI_ADDR   0x00900104L
#define TSU_VAL_INT_PRI_STRIDE 1
#define TSU_VAL_INT_PRI_DEPTH  1

	/*
	 * Interrupt status clear register. 1b per source (1=source will be cleared
	 * from int_status register when kick is called).
	 */
#define TSU_VAL_INT_STATUS_CLEAR_ADDR   0x00900105L
#define TSU_VAL_INT_STATUS_CLEAR_STRIDE 1
#define TSU_VAL_INT_STATUS_CLEAR_DEPTH  1

	/* Trigger the int_status clear operation. */
#define TSU_VAL_INT_STATUS_CLEAR_KICK_ADDR   0x00900106L
#define TSU_VAL_INT_STATUS_CLEAR_KICK_STRIDE 1
#define TSU_VAL_INT_STATUS_CLEAR_KICK_DEPTH  1

	/*
	 * This register must be set and the kick register is written in order to
	 * start the operation.
	 */
#define TSU_RQH_UF_CONTROL_ADDR   0x00a00000L
#define TSU_RQH_UF_CONTROL_STRIDE 1
#define TSU_RQH_UF_CONTROL_DEPTH  1

	/* Starts operation defined in uf_control. */
#define TSU_RQH_UF_CONTROL_KICK_ADDR   0x00a00001L
#define TSU_RQH_UF_CONTROL_KICK_STRIDE 1
#define TSU_RQH_UF_CONTROL_KICK_DEPTH  1

	/* Interrupt status register. 1b per source (1 = int triggered). */
#define TSU_RQH_INT_STATUS_ADDR   0x00a00002L
#define TSU_RQH_INT_STATUS_STRIDE 1
#define TSU_RQH_INT_STATUS_DEPTH  1

	/* Interrupt mask register. 1b per source (1 = masked). */
#define TSU_RQH_INT_MASK_ADDR   0x00a00003L
#define TSU_RQH_INT_MASK_STRIDE 1
#define TSU_RQH_INT_MASK_DEPTH  1

	/* Interrupt priority register. 1b per source (1 = high 0 = low). */
#define TSU_RQH_INT_PRI_ADDR   0x00a00004L
#define TSU_RQH_INT_PRI_STRIDE 1
#define TSU_RQH_INT_PRI_DEPTH  1

	/*
	 * Interrupt status clear register. 1b per source (1=source will be cleared
	 * from int_status register when kick is called).
	 */
#define TSU_RQH_INT_STATUS_CLEAR_ADDR   0x00a00005L
#define TSU_RQH_INT_STATUS_CLEAR_STRIDE 1
#define TSU_RQH_INT_STATUS_CLEAR_DEPTH  1

	/* Trigger the int_status clear operation. */
#define TSU_RQH_INT_STATUS_CLEAR_KICK_ADDR   0x00a00006L
#define TSU_RQH_INT_STATUS_CLEAR_KICK_STRIDE 1
#define TSU_RQH_INT_STATUS_CLEAR_KICK_DEPTH  1

#define TSU_RQH_QP_BASE_ADDR_0_ADDR   0x00a00080L
#define TSU_RQH_QP_BASE_ADDR_0_STRIDE 1
#define TSU_RQH_QP_BASE_ADDR_0_DEPTH  34

#define TSU_RQH_QP_BASE_ADDR_1_ADDR   0x00a000c0L
#define TSU_RQH_QP_BASE_ADDR_1_STRIDE 1
#define TSU_RQH_QP_BASE_ADDR_1_DEPTH  34

#define TSU_RQH_QP_BASE_ADDR_2_ADDR   0x00a00100L
#define TSU_RQH_QP_BASE_ADDR_2_STRIDE 1
#define TSU_RQH_QP_BASE_ADDR_2_DEPTH  34

	/*
	 * Base address registers per UF for software owned descriptor portion of
	 * receive queue descriptors.
	 */
#define TSU_DSCR_RQ_BASE_ADDR_SW_0_ADDR   0x00b00300L
#define TSU_DSCR_RQ_BASE_ADDR_SW_0_STRIDE 1
#define TSU_DSCR_RQ_BASE_ADDR_SW_0_DEPTH  34

#define TSU_DSCR_RQ_BASE_ADDR_SW_1_ADDR   0x00b00340L
#define TSU_DSCR_RQ_BASE_ADDR_SW_1_STRIDE 1
#define TSU_DSCR_RQ_BASE_ADDR_SW_1_DEPTH  34

#define TSU_DSCR_RQ_BASE_ADDR_SW_2_ADDR   0x00b00380L
#define TSU_DSCR_RQ_BASE_ADDR_SW_2_STRIDE 1
#define TSU_DSCR_RQ_BASE_ADDR_SW_2_DEPTH  34

	/*
	 * Base address registers per UF for hardware owned descriptor portion of
	 * receive queue descriptors.
	 */
#define TSU_DSCR_RQ_BASE_ADDR_HW_0_ADDR   0x00b003c0L
#define TSU_DSCR_RQ_BASE_ADDR_HW_0_STRIDE 1
#define TSU_DSCR_RQ_BASE_ADDR_HW_0_DEPTH  34

#define TSU_DSCR_RQ_BASE_ADDR_HW_1_ADDR   0x00b00400L
#define TSU_DSCR_RQ_BASE_ADDR_HW_1_STRIDE 1
#define TSU_DSCR_RQ_BASE_ADDR_HW_1_DEPTH  34

#define TSU_DSCR_RQ_BASE_ADDR_HW_2_ADDR   0x00b00440L
#define TSU_DSCR_RQ_BASE_ADDR_HW_2_STRIDE 1
#define TSU_DSCR_RQ_BASE_ADDR_HW_2_DEPTH  34

	/*
	 * This register must be set and the kick register is written in order to
	 * start the operation.
	 */
#define TSU_DSCR_UF_CONTROL_ADDR   0x00b00700L
#define TSU_DSCR_UF_CONTROL_STRIDE 1
#define TSU_DSCR_UF_CONTROL_DEPTH  1

	/* Starts operation defined in uf_control. */
#define TSU_DSCR_UF_CONTROL_KICK_ADDR   0x00b00701L
#define TSU_DSCR_UF_CONTROL_KICK_STRIDE 1
#define TSU_DSCR_UF_CONTROL_KICK_DEPTH  1

	/* Interrupt status register. 1b per source (1 = int triggered). */
#define TSU_DSCR_INT_STATUS_ADDR   0x00b00702L
#define TSU_DSCR_INT_STATUS_STRIDE 1
#define TSU_DSCR_INT_STATUS_DEPTH  1

	/* Interrupt mask register. 1b per source (1 = masked). */
#define TSU_DSCR_INT_MASK_ADDR   0x00b00703L
#define TSU_DSCR_INT_MASK_STRIDE 1
#define TSU_DSCR_INT_MASK_DEPTH  1

	/* Interrupt priority register. 1b per source (1 = high 0 = low). */
#define TSU_DSCR_INT_PRI_ADDR   0x00b00704L
#define TSU_DSCR_INT_PRI_STRIDE 1
#define TSU_DSCR_INT_PRI_DEPTH  1

	/*
	 * Interrupt status clear register. 1b per source (1=source will be cleared
	 * from int_status register when kick is called).
	 */
#define TSU_DSCR_INT_STATUS_CLEAR_ADDR   0x00b00705L
#define TSU_DSCR_INT_STATUS_CLEAR_STRIDE 1
#define TSU_DSCR_INT_STATUS_CLEAR_DEPTH  1

	/* Trigger the int_status clear operation. */
#define TSU_DSCR_INT_STATUS_CLEAR_KICK_ADDR   0x00b00706L
#define TSU_DSCR_INT_STATUS_CLEAR_KICK_STRIDE 1
#define TSU_DSCR_INT_STATUS_CLEAR_KICK_DEPTH  1

	/* Various diagnostic control bits */
#define TSU_DSCR_DIAGNOSTIC_ADDR   0x00b00800L
#define TSU_DSCR_DIAGNOSTIC_STRIDE 1
#define TSU_DSCR_DIAGNOSTIC_DEPTH  1

	/* Fatal interrupt bits */
#define TSU_DSCR_FATAL_INTERRUPT_ADDR   0x00b01000L
#define TSU_DSCR_FATAL_INTERRUPT_STRIDE 1
#define TSU_DSCR_FATAL_INTERRUPT_DEPTH  1

	/* RSS table containing CQ and RQ. This table is used for EoIB RSS. */
#define TSU_RCV_RSS_EOIB_TABLE_ADDR   0x00c00000L
#define TSU_RCV_RSS_EOIB_TABLE_STRIDE 1
#define TSU_RCV_RSS_EOIB_TABLE_DEPTH  128

	/*
	 * Control register for RSS per vHCA (UF0-UF32). Containing the bit masks to
	 * use when masking hashes.
	 */
#define TSU_RCV_RSS_CTRL_EOIB_TABLE_ADDR   0x00c00080L
#define TSU_RCV_RSS_CTRL_EOIB_TABLE_STRIDE 1
#define TSU_RCV_RSS_CTRL_EOIB_TABLE_DEPTH  33

	/* RSS table containing CQ and RQ. This table is used for IPoIB RSS. */
#define TSU_RCV_RSS_IPOIB_TABLE_ADDR   0x00c00100L
#define TSU_RCV_RSS_IPOIB_TABLE_STRIDE 1
#define TSU_RCV_RSS_IPOIB_TABLE_DEPTH  128

	/*
	 * Control register for RSS per vHCA (UF0-UF32). Containing the bit masks to
	 * use when masking hashes.
	 */
#define TSU_RCV_RSS_CTRL_IPOIB_TABLE_ADDR   0x00c00180L
#define TSU_RCV_RSS_CTRL_IPOIB_TABLE_STRIDE 1
#define TSU_RCV_RSS_CTRL_IPOIB_TABLE_DEPTH  33

	/*
	 * Control register for EPS-A offloading per vHCA (UF0-UF32). It is
	 * containing the size which is the limit for sending packets to EPS-A.
	 */
#define TSU_RCV_PROXY_SIZE_ADDR   0x00c00200L
#define TSU_RCV_PROXY_SIZE_STRIDE 1
#define TSU_RCV_PROXY_SIZE_DEPTH  33

	/* Maximum MAD packet size supported. */
#define TSU_RCV_MAD_SIZE_ADDR   0x00c00300L
#define TSU_RCV_MAD_SIZE_STRIDE 1
#define TSU_RCV_MAD_SIZE_DEPTH  1

	/*
	 * One bit per vHCA indicating if the vHCA is allowed to use proxy mode.
	 */
#define TSU_RCV_PROXY_ALLOWED_ADDR   0x00c00301L
#define TSU_RCV_PROXY_ALLOWED_STRIDE 1
#define TSU_RCV_PROXY_ALLOWED_DEPTH  1

	/*
	 * Error counter for multicast rejects. There is one register per vHCA port.
	 */
#define TSU_RCV_EOIB_MCAST_REJECT_ADDR   0x00c02000L
#define TSU_RCV_EOIB_MCAST_REJECT_STRIDE 1
#define TSU_RCV_EOIB_MCAST_REJECT_DEPTH  68

	/*
	 * Error counter for broadcast rejects. There is one register per vHCA port.
	 */
#define TSU_RCV_EOIB_BCAST_REJECT_ADDR   0x00c02080L
#define TSU_RCV_EOIB_BCAST_REJECT_STRIDE 1
#define TSU_RCV_EOIB_BCAST_REJECT_DEPTH  68

	/*
	 * Error counter for unicast rejects. There is one register per vHCA port.
	 */
#define TSU_RCV_EOIB_UCAST_REJECT_ADDR   0x00c02100L
#define TSU_RCV_EOIB_UCAST_REJECT_STRIDE 1
#define TSU_RCV_EOIB_UCAST_REJECT_DEPTH  68

	/*
	 * Error counter for rejects. There is one register per vHCA port.
	 */
#define TSU_RCV_EOIB_TCP_PORT_VIOLATION_REJECT_ADDR   0x00c02180L
#define TSU_RCV_EOIB_TCP_PORT_VIOLATION_REJECT_STRIDE 1
#define TSU_RCV_EOIB_TCP_PORT_VIOLATION_REJECT_DEPTH  68

	/*
	 * Error counter for runt rejects. There is one register per vHCA port.
	 */
#define TSU_RCV_EOIB_RUNTS_REJECT_ADDR   0x00c02200L
#define TSU_RCV_EOIB_RUNTS_REJECT_STRIDE 1
#define TSU_RCV_EOIB_RUNTS_REJECT_DEPTH  68

	/*
	 * Error counter for outer VLAN rejects. There is one register per vHCA port.
	 */
#define TSU_RCV_EOIB_OUTER_VLAN_REJECT_ADDR   0x00c02280L
#define TSU_RCV_EOIB_OUTER_VLAN_REJECT_STRIDE 1
#define TSU_RCV_EOIB_OUTER_VLAN_REJECT_DEPTH  68

	/*
	 * Error counter for VLAN tag rejects. There is one register per vHCA port.
	 */
#define TSU_RCV_EOIB_VLAN_TAG_REJECT_ADDR   0x00c02300L
#define TSU_RCV_EOIB_VLAN_TAG_REJECT_STRIDE 1
#define TSU_RCV_EOIB_VLAN_TAG_REJECT_DEPTH  68

	/*
	 * Error counter for VID rejects. There is one register per vHCA port.
	 */
#define TSU_RCV_EOIB_VID_REJECT_ADDR   0x00c02380L
#define TSU_RCV_EOIB_VID_REJECT_STRIDE 1
#define TSU_RCV_EOIB_VID_REJECT_DEPTH  68

	/*
	 * Error counter for TCP port filtering violation rejects. There is one
	 * register per vHCA port.
	 */
#define TSU_RCV_IPOIB_TCP_PORT_VIOLATION_REJECT_ADDR   0x00c02400L
#define TSU_RCV_IPOIB_TCP_PORT_VIOLATION_REJECT_STRIDE 1
#define TSU_RCV_IPOIB_TCP_PORT_VIOLATION_REJECT_DEPTH  68

	/*
	 * Control if multicast packets should be forwarded to yourself or not when
	 * the QP is a IPoIB or EoIB QP.
	 */
#define TSU_RCV_NO_MCAST_DUPLICATION_ADDR   0x00c02800L
#define TSU_RCV_NO_MCAST_DUPLICATION_STRIDE 1
#define TSU_RCV_NO_MCAST_DUPLICATION_DEPTH  1

	/* Trap register for P-Key and Q-Key traps. */
#define TSU_RCV_KEY_TRAP_SGID_UPPER_ADDR   0x00c04000L
#define TSU_RCV_KEY_TRAP_SGID_UPPER_STRIDE 1
#define TSU_RCV_KEY_TRAP_SGID_UPPER_DEPTH  1

	/* Trap register for P-Key and Q-Key traps. */
#define TSU_RCV_KEY_TRAP_SGID_LOWER_ADDR   0x00c04001L
#define TSU_RCV_KEY_TRAP_SGID_LOWER_STRIDE 1
#define TSU_RCV_KEY_TRAP_SGID_LOWER_DEPTH  1

	/* Trap register for P-Key and Q-Key traps. */
#define TSU_RCV_KEY_TRAP_DGID_UPPER_ADDR   0x00c04002L
#define TSU_RCV_KEY_TRAP_DGID_UPPER_STRIDE 1
#define TSU_RCV_KEY_TRAP_DGID_UPPER_DEPTH  1

	/* Trap register for P-Key and Q-Key traps. */
#define TSU_RCV_KEY_TRAP_DGID_LOWER_ADDR   0x00c04003L
#define TSU_RCV_KEY_TRAP_DGID_LOWER_STRIDE 1
#define TSU_RCV_KEY_TRAP_DGID_LOWER_DEPTH  1

	/* Trap register for P-Key and Q-Key traps. */
#define TSU_RCV_KEY_TRAP_QP_ADDR   0x00c04004L
#define TSU_RCV_KEY_TRAP_QP_STRIDE 1
#define TSU_RCV_KEY_TRAP_QP_DEPTH  1

	/* Trap register for P-Key and Q-Key traps. */
#define TSU_RCV_KEY_TRAP_LID_KEY_ADDR   0x00c04005L
#define TSU_RCV_KEY_TRAP_LID_KEY_STRIDE 1
#define TSU_RCV_KEY_TRAP_LID_KEY_DEPTH  1

	/* Pop register for P-Key and Q-Key trap FIFO. */
#define TSU_RCV_KEY_TRAP_POP_ADDR   0x00c04008L
#define TSU_RCV_KEY_TRAP_POP_STRIDE 1
#define TSU_RCV_KEY_TRAP_POP_DEPTH  1

	/* Register indicating what to do if the trap FIFO is full. */
#define TSU_RCV_KEY_TRAP_BACKPRESSURE_ADDR   0x00c04010L
#define TSU_RCV_KEY_TRAP_BACKPRESSURE_STRIDE 1
#define TSU_RCV_KEY_TRAP_BACKPRESSURE_DEPTH  1

	/* Interrupt status register. 1b per source (1 = int triggered). */
#define TSU_RCV_INT_STATUS_ADDR   0x00c04400L
#define TSU_RCV_INT_STATUS_STRIDE 1
#define TSU_RCV_INT_STATUS_DEPTH  1

	/* Interrupt mask register. 1b per source (1 = masked). */
#define TSU_RCV_INT_MASK_ADDR   0x00c04401L
#define TSU_RCV_INT_MASK_STRIDE 1
#define TSU_RCV_INT_MASK_DEPTH  1

	/* Interrupt priority register. 1b per source (1 = high 0 = low). */
#define TSU_RCV_INT_PRI_ADDR   0x00c04402L
#define TSU_RCV_INT_PRI_STRIDE 1
#define TSU_RCV_INT_PRI_DEPTH  1

	/*
	 * Interrupt status clear register. 1b per source (1=source will be cleared
	 * from int_status register when kick is called).
	 */
#define TSU_RCV_INT_STATUS_CLEAR_ADDR   0x00c04403L
#define TSU_RCV_INT_STATUS_CLEAR_STRIDE 1
#define TSU_RCV_INT_STATUS_CLEAR_DEPTH  1

	/* Trigger the int_status clear operation. */
#define TSU_RCV_INT_STATUS_CLEAR_KICK_ADDR   0x00c04404L
#define TSU_RCV_INT_STATUS_CLEAR_KICK_STRIDE 1
#define TSU_RCV_INT_STATUS_CLEAR_KICK_DEPTH  1

	/*
	 * 64 bits of IPv4/IPv6 address. This register is fed by a FIFO feeding into
	 * int_status. Clearing the interrupt status will pop the FIFO.
	 */
#define TSU_RCV_PORT_FILTER_IP_SOURCE_ADDR   0x00c04800L
#define TSU_RCV_PORT_FILTER_IP_SOURCE_STRIDE 1
#define TSU_RCV_PORT_FILTER_IP_SOURCE_DEPTH  1

	/*
	 * TCP destination port and SLID. This register is fed by a FIFO feeding into
	 * int_status. Clearing the interrupt status will pop the FIFO.
	 */
#define TSU_RCV_PORT_FILTER_SLID_PORT_ADDR   0x00c04801L
#define TSU_RCV_PORT_FILTER_SLID_PORT_STRIDE 1
#define TSU_RCV_PORT_FILTER_SLID_PORT_DEPTH  1

	/* Decide if the debug FIFO should be used or not. */
#define TSU_RCV_PORT_FILTER_USE_FIFO_ADDR   0x00c04802L
#define TSU_RCV_PORT_FILTER_USE_FIFO_STRIDE 1
#define TSU_RCV_PORT_FILTER_USE_FIFO_DEPTH  1

	/* Pop register for port filter debug FIFO. */
#define TSU_RCV_PORT_FILTER_POP_ADDR   0x00c04803L
#define TSU_RCV_PORT_FILTER_POP_STRIDE 1
#define TSU_RCV_PORT_FILTER_POP_DEPTH  1

	/*
	 * Shared P-Key table for all UFs on this port. Number of entries valid per
	 * UF is defined by the p1_pkey_uf_stride register.
	 */
#define TSU_IBPR_P1_PKEY_TABLE_ADDR   0x00d00000L
#define TSU_IBPR_P1_PKEY_TABLE_STRIDE 1
#define TSU_IBPR_P1_PKEY_TABLE_DEPTH  272

	/*
	 * Size of individual P-Key tables per UF. All UFs have the same size or if
	 * set to 0, it means one common table.
	 */
#define TSU_IBPR_P1_PKEY_UF_STRIDE_ADDR   0x00d00200L
#define TSU_IBPR_P1_PKEY_UF_STRIDE_STRIDE 1
#define TSU_IBPR_P1_PKEY_UF_STRIDE_DEPTH  1

	/* Permission and entry table for TCP port filtering. */
#define TSU_IBPR_P1_TCP_PERMISSION_TABLE_ADDR   0x00d00400L
#define TSU_IBPR_P1_TCP_PERMISSION_TABLE_STRIDE 1
#define TSU_IBPR_P1_TCP_PERMISSION_TABLE_DEPTH  272

	/* Range table for the TCP Port filtering. */
#define TSU_IBPR_P1_TCP_PORT_RANGE_TABLE_ADDR   0x00d00600L
#define TSU_IBPR_P1_TCP_PORT_RANGE_TABLE_STRIDE 1
#define TSU_IBPR_P1_TCP_PORT_RANGE_TABLE_DEPTH  32

	/*
	 * Own LIDs base and LMC. Potentially all own LID bits come from the QP state
	 * entry. The number of bits to use is based on the LMC. Per UF register.
	 */
#define TSU_IBPR_P1_OWN_LID_BASE_ADDR   0x00d00800L
#define TSU_IBPR_P1_OWN_LID_BASE_STRIDE 1
#define TSU_IBPR_P1_OWN_LID_BASE_DEPTH  34

	/*
	 * Upper 64 bits of GID for port1. There are (2 * NUM_VHCA + 1) 67 GIDs per
	 * physical IB port.
	 */
#define TSU_IBPR_P1_GID_UPPER_ADDR   0x00d00880L
#define TSU_IBPR_P1_GID_UPPER_STRIDE 1
#define TSU_IBPR_P1_GID_UPPER_DEPTH  67

	/*
	 * Lower 64 bits of GID for port1. There are (2 * NUM_VHCA + 1) 67 GIDs per
	 * physical IB port.
	 */
#define TSU_IBPR_P1_GID_LOWER_ADDR   0x00d00900L
#define TSU_IBPR_P1_GID_LOWER_STRIDE 1
#define TSU_IBPR_P1_GID_LOWER_DEPTH  67

	/*
	 * GID forwarding table. The forwarding table is used to figure out if a
	 * packet should be sent in loopback or not. There are (2 * NUM_VHCA + 1) 67
	 * GIDs per physical IB port.
	 */
#define TSU_IBPR_P1_GID_FORWARDING_TABLE_ADDR   0x00d00980L
#define TSU_IBPR_P1_GID_FORWARDING_TABLE_STRIDE 1
#define TSU_IBPR_P1_GID_FORWARDING_TABLE_DEPTH  67

	/*
	 * One bit ber UF. If set for the UF, the upper 64bits are ignored in the
	 * DGID check.
	 */
#define TSU_IBPR_P1_IGNORE_UPPER_64B_DGID_CHECK_ADDR   0x00d00a00L
#define TSU_IBPR_P1_IGNORE_UPPER_64B_DGID_CHECK_STRIDE 1
#define TSU_IBPR_P1_IGNORE_UPPER_64B_DGID_CHECK_DEPTH  1

	/* Default vSwitch port for vSwitch1. */
#define TSU_IBPR_P1_DEFAULT_VSWITCH_PORT_ADDR   0x00d00a80L
#define TSU_IBPR_P1_DEFAULT_VSWITCH_PORT_STRIDE 1
#define TSU_IBPR_P1_DEFAULT_VSWITCH_PORT_DEPTH  1

	/* Default SM HCA. Indicating which vHCA to send SM packets to. */
#define TSU_IBPR_P1_DEFAULT_SM_HCA_ADDR   0x00d00b00L
#define TSU_IBPR_P1_DEFAULT_SM_HCA_STRIDE 1
#define TSU_IBPR_P1_DEFAULT_SM_HCA_DEPTH  1

	/*
	 * When a bit is set, the TSU will forward the particular management class to
	 * EPS-C. Per UF0-UF32.
	 */
#define TSU_IBPR_P1_GSI_FORWARDING_TABLE_ADDR   0x00d00b80L
#define TSU_IBPR_P1_GSI_FORWARDING_TABLE_STRIDE 1
#define TSU_IBPR_P1_GSI_FORWARDING_TABLE_DEPTH  33

	/*
	 * Register with a bit per UF/VHCA indicating if the UF/VHCA is allowed to
	 * send SMPs.
	 */
#define TSU_IBPR_P1_SMP_ALLOWED_ADDR   0x00d01000L
#define TSU_IBPR_P1_SMP_ALLOWED_STRIDE 1
#define TSU_IBPR_P1_SMP_ALLOWED_DEPTH  1

	/*
	 * Status register with a bit per UF/VHCA indicating if an UF/VHCA SMP not
	 * allowed packet drop status is cleared.
	 */
#define TSU_IBPR_P1_SMP_ALLOWED_DROP_STATUS_CLEAR_ADDR   0x00d01080L
#define TSU_IBPR_P1_SMP_ALLOWED_DROP_STATUS_CLEAR_STRIDE 1
#define TSU_IBPR_P1_SMP_ALLOWED_DROP_STATUS_CLEAR_DEPTH  1

	/*
	 * Status register with a bit per UF/VHCA indicating if an UF/VHCA SMP not
	 * allowed packet is dropped.
	 */
#define TSU_IBPR_P1_SMP_ALLOWED_DROP_STATUS_ADDR   0x00d01100L
#define TSU_IBPR_P1_SMP_ALLOWED_DROP_STATUS_STRIDE 1
#define TSU_IBPR_P1_SMP_ALLOWED_DROP_STATUS_DEPTH  1

	/* Rx choke register */
#define TSU_IBPR_P1_RX_CHOKE_ADDR   0x00d01180L
#define TSU_IBPR_P1_RX_CHOKE_STRIDE 1
#define TSU_IBPR_P1_RX_CHOKE_DEPTH  1

	/*
	 * Get vlink state for the vHCA and the vSwitch. It is up to the firmware to
	 * report correct physical link states when one side is set to disabled and
	 * the other side is down.
	 */
#define TSU_IBPR_P1_VLINK_STATE_ADDR   0x00d01200L
#define TSU_IBPR_P1_VLINK_STATE_STRIDE 1
#define TSU_IBPR_P1_VLINK_STATE_DEPTH  33

	/*
	 * When data is present, this register should be read for processing.
	 * Hardware multicast FIFO is popped when p1_mcast_pop is written.
	 */
#define TSU_IBPR_P1_MCAST_GID_UPPER_ADDR   0x00d01800L
#define TSU_IBPR_P1_MCAST_GID_UPPER_STRIDE 1
#define TSU_IBPR_P1_MCAST_GID_UPPER_DEPTH  1

	/*
	 * When data is present, this register should be read for processing.
	 * Hardware multicast FIFO is popped when p1_mcast_pop is written.
	 */
#define TSU_IBPR_P1_MCAST_GID_LOWER_ADDR   0x00d01802L
#define TSU_IBPR_P1_MCAST_GID_LOWER_STRIDE 1
#define TSU_IBPR_P1_MCAST_GID_LOWER_DEPTH  1

	/*
	 * When data is present, this register should be read for processing.
	 * Hardware multicast FIFO is popped when p1_mcast_pop is written.
	 */
#define TSU_IBPR_P1_MCAST_GIDHASH_LID_ADDR   0x00d01804L
#define TSU_IBPR_P1_MCAST_GIDHASH_LID_STRIDE 1
#define TSU_IBPR_P1_MCAST_GIDHASH_LID_DEPTH  1

	/*
	 * This pop register is written after data in p1_mcast_gid_upper,
	 * p1_mcast_gid_lower and p1_mcast_lid is read. Writing this register will
	 * pop the FIFO.
	 */
#define TSU_IBPR_P1_MCAST_POP_ADDR   0x00d01806L
#define TSU_IBPR_P1_MCAST_POP_STRIDE 1
#define TSU_IBPR_P1_MCAST_POP_DEPTH  1

	/*
	 * This registers indicate how many multicast packets this port can hold
	 * before starting drop packets.
	 */
#define TSU_IBPR_P1_MCAST_MAX_PKTS_ADDR   0x00d01808L
#define TSU_IBPR_P1_MCAST_MAX_PKTS_STRIDE 1
#define TSU_IBPR_P1_MCAST_MAX_PKTS_DEPTH  1

	/*
	 * This register contain the credit for writing to the CSR FIFO for multicast
	 * packets.
	 */
#define TSU_IBPR_P1_MCAST_WR_CREDIT_ADDR   0x00d0180aL
#define TSU_IBPR_P1_MCAST_WR_CREDIT_STRIDE 1
#define TSU_IBPR_P1_MCAST_WR_CREDIT_DEPTH  1

	/* Write to multicast FIFO. */
#define TSU_IBPR_P1_MCAST_WR_FIFO_ADDR   0x00d0180cL
#define TSU_IBPR_P1_MCAST_WR_FIFO_STRIDE 1
#define TSU_IBPR_P1_MCAST_WR_FIFO_DEPTH  1

	/* Kick multicast FIFO - data is valid in the multicast FIFO. */
#define TSU_IBPR_P1_MCAST_WR_FIFO_KICK_ADDR   0x00d0180eL
#define TSU_IBPR_P1_MCAST_WR_FIFO_KICK_STRIDE 1
#define TSU_IBPR_P1_MCAST_WR_FIFO_KICK_DEPTH  1

	/* Congestion DLID cam */
#define TSU_IBPR_P1_CONG_CAM_ADDR   0x00d02000L
#define TSU_IBPR_P1_CONG_CAM_STRIDE 1
#define TSU_IBPR_P1_CONG_CAM_DEPTH  32

	/* Congestion Control Table Index */
#define TSU_IBPR_P1_CONG_CCTI_ADDR   0x00d02080L
#define TSU_IBPR_P1_CONG_CCTI_STRIDE 1
#define TSU_IBPR_P1_CONG_CCTI_DEPTH  32

	/* Congestion Control Table */
#define TSU_IBPR_P1_CONG_CCT_ADDR   0x00d02100L
#define TSU_IBPR_P1_CONG_CCT_STRIDE 1
#define TSU_IBPR_P1_CONG_CCT_DEPTH  128

	/* Congestion Control Table Index data */
#define TSU_IBPR_P1_CONG_CCTI_DATA_ADDR   0x00d02180L
#define TSU_IBPR_P1_CONG_CCTI_DATA_STRIDE 1
#define TSU_IBPR_P1_CONG_CCTI_DATA_DEPTH  32

	/*
	 * This pop register is written after data in p1 congestion log is read.
	 * Writing this register will pop the FIFO.
	 */
#define TSU_IBPR_P1_CONGESTION_LOG_POP_ADDR   0x00d02200L
#define TSU_IBPR_P1_CONGESTION_LOG_POP_STRIDE 1
#define TSU_IBPR_P1_CONGESTION_LOG_POP_DEPTH  1

	/* When this bit is set congestion log update from HW is enabled */
#define TSU_IBPR_P1_CONGESTION_LOG_ENABLE_ADDR   0x00d02280L
#define TSU_IBPR_P1_CONGESTION_LOG_ENABLE_STRIDE 1
#define TSU_IBPR_P1_CONGESTION_LOG_ENABLE_DEPTH  1

	/*
	 * When data is present, this register contains congestion log. Hardware
	 * multicast FIFO is popped when p1_congestion_log_pop is written.
	 */
#define TSU_IBPR_P1_CONGESTION_LOG_ADDR   0x00d02300L
#define TSU_IBPR_P1_CONGESTION_LOG_STRIDE 1
#define TSU_IBPR_P1_CONGESTION_LOG_DEPTH  1

	/* Sample interval register. */
#define TSU_IBPR_VSWITCH1_SAMPLE_INTERVAL_ADDR   0x00d02800L
#define TSU_IBPR_VSWITCH1_SAMPLE_INTERVAL_STRIDE 1
#define TSU_IBPR_VSWITCH1_SAMPLE_INTERVAL_DEPTH  1

	/* Sample start delay register. */
#define TSU_IBPR_VSWITCH1_SAMPLE_START_ADDR   0x00d02802L
#define TSU_IBPR_VSWITCH1_SAMPLE_START_STRIDE 1
#define TSU_IBPR_VSWITCH1_SAMPLE_START_DEPTH  1

	/* Sample count register. This register contain the counted values. */
#define TSU_IBPR_VSWITCH1_SAMPLE_COUNT_ADDR   0x00d02804L
#define TSU_IBPR_VSWITCH1_SAMPLE_COUNT_STRIDE 1
#define TSU_IBPR_VSWITCH1_SAMPLE_COUNT_DEPTH  1

	/*
	 * Sample UF register. Indicating which port this entry is counting for and
	 * what type it is counting.
	 */
#define TSU_IBPR_VSWITCH1_SAMPLE_PORT_ADDR   0x00d02806L
#define TSU_IBPR_VSWITCH1_SAMPLE_PORT_STRIDE 1
#define TSU_IBPR_VSWITCH1_SAMPLE_PORT_DEPTH  1

	/* Start port Sampling. */
#define TSU_IBPR_VSWITCH1_PORTSAMPLE_START_ADDR   0x00d02808L
#define TSU_IBPR_VSWITCH1_PORTSAMPLE_START_STRIDE 1
#define TSU_IBPR_VSWITCH1_PORTSAMPLE_START_DEPTH  1

	/* Sample status register. */
#define TSU_IBPR_VSWITCH1_SAMPLE_STATUS_ADDR   0x00d0280aL
#define TSU_IBPR_VSWITCH1_SAMPLE_STATUS_STRIDE 1
#define TSU_IBPR_VSWITCH1_SAMPLE_STATUS_DEPTH  1

	/* Sample interval register. */
#define TSU_IBPR_VHCA_P1_SAMPLE_INTERVAL_ADDR   0x00d02880L
#define TSU_IBPR_VHCA_P1_SAMPLE_INTERVAL_STRIDE 1
#define TSU_IBPR_VHCA_P1_SAMPLE_INTERVAL_DEPTH  1

	/* Sample start delay register. */
#define TSU_IBPR_VHCA_P1_SAMPLE_START_ADDR   0x00d02882L
#define TSU_IBPR_VHCA_P1_SAMPLE_START_STRIDE 1
#define TSU_IBPR_VHCA_P1_SAMPLE_START_DEPTH  1

	/* Sample count register. This register contain the counted values. */
#define TSU_IBPR_VHCA_P1_SAMPLE_COUNT_ADDR   0x00d02884L
#define TSU_IBPR_VHCA_P1_SAMPLE_COUNT_STRIDE 1
#define TSU_IBPR_VHCA_P1_SAMPLE_COUNT_DEPTH  1

	/*
	 * Sample UF register. Indicating which port this entry is counting for and
	 * what type it is counting.
	 */
#define TSU_IBPR_VHCA_P1_SAMPLE_PORT_ADDR   0x00d02886L
#define TSU_IBPR_VHCA_P1_SAMPLE_PORT_STRIDE 1
#define TSU_IBPR_VHCA_P1_SAMPLE_PORT_DEPTH  1

	/* Start port Sampling. */
#define TSU_IBPR_VHCA_P1_PORTSAMPLE_START_ADDR   0x00d02888L
#define TSU_IBPR_VHCA_P1_PORTSAMPLE_START_STRIDE 1
#define TSU_IBPR_VHCA_P1_PORTSAMPLE_START_DEPTH  1

	/* Sample status register. */
#define TSU_IBPR_VHCA_P1_SAMPLE_STATUS_ADDR   0x00d0288aL
#define TSU_IBPR_VHCA_P1_SAMPLE_STATUS_STRIDE 1
#define TSU_IBPR_VHCA_P1_SAMPLE_STATUS_DEPTH  1

	/* Port counter PortXmitDiscards. This is per vSwitch port [32:0]. */
#define TSU_IBPR_VSWITCH1_XMIT_DISCARDS_ADDR   0x00d02900L
#define TSU_IBPR_VSWITCH1_XMIT_DISCARDS_STRIDE 1
#define TSU_IBPR_VSWITCH1_XMIT_DISCARDS_DEPTH  33

	/* Port counter PortRcvSwitchRelayErrors. This is per Switch */
#define TSU_IBPR_VSWITCH1_RCV_SWITCH_RELAY_ERRORS_ADDR   0x00d02980L
#define TSU_IBPR_VSWITCH1_RCV_SWITCH_RELAY_ERRORS_STRIDE 1
#define TSU_IBPR_VSWITCH1_RCV_SWITCH_RELAY_ERRORS_DEPTH  1

	/* Vendor Port counter receive packets drop. This is per vSwitch. */
#define TSU_IBPR_VSWITCH1_RCV_PKTS_DROP_ADDR   0x00d02982L
#define TSU_IBPR_VSWITCH1_RCV_PKTS_DROP_STRIDE 1
#define TSU_IBPR_VSWITCH1_RCV_PKTS_DROP_DEPTH  1

	/* Clear portcounter port receive drop */
#define TSU_IBPR_VSWITCH1_PORTCOUNTER_PRCVDROP_CLEAR_ADDR   0x00d02984L
#define TSU_IBPR_VSWITCH1_PORTCOUNTER_PRCVDROP_CLEAR_STRIDE 1
#define TSU_IBPR_VSWITCH1_PORTCOUNTER_PRCVDROP_CLEAR_DEPTH  1

	/* Clear portcounter Port Receive Switch Relay Error */
#define TSU_IBPR_VSWITCH1_PORTCOUNTER_PRSRE_CLEAR_ADDR   0x00d02986L
#define TSU_IBPR_VSWITCH1_PORTCOUNTER_PRSRE_CLEAR_STRIDE 1
#define TSU_IBPR_VSWITCH1_PORTCOUNTER_PRSRE_CLEAR_DEPTH  1

	/* Port counter PortXmitDiscards. This is per vSwitch port. */
#define TSU_IBPR_VHCA_P1_XMIT_DISCARDS_ADDR   0x00d02a00L
#define TSU_IBPR_VHCA_P1_XMIT_DISCARDS_STRIDE 1
#define TSU_IBPR_VHCA_P1_XMIT_DISCARDS_DEPTH  33

	/*
	 * Port counter Port Receive data. This is per vSwitch port - not the
	 * external port.
	 */
#define TSU_IBPR_VHCA_P1_RCV_DATA_ADDR   0x00d02a80L
#define TSU_IBPR_VHCA_P1_RCV_DATA_STRIDE 1
#define TSU_IBPR_VHCA_P1_RCV_DATA_DEPTH  34

	/*
	 * Port counter Port Receive Packets. This is per vSwitch port - not the
	 * external port.
	 */
#define TSU_IBPR_VHCA_P1_RCV_PKTS_ADDR   0x00d02b00L
#define TSU_IBPR_VHCA_P1_RCV_PKTS_STRIDE 1
#define TSU_IBPR_VHCA_P1_RCV_PKTS_DEPTH  34

	/*
	 * Port counter Port Xmit data. This is per vSwitch port - not the external
	 * port.
	 */
#define TSU_IBPR_VHCA_P1_XMIT_DATA_ADDR   0x00d02b80L
#define TSU_IBPR_VHCA_P1_XMIT_DATA_STRIDE 1
#define TSU_IBPR_VHCA_P1_XMIT_DATA_DEPTH  34

	/*
	 * Port counter Port Xmit Packets. This is per vSwitch port - not the
	 * external port.
	 */
#define TSU_IBPR_VHCA_P1_XMIT_PKTS_ADDR   0x00d02c00L
#define TSU_IBPR_VHCA_P1_XMIT_PKTS_STRIDE 1
#define TSU_IBPR_VHCA_P1_XMIT_PKTS_DEPTH  34

	/*
	 * Port counter counting packets dropped (marked p_error) in Xmit path.
	 */
#define TSU_IBPR_VHCA_P1_XMIT_PKTS_DROP_ADDR   0x00d02c80L
#define TSU_IBPR_VHCA_P1_XMIT_PKTS_DROP_STRIDE 1
#define TSU_IBPR_VHCA_P1_XMIT_PKTS_DROP_DEPTH  1

	/* Clear portcounter Port Xmit Drop. */
#define TSU_IBPR_VHCA_P1_PORTCOUNTER_PXDROP_CLEAR_ADDR   0x00d02c82L
#define TSU_IBPR_VHCA_P1_PORTCOUNTER_PXDROP_CLEAR_STRIDE 1
#define TSU_IBPR_VHCA_P1_PORTCOUNTER_PXDROP_CLEAR_DEPTH  1

	/*
	 * Shared P-Key table for all UFs on this port. Number of entries valid per
	 * UF is defined by the p2_pkey_uf_stride register.
	 */
#define TSU_IBPR_P2_PKEY_TABLE_ADDR   0x00d08000L
#define TSU_IBPR_P2_PKEY_TABLE_STRIDE 1
#define TSU_IBPR_P2_PKEY_TABLE_DEPTH  272

	/*
	 * Size of individual P-Key tables per UF. All UFs have the same size or if
	 * set to 0, it means one common table.
	 */
#define TSU_IBPR_P2_PKEY_UF_STRIDE_ADDR   0x00d08200L
#define TSU_IBPR_P2_PKEY_UF_STRIDE_STRIDE 1
#define TSU_IBPR_P2_PKEY_UF_STRIDE_DEPTH  1

	/* Permission and entry table for TCP port filtering. */
#define TSU_IBPR_P2_TCP_PERMISSION_TABLE_ADDR   0x00d08400L
#define TSU_IBPR_P2_TCP_PERMISSION_TABLE_STRIDE 1
#define TSU_IBPR_P2_TCP_PERMISSION_TABLE_DEPTH  272

	/* Range table for the TCP Port filtering. */
#define TSU_IBPR_P2_TCP_PORT_RANGE_TABLE_ADDR   0x00d08600L
#define TSU_IBPR_P2_TCP_PORT_RANGE_TABLE_STRIDE 1
#define TSU_IBPR_P2_TCP_PORT_RANGE_TABLE_DEPTH  32

	/*
	 * Own LIDs base and LMC. Potentially all own LID bits come from the QP state
	 * entry. The number of bits to use is based on the LMC. Per UF register.
	 */
#define TSU_IBPR_P2_OWN_LID_BASE_ADDR   0x00d08800L
#define TSU_IBPR_P2_OWN_LID_BASE_STRIDE 1
#define TSU_IBPR_P2_OWN_LID_BASE_DEPTH  34

	/*
	 * Upper 64 bits of GID for port2. There are (2 * NUM_VHCA + 1) 67 GIDs per
	 * physical IB port.
	 */
#define TSU_IBPR_P2_GID_UPPER_ADDR   0x00d08880L
#define TSU_IBPR_P2_GID_UPPER_STRIDE 1
#define TSU_IBPR_P2_GID_UPPER_DEPTH  67

	/*
	 * Lower 64 bits of GID for port2. There are (2 * NUM_VHCA + 1) 67 GIDs per
	 * physical IB port.
	 */
#define TSU_IBPR_P2_GID_LOWER_ADDR   0x00d08900L
#define TSU_IBPR_P2_GID_LOWER_STRIDE 1
#define TSU_IBPR_P2_GID_LOWER_DEPTH  67

	/*
	 * GID forwarding table. The forwarding table is used to figure out if a
	 * packet should be sent in loopback or not. There are (2 * NUM_VHCA + 1) 67
	 * GIDs per physical IB port.
	 */
#define TSU_IBPR_P2_GID_FORWARDING_TABLE_ADDR   0x00d08980L
#define TSU_IBPR_P2_GID_FORWARDING_TABLE_STRIDE 1
#define TSU_IBPR_P2_GID_FORWARDING_TABLE_DEPTH  67

	/*
	 * One bit ber UF. If set for the UF, the upper 64bits are ignored in the
	 * DGID check.
	 */
#define TSU_IBPR_P2_IGNORE_UPPER_64B_DGID_CHECK_ADDR   0x00d08a00L
#define TSU_IBPR_P2_IGNORE_UPPER_64B_DGID_CHECK_STRIDE 1
#define TSU_IBPR_P2_IGNORE_UPPER_64B_DGID_CHECK_DEPTH  1

	/* Default vSwitch port for vSwitch2. */
#define TSU_IBPR_P2_DEFAULT_VSWITCH_PORT_ADDR   0x00d08a80L
#define TSU_IBPR_P2_DEFAULT_VSWITCH_PORT_STRIDE 1
#define TSU_IBPR_P2_DEFAULT_VSWITCH_PORT_DEPTH  1

	/* Default SM HCA. Indicating which vHCA to send SM packets to. */
#define TSU_IBPR_P2_DEFAULT_SM_HCA_ADDR   0x00d08b00L
#define TSU_IBPR_P2_DEFAULT_SM_HCA_STRIDE 1
#define TSU_IBPR_P2_DEFAULT_SM_HCA_DEPTH  1

	/*
	 * When a bit is set, the TSU will forward the particular management class to
	 * EPS-C. Per UF0-UF32.
	 */
#define TSU_IBPR_P2_GSI_FORWARDING_TABLE_ADDR   0x00d08b80L
#define TSU_IBPR_P2_GSI_FORWARDING_TABLE_STRIDE 1
#define TSU_IBPR_P2_GSI_FORWARDING_TABLE_DEPTH  33

	/*
	 * Register with a bit per UF/VHCA indicating if the UF/VHCA is allowed to
	 * send SMPs.
	 */
#define TSU_IBPR_P2_SMP_ALLOWED_ADDR   0x00d09000L
#define TSU_IBPR_P2_SMP_ALLOWED_STRIDE 1
#define TSU_IBPR_P2_SMP_ALLOWED_DEPTH  1

	/*
	 * Status register with a bit per UF/VHCA indicating if an UF/VHCA SMP not
	 * allowed packet drop status is cleared.
	 */
#define TSU_IBPR_P2_SMP_ALLOWED_DROP_STATUS_CLEAR_ADDR   0x00d09080L
#define TSU_IBPR_P2_SMP_ALLOWED_DROP_STATUS_CLEAR_STRIDE 1
#define TSU_IBPR_P2_SMP_ALLOWED_DROP_STATUS_CLEAR_DEPTH  1

	/*
	 * Status register with a bit per UF/VHCA indicating if an UF/VHCA SMP not
	 * allowed packet is dropped.
	 */
#define TSU_IBPR_P2_SMP_ALLOWED_DROP_STATUS_ADDR   0x00d09100L
#define TSU_IBPR_P2_SMP_ALLOWED_DROP_STATUS_STRIDE 1
#define TSU_IBPR_P2_SMP_ALLOWED_DROP_STATUS_DEPTH  1

	/* Rx choke register */
#define TSU_IBPR_P2_RX_CHOKE_ADDR   0x00d09180L
#define TSU_IBPR_P2_RX_CHOKE_STRIDE 1
#define TSU_IBPR_P2_RX_CHOKE_DEPTH  1

	/*
	 * Get vlink state for the vHCA and the vSwitch. It is up to the firmware to
	 * report correct physical link states when one side is set to disabled and
	 * the other side is down.
	 */
#define TSU_IBPR_P2_VLINK_STATE_ADDR   0x00d09200L
#define TSU_IBPR_P2_VLINK_STATE_STRIDE 1
#define TSU_IBPR_P2_VLINK_STATE_DEPTH  33

	/*
	 * When data is present, this register should be read for processing.
	 * Hardware multicast FIFO is popped when p2_mcast_pop is written.
	 */
#define TSU_IBPR_P2_MCAST_GID_UPPER_ADDR   0x00d09800L
#define TSU_IBPR_P2_MCAST_GID_UPPER_STRIDE 1
#define TSU_IBPR_P2_MCAST_GID_UPPER_DEPTH  1

	/*
	 * When data is present, this register should be read for processing.
	 * Hardware multicast FIFO is popped when p2_mcast_pop is written.
	 */
#define TSU_IBPR_P2_MCAST_GID_LOWER_ADDR   0x00d09802L
#define TSU_IBPR_P2_MCAST_GID_LOWER_STRIDE 1
#define TSU_IBPR_P2_MCAST_GID_LOWER_DEPTH  1

	/*
	 * When data is present, this register should be read for processing.
	 * Hardware multicast FIFO is popped when p2_mcast_pop is written.
	 */
#define TSU_IBPR_P2_MCAST_GIDHASH_LID_ADDR   0x00d09804L
#define TSU_IBPR_P2_MCAST_GIDHASH_LID_STRIDE 1
#define TSU_IBPR_P2_MCAST_GIDHASH_LID_DEPTH  1

	/*
	 * This pop register is written after data in p2_mcast_gid_upper,
	 * p2_mcast_gid_lower and p2_mcast_lid is read. Writing this register will
	 * pop the FIFO.
	 */
#define TSU_IBPR_P2_MCAST_POP_ADDR   0x00d09806L
#define TSU_IBPR_P2_MCAST_POP_STRIDE 1
#define TSU_IBPR_P2_MCAST_POP_DEPTH  1

	/*
	 * This registers indicate how many multicast packets this port can hold
	 * before starting drop packets.
	 */
#define TSU_IBPR_P2_MCAST_MAX_PKTS_ADDR   0x00d09808L
#define TSU_IBPR_P2_MCAST_MAX_PKTS_STRIDE 1
#define TSU_IBPR_P2_MCAST_MAX_PKTS_DEPTH  1

	/*
	 * This register contain the credit for writing to the CSR FIFO for multicast
	 * packets.
	 */
#define TSU_IBPR_P2_MCAST_WR_CREDIT_ADDR   0x00d0980aL
#define TSU_IBPR_P2_MCAST_WR_CREDIT_STRIDE 1
#define TSU_IBPR_P2_MCAST_WR_CREDIT_DEPTH  1

	/* Write to multicast FIFO. */
#define TSU_IBPR_P2_MCAST_WR_FIFO_ADDR   0x00d0980cL
#define TSU_IBPR_P2_MCAST_WR_FIFO_STRIDE 1
#define TSU_IBPR_P2_MCAST_WR_FIFO_DEPTH  1

	/* Kick multicast FIFO - data is valid in the multicast FIFO. */
#define TSU_IBPR_P2_MCAST_WR_FIFO_KICK_ADDR   0x00d0980eL
#define TSU_IBPR_P2_MCAST_WR_FIFO_KICK_STRIDE 1
#define TSU_IBPR_P2_MCAST_WR_FIFO_KICK_DEPTH  1

	/* Congestion DLID cam */
#define TSU_IBPR_P2_CONG_CAM_ADDR   0x00d0a000L
#define TSU_IBPR_P2_CONG_CAM_STRIDE 1
#define TSU_IBPR_P2_CONG_CAM_DEPTH  32

	/* Congestion Control Table Index */
#define TSU_IBPR_P2_CONG_CCTI_ADDR   0x00d0a080L
#define TSU_IBPR_P2_CONG_CCTI_STRIDE 1
#define TSU_IBPR_P2_CONG_CCTI_DEPTH  32

	/* Congestion Control Table */
#define TSU_IBPR_P2_CONG_CCT_ADDR   0x00d0a100L
#define TSU_IBPR_P2_CONG_CCT_STRIDE 1
#define TSU_IBPR_P2_CONG_CCT_DEPTH  128

	/* Congestion Control Table Index data */
#define TSU_IBPR_P2_CONG_CCTI_DATA_ADDR   0x00d0a180L
#define TSU_IBPR_P2_CONG_CCTI_DATA_STRIDE 1
#define TSU_IBPR_P2_CONG_CCTI_DATA_DEPTH  32

	/*
	 * This pop register is written after data in p2 congestion log is read.
	 * Writing this register will pop the FIFO.
	 */
#define TSU_IBPR_P2_CONGESTION_LOG_POP_ADDR   0x00d0a200L
#define TSU_IBPR_P2_CONGESTION_LOG_POP_STRIDE 1
#define TSU_IBPR_P2_CONGESTION_LOG_POP_DEPTH  1

	/* When this bit is set congestion log update from HW is enabled */
#define TSU_IBPR_P2_CONGESTION_LOG_ENABLE_ADDR   0x00d0a280L
#define TSU_IBPR_P2_CONGESTION_LOG_ENABLE_STRIDE 1
#define TSU_IBPR_P2_CONGESTION_LOG_ENABLE_DEPTH  1

	/*
	 * When data is present, this register contains congestion log. Hardware
	 * multicast FIFO is popped when p2_congestion_log_pop is written.
	 */
#define TSU_IBPR_P2_CONGESTION_LOG_ADDR   0x00d0a300L
#define TSU_IBPR_P2_CONGESTION_LOG_STRIDE 1
#define TSU_IBPR_P2_CONGESTION_LOG_DEPTH  1

	/* Sample interval register. */
#define TSU_IBPR_VSWITCH2_SAMPLE_INTERVAL_ADDR   0x00d0a800L
#define TSU_IBPR_VSWITCH2_SAMPLE_INTERVAL_STRIDE 1
#define TSU_IBPR_VSWITCH2_SAMPLE_INTERVAL_DEPTH  1

	/* Sample start delay register. */
#define TSU_IBPR_VSWITCH2_SAMPLE_START_ADDR   0x00d0a802L
#define TSU_IBPR_VSWITCH2_SAMPLE_START_STRIDE 1
#define TSU_IBPR_VSWITCH2_SAMPLE_START_DEPTH  1

	/* Sample count register. This register contain the counted values. */
#define TSU_IBPR_VSWITCH2_SAMPLE_COUNT_ADDR   0x00d0a804L
#define TSU_IBPR_VSWITCH2_SAMPLE_COUNT_STRIDE 1
#define TSU_IBPR_VSWITCH2_SAMPLE_COUNT_DEPTH  1

	/*
	 * Sample UF register. Indicating which UF this entry is counting for and
	 * what type it is counting.
	 */
#define TSU_IBPR_VSWITCH2_SAMPLE_PORT_ADDR   0x00d0a806L
#define TSU_IBPR_VSWITCH2_SAMPLE_PORT_STRIDE 1
#define TSU_IBPR_VSWITCH2_SAMPLE_PORT_DEPTH  1

	/* Start port Sampling. */
#define TSU_IBPR_VSWITCH2_PORTSAMPLE_START_ADDR   0x00d0a808L
#define TSU_IBPR_VSWITCH2_PORTSAMPLE_START_STRIDE 1
#define TSU_IBPR_VSWITCH2_PORTSAMPLE_START_DEPTH  1

	/* Sample status register. */
#define TSU_IBPR_VSWITCH2_SAMPLE_STATUS_ADDR   0x00d0a80aL
#define TSU_IBPR_VSWITCH2_SAMPLE_STATUS_STRIDE 1
#define TSU_IBPR_VSWITCH2_SAMPLE_STATUS_DEPTH  1

	/* Sample interval register. */
#define TSU_IBPR_VHCA_P2_SAMPLE_INTERVAL_ADDR   0x00d0a880L
#define TSU_IBPR_VHCA_P2_SAMPLE_INTERVAL_STRIDE 1
#define TSU_IBPR_VHCA_P2_SAMPLE_INTERVAL_DEPTH  1

	/* Sample start delay register. */
#define TSU_IBPR_VHCA_P2_SAMPLE_START_ADDR   0x00d0a882L
#define TSU_IBPR_VHCA_P2_SAMPLE_START_STRIDE 1
#define TSU_IBPR_VHCA_P2_SAMPLE_START_DEPTH  1

	/* Sample count register. This register contain the counted values. */
#define TSU_IBPR_VHCA_P2_SAMPLE_COUNT_ADDR   0x00d0a884L
#define TSU_IBPR_VHCA_P2_SAMPLE_COUNT_STRIDE 1
#define TSU_IBPR_VHCA_P2_SAMPLE_COUNT_DEPTH  1

	/*
	 * Sample UF register. Indicating which port this entry is counting for and
	 * what type it is counting.
	 */
#define TSU_IBPR_VHCA_P2_SAMPLE_PORT_ADDR   0x00d0a886L
#define TSU_IBPR_VHCA_P2_SAMPLE_PORT_STRIDE 1
#define TSU_IBPR_VHCA_P2_SAMPLE_PORT_DEPTH  1

	/* Start port Sampling. */
#define TSU_IBPR_VHCA_P2_PORTSAMPLE_START_ADDR   0x00d0a888L
#define TSU_IBPR_VHCA_P2_PORTSAMPLE_START_STRIDE 1
#define TSU_IBPR_VHCA_P2_PORTSAMPLE_START_DEPTH  1

	/* Sample status register. */
#define TSU_IBPR_VHCA_P2_SAMPLE_STATUS_ADDR   0x00d0a88aL
#define TSU_IBPR_VHCA_P2_SAMPLE_STATUS_STRIDE 1
#define TSU_IBPR_VHCA_P2_SAMPLE_STATUS_DEPTH  1

	/* Port counter PortXmitDiscards. This is per vSwitch port [32:0]. */
#define TSU_IBPR_VSWITCH2_XMIT_DISCARDS_ADDR   0x00d0a900L
#define TSU_IBPR_VSWITCH2_XMIT_DISCARDS_STRIDE 1
#define TSU_IBPR_VSWITCH2_XMIT_DISCARDS_DEPTH  33

	/* Port counter PortRcvSwitchRelayErrors. This is per Switch */
#define TSU_IBPR_VSWITCH2_RCV_SWITCH_RELAY_ERRORS_ADDR   0x00d0a980L
#define TSU_IBPR_VSWITCH2_RCV_SWITCH_RELAY_ERRORS_STRIDE 1
#define TSU_IBPR_VSWITCH2_RCV_SWITCH_RELAY_ERRORS_DEPTH  1

	/* Vendor Port counter receive packets drop. This is per vSwitch. */
#define TSU_IBPR_VSWITCH2_RCV_PKTS_DROP_ADDR   0x00d0a982L
#define TSU_IBPR_VSWITCH2_RCV_PKTS_DROP_STRIDE 1
#define TSU_IBPR_VSWITCH2_RCV_PKTS_DROP_DEPTH  1

	/* Clear portcounter port receive drop */
#define TSU_IBPR_VSWITCH2_PORTCOUNTER_PRCVDROP_CLEAR_ADDR   0x00d0a984L
#define TSU_IBPR_VSWITCH2_PORTCOUNTER_PRCVDROP_CLEAR_STRIDE 1
#define TSU_IBPR_VSWITCH2_PORTCOUNTER_PRCVDROP_CLEAR_DEPTH  1

	/* Clear portcounter Port Receive Switch Relay Error */
#define TSU_IBPR_VSWITCH2_PORTCOUNTER_PRSRE_CLEAR_ADDR   0x00d0a986L
#define TSU_IBPR_VSWITCH2_PORTCOUNTER_PRSRE_CLEAR_STRIDE 1
#define TSU_IBPR_VSWITCH2_PORTCOUNTER_PRSRE_CLEAR_DEPTH  1

	/* Port counter PortXmitDiscards. This is per vSwitch port. */
#define TSU_IBPR_VHCA_P2_XMIT_DISCARDS_ADDR   0x00d0b000L
#define TSU_IBPR_VHCA_P2_XMIT_DISCARDS_STRIDE 1
#define TSU_IBPR_VHCA_P2_XMIT_DISCARDS_DEPTH  33

	/*
	 * Port counter Port Receive data. This is per vSwitch port - not the
	 * external port.
	 */
#define TSU_IBPR_VHCA_P2_RCV_DATA_ADDR   0x00d0b080L
#define TSU_IBPR_VHCA_P2_RCV_DATA_STRIDE 1
#define TSU_IBPR_VHCA_P2_RCV_DATA_DEPTH  34

	/*
	 * Port counter Port Receive Packets. This is per vSwitch port - not the
	 * external port.
	 */
#define TSU_IBPR_VHCA_P2_RCV_PKTS_ADDR   0x00d0b100L
#define TSU_IBPR_VHCA_P2_RCV_PKTS_STRIDE 1
#define TSU_IBPR_VHCA_P2_RCV_PKTS_DEPTH  34

	/*
	 * Port counter Port Xmit data. This is per vSwitch port - not the external
	 * port.
	 */
#define TSU_IBPR_VHCA_P2_XMIT_DATA_ADDR   0x00d0b180L
#define TSU_IBPR_VHCA_P2_XMIT_DATA_STRIDE 1
#define TSU_IBPR_VHCA_P2_XMIT_DATA_DEPTH  34

	/*
	 * Port counter Port Xmit Packets. This is per vSwitch port - not the
	 * external port.
	 */
#define TSU_IBPR_VHCA_P2_XMIT_PKTS_ADDR   0x00d0b200L
#define TSU_IBPR_VHCA_P2_XMIT_PKTS_STRIDE 1
#define TSU_IBPR_VHCA_P2_XMIT_PKTS_DEPTH  34

	/*
	 * Port counter counting packets dropped (marked p_error) in Xmit path.
	 */
#define TSU_IBPR_VHCA_P2_XMIT_PKTS_DROP_ADDR   0x00d0b280L
#define TSU_IBPR_VHCA_P2_XMIT_PKTS_DROP_STRIDE 1
#define TSU_IBPR_VHCA_P2_XMIT_PKTS_DROP_DEPTH  1

	/* Clear portcounter Port Xmit Drop. */
#define TSU_IBPR_VHCA_P2_PORTCOUNTER_PXDROP_CLEAR_ADDR   0x00d0b282L
#define TSU_IBPR_VHCA_P2_PORTCOUNTER_PXDROP_CLEAR_STRIDE 1
#define TSU_IBPR_VHCA_P2_PORTCOUNTER_PXDROP_CLEAR_DEPTH  1

	/* Set link state for the vHCA or the vSwitch. */
#define TSU_IBPR_SET_VLINK_STATE_ADDR   0x00d10000L
#define TSU_IBPR_SET_VLINK_STATE_STRIDE 1
#define TSU_IBPR_SET_VLINK_STATE_DEPTH  1

	/* link state for the vHCA or the vSwitch. */
#define TSU_IBPR_VLINK_STATE_REGISTER_ADDR   0x00d10002L
#define TSU_IBPR_VLINK_STATE_REGISTER_STRIDE 1
#define TSU_IBPR_VLINK_STATE_REGISTER_DEPTH  1

	/* Interrupt status register. 1b per source (1 = int triggered). */
#define TSU_IBPR_INT_STATUS_ADDR   0x00d10004L
#define TSU_IBPR_INT_STATUS_STRIDE 1
#define TSU_IBPR_INT_STATUS_DEPTH  1

	/* Interrupt mask register. 1b per source (1 = masked). */
#define TSU_IBPR_INT_MASK_ADDR   0x00d10006L
#define TSU_IBPR_INT_MASK_STRIDE 1
#define TSU_IBPR_INT_MASK_DEPTH  1

	/* Interrupt priority register. 1b per source (1 = high 0 = low). */
#define TSU_IBPR_INT_PRI_ADDR   0x00d10008L
#define TSU_IBPR_INT_PRI_STRIDE 1
#define TSU_IBPR_INT_PRI_DEPTH  1

	/*
	 * Interrupt status clear register. 1b per source (1=source will be cleared
	 * from int_status register when kick is called).
	 */
#define TSU_IBPR_INT_STATUS_CLEAR_ADDR   0x00d1000aL
#define TSU_IBPR_INT_STATUS_CLEAR_STRIDE 1
#define TSU_IBPR_INT_STATUS_CLEAR_DEPTH  1

	/* Trigger the int_status clear operation. */
#define TSU_IBPR_INT_STATUS_CLEAR_KICK_ADDR   0x00d1000cL
#define TSU_IBPR_INT_STATUS_CLEAR_KICK_STRIDE 1
#define TSU_IBPR_INT_STATUS_CLEAR_KICK_DEPTH  1

	/* Trace buffer setup */
#define TSU_IBPR_TRACE_BUFFER_SETUP_ADDR   0x00d10080L
#define TSU_IBPR_TRACE_BUFFER_SETUP_STRIDE 1
#define TSU_IBPR_TRACE_BUFFER_SETUP_DEPTH  1

	/* Trace buffer Store qualifier1 */
#define TSU_IBPR_TRACE_STORE_QUALIFIER1_ADDR   0x00d10082L
#define TSU_IBPR_TRACE_STORE_QUALIFIER1_STRIDE 1
#define TSU_IBPR_TRACE_STORE_QUALIFIER1_DEPTH  1

	/* Trace buffer Store qualifier2 */
#define TSU_IBPR_TRACE_STORE_QUALIFIER2_ADDR   0x00d10084L
#define TSU_IBPR_TRACE_STORE_QUALIFIER2_STRIDE 1
#define TSU_IBPR_TRACE_STORE_QUALIFIER2_DEPTH  1

	/* Trace buffer Store qualifier1 mask */
#define TSU_IBPR_TRACE_STORE_QUALIFIER1_MASK_ADDR   0x00d10086L
#define TSU_IBPR_TRACE_STORE_QUALIFIER1_MASK_STRIDE 1
#define TSU_IBPR_TRACE_STORE_QUALIFIER1_MASK_DEPTH  1

	/* Trace buffer Store qualifier2 mask */
#define TSU_IBPR_TRACE_STORE_QUALIFIER2_MASK_ADDR   0x00d10088L
#define TSU_IBPR_TRACE_STORE_QUALIFIER2_MASK_STRIDE 1
#define TSU_IBPR_TRACE_STORE_QUALIFIER2_MASK_DEPTH  1

	/* Trace buffer trigger1 */
#define TSU_IBPR_TRACE_TRIGGER1_ADDR   0x00d1008aL
#define TSU_IBPR_TRACE_TRIGGER1_STRIDE 1
#define TSU_IBPR_TRACE_TRIGGER1_DEPTH  1

	/* Trace buffer trigger2 */
#define TSU_IBPR_TRACE_TRIGGER2_ADDR   0x00d1008cL
#define TSU_IBPR_TRACE_TRIGGER2_STRIDE 1
#define TSU_IBPR_TRACE_TRIGGER2_DEPTH  1

	/* Trace buffer trigger1 mask */
#define TSU_IBPR_TRACE_TRIGGER1_MASK_ADDR   0x00d1008eL
#define TSU_IBPR_TRACE_TRIGGER1_MASK_STRIDE 1
#define TSU_IBPR_TRACE_TRIGGER1_MASK_DEPTH  1

	/* Trace buffer trigger2 mask */
#define TSU_IBPR_TRACE_TRIGGER2_MASK_ADDR   0x00d10090L
#define TSU_IBPR_TRACE_TRIGGER2_MASK_STRIDE 1
#define TSU_IBPR_TRACE_TRIGGER2_MASK_DEPTH  1

	/* Start trace buffer */
#define TSU_IBPR_TRACE_START_ADDR   0x00d10092L
#define TSU_IBPR_TRACE_START_STRIDE 1
#define TSU_IBPR_TRACE_START_DEPTH  1

	/* Stop trace buffer */
#define TSU_IBPR_TRACE_STOP_ADDR   0x00d10094L
#define TSU_IBPR_TRACE_STOP_STRIDE 1
#define TSU_IBPR_TRACE_STOP_DEPTH  1

	/* Trace buffer status */
#define TSU_IBPR_TRACE_BUFFER_STATUS_ADDR   0x00d10096L
#define TSU_IBPR_TRACE_BUFFER_STATUS_STRIDE 1
#define TSU_IBPR_TRACE_BUFFER_STATUS_DEPTH  1

	/* Trace buffer */
#define TSU_IBPR_TRACE_BUFFER_ADDR   0x00d14000L
#define TSU_IBPR_TRACE_BUFFER_STRIDE 1
#define TSU_IBPR_TRACE_BUFFER_DEPTH  16384

	/* Trace buffer assoc info */
#define TSU_IBPR_TRACE_BUFFER_ASSOC_INFO_ADDR   0x00d18000L
#define TSU_IBPR_TRACE_BUFFER_ASSOC_INFO_STRIDE 1
#define TSU_IBPR_TRACE_BUFFER_ASSOC_INFO_DEPTH  16384

	/* Debug */
#define TSU_IBPR_TRACE_BUFFER_DEBUG_ADDR   0x00d1c000L
#define TSU_IBPR_TRACE_BUFFER_DEBUG_STRIDE 1
#define TSU_IBPR_TRACE_BUFFER_DEBUG_DEPTH  16384

	/*
	 * Per vHCA (UF0-32) register. This table contain valid RSS combinations to
	 * calculate for this UF.
	 */
#define TSU_IBPR_RSS_CONTROL_ADDR   0x00d20000L
#define TSU_IBPR_RSS_CONTROL_STRIDE 1
#define TSU_IBPR_RSS_CONTROL_DEPTH  33

	/* 16B Secret key for RSS generation for IPv4. */
#define TSU_IBPR_RSS_IPV4_SECRET_KEY_ADDR   0x00d20080L
#define TSU_IBPR_RSS_IPV4_SECRET_KEY_STRIDE 1
#define TSU_IBPR_RSS_IPV4_SECRET_KEY_DEPTH  2

	/* 40B Secret key for RSS generation for IPv6. */
#define TSU_IBPR_RSS_IPV6_SECRET_KEY_ADDR   0x00d20090L
#define TSU_IBPR_RSS_IPV6_SECRET_KEY_STRIDE 1
#define TSU_IBPR_RSS_IPV6_SECRET_KEY_DEPTH  5

	/* Per vHCA + EPS-C ethernet MAC address register. */
#define TSU_IBPR_P1_EOIB_MAC1_ADDR   0x00d20100L
#define TSU_IBPR_P1_EOIB_MAC1_STRIDE 1
#define TSU_IBPR_P1_EOIB_MAC1_DEPTH  34

	/* Per vHCA + EPS-C ethernet MAC address register. */
#define TSU_IBPR_P1_EOIB_MAC2_ADDR   0x00d20180L
#define TSU_IBPR_P1_EOIB_MAC2_STRIDE 1
#define TSU_IBPR_P1_EOIB_MAC2_DEPTH  34

	/* Per vHCA + EPS-C ethernet MAC address register. */
#define TSU_IBPR_P2_EOIB_MAC1_ADDR   0x00d20200L
#define TSU_IBPR_P2_EOIB_MAC1_STRIDE 1
#define TSU_IBPR_P2_EOIB_MAC1_DEPTH  34

	/* Per vHCA + EPS-C ethernet MAC address register. */
#define TSU_IBPR_P2_EOIB_MAC2_ADDR   0x00d20280L
#define TSU_IBPR_P2_EOIB_MAC2_STRIDE 1
#define TSU_IBPR_P2_EOIB_MAC2_DEPTH  34

	/* Per vHCA + EPS-C ethernet control register. */
#define TSU_IBPR_EOIB_CONTROL_ADDR   0x00d20300L
#define TSU_IBPR_EOIB_CONTROL_STRIDE 1
#define TSU_IBPR_EOIB_CONTROL_DEPTH  34

	/* Per vHCA + EPS-C DMAC seed register. */
#define TSU_IBPR_DMAC_SEED_ADDR   0x00d20380L
#define TSU_IBPR_DMAC_SEED_STRIDE 1
#define TSU_IBPR_DMAC_SEED_DEPTH  34

	/* Per vHCA + EPS-C VLAN EtherTypes register. */
#define TSU_IBPR_EOIB_VLAN_ETHERTYPES_1_ADDR   0x00d20400L
#define TSU_IBPR_EOIB_VLAN_ETHERTYPES_1_STRIDE 1
#define TSU_IBPR_EOIB_VLAN_ETHERTYPES_1_DEPTH  1

	/* Per vHCA + EPS-C VLAN EtherTypes register. */
#define TSU_IBPR_EOIB_VLAN_ETHERTYPES_2_ADDR   0x00d20480L
#define TSU_IBPR_EOIB_VLAN_ETHERTYPES_2_STRIDE 1
#define TSU_IBPR_EOIB_VLAN_ETHERTYPES_2_DEPTH  1

	/* Per vHCA PF control register. */
#define TSU_IBPR_EOIB_PF_CONTROL_ADDR   0x00d20500L
#define TSU_IBPR_EOIB_PF_CONTROL_STRIDE 1
#define TSU_IBPR_EOIB_PF_CONTROL_DEPTH  34

	/* Common unicast overflow table for all vHCAs. */
#define TSU_IBPR_EOIB_UNICAST_OVERFLOW_TABLE_ADDR   0x00d20580L
#define TSU_IBPR_EOIB_UNICAST_OVERFLOW_TABLE_STRIDE 1
#define TSU_IBPR_EOIB_UNICAST_OVERFLOW_TABLE_DEPTH  64

	/* Common multicast table for all VHCAs. */
#define TSU_IBPR_EOIB_MULTICAST_TABLE_ADDR   0x00d20600L
#define TSU_IBPR_EOIB_MULTICAST_TABLE_STRIDE 1
#define TSU_IBPR_EOIB_MULTICAST_TABLE_DEPTH  64

	/*
	 * Per vHCA + EPS-C VID table. There are 64 entries per UF. 4096b * 34 (64x34
	 * entries).
	 */
#define TSU_IBPR_EOIB_VID_TABLE_ADDR   0x00d21000L
#define TSU_IBPR_EOIB_VID_TABLE_STRIDE 1
#define TSU_IBPR_EOIB_VID_TABLE_DEPTH  2176

	/*
	 * Header split register indicating what EoIB headers to try splitting at.
	 */
#define TSU_IBPR_HDR_SPLIT_EOIB_ADDR   0x00d22000L
#define TSU_IBPR_HDR_SPLIT_EOIB_STRIDE 1
#define TSU_IBPR_HDR_SPLIT_EOIB_DEPTH  33

	/*
	 * Header split register indicating what IPoIB headers to try splitting at
	 * for UD transport.
	 */
#define TSU_IBPR_HDR_SPLIT_IPOIB_UD_ADDR   0x00d22080L
#define TSU_IBPR_HDR_SPLIT_IPOIB_UD_STRIDE 1
#define TSU_IBPR_HDR_SPLIT_IPOIB_UD_DEPTH  33

	/* Legal ether type. */
#define TSU_IBPR_LEGAL_ETHER_TYPE_ADDR   0x00d22100L
#define TSU_IBPR_LEGAL_ETHER_TYPE_STRIDE 1
#define TSU_IBPR_LEGAL_ETHER_TYPE_DEPTH  2

	/*
	 * Legal extensions for IPv6. 256 bits per UF. Table size is then 4*NUM_UF
	 * (should be 34)
	 */
#define TSU_IBPR_IPV6_LEGAL_EXTENSION_HEADER_ADDR   0x00d22200L
#define TSU_IBPR_IPV6_LEGAL_EXTENSION_HEADER_STRIDE 1
#define TSU_IBPR_IPV6_LEGAL_EXTENSION_HEADER_DEPTH  4

	/* Max ethernet frame size typically 1500 or 1535 */
#define TSU_IBPR_MAX_ETH_FRAME_ADDR   0x00d22300L
#define TSU_IBPR_MAX_ETH_FRAME_STRIDE 1
#define TSU_IBPR_MAX_ETH_FRAME_DEPTH  1

	/* bypass offload */
#define TSU_IBPR_BYPASS_OFFLOAD_ADDR   0x00d22320L
#define TSU_IBPR_BYPASS_OFFLOAD_STRIDE 1
#define TSU_IBPR_BYPASS_OFFLOAD_DEPTH  1

	/* debug signals */
#define TSU_IBPR_IBPR_DEBUG_ADDR   0x00d22340L
#define TSU_IBPR_IBPR_DEBUG_STRIDE 1
#define TSU_IBPR_IBPR_DEBUG_DEPTH  1

	/*
	 * Base address registers per UF for software owned descriptor portion of
	 * send queue descriptors.
	 */
#define TSU_SQS_SQ_BASE_ADDR_SW_0_ADDR   0x00e00000L
#define TSU_SQS_SQ_BASE_ADDR_SW_0_STRIDE 1
#define TSU_SQS_SQ_BASE_ADDR_SW_0_DEPTH  34

	/*
	 * Base address registers per UF for software owned descriptor portion of
	 * send queue descriptors.
	 */
#define TSU_SQS_SQ_BASE_ADDR_SW_1_ADDR   0x00e00040L
#define TSU_SQS_SQ_BASE_ADDR_SW_1_STRIDE 1
#define TSU_SQS_SQ_BASE_ADDR_SW_1_DEPTH  34

	/*
	 * Base address registers per UF for software owned descriptor portion of
	 * send queue descriptors.
	 */
#define TSU_SQS_SQ_BASE_ADDR_SW_2_ADDR   0x00e00080L
#define TSU_SQS_SQ_BASE_ADDR_SW_2_STRIDE 1
#define TSU_SQS_SQ_BASE_ADDR_SW_2_DEPTH  34

	/*
	 * Base address registers per UF for hardware owned descriptor portion of
	 * send queue descriptors.
	 */
#define TSU_SQS_SQ_BASE_ADDR_HW_0_ADDR   0x00e00100L
#define TSU_SQS_SQ_BASE_ADDR_HW_0_STRIDE 1
#define TSU_SQS_SQ_BASE_ADDR_HW_0_DEPTH  34

	/*
	 * Base address registers per UF for hardware owned descriptor portion of
	 * send queue descriptors.
	 */
#define TSU_SQS_SQ_BASE_ADDR_HW_1_ADDR   0x00e00140L
#define TSU_SQS_SQ_BASE_ADDR_HW_1_STRIDE 1
#define TSU_SQS_SQ_BASE_ADDR_HW_1_DEPTH  34

	/*
	 * Base address registers per UF for hardware owned descriptor portion of
	 * send queue descriptors.
	 */
#define TSU_SQS_SQ_BASE_ADDR_HW_2_ADDR   0x00e00180L
#define TSU_SQS_SQ_BASE_ADDR_HW_2_STRIDE 1
#define TSU_SQS_SQ_BASE_ADDR_HW_2_DEPTH  34

	/*
	 * SQS list table is used to program the list number to associate with UF.
	 * Address is list number and data is UF. A single UF can allocate multiple
	 * lists.
	 */
#define TSU_SQS_SQS_LIST_TABLE_ADDR   0x00e00200L
#define TSU_SQS_SQS_LIST_TABLE_STRIDE 1
#define TSU_SQS_SQS_LIST_TABLE_DEPTH  68

	/*
	 * This register must be set and the kick register is written in order to
	 * start the operation.
	 */
#define TSU_SQS_UF_CONTROL_ADDR   0x00e00280L
#define TSU_SQS_UF_CONTROL_STRIDE 1
#define TSU_SQS_UF_CONTROL_DEPTH  1

	/* Starts operation defined in uf_control. */
#define TSU_SQS_UF_CONTROL_KICK_ADDR   0x00e00281L
#define TSU_SQS_UF_CONTROL_KICK_STRIDE 1
#define TSU_SQS_UF_CONTROL_KICK_DEPTH  1

	/* Interrupt status register. 1b per source (1 = int triggered). */
#define TSU_SQS_INT_STATUS_ADDR   0x00e00282L
#define TSU_SQS_INT_STATUS_STRIDE 1
#define TSU_SQS_INT_STATUS_DEPTH  1

	/* Interrupt mask register. 1b per source (1 = masked). */
#define TSU_SQS_INT_MASK_ADDR   0x00e00283L
#define TSU_SQS_INT_MASK_STRIDE 1
#define TSU_SQS_INT_MASK_DEPTH  1

	/* Interrupt priority register. 1b per source (1 = high 0 = low). */
#define TSU_SQS_INT_PRI_ADDR   0x00e00284L
#define TSU_SQS_INT_PRI_STRIDE 1
#define TSU_SQS_INT_PRI_DEPTH  1

	/*
	 * Interrupt status clear register. 1b per source (1=source will be cleared
	 * from int_status register when kick is called).
	 */
#define TSU_SQS_INT_STATUS_CLEAR_ADDR   0x00e00285L
#define TSU_SQS_INT_STATUS_CLEAR_STRIDE 1
#define TSU_SQS_INT_STATUS_CLEAR_DEPTH  1

	/* Trigger the int_status clear operation. */
#define TSU_SQS_INT_STATUS_CLEAR_KICK_ADDR   0x00e00286L
#define TSU_SQS_INT_STATUS_CLEAR_KICK_STRIDE 1
#define TSU_SQS_INT_STATUS_CLEAR_KICK_DEPTH  1

	/* Address: SQS list number. Flush status. */
#define TSU_SQS_SQS_LIST_STATUS0_ADDR   0x00e00300L
#define TSU_SQS_SQS_LIST_STATUS0_STRIDE 1
#define TSU_SQS_SQS_LIST_STATUS0_DEPTH  68

	/*
	 * Address: SQS list number. Set when the PCIe response has error on the
	 * descriptor read.
	 */
#define TSU_SQS_SQS_LIST_STATUS1_ADDR   0x00e00380L
#define TSU_SQS_SQS_LIST_STATUS1_STRIDE 1
#define TSU_SQS_SQS_LIST_STATUS1_DEPTH  68

	/*
	 * Hash mask and shift control. XOR width is based on the log 2 of number of
	 * list for that UF.
	 */
#define TSU_SQS_HASH_CTRL_ADDR   0x00e00400L
#define TSU_SQS_HASH_CTRL_STRIDE 1
#define TSU_SQS_HASH_CTRL_DEPTH  4

	/*
	 * Disble Atomic cmp and swap for the QP next pointer null check. If set,
	 * hardware generates read-then-write to update the QP next pointer.
	 */
#define TSU_SQS_ATOMIC_DISABLE_ADDR   0x00e00405L
#define TSU_SQS_ATOMIC_DISABLE_STRIDE 1
#define TSU_SQS_ATOMIC_DISABLE_DEPTH  1

	/* Number of burst read for the send queue element per QP. */
#define TSU_SQS_SQ_BURST_READ_SIZE_ADDR   0x00e00406L
#define TSU_SQS_SQ_BURST_READ_SIZE_STRIDE 1
#define TSU_SQS_SQ_BURST_READ_SIZE_DEPTH  1

	/* Number of DB count from CBU. */
#define TSU_SQS_CBU_DB_CNT_ADDR   0x00e00407L
#define TSU_SQS_CBU_DB_CNT_STRIDE 1
#define TSU_SQS_CBU_DB_CNT_DEPTH  1

	/* Number of DB count from ERR. */
#define TSU_SQS_ERR_DB_CNT_ADDR   0x00e00408L
#define TSU_SQS_ERR_DB_CNT_STRIDE 1
#define TSU_SQS_ERR_DB_CNT_DEPTH  1

	/* Number of LLQ push. */
#define TSU_SQS_LLQ_PUSH_CNT_ADDR   0x00e00409L
#define TSU_SQS_LLQ_PUSH_CNT_STRIDE 1
#define TSU_SQS_LLQ_PUSH_CNT_DEPTH  1

	/* Number of LLQ pop. */
#define TSU_SQS_LLQ_POP_CNT_ADDR   0x00e0040aL
#define TSU_SQS_LLQ_POP_CNT_STRIDE 1
#define TSU_SQS_LLQ_POP_CNT_DEPTH  1

	/* Number of LLQ peek. */
#define TSU_SQS_LLQ_PEEK_CNT_ADDR   0x00e0040bL
#define TSU_SQS_LLQ_PEEK_CNT_STRIDE 1
#define TSU_SQS_LLQ_PEEK_CNT_DEPTH  1

	/* Number of Send Queue read. */
#define TSU_SQS_SQ_RD_CNT_ADDR   0x00e0040cL
#define TSU_SQS_SQ_RD_CNT_STRIDE 1
#define TSU_SQS_SQ_RD_CNT_DEPTH  1

	/* Number of Descriptor read. */
#define TSU_SQS_DSCR_REQ_CNT_ADDR   0x00e0040dL
#define TSU_SQS_DSCR_REQ_CNT_STRIDE 1
#define TSU_SQS_DSCR_REQ_CNT_DEPTH  1

	/* Number of Descriptor read response. */
#define TSU_SQS_DSCR_RSP_CNT_ADDR   0x00e0040eL
#define TSU_SQS_DSCR_RSP_CNT_STRIDE 1
#define TSU_SQS_DSCR_RSP_CNT_DEPTH  1

	/* Number of Atomic request. */
#define TSU_SQS_ATM_REQ_CNT_ADDR   0x00e0040fL
#define TSU_SQS_ATM_REQ_CNT_STRIDE 1
#define TSU_SQS_ATM_REQ_CNT_DEPTH  1

	/* Number of Atomic response. */
#define TSU_SQS_ATM_RSP_CNT_ADDR   0x00e00410L
#define TSU_SQS_ATM_RSP_CNT_STRIDE 1
#define TSU_SQS_ATM_RSP_CNT_DEPTH  1

	/* Number of QP insert to the SQS list. */
#define TSU_SQS_PUSH_SQS_LIST_CNT_ADDR   0x00e00411L
#define TSU_SQS_PUSH_SQS_LIST_CNT_STRIDE 1
#define TSU_SQS_PUSH_SQS_LIST_CNT_DEPTH  1

	/* Number of clock to wait before writting to the ring. */
#define TSU_SQS_RING_TIMER_ADDR   0x00e00412L
#define TSU_SQS_RING_TIMER_STRIDE 1
#define TSU_SQS_RING_TIMER_DEPTH  1

	/* Set to write 64B for the send queue hardware descriptor. */
#define TSU_SQS_PADDED_SQ_DSCR_HW_ADDR   0x00e00413L
#define TSU_SQS_PADDED_SQ_DSCR_HW_STRIDE 1
#define TSU_SQS_PADDED_SQ_DSCR_HW_DEPTH  1

	/* Set to write 64B for the PIO ring buffer. */
#define TSU_SQS_PADDED_RING_BUFFER_ADDR   0x00e00414L
#define TSU_SQS_PADDED_RING_BUFFER_STRIDE 1
#define TSU_SQS_PADDED_RING_BUFFER_DEPTH  1

	/* ECC error control */
#define TSU_SQS_ECC_ERR_CTRL_ADDR   0x00e00415L
#define TSU_SQS_ECC_ERR_CTRL_STRIDE 1
#define TSU_SQS_ECC_ERR_CTRL_DEPTH  1

	/* ECC status */
#define TSU_SQS_ECC_ERR_STATUS_ADDR   0x00e00416L
#define TSU_SQS_ECC_ERR_STATUS_STRIDE 1
#define TSU_SQS_ECC_ERR_STATUS_DEPTH  1

	/* ECC status */
#define TSU_SQS_ECC_ERR_STATUS_CLEAR_ADDR   0x00e00417L
#define TSU_SQS_ECC_ERR_STATUS_CLEAR_STRIDE 1
#define TSU_SQS_ECC_ERR_STATUS_CLEAR_DEPTH  1

	/* SQ MMU context to use EPSC memory permission */
#define TSU_SQS_SQ_MMU_CONTEXT_EPSC_PERM_ADDR   0x00e00418L
#define TSU_SQS_SQ_MMU_CONTEXT_EPSC_PERM_STRIDE 1
#define TSU_SQS_SQ_MMU_CONTEXT_EPSC_PERM_DEPTH  1

	/* Timer scale: 12 bits interval counter 8.192us 32 bits wrap counter */
#define TSU_SQS_TIMER_SCALE_ADDR   0x00e00419L
#define TSU_SQS_TIMER_SCALE_STRIDE 1
#define TSU_SQS_TIMER_SCALE_DEPTH  1

	/* LLQ credit for Doorbell Retry Transport Timer and Response */
#define TSU_SQS_LLQ_CREDIT_ADDR   0x00e0041aL
#define TSU_SQS_LLQ_CREDIT_STRIDE 1
#define TSU_SQS_LLQ_CREDIT_DEPTH  1

	/* software mode for qps_if */
#define TSU_SQS_QPS_IF_ADDR   0x00e0041bL
#define TSU_SQS_QPS_IF_STRIDE 1
#define TSU_SQS_QPS_IF_DEPTH  1

	/* software mode for qps_if kick */
#define TSU_SQS_QPS_IF_KICK_ADDR   0x00e0041cL
#define TSU_SQS_QPS_IF_KICK_STRIDE 1
#define TSU_SQS_QPS_IF_KICK_DEPTH  1

	/* software mode for host_if response scheduling */
#define TSU_SQS_HOST_IF0_ADDR   0x00e0041dL
#define TSU_SQS_HOST_IF0_STRIDE 1
#define TSU_SQS_HOST_IF0_DEPTH  1

	/* software mode for host_if response scheduling */
#define TSU_SQS_HOST_IF1_ADDR   0x00e0041eL
#define TSU_SQS_HOST_IF1_STRIDE 1
#define TSU_SQS_HOST_IF1_DEPTH  1

	/* software mode for host_if response scheduling */
#define TSU_SQS_HOST_IF2_ADDR   0x00e0041fL
#define TSU_SQS_HOST_IF2_STRIDE 1
#define TSU_SQS_HOST_IF2_DEPTH  1

	/* software mode for host_if response scheduling */
#define TSU_SQS_HOST_IF3_ADDR   0x00e00420L
#define TSU_SQS_HOST_IF3_STRIDE 1
#define TSU_SQS_HOST_IF3_DEPTH  1

	/* software mode for host_if response scheduling kick */
#define TSU_SQS_HOST_IF_KICK_ADDR   0x00e00421L
#define TSU_SQS_HOST_IF_KICK_STRIDE 1
#define TSU_SQS_HOST_IF_KICK_DEPTH  1

	/* Base address registers per UF for hardware to FIFO PIO doorbell. */
#define TSU_SQS_PIO_RING_BASE_ADDR_0_ADDR   0x00e00500L
#define TSU_SQS_PIO_RING_BASE_ADDR_0_STRIDE 1
#define TSU_SQS_PIO_RING_BASE_ADDR_0_DEPTH  34

	/* Base address registers per UF for hardware to FIFO PIO doorbell. */
#define TSU_SQS_PIO_RING_BASE_ADDR_1_ADDR   0x00e00540L
#define TSU_SQS_PIO_RING_BASE_ADDR_1_STRIDE 1
#define TSU_SQS_PIO_RING_BASE_ADDR_1_DEPTH  34

	/* Base address registers per UF for hardware to FIFO PIO doorbell. */
#define TSU_SQS_PIO_RING_BASE_ADDR_2_ADDR   0x00e00580L
#define TSU_SQS_PIO_RING_BASE_ADDR_2_STRIDE 1
#define TSU_SQS_PIO_RING_BASE_ADDR_2_DEPTH  34

	/* Read/Write for the PIO ring buffer write pointer */
#define TSU_SQS_PIO_RING_BUFFER_WR_PTR_ADDR   0x00e005c0L
#define TSU_SQS_PIO_RING_BUFFER_WR_PTR_STRIDE 1
#define TSU_SQS_PIO_RING_BUFFER_WR_PTR_DEPTH  34

	/*
	 * Address: SQS list number. Set when the PCIe response has error on the
	 * descriptor read.
	 */
#define TSU_SQS_SQS_LIST_ERR_STATUS_ADDR   0x00e00600L
#define TSU_SQS_SQS_LIST_ERR_STATUS_STRIDE 1
#define TSU_SQS_SQS_LIST_ERR_STATUS_DEPTH  68

	/* Read/Write for the PIO ring buffer read pointer */
#define TSU_SQS_PIO_RING_BUFFER_RD_PTR_ADDR   0x00e00680L
#define TSU_SQS_PIO_RING_BUFFER_RD_PTR_STRIDE 1
#define TSU_SQS_PIO_RING_BUFFER_RD_PTR_DEPTH  34

	/* Read/Write for the PIO ring buffer pending count */
#define TSU_SQS_PIO_RING_BUFFER_PENDING_CNT_ADDR   0x00e006c0L
#define TSU_SQS_PIO_RING_BUFFER_PENDING_CNT_STRIDE 1
#define TSU_SQS_PIO_RING_BUFFER_PENDING_CNT_DEPTH  34

	/* Base address registers per UF for response queue. */
#define TSU_SQS_RSPQ_BASE_ADDR_0_ADDR   0x00e00700L
#define TSU_SQS_RSPQ_BASE_ADDR_0_STRIDE 1
#define TSU_SQS_RSPQ_BASE_ADDR_0_DEPTH  33

	/* Base address registers per UF for response queue. */
#define TSU_SQS_RSPQ_BASE_ADDR_1_ADDR   0x00e00740L
#define TSU_SQS_RSPQ_BASE_ADDR_1_STRIDE 1
#define TSU_SQS_RSPQ_BASE_ADDR_1_DEPTH  33

	/* Base address registers per UF for response queue. */
#define TSU_SQS_RSPQ_BASE_ADDR_2_ADDR   0x00e00780L
#define TSU_SQS_RSPQ_BASE_ADDR_2_STRIDE 1
#define TSU_SQS_RSPQ_BASE_ADDR_2_DEPTH  33

	/* Credit a particular TVL can get. */
#define TSU_SQS_TVL_CREDIT_ADDR   0x00e007c0L
#define TSU_SQS_TVL_CREDIT_STRIDE 1
#define TSU_SQS_TVL_CREDIT_DEPTH  128

	/* Head pointer for MMU contexts policies check failed. */
#define TSU_SQS_BAD_MMU_CNTXT_HP_ADDR   0x00e00840L
#define TSU_SQS_BAD_MMU_CNTXT_HP_STRIDE 1
#define TSU_SQS_BAD_MMU_CNTXT_HP_DEPTH  34

	/*
	 * Base address registers per UF for response queue tvl pointer. Each tvl has
	 * 16 bytes pointers
	 */
#define TSU_SQS_RSPQ_TVL_BASE_ADDR_0_ADDR   0x00e00880L
#define TSU_SQS_RSPQ_TVL_BASE_ADDR_0_STRIDE 1
#define TSU_SQS_RSPQ_TVL_BASE_ADDR_0_DEPTH  33

	/* Base address registers per UF for response queue tvl pointer. */
#define TSU_SQS_RSPQ_TVL_BASE_ADDR_1_ADDR   0x00e008c0L
#define TSU_SQS_RSPQ_TVL_BASE_ADDR_1_STRIDE 1
#define TSU_SQS_RSPQ_TVL_BASE_ADDR_1_DEPTH  33

	/*
	 * Base address registers per UF for response queue tvl pointer. Warning!
	 * This register is unused by hardware and it is always read as 0.
	 */
#define TSU_SQS_RSPQ_TVL_BASE_ADDR_2_ADDR   0x00e00900L
#define TSU_SQS_RSPQ_TVL_BASE_ADDR_2_STRIDE 1
#define TSU_SQS_RSPQ_TVL_BASE_ADDR_2_DEPTH  33

	/* Address: uf number tvl list number. Flush and Error status. */
#define TSU_SQS_RSPQ_LIST_STATUS_ADDR   0x00e02000L
#define TSU_SQS_RSPQ_LIST_STATUS_STRIDE 1
#define TSU_SQS_RSPQ_LIST_STATUS_DEPTH  4224

	/*
	 * Base address registers per UF for software owned descriptor portion of
	 * completion queue descriptors.
	 */
#define TSU_CBLD_CQ_BASE_ADDR_SW_0_ADDR   0x00f00000L
#define TSU_CBLD_CQ_BASE_ADDR_SW_0_STRIDE 1
#define TSU_CBLD_CQ_BASE_ADDR_SW_0_DEPTH  34

#define TSU_CBLD_CQ_BASE_ADDR_SW_1_ADDR   0x00f00040L
#define TSU_CBLD_CQ_BASE_ADDR_SW_1_STRIDE 1
#define TSU_CBLD_CQ_BASE_ADDR_SW_1_DEPTH  34

#define TSU_CBLD_CQ_BASE_ADDR_SW_2_ADDR   0x00f00080L
#define TSU_CBLD_CQ_BASE_ADDR_SW_2_STRIDE 1
#define TSU_CBLD_CQ_BASE_ADDR_SW_2_DEPTH  34

	/*
	 * Base address registers per UF for hardware owned descriptor portion of
	 * completion queue descriptors.
	 */
#define TSU_CBLD_CQ_BASE_ADDR_HW_0_ADDR   0x00f000c0L
#define TSU_CBLD_CQ_BASE_ADDR_HW_0_STRIDE 1
#define TSU_CBLD_CQ_BASE_ADDR_HW_0_DEPTH  34

#define TSU_CBLD_CQ_BASE_ADDR_HW_1_ADDR   0x00f00100L
#define TSU_CBLD_CQ_BASE_ADDR_HW_1_STRIDE 1
#define TSU_CBLD_CQ_BASE_ADDR_HW_1_DEPTH  34

#define TSU_CBLD_CQ_BASE_ADDR_HW_2_ADDR   0x00f00140L
#define TSU_CBLD_CQ_BASE_ADDR_HW_2_STRIDE 1
#define TSU_CBLD_CQ_BASE_ADDR_HW_2_DEPTH  34

	/* Error type the programmable counter is counting. */
#define TSU_CBLD_PROG_ERROR_TYPE_ADDR   0x00f00200L
#define TSU_CBLD_PROG_ERROR_TYPE_STRIDE 1
#define TSU_CBLD_PROG_ERROR_TYPE_DEPTH  1

	/*
	 * Counts how many times error type defined in prog_error_type register is
	 * received by tsu_cbld. Sticky at max value and then needs to be cleared.
	 */
#define TSU_CBLD_PROG_COUNTER_ADDR   0x00f00201L
#define TSU_CBLD_PROG_COUNTER_STRIDE 1
#define TSU_CBLD_PROG_COUNTER_DEPTH  1

	/* Clears prog_counter. */
#define TSU_CBLD_CLEAR_PROG_COUNTER_ADDR   0x00f00202L
#define TSU_CBLD_CLEAR_PROG_COUNTER_STRIDE 1
#define TSU_CBLD_CLEAR_PROG_COUNTER_DEPTH  1

	/* Interrupt status register. 1b per source (1 = int triggered). */
#define TSU_CBLD_INT_STATUS_ADDR   0x00f00400L
#define TSU_CBLD_INT_STATUS_STRIDE 1
#define TSU_CBLD_INT_STATUS_DEPTH  1

	/* Interrupt mask register. 1b per source (1 = masked). */
#define TSU_CBLD_INT_MASK_ADDR   0x00f00401L
#define TSU_CBLD_INT_MASK_STRIDE 1
#define TSU_CBLD_INT_MASK_DEPTH  1

	/* Interrupt priority register. 1b per source (1 = high 0 = low). */
#define TSU_CBLD_INT_PRI_ADDR   0x00f00402L
#define TSU_CBLD_INT_PRI_STRIDE 1
#define TSU_CBLD_INT_PRI_DEPTH  1

	/*
	 * Interrupt status clear register. 1b per source (1=source will be cleared
	 * from int_status register when kick is called).
	 */
#define TSU_CBLD_INT_STATUS_CLEAR_ADDR   0x00f00403L
#define TSU_CBLD_INT_STATUS_CLEAR_STRIDE 1
#define TSU_CBLD_INT_STATUS_CLEAR_DEPTH  1

	/* Trigger the int_status clear operation. */
#define TSU_CBLD_INT_STATUS_CLEAR_KICK_ADDR   0x00f00404L
#define TSU_CBLD_INT_STATUS_CLEAR_KICK_STRIDE 1
#define TSU_CBLD_INT_STATUS_CLEAR_KICK_DEPTH  1

	/*
	 * This register must be set and the kick register is written in order to
	 * start the operation.
	 */
#define TSU_CBLD_UF_CONTROL_ADDR   0x00f00700L
#define TSU_CBLD_UF_CONTROL_STRIDE 1
#define TSU_CBLD_UF_CONTROL_DEPTH  1

	/* Starts operation defined in uf_control. */
#define TSU_CBLD_UF_CONTROL_KICK_ADDR   0x00f00701L
#define TSU_CBLD_UF_CONTROL_KICK_STRIDE 1
#define TSU_CBLD_UF_CONTROL_KICK_DEPTH  1

	/*
	 * One bit per vHCA indicating if the vHCA is allowed to use proxy mode.
	 */
#define TSU_CBLD_PROXY_ALLOWED_ADDR   0x00f00702L
#define TSU_CBLD_PROXY_ALLOWED_STRIDE 1
#define TSU_CBLD_PROXY_ALLOWED_DEPTH  1

	/* Various diagnostic control bits */
#define TSU_CBLD_DIAGNOSTIC_ADDR   0x00f00800L
#define TSU_CBLD_DIAGNOSTIC_STRIDE 1
#define TSU_CBLD_DIAGNOSTIC_DEPTH  1

	/*
	 * Debug register0. There are no definitions of the fields generated, but
	 * they can be found from the HW definitions.
	 */
#define TSU_CBLD_DEBUG_0_ADDR   0x00f00801L
#define TSU_CBLD_DEBUG_0_STRIDE 1
#define TSU_CBLD_DEBUG_0_DEPTH  1

	/*
	 * Debug register. There are no definitions of the fields generated, but they
	 * can be found from the HW definitions.
	 */
#define TSU_CBLD_DEBUG_1_ADDR   0x00f00802L
#define TSU_CBLD_DEBUG_1_STRIDE 1
#define TSU_CBLD_DEBUG_1_DEPTH  1

	/*
	 * Debug register. There are no definitions of the fields generated, but they
	 * can be found from the HW definitions.
	 */
#define TSU_CBLD_DEBUG_2_ADDR   0x00f00803L
#define TSU_CBLD_DEBUG_2_STRIDE 1
#define TSU_CBLD_DEBUG_2_DEPTH  1

	/* Clears the diag RAM for the UF specified. */
#define TSU_CBLD_CLEAR_DIAG_RAM_ADDR   0x00f01000L
#define TSU_CBLD_CLEAR_DIAG_RAM_STRIDE 1
#define TSU_CBLD_CLEAR_DIAG_RAM_DEPTH  1

	/* Clears the diag RAM - per UF. */
#define TSU_CBLD_CLEAR_DIAG_RAM_KICK_ADDR   0x00f01001L
#define TSU_CBLD_CLEAR_DIAG_RAM_KICK_STRIDE 1
#define TSU_CBLD_CLEAR_DIAG_RAM_KICK_DEPTH  1

	/* Read the address for the UF. */
#define TSU_CBLD_DIAG_RAM_ADDR_ADDR   0x00f0139cL
#define TSU_CBLD_DIAG_RAM_ADDR_STRIDE 1
#define TSU_CBLD_DIAG_RAM_ADDR_DEPTH  34

	/* Set up which RAM entry to read. */
#define TSU_CBLD_DIAG_RAM_READ_ADDR_ADDR   0x00f0179cL
#define TSU_CBLD_DIAG_RAM_READ_ADDR_STRIDE 1
#define TSU_CBLD_DIAG_RAM_READ_ADDR_DEPTH  1

	/*
	 * Kick - reads the data from the RAM entry specified in diag_ram_read_addr
	 * and adds it to registers which can be read.
	 */
#define TSU_CBLD_DIAG_RAM_READ_KICK_ADDR   0x00f01b9bL
#define TSU_CBLD_DIAG_RAM_READ_KICK_STRIDE 1
#define TSU_CBLD_DIAG_RAM_READ_KICK_DEPTH  1

	/* Time to wait before starting send queue mode. */
#define TSU_CBLD_FENCE_TIME_TO_WAIT_ADDR   0x00f02000L
#define TSU_CBLD_FENCE_TIME_TO_WAIT_STRIDE 1
#define TSU_CBLD_FENCE_TIME_TO_WAIT_DEPTH  1

	/*
	 * QP state transitions for different error classes. This register should not
	 * be used unless there is a bug.
	 */
#define TSU_CBLD_ERR_CLASS_MODE_ADDR   0x00f02001L
#define TSU_CBLD_ERR_CLASS_MODE_STRIDE 1
#define TSU_CBLD_ERR_CLASS_MODE_DEPTH  1

	/*
	 * When this register is written to, the content of indirect_eq_sw_index_wr,
	 * indirect_eq_hw_index_wr, indirect_eq_ctrl_wr, indirect_eq_base_addr_wr,
	 * indirect_eq_size_wr is written to event queue entry number defined by the
	 * value in the indirect_addr.
	 */
#define TSU_CBLD_INDIRECT_WR_KICK_ADDR   0x00f04000L
#define TSU_CBLD_INDIRECT_WR_KICK_STRIDE 1
#define TSU_CBLD_INDIRECT_WR_KICK_DEPTH  128

	/*
	 * Head index register. Indirect register to write in order to get a
	 * consistent view of the complete descriptor. This is used along with the
	 * address and write register.
	 */
#define TSU_CBLD_INDIRECT_EQ_SW_INDEX_WR_ADDR   0x00f04080L
#define TSU_CBLD_INDIRECT_EQ_SW_INDEX_WR_STRIDE 1
#define TSU_CBLD_INDIRECT_EQ_SW_INDEX_WR_DEPTH  1

	/*
	 * Tail index register. Indirect register to write in order to get a
	 * consistent view of the complete descriptor. This is used along with the
	 * address and write register.
	 */
#define TSU_CBLD_INDIRECT_EQ_HW_INDEX_WR_ADDR   0x00f04081L
#define TSU_CBLD_INDIRECT_EQ_HW_INDEX_WR_STRIDE 1
#define TSU_CBLD_INDIRECT_EQ_HW_INDEX_WR_DEPTH  1

	/*
	 * MMU context and descriptor control register. Indirect register to write in
	 * order to get a consistent view of the complete descriptor. This is used
	 * along with the address and write register.
	 */
#define TSU_CBLD_INDIRECT_EQ_CTRL_WR_ADDR   0x00f04082L
#define TSU_CBLD_INDIRECT_EQ_CTRL_WR_STRIDE 1
#define TSU_CBLD_INDIRECT_EQ_CTRL_WR_DEPTH  1

	/*
	 * Base address register. Indirect register to write in order to get a
	 * consistent view of the complete descriptor. This is used along with the
	 * address and write register.
	 */
#define TSU_CBLD_INDIRECT_EQ_BASE_ADDR_WR_ADDR   0x00f04083L
#define TSU_CBLD_INDIRECT_EQ_BASE_ADDR_WR_STRIDE 1
#define TSU_CBLD_INDIRECT_EQ_BASE_ADDR_WR_DEPTH  1

	/*
	 * Max number of entries and sequence number register. Indirect register to
	 * write in order to get a consistent view of the complete descriptor. This
	 * is used along with the address and write register.
	 */
#define TSU_CBLD_INDIRECT_MMU_CONTEXT_WR_ADDR   0x00f04084L
#define TSU_CBLD_INDIRECT_MMU_CONTEXT_WR_STRIDE 1
#define TSU_CBLD_INDIRECT_MMU_CONTEXT_WR_DEPTH  1

	/*
	 * When this register is written to, the content of event queue entry in
	 * indirect_addr is written to indirect_eq_sw_index_rd,
	 * indirect_eq_hw_index_rd, indirect_eq_ctrl_rd, indirect_eq_base_addr_rd,
	 * indirect_eq_size_rd. These registers can now be read as one consistent
	 * register.
	 */
#define TSU_CBLD_INDIRECT_RD_KICK_ADDR   0x00f04100L
#define TSU_CBLD_INDIRECT_RD_KICK_STRIDE 1
#define TSU_CBLD_INDIRECT_RD_KICK_DEPTH  128

	/*
	 * Head index register. Indirect register to read in order to get a
	 * consistent view of the complete descriptor. This is used along with the
	 * address and read register.
	 */
#define TSU_CBLD_INDIRECT_EQ_SW_INDEX_RD_ADDR   0x00f04180L
#define TSU_CBLD_INDIRECT_EQ_SW_INDEX_RD_STRIDE 1
#define TSU_CBLD_INDIRECT_EQ_SW_INDEX_RD_DEPTH  1

	/*
	 * Tail index register. Indirect register to read in order to get a
	 * consistent view of the complete descriptor. This is used along with the
	 * address and read register.
	 */
#define TSU_CBLD_INDIRECT_EQ_HW_INDEX_RD_ADDR   0x00f04181L
#define TSU_CBLD_INDIRECT_EQ_HW_INDEX_RD_STRIDE 1
#define TSU_CBLD_INDIRECT_EQ_HW_INDEX_RD_DEPTH  1

	/*
	 * MMU context and descriptor control register. Indirect register to read in
	 * order to get a consistent view of the complete descriptor. This is used
	 * along with the address and write register.
	 */
#define TSU_CBLD_INDIRECT_EQ_CTRL_RD_ADDR   0x00f04182L
#define TSU_CBLD_INDIRECT_EQ_CTRL_RD_STRIDE 1
#define TSU_CBLD_INDIRECT_EQ_CTRL_RD_DEPTH  1

	/*
	 * Base address register. Indirect register to read in order to get a
	 * consistent view of the complete descriptor. This is used along with the
	 * address and read register.
	 */
#define TSU_CBLD_INDIRECT_EQ_BASE_ADDR_RD_ADDR   0x00f04183L
#define TSU_CBLD_INDIRECT_EQ_BASE_ADDR_RD_STRIDE 1
#define TSU_CBLD_INDIRECT_EQ_BASE_ADDR_RD_DEPTH  1

	/*
	 * Max number of entries and sequence number register. Indirect register to
	 * read in order to get a consistent view of the complete descriptor. This is
	 * used along with the address and read register.
	 */
#define TSU_CBLD_INDIRECT_MMU_CONTEXT_RD_ADDR   0x00f04184L
#define TSU_CBLD_INDIRECT_MMU_CONTEXT_RD_STRIDE 1
#define TSU_CBLD_INDIRECT_MMU_CONTEXT_RD_DEPTH  1

	/*
	 * Directly accessible software index. Software can update this directly
	 * without having to go through a staging read/write register.
	 */
#define TSU_CBLD_EQ_SW_INDEX_ADDR   0x00f04200L
#define TSU_CBLD_EQ_SW_INDEX_STRIDE 1
#define TSU_CBLD_EQ_SW_INDEX_DEPTH  128

	/*
	 * Directly accessible software index. Software can update this directly
	 * without having to go through a staging read/write register.
	 */
#define TSU_CBLD_EQ_HW_INDEX_ADDR   0x00f04280L
#define TSU_CBLD_EQ_HW_INDEX_STRIDE 1
#define TSU_CBLD_EQ_HW_INDEX_DEPTH  128

	/*
	 * Used for translating each vHCA's EQ number to the physical EQ number.
	 */
#define TSU_CBLD_EQ_MAPPING_TABLE_ADDR   0x00f04300L
#define TSU_CBLD_EQ_MAPPING_TABLE_STRIDE 1
#define TSU_CBLD_EQ_MAPPING_TABLE_DEPTH  34

	/* EQ Overflow Status 0 EQs 0-63 */
#define TSU_CBLD_EQ_OVERFLOW_STATUS_0_ADDR   0x00f04400L
#define TSU_CBLD_EQ_OVERFLOW_STATUS_0_STRIDE 1
#define TSU_CBLD_EQ_OVERFLOW_STATUS_0_DEPTH  1

	/* EQ Overflow Status 1 EQs 64-127 */
#define TSU_CBLD_EQ_OVERFLOW_STATUS_1_ADDR   0x00f04401L
#define TSU_CBLD_EQ_OVERFLOW_STATUS_1_STRIDE 1
#define TSU_CBLD_EQ_OVERFLOW_STATUS_1_DEPTH  1

	/* EQ Invalid Status 0 EQs 0-63 */
#define TSU_CBLD_EQ_INVALID_STATUS_0_ADDR   0x00f04402L
#define TSU_CBLD_EQ_INVALID_STATUS_0_STRIDE 1
#define TSU_CBLD_EQ_INVALID_STATUS_0_DEPTH  1

	/* EQ Invalid Status 1 EQs 64-127 */
#define TSU_CBLD_EQ_INVALID_STATUS_1_ADDR   0x00f04403L
#define TSU_CBLD_EQ_INVALID_STATUS_1_STRIDE 1
#define TSU_CBLD_EQ_INVALID_STATUS_1_DEPTH  1

	/* EQ out of range status */
#define TSU_CBLD_EQ_OUT_OF_RANGE_STATUS_ADDR   0x00f04404L
#define TSU_CBLD_EQ_OUT_OF_RANGE_STATUS_STRIDE 1
#define TSU_CBLD_EQ_OUT_OF_RANGE_STATUS_DEPTH  1

	/* Clear EQ Status 0 EQs 0-63 */
#define TSU_CBLD_CLEAR_EQ_STATUS_0_ADDR   0x00f04405L
#define TSU_CBLD_CLEAR_EQ_STATUS_0_STRIDE 1
#define TSU_CBLD_CLEAR_EQ_STATUS_0_DEPTH  1

	/* Clear EQ Status 1 EQs 64-127 */
#define TSU_CBLD_CLEAR_EQ_STATUS_1_ADDR   0x00f04406L
#define TSU_CBLD_CLEAR_EQ_STATUS_1_STRIDE 1
#define TSU_CBLD_CLEAR_EQ_STATUS_1_DEPTH  1

	/* Initiates clear of EQ status bits as indicated in Clear EQ Status 0/1. */
#define TSU_CBLD_CLEAR_EQ_STATUS_KICK_ADDR   0x00f04407L
#define TSU_CBLD_CLEAR_EQ_STATUS_KICK_STRIDE 1
#define TSU_CBLD_CLEAR_EQ_STATUS_KICK_DEPTH  1

	/* Clear per UF EQ out of range Status */
#define TSU_CBLD_CLEAR_EQ_UF_STATUS_ADDR   0x00f04408L
#define TSU_CBLD_CLEAR_EQ_UF_STATUS_STRIDE 1
#define TSU_CBLD_CLEAR_EQ_UF_STATUS_DEPTH  1

	/* Initiates clear of per UF out of range EQ status bits */
#define TSU_CBLD_CLEAR_EQ_UF_STATUS_KICK_ADDR   0x00f04409L
#define TSU_CBLD_CLEAR_EQ_UF_STATUS_KICK_STRIDE 1
#define TSU_CBLD_CLEAR_EQ_UF_STATUS_KICK_DEPTH  1

	/* Clear all counters having the bit set in the mask. */
#define TSU_CBLD_CLEAR_ERROR_COUNTERS_ADDR   0x00f08400L
#define TSU_CBLD_CLEAR_ERROR_COUNTERS_STRIDE 1
#define TSU_CBLD_CLEAR_ERROR_COUNTERS_DEPTH  1

	/* Clear all counters having the bit set in the mask. */
#define TSU_CBLD_CLEAR_ERROR_COUNTERS_KICK_ADDR   0x00f08401L
#define TSU_CBLD_CLEAR_ERROR_COUNTERS_KICK_STRIDE 1
#define TSU_CBLD_CLEAR_ERROR_COUNTERS_KICK_DEPTH  1

	/* Data from the diagnostic RAM. */
#define TSU_CBLD_DIAG_RAM_DATA_ADDR   0x00f0c000L
#define TSU_CBLD_DIAG_RAM_DATA_STRIDE 1
#define TSU_CBLD_DIAG_RAM_DATA_DEPTH  10

	/* Error counters. */
#define TSU_CBLD_ERROR_COUNTER_1_ADDR   0x00f10000L
#define TSU_CBLD_ERROR_COUNTER_1_STRIDE 1
#define TSU_CBLD_ERROR_COUNTER_1_DEPTH  34

	/* Error counters. */
#define TSU_CBLD_ERROR_COUNTER_2_ADDR   0x00f10040L
#define TSU_CBLD_ERROR_COUNTER_2_STRIDE 1
#define TSU_CBLD_ERROR_COUNTER_2_DEPTH  34

	/* Error counters. */
#define TSU_CBLD_ERROR_COUNTER_3_ADDR   0x00f10080L
#define TSU_CBLD_ERROR_COUNTER_3_STRIDE 1
#define TSU_CBLD_ERROR_COUNTER_3_DEPTH  34

	/* Error counters. */
#define TSU_CBLD_ERROR_COUNTER_4_ADDR   0x00f100c0L
#define TSU_CBLD_ERROR_COUNTER_4_STRIDE 1
#define TSU_CBLD_ERROR_COUNTER_4_DEPTH  34

	/* Error counters. */
#define TSU_CBLD_ERROR_COUNTER_5_ADDR   0x00f10100L
#define TSU_CBLD_ERROR_COUNTER_5_STRIDE 1
#define TSU_CBLD_ERROR_COUNTER_5_DEPTH  34

	/* Error counters. */
#define TSU_CBLD_ERROR_COUNTER_6_ADDR   0x00f10140L
#define TSU_CBLD_ERROR_COUNTER_6_STRIDE 1
#define TSU_CBLD_ERROR_COUNTER_6_DEPTH  34

	/* Error counters. */
#define TSU_CBLD_ERROR_COUNTER_7_ADDR   0x00f10180L
#define TSU_CBLD_ERROR_COUNTER_7_STRIDE 1
#define TSU_CBLD_ERROR_COUNTER_7_DEPTH  34

	/* Error counters. */
#define TSU_CBLD_ERROR_COUNTER_8_ADDR   0x00f101c0L
#define TSU_CBLD_ERROR_COUNTER_8_STRIDE 1
#define TSU_CBLD_ERROR_COUNTER_8_DEPTH  34

	/* Error counters. */
#define TSU_CBLD_ERROR_COUNTER_9_ADDR   0x00f10200L
#define TSU_CBLD_ERROR_COUNTER_9_STRIDE 1
#define TSU_CBLD_ERROR_COUNTER_9_DEPTH  34

	/* Error counters. */
#define TSU_CBLD_ERROR_COUNTER_10_ADDR   0x00f10240L
#define TSU_CBLD_ERROR_COUNTER_10_STRIDE 1
#define TSU_CBLD_ERROR_COUNTER_10_DEPTH  34

	/* Error counters. */
#define TSU_CBLD_ERROR_COUNTER_11_ADDR   0x00f10280L
#define TSU_CBLD_ERROR_COUNTER_11_STRIDE 1
#define TSU_CBLD_ERROR_COUNTER_11_DEPTH  34

	/* Error counters. */
#define TSU_CBLD_ERROR_COUNTER_0_ADDR   0x00f102c0L
#define TSU_CBLD_ERROR_COUNTER_0_STRIDE 1
#define TSU_CBLD_ERROR_COUNTER_0_DEPTH  34

	/*
	 * Clear TX offload error counters. This register has one bit per UF, and
	 * will clear the corresponding counter.
	 */
#define TSU_CBLD_TX_OFFLOAD_COUNTER_CLEAR_ADDR   0x00f107feL
#define TSU_CBLD_TX_OFFLOAD_COUNTER_CLEAR_STRIDE 1
#define TSU_CBLD_TX_OFFLOAD_COUNTER_CLEAR_DEPTH  1

	/*
	 * Clear TX offload error counters. This register has one bit per UF, and
	 * will clear the corresponding counter.
	 */
#define TSU_CBLD_TX_OFFLOAD_COUNTER_CLEAR_KICK_ADDR   0x00f107ffL
#define TSU_CBLD_TX_OFFLOAD_COUNTER_CLEAR_KICK_STRIDE 1
#define TSU_CBLD_TX_OFFLOAD_COUNTER_CLEAR_KICK_DEPTH  1

	/* TX offload error counters - there is one register per UF. */
#define TSU_CBLD_TX_OFFLOAD_COUNTER_ADDR   0x00f10800L
#define TSU_CBLD_TX_OFFLOAD_COUNTER_STRIDE 1
#define TSU_CBLD_TX_OFFLOAD_COUNTER_DEPTH  34

	/* Sent count per UF for completions and events. */
#define TSU_CBLD_EVENT_CQ_SENT_ADDR   0x00f10840L
#define TSU_CBLD_EVENT_CQ_SENT_STRIDE 1
#define TSU_CBLD_EVENT_CQ_SENT_DEPTH  34

#define IBU_P1_CNT1US_CNT124US_ADDR   0x01100001L
#define IBU_P1_CNT1US_CNT124US_STRIDE 1
#define IBU_P1_CNT1US_CNT124US_DEPTH  1

#define IBU_P1_CNT2MS_ADDR   0x01100002L
#define IBU_P1_CNT2MS_STRIDE 1
#define IBU_P1_CNT2MS_DEPTH  1

#define IBU_P1_CNT10MS_ADDR   0x01100003L
#define IBU_P1_CNT10MS_STRIDE 1
#define IBU_P1_CNT10MS_DEPTH  1

#define IBU_P1_CNT100MS_ADDR   0x01100004L
#define IBU_P1_CNT100MS_STRIDE 1
#define IBU_P1_CNT100MS_DEPTH  1

#define IBU_P1_CNT150MS_ADDR   0x01100005L
#define IBU_P1_CNT150MS_STRIDE 1
#define IBU_P1_CNT150MS_DEPTH  1

#define IBU_P1_CNT400MS_ADDR   0x01100006L
#define IBU_P1_CNT400MS_STRIDE 1
#define IBU_P1_CNT400MS_DEPTH  1

#define IBU_P1_SKP_TO_CNT_ADDR   0x01100007L
#define IBU_P1_SKP_TO_CNT_STRIDE 1
#define IBU_P1_SKP_TO_CNT_DEPTH  1

#define IBU_P1_TGT_VAL_ADDR   0x01100008L
#define IBU_P1_TGT_VAL_STRIDE 1
#define IBU_P1_TGT_VAL_DEPTH  1

#define IBU_P1_PHY_VCONFIG_ADDR   0x01100009L
#define IBU_P1_PHY_VCONFIG_STRIDE 1
#define IBU_P1_PHY_VCONFIG_DEPTH  1

#define IBU_P1_PHY_DISP_ERROR_CNT_ADDR   0x0110000aL
#define IBU_P1_PHY_DISP_ERROR_CNT_STRIDE 1
#define IBU_P1_PHY_DISP_ERROR_CNT_DEPTH  1

#define IBU_P1_PHY_CODE_ERROR_CNT_ADDR   0x0110000bL
#define IBU_P1_PHY_CODE_ERROR_CNT_STRIDE 1
#define IBU_P1_PHY_CODE_ERROR_CNT_DEPTH  1

#define IBU_P1_PHY_EVENT_LOG_ADDR   0x0110000cL
#define IBU_P1_PHY_EVENT_LOG_STRIDE 1
#define IBU_P1_PHY_EVENT_LOG_DEPTH  1

#define IBU_P1_PORT_TRAIN_FSM_ADDR   0x0110000dL
#define IBU_P1_PORT_TRAIN_FSM_STRIDE 1
#define IBU_P1_PORT_TRAIN_FSM_DEPTH  1

#define IBU_P1_PHY_TRAIN_SMTIMER_VS1_ADDR   0x0110000eL
#define IBU_P1_PHY_TRAIN_SMTIMER_VS1_STRIDE 1
#define IBU_P1_PHY_TRAIN_SMTIMER_VS1_DEPTH  1

#define IBU_P1_MASK_ADDR   0x0110000fL
#define IBU_P1_MASK_STRIDE 1
#define IBU_P1_MASK_DEPTH  1

#define IBU_P1_STATUS_ADDR   0x01100010L
#define IBU_P1_STATUS_STRIDE 1
#define IBU_P1_STATUS_DEPTH  1

#define IBU_P1_LINK_WIDTH_ENABLED_ADDR   0x01100011L
#define IBU_P1_LINK_WIDTH_ENABLED_STRIDE 1
#define IBU_P1_LINK_WIDTH_ENABLED_DEPTH  1

#define IBU_P1_LINK_WIDTH_SUPPORTED_ADDR   0x01100012L
#define IBU_P1_LINK_WIDTH_SUPPORTED_STRIDE 1
#define IBU_P1_LINK_WIDTH_SUPPORTED_DEPTH  1

#define IBU_P1_LINK_WIDTH_ACTIVE_ADDR   0x01100013L
#define IBU_P1_LINK_WIDTH_ACTIVE_STRIDE 1
#define IBU_P1_LINK_WIDTH_ACTIVE_DEPTH  1

#define IBU_P1_LINK_SPEED_SUPPORTED_ADDR   0x01100014L
#define IBU_P1_LINK_SPEED_SUPPORTED_STRIDE 1
#define IBU_P1_LINK_SPEED_SUPPORTED_DEPTH  1

#define IBU_P1_PORT_PHYSICAL_STATE_ADDR   0x01100015L
#define IBU_P1_PORT_PHYSICAL_STATE_STRIDE 1
#define IBU_P1_PORT_PHYSICAL_STATE_DEPTH  1

#define IBU_P1_LINK_DOWN_DEFAULT_STATE_ADDR   0x01100016L
#define IBU_P1_LINK_DOWN_DEFAULT_STATE_STRIDE 1
#define IBU_P1_LINK_DOWN_DEFAULT_STATE_DEPTH  1

#define IBU_P1_LINK_SPEED_ACTIVE_ADDR   0x01100017L
#define IBU_P1_LINK_SPEED_ACTIVE_STRIDE 1
#define IBU_P1_LINK_SPEED_ACTIVE_DEPTH  1

#define IBU_P1_LINK_SPEED_ENABLED_ADDR   0x01100018L
#define IBU_P1_LINK_SPEED_ENABLED_STRIDE 1
#define IBU_P1_LINK_SPEED_ENABLED_DEPTH  1

#define IBU_P1_PCPHY_CNT_RST_ADDR   0x01100019L
#define IBU_P1_PCPHY_CNT_RST_STRIDE 1
#define IBU_P1_PCPHY_CNT_RST_DEPTH  1

#define IBU_P1_PCPHY_CNT_LOAD_ADDR   0x0110001aL
#define IBU_P1_PCPHY_CNT_LOAD_STRIDE 1
#define IBU_P1_PCPHY_CNT_LOAD_DEPTH  1

#define IBU_P1_PCSYMB_ERR_CNT_ADDR   0x0110001bL
#define IBU_P1_PCSYMB_ERR_CNT_STRIDE 1
#define IBU_P1_PCSYMB_ERR_CNT_DEPTH  1

#define IBU_P1_PCLINK_ERR_REC_CNT_ADDR   0x0110001cL
#define IBU_P1_PCLINK_ERR_REC_CNT_STRIDE 1
#define IBU_P1_PCLINK_ERR_REC_CNT_DEPTH  1

#define IBU_P1_PCLINK_DOWNED_CNT_ADDR   0x0110001dL
#define IBU_P1_PCLINK_DOWNED_CNT_STRIDE 1
#define IBU_P1_PCLINK_DOWNED_CNT_DEPTH  1

#define IBU_P1_PCSYMB_ERR_CNT_LANE0_ADDR   0x0110001eL
#define IBU_P1_PCSYMB_ERR_CNT_LANE0_STRIDE 1
#define IBU_P1_PCSYMB_ERR_CNT_LANE0_DEPTH  1

#define IBU_P1_PCSYMB_ERR_CNT_LANE1_ADDR   0x0110001fL
#define IBU_P1_PCSYMB_ERR_CNT_LANE1_STRIDE 1
#define IBU_P1_PCSYMB_ERR_CNT_LANE1_DEPTH  1

#define IBU_P1_PCSYMB_ERR_CNT_LANE2_ADDR   0x01100020L
#define IBU_P1_PCSYMB_ERR_CNT_LANE2_STRIDE 1
#define IBU_P1_PCSYMB_ERR_CNT_LANE2_DEPTH  1

#define IBU_P1_PCSYMB_ERR_CNT_LANE3_ADDR   0x01100021L
#define IBU_P1_PCSYMB_ERR_CNT_LANE3_STRIDE 1
#define IBU_P1_PCSYMB_ERR_CNT_LANE3_DEPTH  1

#define IBU_P1_TS3_REV1_TT0_COUNTER_ADDR   0x01100022L
#define IBU_P1_TS3_REV1_TT0_COUNTER_STRIDE 1
#define IBU_P1_TS3_REV1_TT0_COUNTER_DEPTH  1

#define IBU_P1_TS3_REV1_TT1_COUNTER_ADDR   0x01100023L
#define IBU_P1_TS3_REV1_TT1_COUNTER_STRIDE 1
#define IBU_P1_TS3_REV1_TT1_COUNTER_DEPTH  1

#define IBU_P1_TS3_REV1_TT2_COUNTER_ADDR   0x01100024L
#define IBU_P1_TS3_REV1_TT2_COUNTER_STRIDE 1
#define IBU_P1_TS3_REV1_TT2_COUNTER_DEPTH  1

#define IBU_P1_TS3_REV1_TT3_COUNTER_ADDR   0x01100025L
#define IBU_P1_TS3_REV1_TT3_COUNTER_STRIDE 1
#define IBU_P1_TS3_REV1_TT3_COUNTER_DEPTH  1

#define IBU_P1_PHY_ALIGN_ERROR_CNT_ADDR   0x01100026L
#define IBU_P1_PHY_ALIGN_ERROR_CNT_STRIDE 1
#define IBU_P1_PHY_ALIGN_ERROR_CNT_DEPTH  1

#define IBU_P1_PHY_CNTRL_IN_PKT_ERROR_CNT_ADDR   0x01100027L
#define IBU_P1_PHY_CNTRL_IN_PKT_ERROR_CNT_STRIDE 1
#define IBU_P1_PHY_CNTRL_IN_PKT_ERROR_CNT_DEPTH  1

#define IBU_P1_PHY_PAD_ERROR_CNT_ADDR   0x01100028L
#define IBU_P1_PHY_PAD_ERROR_CNT_STRIDE 1
#define IBU_P1_PHY_PAD_ERROR_CNT_DEPTH  1

#define IBU_P1_PHY_EDR_FDR_CONFIG0_ADDR   0x01100029L
#define IBU_P1_PHY_EDR_FDR_CONFIG0_STRIDE 1
#define IBU_P1_PHY_EDR_FDR_CONFIG0_DEPTH  1

#define IBU_P1_PHY_EDR_FDR_CONFIG1_ADDR   0x0110002aL
#define IBU_P1_PHY_EDR_FDR_CONFIG1_STRIDE 1
#define IBU_P1_PHY_EDR_FDR_CONFIG1_DEPTH  1

#define IBU_P1_PHY_LEAKY_BKT_THRSH_ADDR   0x0110002bL
#define IBU_P1_PHY_LEAKY_BKT_THRSH_STRIDE 1
#define IBU_P1_PHY_LEAKY_BKT_THRSH_DEPTH  1

#define IBU_P1_RCV_TS3_STATUS_LOW_ADDR   0x0110002dL
#define IBU_P1_RCV_TS3_STATUS_LOW_STRIDE 1
#define IBU_P1_RCV_TS3_STATUS_LOW_DEPTH  1

#define IBU_P1_RCV_TS3_STATUS_HIGH_ADDR   0x0110002eL
#define IBU_P1_RCV_TS3_STATUS_HIGH_STRIDE 1
#define IBU_P1_RCV_TS3_STATUS_HIGH_DEPTH  1

#define IBU_P1_GUID0_ADDR   0x0110002fL
#define IBU_P1_GUID0_STRIDE 1
#define IBU_P1_GUID0_DEPTH  1

#define IBU_P1_GUID1_ADDR   0x01100030L
#define IBU_P1_GUID1_STRIDE 1
#define IBU_P1_GUID1_DEPTH  1

#define IBU_P1_PNUM_ADDR   0x01100031L
#define IBU_P1_PNUM_STRIDE 1
#define IBU_P1_PNUM_DEPTH  1

#define IBU_P1_CNT4MS_ADDR   0x01100032L
#define IBU_P1_CNT4MS_STRIDE 1
#define IBU_P1_CNT4MS_DEPTH  1

#define IBU_P1_CNT36MS_ADDR   0x01100033L
#define IBU_P1_CNT36MS_STRIDE 1
#define IBU_P1_CNT36MS_DEPTH  1

#define IBU_P1_PHY_TS3_CONFIG_ADDR   0x01100034L
#define IBU_P1_PHY_TS3_CONFIG_STRIDE 1
#define IBU_P1_PHY_TS3_CONFIG_DEPTH  1

#define IBU_P1_DDS_WINDOW_START_ADDR   0x01100035L
#define IBU_P1_DDS_WINDOW_START_STRIDE 1
#define IBU_P1_DDS_WINDOW_START_DEPTH  1

#define IBU_P1_DDS_WINDOW_END_ADDR   0x01100036L
#define IBU_P1_DDS_WINDOW_END_STRIDE 1
#define IBU_P1_DDS_WINDOW_END_DEPTH  1

#define IBU_P1_DDS_DEFAULT_WINDOW_END_ADDR   0x01100037L
#define IBU_P1_DDS_DEFAULT_WINDOW_END_STRIDE 1
#define IBU_P1_DDS_DEFAULT_WINDOW_END_DEPTH  1

#define IBU_P1_RX_TS3DDS_STATUS_ADDR   0x01100038L
#define IBU_P1_RX_TS3DDS_STATUS_STRIDE 1
#define IBU_P1_RX_TS3DDS_STATUS_DEPTH  1

#define IBU_P1_TX_TS3DDS_STATUS_ADDR   0x01100039L
#define IBU_P1_TX_TS3DDS_STATUS_STRIDE 1
#define IBU_P1_TX_TS3DDS_STATUS_DEPTH  1

#define IBU_P1_CNT16MS_ADDR   0x0110003aL
#define IBU_P1_CNT16MS_STRIDE 1
#define IBU_P1_CNT16MS_DEPTH  1

#define IBU_P1_CONF_TEST4MS_SCT_ADDR   0x0110003bL
#define IBU_P1_CONF_TEST4MS_SCT_STRIDE 1
#define IBU_P1_CONF_TEST4MS_SCT_DEPTH  1

#define IBU_P1_CONF_TEST16MS_SCT_ADDR   0x0110003cL
#define IBU_P1_CONF_TEST16MS_SCT_STRIDE 1
#define IBU_P1_CONF_TEST16MS_SCT_DEPTH  1

#define IBU_P1_LOCAL_ADDTEST_LIMIT_ADDR   0x0110003dL
#define IBU_P1_LOCAL_ADDTEST_LIMIT_STRIDE 1
#define IBU_P1_LOCAL_ADDTEST_LIMIT_DEPTH  1

#define IBU_P1_REMOTE_ADDTEST_LIMIT_ADDR   0x0110003eL
#define IBU_P1_REMOTE_ADDTEST_LIMIT_STRIDE 1
#define IBU_P1_REMOTE_ADDTEST_LIMIT_DEPTH  1

#define IBU_P1_TS3_REV1_TT4_COUNTER_ADDR   0x0110003fL
#define IBU_P1_TS3_REV1_TT4_COUNTER_STRIDE 1
#define IBU_P1_TS3_REV1_TT4_COUNTER_DEPTH  1

#define IBU_P1_TS3_REV1_TT5_COUNTER_ADDR   0x01100040L
#define IBU_P1_TS3_REV1_TT5_COUNTER_STRIDE 1
#define IBU_P1_TS3_REV1_TT5_COUNTER_DEPTH  1

#define IBU_P1_TS3_REV1_TT6_COUNTER_ADDR   0x01100041L
#define IBU_P1_TS3_REV1_TT6_COUNTER_STRIDE 1
#define IBU_P1_TS3_REV1_TT6_COUNTER_DEPTH  1

#define IBU_P1_TS3_REV1_TT7_COUNTER_ADDR   0x01100042L
#define IBU_P1_TS3_REV1_TT7_COUNTER_STRIDE 1
#define IBU_P1_TS3_REV1_TT7_COUNTER_DEPTH  1

#define IBU_P1_TS3_REV1_TT8_COUNTER_ADDR   0x01100043L
#define IBU_P1_TS3_REV1_TT8_COUNTER_STRIDE 1
#define IBU_P1_TS3_REV1_TT8_COUNTER_DEPTH  1

#define IBU_P1_TS3_REV1_TT9_COUNTER_ADDR   0x01100044L
#define IBU_P1_TS3_REV1_TT9_COUNTER_STRIDE 1
#define IBU_P1_TS3_REV1_TT9_COUNTER_DEPTH  1

#define IBU_P1_TS3_REV1_TT10_COUNTER_ADDR   0x01100045L
#define IBU_P1_TS3_REV1_TT10_COUNTER_STRIDE 1
#define IBU_P1_TS3_REV1_TT10_COUNTER_DEPTH  1

#define IBU_P1_TS3_REV1_TT11_COUNTER_ADDR   0x01100046L
#define IBU_P1_TS3_REV1_TT11_COUNTER_STRIDE 1
#define IBU_P1_TS3_REV1_TT11_COUNTER_DEPTH  1

#define IBU_P1_TS3_REV1_TT12_COUNTER_ADDR   0x01100047L
#define IBU_P1_TS3_REV1_TT12_COUNTER_STRIDE 1
#define IBU_P1_TS3_REV1_TT12_COUNTER_DEPTH  1

#define IBU_P1_TS3_REV1_TT13_COUNTER_ADDR   0x01100048L
#define IBU_P1_TS3_REV1_TT13_COUNTER_STRIDE 1
#define IBU_P1_TS3_REV1_TT13_COUNTER_DEPTH  1

#define IBU_P1_TS3_REV1_TT14_COUNTER_ADDR   0x01100049L
#define IBU_P1_TS3_REV1_TT14_COUNTER_STRIDE 1
#define IBU_P1_TS3_REV1_TT14_COUNTER_DEPTH  1

#define IBU_P1_TS3_REV1_TT15_COUNTER_ADDR   0x0110004aL
#define IBU_P1_TS3_REV1_TT15_COUNTER_STRIDE 1
#define IBU_P1_TS3_REV1_TT15_COUNTER_DEPTH  1

#define IBU_P1_CONF_TEST_LANE_ERROR_LIMIT_ADDR   0x0110004bL
#define IBU_P1_CONF_TEST_LANE_ERROR_LIMIT_STRIDE 1
#define IBU_P1_CONF_TEST_LANE_ERROR_LIMIT_DEPTH  1

#define IBU_P1_CONF_TEST_IDLE_LIMIT_ADDR   0x0110004cL
#define IBU_P1_CONF_TEST_IDLE_LIMIT_STRIDE 1
#define IBU_P1_CONF_TEST_IDLE_LIMIT_DEPTH  1

#define IBU_P1_CONF_TEST2MS_SCT_ADDR   0x0110004dL
#define IBU_P1_CONF_TEST2MS_SCT_STRIDE 1
#define IBU_P1_CONF_TEST2MS_SCT_DEPTH  1

#define IBU_P1_CNT100_MS_HBR_ADDR   0x0110004eL
#define IBU_P1_CNT100_MS_HBR_STRIDE 1
#define IBU_P1_CNT100_MS_HBR_DEPTH  1

#define IBU_P1_PMAEQULANE0_STATUS_ADDR   0x0110004fL
#define IBU_P1_PMAEQULANE0_STATUS_STRIDE 1
#define IBU_P1_PMAEQULANE0_STATUS_DEPTH  1

#define IBU_P1_PMAEQULANE1_STATUS_ADDR   0x01100050L
#define IBU_P1_PMAEQULANE1_STATUS_STRIDE 1
#define IBU_P1_PMAEQULANE1_STATUS_DEPTH  1

#define IBU_P1_PMAEQULANE2_STATUS_ADDR   0x01100051L
#define IBU_P1_PMAEQULANE2_STATUS_STRIDE 1
#define IBU_P1_PMAEQULANE2_STATUS_DEPTH  1

#define IBU_P1_PMAEQULANE3_STATUS_ADDR   0x01100052L
#define IBU_P1_PMAEQULANE3_STATUS_STRIDE 1
#define IBU_P1_PMAEQULANE3_STATUS_DEPTH  1

#define IBU_P1_PMADDSLANE0_STATUS_ADDR   0x01100053L
#define IBU_P1_PMADDSLANE0_STATUS_STRIDE 1
#define IBU_P1_PMADDSLANE0_STATUS_DEPTH  1

#define IBU_P1_PMADDSLANE1_STATUS_ADDR   0x01100054L
#define IBU_P1_PMADDSLANE1_STATUS_STRIDE 1
#define IBU_P1_PMADDSLANE1_STATUS_DEPTH  1

#define IBU_P1_PMADDSLANE2_STATUS_ADDR   0x01100055L
#define IBU_P1_PMADDSLANE2_STATUS_STRIDE 1
#define IBU_P1_PMADDSLANE2_STATUS_DEPTH  1

#define IBU_P1_PMADDSLANE3_STATUS_ADDR   0x01100056L
#define IBU_P1_PMADDSLANE3_STATUS_STRIDE 1
#define IBU_P1_PMADDSLANE3_STATUS_DEPTH  1

#define IBU_P1_PHY_EDPL_ERR0_ADDR   0x01100057L
#define IBU_P1_PHY_EDPL_ERR0_STRIDE 1
#define IBU_P1_PHY_EDPL_ERR0_DEPTH  1

#define IBU_P1_PHY_EDPL_ERR1_ADDR   0x01100058L
#define IBU_P1_PHY_EDPL_ERR1_STRIDE 1
#define IBU_P1_PHY_EDPL_ERR1_DEPTH  1

#define IBU_P1_PHY_EDPL_ERR2_ADDR   0x01100059L
#define IBU_P1_PHY_EDPL_ERR2_STRIDE 1
#define IBU_P1_PHY_EDPL_ERR2_DEPTH  1

#define IBU_P1_PHY_EDPL_ERR3_ADDR   0x0110005aL
#define IBU_P1_PHY_EDPL_ERR3_STRIDE 1
#define IBU_P1_PHY_EDPL_ERR3_DEPTH  1

#define IBU_P1_PHY_BLK_TYPE_ERR_ADDR   0x0110005bL
#define IBU_P1_PHY_BLK_TYPE_ERR_STRIDE 1
#define IBU_P1_PHY_BLK_TYPE_ERR_DEPTH  1

#define IBU_P1_PHY_BLK_EOP_ERR_ADDR   0x0110005cL
#define IBU_P1_PHY_BLK_EOP_ERR_STRIDE 1
#define IBU_P1_PHY_BLK_EOP_ERR_DEPTH  1

#define IBU_P1_PHY_CIN_PKT_ERR_ADDR   0x0110005dL
#define IBU_P1_PHY_CIN_PKT_ERR_STRIDE 1
#define IBU_P1_PHY_CIN_PKT_ERR_DEPTH  1

#define IBU_P1_PHY_SYN_HDR_ERR_ADDR   0x0110005eL
#define IBU_P1_PHY_SYN_HDR_ERR_STRIDE 1
#define IBU_P1_PHY_SYN_HDR_ERR_DEPTH  1

#define IBU_P1_PHY_PRBS_ERR0_ADDR   0x0110005fL
#define IBU_P1_PHY_PRBS_ERR0_STRIDE 1
#define IBU_P1_PHY_PRBS_ERR0_DEPTH  1

#define IBU_P1_PHY_PRBS_ERR1_ADDR   0x01100060L
#define IBU_P1_PHY_PRBS_ERR1_STRIDE 1
#define IBU_P1_PHY_PRBS_ERR1_DEPTH  1

#define IBU_P1_PHY_PRBS_ERR2_ADDR   0x01100061L
#define IBU_P1_PHY_PRBS_ERR2_STRIDE 1
#define IBU_P1_PHY_PRBS_ERR2_DEPTH  1

#define IBU_P1_PHY_PRBS_ERR3_ADDR   0x01100062L
#define IBU_P1_PHY_PRBS_ERR3_STRIDE 1
#define IBU_P1_PHY_PRBS_ERR3_DEPTH  1

#define IBU_P1_PHY_DESKEW_STATUS_ADDR   0x01100063L
#define IBU_P1_PHY_DESKEW_STATUS_STRIDE 1
#define IBU_P1_PHY_DESKEW_STATUS_DEPTH  1

#define IBU_P1_PHY_FECUNC_ERR0_ADDR   0x01100064L
#define IBU_P1_PHY_FECUNC_ERR0_STRIDE 1
#define IBU_P1_PHY_FECUNC_ERR0_DEPTH  1

#define IBU_P1_PHY_FECUNC_ERR1_ADDR   0x01100065L
#define IBU_P1_PHY_FECUNC_ERR1_STRIDE 1
#define IBU_P1_PHY_FECUNC_ERR1_DEPTH  1

#define IBU_P1_PHY_FECUNC_ERR2_ADDR   0x01100066L
#define IBU_P1_PHY_FECUNC_ERR2_STRIDE 1
#define IBU_P1_PHY_FECUNC_ERR2_DEPTH  1

#define IBU_P1_PHY_FECUNC_ERR3_ADDR   0x01100067L
#define IBU_P1_PHY_FECUNC_ERR3_STRIDE 1
#define IBU_P1_PHY_FECUNC_ERR3_DEPTH  1

#define IBU_P1_PHY_FECCOR_ERR0_ADDR   0x01100068L
#define IBU_P1_PHY_FECCOR_ERR0_STRIDE 1
#define IBU_P1_PHY_FECCOR_ERR0_DEPTH  1

#define IBU_P1_PHY_FECCOR_ERR1_ADDR   0x01100069L
#define IBU_P1_PHY_FECCOR_ERR1_STRIDE 1
#define IBU_P1_PHY_FECCOR_ERR1_DEPTH  1

#define IBU_P1_PHY_FECCOR_ERR2_ADDR   0x0110006aL
#define IBU_P1_PHY_FECCOR_ERR2_STRIDE 1
#define IBU_P1_PHY_FECCOR_ERR2_DEPTH  1

#define IBU_P1_PHY_FECCOR_ERR3_ADDR   0x0110006bL
#define IBU_P1_PHY_FECCOR_ERR3_STRIDE 1
#define IBU_P1_PHY_FECCOR_ERR3_DEPTH  1

#define IBU_P1_PHY_SMSTATUS_ADDR   0x0110006cL
#define IBU_P1_PHY_SMSTATUS_STRIDE 1
#define IBU_P1_PHY_SMSTATUS_DEPTH  1

#define IBU_P1_PHY_TS3_NEGOTIATED_STATUS_ADDR   0x0110006dL
#define IBU_P1_PHY_TS3_NEGOTIATED_STATUS_STRIDE 1
#define IBU_P1_PHY_TS3_NEGOTIATED_STATUS_DEPTH  1

#define IBU_P1_PHY_TEST_ADDR   0x0110006eL
#define IBU_P1_PHY_TEST_STRIDE 1
#define IBU_P1_PHY_TEST_DEPTH  1

#define IBU_P1_EDR_FDR_RX_STATUS_REG0_ADDR   0x0110006fL
#define IBU_P1_EDR_FDR_RX_STATUS_REG0_STRIDE 1
#define IBU_P1_EDR_FDR_RX_STATUS_REG0_DEPTH  1

#define IBU_P1_EDR_FDR_RX_STATUS_REG1_ADDR   0x01100070L
#define IBU_P1_EDR_FDR_RX_STATUS_REG1_STRIDE 1
#define IBU_P1_EDR_FDR_RX_STATUS_REG1_DEPTH  1

#define IBU_P1_EDR_FDR_RX_STATUS_REG2_ADDR   0x01100071L
#define IBU_P1_EDR_FDR_RX_STATUS_REG2_STRIDE 1
#define IBU_P1_EDR_FDR_RX_STATUS_REG2_DEPTH  1

#define IBU_P1_EDR_FDR_TX_STATUS_REG0_ADDR   0x01100072L
#define IBU_P1_EDR_FDR_TX_STATUS_REG0_STRIDE 1
#define IBU_P1_EDR_FDR_TX_STATUS_REG0_DEPTH  1

#define IBU_P1_INT_PRIORITY_ADDR   0x01100073L
#define IBU_P1_INT_PRIORITY_STRIDE 1
#define IBU_P1_INT_PRIORITY_DEPTH  1

#define IBU_P1_INT_FATAL_ADDR   0x01100074L
#define IBU_P1_INT_FATAL_STRIDE 1
#define IBU_P1_INT_FATAL_DEPTH  1

#define IBU_P1_LINK_ROUND_TRIP_LATENCY_ADDR   0x01100075L
#define IBU_P1_LINK_ROUND_TRIP_LATENCY_STRIDE 1
#define IBU_P1_LINK_ROUND_TRIP_LATENCY_DEPTH  1

#define IBU_P1_PHY_FORCE_LEGACY_MODE_ADDR   0x01100076L
#define IBU_P1_PHY_FORCE_LEGACY_MODE_STRIDE 1
#define IBU_P1_PHY_FORCE_LEGACY_MODE_DEPTH  1

#define IBU_P1_SERDES_BYPASS_ADDR   0x01100077L
#define IBU_P1_SERDES_BYPASS_STRIDE 1
#define IBU_P1_SERDES_BYPASS_DEPTH  1

#define IBU_P1_LID_ADDR   0x01100100L
#define IBU_P1_LID_STRIDE 1
#define IBU_P1_LID_DEPTH  1

#define IBU_P1_LMC_ADDR   0x01100101L
#define IBU_P1_LMC_STRIDE 1
#define IBU_P1_LMC_DEPTH  1

#define IBU_P1_PORT_STATE_ADDR   0x01100102L
#define IBU_P1_PORT_STATE_STRIDE 1
#define IBU_P1_PORT_STATE_DEPTH  1

#define IBU_P1_VLCAP_ADDR   0x01100103L
#define IBU_P1_VLCAP_STRIDE 1
#define IBU_P1_VLCAP_DEPTH  1

#define IBU_P1_NEIGHBOR_MTU_ADDR   0x01100104L
#define IBU_P1_NEIGHBOR_MTU_STRIDE 1
#define IBU_P1_NEIGHBOR_MTU_DEPTH  1

#define IBU_P1_VLHIGH_LIMIT_ADDR   0x01100105L
#define IBU_P1_VLHIGH_LIMIT_STRIDE 1
#define IBU_P1_VLHIGH_LIMIT_DEPTH  1

#define IBU_P1_VLARBITRATION_HIGH_CAP_ADDR   0x01100106L
#define IBU_P1_VLARBITRATION_HIGH_CAP_STRIDE 1
#define IBU_P1_VLARBITRATION_HIGH_CAP_DEPTH  1

#define IBU_P1_VLARBITRATION_LOW_CAP_ADDR   0x01100107L
#define IBU_P1_VLARBITRATION_LOW_CAP_STRIDE 1
#define IBU_P1_VLARBITRATION_LOW_CAP_DEPTH  1

#define IBU_P1_MTUCAP_ADDR   0x01100108L
#define IBU_P1_MTUCAP_STRIDE 1
#define IBU_P1_MTUCAP_DEPTH  1

#define IBU_P1_OPERATIONAL_VLS_ADDR   0x01100109L
#define IBU_P1_OPERATIONAL_VLS_STRIDE 1
#define IBU_P1_OPERATIONAL_VLS_DEPTH  1

#define IBU_P1_PCPORT_RCV_ERROR_ADDR   0x0110010cL
#define IBU_P1_PCPORT_RCV_ERROR_STRIDE 1
#define IBU_P1_PCPORT_RCV_ERROR_DEPTH  1

#define IBU_P1_PCPORT_RCV_REMOTE_PHYSICAL_ERRORS_ADDR   0x0110010dL
#define IBU_P1_PCPORT_RCV_REMOTE_PHYSICAL_ERRORS_STRIDE 1
#define IBU_P1_PCPORT_RCV_REMOTE_PHYSICAL_ERRORS_DEPTH  1

#define IBU_P1_PCPORT_XMIT_DISCARDS_ADDR   0x0110010eL
#define IBU_P1_PCPORT_XMIT_DISCARDS_STRIDE 1
#define IBU_P1_PCPORT_XMIT_DISCARDS_DEPTH  1

#define IBU_P1_PCLOCAL_LINK_INTEGRITY_ERRORS_ADDR   0x0110010fL
#define IBU_P1_PCLOCAL_LINK_INTEGRITY_ERRORS_STRIDE 1
#define IBU_P1_PCLOCAL_LINK_INTEGRITY_ERRORS_DEPTH  1

#define IBU_P1_PCEXCESSIVE_BUFFER_OVERRUN_ERRORS_ADDR   0x01100110L
#define IBU_P1_PCEXCESSIVE_BUFFER_OVERRUN_ERRORS_STRIDE 1
#define IBU_P1_PCEXCESSIVE_BUFFER_OVERRUN_ERRORS_DEPTH  1

#define IBU_P1_PCVL15_DROPPED_ADDR   0x01100111L
#define IBU_P1_PCVL15_DROPPED_STRIDE 1
#define IBU_P1_PCVL15_DROPPED_DEPTH  1

#define IBU_P1_PCPORT_XMIT_WAIT_ADDR   0x01100112L
#define IBU_P1_PCPORT_XMIT_WAIT_STRIDE 1
#define IBU_P1_PCPORT_XMIT_WAIT_DEPTH  1

#define IBU_P1_PCPORT_XMIT_DATA_LSQW_ADDR   0x01100113L
#define IBU_P1_PCPORT_XMIT_DATA_LSQW_STRIDE 1
#define IBU_P1_PCPORT_XMIT_DATA_LSQW_DEPTH  1

#define IBU_P1_LINK_ERROR_CHECK_ENABLE_ADDR   0x01100114L
#define IBU_P1_LINK_ERROR_CHECK_ENABLE_STRIDE 1
#define IBU_P1_LINK_ERROR_CHECK_ENABLE_DEPTH  1

#define IBU_P1_PCPORT_RCV_DATA_LSQW_ADDR   0x01100115L
#define IBU_P1_PCPORT_RCV_DATA_LSQW_STRIDE 1
#define IBU_P1_PCPORT_RCV_DATA_LSQW_DEPTH  1

#define IBU_P1_PCPORT_RCV_DATA_HSQW_ADDR   0x01100116L
#define IBU_P1_PCPORT_RCV_DATA_HSQW_STRIDE 1
#define IBU_P1_PCPORT_RCV_DATA_HSQW_DEPTH  1

#define IBU_P1_PCPORT_XMIT_PKTS_LSQW_ADDR   0x01100117L
#define IBU_P1_PCPORT_XMIT_PKTS_LSQW_STRIDE 1
#define IBU_P1_PCPORT_XMIT_PKTS_LSQW_DEPTH  1

#define IBU_P1_PCPORT_XMIT_PKTS_HSQW_ADDR   0x01100118L
#define IBU_P1_PCPORT_XMIT_PKTS_HSQW_STRIDE 1
#define IBU_P1_PCPORT_XMIT_PKTS_HSQW_DEPTH  1

#define IBU_P1_PCPORT_RCV_PKTS_LSQW_ADDR   0x01100119L
#define IBU_P1_PCPORT_RCV_PKTS_LSQW_STRIDE 1
#define IBU_P1_PCPORT_RCV_PKTS_LSQW_DEPTH  1

#define IBU_P1_PCPORT_RCV_PKTS_HSQW_ADDR   0x0110011aL
#define IBU_P1_PCPORT_RCV_PKTS_HSQW_STRIDE 1
#define IBU_P1_PCPORT_RCV_PKTS_HSQW_DEPTH  1

#define IBU_P1_PCPORT_UCXMIT_PKTS_LSQW_ADDR   0x0110011bL
#define IBU_P1_PCPORT_UCXMIT_PKTS_LSQW_STRIDE 1
#define IBU_P1_PCPORT_UCXMIT_PKTS_LSQW_DEPTH  1

#define IBU_P1_PCPORT_UCXMIT_PKTS_HSQW_ADDR   0x0110011cL
#define IBU_P1_PCPORT_UCXMIT_PKTS_HSQW_STRIDE 1
#define IBU_P1_PCPORT_UCXMIT_PKTS_HSQW_DEPTH  1

#define IBU_P1_PCPORT_MCXMIT_PKTS_LSQW_ADDR   0x0110011dL
#define IBU_P1_PCPORT_MCXMIT_PKTS_LSQW_STRIDE 1
#define IBU_P1_PCPORT_MCXMIT_PKTS_LSQW_DEPTH  1

#define IBU_P1_PCPORT_MCXMIT_PKTS_HSQW_ADDR   0x0110011eL
#define IBU_P1_PCPORT_MCXMIT_PKTS_HSQW_STRIDE 1
#define IBU_P1_PCPORT_MCXMIT_PKTS_HSQW_DEPTH  1

#define IBU_P1_PCPORT_UCRCV_PKTS_LSQW_ADDR   0x0110011fL
#define IBU_P1_PCPORT_UCRCV_PKTS_LSQW_STRIDE 1
#define IBU_P1_PCPORT_UCRCV_PKTS_LSQW_DEPTH  1

#define IBU_P1_PCPORT_UCRCV_PKTS_HSQW_ADDR   0x01100120L
#define IBU_P1_PCPORT_UCRCV_PKTS_HSQW_STRIDE 1
#define IBU_P1_PCPORT_UCRCV_PKTS_HSQW_DEPTH  1

#define IBU_P1_PCPORT_MCRCV_PKTS_LSQW_ADDR   0x01100121L
#define IBU_P1_PCPORT_MCRCV_PKTS_LSQW_STRIDE 1
#define IBU_P1_PCPORT_MCRCV_PKTS_LSQW_DEPTH  1

#define IBU_P1_PCPORT_MCRCV_PKTS_HSQW_ADDR   0x01100122L
#define IBU_P1_PCPORT_MCRCV_PKTS_HSQW_STRIDE 1
#define IBU_P1_PCPORT_MCRCV_PKTS_HSQW_DEPTH  1

#define IBU_P1_PCPORT_XMIT_WAIT_VL0_ADDR   0x01100123L
#define IBU_P1_PCPORT_XMIT_WAIT_VL0_STRIDE 1
#define IBU_P1_PCPORT_XMIT_WAIT_VL0_DEPTH  1

#define IBU_P1_PCPORT_XMIT_WAIT_VL1_ADDR   0x01100124L
#define IBU_P1_PCPORT_XMIT_WAIT_VL1_STRIDE 1
#define IBU_P1_PCPORT_XMIT_WAIT_VL1_DEPTH  1

#define IBU_P1_PCPORT_XMIT_WAIT_VL2_ADDR   0x01100125L
#define IBU_P1_PCPORT_XMIT_WAIT_VL2_STRIDE 1
#define IBU_P1_PCPORT_XMIT_WAIT_VL2_DEPTH  1

#define IBU_P1_PCPORT_XMIT_WAIT_VL3_ADDR   0x01100126L
#define IBU_P1_PCPORT_XMIT_WAIT_VL3_STRIDE 1
#define IBU_P1_PCPORT_XMIT_WAIT_VL3_DEPTH  1

#define IBU_P1_PCPORT_XMIT_WAIT_VL4_ADDR   0x01100127L
#define IBU_P1_PCPORT_XMIT_WAIT_VL4_STRIDE 1
#define IBU_P1_PCPORT_XMIT_WAIT_VL4_DEPTH  1

#define IBU_P1_PCPORT_XMIT_WAIT_VL5_ADDR   0x01100128L
#define IBU_P1_PCPORT_XMIT_WAIT_VL5_STRIDE 1
#define IBU_P1_PCPORT_XMIT_WAIT_VL5_DEPTH  1

#define IBU_P1_PCPORT_XMIT_WAIT_VL6_ADDR   0x01100129L
#define IBU_P1_PCPORT_XMIT_WAIT_VL6_STRIDE 1
#define IBU_P1_PCPORT_XMIT_WAIT_VL6_DEPTH  1

#define IBU_P1_PCPORT_XMIT_WAIT_VL7_ADDR   0x0110012aL
#define IBU_P1_PCPORT_XMIT_WAIT_VL7_STRIDE 1
#define IBU_P1_PCPORT_XMIT_WAIT_VL7_DEPTH  1

#define IBU_P1_PCPORT_XMIT_WAIT_VL15_ADDR   0x0110012bL
#define IBU_P1_PCPORT_XMIT_WAIT_VL15_STRIDE 1
#define IBU_P1_PCPORT_XMIT_WAIT_VL15_DEPTH  1

#define IBU_P1_PCRX_LINK_CNT_RST_ADDR   0x0110012cL
#define IBU_P1_PCRX_LINK_CNT_RST_STRIDE 1
#define IBU_P1_PCRX_LINK_CNT_RST_DEPTH  1

#define IBU_P1_PCRX_LINK_CNT_LOAD_ADDR   0x0110012dL
#define IBU_P1_PCRX_LINK_CNT_LOAD_STRIDE 1
#define IBU_P1_PCRX_LINK_CNT_LOAD_DEPTH  1

#define IBU_P1_LOCAL_PHY_ERRORS_ADDR   0x0110012eL
#define IBU_P1_LOCAL_PHY_ERRORS_STRIDE 1
#define IBU_P1_LOCAL_PHY_ERRORS_DEPTH  1

#define IBU_P1_OVERRUN_ERRORS_ADDR   0x0110012fL
#define IBU_P1_OVERRUN_ERRORS_STRIDE 1
#define IBU_P1_OVERRUN_ERRORS_DEPTH  1

#define IBU_P1_PSLINK_DLID_ADDR   0x01100130L
#define IBU_P1_PSLINK_DLID_STRIDE 1
#define IBU_P1_PSLINK_DLID_DEPTH  1

#define IBU_P1_PSTICK_ADDR   0x01100131L
#define IBU_P1_PSTICK_STRIDE 1
#define IBU_P1_PSTICK_DEPTH  1

#define IBU_P1_PSSTATUS_ADDR   0x01100132L
#define IBU_P1_PSSTATUS_STRIDE 1
#define IBU_P1_PSSTATUS_DEPTH  1

#define IBU_P1_PSSTART_DELAY_ADDR   0x01100133L
#define IBU_P1_PSSTART_DELAY_STRIDE 1
#define IBU_P1_PSSTART_DELAY_DEPTH  1

#define IBU_P1_PSINTERVAL_ADDR   0x01100134L
#define IBU_P1_PSINTERVAL_STRIDE 1
#define IBU_P1_PSINTERVAL_DEPTH  1

#define IBU_P1_PSCNT_SEL0_ADDR   0x01100135L
#define IBU_P1_PSCNT_SEL0_STRIDE 1
#define IBU_P1_PSCNT_SEL0_DEPTH  1

#define IBU_P1_PSCNT_SEL1_ADDR   0x01100136L
#define IBU_P1_PSCNT_SEL1_STRIDE 1
#define IBU_P1_PSCNT_SEL1_DEPTH  1

#define IBU_P1_PSCNT_SEL2_ADDR   0x01100137L
#define IBU_P1_PSCNT_SEL2_STRIDE 1
#define IBU_P1_PSCNT_SEL2_DEPTH  1

#define IBU_P1_PSCNT_SEL3_ADDR   0x01100138L
#define IBU_P1_PSCNT_SEL3_STRIDE 1
#define IBU_P1_PSCNT_SEL3_DEPTH  1

#define IBU_P1_PSCNT0_ADDR   0x01100139L
#define IBU_P1_PSCNT0_STRIDE 1
#define IBU_P1_PSCNT0_DEPTH  1

#define IBU_P1_PSCNT1_ADDR   0x0110013aL
#define IBU_P1_PSCNT1_STRIDE 1
#define IBU_P1_PSCNT1_DEPTH  1

#define IBU_P1_PSCNT2_ADDR   0x0110013bL
#define IBU_P1_PSCNT2_STRIDE 1
#define IBU_P1_PSCNT2_DEPTH  1

#define IBU_P1_PSCNT3_ADDR   0x0110013cL
#define IBU_P1_PSCNT3_STRIDE 1
#define IBU_P1_PSCNT3_DEPTH  1

#define IBU_P1_PSINIT_SAMPLING_ADDR   0x0110013dL
#define IBU_P1_PSINIT_SAMPLING_STRIDE 1
#define IBU_P1_PSINIT_SAMPLING_DEPTH  1

#define IBU_P1_PSCNT_LOAD_ADDR   0x0110013eL
#define IBU_P1_PSCNT_LOAD_STRIDE 1
#define IBU_P1_PSCNT_LOAD_DEPTH  1

#define IBU_P1_PORT_STATE_CHANGE_ADDR   0x0110013fL
#define IBU_P1_PORT_STATE_CHANGE_STRIDE 1
#define IBU_P1_PORT_STATE_CHANGE_DEPTH  1

#define IBU_P1_LINK_VCONFIG0_ADDR   0x01100141L
#define IBU_P1_LINK_VCONFIG0_STRIDE 1
#define IBU_P1_LINK_VCONFIG0_DEPTH  1

#define IBU_P1_LINK_VCONFIG1_ADDR   0x01100142L
#define IBU_P1_LINK_VCONFIG1_STRIDE 1
#define IBU_P1_LINK_VCONFIG1_DEPTH  1

#define IBU_P1_LINK_VCONFIG2_ADDR   0x01100143L
#define IBU_P1_LINK_VCONFIG2_STRIDE 1
#define IBU_P1_LINK_VCONFIG2_DEPTH  1

#define IBU_P1_LINK_RX_CREDIT_VL1_0_ADDR   0x01100144L
#define IBU_P1_LINK_RX_CREDIT_VL1_0_STRIDE 1
#define IBU_P1_LINK_RX_CREDIT_VL1_0_DEPTH  1

#define IBU_P1_LINK_RX_CREDIT_VL3_2_ADDR   0x01100145L
#define IBU_P1_LINK_RX_CREDIT_VL3_2_STRIDE 1
#define IBU_P1_LINK_RX_CREDIT_VL3_2_DEPTH  1

#define IBU_P1_LINK_RX_CREDIT_VL5_4_ADDR   0x01100146L
#define IBU_P1_LINK_RX_CREDIT_VL5_4_STRIDE 1
#define IBU_P1_LINK_RX_CREDIT_VL5_4_DEPTH  1

#define IBU_P1_LINK_RX_CREDIT_VL7_6_ADDR   0x01100147L
#define IBU_P1_LINK_RX_CREDIT_VL7_6_STRIDE 1
#define IBU_P1_LINK_RX_CREDIT_VL7_6_DEPTH  1

#define IBU_P1_LINK_TX_CREDIT_VL1_0_ADDR   0x01100148L
#define IBU_P1_LINK_TX_CREDIT_VL1_0_STRIDE 1
#define IBU_P1_LINK_TX_CREDIT_VL1_0_DEPTH  1

#define IBU_P1_LINK_TX_CREDIT_VL3_2_ADDR   0x01100149L
#define IBU_P1_LINK_TX_CREDIT_VL3_2_STRIDE 1
#define IBU_P1_LINK_TX_CREDIT_VL3_2_DEPTH  1

#define IBU_P1_LINK_TX_CREDIT_VL5_4_ADDR   0x0110014aL
#define IBU_P1_LINK_TX_CREDIT_VL5_4_STRIDE 1
#define IBU_P1_LINK_TX_CREDIT_VL5_4_DEPTH  1

#define IBU_P1_LINK_TX_CREDIT_VL7_6_ADDR   0x0110014bL
#define IBU_P1_LINK_TX_CREDIT_VL7_6_STRIDE 1
#define IBU_P1_LINK_TX_CREDIT_VL7_6_DEPTH  1

#define IBU_P1_PCTX_LINK_CNT_RST_ADDR   0x0110014cL
#define IBU_P1_PCTX_LINK_CNT_RST_STRIDE 1
#define IBU_P1_PCTX_LINK_CNT_RST_DEPTH  1

#define IBU_P1_PCTX_LINK_CNT_LOAD_ADDR   0x0110014dL
#define IBU_P1_PCTX_LINK_CNT_LOAD_STRIDE 1
#define IBU_P1_PCTX_LINK_CNT_LOAD_DEPTH  1

#define IBU_P1_PSCNT_WIDTH_ADDR   0x0110014fL
#define IBU_P1_PSCNT_WIDTH_STRIDE 1
#define IBU_P1_PSCNT_WIDTH_DEPTH  1

#define IBU_P1_PSCNT_MASK_ADDR   0x01100150L
#define IBU_P1_PSCNT_MASK_STRIDE 1
#define IBU_P1_PSCNT_MASK_DEPTH  1

#define IBU_P1_PCICRC_RCV_ERRORS_ADDR   0x01100151L
#define IBU_P1_PCICRC_RCV_ERRORS_STRIDE 1
#define IBU_P1_PCICRC_RCV_ERRORS_DEPTH  1

#define IBU_P1_PCVCRC_RCV_ERRORS_ADDR   0x01100152L
#define IBU_P1_PCVCRC_RCV_ERRORS_STRIDE 1
#define IBU_P1_PCVCRC_RCV_ERRORS_DEPTH  1

#define IBU_P1_PCLEN_RCV_ERRORS_ADDR   0x01100153L
#define IBU_P1_PCLEN_RCV_ERRORS_STRIDE 1
#define IBU_P1_PCLEN_RCV_ERRORS_DEPTH  1

#define IBU_P1_PCDLID_RCV_ERRORS_ADDR   0x01100154L
#define IBU_P1_PCDLID_RCV_ERRORS_STRIDE 1
#define IBU_P1_PCDLID_RCV_ERRORS_DEPTH  1

#define IBU_P1_PCRCV_FCLEN_ERRORS_ADDR   0x01100155L
#define IBU_P1_PCRCV_FCLEN_ERRORS_STRIDE 1
#define IBU_P1_PCRCV_FCLEN_ERRORS_DEPTH  1

#define IBU_P1_PCRCV_FCVL_ERRORS_ADDR   0x01100156L
#define IBU_P1_PCRCV_FCVL_ERRORS_STRIDE 1
#define IBU_P1_PCRCV_FCVL_ERRORS_DEPTH  1

#define IBU_P1_PCRCV_FCCRC_ERRORS_ADDR   0x01100157L
#define IBU_P1_PCRCV_FCCRC_ERRORS_STRIDE 1
#define IBU_P1_PCRCV_FCCRC_ERRORS_DEPTH  1

#define IBU_P1_PORT_LOCAL_PHYSICAL_ERRORS_ADDR   0x01100158L
#define IBU_P1_PORT_LOCAL_PHYSICAL_ERRORS_STRIDE 1
#define IBU_P1_PORT_LOCAL_PHYSICAL_ERRORS_DEPTH  1

#define IBU_P1_PCMAL_FORMED_ERRORS_ADDR   0x01100159L
#define IBU_P1_PCMAL_FORMED_ERRORS_STRIDE 1
#define IBU_P1_PCMAL_FORMED_ERRORS_DEPTH  1

#define IBU_P1_PCBUF_OVER_ERRORS_ADDR   0x0110015aL
#define IBU_P1_PCBUF_OVER_ERRORS_STRIDE 1
#define IBU_P1_PCBUF_OVER_ERRORS_DEPTH  1

#define IBU_P1_PCVLMAP_ERRORS_ADDR   0x0110015bL
#define IBU_P1_PCVLMAP_ERRORS_STRIDE 1
#define IBU_P1_PCVLMAP_ERRORS_DEPTH  1

#define IBU_P1_PCVLINIT_CREDIT_VL1_VL0_ADDR   0x0110015cL
#define IBU_P1_PCVLINIT_CREDIT_VL1_VL0_STRIDE 1
#define IBU_P1_PCVLINIT_CREDIT_VL1_VL0_DEPTH  1

#define IBU_P1_PCVLINIT_CREDIT_VL3_VL2_ADDR   0x0110015dL
#define IBU_P1_PCVLINIT_CREDIT_VL3_VL2_STRIDE 1
#define IBU_P1_PCVLINIT_CREDIT_VL3_VL2_DEPTH  1

#define IBU_P1_PCVLINIT_CREDIT_VL5_VL4_ADDR   0x0110015eL
#define IBU_P1_PCVLINIT_CREDIT_VL5_VL4_STRIDE 1
#define IBU_P1_PCVLINIT_CREDIT_VL5_VL4_DEPTH  1

#define IBU_P1_PCVLINIT_CREDIT_VL7_VL6_ADDR   0x0110015fL
#define IBU_P1_PCVLINIT_CREDIT_VL7_VL6_STRIDE 1
#define IBU_P1_PCVLINIT_CREDIT_VL7_VL6_DEPTH  1

#define IBU_P1_PCRX_VL07_ECC_COR_ERR_CNT_ADDR   0x01100160L
#define IBU_P1_PCRX_VL07_ECC_COR_ERR_CNT_STRIDE 1
#define IBU_P1_PCRX_VL07_ECC_COR_ERR_CNT_DEPTH  1

#define IBU_P1_PCRX_VL07_ECC_UNC_ERR_CNT_ADDR   0x01100161L
#define IBU_P1_PCRX_VL07_ECC_UNC_ERR_CNT_STRIDE 1
#define IBU_P1_PCRX_VL07_ECC_UNC_ERR_CNT_DEPTH  1

#define IBU_P1_PCRX_VL15_ECC_COR_ERR_CNT_ADDR   0x01100162L
#define IBU_P1_PCRX_VL15_ECC_COR_ERR_CNT_STRIDE 1
#define IBU_P1_PCRX_VL15_ECC_COR_ERR_CNT_DEPTH  1

#define IBU_P1_PCRX_VL15_ECC_UNC_ERR_CNT_ADDR   0x01100163L
#define IBU_P1_PCRX_VL15_ECC_UNC_ERR_CNT_STRIDE 1
#define IBU_P1_PCRX_VL15_ECC_UNC_ERR_CNT_DEPTH  1

#define IBU_P1_PCRX_LOOP_ECC_COR_ERR_CNT_ADDR   0x01100164L
#define IBU_P1_PCRX_LOOP_ECC_COR_ERR_CNT_STRIDE 1
#define IBU_P1_PCRX_LOOP_ECC_COR_ERR_CNT_DEPTH  1

#define IBU_P1_PCRX_LOOP_ECC_UNC_ERR_CNT_ADDR   0x01100165L
#define IBU_P1_PCRX_LOOP_ECC_UNC_ERR_CNT_STRIDE 1
#define IBU_P1_PCRX_LOOP_ECC_UNC_ERR_CNT_DEPTH  1

#define IBU_P1_PCECCENA_ERR_ADDR   0x01100166L
#define IBU_P1_PCECCENA_ERR_STRIDE 1
#define IBU_P1_PCECCENA_ERR_DEPTH  1

#define IBU_P1_PCTX_ECC_COR_ERR_CNT_ADDR   0x01100167L
#define IBU_P1_PCTX_ECC_COR_ERR_CNT_STRIDE 1
#define IBU_P1_PCTX_ECC_COR_ERR_CNT_DEPTH  1

#define IBU_P1_PCTX_ECC_UNC_ERR_CNT_ADDR   0x01100168L
#define IBU_P1_PCTX_ECC_UNC_ERR_CNT_STRIDE 1
#define IBU_P1_PCTX_ECC_UNC_ERR_CNT_DEPTH  1

#define IBU_P1_TX_SRAMSTATUS_ADDR   0x01100169L
#define IBU_P1_TX_SRAMSTATUS_STRIDE 1
#define IBU_P1_TX_SRAMSTATUS_DEPTH  1

#define IBU_P1_TX_CACHE_STATUS_ADDR   0x0110016aL
#define IBU_P1_TX_CACHE_STATUS_STRIDE 1
#define IBU_P1_TX_CACHE_STATUS_DEPTH  1

#define IBU_P1_TX_DEBUG_ADDR   0x0110016bL
#define IBU_P1_TX_DEBUG_STRIDE 1
#define IBU_P1_TX_DEBUG_DEPTH  1

#define IBU_P1_RX_VL07_SRAMSTATUS_ADDR   0x0110016cL
#define IBU_P1_RX_VL07_SRAMSTATUS_STRIDE 1
#define IBU_P1_RX_VL07_SRAMSTATUS_DEPTH  1

#define IBU_P1_RX_VL15_SRAMSTATUS_ADDR   0x0110016dL
#define IBU_P1_RX_VL15_SRAMSTATUS_STRIDE 1
#define IBU_P1_RX_VL15_SRAMSTATUS_DEPTH  1

#define IBU_P1_LOOPSRAMSTATUS_ADDR   0x0110016eL
#define IBU_P1_LOOPSRAMSTATUS_STRIDE 1
#define IBU_P1_LOOPSRAMSTATUS_DEPTH  1

#define IBU_P1_RX_DEBUG_ADDR   0x0110016fL
#define IBU_P1_RX_DEBUG_STRIDE 1
#define IBU_P1_RX_DEBUG_DEPTH  1

#define IBU_P1_TX_ARB_LOOPBACK_SRAMSTATUS_ADDR   0x01100170L
#define IBU_P1_TX_ARB_LOOPBACK_SRAMSTATUS_STRIDE 1
#define IBU_P1_TX_ARB_LOOPBACK_SRAMSTATUS_DEPTH  1

#define IBU_P1_REMOTE_RX_BUFF_LIMIT_ADDR   0x01100171L
#define IBU_P1_REMOTE_RX_BUFF_LIMIT_STRIDE 1
#define IBU_P1_REMOTE_RX_BUFF_LIMIT_DEPTH  1

#define IBU_P1_FCTX_TIMER_ADDR   0x01100172L
#define IBU_P1_FCTX_TIMER_STRIDE 1
#define IBU_P1_FCTX_TIMER_DEPTH  1

#define IBU_P1_FCRX_TIMER_ADDR   0x01100173L
#define IBU_P1_FCRX_TIMER_STRIDE 1
#define IBU_P1_FCRX_TIMER_DEPTH  1

#define IBU_P1_PCPORT_XMIT_DATA_HSQW_ADDR   0x01100174L
#define IBU_P1_PCPORT_XMIT_DATA_HSQW_STRIDE 1
#define IBU_P1_PCPORT_XMIT_DATA_HSQW_DEPTH  1

#define IBU_P1_PCPORT_XMIT_VLDISCARDS_ADDR   0x01100175L
#define IBU_P1_PCPORT_XMIT_VLDISCARDS_STRIDE 1
#define IBU_P1_PCPORT_XMIT_VLDISCARDS_DEPTH  1

#define IBU_P1_PCPORT_COL_LIMIT_ADDR   0x01100176L
#define IBU_P1_PCPORT_COL_LIMIT_STRIDE 1
#define IBU_P1_PCPORT_COL_LIMIT_DEPTH  1

#define IBU_P1_VLARB_HI_PRI_TABLE_ADDR   0x01100180L
#define IBU_P1_VLARB_HI_PRI_TABLE_STRIDE 1
#define IBU_P1_VLARB_HI_PRI_TABLE_DEPTH  10

#define IBU_P1_VLARB_LO_PRI_TABLE_ADDR   0x011001c0L
#define IBU_P1_VLARB_LO_PRI_TABLE_STRIDE 1
#define IBU_P1_VLARB_LO_PRI_TABLE_DEPTH  10

#define IBU_P1_TX_TBSVL10_ADDR   0x011001d0L
#define IBU_P1_TX_TBSVL10_STRIDE 1
#define IBU_P1_TX_TBSVL10_DEPTH  1

#define IBU_P1_TX_TBSVL32_ADDR   0x011001d1L
#define IBU_P1_TX_TBSVL32_STRIDE 1
#define IBU_P1_TX_TBSVL32_DEPTH  1

#define IBU_P1_TX_TBSVL54_ADDR   0x011001d2L
#define IBU_P1_TX_TBSVL54_STRIDE 1
#define IBU_P1_TX_TBSVL54_DEPTH  1

#define IBU_P1_TX_TBSVL76_ADDR   0x011001d3L
#define IBU_P1_TX_TBSVL76_STRIDE 1
#define IBU_P1_TX_TBSVL76_DEPTH  1

#define IBU_P1_TX_TBSARB_VL10_ADDR   0x011001d4L
#define IBU_P1_TX_TBSARB_VL10_STRIDE 1
#define IBU_P1_TX_TBSARB_VL10_DEPTH  1

#define IBU_P1_TX_TBSARB_VL32_ADDR   0x011001d5L
#define IBU_P1_TX_TBSARB_VL32_STRIDE 1
#define IBU_P1_TX_TBSARB_VL32_DEPTH  1

#define IBU_P1_TX_TBSARB_VL54_ADDR   0x011001d6L
#define IBU_P1_TX_TBSARB_VL54_STRIDE 1
#define IBU_P1_TX_TBSARB_VL54_DEPTH  1

#define IBU_P1_TX_TBSARB_VL76_ADDR   0x011001d7L
#define IBU_P1_TX_TBSARB_VL76_STRIDE 1
#define IBU_P1_TX_TBSARB_VL76_DEPTH  1

#define IBU_P1_RX_TRACE_CAPTURE_ENABLE_ADDR   0x011001d8L
#define IBU_P1_RX_TRACE_CAPTURE_ENABLE_STRIDE 1
#define IBU_P1_RX_TRACE_CAPTURE_ENABLE_DEPTH  1

#define IBU_P1_RX_TRACE_CAPTURE_MODE_ADDR   0x011001d9L
#define IBU_P1_RX_TRACE_CAPTURE_MODE_STRIDE 1
#define IBU_P1_RX_TRACE_CAPTURE_MODE_DEPTH  1

#define IBU_P1_RX_TRACE_CAPTURE_RDY_ADDR   0x011001daL
#define IBU_P1_RX_TRACE_CAPTURE_RDY_STRIDE 1
#define IBU_P1_RX_TRACE_CAPTURE_RDY_DEPTH  1

#define IBU_P1_RX_TRACE_CAPTURE_TIMER_ADDR   0x011001dbL
#define IBU_P1_RX_TRACE_CAPTURE_TIMER_STRIDE 1
#define IBU_P1_RX_TRACE_CAPTURE_TIMER_DEPTH  1

#define IBU_P1_RX_TRACE_CAPTURE_START_ADDR   0x011001dcL
#define IBU_P1_RX_TRACE_CAPTURE_START_STRIDE 1
#define IBU_P1_RX_TRACE_CAPTURE_START_DEPTH  1

#define IBU_P1_RX_TRACE_CAPTURE_DATA1_ADDR   0x011001e0L
#define IBU_P1_RX_TRACE_CAPTURE_DATA1_STRIDE 1
#define IBU_P1_RX_TRACE_CAPTURE_DATA1_DEPTH  1

#define IBU_P1_RX_TRACE_CAPTURE_DATA2_ADDR   0x011001e1L
#define IBU_P1_RX_TRACE_CAPTURE_DATA2_STRIDE 1
#define IBU_P1_RX_TRACE_CAPTURE_DATA2_DEPTH  1

#define IBU_P1_RX_TRACE_CAPTURE_DATA3_ADDR   0x011001e2L
#define IBU_P1_RX_TRACE_CAPTURE_DATA3_STRIDE 1
#define IBU_P1_RX_TRACE_CAPTURE_DATA3_DEPTH  1

#define IBU_P1_RX_TRACE_CAPTURE_DATA4_ADDR   0x011001e3L
#define IBU_P1_RX_TRACE_CAPTURE_DATA4_STRIDE 1
#define IBU_P1_RX_TRACE_CAPTURE_DATA4_DEPTH  1

#define IBU_P1_RX_TRACE_CAPTURE_DATA5_ADDR   0x011001e4L
#define IBU_P1_RX_TRACE_CAPTURE_DATA5_STRIDE 1
#define IBU_P1_RX_TRACE_CAPTURE_DATA5_DEPTH  1

#define IBU_P1_RX_TRACE_CAPTURE_DATA6_ADDR   0x011001e5L
#define IBU_P1_RX_TRACE_CAPTURE_DATA6_STRIDE 1
#define IBU_P1_RX_TRACE_CAPTURE_DATA6_DEPTH  1

#define IBU_P1_RX_TRACE_CAPTURE_DATA7_ADDR   0x011001e6L
#define IBU_P1_RX_TRACE_CAPTURE_DATA7_STRIDE 1
#define IBU_P1_RX_TRACE_CAPTURE_DATA7_DEPTH  1

#define IBU_P1_RX_TRACE_CAPTURE_DATA8_ADDR   0x011001e7L
#define IBU_P1_RX_TRACE_CAPTURE_DATA8_STRIDE 1
#define IBU_P1_RX_TRACE_CAPTURE_DATA8_DEPTH  1

#define IBU_P1_RX_TRACE_CAPTURE_DATA9_ADDR   0x011001e8L
#define IBU_P1_RX_TRACE_CAPTURE_DATA9_STRIDE 1
#define IBU_P1_RX_TRACE_CAPTURE_DATA9_DEPTH  1

#define IBU_P1_RX_TRACE_CAPTURE_DATA10_ADDR   0x011001e9L
#define IBU_P1_RX_TRACE_CAPTURE_DATA10_STRIDE 1
#define IBU_P1_RX_TRACE_CAPTURE_DATA10_DEPTH  1

#define IBU_P1_LINK_RX_FCCL_VL1_0_ADDR   0x011001eaL
#define IBU_P1_LINK_RX_FCCL_VL1_0_STRIDE 1
#define IBU_P1_LINK_RX_FCCL_VL1_0_DEPTH  1

#define IBU_P1_LINK_RX_FCCL_VL3_2_ADDR   0x011001ebL
#define IBU_P1_LINK_RX_FCCL_VL3_2_STRIDE 1
#define IBU_P1_LINK_RX_FCCL_VL3_2_DEPTH  1

#define IBU_P1_LINK_RX_FCCL_VL5_4_ADDR   0x011001ecL
#define IBU_P1_LINK_RX_FCCL_VL5_4_STRIDE 1
#define IBU_P1_LINK_RX_FCCL_VL5_4_DEPTH  1

#define IBU_P1_LINK_RX_FCCL_VL7_6_ADDR   0x011001edL
#define IBU_P1_LINK_RX_FCCL_VL7_6_STRIDE 1
#define IBU_P1_LINK_RX_FCCL_VL7_6_DEPTH  1

#define IBU_P1_LINK_NEIGHBOR_JUMBO_MTU_ADDR   0x011001eeL
#define IBU_P1_LINK_NEIGHBOR_JUMBO_MTU_STRIDE 1
#define IBU_P1_LINK_NEIGHBOR_JUMBO_MTU_DEPTH  1

#define IBU_P1_ADD_DEFAULT_LANE0_ADDR   0x01100210L
#define IBU_P1_ADD_DEFAULT_LANE0_STRIDE 1
#define IBU_P1_ADD_DEFAULT_LANE0_DEPTH  1

#define IBU_P1_ADD_DEFAULT_LANE1_ADDR   0x01100211L
#define IBU_P1_ADD_DEFAULT_LANE1_STRIDE 1
#define IBU_P1_ADD_DEFAULT_LANE1_DEPTH  1

#define IBU_P1_ADD_DEFAULT_LANE2_ADDR   0x01100212L
#define IBU_P1_ADD_DEFAULT_LANE2_STRIDE 1
#define IBU_P1_ADD_DEFAULT_LANE2_DEPTH  1

#define IBU_P1_ADD_DEFAULT_LANE3_ADDR   0x01100213L
#define IBU_P1_ADD_DEFAULT_LANE3_STRIDE 1
#define IBU_P1_ADD_DEFAULT_LANE3_DEPTH  1

#define IBU_P1_PHY_ADD0_LANE0_ADDR   0x01100214L
#define IBU_P1_PHY_ADD0_LANE0_STRIDE 1
#define IBU_P1_PHY_ADD0_LANE0_DEPTH  1

#define IBU_P1_PHY_ADD0_LANE1_ADDR   0x01100215L
#define IBU_P1_PHY_ADD0_LANE1_STRIDE 1
#define IBU_P1_PHY_ADD0_LANE1_DEPTH  1

#define IBU_P1_PHY_ADD0_LANE2_ADDR   0x01100216L
#define IBU_P1_PHY_ADD0_LANE2_STRIDE 1
#define IBU_P1_PHY_ADD0_LANE2_DEPTH  1

#define IBU_P1_PHY_ADD0_LANE3_ADDR   0x01100217L
#define IBU_P1_PHY_ADD0_LANE3_STRIDE 1
#define IBU_P1_PHY_ADD0_LANE3_DEPTH  1

#define IBU_P1_PHY_ADD1_LANE0_ADDR   0x01100218L
#define IBU_P1_PHY_ADD1_LANE0_STRIDE 1
#define IBU_P1_PHY_ADD1_LANE0_DEPTH  1

#define IBU_P1_PHY_ADD1_LANE1_ADDR   0x01100219L
#define IBU_P1_PHY_ADD1_LANE1_STRIDE 1
#define IBU_P1_PHY_ADD1_LANE1_DEPTH  1

#define IBU_P1_PHY_ADD1_LANE2_ADDR   0x0110021aL
#define IBU_P1_PHY_ADD1_LANE2_STRIDE 1
#define IBU_P1_PHY_ADD1_LANE2_DEPTH  1

#define IBU_P1_PHY_ADD1_LANE3_ADDR   0x0110021bL
#define IBU_P1_PHY_ADD1_LANE3_STRIDE 1
#define IBU_P1_PHY_ADD1_LANE3_DEPTH  1

#define IBU_P1_PHY_ADD2_LANE0_ADDR   0x0110021cL
#define IBU_P1_PHY_ADD2_LANE0_STRIDE 1
#define IBU_P1_PHY_ADD2_LANE0_DEPTH  1

#define IBU_P1_PHY_ADD2_LANE1_ADDR   0x0110021dL
#define IBU_P1_PHY_ADD2_LANE1_STRIDE 1
#define IBU_P1_PHY_ADD2_LANE1_DEPTH  1

#define IBU_P1_PHY_ADD2_LANE2_ADDR   0x0110021eL
#define IBU_P1_PHY_ADD2_LANE2_STRIDE 1
#define IBU_P1_PHY_ADD2_LANE2_DEPTH  1

#define IBU_P1_PHY_ADD2_LANE3_ADDR   0x0110021fL
#define IBU_P1_PHY_ADD2_LANE3_STRIDE 1
#define IBU_P1_PHY_ADD2_LANE3_DEPTH  1

#define IBU_P1_PHY_ADD3_LANE0_ADDR   0x01100220L
#define IBU_P1_PHY_ADD3_LANE0_STRIDE 1
#define IBU_P1_PHY_ADD3_LANE0_DEPTH  1

#define IBU_P1_PHY_ADD3_LANE1_ADDR   0x01100221L
#define IBU_P1_PHY_ADD3_LANE1_STRIDE 1
#define IBU_P1_PHY_ADD3_LANE1_DEPTH  1

#define IBU_P1_PHY_ADD3_LANE2_ADDR   0x01100222L
#define IBU_P1_PHY_ADD3_LANE2_STRIDE 1
#define IBU_P1_PHY_ADD3_LANE2_DEPTH  1

#define IBU_P1_PHY_ADD3_LANE3_ADDR   0x01100223L
#define IBU_P1_PHY_ADD3_LANE3_STRIDE 1
#define IBU_P1_PHY_ADD3_LANE3_DEPTH  1

#define IBU_P1_PHY_ADD4_LANE0_ADDR   0x01100224L
#define IBU_P1_PHY_ADD4_LANE0_STRIDE 1
#define IBU_P1_PHY_ADD4_LANE0_DEPTH  1

#define IBU_P1_PHY_ADD4_LANE1_ADDR   0x01100225L
#define IBU_P1_PHY_ADD4_LANE1_STRIDE 1
#define IBU_P1_PHY_ADD4_LANE1_DEPTH  1

#define IBU_P1_PHY_ADD4_LANE2_ADDR   0x01100226L
#define IBU_P1_PHY_ADD4_LANE2_STRIDE 1
#define IBU_P1_PHY_ADD4_LANE2_DEPTH  1

#define IBU_P1_PHY_ADD4_LANE3_ADDR   0x01100227L
#define IBU_P1_PHY_ADD4_LANE3_STRIDE 1
#define IBU_P1_PHY_ADD4_LANE3_DEPTH  1

#define IBU_P1_PHY_ADD5_LANE0_ADDR   0x01100228L
#define IBU_P1_PHY_ADD5_LANE0_STRIDE 1
#define IBU_P1_PHY_ADD5_LANE0_DEPTH  1

#define IBU_P1_PHY_ADD5_LANE1_ADDR   0x01100229L
#define IBU_P1_PHY_ADD5_LANE1_STRIDE 1
#define IBU_P1_PHY_ADD5_LANE1_DEPTH  1

#define IBU_P1_PHY_ADD5_LANE2_ADDR   0x0110022aL
#define IBU_P1_PHY_ADD5_LANE2_STRIDE 1
#define IBU_P1_PHY_ADD5_LANE2_DEPTH  1

#define IBU_P1_PHY_ADD5_LANE3_ADDR   0x0110022bL
#define IBU_P1_PHY_ADD5_LANE3_STRIDE 1
#define IBU_P1_PHY_ADD5_LANE3_DEPTH  1

#define IBU_P1_PHY_ADD6_LANE0_ADDR   0x0110022cL
#define IBU_P1_PHY_ADD6_LANE0_STRIDE 1
#define IBU_P1_PHY_ADD6_LANE0_DEPTH  1

#define IBU_P1_PHY_ADD6_LANE1_ADDR   0x0110022dL
#define IBU_P1_PHY_ADD6_LANE1_STRIDE 1
#define IBU_P1_PHY_ADD6_LANE1_DEPTH  1

#define IBU_P1_PHY_ADD6_LANE2_ADDR   0x0110022eL
#define IBU_P1_PHY_ADD6_LANE2_STRIDE 1
#define IBU_P1_PHY_ADD6_LANE2_DEPTH  1

#define IBU_P1_PHY_ADD6_LANE3_ADDR   0x0110022fL
#define IBU_P1_PHY_ADD6_LANE3_STRIDE 1
#define IBU_P1_PHY_ADD6_LANE3_DEPTH  1

#define IBU_P1_PHY_ADD7_LANE0_ADDR   0x01100230L
#define IBU_P1_PHY_ADD7_LANE0_STRIDE 1
#define IBU_P1_PHY_ADD7_LANE0_DEPTH  1

#define IBU_P1_PHY_ADD7_LANE1_ADDR   0x01100231L
#define IBU_P1_PHY_ADD7_LANE1_STRIDE 1
#define IBU_P1_PHY_ADD7_LANE1_DEPTH  1

#define IBU_P1_PHY_ADD7_LANE2_ADDR   0x01100232L
#define IBU_P1_PHY_ADD7_LANE2_STRIDE 1
#define IBU_P1_PHY_ADD7_LANE2_DEPTH  1

#define IBU_P1_PHY_ADD7_LANE3_ADDR   0x01100233L
#define IBU_P1_PHY_ADD7_LANE3_STRIDE 1
#define IBU_P1_PHY_ADD7_LANE3_DEPTH  1

#define IBU_P1_PHY_ADD8_LANE0_ADDR   0x01100234L
#define IBU_P1_PHY_ADD8_LANE0_STRIDE 1
#define IBU_P1_PHY_ADD8_LANE0_DEPTH  1

#define IBU_P1_PHY_ADD8_LANE1_ADDR   0x01100235L
#define IBU_P1_PHY_ADD8_LANE1_STRIDE 1
#define IBU_P1_PHY_ADD8_LANE1_DEPTH  1

#define IBU_P1_PHY_ADD8_LANE2_ADDR   0x01100236L
#define IBU_P1_PHY_ADD8_LANE2_STRIDE 1
#define IBU_P1_PHY_ADD8_LANE2_DEPTH  1

#define IBU_P1_PHY_ADD8_LANE3_ADDR   0x01100237L
#define IBU_P1_PHY_ADD8_LANE3_STRIDE 1
#define IBU_P1_PHY_ADD8_LANE3_DEPTH  1

#define IBU_P1_PHY_ADD9_LANE0_ADDR   0x01100238L
#define IBU_P1_PHY_ADD9_LANE0_STRIDE 1
#define IBU_P1_PHY_ADD9_LANE0_DEPTH  1

#define IBU_P1_PHY_ADD9_LANE1_ADDR   0x01100239L
#define IBU_P1_PHY_ADD9_LANE1_STRIDE 1
#define IBU_P1_PHY_ADD9_LANE1_DEPTH  1

#define IBU_P1_PHY_ADD9_LANE2_ADDR   0x0110023aL
#define IBU_P1_PHY_ADD9_LANE2_STRIDE 1
#define IBU_P1_PHY_ADD9_LANE2_DEPTH  1

#define IBU_P1_PHY_ADD9_LANE3_ADDR   0x0110023bL
#define IBU_P1_PHY_ADD9_LANE3_STRIDE 1
#define IBU_P1_PHY_ADD9_LANE3_DEPTH  1

#define IBU_P1_PHY_ADD10_LANE0_ADDR   0x0110023cL
#define IBU_P1_PHY_ADD10_LANE0_STRIDE 1
#define IBU_P1_PHY_ADD10_LANE0_DEPTH  1

#define IBU_P1_PHY_ADD10_LANE1_ADDR   0x0110023dL
#define IBU_P1_PHY_ADD10_LANE1_STRIDE 1
#define IBU_P1_PHY_ADD10_LANE1_DEPTH  1

#define IBU_P1_PHY_ADD10_LANE2_ADDR   0x0110023eL
#define IBU_P1_PHY_ADD10_LANE2_STRIDE 1
#define IBU_P1_PHY_ADD10_LANE2_DEPTH  1

#define IBU_P1_PHY_ADD10_LANE3_ADDR   0x0110023fL
#define IBU_P1_PHY_ADD10_LANE3_STRIDE 1
#define IBU_P1_PHY_ADD10_LANE3_DEPTH  1

#define IBU_P1_PHY_ADD11_LANE0_ADDR   0x01100240L
#define IBU_P1_PHY_ADD11_LANE0_STRIDE 1
#define IBU_P1_PHY_ADD11_LANE0_DEPTH  1

#define IBU_P1_PHY_ADD11_LANE1_ADDR   0x01100241L
#define IBU_P1_PHY_ADD11_LANE1_STRIDE 1
#define IBU_P1_PHY_ADD11_LANE1_DEPTH  1

#define IBU_P1_PHY_ADD11_LANE2_ADDR   0x01100242L
#define IBU_P1_PHY_ADD11_LANE2_STRIDE 1
#define IBU_P1_PHY_ADD11_LANE2_DEPTH  1

#define IBU_P1_PHY_ADD11_LANE3_ADDR   0x01100243L
#define IBU_P1_PHY_ADD11_LANE3_STRIDE 1
#define IBU_P1_PHY_ADD11_LANE3_DEPTH  1

#define IBU_P1_PHY_ADD12_LANE0_ADDR   0x01100244L
#define IBU_P1_PHY_ADD12_LANE0_STRIDE 1
#define IBU_P1_PHY_ADD12_LANE0_DEPTH  1

#define IBU_P1_PHY_ADD12_LANE1_ADDR   0x01100245L
#define IBU_P1_PHY_ADD12_LANE1_STRIDE 1
#define IBU_P1_PHY_ADD12_LANE1_DEPTH  1

#define IBU_P1_PHY_ADD12_LANE2_ADDR   0x01100246L
#define IBU_P1_PHY_ADD12_LANE2_STRIDE 1
#define IBU_P1_PHY_ADD12_LANE2_DEPTH  1

#define IBU_P1_PHY_ADD12_LANE3_ADDR   0x01100247L
#define IBU_P1_PHY_ADD12_LANE3_STRIDE 1
#define IBU_P1_PHY_ADD12_LANE3_DEPTH  1

#define IBU_P1_PHY_ADD13_LANE0_ADDR   0x01100248L
#define IBU_P1_PHY_ADD13_LANE0_STRIDE 1
#define IBU_P1_PHY_ADD13_LANE0_DEPTH  1

#define IBU_P1_PHY_ADD13_LANE1_ADDR   0x01100249L
#define IBU_P1_PHY_ADD13_LANE1_STRIDE 1
#define IBU_P1_PHY_ADD13_LANE1_DEPTH  1

#define IBU_P1_PHY_ADD13_LANE2_ADDR   0x0110024aL
#define IBU_P1_PHY_ADD13_LANE2_STRIDE 1
#define IBU_P1_PHY_ADD13_LANE2_DEPTH  1

#define IBU_P1_PHY_ADD13_LANE3_ADDR   0x0110024bL
#define IBU_P1_PHY_ADD13_LANE3_STRIDE 1
#define IBU_P1_PHY_ADD13_LANE3_DEPTH  1

#define IBU_P1_PHY_ADD14_LANE0_ADDR   0x0110024cL
#define IBU_P1_PHY_ADD14_LANE0_STRIDE 1
#define IBU_P1_PHY_ADD14_LANE0_DEPTH  1

#define IBU_P1_PHY_ADD14_LANE1_ADDR   0x0110024dL
#define IBU_P1_PHY_ADD14_LANE1_STRIDE 1
#define IBU_P1_PHY_ADD14_LANE1_DEPTH  1

#define IBU_P1_PHY_ADD14_LANE2_ADDR   0x0110024eL
#define IBU_P1_PHY_ADD14_LANE2_STRIDE 1
#define IBU_P1_PHY_ADD14_LANE2_DEPTH  1

#define IBU_P1_PHY_ADD14_LANE3_ADDR   0x0110024fL
#define IBU_P1_PHY_ADD14_LANE3_STRIDE 1
#define IBU_P1_PHY_ADD14_LANE3_DEPTH  1

#define IBU_P1_PHY_ADD15_LANE0_ADDR   0x01100250L
#define IBU_P1_PHY_ADD15_LANE0_STRIDE 1
#define IBU_P1_PHY_ADD15_LANE0_DEPTH  1

#define IBU_P1_PHY_ADD15_LANE1_ADDR   0x01100251L
#define IBU_P1_PHY_ADD15_LANE1_STRIDE 1
#define IBU_P1_PHY_ADD15_LANE1_DEPTH  1

#define IBU_P1_PHY_ADD15_LANE2_ADDR   0x01100252L
#define IBU_P1_PHY_ADD15_LANE2_STRIDE 1
#define IBU_P1_PHY_ADD15_LANE2_DEPTH  1

#define IBU_P1_PHY_ADD15_LANE3_ADDR   0x01100253L
#define IBU_P1_PHY_ADD15_LANE3_STRIDE 1
#define IBU_P1_PHY_ADD15_LANE3_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD0_LANE0_ADDR   0x01100254L
#define IBU_P1_PHY_AMP1_ADD0_LANE0_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD0_LANE0_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD0_LANE1_ADDR   0x01100255L
#define IBU_P1_PHY_AMP1_ADD0_LANE1_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD0_LANE1_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD0_LANE2_ADDR   0x01100256L
#define IBU_P1_PHY_AMP1_ADD0_LANE2_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD0_LANE2_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD0_LANE3_ADDR   0x01100257L
#define IBU_P1_PHY_AMP1_ADD0_LANE3_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD0_LANE3_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD1_LANE0_ADDR   0x01100258L
#define IBU_P1_PHY_AMP1_ADD1_LANE0_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD1_LANE0_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD1_LANE1_ADDR   0x01100259L
#define IBU_P1_PHY_AMP1_ADD1_LANE1_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD1_LANE1_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD1_LANE2_ADDR   0x0110025aL
#define IBU_P1_PHY_AMP1_ADD1_LANE2_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD1_LANE2_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD1_LANE3_ADDR   0x0110025bL
#define IBU_P1_PHY_AMP1_ADD1_LANE3_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD1_LANE3_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD2_LANE0_ADDR   0x0110025cL
#define IBU_P1_PHY_AMP1_ADD2_LANE0_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD2_LANE0_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD2_LANE1_ADDR   0x0110025dL
#define IBU_P1_PHY_AMP1_ADD2_LANE1_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD2_LANE1_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD2_LANE2_ADDR   0x0110025eL
#define IBU_P1_PHY_AMP1_ADD2_LANE2_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD2_LANE2_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD2_LANE3_ADDR   0x0110025fL
#define IBU_P1_PHY_AMP1_ADD2_LANE3_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD2_LANE3_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD3_LANE0_ADDR   0x01100260L
#define IBU_P1_PHY_AMP1_ADD3_LANE0_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD3_LANE0_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD3_LANE1_ADDR   0x01100261L
#define IBU_P1_PHY_AMP1_ADD3_LANE1_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD3_LANE1_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD3_LANE2_ADDR   0x01100262L
#define IBU_P1_PHY_AMP1_ADD3_LANE2_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD3_LANE2_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD3_LANE3_ADDR   0x01100263L
#define IBU_P1_PHY_AMP1_ADD3_LANE3_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD3_LANE3_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD4_LANE0_ADDR   0x01100264L
#define IBU_P1_PHY_AMP1_ADD4_LANE0_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD4_LANE0_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD4_LANE1_ADDR   0x01100265L
#define IBU_P1_PHY_AMP1_ADD4_LANE1_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD4_LANE1_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD4_LANE2_ADDR   0x01100266L
#define IBU_P1_PHY_AMP1_ADD4_LANE2_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD4_LANE2_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD4_LANE3_ADDR   0x01100267L
#define IBU_P1_PHY_AMP1_ADD4_LANE3_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD4_LANE3_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD5_LANE0_ADDR   0x01100268L
#define IBU_P1_PHY_AMP1_ADD5_LANE0_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD5_LANE0_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD5_LANE1_ADDR   0x01100269L
#define IBU_P1_PHY_AMP1_ADD5_LANE1_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD5_LANE1_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD5_LANE2_ADDR   0x0110026aL
#define IBU_P1_PHY_AMP1_ADD5_LANE2_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD5_LANE2_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD5_LANE3_ADDR   0x0110026bL
#define IBU_P1_PHY_AMP1_ADD5_LANE3_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD5_LANE3_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD6_LANE0_ADDR   0x0110026cL
#define IBU_P1_PHY_AMP1_ADD6_LANE0_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD6_LANE0_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD6_LANE1_ADDR   0x0110026dL
#define IBU_P1_PHY_AMP1_ADD6_LANE1_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD6_LANE1_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD6_LANE2_ADDR   0x0110026eL
#define IBU_P1_PHY_AMP1_ADD6_LANE2_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD6_LANE2_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD6_LANE3_ADDR   0x0110026fL
#define IBU_P1_PHY_AMP1_ADD6_LANE3_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD6_LANE3_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD7_LANE0_ADDR   0x01100270L
#define IBU_P1_PHY_AMP1_ADD7_LANE0_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD7_LANE0_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD7_LANE1_ADDR   0x01100271L
#define IBU_P1_PHY_AMP1_ADD7_LANE1_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD7_LANE1_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD7_LANE2_ADDR   0x01100272L
#define IBU_P1_PHY_AMP1_ADD7_LANE2_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD7_LANE2_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD7_LANE3_ADDR   0x01100273L
#define IBU_P1_PHY_AMP1_ADD7_LANE3_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD7_LANE3_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD8_LANE0_ADDR   0x01100274L
#define IBU_P1_PHY_AMP1_ADD8_LANE0_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD8_LANE0_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD8_LANE1_ADDR   0x01100275L
#define IBU_P1_PHY_AMP1_ADD8_LANE1_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD8_LANE1_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD8_LANE2_ADDR   0x01100276L
#define IBU_P1_PHY_AMP1_ADD8_LANE2_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD8_LANE2_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD8_LANE3_ADDR   0x01100277L
#define IBU_P1_PHY_AMP1_ADD8_LANE3_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD8_LANE3_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD9_LANE0_ADDR   0x01100278L
#define IBU_P1_PHY_AMP1_ADD9_LANE0_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD9_LANE0_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD9_LANE1_ADDR   0x01100279L
#define IBU_P1_PHY_AMP1_ADD9_LANE1_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD9_LANE1_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD9_LANE2_ADDR   0x0110027aL
#define IBU_P1_PHY_AMP1_ADD9_LANE2_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD9_LANE2_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD9_LANE3_ADDR   0x0110027bL
#define IBU_P1_PHY_AMP1_ADD9_LANE3_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD9_LANE3_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD10_LANE0_ADDR   0x0110027cL
#define IBU_P1_PHY_AMP1_ADD10_LANE0_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD10_LANE0_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD10_LANE1_ADDR   0x0110027dL
#define IBU_P1_PHY_AMP1_ADD10_LANE1_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD10_LANE1_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD10_LANE2_ADDR   0x0110027eL
#define IBU_P1_PHY_AMP1_ADD10_LANE2_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD10_LANE2_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD10_LANE3_ADDR   0x0110027fL
#define IBU_P1_PHY_AMP1_ADD10_LANE3_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD10_LANE3_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD11_LANE0_ADDR   0x01100280L
#define IBU_P1_PHY_AMP1_ADD11_LANE0_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD11_LANE0_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD11_LANE1_ADDR   0x01100281L
#define IBU_P1_PHY_AMP1_ADD11_LANE1_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD11_LANE1_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD11_LANE2_ADDR   0x01100282L
#define IBU_P1_PHY_AMP1_ADD11_LANE2_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD11_LANE2_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD11_LANE3_ADDR   0x01100283L
#define IBU_P1_PHY_AMP1_ADD11_LANE3_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD11_LANE3_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD12_LANE0_ADDR   0x01100284L
#define IBU_P1_PHY_AMP1_ADD12_LANE0_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD12_LANE0_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD12_LANE1_ADDR   0x01100285L
#define IBU_P1_PHY_AMP1_ADD12_LANE1_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD12_LANE1_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD12_LANE2_ADDR   0x01100286L
#define IBU_P1_PHY_AMP1_ADD12_LANE2_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD12_LANE2_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD12_LANE3_ADDR   0x01100287L
#define IBU_P1_PHY_AMP1_ADD12_LANE3_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD12_LANE3_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD13_LANE0_ADDR   0x01100288L
#define IBU_P1_PHY_AMP1_ADD13_LANE0_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD13_LANE0_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD13_LANE1_ADDR   0x01100289L
#define IBU_P1_PHY_AMP1_ADD13_LANE1_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD13_LANE1_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD13_LANE2_ADDR   0x0110028aL
#define IBU_P1_PHY_AMP1_ADD13_LANE2_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD13_LANE2_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD13_LANE3_ADDR   0x0110028bL
#define IBU_P1_PHY_AMP1_ADD13_LANE3_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD13_LANE3_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD14_LANE0_ADDR   0x0110028cL
#define IBU_P1_PHY_AMP1_ADD14_LANE0_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD14_LANE0_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD14_LANE1_ADDR   0x0110028dL
#define IBU_P1_PHY_AMP1_ADD14_LANE1_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD14_LANE1_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD14_LANE2_ADDR   0x0110028eL
#define IBU_P1_PHY_AMP1_ADD14_LANE2_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD14_LANE2_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD14_LANE3_ADDR   0x0110028fL
#define IBU_P1_PHY_AMP1_ADD14_LANE3_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD14_LANE3_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD15_LANE0_ADDR   0x01100290L
#define IBU_P1_PHY_AMP1_ADD15_LANE0_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD15_LANE0_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD15_LANE1_ADDR   0x01100291L
#define IBU_P1_PHY_AMP1_ADD15_LANE1_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD15_LANE1_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD15_LANE2_ADDR   0x01100292L
#define IBU_P1_PHY_AMP1_ADD15_LANE2_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD15_LANE2_DEPTH  1

#define IBU_P1_PHY_AMP1_ADD15_LANE3_ADDR   0x01100293L
#define IBU_P1_PHY_AMP1_ADD15_LANE3_STRIDE 1
#define IBU_P1_PHY_AMP1_ADD15_LANE3_DEPTH  1

#define IBU_P1_REMOTE_DDS0_ADDR   0x01100294L
#define IBU_P1_REMOTE_DDS0_STRIDE 1
#define IBU_P1_REMOTE_DDS0_DEPTH  1

#define IBU_P1_REMOTE_DDS1_ADDR   0x01100295L
#define IBU_P1_REMOTE_DDS1_STRIDE 1
#define IBU_P1_REMOTE_DDS1_DEPTH  1

#define IBU_P1_REMOTE_DDS2_ADDR   0x01100296L
#define IBU_P1_REMOTE_DDS2_STRIDE 1
#define IBU_P1_REMOTE_DDS2_DEPTH  1

#define IBU_P1_REMOTE_DDS3_ADDR   0x01100297L
#define IBU_P1_REMOTE_DDS3_STRIDE 1
#define IBU_P1_REMOTE_DDS3_DEPTH  1

#define IBU_P1_REMOTE_DDS4_ADDR   0x01100298L
#define IBU_P1_REMOTE_DDS4_STRIDE 1
#define IBU_P1_REMOTE_DDS4_DEPTH  1

#define IBU_P1_REMOTE_DDS5_ADDR   0x01100299L
#define IBU_P1_REMOTE_DDS5_STRIDE 1
#define IBU_P1_REMOTE_DDS5_DEPTH  1

#define IBU_P1_REMOTE_DDS6_ADDR   0x0110029aL
#define IBU_P1_REMOTE_DDS6_STRIDE 1
#define IBU_P1_REMOTE_DDS6_DEPTH  1

#define IBU_P1_REMOTE_DDS7_ADDR   0x0110029bL
#define IBU_P1_REMOTE_DDS7_STRIDE 1
#define IBU_P1_REMOTE_DDS7_DEPTH  1

#define IBU_P1_REMOTE_DDS8_ADDR   0x0110029cL
#define IBU_P1_REMOTE_DDS8_STRIDE 1
#define IBU_P1_REMOTE_DDS8_DEPTH  1

#define IBU_P1_REMOTE_DDS9_ADDR   0x0110029dL
#define IBU_P1_REMOTE_DDS9_STRIDE 1
#define IBU_P1_REMOTE_DDS9_DEPTH  1

#define IBU_P1_REMOTE_DDS10_ADDR   0x0110029eL
#define IBU_P1_REMOTE_DDS10_STRIDE 1
#define IBU_P1_REMOTE_DDS10_DEPTH  1

#define IBU_P1_REMOTE_DDS11_ADDR   0x0110029fL
#define IBU_P1_REMOTE_DDS11_STRIDE 1
#define IBU_P1_REMOTE_DDS11_DEPTH  1

#define IBU_P1_REMOTE_DDS12_ADDR   0x011002a0L
#define IBU_P1_REMOTE_DDS12_STRIDE 1
#define IBU_P1_REMOTE_DDS12_DEPTH  1

#define IBU_P1_REMOTE_DDS13_ADDR   0x011002a1L
#define IBU_P1_REMOTE_DDS13_STRIDE 1
#define IBU_P1_REMOTE_DDS13_DEPTH  1

#define IBU_P1_REMOTE_DDS14_ADDR   0x011002a2L
#define IBU_P1_REMOTE_DDS14_STRIDE 1
#define IBU_P1_REMOTE_DDS14_DEPTH  1

#define IBU_P1_REMOTE_DDS15_ADDR   0x011002a3L
#define IBU_P1_REMOTE_DDS15_STRIDE 1
#define IBU_P1_REMOTE_DDS15_DEPTH  1

#define IBU_P1_BAD_CSR_ADDR   0x01100badL
#define IBU_P1_BAD_CSR_STRIDE 1
#define IBU_P1_BAD_CSR_DEPTH  1

	/* CETUS register */
#define IBU_P1_CETUS_CH0_000_ADDR   0x01140000L
#define IBU_P1_CETUS_CH0_000_STRIDE 1
#define IBU_P1_CETUS_CH0_000_DEPTH  1

	/* CETUS register */
#define IBU_P1_CETUS_CH0_001_ADDR   0x01140001L
#define IBU_P1_CETUS_CH0_001_STRIDE 1
#define IBU_P1_CETUS_CH0_001_DEPTH  1

	/* CETUS register */
#define IBU_P1_CETUS_CH0_002_ADDR   0x01140002L
#define IBU_P1_CETUS_CH0_002_STRIDE 1
#define IBU_P1_CETUS_CH0_002_DEPTH  1

#define IBU_P1_CETUS_CH0_003_ADDR   0x01140003L
#define IBU_P1_CETUS_CH0_003_STRIDE 1
#define IBU_P1_CETUS_CH0_003_DEPTH  1

#define IBU_P1_CETUS_CH0_004_ADDR   0x01140004L
#define IBU_P1_CETUS_CH0_004_STRIDE 1
#define IBU_P1_CETUS_CH0_004_DEPTH  1

#define IBU_P1_CETUS_CH0_005_ADDR   0x01140005L
#define IBU_P1_CETUS_CH0_005_STRIDE 1
#define IBU_P1_CETUS_CH0_005_DEPTH  1

#define IBU_P1_CETUS_CH0_006_ADDR   0x01140006L
#define IBU_P1_CETUS_CH0_006_STRIDE 1
#define IBU_P1_CETUS_CH0_006_DEPTH  1

#define IBU_P1_CETUS_CH0_007_ADDR   0x01140007L
#define IBU_P1_CETUS_CH0_007_STRIDE 1
#define IBU_P1_CETUS_CH0_007_DEPTH  1

#define IBU_P1_CETUS_CH0_008_ADDR   0x01140008L
#define IBU_P1_CETUS_CH0_008_STRIDE 1
#define IBU_P1_CETUS_CH0_008_DEPTH  1

#define IBU_P1_CETUS_CH0_009_ADDR   0x01140009L
#define IBU_P1_CETUS_CH0_009_STRIDE 1
#define IBU_P1_CETUS_CH0_009_DEPTH  1

#define IBU_P1_CETUS_CH0_010_ADDR   0x0114000aL
#define IBU_P1_CETUS_CH0_010_STRIDE 1
#define IBU_P1_CETUS_CH0_010_DEPTH  1

#define IBU_P1_CETUS_CH0_011_ADDR   0x0114000bL
#define IBU_P1_CETUS_CH0_011_STRIDE 1
#define IBU_P1_CETUS_CH0_011_DEPTH  1

#define IBU_P1_CETUS_CH0_012_ADDR   0x0114000cL
#define IBU_P1_CETUS_CH0_012_STRIDE 1
#define IBU_P1_CETUS_CH0_012_DEPTH  1

#define IBU_P1_CETUS_CH0_013_ADDR   0x0114000dL
#define IBU_P1_CETUS_CH0_013_STRIDE 1
#define IBU_P1_CETUS_CH0_013_DEPTH  1

#define IBU_P1_CETUS_CH0_014_ADDR   0x0114000eL
#define IBU_P1_CETUS_CH0_014_STRIDE 1
#define IBU_P1_CETUS_CH0_014_DEPTH  1

#define IBU_P1_CETUS_CH0_015_ADDR   0x0114000fL
#define IBU_P1_CETUS_CH0_015_STRIDE 1
#define IBU_P1_CETUS_CH0_015_DEPTH  1

#define IBU_P1_CETUS_CH0_016_ADDR   0x01140010L
#define IBU_P1_CETUS_CH0_016_STRIDE 1
#define IBU_P1_CETUS_CH0_016_DEPTH  1

#define IBU_P1_CETUS_CH0_017_ADDR   0x01140011L
#define IBU_P1_CETUS_CH0_017_STRIDE 1
#define IBU_P1_CETUS_CH0_017_DEPTH  1

#define IBU_P1_CETUS_CH0_018_ADDR   0x01140012L
#define IBU_P1_CETUS_CH0_018_STRIDE 1
#define IBU_P1_CETUS_CH0_018_DEPTH  1

#define IBU_P1_CETUS_CH0_019_ADDR   0x01140013L
#define IBU_P1_CETUS_CH0_019_STRIDE 1
#define IBU_P1_CETUS_CH0_019_DEPTH  1

#define IBU_P1_CETUS_CH0_020_ADDR   0x01140014L
#define IBU_P1_CETUS_CH0_020_STRIDE 1
#define IBU_P1_CETUS_CH0_020_DEPTH  1

#define IBU_P1_CETUS_CH0_021_ADDR   0x01140015L
#define IBU_P1_CETUS_CH0_021_STRIDE 1
#define IBU_P1_CETUS_CH0_021_DEPTH  1

#define IBU_P1_CETUS_CH0_022_ADDR   0x01140016L
#define IBU_P1_CETUS_CH0_022_STRIDE 1
#define IBU_P1_CETUS_CH0_022_DEPTH  1

#define IBU_P1_CETUS_CH0_023_ADDR   0x01140017L
#define IBU_P1_CETUS_CH0_023_STRIDE 1
#define IBU_P1_CETUS_CH0_023_DEPTH  1

#define IBU_P1_CETUS_CH0_024_ADDR   0x01140018L
#define IBU_P1_CETUS_CH0_024_STRIDE 1
#define IBU_P1_CETUS_CH0_024_DEPTH  1

#define IBU_P1_CETUS_CH0_025_ADDR   0x01140019L
#define IBU_P1_CETUS_CH0_025_STRIDE 1
#define IBU_P1_CETUS_CH0_025_DEPTH  1

#define IBU_P1_CETUS_CH0_026_ADDR   0x0114001aL
#define IBU_P1_CETUS_CH0_026_STRIDE 1
#define IBU_P1_CETUS_CH0_026_DEPTH  1

#define IBU_P1_CETUS_CH0_027_ADDR   0x0114001bL
#define IBU_P1_CETUS_CH0_027_STRIDE 1
#define IBU_P1_CETUS_CH0_027_DEPTH  1

#define IBU_P1_CETUS_CH0_028_ADDR   0x0114001cL
#define IBU_P1_CETUS_CH0_028_STRIDE 1
#define IBU_P1_CETUS_CH0_028_DEPTH  1

#define IBU_P1_CETUS_CH0_029_ADDR   0x0114001dL
#define IBU_P1_CETUS_CH0_029_STRIDE 1
#define IBU_P1_CETUS_CH0_029_DEPTH  1

#define IBU_P1_CETUS_CH0_030_ADDR   0x0114001eL
#define IBU_P1_CETUS_CH0_030_STRIDE 1
#define IBU_P1_CETUS_CH0_030_DEPTH  1

#define IBU_P1_CETUS_CH0_031_ADDR   0x0114001fL
#define IBU_P1_CETUS_CH0_031_STRIDE 1
#define IBU_P1_CETUS_CH0_031_DEPTH  1

#define IBU_P1_CETUS_CH0_032_ADDR   0x01140020L
#define IBU_P1_CETUS_CH0_032_STRIDE 1
#define IBU_P1_CETUS_CH0_032_DEPTH  1

#define IBU_P1_CETUS_CH0_033_ADDR   0x01140021L
#define IBU_P1_CETUS_CH0_033_STRIDE 1
#define IBU_P1_CETUS_CH0_033_DEPTH  1

#define IBU_P1_CETUS_CH0_034_ADDR   0x01140022L
#define IBU_P1_CETUS_CH0_034_STRIDE 1
#define IBU_P1_CETUS_CH0_034_DEPTH  1

#define IBU_P1_CETUS_CH0_035_ADDR   0x01140023L
#define IBU_P1_CETUS_CH0_035_STRIDE 1
#define IBU_P1_CETUS_CH0_035_DEPTH  1

#define IBU_P1_CETUS_CH0_036_ADDR   0x01140024L
#define IBU_P1_CETUS_CH0_036_STRIDE 1
#define IBU_P1_CETUS_CH0_036_DEPTH  1

#define IBU_P1_CETUS_CH0_037_ADDR   0x01140025L
#define IBU_P1_CETUS_CH0_037_STRIDE 1
#define IBU_P1_CETUS_CH0_037_DEPTH  1

#define IBU_P1_CETUS_CH0_038_ADDR   0x01140026L
#define IBU_P1_CETUS_CH0_038_STRIDE 1
#define IBU_P1_CETUS_CH0_038_DEPTH  1

#define IBU_P1_CETUS_CH0_039_ADDR   0x01140027L
#define IBU_P1_CETUS_CH0_039_STRIDE 1
#define IBU_P1_CETUS_CH0_039_DEPTH  1

#define IBU_P1_CETUS_CH0_040_ADDR   0x01140028L
#define IBU_P1_CETUS_CH0_040_STRIDE 1
#define IBU_P1_CETUS_CH0_040_DEPTH  1

#define IBU_P1_CETUS_CH0_041_ADDR   0x01140029L
#define IBU_P1_CETUS_CH0_041_STRIDE 1
#define IBU_P1_CETUS_CH0_041_DEPTH  1

#define IBU_P1_CETUS_CH0_042_ADDR   0x0114002aL
#define IBU_P1_CETUS_CH0_042_STRIDE 1
#define IBU_P1_CETUS_CH0_042_DEPTH  1

#define IBU_P1_CETUS_CH0_043_ADDR   0x0114002bL
#define IBU_P1_CETUS_CH0_043_STRIDE 1
#define IBU_P1_CETUS_CH0_043_DEPTH  1

#define IBU_P1_CETUS_CH0_044_ADDR   0x0114002cL
#define IBU_P1_CETUS_CH0_044_STRIDE 1
#define IBU_P1_CETUS_CH0_044_DEPTH  1

#define IBU_P1_CETUS_CH0_045_ADDR   0x0114002dL
#define IBU_P1_CETUS_CH0_045_STRIDE 1
#define IBU_P1_CETUS_CH0_045_DEPTH  1

#define IBU_P1_CETUS_CH0_046_ADDR   0x0114002eL
#define IBU_P1_CETUS_CH0_046_STRIDE 1
#define IBU_P1_CETUS_CH0_046_DEPTH  1

#define IBU_P1_CETUS_CH0_047_ADDR   0x0114002fL
#define IBU_P1_CETUS_CH0_047_STRIDE 1
#define IBU_P1_CETUS_CH0_047_DEPTH  1

#define IBU_P1_CETUS_CH0_048_ADDR   0x01140030L
#define IBU_P1_CETUS_CH0_048_STRIDE 1
#define IBU_P1_CETUS_CH0_048_DEPTH  1

#define IBU_P1_CETUS_CH0_049_ADDR   0x01140031L
#define IBU_P1_CETUS_CH0_049_STRIDE 1
#define IBU_P1_CETUS_CH0_049_DEPTH  1

#define IBU_P1_CETUS_CH0_050_ADDR   0x01140032L
#define IBU_P1_CETUS_CH0_050_STRIDE 1
#define IBU_P1_CETUS_CH0_050_DEPTH  1

#define IBU_P1_CETUS_CH0_051_ADDR   0x01140033L
#define IBU_P1_CETUS_CH0_051_STRIDE 1
#define IBU_P1_CETUS_CH0_051_DEPTH  1

#define IBU_P1_CETUS_CH0_052_ADDR   0x01140034L
#define IBU_P1_CETUS_CH0_052_STRIDE 1
#define IBU_P1_CETUS_CH0_052_DEPTH  1

#define IBU_P1_CETUS_CH0_053_ADDR   0x01140035L
#define IBU_P1_CETUS_CH0_053_STRIDE 1
#define IBU_P1_CETUS_CH0_053_DEPTH  1

#define IBU_P1_CETUS_CH0_054_ADDR   0x01140036L
#define IBU_P1_CETUS_CH0_054_STRIDE 1
#define IBU_P1_CETUS_CH0_054_DEPTH  1

#define IBU_P1_CETUS_CH0_055_ADDR   0x01140037L
#define IBU_P1_CETUS_CH0_055_STRIDE 1
#define IBU_P1_CETUS_CH0_055_DEPTH  1

#define IBU_P1_CETUS_CH0_056_ADDR   0x01140038L
#define IBU_P1_CETUS_CH0_056_STRIDE 1
#define IBU_P1_CETUS_CH0_056_DEPTH  1

#define IBU_P1_CETUS_CH0_057_ADDR   0x01140039L
#define IBU_P1_CETUS_CH0_057_STRIDE 1
#define IBU_P1_CETUS_CH0_057_DEPTH  1

#define IBU_P1_CETUS_CH0_058_ADDR   0x0114003aL
#define IBU_P1_CETUS_CH0_058_STRIDE 1
#define IBU_P1_CETUS_CH0_058_DEPTH  1

#define IBU_P1_CETUS_CH0_059_ADDR   0x0114003bL
#define IBU_P1_CETUS_CH0_059_STRIDE 1
#define IBU_P1_CETUS_CH0_059_DEPTH  1

#define IBU_P1_CETUS_CH0_060_ADDR   0x0114003cL
#define IBU_P1_CETUS_CH0_060_STRIDE 1
#define IBU_P1_CETUS_CH0_060_DEPTH  1

#define IBU_P1_CETUS_CH0_061_ADDR   0x0114003dL
#define IBU_P1_CETUS_CH0_061_STRIDE 1
#define IBU_P1_CETUS_CH0_061_DEPTH  1

#define IBU_P1_CETUS_CH0_062_ADDR   0x0114003eL
#define IBU_P1_CETUS_CH0_062_STRIDE 1
#define IBU_P1_CETUS_CH0_062_DEPTH  1

#define IBU_P1_CETUS_CH0_063_ADDR   0x0114003fL
#define IBU_P1_CETUS_CH0_063_STRIDE 1
#define IBU_P1_CETUS_CH0_063_DEPTH  1

#define IBU_P1_CETUS_CH0_064_ADDR   0x01140040L
#define IBU_P1_CETUS_CH0_064_STRIDE 1
#define IBU_P1_CETUS_CH0_064_DEPTH  1

#define IBU_P1_CETUS_CH0_065_ADDR   0x01140041L
#define IBU_P1_CETUS_CH0_065_STRIDE 1
#define IBU_P1_CETUS_CH0_065_DEPTH  1

#define IBU_P1_CETUS_CH0_066_ADDR   0x01140042L
#define IBU_P1_CETUS_CH0_066_STRIDE 1
#define IBU_P1_CETUS_CH0_066_DEPTH  1

#define IBU_P1_CETUS_CH0_067_ADDR   0x01140043L
#define IBU_P1_CETUS_CH0_067_STRIDE 1
#define IBU_P1_CETUS_CH0_067_DEPTH  1

#define IBU_P1_CETUS_CH0_068_ADDR   0x01140044L
#define IBU_P1_CETUS_CH0_068_STRIDE 1
#define IBU_P1_CETUS_CH0_068_DEPTH  1

#define IBU_P1_CETUS_CH0_069_ADDR   0x01140045L
#define IBU_P1_CETUS_CH0_069_STRIDE 1
#define IBU_P1_CETUS_CH0_069_DEPTH  1

#define IBU_P1_CETUS_CH0_070_ADDR   0x01140046L
#define IBU_P1_CETUS_CH0_070_STRIDE 1
#define IBU_P1_CETUS_CH0_070_DEPTH  1

#define IBU_P1_CETUS_CH0_071_ADDR   0x01140047L
#define IBU_P1_CETUS_CH0_071_STRIDE 1
#define IBU_P1_CETUS_CH0_071_DEPTH  1

#define IBU_P1_CETUS_CH0_072_ADDR   0x01140048L
#define IBU_P1_CETUS_CH0_072_STRIDE 1
#define IBU_P1_CETUS_CH0_072_DEPTH  1

#define IBU_P1_CETUS_CH0_073_ADDR   0x01140049L
#define IBU_P1_CETUS_CH0_073_STRIDE 1
#define IBU_P1_CETUS_CH0_073_DEPTH  1

#define IBU_P1_CETUS_CH0_074_ADDR   0x0114004aL
#define IBU_P1_CETUS_CH0_074_STRIDE 1
#define IBU_P1_CETUS_CH0_074_DEPTH  1

#define IBU_P1_CETUS_CH0_075_ADDR   0x0114004bL
#define IBU_P1_CETUS_CH0_075_STRIDE 1
#define IBU_P1_CETUS_CH0_075_DEPTH  1

#define IBU_P1_CETUS_CH0_076_ADDR   0x0114004cL
#define IBU_P1_CETUS_CH0_076_STRIDE 1
#define IBU_P1_CETUS_CH0_076_DEPTH  1

#define IBU_P1_CETUS_CH0_077_ADDR   0x0114004dL
#define IBU_P1_CETUS_CH0_077_STRIDE 1
#define IBU_P1_CETUS_CH0_077_DEPTH  1

#define IBU_P1_CETUS_CH0_078_ADDR   0x0114004eL
#define IBU_P1_CETUS_CH0_078_STRIDE 1
#define IBU_P1_CETUS_CH0_078_DEPTH  1

#define IBU_P1_CETUS_CH0_079_ADDR   0x0114004fL
#define IBU_P1_CETUS_CH0_079_STRIDE 1
#define IBU_P1_CETUS_CH0_079_DEPTH  1

#define IBU_P1_CETUS_CH0_080_ADDR   0x01140050L
#define IBU_P1_CETUS_CH0_080_STRIDE 1
#define IBU_P1_CETUS_CH0_080_DEPTH  1

#define IBU_P1_CETUS_CH0_081_ADDR   0x01140051L
#define IBU_P1_CETUS_CH0_081_STRIDE 1
#define IBU_P1_CETUS_CH0_081_DEPTH  1

#define IBU_P1_CETUS_CH0_082_ADDR   0x01140052L
#define IBU_P1_CETUS_CH0_082_STRIDE 1
#define IBU_P1_CETUS_CH0_082_DEPTH  1

#define IBU_P1_CETUS_CH0_083_ADDR   0x01140053L
#define IBU_P1_CETUS_CH0_083_STRIDE 1
#define IBU_P1_CETUS_CH0_083_DEPTH  1

#define IBU_P1_CETUS_CH0_084_ADDR   0x01140054L
#define IBU_P1_CETUS_CH0_084_STRIDE 1
#define IBU_P1_CETUS_CH0_084_DEPTH  1

#define IBU_P1_CETUS_CH0_085_ADDR   0x01140055L
#define IBU_P1_CETUS_CH0_085_STRIDE 1
#define IBU_P1_CETUS_CH0_085_DEPTH  1

#define IBU_P1_CETUS_CH0_086_ADDR   0x01140056L
#define IBU_P1_CETUS_CH0_086_STRIDE 1
#define IBU_P1_CETUS_CH0_086_DEPTH  1

#define IBU_P1_CETUS_CH0_087_ADDR   0x01140057L
#define IBU_P1_CETUS_CH0_087_STRIDE 1
#define IBU_P1_CETUS_CH0_087_DEPTH  1

#define IBU_P1_CETUS_CH0_088_ADDR   0x01140058L
#define IBU_P1_CETUS_CH0_088_STRIDE 1
#define IBU_P1_CETUS_CH0_088_DEPTH  1

#define IBU_P1_CETUS_CH0_089_ADDR   0x01140059L
#define IBU_P1_CETUS_CH0_089_STRIDE 1
#define IBU_P1_CETUS_CH0_089_DEPTH  1

#define IBU_P1_CETUS_CH0_090_ADDR   0x0114005aL
#define IBU_P1_CETUS_CH0_090_STRIDE 1
#define IBU_P1_CETUS_CH0_090_DEPTH  1

#define IBU_P1_CETUS_CH0_091_ADDR   0x0114005bL
#define IBU_P1_CETUS_CH0_091_STRIDE 1
#define IBU_P1_CETUS_CH0_091_DEPTH  1

#define IBU_P1_CETUS_CH0_092_ADDR   0x0114005cL
#define IBU_P1_CETUS_CH0_092_STRIDE 1
#define IBU_P1_CETUS_CH0_092_DEPTH  1

#define IBU_P1_CETUS_CH0_093_ADDR   0x0114005dL
#define IBU_P1_CETUS_CH0_093_STRIDE 1
#define IBU_P1_CETUS_CH0_093_DEPTH  1

#define IBU_P1_CETUS_CH0_094_ADDR   0x0114005eL
#define IBU_P1_CETUS_CH0_094_STRIDE 1
#define IBU_P1_CETUS_CH0_094_DEPTH  1

#define IBU_P1_CETUS_CH0_095_ADDR   0x0114005fL
#define IBU_P1_CETUS_CH0_095_STRIDE 1
#define IBU_P1_CETUS_CH0_095_DEPTH  1

#define IBU_P1_CETUS_CH0_096_ADDR   0x01140060L
#define IBU_P1_CETUS_CH0_096_STRIDE 1
#define IBU_P1_CETUS_CH0_096_DEPTH  1

#define IBU_P1_CETUS_CH0_097_ADDR   0x01140061L
#define IBU_P1_CETUS_CH0_097_STRIDE 1
#define IBU_P1_CETUS_CH0_097_DEPTH  1

#define IBU_P1_CETUS_CH0_098_ADDR   0x01140062L
#define IBU_P1_CETUS_CH0_098_STRIDE 1
#define IBU_P1_CETUS_CH0_098_DEPTH  1

#define IBU_P1_CETUS_CH0_099_ADDR   0x01140063L
#define IBU_P1_CETUS_CH0_099_STRIDE 1
#define IBU_P1_CETUS_CH0_099_DEPTH  1

#define IBU_P1_CETUS_CH0_100_ADDR   0x01140064L
#define IBU_P1_CETUS_CH0_100_STRIDE 1
#define IBU_P1_CETUS_CH0_100_DEPTH  1

#define IBU_P1_CETUS_CH0_101_ADDR   0x01140065L
#define IBU_P1_CETUS_CH0_101_STRIDE 1
#define IBU_P1_CETUS_CH0_101_DEPTH  1

#define IBU_P1_CETUS_CH0_102_ADDR   0x01140066L
#define IBU_P1_CETUS_CH0_102_STRIDE 1
#define IBU_P1_CETUS_CH0_102_DEPTH  1

#define IBU_P1_CETUS_CH0_103_ADDR   0x01140067L
#define IBU_P1_CETUS_CH0_103_STRIDE 1
#define IBU_P1_CETUS_CH0_103_DEPTH  1

#define IBU_P1_CETUS_CH0_104_ADDR   0x01140068L
#define IBU_P1_CETUS_CH0_104_STRIDE 1
#define IBU_P1_CETUS_CH0_104_DEPTH  1

#define IBU_P1_CETUS_CH0_105_ADDR   0x01140069L
#define IBU_P1_CETUS_CH0_105_STRIDE 1
#define IBU_P1_CETUS_CH0_105_DEPTH  1

#define IBU_P1_CETUS_CH0_106_ADDR   0x0114006aL
#define IBU_P1_CETUS_CH0_106_STRIDE 1
#define IBU_P1_CETUS_CH0_106_DEPTH  1

#define IBU_P1_CETUS_CH0_107_ADDR   0x0114006bL
#define IBU_P1_CETUS_CH0_107_STRIDE 1
#define IBU_P1_CETUS_CH0_107_DEPTH  1

#define IBU_P1_CETUS_CH0_108_ADDR   0x0114006cL
#define IBU_P1_CETUS_CH0_108_STRIDE 1
#define IBU_P1_CETUS_CH0_108_DEPTH  1

#define IBU_P1_CETUS_CH0_109_ADDR   0x0114006dL
#define IBU_P1_CETUS_CH0_109_STRIDE 1
#define IBU_P1_CETUS_CH0_109_DEPTH  1

#define IBU_P1_CETUS_CH0_110_ADDR   0x0114006eL
#define IBU_P1_CETUS_CH0_110_STRIDE 1
#define IBU_P1_CETUS_CH0_110_DEPTH  1

#define IBU_P1_CETUS_CH0_111_ADDR   0x0114006fL
#define IBU_P1_CETUS_CH0_111_STRIDE 1
#define IBU_P1_CETUS_CH0_111_DEPTH  1

#define IBU_P1_CETUS_CH0_112_ADDR   0x01140070L
#define IBU_P1_CETUS_CH0_112_STRIDE 1
#define IBU_P1_CETUS_CH0_112_DEPTH  1

#define IBU_P1_CETUS_CH0_113_ADDR   0x01140071L
#define IBU_P1_CETUS_CH0_113_STRIDE 1
#define IBU_P1_CETUS_CH0_113_DEPTH  1

#define IBU_P1_CETUS_CH0_114_ADDR   0x01140072L
#define IBU_P1_CETUS_CH0_114_STRIDE 1
#define IBU_P1_CETUS_CH0_114_DEPTH  1

#define IBU_P1_CETUS_CH0_115_ADDR   0x01140073L
#define IBU_P1_CETUS_CH0_115_STRIDE 1
#define IBU_P1_CETUS_CH0_115_DEPTH  1

#define IBU_P1_CETUS_CH0_116_ADDR   0x01140074L
#define IBU_P1_CETUS_CH0_116_STRIDE 1
#define IBU_P1_CETUS_CH0_116_DEPTH  1

#define IBU_P1_CETUS_CH0_117_ADDR   0x01140075L
#define IBU_P1_CETUS_CH0_117_STRIDE 1
#define IBU_P1_CETUS_CH0_117_DEPTH  1

#define IBU_P1_CETUS_CH0_118_ADDR   0x01140076L
#define IBU_P1_CETUS_CH0_118_STRIDE 1
#define IBU_P1_CETUS_CH0_118_DEPTH  1

#define IBU_P1_CETUS_CH0_119_ADDR   0x01140077L
#define IBU_P1_CETUS_CH0_119_STRIDE 1
#define IBU_P1_CETUS_CH0_119_DEPTH  1

#define IBU_P1_CETUS_CH0_120_ADDR   0x01140078L
#define IBU_P1_CETUS_CH0_120_STRIDE 1
#define IBU_P1_CETUS_CH0_120_DEPTH  1

#define IBU_P1_CETUS_CH0_121_ADDR   0x01140079L
#define IBU_P1_CETUS_CH0_121_STRIDE 1
#define IBU_P1_CETUS_CH0_121_DEPTH  1

#define IBU_P1_CETUS_CH0_122_ADDR   0x0114007aL
#define IBU_P1_CETUS_CH0_122_STRIDE 1
#define IBU_P1_CETUS_CH0_122_DEPTH  1

#define IBU_P1_CETUS_CH0_123_ADDR   0x0114007bL
#define IBU_P1_CETUS_CH0_123_STRIDE 1
#define IBU_P1_CETUS_CH0_123_DEPTH  1

#define IBU_P1_CETUS_CH0_124_ADDR   0x0114007cL
#define IBU_P1_CETUS_CH0_124_STRIDE 1
#define IBU_P1_CETUS_CH0_124_DEPTH  1

#define IBU_P1_CETUS_CH0_125_ADDR   0x0114007dL
#define IBU_P1_CETUS_CH0_125_STRIDE 1
#define IBU_P1_CETUS_CH0_125_DEPTH  1

#define IBU_P1_CETUS_CH0_126_ADDR   0x0114007eL
#define IBU_P1_CETUS_CH0_126_STRIDE 1
#define IBU_P1_CETUS_CH0_126_DEPTH  1

#define IBU_P1_CETUS_CH0_127_ADDR   0x0114007fL
#define IBU_P1_CETUS_CH0_127_STRIDE 1
#define IBU_P1_CETUS_CH0_127_DEPTH  1

#define IBU_P1_CETUS_CH0_128_ADDR   0x01140080L
#define IBU_P1_CETUS_CH0_128_STRIDE 1
#define IBU_P1_CETUS_CH0_128_DEPTH  1

#define IBU_P1_CETUS_CH0_129_ADDR   0x01140081L
#define IBU_P1_CETUS_CH0_129_STRIDE 1
#define IBU_P1_CETUS_CH0_129_DEPTH  1

#define IBU_P1_CETUS_CH0_130_ADDR   0x01140082L
#define IBU_P1_CETUS_CH0_130_STRIDE 1
#define IBU_P1_CETUS_CH0_130_DEPTH  1

#define IBU_P1_CETUS_CH0_131_ADDR   0x01140083L
#define IBU_P1_CETUS_CH0_131_STRIDE 1
#define IBU_P1_CETUS_CH0_131_DEPTH  1

#define IBU_P1_CETUS_CH0_132_ADDR   0x01140084L
#define IBU_P1_CETUS_CH0_132_STRIDE 1
#define IBU_P1_CETUS_CH0_132_DEPTH  1

#define IBU_P1_CETUS_CH0_133_ADDR   0x01140085L
#define IBU_P1_CETUS_CH0_133_STRIDE 1
#define IBU_P1_CETUS_CH0_133_DEPTH  1

#define IBU_P1_CETUS_CH0_134_ADDR   0x01140086L
#define IBU_P1_CETUS_CH0_134_STRIDE 1
#define IBU_P1_CETUS_CH0_134_DEPTH  1

#define IBU_P1_CETUS_CH0_135_ADDR   0x01140087L
#define IBU_P1_CETUS_CH0_135_STRIDE 1
#define IBU_P1_CETUS_CH0_135_DEPTH  1

#define IBU_P1_CETUS_CH0_136_ADDR   0x01140088L
#define IBU_P1_CETUS_CH0_136_STRIDE 1
#define IBU_P1_CETUS_CH0_136_DEPTH  1

#define IBU_P1_CETUS_CH0_137_ADDR   0x01140089L
#define IBU_P1_CETUS_CH0_137_STRIDE 1
#define IBU_P1_CETUS_CH0_137_DEPTH  1

#define IBU_P1_CETUS_CH0_138_ADDR   0x0114008aL
#define IBU_P1_CETUS_CH0_138_STRIDE 1
#define IBU_P1_CETUS_CH0_138_DEPTH  1

#define IBU_P1_CETUS_CH0_139_ADDR   0x0114008bL
#define IBU_P1_CETUS_CH0_139_STRIDE 1
#define IBU_P1_CETUS_CH0_139_DEPTH  1

	/* CETUS register */
#define IBU_P1_CETUS_CH1_000_ADDR   0x01140100L
#define IBU_P1_CETUS_CH1_000_STRIDE 1
#define IBU_P1_CETUS_CH1_000_DEPTH  1

	/* CETUS register */
#define IBU_P1_CETUS_CH1_001_ADDR   0x01140101L
#define IBU_P1_CETUS_CH1_001_STRIDE 1
#define IBU_P1_CETUS_CH1_001_DEPTH  1

	/* CETUS register */
#define IBU_P1_CETUS_CH1_002_ADDR   0x01140102L
#define IBU_P1_CETUS_CH1_002_STRIDE 1
#define IBU_P1_CETUS_CH1_002_DEPTH  1

#define IBU_P1_CETUS_CH1_003_ADDR   0x01140103L
#define IBU_P1_CETUS_CH1_003_STRIDE 1
#define IBU_P1_CETUS_CH1_003_DEPTH  1

#define IBU_P1_CETUS_CH1_004_ADDR   0x01140104L
#define IBU_P1_CETUS_CH1_004_STRIDE 1
#define IBU_P1_CETUS_CH1_004_DEPTH  1

#define IBU_P1_CETUS_CH1_005_ADDR   0x01140105L
#define IBU_P1_CETUS_CH1_005_STRIDE 1
#define IBU_P1_CETUS_CH1_005_DEPTH  1

#define IBU_P1_CETUS_CH1_006_ADDR   0x01140106L
#define IBU_P1_CETUS_CH1_006_STRIDE 1
#define IBU_P1_CETUS_CH1_006_DEPTH  1

#define IBU_P1_CETUS_CH1_007_ADDR   0x01140107L
#define IBU_P1_CETUS_CH1_007_STRIDE 1
#define IBU_P1_CETUS_CH1_007_DEPTH  1

#define IBU_P1_CETUS_CH1_008_ADDR   0x01140108L
#define IBU_P1_CETUS_CH1_008_STRIDE 1
#define IBU_P1_CETUS_CH1_008_DEPTH  1

#define IBU_P1_CETUS_CH1_009_ADDR   0x01140109L
#define IBU_P1_CETUS_CH1_009_STRIDE 1
#define IBU_P1_CETUS_CH1_009_DEPTH  1

#define IBU_P1_CETUS_CH1_010_ADDR   0x0114010aL
#define IBU_P1_CETUS_CH1_010_STRIDE 1
#define IBU_P1_CETUS_CH1_010_DEPTH  1

#define IBU_P1_CETUS_CH1_011_ADDR   0x0114010bL
#define IBU_P1_CETUS_CH1_011_STRIDE 1
#define IBU_P1_CETUS_CH1_011_DEPTH  1

#define IBU_P1_CETUS_CH1_012_ADDR   0x0114010cL
#define IBU_P1_CETUS_CH1_012_STRIDE 1
#define IBU_P1_CETUS_CH1_012_DEPTH  1

#define IBU_P1_CETUS_CH1_013_ADDR   0x0114010dL
#define IBU_P1_CETUS_CH1_013_STRIDE 1
#define IBU_P1_CETUS_CH1_013_DEPTH  1

#define IBU_P1_CETUS_CH1_014_ADDR   0x0114010eL
#define IBU_P1_CETUS_CH1_014_STRIDE 1
#define IBU_P1_CETUS_CH1_014_DEPTH  1

#define IBU_P1_CETUS_CH1_015_ADDR   0x0114010fL
#define IBU_P1_CETUS_CH1_015_STRIDE 1
#define IBU_P1_CETUS_CH1_015_DEPTH  1

#define IBU_P1_CETUS_CH1_016_ADDR   0x01140110L
#define IBU_P1_CETUS_CH1_016_STRIDE 1
#define IBU_P1_CETUS_CH1_016_DEPTH  1

#define IBU_P1_CETUS_CH1_017_ADDR   0x01140111L
#define IBU_P1_CETUS_CH1_017_STRIDE 1
#define IBU_P1_CETUS_CH1_017_DEPTH  1

#define IBU_P1_CETUS_CH1_018_ADDR   0x01140112L
#define IBU_P1_CETUS_CH1_018_STRIDE 1
#define IBU_P1_CETUS_CH1_018_DEPTH  1

#define IBU_P1_CETUS_CH1_019_ADDR   0x01140113L
#define IBU_P1_CETUS_CH1_019_STRIDE 1
#define IBU_P1_CETUS_CH1_019_DEPTH  1

#define IBU_P1_CETUS_CH1_020_ADDR   0x01140114L
#define IBU_P1_CETUS_CH1_020_STRIDE 1
#define IBU_P1_CETUS_CH1_020_DEPTH  1

#define IBU_P1_CETUS_CH1_021_ADDR   0x01140115L
#define IBU_P1_CETUS_CH1_021_STRIDE 1
#define IBU_P1_CETUS_CH1_021_DEPTH  1

#define IBU_P1_CETUS_CH1_022_ADDR   0x01140116L
#define IBU_P1_CETUS_CH1_022_STRIDE 1
#define IBU_P1_CETUS_CH1_022_DEPTH  1

#define IBU_P1_CETUS_CH1_023_ADDR   0x01140117L
#define IBU_P1_CETUS_CH1_023_STRIDE 1
#define IBU_P1_CETUS_CH1_023_DEPTH  1

#define IBU_P1_CETUS_CH1_024_ADDR   0x01140118L
#define IBU_P1_CETUS_CH1_024_STRIDE 1
#define IBU_P1_CETUS_CH1_024_DEPTH  1

#define IBU_P1_CETUS_CH1_025_ADDR   0x01140119L
#define IBU_P1_CETUS_CH1_025_STRIDE 1
#define IBU_P1_CETUS_CH1_025_DEPTH  1

#define IBU_P1_CETUS_CH1_026_ADDR   0x0114011aL
#define IBU_P1_CETUS_CH1_026_STRIDE 1
#define IBU_P1_CETUS_CH1_026_DEPTH  1

#define IBU_P1_CETUS_CH1_027_ADDR   0x0114011bL
#define IBU_P1_CETUS_CH1_027_STRIDE 1
#define IBU_P1_CETUS_CH1_027_DEPTH  1

#define IBU_P1_CETUS_CH1_028_ADDR   0x0114011cL
#define IBU_P1_CETUS_CH1_028_STRIDE 1
#define IBU_P1_CETUS_CH1_028_DEPTH  1

#define IBU_P1_CETUS_CH1_029_ADDR   0x0114011dL
#define IBU_P1_CETUS_CH1_029_STRIDE 1
#define IBU_P1_CETUS_CH1_029_DEPTH  1

#define IBU_P1_CETUS_CH1_030_ADDR   0x0114011eL
#define IBU_P1_CETUS_CH1_030_STRIDE 1
#define IBU_P1_CETUS_CH1_030_DEPTH  1

#define IBU_P1_CETUS_CH1_031_ADDR   0x0114011fL
#define IBU_P1_CETUS_CH1_031_STRIDE 1
#define IBU_P1_CETUS_CH1_031_DEPTH  1

#define IBU_P1_CETUS_CH1_032_ADDR   0x01140120L
#define IBU_P1_CETUS_CH1_032_STRIDE 1
#define IBU_P1_CETUS_CH1_032_DEPTH  1

#define IBU_P1_CETUS_CH1_033_ADDR   0x01140121L
#define IBU_P1_CETUS_CH1_033_STRIDE 1
#define IBU_P1_CETUS_CH1_033_DEPTH  1

#define IBU_P1_CETUS_CH1_034_ADDR   0x01140122L
#define IBU_P1_CETUS_CH1_034_STRIDE 1
#define IBU_P1_CETUS_CH1_034_DEPTH  1

#define IBU_P1_CETUS_CH1_035_ADDR   0x01140123L
#define IBU_P1_CETUS_CH1_035_STRIDE 1
#define IBU_P1_CETUS_CH1_035_DEPTH  1

#define IBU_P1_CETUS_CH1_036_ADDR   0x01140124L
#define IBU_P1_CETUS_CH1_036_STRIDE 1
#define IBU_P1_CETUS_CH1_036_DEPTH  1

#define IBU_P1_CETUS_CH1_037_ADDR   0x01140125L
#define IBU_P1_CETUS_CH1_037_STRIDE 1
#define IBU_P1_CETUS_CH1_037_DEPTH  1

#define IBU_P1_CETUS_CH1_038_ADDR   0x01140126L
#define IBU_P1_CETUS_CH1_038_STRIDE 1
#define IBU_P1_CETUS_CH1_038_DEPTH  1

#define IBU_P1_CETUS_CH1_039_ADDR   0x01140127L
#define IBU_P1_CETUS_CH1_039_STRIDE 1
#define IBU_P1_CETUS_CH1_039_DEPTH  1

#define IBU_P1_CETUS_CH1_040_ADDR   0x01140128L
#define IBU_P1_CETUS_CH1_040_STRIDE 1
#define IBU_P1_CETUS_CH1_040_DEPTH  1

#define IBU_P1_CETUS_CH1_041_ADDR   0x01140129L
#define IBU_P1_CETUS_CH1_041_STRIDE 1
#define IBU_P1_CETUS_CH1_041_DEPTH  1

#define IBU_P1_CETUS_CH1_042_ADDR   0x0114012aL
#define IBU_P1_CETUS_CH1_042_STRIDE 1
#define IBU_P1_CETUS_CH1_042_DEPTH  1

#define IBU_P1_CETUS_CH1_043_ADDR   0x0114012bL
#define IBU_P1_CETUS_CH1_043_STRIDE 1
#define IBU_P1_CETUS_CH1_043_DEPTH  1

#define IBU_P1_CETUS_CH1_044_ADDR   0x0114012cL
#define IBU_P1_CETUS_CH1_044_STRIDE 1
#define IBU_P1_CETUS_CH1_044_DEPTH  1

#define IBU_P1_CETUS_CH1_045_ADDR   0x0114012dL
#define IBU_P1_CETUS_CH1_045_STRIDE 1
#define IBU_P1_CETUS_CH1_045_DEPTH  1

#define IBU_P1_CETUS_CH1_046_ADDR   0x0114012eL
#define IBU_P1_CETUS_CH1_046_STRIDE 1
#define IBU_P1_CETUS_CH1_046_DEPTH  1

#define IBU_P1_CETUS_CH1_047_ADDR   0x0114012fL
#define IBU_P1_CETUS_CH1_047_STRIDE 1
#define IBU_P1_CETUS_CH1_047_DEPTH  1

#define IBU_P1_CETUS_CH1_048_ADDR   0x01140130L
#define IBU_P1_CETUS_CH1_048_STRIDE 1
#define IBU_P1_CETUS_CH1_048_DEPTH  1

#define IBU_P1_CETUS_CH1_049_ADDR   0x01140131L
#define IBU_P1_CETUS_CH1_049_STRIDE 1
#define IBU_P1_CETUS_CH1_049_DEPTH  1

#define IBU_P1_CETUS_CH1_050_ADDR   0x01140132L
#define IBU_P1_CETUS_CH1_050_STRIDE 1
#define IBU_P1_CETUS_CH1_050_DEPTH  1

#define IBU_P1_CETUS_CH1_051_ADDR   0x01140133L
#define IBU_P1_CETUS_CH1_051_STRIDE 1
#define IBU_P1_CETUS_CH1_051_DEPTH  1

#define IBU_P1_CETUS_CH1_052_ADDR   0x01140134L
#define IBU_P1_CETUS_CH1_052_STRIDE 1
#define IBU_P1_CETUS_CH1_052_DEPTH  1

#define IBU_P1_CETUS_CH1_053_ADDR   0x01140135L
#define IBU_P1_CETUS_CH1_053_STRIDE 1
#define IBU_P1_CETUS_CH1_053_DEPTH  1

#define IBU_P1_CETUS_CH1_054_ADDR   0x01140136L
#define IBU_P1_CETUS_CH1_054_STRIDE 1
#define IBU_P1_CETUS_CH1_054_DEPTH  1

#define IBU_P1_CETUS_CH1_055_ADDR   0x01140137L
#define IBU_P1_CETUS_CH1_055_STRIDE 1
#define IBU_P1_CETUS_CH1_055_DEPTH  1

#define IBU_P1_CETUS_CH1_056_ADDR   0x01140138L
#define IBU_P1_CETUS_CH1_056_STRIDE 1
#define IBU_P1_CETUS_CH1_056_DEPTH  1

#define IBU_P1_CETUS_CH1_057_ADDR   0x01140139L
#define IBU_P1_CETUS_CH1_057_STRIDE 1
#define IBU_P1_CETUS_CH1_057_DEPTH  1

#define IBU_P1_CETUS_CH1_058_ADDR   0x0114013aL
#define IBU_P1_CETUS_CH1_058_STRIDE 1
#define IBU_P1_CETUS_CH1_058_DEPTH  1

#define IBU_P1_CETUS_CH1_059_ADDR   0x0114013bL
#define IBU_P1_CETUS_CH1_059_STRIDE 1
#define IBU_P1_CETUS_CH1_059_DEPTH  1

#define IBU_P1_CETUS_CH1_060_ADDR   0x0114013cL
#define IBU_P1_CETUS_CH1_060_STRIDE 1
#define IBU_P1_CETUS_CH1_060_DEPTH  1

#define IBU_P1_CETUS_CH1_061_ADDR   0x0114013dL
#define IBU_P1_CETUS_CH1_061_STRIDE 1
#define IBU_P1_CETUS_CH1_061_DEPTH  1

#define IBU_P1_CETUS_CH1_062_ADDR   0x0114013eL
#define IBU_P1_CETUS_CH1_062_STRIDE 1
#define IBU_P1_CETUS_CH1_062_DEPTH  1

#define IBU_P1_CETUS_CH1_063_ADDR   0x0114013fL
#define IBU_P1_CETUS_CH1_063_STRIDE 1
#define IBU_P1_CETUS_CH1_063_DEPTH  1

#define IBU_P1_CETUS_CH1_064_ADDR   0x01140140L
#define IBU_P1_CETUS_CH1_064_STRIDE 1
#define IBU_P1_CETUS_CH1_064_DEPTH  1

#define IBU_P1_CETUS_CH1_065_ADDR   0x01140141L
#define IBU_P1_CETUS_CH1_065_STRIDE 1
#define IBU_P1_CETUS_CH1_065_DEPTH  1

#define IBU_P1_CETUS_CH1_066_ADDR   0x01140142L
#define IBU_P1_CETUS_CH1_066_STRIDE 1
#define IBU_P1_CETUS_CH1_066_DEPTH  1

#define IBU_P1_CETUS_CH1_067_ADDR   0x01140143L
#define IBU_P1_CETUS_CH1_067_STRIDE 1
#define IBU_P1_CETUS_CH1_067_DEPTH  1

#define IBU_P1_CETUS_CH1_068_ADDR   0x01140144L
#define IBU_P1_CETUS_CH1_068_STRIDE 1
#define IBU_P1_CETUS_CH1_068_DEPTH  1

#define IBU_P1_CETUS_CH1_069_ADDR   0x01140145L
#define IBU_P1_CETUS_CH1_069_STRIDE 1
#define IBU_P1_CETUS_CH1_069_DEPTH  1

#define IBU_P1_CETUS_CH1_070_ADDR   0x01140146L
#define IBU_P1_CETUS_CH1_070_STRIDE 1
#define IBU_P1_CETUS_CH1_070_DEPTH  1

#define IBU_P1_CETUS_CH1_071_ADDR   0x01140147L
#define IBU_P1_CETUS_CH1_071_STRIDE 1
#define IBU_P1_CETUS_CH1_071_DEPTH  1

#define IBU_P1_CETUS_CH1_072_ADDR   0x01140148L
#define IBU_P1_CETUS_CH1_072_STRIDE 1
#define IBU_P1_CETUS_CH1_072_DEPTH  1

#define IBU_P1_CETUS_CH1_073_ADDR   0x01140149L
#define IBU_P1_CETUS_CH1_073_STRIDE 1
#define IBU_P1_CETUS_CH1_073_DEPTH  1

#define IBU_P1_CETUS_CH1_074_ADDR   0x0114014aL
#define IBU_P1_CETUS_CH1_074_STRIDE 1
#define IBU_P1_CETUS_CH1_074_DEPTH  1

#define IBU_P1_CETUS_CH1_075_ADDR   0x0114014bL
#define IBU_P1_CETUS_CH1_075_STRIDE 1
#define IBU_P1_CETUS_CH1_075_DEPTH  1

#define IBU_P1_CETUS_CH1_076_ADDR   0x0114014cL
#define IBU_P1_CETUS_CH1_076_STRIDE 1
#define IBU_P1_CETUS_CH1_076_DEPTH  1

#define IBU_P1_CETUS_CH1_077_ADDR   0x0114014dL
#define IBU_P1_CETUS_CH1_077_STRIDE 1
#define IBU_P1_CETUS_CH1_077_DEPTH  1

#define IBU_P1_CETUS_CH1_078_ADDR   0x0114014eL
#define IBU_P1_CETUS_CH1_078_STRIDE 1
#define IBU_P1_CETUS_CH1_078_DEPTH  1

#define IBU_P1_CETUS_CH1_079_ADDR   0x0114014fL
#define IBU_P1_CETUS_CH1_079_STRIDE 1
#define IBU_P1_CETUS_CH1_079_DEPTH  1

#define IBU_P1_CETUS_CH1_080_ADDR   0x01140150L
#define IBU_P1_CETUS_CH1_080_STRIDE 1
#define IBU_P1_CETUS_CH1_080_DEPTH  1

#define IBU_P1_CETUS_CH1_081_ADDR   0x01140151L
#define IBU_P1_CETUS_CH1_081_STRIDE 1
#define IBU_P1_CETUS_CH1_081_DEPTH  1

#define IBU_P1_CETUS_CH1_082_ADDR   0x01140152L
#define IBU_P1_CETUS_CH1_082_STRIDE 1
#define IBU_P1_CETUS_CH1_082_DEPTH  1

#define IBU_P1_CETUS_CH1_083_ADDR   0x01140153L
#define IBU_P1_CETUS_CH1_083_STRIDE 1
#define IBU_P1_CETUS_CH1_083_DEPTH  1

#define IBU_P1_CETUS_CH1_084_ADDR   0x01140154L
#define IBU_P1_CETUS_CH1_084_STRIDE 1
#define IBU_P1_CETUS_CH1_084_DEPTH  1

#define IBU_P1_CETUS_CH1_085_ADDR   0x01140155L
#define IBU_P1_CETUS_CH1_085_STRIDE 1
#define IBU_P1_CETUS_CH1_085_DEPTH  1

#define IBU_P1_CETUS_CH1_086_ADDR   0x01140156L
#define IBU_P1_CETUS_CH1_086_STRIDE 1
#define IBU_P1_CETUS_CH1_086_DEPTH  1

#define IBU_P1_CETUS_CH1_087_ADDR   0x01140157L
#define IBU_P1_CETUS_CH1_087_STRIDE 1
#define IBU_P1_CETUS_CH1_087_DEPTH  1

#define IBU_P1_CETUS_CH1_088_ADDR   0x01140158L
#define IBU_P1_CETUS_CH1_088_STRIDE 1
#define IBU_P1_CETUS_CH1_088_DEPTH  1

#define IBU_P1_CETUS_CH1_089_ADDR   0x01140159L
#define IBU_P1_CETUS_CH1_089_STRIDE 1
#define IBU_P1_CETUS_CH1_089_DEPTH  1

#define IBU_P1_CETUS_CH1_090_ADDR   0x0114015aL
#define IBU_P1_CETUS_CH1_090_STRIDE 1
#define IBU_P1_CETUS_CH1_090_DEPTH  1

#define IBU_P1_CETUS_CH1_091_ADDR   0x0114015bL
#define IBU_P1_CETUS_CH1_091_STRIDE 1
#define IBU_P1_CETUS_CH1_091_DEPTH  1

#define IBU_P1_CETUS_CH1_092_ADDR   0x0114015cL
#define IBU_P1_CETUS_CH1_092_STRIDE 1
#define IBU_P1_CETUS_CH1_092_DEPTH  1

#define IBU_P1_CETUS_CH1_093_ADDR   0x0114015dL
#define IBU_P1_CETUS_CH1_093_STRIDE 1
#define IBU_P1_CETUS_CH1_093_DEPTH  1

#define IBU_P1_CETUS_CH1_094_ADDR   0x0114015eL
#define IBU_P1_CETUS_CH1_094_STRIDE 1
#define IBU_P1_CETUS_CH1_094_DEPTH  1

#define IBU_P1_CETUS_CH1_095_ADDR   0x0114015fL
#define IBU_P1_CETUS_CH1_095_STRIDE 1
#define IBU_P1_CETUS_CH1_095_DEPTH  1

#define IBU_P1_CETUS_CH1_096_ADDR   0x01140160L
#define IBU_P1_CETUS_CH1_096_STRIDE 1
#define IBU_P1_CETUS_CH1_096_DEPTH  1

#define IBU_P1_CETUS_CH1_097_ADDR   0x01140161L
#define IBU_P1_CETUS_CH1_097_STRIDE 1
#define IBU_P1_CETUS_CH1_097_DEPTH  1

#define IBU_P1_CETUS_CH1_098_ADDR   0x01140162L
#define IBU_P1_CETUS_CH1_098_STRIDE 1
#define IBU_P1_CETUS_CH1_098_DEPTH  1

#define IBU_P1_CETUS_CH1_099_ADDR   0x01140163L
#define IBU_P1_CETUS_CH1_099_STRIDE 1
#define IBU_P1_CETUS_CH1_099_DEPTH  1

#define IBU_P1_CETUS_CH1_100_ADDR   0x01140164L
#define IBU_P1_CETUS_CH1_100_STRIDE 1
#define IBU_P1_CETUS_CH1_100_DEPTH  1

#define IBU_P1_CETUS_CH1_101_ADDR   0x01140165L
#define IBU_P1_CETUS_CH1_101_STRIDE 1
#define IBU_P1_CETUS_CH1_101_DEPTH  1

#define IBU_P1_CETUS_CH1_102_ADDR   0x01140166L
#define IBU_P1_CETUS_CH1_102_STRIDE 1
#define IBU_P1_CETUS_CH1_102_DEPTH  1

#define IBU_P1_CETUS_CH1_103_ADDR   0x01140167L
#define IBU_P1_CETUS_CH1_103_STRIDE 1
#define IBU_P1_CETUS_CH1_103_DEPTH  1

#define IBU_P1_CETUS_CH1_104_ADDR   0x01140168L
#define IBU_P1_CETUS_CH1_104_STRIDE 1
#define IBU_P1_CETUS_CH1_104_DEPTH  1

#define IBU_P1_CETUS_CH1_105_ADDR   0x01140169L
#define IBU_P1_CETUS_CH1_105_STRIDE 1
#define IBU_P1_CETUS_CH1_105_DEPTH  1

#define IBU_P1_CETUS_CH1_106_ADDR   0x0114016aL
#define IBU_P1_CETUS_CH1_106_STRIDE 1
#define IBU_P1_CETUS_CH1_106_DEPTH  1

#define IBU_P1_CETUS_CH1_107_ADDR   0x0114016bL
#define IBU_P1_CETUS_CH1_107_STRIDE 1
#define IBU_P1_CETUS_CH1_107_DEPTH  1

#define IBU_P1_CETUS_CH1_108_ADDR   0x0114016cL
#define IBU_P1_CETUS_CH1_108_STRIDE 1
#define IBU_P1_CETUS_CH1_108_DEPTH  1

#define IBU_P1_CETUS_CH1_109_ADDR   0x0114016dL
#define IBU_P1_CETUS_CH1_109_STRIDE 1
#define IBU_P1_CETUS_CH1_109_DEPTH  1

#define IBU_P1_CETUS_CH1_110_ADDR   0x0114016eL
#define IBU_P1_CETUS_CH1_110_STRIDE 1
#define IBU_P1_CETUS_CH1_110_DEPTH  1

#define IBU_P1_CETUS_CH1_111_ADDR   0x0114016fL
#define IBU_P1_CETUS_CH1_111_STRIDE 1
#define IBU_P1_CETUS_CH1_111_DEPTH  1

#define IBU_P1_CETUS_CH1_112_ADDR   0x01140170L
#define IBU_P1_CETUS_CH1_112_STRIDE 1
#define IBU_P1_CETUS_CH1_112_DEPTH  1

#define IBU_P1_CETUS_CH1_113_ADDR   0x01140171L
#define IBU_P1_CETUS_CH1_113_STRIDE 1
#define IBU_P1_CETUS_CH1_113_DEPTH  1

#define IBU_P1_CETUS_CH1_114_ADDR   0x01140172L
#define IBU_P1_CETUS_CH1_114_STRIDE 1
#define IBU_P1_CETUS_CH1_114_DEPTH  1

#define IBU_P1_CETUS_CH1_115_ADDR   0x01140173L
#define IBU_P1_CETUS_CH1_115_STRIDE 1
#define IBU_P1_CETUS_CH1_115_DEPTH  1

#define IBU_P1_CETUS_CH1_116_ADDR   0x01140174L
#define IBU_P1_CETUS_CH1_116_STRIDE 1
#define IBU_P1_CETUS_CH1_116_DEPTH  1

#define IBU_P1_CETUS_CH1_117_ADDR   0x01140175L
#define IBU_P1_CETUS_CH1_117_STRIDE 1
#define IBU_P1_CETUS_CH1_117_DEPTH  1

#define IBU_P1_CETUS_CH1_118_ADDR   0x01140176L
#define IBU_P1_CETUS_CH1_118_STRIDE 1
#define IBU_P1_CETUS_CH1_118_DEPTH  1

#define IBU_P1_CETUS_CH1_119_ADDR   0x01140177L
#define IBU_P1_CETUS_CH1_119_STRIDE 1
#define IBU_P1_CETUS_CH1_119_DEPTH  1

#define IBU_P1_CETUS_CH1_120_ADDR   0x01140178L
#define IBU_P1_CETUS_CH1_120_STRIDE 1
#define IBU_P1_CETUS_CH1_120_DEPTH  1

#define IBU_P1_CETUS_CH1_121_ADDR   0x01140179L
#define IBU_P1_CETUS_CH1_121_STRIDE 1
#define IBU_P1_CETUS_CH1_121_DEPTH  1

#define IBU_P1_CETUS_CH1_122_ADDR   0x0114017aL
#define IBU_P1_CETUS_CH1_122_STRIDE 1
#define IBU_P1_CETUS_CH1_122_DEPTH  1

#define IBU_P1_CETUS_CH1_123_ADDR   0x0114017bL
#define IBU_P1_CETUS_CH1_123_STRIDE 1
#define IBU_P1_CETUS_CH1_123_DEPTH  1

#define IBU_P1_CETUS_CH1_124_ADDR   0x0114017cL
#define IBU_P1_CETUS_CH1_124_STRIDE 1
#define IBU_P1_CETUS_CH1_124_DEPTH  1

#define IBU_P1_CETUS_CH1_125_ADDR   0x0114017dL
#define IBU_P1_CETUS_CH1_125_STRIDE 1
#define IBU_P1_CETUS_CH1_125_DEPTH  1

#define IBU_P1_CETUS_CH1_126_ADDR   0x0114017eL
#define IBU_P1_CETUS_CH1_126_STRIDE 1
#define IBU_P1_CETUS_CH1_126_DEPTH  1

#define IBU_P1_CETUS_CH1_127_ADDR   0x0114017fL
#define IBU_P1_CETUS_CH1_127_STRIDE 1
#define IBU_P1_CETUS_CH1_127_DEPTH  1

#define IBU_P1_CETUS_CH1_128_ADDR   0x01140180L
#define IBU_P1_CETUS_CH1_128_STRIDE 1
#define IBU_P1_CETUS_CH1_128_DEPTH  1

#define IBU_P1_CETUS_CH1_129_ADDR   0x01140181L
#define IBU_P1_CETUS_CH1_129_STRIDE 1
#define IBU_P1_CETUS_CH1_129_DEPTH  1

#define IBU_P1_CETUS_CH1_130_ADDR   0x01140182L
#define IBU_P1_CETUS_CH1_130_STRIDE 1
#define IBU_P1_CETUS_CH1_130_DEPTH  1

#define IBU_P1_CETUS_CH1_131_ADDR   0x01140183L
#define IBU_P1_CETUS_CH1_131_STRIDE 1
#define IBU_P1_CETUS_CH1_131_DEPTH  1

#define IBU_P1_CETUS_CH1_132_ADDR   0x01140184L
#define IBU_P1_CETUS_CH1_132_STRIDE 1
#define IBU_P1_CETUS_CH1_132_DEPTH  1

#define IBU_P1_CETUS_CH1_133_ADDR   0x01140185L
#define IBU_P1_CETUS_CH1_133_STRIDE 1
#define IBU_P1_CETUS_CH1_133_DEPTH  1

#define IBU_P1_CETUS_CH1_134_ADDR   0x01140186L
#define IBU_P1_CETUS_CH1_134_STRIDE 1
#define IBU_P1_CETUS_CH1_134_DEPTH  1

#define IBU_P1_CETUS_CH1_135_ADDR   0x01140187L
#define IBU_P1_CETUS_CH1_135_STRIDE 1
#define IBU_P1_CETUS_CH1_135_DEPTH  1

#define IBU_P1_CETUS_CH1_136_ADDR   0x01140188L
#define IBU_P1_CETUS_CH1_136_STRIDE 1
#define IBU_P1_CETUS_CH1_136_DEPTH  1

#define IBU_P1_CETUS_CH1_137_ADDR   0x01140189L
#define IBU_P1_CETUS_CH1_137_STRIDE 1
#define IBU_P1_CETUS_CH1_137_DEPTH  1

#define IBU_P1_CETUS_CH1_138_ADDR   0x0114018aL
#define IBU_P1_CETUS_CH1_138_STRIDE 1
#define IBU_P1_CETUS_CH1_138_DEPTH  1

#define IBU_P1_CETUS_CH1_139_ADDR   0x0114018bL
#define IBU_P1_CETUS_CH1_139_STRIDE 1
#define IBU_P1_CETUS_CH1_139_DEPTH  1

#define IBU_P1_CETUS_PLLA_CONTROL0_ADDR   0x01140200L
#define IBU_P1_CETUS_PLLA_CONTROL0_STRIDE 1
#define IBU_P1_CETUS_PLLA_CONTROL0_DEPTH  1

#define IBU_P1_CETUS_PLLA_CONTROL1_ADDR   0x01140201L
#define IBU_P1_CETUS_PLLA_CONTROL1_STRIDE 1
#define IBU_P1_CETUS_PLLA_CONTROL1_DEPTH  1

#define IBU_P1_CETUS_PLLA_CONTROL2_ADDR   0x01140202L
#define IBU_P1_CETUS_PLLA_CONTROL2_STRIDE 1
#define IBU_P1_CETUS_PLLA_CONTROL2_DEPTH  1

#define IBU_P1_CETUS_PLLA_EXTFB_CNTR_ADDR   0x01140203L
#define IBU_P1_CETUS_PLLA_EXTFB_CNTR_STRIDE 1
#define IBU_P1_CETUS_PLLA_EXTFB_CNTR_DEPTH  1

#define IBU_P1_CETUS_PLLA_FBCNT_ATO_ADDR   0x01140204L
#define IBU_P1_CETUS_PLLA_FBCNT_ATO_STRIDE 1
#define IBU_P1_CETUS_PLLA_FBCNT_ATO_DEPTH  1

#define IBU_P1_CETUS_PLLA_SPARE_USRCNTR_ADDR   0x01140205L
#define IBU_P1_CETUS_PLLA_SPARE_USRCNTR_STRIDE 1
#define IBU_P1_CETUS_PLLA_SPARE_USRCNTR_DEPTH  1

#define IBU_P1_CETUS_PLLA_DIV_EN_ADDR   0x01140206L
#define IBU_P1_CETUS_PLLA_DIV_EN_STRIDE 1
#define IBU_P1_CETUS_PLLA_DIV_EN_DEPTH  1

#define IBU_P1_CETUS_PLLA_VCO_WAIT_CNT_ADDR   0x01140207L
#define IBU_P1_CETUS_PLLA_VCO_WAIT_CNT_STRIDE 1
#define IBU_P1_CETUS_PLLA_VCO_WAIT_CNT_DEPTH  1

#define IBU_P1_CETUS_PLLA_STATUS0_ADDR   0x01140208L
#define IBU_P1_CETUS_PLLA_STATUS0_STRIDE 1
#define IBU_P1_CETUS_PLLA_STATUS0_DEPTH  1

#define IBU_P1_CETUS_PLLA_STATUS1_ADDR   0x01140209L
#define IBU_P1_CETUS_PLLA_STATUS1_STRIDE 1
#define IBU_P1_CETUS_PLLA_STATUS1_DEPTH  1

#define IBU_P1_CETUS_PLLA_010_ADDR   0x0114020aL
#define IBU_P1_CETUS_PLLA_010_STRIDE 1
#define IBU_P1_CETUS_PLLA_010_DEPTH  1

#define IBU_P1_CETUS_PLLA_011_ADDR   0x0114020bL
#define IBU_P1_CETUS_PLLA_011_STRIDE 1
#define IBU_P1_CETUS_PLLA_011_DEPTH  1

#define IBU_P1_CETUS_PLLA_012_ADDR   0x0114020cL
#define IBU_P1_CETUS_PLLA_012_STRIDE 1
#define IBU_P1_CETUS_PLLA_012_DEPTH  1

#define IBU_P1_CETUS_PLLA_013_ADDR   0x0114020dL
#define IBU_P1_CETUS_PLLA_013_STRIDE 1
#define IBU_P1_CETUS_PLLA_013_DEPTH  1

#define IBU_P1_CETUS_PLLA_014_ADDR   0x0114020eL
#define IBU_P1_CETUS_PLLA_014_STRIDE 1
#define IBU_P1_CETUS_PLLA_014_DEPTH  1

#define IBU_P1_CETUS_PLLA_015_ADDR   0x0114020fL
#define IBU_P1_CETUS_PLLA_015_STRIDE 1
#define IBU_P1_CETUS_PLLA_015_DEPTH  1

#define IBU_P1_CETUS_PLLA_016_ADDR   0x01140210L
#define IBU_P1_CETUS_PLLA_016_STRIDE 1
#define IBU_P1_CETUS_PLLA_016_DEPTH  1

#define IBU_P1_CETUS_PLLA_017_ADDR   0x01140211L
#define IBU_P1_CETUS_PLLA_017_STRIDE 1
#define IBU_P1_CETUS_PLLA_017_DEPTH  1

#define IBU_P1_CETUS_PLLA_018_ADDR   0x01140212L
#define IBU_P1_CETUS_PLLA_018_STRIDE 1
#define IBU_P1_CETUS_PLLA_018_DEPTH  1

#define IBU_P1_CETUS_PLLA_019_ADDR   0x01140213L
#define IBU_P1_CETUS_PLLA_019_STRIDE 1
#define IBU_P1_CETUS_PLLA_019_DEPTH  1

#define IBU_P1_CETUS_PLLA_020_ADDR   0x01140214L
#define IBU_P1_CETUS_PLLA_020_STRIDE 1
#define IBU_P1_CETUS_PLLA_020_DEPTH  1

#define IBU_P1_CETUS_PLLA_021_ADDR   0x01140215L
#define IBU_P1_CETUS_PLLA_021_STRIDE 1
#define IBU_P1_CETUS_PLLA_021_DEPTH  1

#define IBU_P1_CETUS_PLLA_022_ADDR   0x01140216L
#define IBU_P1_CETUS_PLLA_022_STRIDE 1
#define IBU_P1_CETUS_PLLA_022_DEPTH  1

#define IBU_P1_CETUS_PLLA_023_ADDR   0x01140217L
#define IBU_P1_CETUS_PLLA_023_STRIDE 1
#define IBU_P1_CETUS_PLLA_023_DEPTH  1

#define IBU_P1_CETUS_PLLA_024_ADDR   0x01140218L
#define IBU_P1_CETUS_PLLA_024_STRIDE 1
#define IBU_P1_CETUS_PLLA_024_DEPTH  1

	/* CETUS register */
#define IBU_P1_CETUS_CH2_000_ADDR   0x01140300L
#define IBU_P1_CETUS_CH2_000_STRIDE 1
#define IBU_P1_CETUS_CH2_000_DEPTH  1

	/* CETUS register */
#define IBU_P1_CETUS_CH2_001_ADDR   0x01140301L
#define IBU_P1_CETUS_CH2_001_STRIDE 1
#define IBU_P1_CETUS_CH2_001_DEPTH  1

	/* CETUS register */
#define IBU_P1_CETUS_CH2_002_ADDR   0x01140302L
#define IBU_P1_CETUS_CH2_002_STRIDE 1
#define IBU_P1_CETUS_CH2_002_DEPTH  1

#define IBU_P1_CETUS_CH2_003_ADDR   0x01140303L
#define IBU_P1_CETUS_CH2_003_STRIDE 1
#define IBU_P1_CETUS_CH2_003_DEPTH  1

#define IBU_P1_CETUS_CH2_004_ADDR   0x01140304L
#define IBU_P1_CETUS_CH2_004_STRIDE 1
#define IBU_P1_CETUS_CH2_004_DEPTH  1

#define IBU_P1_CETUS_CH2_005_ADDR   0x01140305L
#define IBU_P1_CETUS_CH2_005_STRIDE 1
#define IBU_P1_CETUS_CH2_005_DEPTH  1

#define IBU_P1_CETUS_CH2_006_ADDR   0x01140306L
#define IBU_P1_CETUS_CH2_006_STRIDE 1
#define IBU_P1_CETUS_CH2_006_DEPTH  1

#define IBU_P1_CETUS_CH2_007_ADDR   0x01140307L
#define IBU_P1_CETUS_CH2_007_STRIDE 1
#define IBU_P1_CETUS_CH2_007_DEPTH  1

#define IBU_P1_CETUS_CH2_008_ADDR   0x01140308L
#define IBU_P1_CETUS_CH2_008_STRIDE 1
#define IBU_P1_CETUS_CH2_008_DEPTH  1

#define IBU_P1_CETUS_CH2_009_ADDR   0x01140309L
#define IBU_P1_CETUS_CH2_009_STRIDE 1
#define IBU_P1_CETUS_CH2_009_DEPTH  1

#define IBU_P1_CETUS_CH2_010_ADDR   0x0114030aL
#define IBU_P1_CETUS_CH2_010_STRIDE 1
#define IBU_P1_CETUS_CH2_010_DEPTH  1

#define IBU_P1_CETUS_CH2_011_ADDR   0x0114030bL
#define IBU_P1_CETUS_CH2_011_STRIDE 1
#define IBU_P1_CETUS_CH2_011_DEPTH  1

#define IBU_P1_CETUS_CH2_012_ADDR   0x0114030cL
#define IBU_P1_CETUS_CH2_012_STRIDE 1
#define IBU_P1_CETUS_CH2_012_DEPTH  1

#define IBU_P1_CETUS_CH2_013_ADDR   0x0114030dL
#define IBU_P1_CETUS_CH2_013_STRIDE 1
#define IBU_P1_CETUS_CH2_013_DEPTH  1

#define IBU_P1_CETUS_CH2_014_ADDR   0x0114030eL
#define IBU_P1_CETUS_CH2_014_STRIDE 1
#define IBU_P1_CETUS_CH2_014_DEPTH  1

#define IBU_P1_CETUS_CH2_015_ADDR   0x0114030fL
#define IBU_P1_CETUS_CH2_015_STRIDE 1
#define IBU_P1_CETUS_CH2_015_DEPTH  1

#define IBU_P1_CETUS_CH2_016_ADDR   0x01140310L
#define IBU_P1_CETUS_CH2_016_STRIDE 1
#define IBU_P1_CETUS_CH2_016_DEPTH  1

#define IBU_P1_CETUS_CH2_017_ADDR   0x01140311L
#define IBU_P1_CETUS_CH2_017_STRIDE 1
#define IBU_P1_CETUS_CH2_017_DEPTH  1

#define IBU_P1_CETUS_CH2_018_ADDR   0x01140312L
#define IBU_P1_CETUS_CH2_018_STRIDE 1
#define IBU_P1_CETUS_CH2_018_DEPTH  1

#define IBU_P1_CETUS_CH2_019_ADDR   0x01140313L
#define IBU_P1_CETUS_CH2_019_STRIDE 1
#define IBU_P1_CETUS_CH2_019_DEPTH  1

#define IBU_P1_CETUS_CH2_020_ADDR   0x01140314L
#define IBU_P1_CETUS_CH2_020_STRIDE 1
#define IBU_P1_CETUS_CH2_020_DEPTH  1

#define IBU_P1_CETUS_CH2_021_ADDR   0x01140315L
#define IBU_P1_CETUS_CH2_021_STRIDE 1
#define IBU_P1_CETUS_CH2_021_DEPTH  1

#define IBU_P1_CETUS_CH2_022_ADDR   0x01140316L
#define IBU_P1_CETUS_CH2_022_STRIDE 1
#define IBU_P1_CETUS_CH2_022_DEPTH  1

#define IBU_P1_CETUS_CH2_023_ADDR   0x01140317L
#define IBU_P1_CETUS_CH2_023_STRIDE 1
#define IBU_P1_CETUS_CH2_023_DEPTH  1

#define IBU_P1_CETUS_CH2_024_ADDR   0x01140318L
#define IBU_P1_CETUS_CH2_024_STRIDE 1
#define IBU_P1_CETUS_CH2_024_DEPTH  1

#define IBU_P1_CETUS_CH2_025_ADDR   0x01140319L
#define IBU_P1_CETUS_CH2_025_STRIDE 1
#define IBU_P1_CETUS_CH2_025_DEPTH  1

#define IBU_P1_CETUS_CH2_026_ADDR   0x0114031aL
#define IBU_P1_CETUS_CH2_026_STRIDE 1
#define IBU_P1_CETUS_CH2_026_DEPTH  1

#define IBU_P1_CETUS_CH2_027_ADDR   0x0114031bL
#define IBU_P1_CETUS_CH2_027_STRIDE 1
#define IBU_P1_CETUS_CH2_027_DEPTH  1

#define IBU_P1_CETUS_CH2_028_ADDR   0x0114031cL
#define IBU_P1_CETUS_CH2_028_STRIDE 1
#define IBU_P1_CETUS_CH2_028_DEPTH  1

#define IBU_P1_CETUS_CH2_029_ADDR   0x0114031dL
#define IBU_P1_CETUS_CH2_029_STRIDE 1
#define IBU_P1_CETUS_CH2_029_DEPTH  1

#define IBU_P1_CETUS_CH2_030_ADDR   0x0114031eL
#define IBU_P1_CETUS_CH2_030_STRIDE 1
#define IBU_P1_CETUS_CH2_030_DEPTH  1

#define IBU_P1_CETUS_CH2_031_ADDR   0x0114031fL
#define IBU_P1_CETUS_CH2_031_STRIDE 1
#define IBU_P1_CETUS_CH2_031_DEPTH  1

#define IBU_P1_CETUS_CH2_032_ADDR   0x01140320L
#define IBU_P1_CETUS_CH2_032_STRIDE 1
#define IBU_P1_CETUS_CH2_032_DEPTH  1

#define IBU_P1_CETUS_CH2_033_ADDR   0x01140321L
#define IBU_P1_CETUS_CH2_033_STRIDE 1
#define IBU_P1_CETUS_CH2_033_DEPTH  1

#define IBU_P1_CETUS_CH2_034_ADDR   0x01140322L
#define IBU_P1_CETUS_CH2_034_STRIDE 1
#define IBU_P1_CETUS_CH2_034_DEPTH  1

#define IBU_P1_CETUS_CH2_035_ADDR   0x01140323L
#define IBU_P1_CETUS_CH2_035_STRIDE 1
#define IBU_P1_CETUS_CH2_035_DEPTH  1

#define IBU_P1_CETUS_CH2_036_ADDR   0x01140324L
#define IBU_P1_CETUS_CH2_036_STRIDE 1
#define IBU_P1_CETUS_CH2_036_DEPTH  1

#define IBU_P1_CETUS_CH2_037_ADDR   0x01140325L
#define IBU_P1_CETUS_CH2_037_STRIDE 1
#define IBU_P1_CETUS_CH2_037_DEPTH  1

#define IBU_P1_CETUS_CH2_038_ADDR   0x01140326L
#define IBU_P1_CETUS_CH2_038_STRIDE 1
#define IBU_P1_CETUS_CH2_038_DEPTH  1

#define IBU_P1_CETUS_CH2_039_ADDR   0x01140327L
#define IBU_P1_CETUS_CH2_039_STRIDE 1
#define IBU_P1_CETUS_CH2_039_DEPTH  1

#define IBU_P1_CETUS_CH2_040_ADDR   0x01140328L
#define IBU_P1_CETUS_CH2_040_STRIDE 1
#define IBU_P1_CETUS_CH2_040_DEPTH  1

#define IBU_P1_CETUS_CH2_041_ADDR   0x01140329L
#define IBU_P1_CETUS_CH2_041_STRIDE 1
#define IBU_P1_CETUS_CH2_041_DEPTH  1

#define IBU_P1_CETUS_CH2_042_ADDR   0x0114032aL
#define IBU_P1_CETUS_CH2_042_STRIDE 1
#define IBU_P1_CETUS_CH2_042_DEPTH  1

#define IBU_P1_CETUS_CH2_043_ADDR   0x0114032bL
#define IBU_P1_CETUS_CH2_043_STRIDE 1
#define IBU_P1_CETUS_CH2_043_DEPTH  1

#define IBU_P1_CETUS_CH2_044_ADDR   0x0114032cL
#define IBU_P1_CETUS_CH2_044_STRIDE 1
#define IBU_P1_CETUS_CH2_044_DEPTH  1

#define IBU_P1_CETUS_CH2_045_ADDR   0x0114032dL
#define IBU_P1_CETUS_CH2_045_STRIDE 1
#define IBU_P1_CETUS_CH2_045_DEPTH  1

#define IBU_P1_CETUS_CH2_046_ADDR   0x0114032eL
#define IBU_P1_CETUS_CH2_046_STRIDE 1
#define IBU_P1_CETUS_CH2_046_DEPTH  1

#define IBU_P1_CETUS_CH2_047_ADDR   0x0114032fL
#define IBU_P1_CETUS_CH2_047_STRIDE 1
#define IBU_P1_CETUS_CH2_047_DEPTH  1

#define IBU_P1_CETUS_CH2_048_ADDR   0x01140330L
#define IBU_P1_CETUS_CH2_048_STRIDE 1
#define IBU_P1_CETUS_CH2_048_DEPTH  1

#define IBU_P1_CETUS_CH2_049_ADDR   0x01140331L
#define IBU_P1_CETUS_CH2_049_STRIDE 1
#define IBU_P1_CETUS_CH2_049_DEPTH  1

#define IBU_P1_CETUS_CH2_050_ADDR   0x01140332L
#define IBU_P1_CETUS_CH2_050_STRIDE 1
#define IBU_P1_CETUS_CH2_050_DEPTH  1

#define IBU_P1_CETUS_CH2_051_ADDR   0x01140333L
#define IBU_P1_CETUS_CH2_051_STRIDE 1
#define IBU_P1_CETUS_CH2_051_DEPTH  1

#define IBU_P1_CETUS_CH2_052_ADDR   0x01140334L
#define IBU_P1_CETUS_CH2_052_STRIDE 1
#define IBU_P1_CETUS_CH2_052_DEPTH  1

#define IBU_P1_CETUS_CH2_053_ADDR   0x01140335L
#define IBU_P1_CETUS_CH2_053_STRIDE 1
#define IBU_P1_CETUS_CH2_053_DEPTH  1

#define IBU_P1_CETUS_CH2_054_ADDR   0x01140336L
#define IBU_P1_CETUS_CH2_054_STRIDE 1
#define IBU_P1_CETUS_CH2_054_DEPTH  1

#define IBU_P1_CETUS_CH2_055_ADDR   0x01140337L
#define IBU_P1_CETUS_CH2_055_STRIDE 1
#define IBU_P1_CETUS_CH2_055_DEPTH  1

#define IBU_P1_CETUS_CH2_056_ADDR   0x01140338L
#define IBU_P1_CETUS_CH2_056_STRIDE 1
#define IBU_P1_CETUS_CH2_056_DEPTH  1

#define IBU_P1_CETUS_CH2_057_ADDR   0x01140339L
#define IBU_P1_CETUS_CH2_057_STRIDE 1
#define IBU_P1_CETUS_CH2_057_DEPTH  1

#define IBU_P1_CETUS_CH2_058_ADDR   0x0114033aL
#define IBU_P1_CETUS_CH2_058_STRIDE 1
#define IBU_P1_CETUS_CH2_058_DEPTH  1

#define IBU_P1_CETUS_CH2_059_ADDR   0x0114033bL
#define IBU_P1_CETUS_CH2_059_STRIDE 1
#define IBU_P1_CETUS_CH2_059_DEPTH  1

#define IBU_P1_CETUS_CH2_060_ADDR   0x0114033cL
#define IBU_P1_CETUS_CH2_060_STRIDE 1
#define IBU_P1_CETUS_CH2_060_DEPTH  1

#define IBU_P1_CETUS_CH2_061_ADDR   0x0114033dL
#define IBU_P1_CETUS_CH2_061_STRIDE 1
#define IBU_P1_CETUS_CH2_061_DEPTH  1

#define IBU_P1_CETUS_CH2_062_ADDR   0x0114033eL
#define IBU_P1_CETUS_CH2_062_STRIDE 1
#define IBU_P1_CETUS_CH2_062_DEPTH  1

#define IBU_P1_CETUS_CH2_063_ADDR   0x0114033fL
#define IBU_P1_CETUS_CH2_063_STRIDE 1
#define IBU_P1_CETUS_CH2_063_DEPTH  1

#define IBU_P1_CETUS_CH2_064_ADDR   0x01140340L
#define IBU_P1_CETUS_CH2_064_STRIDE 1
#define IBU_P1_CETUS_CH2_064_DEPTH  1

#define IBU_P1_CETUS_CH2_065_ADDR   0x01140341L
#define IBU_P1_CETUS_CH2_065_STRIDE 1
#define IBU_P1_CETUS_CH2_065_DEPTH  1

#define IBU_P1_CETUS_CH2_066_ADDR   0x01140342L
#define IBU_P1_CETUS_CH2_066_STRIDE 1
#define IBU_P1_CETUS_CH2_066_DEPTH  1

#define IBU_P1_CETUS_CH2_067_ADDR   0x01140343L
#define IBU_P1_CETUS_CH2_067_STRIDE 1
#define IBU_P1_CETUS_CH2_067_DEPTH  1

#define IBU_P1_CETUS_CH2_068_ADDR   0x01140344L
#define IBU_P1_CETUS_CH2_068_STRIDE 1
#define IBU_P1_CETUS_CH2_068_DEPTH  1

#define IBU_P1_CETUS_CH2_069_ADDR   0x01140345L
#define IBU_P1_CETUS_CH2_069_STRIDE 1
#define IBU_P1_CETUS_CH2_069_DEPTH  1

#define IBU_P1_CETUS_CH2_070_ADDR   0x01140346L
#define IBU_P1_CETUS_CH2_070_STRIDE 1
#define IBU_P1_CETUS_CH2_070_DEPTH  1

#define IBU_P1_CETUS_CH2_071_ADDR   0x01140347L
#define IBU_P1_CETUS_CH2_071_STRIDE 1
#define IBU_P1_CETUS_CH2_071_DEPTH  1

#define IBU_P1_CETUS_CH2_072_ADDR   0x01140348L
#define IBU_P1_CETUS_CH2_072_STRIDE 1
#define IBU_P1_CETUS_CH2_072_DEPTH  1

#define IBU_P1_CETUS_CH2_073_ADDR   0x01140349L
#define IBU_P1_CETUS_CH2_073_STRIDE 1
#define IBU_P1_CETUS_CH2_073_DEPTH  1

#define IBU_P1_CETUS_CH2_074_ADDR   0x0114034aL
#define IBU_P1_CETUS_CH2_074_STRIDE 1
#define IBU_P1_CETUS_CH2_074_DEPTH  1

#define IBU_P1_CETUS_CH2_075_ADDR   0x0114034bL
#define IBU_P1_CETUS_CH2_075_STRIDE 1
#define IBU_P1_CETUS_CH2_075_DEPTH  1

#define IBU_P1_CETUS_CH2_076_ADDR   0x0114034cL
#define IBU_P1_CETUS_CH2_076_STRIDE 1
#define IBU_P1_CETUS_CH2_076_DEPTH  1

#define IBU_P1_CETUS_CH2_077_ADDR   0x0114034dL
#define IBU_P1_CETUS_CH2_077_STRIDE 1
#define IBU_P1_CETUS_CH2_077_DEPTH  1

#define IBU_P1_CETUS_CH2_078_ADDR   0x0114034eL
#define IBU_P1_CETUS_CH2_078_STRIDE 1
#define IBU_P1_CETUS_CH2_078_DEPTH  1

#define IBU_P1_CETUS_CH2_079_ADDR   0x0114034fL
#define IBU_P1_CETUS_CH2_079_STRIDE 1
#define IBU_P1_CETUS_CH2_079_DEPTH  1

#define IBU_P1_CETUS_CH2_080_ADDR   0x01140350L
#define IBU_P1_CETUS_CH2_080_STRIDE 1
#define IBU_P1_CETUS_CH2_080_DEPTH  1

#define IBU_P1_CETUS_CH2_081_ADDR   0x01140351L
#define IBU_P1_CETUS_CH2_081_STRIDE 1
#define IBU_P1_CETUS_CH2_081_DEPTH  1

#define IBU_P1_CETUS_CH2_082_ADDR   0x01140352L
#define IBU_P1_CETUS_CH2_082_STRIDE 1
#define IBU_P1_CETUS_CH2_082_DEPTH  1

#define IBU_P1_CETUS_CH2_083_ADDR   0x01140353L
#define IBU_P1_CETUS_CH2_083_STRIDE 1
#define IBU_P1_CETUS_CH2_083_DEPTH  1

#define IBU_P1_CETUS_CH2_084_ADDR   0x01140354L
#define IBU_P1_CETUS_CH2_084_STRIDE 1
#define IBU_P1_CETUS_CH2_084_DEPTH  1

#define IBU_P1_CETUS_CH2_085_ADDR   0x01140355L
#define IBU_P1_CETUS_CH2_085_STRIDE 1
#define IBU_P1_CETUS_CH2_085_DEPTH  1

#define IBU_P1_CETUS_CH2_086_ADDR   0x01140356L
#define IBU_P1_CETUS_CH2_086_STRIDE 1
#define IBU_P1_CETUS_CH2_086_DEPTH  1

#define IBU_P1_CETUS_CH2_087_ADDR   0x01140357L
#define IBU_P1_CETUS_CH2_087_STRIDE 1
#define IBU_P1_CETUS_CH2_087_DEPTH  1

#define IBU_P1_CETUS_CH2_088_ADDR   0x01140358L
#define IBU_P1_CETUS_CH2_088_STRIDE 1
#define IBU_P1_CETUS_CH2_088_DEPTH  1

#define IBU_P1_CETUS_CH2_089_ADDR   0x01140359L
#define IBU_P1_CETUS_CH2_089_STRIDE 1
#define IBU_P1_CETUS_CH2_089_DEPTH  1

#define IBU_P1_CETUS_CH2_090_ADDR   0x0114035aL
#define IBU_P1_CETUS_CH2_090_STRIDE 1
#define IBU_P1_CETUS_CH2_090_DEPTH  1

#define IBU_P1_CETUS_CH2_091_ADDR   0x0114035bL
#define IBU_P1_CETUS_CH2_091_STRIDE 1
#define IBU_P1_CETUS_CH2_091_DEPTH  1

#define IBU_P1_CETUS_CH2_092_ADDR   0x0114035cL
#define IBU_P1_CETUS_CH2_092_STRIDE 1
#define IBU_P1_CETUS_CH2_092_DEPTH  1

#define IBU_P1_CETUS_CH2_093_ADDR   0x0114035dL
#define IBU_P1_CETUS_CH2_093_STRIDE 1
#define IBU_P1_CETUS_CH2_093_DEPTH  1

#define IBU_P1_CETUS_CH2_094_ADDR   0x0114035eL
#define IBU_P1_CETUS_CH2_094_STRIDE 1
#define IBU_P1_CETUS_CH2_094_DEPTH  1

#define IBU_P1_CETUS_CH2_095_ADDR   0x0114035fL
#define IBU_P1_CETUS_CH2_095_STRIDE 1
#define IBU_P1_CETUS_CH2_095_DEPTH  1

#define IBU_P1_CETUS_CH2_096_ADDR   0x01140360L
#define IBU_P1_CETUS_CH2_096_STRIDE 1
#define IBU_P1_CETUS_CH2_096_DEPTH  1

#define IBU_P1_CETUS_CH2_097_ADDR   0x01140361L
#define IBU_P1_CETUS_CH2_097_STRIDE 1
#define IBU_P1_CETUS_CH2_097_DEPTH  1

#define IBU_P1_CETUS_CH2_098_ADDR   0x01140362L
#define IBU_P1_CETUS_CH2_098_STRIDE 1
#define IBU_P1_CETUS_CH2_098_DEPTH  1

#define IBU_P1_CETUS_CH2_099_ADDR   0x01140363L
#define IBU_P1_CETUS_CH2_099_STRIDE 1
#define IBU_P1_CETUS_CH2_099_DEPTH  1

#define IBU_P1_CETUS_CH2_100_ADDR   0x01140364L
#define IBU_P1_CETUS_CH2_100_STRIDE 1
#define IBU_P1_CETUS_CH2_100_DEPTH  1

#define IBU_P1_CETUS_CH2_101_ADDR   0x01140365L
#define IBU_P1_CETUS_CH2_101_STRIDE 1
#define IBU_P1_CETUS_CH2_101_DEPTH  1

#define IBU_P1_CETUS_CH2_102_ADDR   0x01140366L
#define IBU_P1_CETUS_CH2_102_STRIDE 1
#define IBU_P1_CETUS_CH2_102_DEPTH  1

#define IBU_P1_CETUS_CH2_103_ADDR   0x01140367L
#define IBU_P1_CETUS_CH2_103_STRIDE 1
#define IBU_P1_CETUS_CH2_103_DEPTH  1

#define IBU_P1_CETUS_CH2_104_ADDR   0x01140368L
#define IBU_P1_CETUS_CH2_104_STRIDE 1
#define IBU_P1_CETUS_CH2_104_DEPTH  1

#define IBU_P1_CETUS_CH2_105_ADDR   0x01140369L
#define IBU_P1_CETUS_CH2_105_STRIDE 1
#define IBU_P1_CETUS_CH2_105_DEPTH  1

#define IBU_P1_CETUS_CH2_106_ADDR   0x0114036aL
#define IBU_P1_CETUS_CH2_106_STRIDE 1
#define IBU_P1_CETUS_CH2_106_DEPTH  1

#define IBU_P1_CETUS_CH2_107_ADDR   0x0114036bL
#define IBU_P1_CETUS_CH2_107_STRIDE 1
#define IBU_P1_CETUS_CH2_107_DEPTH  1

#define IBU_P1_CETUS_CH2_108_ADDR   0x0114036cL
#define IBU_P1_CETUS_CH2_108_STRIDE 1
#define IBU_P1_CETUS_CH2_108_DEPTH  1

#define IBU_P1_CETUS_CH2_109_ADDR   0x0114036dL
#define IBU_P1_CETUS_CH2_109_STRIDE 1
#define IBU_P1_CETUS_CH2_109_DEPTH  1

#define IBU_P1_CETUS_CH2_110_ADDR   0x0114036eL
#define IBU_P1_CETUS_CH2_110_STRIDE 1
#define IBU_P1_CETUS_CH2_110_DEPTH  1

#define IBU_P1_CETUS_CH2_111_ADDR   0x0114036fL
#define IBU_P1_CETUS_CH2_111_STRIDE 1
#define IBU_P1_CETUS_CH2_111_DEPTH  1

#define IBU_P1_CETUS_CH2_112_ADDR   0x01140370L
#define IBU_P1_CETUS_CH2_112_STRIDE 1
#define IBU_P1_CETUS_CH2_112_DEPTH  1

#define IBU_P1_CETUS_CH2_113_ADDR   0x01140371L
#define IBU_P1_CETUS_CH2_113_STRIDE 1
#define IBU_P1_CETUS_CH2_113_DEPTH  1

#define IBU_P1_CETUS_CH2_114_ADDR   0x01140372L
#define IBU_P1_CETUS_CH2_114_STRIDE 1
#define IBU_P1_CETUS_CH2_114_DEPTH  1

#define IBU_P1_CETUS_CH2_115_ADDR   0x01140373L
#define IBU_P1_CETUS_CH2_115_STRIDE 1
#define IBU_P1_CETUS_CH2_115_DEPTH  1

#define IBU_P1_CETUS_CH2_116_ADDR   0x01140374L
#define IBU_P1_CETUS_CH2_116_STRIDE 1
#define IBU_P1_CETUS_CH2_116_DEPTH  1

#define IBU_P1_CETUS_CH2_117_ADDR   0x01140375L
#define IBU_P1_CETUS_CH2_117_STRIDE 1
#define IBU_P1_CETUS_CH2_117_DEPTH  1

#define IBU_P1_CETUS_CH2_118_ADDR   0x01140376L
#define IBU_P1_CETUS_CH2_118_STRIDE 1
#define IBU_P1_CETUS_CH2_118_DEPTH  1

#define IBU_P1_CETUS_CH2_119_ADDR   0x01140377L
#define IBU_P1_CETUS_CH2_119_STRIDE 1
#define IBU_P1_CETUS_CH2_119_DEPTH  1

#define IBU_P1_CETUS_CH2_120_ADDR   0x01140378L
#define IBU_P1_CETUS_CH2_120_STRIDE 1
#define IBU_P1_CETUS_CH2_120_DEPTH  1

#define IBU_P1_CETUS_CH2_121_ADDR   0x01140379L
#define IBU_P1_CETUS_CH2_121_STRIDE 1
#define IBU_P1_CETUS_CH2_121_DEPTH  1

#define IBU_P1_CETUS_CH2_122_ADDR   0x0114037aL
#define IBU_P1_CETUS_CH2_122_STRIDE 1
#define IBU_P1_CETUS_CH2_122_DEPTH  1

#define IBU_P1_CETUS_CH2_123_ADDR   0x0114037bL
#define IBU_P1_CETUS_CH2_123_STRIDE 1
#define IBU_P1_CETUS_CH2_123_DEPTH  1

#define IBU_P1_CETUS_CH2_124_ADDR   0x0114037cL
#define IBU_P1_CETUS_CH2_124_STRIDE 1
#define IBU_P1_CETUS_CH2_124_DEPTH  1

#define IBU_P1_CETUS_CH2_125_ADDR   0x0114037dL
#define IBU_P1_CETUS_CH2_125_STRIDE 1
#define IBU_P1_CETUS_CH2_125_DEPTH  1

#define IBU_P1_CETUS_CH2_126_ADDR   0x0114037eL
#define IBU_P1_CETUS_CH2_126_STRIDE 1
#define IBU_P1_CETUS_CH2_126_DEPTH  1

#define IBU_P1_CETUS_CH2_127_ADDR   0x0114037fL
#define IBU_P1_CETUS_CH2_127_STRIDE 1
#define IBU_P1_CETUS_CH2_127_DEPTH  1

#define IBU_P1_CETUS_CH2_128_ADDR   0x01140380L
#define IBU_P1_CETUS_CH2_128_STRIDE 1
#define IBU_P1_CETUS_CH2_128_DEPTH  1

#define IBU_P1_CETUS_CH2_129_ADDR   0x01140381L
#define IBU_P1_CETUS_CH2_129_STRIDE 1
#define IBU_P1_CETUS_CH2_129_DEPTH  1

#define IBU_P1_CETUS_CH2_130_ADDR   0x01140382L
#define IBU_P1_CETUS_CH2_130_STRIDE 1
#define IBU_P1_CETUS_CH2_130_DEPTH  1

#define IBU_P1_CETUS_CH2_131_ADDR   0x01140383L
#define IBU_P1_CETUS_CH2_131_STRIDE 1
#define IBU_P1_CETUS_CH2_131_DEPTH  1

#define IBU_P1_CETUS_CH2_132_ADDR   0x01140384L
#define IBU_P1_CETUS_CH2_132_STRIDE 1
#define IBU_P1_CETUS_CH2_132_DEPTH  1

#define IBU_P1_CETUS_CH2_133_ADDR   0x01140385L
#define IBU_P1_CETUS_CH2_133_STRIDE 1
#define IBU_P1_CETUS_CH2_133_DEPTH  1

#define IBU_P1_CETUS_CH2_134_ADDR   0x01140386L
#define IBU_P1_CETUS_CH2_134_STRIDE 1
#define IBU_P1_CETUS_CH2_134_DEPTH  1

#define IBU_P1_CETUS_CH2_135_ADDR   0x01140387L
#define IBU_P1_CETUS_CH2_135_STRIDE 1
#define IBU_P1_CETUS_CH2_135_DEPTH  1

#define IBU_P1_CETUS_CH2_136_ADDR   0x01140388L
#define IBU_P1_CETUS_CH2_136_STRIDE 1
#define IBU_P1_CETUS_CH2_136_DEPTH  1

#define IBU_P1_CETUS_CH2_137_ADDR   0x01140389L
#define IBU_P1_CETUS_CH2_137_STRIDE 1
#define IBU_P1_CETUS_CH2_137_DEPTH  1

#define IBU_P1_CETUS_CH2_138_ADDR   0x0114038aL
#define IBU_P1_CETUS_CH2_138_STRIDE 1
#define IBU_P1_CETUS_CH2_138_DEPTH  1

#define IBU_P1_CETUS_CH2_139_ADDR   0x0114038bL
#define IBU_P1_CETUS_CH2_139_STRIDE 1
#define IBU_P1_CETUS_CH2_139_DEPTH  1

	/* CETUS register */
#define IBU_P1_CETUS_CH3_000_ADDR   0x01140400L
#define IBU_P1_CETUS_CH3_000_STRIDE 1
#define IBU_P1_CETUS_CH3_000_DEPTH  1

	/* CETUS register */
#define IBU_P1_CETUS_CH3_001_ADDR   0x01140401L
#define IBU_P1_CETUS_CH3_001_STRIDE 1
#define IBU_P1_CETUS_CH3_001_DEPTH  1

	/* CETUS register */
#define IBU_P1_CETUS_CH3_002_ADDR   0x01140402L
#define IBU_P1_CETUS_CH3_002_STRIDE 1
#define IBU_P1_CETUS_CH3_002_DEPTH  1

#define IBU_P1_CETUS_CH3_003_ADDR   0x01140403L
#define IBU_P1_CETUS_CH3_003_STRIDE 1
#define IBU_P1_CETUS_CH3_003_DEPTH  1

#define IBU_P1_CETUS_CH3_004_ADDR   0x01140404L
#define IBU_P1_CETUS_CH3_004_STRIDE 1
#define IBU_P1_CETUS_CH3_004_DEPTH  1

#define IBU_P1_CETUS_CH3_005_ADDR   0x01140405L
#define IBU_P1_CETUS_CH3_005_STRIDE 1
#define IBU_P1_CETUS_CH3_005_DEPTH  1

#define IBU_P1_CETUS_CH3_006_ADDR   0x01140406L
#define IBU_P1_CETUS_CH3_006_STRIDE 1
#define IBU_P1_CETUS_CH3_006_DEPTH  1

#define IBU_P1_CETUS_CH3_007_ADDR   0x01140407L
#define IBU_P1_CETUS_CH3_007_STRIDE 1
#define IBU_P1_CETUS_CH3_007_DEPTH  1

#define IBU_P1_CETUS_CH3_008_ADDR   0x01140408L
#define IBU_P1_CETUS_CH3_008_STRIDE 1
#define IBU_P1_CETUS_CH3_008_DEPTH  1

#define IBU_P1_CETUS_CH3_009_ADDR   0x01140409L
#define IBU_P1_CETUS_CH3_009_STRIDE 1
#define IBU_P1_CETUS_CH3_009_DEPTH  1

#define IBU_P1_CETUS_CH3_010_ADDR   0x0114040aL
#define IBU_P1_CETUS_CH3_010_STRIDE 1
#define IBU_P1_CETUS_CH3_010_DEPTH  1

#define IBU_P1_CETUS_CH3_011_ADDR   0x0114040bL
#define IBU_P1_CETUS_CH3_011_STRIDE 1
#define IBU_P1_CETUS_CH3_011_DEPTH  1

#define IBU_P1_CETUS_CH3_012_ADDR   0x0114040cL
#define IBU_P1_CETUS_CH3_012_STRIDE 1
#define IBU_P1_CETUS_CH3_012_DEPTH  1

#define IBU_P1_CETUS_CH3_013_ADDR   0x0114040dL
#define IBU_P1_CETUS_CH3_013_STRIDE 1
#define IBU_P1_CETUS_CH3_013_DEPTH  1

#define IBU_P1_CETUS_CH3_014_ADDR   0x0114040eL
#define IBU_P1_CETUS_CH3_014_STRIDE 1
#define IBU_P1_CETUS_CH3_014_DEPTH  1

#define IBU_P1_CETUS_CH3_015_ADDR   0x0114040fL
#define IBU_P1_CETUS_CH3_015_STRIDE 1
#define IBU_P1_CETUS_CH3_015_DEPTH  1

#define IBU_P1_CETUS_CH3_016_ADDR   0x01140410L
#define IBU_P1_CETUS_CH3_016_STRIDE 1
#define IBU_P1_CETUS_CH3_016_DEPTH  1

#define IBU_P1_CETUS_CH3_017_ADDR   0x01140411L
#define IBU_P1_CETUS_CH3_017_STRIDE 1
#define IBU_P1_CETUS_CH3_017_DEPTH  1

#define IBU_P1_CETUS_CH3_018_ADDR   0x01140412L
#define IBU_P1_CETUS_CH3_018_STRIDE 1
#define IBU_P1_CETUS_CH3_018_DEPTH  1

#define IBU_P1_CETUS_CH3_019_ADDR   0x01140413L
#define IBU_P1_CETUS_CH3_019_STRIDE 1
#define IBU_P1_CETUS_CH3_019_DEPTH  1

#define IBU_P1_CETUS_CH3_020_ADDR   0x01140414L
#define IBU_P1_CETUS_CH3_020_STRIDE 1
#define IBU_P1_CETUS_CH3_020_DEPTH  1

#define IBU_P1_CETUS_CH3_021_ADDR   0x01140415L
#define IBU_P1_CETUS_CH3_021_STRIDE 1
#define IBU_P1_CETUS_CH3_021_DEPTH  1

#define IBU_P1_CETUS_CH3_022_ADDR   0x01140416L
#define IBU_P1_CETUS_CH3_022_STRIDE 1
#define IBU_P1_CETUS_CH3_022_DEPTH  1

#define IBU_P1_CETUS_CH3_023_ADDR   0x01140417L
#define IBU_P1_CETUS_CH3_023_STRIDE 1
#define IBU_P1_CETUS_CH3_023_DEPTH  1

#define IBU_P1_CETUS_CH3_024_ADDR   0x01140418L
#define IBU_P1_CETUS_CH3_024_STRIDE 1
#define IBU_P1_CETUS_CH3_024_DEPTH  1

#define IBU_P1_CETUS_CH3_025_ADDR   0x01140419L
#define IBU_P1_CETUS_CH3_025_STRIDE 1
#define IBU_P1_CETUS_CH3_025_DEPTH  1

#define IBU_P1_CETUS_CH3_026_ADDR   0x0114041aL
#define IBU_P1_CETUS_CH3_026_STRIDE 1
#define IBU_P1_CETUS_CH3_026_DEPTH  1

#define IBU_P1_CETUS_CH3_027_ADDR   0x0114041bL
#define IBU_P1_CETUS_CH3_027_STRIDE 1
#define IBU_P1_CETUS_CH3_027_DEPTH  1

#define IBU_P1_CETUS_CH3_028_ADDR   0x0114041cL
#define IBU_P1_CETUS_CH3_028_STRIDE 1
#define IBU_P1_CETUS_CH3_028_DEPTH  1

#define IBU_P1_CETUS_CH3_029_ADDR   0x0114041dL
#define IBU_P1_CETUS_CH3_029_STRIDE 1
#define IBU_P1_CETUS_CH3_029_DEPTH  1

#define IBU_P1_CETUS_CH3_030_ADDR   0x0114041eL
#define IBU_P1_CETUS_CH3_030_STRIDE 1
#define IBU_P1_CETUS_CH3_030_DEPTH  1

#define IBU_P1_CETUS_CH3_031_ADDR   0x0114041fL
#define IBU_P1_CETUS_CH3_031_STRIDE 1
#define IBU_P1_CETUS_CH3_031_DEPTH  1

#define IBU_P1_CETUS_CH3_032_ADDR   0x01140420L
#define IBU_P1_CETUS_CH3_032_STRIDE 1
#define IBU_P1_CETUS_CH3_032_DEPTH  1

#define IBU_P1_CETUS_CH3_033_ADDR   0x01140421L
#define IBU_P1_CETUS_CH3_033_STRIDE 1
#define IBU_P1_CETUS_CH3_033_DEPTH  1

#define IBU_P1_CETUS_CH3_034_ADDR   0x01140422L
#define IBU_P1_CETUS_CH3_034_STRIDE 1
#define IBU_P1_CETUS_CH3_034_DEPTH  1

#define IBU_P1_CETUS_CH3_035_ADDR   0x01140423L
#define IBU_P1_CETUS_CH3_035_STRIDE 1
#define IBU_P1_CETUS_CH3_035_DEPTH  1

#define IBU_P1_CETUS_CH3_036_ADDR   0x01140424L
#define IBU_P1_CETUS_CH3_036_STRIDE 1
#define IBU_P1_CETUS_CH3_036_DEPTH  1

#define IBU_P1_CETUS_CH3_037_ADDR   0x01140425L
#define IBU_P1_CETUS_CH3_037_STRIDE 1
#define IBU_P1_CETUS_CH3_037_DEPTH  1

#define IBU_P1_CETUS_CH3_038_ADDR   0x01140426L
#define IBU_P1_CETUS_CH3_038_STRIDE 1
#define IBU_P1_CETUS_CH3_038_DEPTH  1

#define IBU_P1_CETUS_CH3_039_ADDR   0x01140427L
#define IBU_P1_CETUS_CH3_039_STRIDE 1
#define IBU_P1_CETUS_CH3_039_DEPTH  1

#define IBU_P1_CETUS_CH3_040_ADDR   0x01140428L
#define IBU_P1_CETUS_CH3_040_STRIDE 1
#define IBU_P1_CETUS_CH3_040_DEPTH  1

#define IBU_P1_CETUS_CH3_041_ADDR   0x01140429L
#define IBU_P1_CETUS_CH3_041_STRIDE 1
#define IBU_P1_CETUS_CH3_041_DEPTH  1

#define IBU_P1_CETUS_CH3_042_ADDR   0x0114042aL
#define IBU_P1_CETUS_CH3_042_STRIDE 1
#define IBU_P1_CETUS_CH3_042_DEPTH  1

#define IBU_P1_CETUS_CH3_043_ADDR   0x0114042bL
#define IBU_P1_CETUS_CH3_043_STRIDE 1
#define IBU_P1_CETUS_CH3_043_DEPTH  1

#define IBU_P1_CETUS_CH3_044_ADDR   0x0114042cL
#define IBU_P1_CETUS_CH3_044_STRIDE 1
#define IBU_P1_CETUS_CH3_044_DEPTH  1

#define IBU_P1_CETUS_CH3_045_ADDR   0x0114042dL
#define IBU_P1_CETUS_CH3_045_STRIDE 1
#define IBU_P1_CETUS_CH3_045_DEPTH  1

#define IBU_P1_CETUS_CH3_046_ADDR   0x0114042eL
#define IBU_P1_CETUS_CH3_046_STRIDE 1
#define IBU_P1_CETUS_CH3_046_DEPTH  1

#define IBU_P1_CETUS_CH3_047_ADDR   0x0114042fL
#define IBU_P1_CETUS_CH3_047_STRIDE 1
#define IBU_P1_CETUS_CH3_047_DEPTH  1

#define IBU_P1_CETUS_CH3_048_ADDR   0x01140430L
#define IBU_P1_CETUS_CH3_048_STRIDE 1
#define IBU_P1_CETUS_CH3_048_DEPTH  1

#define IBU_P1_CETUS_CH3_049_ADDR   0x01140431L
#define IBU_P1_CETUS_CH3_049_STRIDE 1
#define IBU_P1_CETUS_CH3_049_DEPTH  1

#define IBU_P1_CETUS_CH3_050_ADDR   0x01140432L
#define IBU_P1_CETUS_CH3_050_STRIDE 1
#define IBU_P1_CETUS_CH3_050_DEPTH  1

#define IBU_P1_CETUS_CH3_051_ADDR   0x01140433L
#define IBU_P1_CETUS_CH3_051_STRIDE 1
#define IBU_P1_CETUS_CH3_051_DEPTH  1

#define IBU_P1_CETUS_CH3_052_ADDR   0x01140434L
#define IBU_P1_CETUS_CH3_052_STRIDE 1
#define IBU_P1_CETUS_CH3_052_DEPTH  1

#define IBU_P1_CETUS_CH3_053_ADDR   0x01140435L
#define IBU_P1_CETUS_CH3_053_STRIDE 1
#define IBU_P1_CETUS_CH3_053_DEPTH  1

#define IBU_P1_CETUS_CH3_054_ADDR   0x01140436L
#define IBU_P1_CETUS_CH3_054_STRIDE 1
#define IBU_P1_CETUS_CH3_054_DEPTH  1

#define IBU_P1_CETUS_CH3_055_ADDR   0x01140437L
#define IBU_P1_CETUS_CH3_055_STRIDE 1
#define IBU_P1_CETUS_CH3_055_DEPTH  1

#define IBU_P1_CETUS_CH3_056_ADDR   0x01140438L
#define IBU_P1_CETUS_CH3_056_STRIDE 1
#define IBU_P1_CETUS_CH3_056_DEPTH  1

#define IBU_P1_CETUS_CH3_057_ADDR   0x01140439L
#define IBU_P1_CETUS_CH3_057_STRIDE 1
#define IBU_P1_CETUS_CH3_057_DEPTH  1

#define IBU_P1_CETUS_CH3_058_ADDR   0x0114043aL
#define IBU_P1_CETUS_CH3_058_STRIDE 1
#define IBU_P1_CETUS_CH3_058_DEPTH  1

#define IBU_P1_CETUS_CH3_059_ADDR   0x0114043bL
#define IBU_P1_CETUS_CH3_059_STRIDE 1
#define IBU_P1_CETUS_CH3_059_DEPTH  1

#define IBU_P1_CETUS_CH3_060_ADDR   0x0114043cL
#define IBU_P1_CETUS_CH3_060_STRIDE 1
#define IBU_P1_CETUS_CH3_060_DEPTH  1

#define IBU_P1_CETUS_CH3_061_ADDR   0x0114043dL
#define IBU_P1_CETUS_CH3_061_STRIDE 1
#define IBU_P1_CETUS_CH3_061_DEPTH  1

#define IBU_P1_CETUS_CH3_062_ADDR   0x0114043eL
#define IBU_P1_CETUS_CH3_062_STRIDE 1
#define IBU_P1_CETUS_CH3_062_DEPTH  1

#define IBU_P1_CETUS_CH3_063_ADDR   0x0114043fL
#define IBU_P1_CETUS_CH3_063_STRIDE 1
#define IBU_P1_CETUS_CH3_063_DEPTH  1

#define IBU_P1_CETUS_CH3_064_ADDR   0x01140440L
#define IBU_P1_CETUS_CH3_064_STRIDE 1
#define IBU_P1_CETUS_CH3_064_DEPTH  1

#define IBU_P1_CETUS_CH3_065_ADDR   0x01140441L
#define IBU_P1_CETUS_CH3_065_STRIDE 1
#define IBU_P1_CETUS_CH3_065_DEPTH  1

#define IBU_P1_CETUS_CH3_066_ADDR   0x01140442L
#define IBU_P1_CETUS_CH3_066_STRIDE 1
#define IBU_P1_CETUS_CH3_066_DEPTH  1

#define IBU_P1_CETUS_CH3_067_ADDR   0x01140443L
#define IBU_P1_CETUS_CH3_067_STRIDE 1
#define IBU_P1_CETUS_CH3_067_DEPTH  1

#define IBU_P1_CETUS_CH3_068_ADDR   0x01140444L
#define IBU_P1_CETUS_CH3_068_STRIDE 1
#define IBU_P1_CETUS_CH3_068_DEPTH  1

#define IBU_P1_CETUS_CH3_069_ADDR   0x01140445L
#define IBU_P1_CETUS_CH3_069_STRIDE 1
#define IBU_P1_CETUS_CH3_069_DEPTH  1

#define IBU_P1_CETUS_CH3_070_ADDR   0x01140446L
#define IBU_P1_CETUS_CH3_070_STRIDE 1
#define IBU_P1_CETUS_CH3_070_DEPTH  1

#define IBU_P1_CETUS_CH3_071_ADDR   0x01140447L
#define IBU_P1_CETUS_CH3_071_STRIDE 1
#define IBU_P1_CETUS_CH3_071_DEPTH  1

#define IBU_P1_CETUS_CH3_072_ADDR   0x01140448L
#define IBU_P1_CETUS_CH3_072_STRIDE 1
#define IBU_P1_CETUS_CH3_072_DEPTH  1

#define IBU_P1_CETUS_CH3_073_ADDR   0x01140449L
#define IBU_P1_CETUS_CH3_073_STRIDE 1
#define IBU_P1_CETUS_CH3_073_DEPTH  1

#define IBU_P1_CETUS_CH3_074_ADDR   0x0114044aL
#define IBU_P1_CETUS_CH3_074_STRIDE 1
#define IBU_P1_CETUS_CH3_074_DEPTH  1

#define IBU_P1_CETUS_CH3_075_ADDR   0x0114044bL
#define IBU_P1_CETUS_CH3_075_STRIDE 1
#define IBU_P1_CETUS_CH3_075_DEPTH  1

#define IBU_P1_CETUS_CH3_076_ADDR   0x0114044cL
#define IBU_P1_CETUS_CH3_076_STRIDE 1
#define IBU_P1_CETUS_CH3_076_DEPTH  1

#define IBU_P1_CETUS_CH3_077_ADDR   0x0114044dL
#define IBU_P1_CETUS_CH3_077_STRIDE 1
#define IBU_P1_CETUS_CH3_077_DEPTH  1

#define IBU_P1_CETUS_CH3_078_ADDR   0x0114044eL
#define IBU_P1_CETUS_CH3_078_STRIDE 1
#define IBU_P1_CETUS_CH3_078_DEPTH  1

#define IBU_P1_CETUS_CH3_079_ADDR   0x0114044fL
#define IBU_P1_CETUS_CH3_079_STRIDE 1
#define IBU_P1_CETUS_CH3_079_DEPTH  1

#define IBU_P1_CETUS_CH3_080_ADDR   0x01140450L
#define IBU_P1_CETUS_CH3_080_STRIDE 1
#define IBU_P1_CETUS_CH3_080_DEPTH  1

#define IBU_P1_CETUS_CH3_081_ADDR   0x01140451L
#define IBU_P1_CETUS_CH3_081_STRIDE 1
#define IBU_P1_CETUS_CH3_081_DEPTH  1

#define IBU_P1_CETUS_CH3_082_ADDR   0x01140452L
#define IBU_P1_CETUS_CH3_082_STRIDE 1
#define IBU_P1_CETUS_CH3_082_DEPTH  1

#define IBU_P1_CETUS_CH3_083_ADDR   0x01140453L
#define IBU_P1_CETUS_CH3_083_STRIDE 1
#define IBU_P1_CETUS_CH3_083_DEPTH  1

#define IBU_P1_CETUS_CH3_084_ADDR   0x01140454L
#define IBU_P1_CETUS_CH3_084_STRIDE 1
#define IBU_P1_CETUS_CH3_084_DEPTH  1

#define IBU_P1_CETUS_CH3_085_ADDR   0x01140455L
#define IBU_P1_CETUS_CH3_085_STRIDE 1
#define IBU_P1_CETUS_CH3_085_DEPTH  1

#define IBU_P1_CETUS_CH3_086_ADDR   0x01140456L
#define IBU_P1_CETUS_CH3_086_STRIDE 1
#define IBU_P1_CETUS_CH3_086_DEPTH  1

#define IBU_P1_CETUS_CH3_087_ADDR   0x01140457L
#define IBU_P1_CETUS_CH3_087_STRIDE 1
#define IBU_P1_CETUS_CH3_087_DEPTH  1

#define IBU_P1_CETUS_CH3_088_ADDR   0x01140458L
#define IBU_P1_CETUS_CH3_088_STRIDE 1
#define IBU_P1_CETUS_CH3_088_DEPTH  1

#define IBU_P1_CETUS_CH3_089_ADDR   0x01140459L
#define IBU_P1_CETUS_CH3_089_STRIDE 1
#define IBU_P1_CETUS_CH3_089_DEPTH  1

#define IBU_P1_CETUS_CH3_090_ADDR   0x0114045aL
#define IBU_P1_CETUS_CH3_090_STRIDE 1
#define IBU_P1_CETUS_CH3_090_DEPTH  1

#define IBU_P1_CETUS_CH3_091_ADDR   0x0114045bL
#define IBU_P1_CETUS_CH3_091_STRIDE 1
#define IBU_P1_CETUS_CH3_091_DEPTH  1

#define IBU_P1_CETUS_CH3_092_ADDR   0x0114045cL
#define IBU_P1_CETUS_CH3_092_STRIDE 1
#define IBU_P1_CETUS_CH3_092_DEPTH  1

#define IBU_P1_CETUS_CH3_093_ADDR   0x0114045dL
#define IBU_P1_CETUS_CH3_093_STRIDE 1
#define IBU_P1_CETUS_CH3_093_DEPTH  1

#define IBU_P1_CETUS_CH3_094_ADDR   0x0114045eL
#define IBU_P1_CETUS_CH3_094_STRIDE 1
#define IBU_P1_CETUS_CH3_094_DEPTH  1

#define IBU_P1_CETUS_CH3_095_ADDR   0x0114045fL
#define IBU_P1_CETUS_CH3_095_STRIDE 1
#define IBU_P1_CETUS_CH3_095_DEPTH  1

#define IBU_P1_CETUS_CH3_096_ADDR   0x01140460L
#define IBU_P1_CETUS_CH3_096_STRIDE 1
#define IBU_P1_CETUS_CH3_096_DEPTH  1

#define IBU_P1_CETUS_CH3_097_ADDR   0x01140461L
#define IBU_P1_CETUS_CH3_097_STRIDE 1
#define IBU_P1_CETUS_CH3_097_DEPTH  1

#define IBU_P1_CETUS_CH3_098_ADDR   0x01140462L
#define IBU_P1_CETUS_CH3_098_STRIDE 1
#define IBU_P1_CETUS_CH3_098_DEPTH  1

#define IBU_P1_CETUS_CH3_099_ADDR   0x01140463L
#define IBU_P1_CETUS_CH3_099_STRIDE 1
#define IBU_P1_CETUS_CH3_099_DEPTH  1

#define IBU_P1_CETUS_CH3_100_ADDR   0x01140464L
#define IBU_P1_CETUS_CH3_100_STRIDE 1
#define IBU_P1_CETUS_CH3_100_DEPTH  1

#define IBU_P1_CETUS_CH3_101_ADDR   0x01140465L
#define IBU_P1_CETUS_CH3_101_STRIDE 1
#define IBU_P1_CETUS_CH3_101_DEPTH  1

#define IBU_P1_CETUS_CH3_102_ADDR   0x01140466L
#define IBU_P1_CETUS_CH3_102_STRIDE 1
#define IBU_P1_CETUS_CH3_102_DEPTH  1

#define IBU_P1_CETUS_CH3_103_ADDR   0x01140467L
#define IBU_P1_CETUS_CH3_103_STRIDE 1
#define IBU_P1_CETUS_CH3_103_DEPTH  1

#define IBU_P1_CETUS_CH3_104_ADDR   0x01140468L
#define IBU_P1_CETUS_CH3_104_STRIDE 1
#define IBU_P1_CETUS_CH3_104_DEPTH  1

#define IBU_P1_CETUS_CH3_105_ADDR   0x01140469L
#define IBU_P1_CETUS_CH3_105_STRIDE 1
#define IBU_P1_CETUS_CH3_105_DEPTH  1

#define IBU_P1_CETUS_CH3_106_ADDR   0x0114046aL
#define IBU_P1_CETUS_CH3_106_STRIDE 1
#define IBU_P1_CETUS_CH3_106_DEPTH  1

#define IBU_P1_CETUS_CH3_107_ADDR   0x0114046bL
#define IBU_P1_CETUS_CH3_107_STRIDE 1
#define IBU_P1_CETUS_CH3_107_DEPTH  1

#define IBU_P1_CETUS_CH3_108_ADDR   0x0114046cL
#define IBU_P1_CETUS_CH3_108_STRIDE 1
#define IBU_P1_CETUS_CH3_108_DEPTH  1

#define IBU_P1_CETUS_CH3_109_ADDR   0x0114046dL
#define IBU_P1_CETUS_CH3_109_STRIDE 1
#define IBU_P1_CETUS_CH3_109_DEPTH  1

#define IBU_P1_CETUS_CH3_110_ADDR   0x0114046eL
#define IBU_P1_CETUS_CH3_110_STRIDE 1
#define IBU_P1_CETUS_CH3_110_DEPTH  1

#define IBU_P1_CETUS_CH3_111_ADDR   0x0114046fL
#define IBU_P1_CETUS_CH3_111_STRIDE 1
#define IBU_P1_CETUS_CH3_111_DEPTH  1

#define IBU_P1_CETUS_CH3_112_ADDR   0x01140470L
#define IBU_P1_CETUS_CH3_112_STRIDE 1
#define IBU_P1_CETUS_CH3_112_DEPTH  1

#define IBU_P1_CETUS_CH3_113_ADDR   0x01140471L
#define IBU_P1_CETUS_CH3_113_STRIDE 1
#define IBU_P1_CETUS_CH3_113_DEPTH  1

#define IBU_P1_CETUS_CH3_114_ADDR   0x01140472L
#define IBU_P1_CETUS_CH3_114_STRIDE 1
#define IBU_P1_CETUS_CH3_114_DEPTH  1

#define IBU_P1_CETUS_CH3_115_ADDR   0x01140473L
#define IBU_P1_CETUS_CH3_115_STRIDE 1
#define IBU_P1_CETUS_CH3_115_DEPTH  1

#define IBU_P1_CETUS_CH3_116_ADDR   0x01140474L
#define IBU_P1_CETUS_CH3_116_STRIDE 1
#define IBU_P1_CETUS_CH3_116_DEPTH  1

#define IBU_P1_CETUS_CH3_117_ADDR   0x01140475L
#define IBU_P1_CETUS_CH3_117_STRIDE 1
#define IBU_P1_CETUS_CH3_117_DEPTH  1

#define IBU_P1_CETUS_CH3_118_ADDR   0x01140476L
#define IBU_P1_CETUS_CH3_118_STRIDE 1
#define IBU_P1_CETUS_CH3_118_DEPTH  1

#define IBU_P1_CETUS_CH3_119_ADDR   0x01140477L
#define IBU_P1_CETUS_CH3_119_STRIDE 1
#define IBU_P1_CETUS_CH3_119_DEPTH  1

#define IBU_P1_CETUS_CH3_120_ADDR   0x01140478L
#define IBU_P1_CETUS_CH3_120_STRIDE 1
#define IBU_P1_CETUS_CH3_120_DEPTH  1

#define IBU_P1_CETUS_CH3_121_ADDR   0x01140479L
#define IBU_P1_CETUS_CH3_121_STRIDE 1
#define IBU_P1_CETUS_CH3_121_DEPTH  1

#define IBU_P1_CETUS_CH3_122_ADDR   0x0114047aL
#define IBU_P1_CETUS_CH3_122_STRIDE 1
#define IBU_P1_CETUS_CH3_122_DEPTH  1

#define IBU_P1_CETUS_CH3_123_ADDR   0x0114047bL
#define IBU_P1_CETUS_CH3_123_STRIDE 1
#define IBU_P1_CETUS_CH3_123_DEPTH  1

#define IBU_P1_CETUS_CH3_124_ADDR   0x0114047cL
#define IBU_P1_CETUS_CH3_124_STRIDE 1
#define IBU_P1_CETUS_CH3_124_DEPTH  1

#define IBU_P1_CETUS_CH3_125_ADDR   0x0114047dL
#define IBU_P1_CETUS_CH3_125_STRIDE 1
#define IBU_P1_CETUS_CH3_125_DEPTH  1

#define IBU_P1_CETUS_CH3_126_ADDR   0x0114047eL
#define IBU_P1_CETUS_CH3_126_STRIDE 1
#define IBU_P1_CETUS_CH3_126_DEPTH  1

#define IBU_P1_CETUS_CH3_127_ADDR   0x0114047fL
#define IBU_P1_CETUS_CH3_127_STRIDE 1
#define IBU_P1_CETUS_CH3_127_DEPTH  1

#define IBU_P1_CETUS_CH3_128_ADDR   0x01140480L
#define IBU_P1_CETUS_CH3_128_STRIDE 1
#define IBU_P1_CETUS_CH3_128_DEPTH  1

#define IBU_P1_CETUS_CH3_129_ADDR   0x01140481L
#define IBU_P1_CETUS_CH3_129_STRIDE 1
#define IBU_P1_CETUS_CH3_129_DEPTH  1

#define IBU_P1_CETUS_CH3_130_ADDR   0x01140482L
#define IBU_P1_CETUS_CH3_130_STRIDE 1
#define IBU_P1_CETUS_CH3_130_DEPTH  1

#define IBU_P1_CETUS_CH3_131_ADDR   0x01140483L
#define IBU_P1_CETUS_CH3_131_STRIDE 1
#define IBU_P1_CETUS_CH3_131_DEPTH  1

#define IBU_P1_CETUS_CH3_132_ADDR   0x01140484L
#define IBU_P1_CETUS_CH3_132_STRIDE 1
#define IBU_P1_CETUS_CH3_132_DEPTH  1

#define IBU_P1_CETUS_CH3_133_ADDR   0x01140485L
#define IBU_P1_CETUS_CH3_133_STRIDE 1
#define IBU_P1_CETUS_CH3_133_DEPTH  1

#define IBU_P1_CETUS_CH3_134_ADDR   0x01140486L
#define IBU_P1_CETUS_CH3_134_STRIDE 1
#define IBU_P1_CETUS_CH3_134_DEPTH  1

#define IBU_P1_CETUS_CH3_135_ADDR   0x01140487L
#define IBU_P1_CETUS_CH3_135_STRIDE 1
#define IBU_P1_CETUS_CH3_135_DEPTH  1

#define IBU_P1_CETUS_CH3_136_ADDR   0x01140488L
#define IBU_P1_CETUS_CH3_136_STRIDE 1
#define IBU_P1_CETUS_CH3_136_DEPTH  1

#define IBU_P1_CETUS_CH3_137_ADDR   0x01140489L
#define IBU_P1_CETUS_CH3_137_STRIDE 1
#define IBU_P1_CETUS_CH3_137_DEPTH  1

#define IBU_P1_CETUS_CH3_138_ADDR   0x0114048aL
#define IBU_P1_CETUS_CH3_138_STRIDE 1
#define IBU_P1_CETUS_CH3_138_DEPTH  1

#define IBU_P1_CETUS_CH3_139_ADDR   0x0114048bL
#define IBU_P1_CETUS_CH3_139_STRIDE 1
#define IBU_P1_CETUS_CH3_139_DEPTH  1

#define IBU_P1_CETUS_PLLB_CONTROL0_ADDR   0x01140600L
#define IBU_P1_CETUS_PLLB_CONTROL0_STRIDE 1
#define IBU_P1_CETUS_PLLB_CONTROL0_DEPTH  1

#define IBU_P1_CETUS_PLLB_CONTROL1_ADDR   0x01140601L
#define IBU_P1_CETUS_PLLB_CONTROL1_STRIDE 1
#define IBU_P1_CETUS_PLLB_CONTROL1_DEPTH  1

#define IBU_P1_CETUS_PLLB_CONTROL2_ADDR   0x01140602L
#define IBU_P1_CETUS_PLLB_CONTROL2_STRIDE 1
#define IBU_P1_CETUS_PLLB_CONTROL2_DEPTH  1

#define IBU_P1_CETUS_PLLB_EXTFB_CNTR_ADDR   0x01140603L
#define IBU_P1_CETUS_PLLB_EXTFB_CNTR_STRIDE 1
#define IBU_P1_CETUS_PLLB_EXTFB_CNTR_DEPTH  1

#define IBU_P1_CETUS_PLLB_FBCNT_ATO_ADDR   0x01140604L
#define IBU_P1_CETUS_PLLB_FBCNT_ATO_STRIDE 1
#define IBU_P1_CETUS_PLLB_FBCNT_ATO_DEPTH  1

#define IBU_P1_CETUS_PLLB_SPARE_USRCNTR_ADDR   0x01140605L
#define IBU_P1_CETUS_PLLB_SPARE_USRCNTR_STRIDE 1
#define IBU_P1_CETUS_PLLB_SPARE_USRCNTR_DEPTH  1

#define IBU_P1_CETUS_PLLB_DIV_EN_ADDR   0x01140606L
#define IBU_P1_CETUS_PLLB_DIV_EN_STRIDE 1
#define IBU_P1_CETUS_PLLB_DIV_EN_DEPTH  1

#define IBU_P1_CETUS_PLLB_VCO_WAIT_CNT_ADDR   0x01140607L
#define IBU_P1_CETUS_PLLB_VCO_WAIT_CNT_STRIDE 1
#define IBU_P1_CETUS_PLLB_VCO_WAIT_CNT_DEPTH  1

#define IBU_P1_CETUS_PLLB_STATUS0_ADDR   0x01140608L
#define IBU_P1_CETUS_PLLB_STATUS0_STRIDE 1
#define IBU_P1_CETUS_PLLB_STATUS0_DEPTH  1

#define IBU_P1_CETUS_PLLB_STATUS1_ADDR   0x01140609L
#define IBU_P1_CETUS_PLLB_STATUS1_STRIDE 1
#define IBU_P1_CETUS_PLLB_STATUS1_DEPTH  1

#define IBU_P1_CETUS_PLLB_010_ADDR   0x0114060aL
#define IBU_P1_CETUS_PLLB_010_STRIDE 1
#define IBU_P1_CETUS_PLLB_010_DEPTH  1

#define IBU_P1_CETUS_PLLB_011_ADDR   0x0114060bL
#define IBU_P1_CETUS_PLLB_011_STRIDE 1
#define IBU_P1_CETUS_PLLB_011_DEPTH  1

#define IBU_P1_CETUS_PLLB_012_ADDR   0x0114060cL
#define IBU_P1_CETUS_PLLB_012_STRIDE 1
#define IBU_P1_CETUS_PLLB_012_DEPTH  1

#define IBU_P1_CETUS_PLLB_013_ADDR   0x0114060dL
#define IBU_P1_CETUS_PLLB_013_STRIDE 1
#define IBU_P1_CETUS_PLLB_013_DEPTH  1

#define IBU_P1_CETUS_PLLB_014_ADDR   0x0114060eL
#define IBU_P1_CETUS_PLLB_014_STRIDE 1
#define IBU_P1_CETUS_PLLB_014_DEPTH  1

#define IBU_P1_CETUS_PLLB_015_ADDR   0x0114060fL
#define IBU_P1_CETUS_PLLB_015_STRIDE 1
#define IBU_P1_CETUS_PLLB_015_DEPTH  1

#define IBU_P1_CETUS_PLLB_016_ADDR   0x01140610L
#define IBU_P1_CETUS_PLLB_016_STRIDE 1
#define IBU_P1_CETUS_PLLB_016_DEPTH  1

#define IBU_P1_CETUS_PLLB_017_ADDR   0x01140611L
#define IBU_P1_CETUS_PLLB_017_STRIDE 1
#define IBU_P1_CETUS_PLLB_017_DEPTH  1

#define IBU_P1_CETUS_PLLB_018_ADDR   0x01140612L
#define IBU_P1_CETUS_PLLB_018_STRIDE 1
#define IBU_P1_CETUS_PLLB_018_DEPTH  1

#define IBU_P1_CETUS_PLLB_019_ADDR   0x01140613L
#define IBU_P1_CETUS_PLLB_019_STRIDE 1
#define IBU_P1_CETUS_PLLB_019_DEPTH  1

#define IBU_P1_CETUS_PLLB_020_ADDR   0x01140614L
#define IBU_P1_CETUS_PLLB_020_STRIDE 1
#define IBU_P1_CETUS_PLLB_020_DEPTH  1

#define IBU_P1_CETUS_PLLB_021_ADDR   0x01140615L
#define IBU_P1_CETUS_PLLB_021_STRIDE 1
#define IBU_P1_CETUS_PLLB_021_DEPTH  1

#define IBU_P1_CETUS_PLLB_022_ADDR   0x01140616L
#define IBU_P1_CETUS_PLLB_022_STRIDE 1
#define IBU_P1_CETUS_PLLB_022_DEPTH  1

#define IBU_P1_CETUS_PLLB_023_ADDR   0x01140617L
#define IBU_P1_CETUS_PLLB_023_STRIDE 1
#define IBU_P1_CETUS_PLLB_023_DEPTH  1

#define IBU_P1_CETUS_PLLB_024_ADDR   0x01140618L
#define IBU_P1_CETUS_PLLB_024_STRIDE 1
#define IBU_P1_CETUS_PLLB_024_DEPTH  1

	/* CETUS register */
#define IBU_P1_CETUS_ALL_000_ADDR   0x01140f00L
#define IBU_P1_CETUS_ALL_000_STRIDE 1
#define IBU_P1_CETUS_ALL_000_DEPTH  1

	/* CETUS register */
#define IBU_P1_CETUS_ALL_001_ADDR   0x01140f01L
#define IBU_P1_CETUS_ALL_001_STRIDE 1
#define IBU_P1_CETUS_ALL_001_DEPTH  1

	/* CETUS register */
#define IBU_P1_CETUS_ALL_002_ADDR   0x01140f02L
#define IBU_P1_CETUS_ALL_002_STRIDE 1
#define IBU_P1_CETUS_ALL_002_DEPTH  1

#define IBU_P1_CETUS_ALL_003_ADDR   0x01140f03L
#define IBU_P1_CETUS_ALL_003_STRIDE 1
#define IBU_P1_CETUS_ALL_003_DEPTH  1

#define IBU_P1_CETUS_ALL_004_ADDR   0x01140f04L
#define IBU_P1_CETUS_ALL_004_STRIDE 1
#define IBU_P1_CETUS_ALL_004_DEPTH  1

#define IBU_P1_CETUS_ALL_005_ADDR   0x01140f05L
#define IBU_P1_CETUS_ALL_005_STRIDE 1
#define IBU_P1_CETUS_ALL_005_DEPTH  1

#define IBU_P1_CETUS_ALL_006_ADDR   0x01140f06L
#define IBU_P1_CETUS_ALL_006_STRIDE 1
#define IBU_P1_CETUS_ALL_006_DEPTH  1

#define IBU_P1_CETUS_ALL_007_ADDR   0x01140f07L
#define IBU_P1_CETUS_ALL_007_STRIDE 1
#define IBU_P1_CETUS_ALL_007_DEPTH  1

#define IBU_P1_CETUS_ALL_008_ADDR   0x01140f08L
#define IBU_P1_CETUS_ALL_008_STRIDE 1
#define IBU_P1_CETUS_ALL_008_DEPTH  1

#define IBU_P1_CETUS_ALL_009_ADDR   0x01140f09L
#define IBU_P1_CETUS_ALL_009_STRIDE 1
#define IBU_P1_CETUS_ALL_009_DEPTH  1

#define IBU_P1_CETUS_ALL_010_ADDR   0x01140f0aL
#define IBU_P1_CETUS_ALL_010_STRIDE 1
#define IBU_P1_CETUS_ALL_010_DEPTH  1

#define IBU_P1_CETUS_ALL_011_ADDR   0x01140f0bL
#define IBU_P1_CETUS_ALL_011_STRIDE 1
#define IBU_P1_CETUS_ALL_011_DEPTH  1

#define IBU_P1_CETUS_ALL_012_ADDR   0x01140f0cL
#define IBU_P1_CETUS_ALL_012_STRIDE 1
#define IBU_P1_CETUS_ALL_012_DEPTH  1

#define IBU_P1_CETUS_ALL_013_ADDR   0x01140f0dL
#define IBU_P1_CETUS_ALL_013_STRIDE 1
#define IBU_P1_CETUS_ALL_013_DEPTH  1

#define IBU_P1_CETUS_ALL_014_ADDR   0x01140f0eL
#define IBU_P1_CETUS_ALL_014_STRIDE 1
#define IBU_P1_CETUS_ALL_014_DEPTH  1

#define IBU_P1_CETUS_ALL_015_ADDR   0x01140f0fL
#define IBU_P1_CETUS_ALL_015_STRIDE 1
#define IBU_P1_CETUS_ALL_015_DEPTH  1

#define IBU_P1_CETUS_ALL_016_ADDR   0x01140f10L
#define IBU_P1_CETUS_ALL_016_STRIDE 1
#define IBU_P1_CETUS_ALL_016_DEPTH  1

#define IBU_P1_CETUS_ALL_017_ADDR   0x01140f11L
#define IBU_P1_CETUS_ALL_017_STRIDE 1
#define IBU_P1_CETUS_ALL_017_DEPTH  1

#define IBU_P1_CETUS_ALL_018_ADDR   0x01140f12L
#define IBU_P1_CETUS_ALL_018_STRIDE 1
#define IBU_P1_CETUS_ALL_018_DEPTH  1

#define IBU_P1_CETUS_ALL_019_ADDR   0x01140f13L
#define IBU_P1_CETUS_ALL_019_STRIDE 1
#define IBU_P1_CETUS_ALL_019_DEPTH  1

#define IBU_P1_CETUS_ALL_020_ADDR   0x01140f14L
#define IBU_P1_CETUS_ALL_020_STRIDE 1
#define IBU_P1_CETUS_ALL_020_DEPTH  1

#define IBU_P1_CETUS_ALL_021_ADDR   0x01140f15L
#define IBU_P1_CETUS_ALL_021_STRIDE 1
#define IBU_P1_CETUS_ALL_021_DEPTH  1

#define IBU_P1_CETUS_ALL_022_ADDR   0x01140f16L
#define IBU_P1_CETUS_ALL_022_STRIDE 1
#define IBU_P1_CETUS_ALL_022_DEPTH  1

#define IBU_P1_CETUS_ALL_023_ADDR   0x01140f17L
#define IBU_P1_CETUS_ALL_023_STRIDE 1
#define IBU_P1_CETUS_ALL_023_DEPTH  1

#define IBU_P1_CETUS_ALL_024_ADDR   0x01140f18L
#define IBU_P1_CETUS_ALL_024_STRIDE 1
#define IBU_P1_CETUS_ALL_024_DEPTH  1

#define IBU_P1_CETUS_ALL_025_ADDR   0x01140f19L
#define IBU_P1_CETUS_ALL_025_STRIDE 1
#define IBU_P1_CETUS_ALL_025_DEPTH  1

#define IBU_P1_CETUS_ALL_026_ADDR   0x01140f1aL
#define IBU_P1_CETUS_ALL_026_STRIDE 1
#define IBU_P1_CETUS_ALL_026_DEPTH  1

#define IBU_P1_CETUS_ALL_027_ADDR   0x01140f1bL
#define IBU_P1_CETUS_ALL_027_STRIDE 1
#define IBU_P1_CETUS_ALL_027_DEPTH  1

#define IBU_P1_CETUS_ALL_028_ADDR   0x01140f1cL
#define IBU_P1_CETUS_ALL_028_STRIDE 1
#define IBU_P1_CETUS_ALL_028_DEPTH  1

#define IBU_P1_CETUS_ALL_029_ADDR   0x01140f1dL
#define IBU_P1_CETUS_ALL_029_STRIDE 1
#define IBU_P1_CETUS_ALL_029_DEPTH  1

#define IBU_P1_CETUS_ALL_030_ADDR   0x01140f1eL
#define IBU_P1_CETUS_ALL_030_STRIDE 1
#define IBU_P1_CETUS_ALL_030_DEPTH  1

#define IBU_P1_CETUS_ALL_031_ADDR   0x01140f1fL
#define IBU_P1_CETUS_ALL_031_STRIDE 1
#define IBU_P1_CETUS_ALL_031_DEPTH  1

#define IBU_P1_CETUS_ALL_032_ADDR   0x01140f20L
#define IBU_P1_CETUS_ALL_032_STRIDE 1
#define IBU_P1_CETUS_ALL_032_DEPTH  1

#define IBU_P1_CETUS_ALL_033_ADDR   0x01140f21L
#define IBU_P1_CETUS_ALL_033_STRIDE 1
#define IBU_P1_CETUS_ALL_033_DEPTH  1

#define IBU_P1_CETUS_ALL_034_ADDR   0x01140f22L
#define IBU_P1_CETUS_ALL_034_STRIDE 1
#define IBU_P1_CETUS_ALL_034_DEPTH  1

#define IBU_P1_CETUS_ALL_035_ADDR   0x01140f23L
#define IBU_P1_CETUS_ALL_035_STRIDE 1
#define IBU_P1_CETUS_ALL_035_DEPTH  1

#define IBU_P1_CETUS_ALL_036_ADDR   0x01140f24L
#define IBU_P1_CETUS_ALL_036_STRIDE 1
#define IBU_P1_CETUS_ALL_036_DEPTH  1

#define IBU_P1_CETUS_ALL_037_ADDR   0x01140f25L
#define IBU_P1_CETUS_ALL_037_STRIDE 1
#define IBU_P1_CETUS_ALL_037_DEPTH  1

#define IBU_P1_CETUS_ALL_038_ADDR   0x01140f26L
#define IBU_P1_CETUS_ALL_038_STRIDE 1
#define IBU_P1_CETUS_ALL_038_DEPTH  1

#define IBU_P1_CETUS_ALL_039_ADDR   0x01140f27L
#define IBU_P1_CETUS_ALL_039_STRIDE 1
#define IBU_P1_CETUS_ALL_039_DEPTH  1

#define IBU_P1_CETUS_ALL_040_ADDR   0x01140f28L
#define IBU_P1_CETUS_ALL_040_STRIDE 1
#define IBU_P1_CETUS_ALL_040_DEPTH  1

#define IBU_P1_CETUS_ALL_041_ADDR   0x01140f29L
#define IBU_P1_CETUS_ALL_041_STRIDE 1
#define IBU_P1_CETUS_ALL_041_DEPTH  1

#define IBU_P1_CETUS_ALL_042_ADDR   0x01140f2aL
#define IBU_P1_CETUS_ALL_042_STRIDE 1
#define IBU_P1_CETUS_ALL_042_DEPTH  1

#define IBU_P1_CETUS_ALL_043_ADDR   0x01140f2bL
#define IBU_P1_CETUS_ALL_043_STRIDE 1
#define IBU_P1_CETUS_ALL_043_DEPTH  1

#define IBU_P1_CETUS_ALL_044_ADDR   0x01140f2cL
#define IBU_P1_CETUS_ALL_044_STRIDE 1
#define IBU_P1_CETUS_ALL_044_DEPTH  1

#define IBU_P1_CETUS_ALL_045_ADDR   0x01140f2dL
#define IBU_P1_CETUS_ALL_045_STRIDE 1
#define IBU_P1_CETUS_ALL_045_DEPTH  1

#define IBU_P1_CETUS_ALL_046_ADDR   0x01140f2eL
#define IBU_P1_CETUS_ALL_046_STRIDE 1
#define IBU_P1_CETUS_ALL_046_DEPTH  1

#define IBU_P1_CETUS_ALL_047_ADDR   0x01140f2fL
#define IBU_P1_CETUS_ALL_047_STRIDE 1
#define IBU_P1_CETUS_ALL_047_DEPTH  1

#define IBU_P1_CETUS_ALL_048_ADDR   0x01140f30L
#define IBU_P1_CETUS_ALL_048_STRIDE 1
#define IBU_P1_CETUS_ALL_048_DEPTH  1

#define IBU_P1_CETUS_ALL_049_ADDR   0x01140f31L
#define IBU_P1_CETUS_ALL_049_STRIDE 1
#define IBU_P1_CETUS_ALL_049_DEPTH  1

#define IBU_P1_CETUS_ALL_050_ADDR   0x01140f32L
#define IBU_P1_CETUS_ALL_050_STRIDE 1
#define IBU_P1_CETUS_ALL_050_DEPTH  1

#define IBU_P1_CETUS_ALL_051_ADDR   0x01140f33L
#define IBU_P1_CETUS_ALL_051_STRIDE 1
#define IBU_P1_CETUS_ALL_051_DEPTH  1

#define IBU_P1_CETUS_ALL_052_ADDR   0x01140f34L
#define IBU_P1_CETUS_ALL_052_STRIDE 1
#define IBU_P1_CETUS_ALL_052_DEPTH  1

#define IBU_P1_CETUS_ALL_053_ADDR   0x01140f35L
#define IBU_P1_CETUS_ALL_053_STRIDE 1
#define IBU_P1_CETUS_ALL_053_DEPTH  1

#define IBU_P1_CETUS_ALL_054_ADDR   0x01140f36L
#define IBU_P1_CETUS_ALL_054_STRIDE 1
#define IBU_P1_CETUS_ALL_054_DEPTH  1

#define IBU_P1_CETUS_ALL_055_ADDR   0x01140f37L
#define IBU_P1_CETUS_ALL_055_STRIDE 1
#define IBU_P1_CETUS_ALL_055_DEPTH  1

#define IBU_P1_CETUS_ALL_056_ADDR   0x01140f38L
#define IBU_P1_CETUS_ALL_056_STRIDE 1
#define IBU_P1_CETUS_ALL_056_DEPTH  1

#define IBU_P1_CETUS_ALL_057_ADDR   0x01140f39L
#define IBU_P1_CETUS_ALL_057_STRIDE 1
#define IBU_P1_CETUS_ALL_057_DEPTH  1

#define IBU_P1_CETUS_ALL_058_ADDR   0x01140f3aL
#define IBU_P1_CETUS_ALL_058_STRIDE 1
#define IBU_P1_CETUS_ALL_058_DEPTH  1

#define IBU_P1_CETUS_ALL_059_ADDR   0x01140f3bL
#define IBU_P1_CETUS_ALL_059_STRIDE 1
#define IBU_P1_CETUS_ALL_059_DEPTH  1

#define IBU_P1_CETUS_ALL_060_ADDR   0x01140f3cL
#define IBU_P1_CETUS_ALL_060_STRIDE 1
#define IBU_P1_CETUS_ALL_060_DEPTH  1

#define IBU_P1_CETUS_ALL_061_ADDR   0x01140f3dL
#define IBU_P1_CETUS_ALL_061_STRIDE 1
#define IBU_P1_CETUS_ALL_061_DEPTH  1

#define IBU_P1_CETUS_ALL_062_ADDR   0x01140f3eL
#define IBU_P1_CETUS_ALL_062_STRIDE 1
#define IBU_P1_CETUS_ALL_062_DEPTH  1

#define IBU_P1_CETUS_ALL_063_ADDR   0x01140f3fL
#define IBU_P1_CETUS_ALL_063_STRIDE 1
#define IBU_P1_CETUS_ALL_063_DEPTH  1

#define IBU_P1_CETUS_ALL_064_ADDR   0x01140f40L
#define IBU_P1_CETUS_ALL_064_STRIDE 1
#define IBU_P1_CETUS_ALL_064_DEPTH  1

#define IBU_P1_CETUS_ALL_065_ADDR   0x01140f41L
#define IBU_P1_CETUS_ALL_065_STRIDE 1
#define IBU_P1_CETUS_ALL_065_DEPTH  1

#define IBU_P1_CETUS_ALL_066_ADDR   0x01140f42L
#define IBU_P1_CETUS_ALL_066_STRIDE 1
#define IBU_P1_CETUS_ALL_066_DEPTH  1

#define IBU_P1_CETUS_ALL_067_ADDR   0x01140f43L
#define IBU_P1_CETUS_ALL_067_STRIDE 1
#define IBU_P1_CETUS_ALL_067_DEPTH  1

#define IBU_P1_CETUS_ALL_068_ADDR   0x01140f44L
#define IBU_P1_CETUS_ALL_068_STRIDE 1
#define IBU_P1_CETUS_ALL_068_DEPTH  1

#define IBU_P1_CETUS_ALL_069_ADDR   0x01140f45L
#define IBU_P1_CETUS_ALL_069_STRIDE 1
#define IBU_P1_CETUS_ALL_069_DEPTH  1

#define IBU_P1_CETUS_ALL_070_ADDR   0x01140f46L
#define IBU_P1_CETUS_ALL_070_STRIDE 1
#define IBU_P1_CETUS_ALL_070_DEPTH  1

#define IBU_P1_CETUS_ALL_071_ADDR   0x01140f47L
#define IBU_P1_CETUS_ALL_071_STRIDE 1
#define IBU_P1_CETUS_ALL_071_DEPTH  1

#define IBU_P1_CETUS_ALL_072_ADDR   0x01140f48L
#define IBU_P1_CETUS_ALL_072_STRIDE 1
#define IBU_P1_CETUS_ALL_072_DEPTH  1

#define IBU_P1_CETUS_ALL_073_ADDR   0x01140f49L
#define IBU_P1_CETUS_ALL_073_STRIDE 1
#define IBU_P1_CETUS_ALL_073_DEPTH  1

#define IBU_P1_CETUS_ALL_074_ADDR   0x01140f4aL
#define IBU_P1_CETUS_ALL_074_STRIDE 1
#define IBU_P1_CETUS_ALL_074_DEPTH  1

#define IBU_P1_CETUS_ALL_075_ADDR   0x01140f4bL
#define IBU_P1_CETUS_ALL_075_STRIDE 1
#define IBU_P1_CETUS_ALL_075_DEPTH  1

#define IBU_P1_CETUS_ALL_076_ADDR   0x01140f4cL
#define IBU_P1_CETUS_ALL_076_STRIDE 1
#define IBU_P1_CETUS_ALL_076_DEPTH  1

#define IBU_P1_CETUS_ALL_077_ADDR   0x01140f4dL
#define IBU_P1_CETUS_ALL_077_STRIDE 1
#define IBU_P1_CETUS_ALL_077_DEPTH  1

#define IBU_P1_CETUS_ALL_078_ADDR   0x01140f4eL
#define IBU_P1_CETUS_ALL_078_STRIDE 1
#define IBU_P1_CETUS_ALL_078_DEPTH  1

#define IBU_P1_CETUS_ALL_079_ADDR   0x01140f4fL
#define IBU_P1_CETUS_ALL_079_STRIDE 1
#define IBU_P1_CETUS_ALL_079_DEPTH  1

#define IBU_P1_CETUS_ALL_080_ADDR   0x01140f50L
#define IBU_P1_CETUS_ALL_080_STRIDE 1
#define IBU_P1_CETUS_ALL_080_DEPTH  1

#define IBU_P1_CETUS_ALL_081_ADDR   0x01140f51L
#define IBU_P1_CETUS_ALL_081_STRIDE 1
#define IBU_P1_CETUS_ALL_081_DEPTH  1

#define IBU_P1_CETUS_ALL_082_ADDR   0x01140f52L
#define IBU_P1_CETUS_ALL_082_STRIDE 1
#define IBU_P1_CETUS_ALL_082_DEPTH  1

#define IBU_P1_CETUS_ALL_083_ADDR   0x01140f53L
#define IBU_P1_CETUS_ALL_083_STRIDE 1
#define IBU_P1_CETUS_ALL_083_DEPTH  1

#define IBU_P1_CETUS_ALL_084_ADDR   0x01140f54L
#define IBU_P1_CETUS_ALL_084_STRIDE 1
#define IBU_P1_CETUS_ALL_084_DEPTH  1

#define IBU_P1_CETUS_ALL_085_ADDR   0x01140f55L
#define IBU_P1_CETUS_ALL_085_STRIDE 1
#define IBU_P1_CETUS_ALL_085_DEPTH  1

#define IBU_P1_CETUS_ALL_086_ADDR   0x01140f56L
#define IBU_P1_CETUS_ALL_086_STRIDE 1
#define IBU_P1_CETUS_ALL_086_DEPTH  1

#define IBU_P1_CETUS_ALL_087_ADDR   0x01140f57L
#define IBU_P1_CETUS_ALL_087_STRIDE 1
#define IBU_P1_CETUS_ALL_087_DEPTH  1

#define IBU_P1_CETUS_ALL_088_ADDR   0x01140f58L
#define IBU_P1_CETUS_ALL_088_STRIDE 1
#define IBU_P1_CETUS_ALL_088_DEPTH  1

#define IBU_P1_CETUS_ALL_089_ADDR   0x01140f59L
#define IBU_P1_CETUS_ALL_089_STRIDE 1
#define IBU_P1_CETUS_ALL_089_DEPTH  1

#define IBU_P1_CETUS_ALL_090_ADDR   0x01140f5aL
#define IBU_P1_CETUS_ALL_090_STRIDE 1
#define IBU_P1_CETUS_ALL_090_DEPTH  1

#define IBU_P1_CETUS_ALL_091_ADDR   0x01140f5bL
#define IBU_P1_CETUS_ALL_091_STRIDE 1
#define IBU_P1_CETUS_ALL_091_DEPTH  1

#define IBU_P1_CETUS_ALL_092_ADDR   0x01140f5cL
#define IBU_P1_CETUS_ALL_092_STRIDE 1
#define IBU_P1_CETUS_ALL_092_DEPTH  1

#define IBU_P1_CETUS_ALL_093_ADDR   0x01140f5dL
#define IBU_P1_CETUS_ALL_093_STRIDE 1
#define IBU_P1_CETUS_ALL_093_DEPTH  1

#define IBU_P1_CETUS_ALL_094_ADDR   0x01140f5eL
#define IBU_P1_CETUS_ALL_094_STRIDE 1
#define IBU_P1_CETUS_ALL_094_DEPTH  1

#define IBU_P1_CETUS_ALL_095_ADDR   0x01140f5fL
#define IBU_P1_CETUS_ALL_095_STRIDE 1
#define IBU_P1_CETUS_ALL_095_DEPTH  1

#define IBU_P1_CETUS_ALL_096_ADDR   0x01140f60L
#define IBU_P1_CETUS_ALL_096_STRIDE 1
#define IBU_P1_CETUS_ALL_096_DEPTH  1

#define IBU_P1_CETUS_ALL_097_ADDR   0x01140f61L
#define IBU_P1_CETUS_ALL_097_STRIDE 1
#define IBU_P1_CETUS_ALL_097_DEPTH  1

#define IBU_P1_CETUS_ALL_098_ADDR   0x01140f62L
#define IBU_P1_CETUS_ALL_098_STRIDE 1
#define IBU_P1_CETUS_ALL_098_DEPTH  1

#define IBU_P1_CETUS_ALL_099_ADDR   0x01140f63L
#define IBU_P1_CETUS_ALL_099_STRIDE 1
#define IBU_P1_CETUS_ALL_099_DEPTH  1

#define IBU_P1_CETUS_ALL_100_ADDR   0x01140f64L
#define IBU_P1_CETUS_ALL_100_STRIDE 1
#define IBU_P1_CETUS_ALL_100_DEPTH  1

#define IBU_P1_CETUS_ALL_101_ADDR   0x01140f65L
#define IBU_P1_CETUS_ALL_101_STRIDE 1
#define IBU_P1_CETUS_ALL_101_DEPTH  1

#define IBU_P1_CETUS_ALL_102_ADDR   0x01140f66L
#define IBU_P1_CETUS_ALL_102_STRIDE 1
#define IBU_P1_CETUS_ALL_102_DEPTH  1

#define IBU_P1_CETUS_ALL_103_ADDR   0x01140f67L
#define IBU_P1_CETUS_ALL_103_STRIDE 1
#define IBU_P1_CETUS_ALL_103_DEPTH  1

#define IBU_P1_CETUS_ALL_104_ADDR   0x01140f68L
#define IBU_P1_CETUS_ALL_104_STRIDE 1
#define IBU_P1_CETUS_ALL_104_DEPTH  1

#define IBU_P1_CETUS_ALL_105_ADDR   0x01140f69L
#define IBU_P1_CETUS_ALL_105_STRIDE 1
#define IBU_P1_CETUS_ALL_105_DEPTH  1

#define IBU_P1_CETUS_ALL_106_ADDR   0x01140f6aL
#define IBU_P1_CETUS_ALL_106_STRIDE 1
#define IBU_P1_CETUS_ALL_106_DEPTH  1

#define IBU_P1_CETUS_ALL_107_ADDR   0x01140f6bL
#define IBU_P1_CETUS_ALL_107_STRIDE 1
#define IBU_P1_CETUS_ALL_107_DEPTH  1

#define IBU_P1_CETUS_ALL_108_ADDR   0x01140f6cL
#define IBU_P1_CETUS_ALL_108_STRIDE 1
#define IBU_P1_CETUS_ALL_108_DEPTH  1

#define IBU_P1_CETUS_ALL_109_ADDR   0x01140f6dL
#define IBU_P1_CETUS_ALL_109_STRIDE 1
#define IBU_P1_CETUS_ALL_109_DEPTH  1

#define IBU_P1_CETUS_ALL_110_ADDR   0x01140f6eL
#define IBU_P1_CETUS_ALL_110_STRIDE 1
#define IBU_P1_CETUS_ALL_110_DEPTH  1

#define IBU_P1_CETUS_ALL_111_ADDR   0x01140f6fL
#define IBU_P1_CETUS_ALL_111_STRIDE 1
#define IBU_P1_CETUS_ALL_111_DEPTH  1

#define IBU_P1_CETUS_ALL_112_ADDR   0x01140f70L
#define IBU_P1_CETUS_ALL_112_STRIDE 1
#define IBU_P1_CETUS_ALL_112_DEPTH  1

#define IBU_P1_CETUS_ALL_113_ADDR   0x01140f71L
#define IBU_P1_CETUS_ALL_113_STRIDE 1
#define IBU_P1_CETUS_ALL_113_DEPTH  1

#define IBU_P1_CETUS_ALL_114_ADDR   0x01140f72L
#define IBU_P1_CETUS_ALL_114_STRIDE 1
#define IBU_P1_CETUS_ALL_114_DEPTH  1

#define IBU_P1_CETUS_ALL_115_ADDR   0x01140f73L
#define IBU_P1_CETUS_ALL_115_STRIDE 1
#define IBU_P1_CETUS_ALL_115_DEPTH  1

#define IBU_P1_CETUS_ALL_116_ADDR   0x01140f74L
#define IBU_P1_CETUS_ALL_116_STRIDE 1
#define IBU_P1_CETUS_ALL_116_DEPTH  1

#define IBU_P1_CETUS_ALL_117_ADDR   0x01140f75L
#define IBU_P1_CETUS_ALL_117_STRIDE 1
#define IBU_P1_CETUS_ALL_117_DEPTH  1

#define IBU_P1_CETUS_ALL_118_ADDR   0x01140f76L
#define IBU_P1_CETUS_ALL_118_STRIDE 1
#define IBU_P1_CETUS_ALL_118_DEPTH  1

#define IBU_P1_CETUS_ALL_119_ADDR   0x01140f77L
#define IBU_P1_CETUS_ALL_119_STRIDE 1
#define IBU_P1_CETUS_ALL_119_DEPTH  1

#define IBU_P1_CETUS_ALL_120_ADDR   0x01140f78L
#define IBU_P1_CETUS_ALL_120_STRIDE 1
#define IBU_P1_CETUS_ALL_120_DEPTH  1

#define IBU_P1_CETUS_ALL_121_ADDR   0x01140f79L
#define IBU_P1_CETUS_ALL_121_STRIDE 1
#define IBU_P1_CETUS_ALL_121_DEPTH  1

#define IBU_P1_CETUS_ALL_122_ADDR   0x01140f7aL
#define IBU_P1_CETUS_ALL_122_STRIDE 1
#define IBU_P1_CETUS_ALL_122_DEPTH  1

#define IBU_P1_CETUS_ALL_123_ADDR   0x01140f7bL
#define IBU_P1_CETUS_ALL_123_STRIDE 1
#define IBU_P1_CETUS_ALL_123_DEPTH  1

#define IBU_P1_CETUS_ALL_124_ADDR   0x01140f7cL
#define IBU_P1_CETUS_ALL_124_STRIDE 1
#define IBU_P1_CETUS_ALL_124_DEPTH  1

#define IBU_P1_CETUS_ALL_125_ADDR   0x01140f7dL
#define IBU_P1_CETUS_ALL_125_STRIDE 1
#define IBU_P1_CETUS_ALL_125_DEPTH  1

#define IBU_P1_CETUS_ALL_126_ADDR   0x01140f7eL
#define IBU_P1_CETUS_ALL_126_STRIDE 1
#define IBU_P1_CETUS_ALL_126_DEPTH  1

#define IBU_P1_CETUS_ALL_127_ADDR   0x01140f7fL
#define IBU_P1_CETUS_ALL_127_STRIDE 1
#define IBU_P1_CETUS_ALL_127_DEPTH  1

#define IBU_P1_CETUS_ALL_128_ADDR   0x01140f80L
#define IBU_P1_CETUS_ALL_128_STRIDE 1
#define IBU_P1_CETUS_ALL_128_DEPTH  1

#define IBU_P1_CETUS_ALL_129_ADDR   0x01140f81L
#define IBU_P1_CETUS_ALL_129_STRIDE 1
#define IBU_P1_CETUS_ALL_129_DEPTH  1

#define IBU_P1_CETUS_ALL_130_ADDR   0x01140f82L
#define IBU_P1_CETUS_ALL_130_STRIDE 1
#define IBU_P1_CETUS_ALL_130_DEPTH  1

#define IBU_P1_CETUS_ALL_131_ADDR   0x01140f83L
#define IBU_P1_CETUS_ALL_131_STRIDE 1
#define IBU_P1_CETUS_ALL_131_DEPTH  1

#define IBU_P1_CETUS_ALL_132_ADDR   0x01140f84L
#define IBU_P1_CETUS_ALL_132_STRIDE 1
#define IBU_P1_CETUS_ALL_132_DEPTH  1

#define IBU_P1_CETUS_ALL_133_ADDR   0x01140f85L
#define IBU_P1_CETUS_ALL_133_STRIDE 1
#define IBU_P1_CETUS_ALL_133_DEPTH  1

#define IBU_P1_CETUS_ALL_134_ADDR   0x01140f86L
#define IBU_P1_CETUS_ALL_134_STRIDE 1
#define IBU_P1_CETUS_ALL_134_DEPTH  1

#define IBU_P1_CETUS_ALL_135_ADDR   0x01140f87L
#define IBU_P1_CETUS_ALL_135_STRIDE 1
#define IBU_P1_CETUS_ALL_135_DEPTH  1

#define IBU_P1_CETUS_ALL_136_ADDR   0x01140f88L
#define IBU_P1_CETUS_ALL_136_STRIDE 1
#define IBU_P1_CETUS_ALL_136_DEPTH  1

#define IBU_P1_CETUS_ALL_137_ADDR   0x01140f89L
#define IBU_P1_CETUS_ALL_137_STRIDE 1
#define IBU_P1_CETUS_ALL_137_DEPTH  1

#define IBU_P1_CETUS_ALL_138_ADDR   0x01140f8aL
#define IBU_P1_CETUS_ALL_138_STRIDE 1
#define IBU_P1_CETUS_ALL_138_DEPTH  1

#define IBU_P1_CETUS_ALL_139_ADDR   0x01140f8bL
#define IBU_P1_CETUS_ALL_139_STRIDE 1
#define IBU_P1_CETUS_ALL_139_DEPTH  1

#define IBU_P1_PMA_RESET_CSR_ADDR   0x01160000L
#define IBU_P1_PMA_RESET_CSR_STRIDE 1
#define IBU_P1_PMA_RESET_CSR_DEPTH  1

#define IBU_P1_PMA_PLLA_CSR_ADDR   0x01160001L
#define IBU_P1_PMA_PLLA_CSR_STRIDE 1
#define IBU_P1_PMA_PLLA_CSR_DEPTH  1

#define IBU_P1_PMA_PLLB_CSR_ADDR   0x01160002L
#define IBU_P1_PMA_PLLB_CSR_STRIDE 1
#define IBU_P1_PMA_PLLB_CSR_DEPTH  1

#define IBU_P1_PMA_CMODE_CSR_ADDR   0x01160003L
#define IBU_P1_PMA_CMODE_CSR_STRIDE 1
#define IBU_P1_PMA_CMODE_CSR_DEPTH  1

#define IBU_P1_PMA_LB_CSR_ADDR   0x01160004L
#define IBU_P1_PMA_LB_CSR_STRIDE 1
#define IBU_P1_PMA_LB_CSR_DEPTH  1

#define IBU_P1_PMA_PWR_CSR_ADDR   0x01160005L
#define IBU_P1_PMA_PWR_CSR_STRIDE 1
#define IBU_P1_PMA_PWR_CSR_DEPTH  1

#define IBU_P1_PMA_STATUS0_CSR_ADDR   0x01160006L
#define IBU_P1_PMA_STATUS0_CSR_STRIDE 1
#define IBU_P1_PMA_STATUS0_CSR_DEPTH  1

#define IBU_P1_PMA_STATUS1_CSR_ADDR   0x01160007L
#define IBU_P1_PMA_STATUS1_CSR_STRIDE 1
#define IBU_P1_PMA_STATUS1_CSR_DEPTH  1

#define IBU_P1_PMA_STATUS2_CSR_ADDR   0x01160008L
#define IBU_P1_PMA_STATUS2_CSR_STRIDE 1
#define IBU_P1_PMA_STATUS2_CSR_DEPTH  1

#define IBU_P1_PMA_TXWCLK0_CNT_CSR_ADDR   0x01160009L
#define IBU_P1_PMA_TXWCLK0_CNT_CSR_STRIDE 1
#define IBU_P1_PMA_TXWCLK0_CNT_CSR_DEPTH  1

#define IBU_P1_PMA_TXWCLK0_CNT_VAL_ADDR   0x0116000aL
#define IBU_P1_PMA_TXWCLK0_CNT_VAL_STRIDE 1
#define IBU_P1_PMA_TXWCLK0_CNT_VAL_DEPTH  1

#define IBU_P1_PMA_RXWCLK0_CNT_CSR_ADDR   0x0116000bL
#define IBU_P1_PMA_RXWCLK0_CNT_CSR_STRIDE 1
#define IBU_P1_PMA_RXWCLK0_CNT_CSR_DEPTH  1

#define IBU_P1_PMA_RXWCLK0_CNT_VAL_ADDR   0x0116000cL
#define IBU_P1_PMA_RXWCLK0_CNT_VAL_STRIDE 1
#define IBU_P1_PMA_RXWCLK0_CNT_VAL_DEPTH  1

#define IBU_P1_PMA_IRQ_STATUS_CSR_ADDR   0x0116000dL
#define IBU_P1_PMA_IRQ_STATUS_CSR_STRIDE 1
#define IBU_P1_PMA_IRQ_STATUS_CSR_DEPTH  1

#define IBU_P1_PMA_IRQ_MASK_CSR_ADDR   0x0116000eL
#define IBU_P1_PMA_IRQ_MASK_CSR_STRIDE 1
#define IBU_P1_PMA_IRQ_MASK_CSR_DEPTH  1

#define IBU_P1_PMA_BAD_CSR_ADDR   0x0116fbadL
#define IBU_P1_PMA_BAD_CSR_STRIDE 1
#define IBU_P1_PMA_BAD_CSR_DEPTH  1

#define IBU_P2_CNT1US_CNT124US_ADDR   0x01180001L
#define IBU_P2_CNT1US_CNT124US_STRIDE 1
#define IBU_P2_CNT1US_CNT124US_DEPTH  1

#define IBU_P2_CNT2MS_ADDR   0x01180002L
#define IBU_P2_CNT2MS_STRIDE 1
#define IBU_P2_CNT2MS_DEPTH  1

#define IBU_P2_CNT10MS_ADDR   0x01180003L
#define IBU_P2_CNT10MS_STRIDE 1
#define IBU_P2_CNT10MS_DEPTH  1

#define IBU_P2_CNT100MS_ADDR   0x01180004L
#define IBU_P2_CNT100MS_STRIDE 1
#define IBU_P2_CNT100MS_DEPTH  1

#define IBU_P2_CNT150MS_ADDR   0x01180005L
#define IBU_P2_CNT150MS_STRIDE 1
#define IBU_P2_CNT150MS_DEPTH  1

#define IBU_P2_CNT400MS_ADDR   0x01180006L
#define IBU_P2_CNT400MS_STRIDE 1
#define IBU_P2_CNT400MS_DEPTH  1

#define IBU_P2_SKP_TO_CNT_ADDR   0x01180007L
#define IBU_P2_SKP_TO_CNT_STRIDE 1
#define IBU_P2_SKP_TO_CNT_DEPTH  1

#define IBU_P2_TGT_VAL_ADDR   0x01180008L
#define IBU_P2_TGT_VAL_STRIDE 1
#define IBU_P2_TGT_VAL_DEPTH  1

#define IBU_P2_PHY_VCONFIG_ADDR   0x01180009L
#define IBU_P2_PHY_VCONFIG_STRIDE 1
#define IBU_P2_PHY_VCONFIG_DEPTH  1

#define IBU_P2_PHY_DISP_ERROR_CNT_ADDR   0x0118000aL
#define IBU_P2_PHY_DISP_ERROR_CNT_STRIDE 1
#define IBU_P2_PHY_DISP_ERROR_CNT_DEPTH  1

#define IBU_P2_PHY_CODE_ERROR_CNT_ADDR   0x0118000bL
#define IBU_P2_PHY_CODE_ERROR_CNT_STRIDE 1
#define IBU_P2_PHY_CODE_ERROR_CNT_DEPTH  1

#define IBU_P2_PHY_EVENT_LOG_ADDR   0x0118000cL
#define IBU_P2_PHY_EVENT_LOG_STRIDE 1
#define IBU_P2_PHY_EVENT_LOG_DEPTH  1

#define IBU_P2_PORT_TRAIN_FSM_ADDR   0x0118000dL
#define IBU_P2_PORT_TRAIN_FSM_STRIDE 1
#define IBU_P2_PORT_TRAIN_FSM_DEPTH  1

#define IBU_P2_PHY_TRAIN_SMTIMER_VS1_ADDR   0x0118000eL
#define IBU_P2_PHY_TRAIN_SMTIMER_VS1_STRIDE 1
#define IBU_P2_PHY_TRAIN_SMTIMER_VS1_DEPTH  1

#define IBU_P2_MASK_ADDR   0x0118000fL
#define IBU_P2_MASK_STRIDE 1
#define IBU_P2_MASK_DEPTH  1

#define IBU_P2_STATUS_ADDR   0x01180010L
#define IBU_P2_STATUS_STRIDE 1
#define IBU_P2_STATUS_DEPTH  1

#define IBU_P2_LINK_WIDTH_ENABLED_ADDR   0x01180011L
#define IBU_P2_LINK_WIDTH_ENABLED_STRIDE 1
#define IBU_P2_LINK_WIDTH_ENABLED_DEPTH  1

#define IBU_P2_LINK_WIDTH_SUPPORTED_ADDR   0x01180012L
#define IBU_P2_LINK_WIDTH_SUPPORTED_STRIDE 1
#define IBU_P2_LINK_WIDTH_SUPPORTED_DEPTH  1

#define IBU_P2_LINK_WIDTH_ACTIVE_ADDR   0x01180013L
#define IBU_P2_LINK_WIDTH_ACTIVE_STRIDE 1
#define IBU_P2_LINK_WIDTH_ACTIVE_DEPTH  1

#define IBU_P2_LINK_SPEED_SUPPORTED_ADDR   0x01180014L
#define IBU_P2_LINK_SPEED_SUPPORTED_STRIDE 1
#define IBU_P2_LINK_SPEED_SUPPORTED_DEPTH  1

#define IBU_P2_PORT_PHYSICAL_STATE_ADDR   0x01180015L
#define IBU_P2_PORT_PHYSICAL_STATE_STRIDE 1
#define IBU_P2_PORT_PHYSICAL_STATE_DEPTH  1

#define IBU_P2_LINK_DOWN_DEFAULT_STATE_ADDR   0x01180016L
#define IBU_P2_LINK_DOWN_DEFAULT_STATE_STRIDE 1
#define IBU_P2_LINK_DOWN_DEFAULT_STATE_DEPTH  1

#define IBU_P2_LINK_SPEED_ACTIVE_ADDR   0x01180017L
#define IBU_P2_LINK_SPEED_ACTIVE_STRIDE 1
#define IBU_P2_LINK_SPEED_ACTIVE_DEPTH  1

#define IBU_P2_LINK_SPEED_ENABLED_ADDR   0x01180018L
#define IBU_P2_LINK_SPEED_ENABLED_STRIDE 1
#define IBU_P2_LINK_SPEED_ENABLED_DEPTH  1

#define IBU_P2_PCPHY_CNT_RST_ADDR   0x01180019L
#define IBU_P2_PCPHY_CNT_RST_STRIDE 1
#define IBU_P2_PCPHY_CNT_RST_DEPTH  1

#define IBU_P2_PCPHY_CNT_LOAD_ADDR   0x0118001aL
#define IBU_P2_PCPHY_CNT_LOAD_STRIDE 1
#define IBU_P2_PCPHY_CNT_LOAD_DEPTH  1

#define IBU_P2_PCSYMB_ERR_CNT_ADDR   0x0118001bL
#define IBU_P2_PCSYMB_ERR_CNT_STRIDE 1
#define IBU_P2_PCSYMB_ERR_CNT_DEPTH  1

#define IBU_P2_PCLINK_ERR_REC_CNT_ADDR   0x0118001cL
#define IBU_P2_PCLINK_ERR_REC_CNT_STRIDE 1
#define IBU_P2_PCLINK_ERR_REC_CNT_DEPTH  1

#define IBU_P2_PCLINK_DOWNED_CNT_ADDR   0x0118001dL
#define IBU_P2_PCLINK_DOWNED_CNT_STRIDE 1
#define IBU_P2_PCLINK_DOWNED_CNT_DEPTH  1

#define IBU_P2_PCSYMB_ERR_CNT_LANE0_ADDR   0x0118001eL
#define IBU_P2_PCSYMB_ERR_CNT_LANE0_STRIDE 1
#define IBU_P2_PCSYMB_ERR_CNT_LANE0_DEPTH  1

#define IBU_P2_PCSYMB_ERR_CNT_LANE1_ADDR   0x0118001fL
#define IBU_P2_PCSYMB_ERR_CNT_LANE1_STRIDE 1
#define IBU_P2_PCSYMB_ERR_CNT_LANE1_DEPTH  1

#define IBU_P2_PCSYMB_ERR_CNT_LANE2_ADDR   0x01180020L
#define IBU_P2_PCSYMB_ERR_CNT_LANE2_STRIDE 1
#define IBU_P2_PCSYMB_ERR_CNT_LANE2_DEPTH  1

#define IBU_P2_PCSYMB_ERR_CNT_LANE3_ADDR   0x01180021L
#define IBU_P2_PCSYMB_ERR_CNT_LANE3_STRIDE 1
#define IBU_P2_PCSYMB_ERR_CNT_LANE3_DEPTH  1

#define IBU_P2_TS3_REV1_TT0_COUNTER_ADDR   0x01180022L
#define IBU_P2_TS3_REV1_TT0_COUNTER_STRIDE 1
#define IBU_P2_TS3_REV1_TT0_COUNTER_DEPTH  1

#define IBU_P2_TS3_REV1_TT1_COUNTER_ADDR   0x01180023L
#define IBU_P2_TS3_REV1_TT1_COUNTER_STRIDE 1
#define IBU_P2_TS3_REV1_TT1_COUNTER_DEPTH  1

#define IBU_P2_TS3_REV1_TT2_COUNTER_ADDR   0x01180024L
#define IBU_P2_TS3_REV1_TT2_COUNTER_STRIDE 1
#define IBU_P2_TS3_REV1_TT2_COUNTER_DEPTH  1

#define IBU_P2_TS3_REV1_TT3_COUNTER_ADDR   0x01180025L
#define IBU_P2_TS3_REV1_TT3_COUNTER_STRIDE 1
#define IBU_P2_TS3_REV1_TT3_COUNTER_DEPTH  1

#define IBU_P2_PHY_ALIGN_ERROR_CNT_ADDR   0x01180026L
#define IBU_P2_PHY_ALIGN_ERROR_CNT_STRIDE 1
#define IBU_P2_PHY_ALIGN_ERROR_CNT_DEPTH  1

#define IBU_P2_PHY_CNTRL_IN_PKT_ERROR_CNT_ADDR   0x01180027L
#define IBU_P2_PHY_CNTRL_IN_PKT_ERROR_CNT_STRIDE 1
#define IBU_P2_PHY_CNTRL_IN_PKT_ERROR_CNT_DEPTH  1

#define IBU_P2_PHY_PAD_ERROR_CNT_ADDR   0x01180028L
#define IBU_P2_PHY_PAD_ERROR_CNT_STRIDE 1
#define IBU_P2_PHY_PAD_ERROR_CNT_DEPTH  1

#define IBU_P2_PHY_EDR_FDR_CONFIG0_ADDR   0x01180029L
#define IBU_P2_PHY_EDR_FDR_CONFIG0_STRIDE 1
#define IBU_P2_PHY_EDR_FDR_CONFIG0_DEPTH  1

#define IBU_P2_PHY_EDR_FDR_CONFIG1_ADDR   0x0118002aL
#define IBU_P2_PHY_EDR_FDR_CONFIG1_STRIDE 1
#define IBU_P2_PHY_EDR_FDR_CONFIG1_DEPTH  1

#define IBU_P2_PHY_LEAKY_BKT_THRSH_ADDR   0x0118002bL
#define IBU_P2_PHY_LEAKY_BKT_THRSH_STRIDE 1
#define IBU_P2_PHY_LEAKY_BKT_THRSH_DEPTH  1

#define IBU_P2_RCV_TS3_STATUS_LOW_ADDR   0x0118002dL
#define IBU_P2_RCV_TS3_STATUS_LOW_STRIDE 1
#define IBU_P2_RCV_TS3_STATUS_LOW_DEPTH  1

#define IBU_P2_RCV_TS3_STATUS_HIGH_ADDR   0x0118002eL
#define IBU_P2_RCV_TS3_STATUS_HIGH_STRIDE 1
#define IBU_P2_RCV_TS3_STATUS_HIGH_DEPTH  1

#define IBU_P2_GUID0_ADDR   0x0118002fL
#define IBU_P2_GUID0_STRIDE 1
#define IBU_P2_GUID0_DEPTH  1

#define IBU_P2_GUID1_ADDR   0x01180030L
#define IBU_P2_GUID1_STRIDE 1
#define IBU_P2_GUID1_DEPTH  1

#define IBU_P2_PNUM_ADDR   0x01180031L
#define IBU_P2_PNUM_STRIDE 1
#define IBU_P2_PNUM_DEPTH  1

#define IBU_P2_CNT4MS_ADDR   0x01180032L
#define IBU_P2_CNT4MS_STRIDE 1
#define IBU_P2_CNT4MS_DEPTH  1

#define IBU_P2_CNT36MS_ADDR   0x01180033L
#define IBU_P2_CNT36MS_STRIDE 1
#define IBU_P2_CNT36MS_DEPTH  1

#define IBU_P2_PHY_TS3_CONFIG_ADDR   0x01180034L
#define IBU_P2_PHY_TS3_CONFIG_STRIDE 1
#define IBU_P2_PHY_TS3_CONFIG_DEPTH  1

#define IBU_P2_DDS_WINDOW_START_ADDR   0x01180035L
#define IBU_P2_DDS_WINDOW_START_STRIDE 1
#define IBU_P2_DDS_WINDOW_START_DEPTH  1

#define IBU_P2_DDS_WINDOW_END_ADDR   0x01180036L
#define IBU_P2_DDS_WINDOW_END_STRIDE 1
#define IBU_P2_DDS_WINDOW_END_DEPTH  1

#define IBU_P2_DDS_DEFAULT_WINDOW_END_ADDR   0x01180037L
#define IBU_P2_DDS_DEFAULT_WINDOW_END_STRIDE 1
#define IBU_P2_DDS_DEFAULT_WINDOW_END_DEPTH  1

#define IBU_P2_RX_TS3DDS_STATUS_ADDR   0x01180038L
#define IBU_P2_RX_TS3DDS_STATUS_STRIDE 1
#define IBU_P2_RX_TS3DDS_STATUS_DEPTH  1

#define IBU_P2_TX_TS3DDS_STATUS_ADDR   0x01180039L
#define IBU_P2_TX_TS3DDS_STATUS_STRIDE 1
#define IBU_P2_TX_TS3DDS_STATUS_DEPTH  1

#define IBU_P2_CNT16MS_ADDR   0x0118003aL
#define IBU_P2_CNT16MS_STRIDE 1
#define IBU_P2_CNT16MS_DEPTH  1

#define IBU_P2_CONF_TEST4MS_SCT_ADDR   0x0118003bL
#define IBU_P2_CONF_TEST4MS_SCT_STRIDE 1
#define IBU_P2_CONF_TEST4MS_SCT_DEPTH  1

#define IBU_P2_CONF_TEST16MS_SCT_ADDR   0x0118003cL
#define IBU_P2_CONF_TEST16MS_SCT_STRIDE 1
#define IBU_P2_CONF_TEST16MS_SCT_DEPTH  1

#define IBU_P2_LOCAL_ADDTEST_LIMIT_ADDR   0x0118003dL
#define IBU_P2_LOCAL_ADDTEST_LIMIT_STRIDE 1
#define IBU_P2_LOCAL_ADDTEST_LIMIT_DEPTH  1

#define IBU_P2_REMOTE_ADDTEST_LIMIT_ADDR   0x0118003eL
#define IBU_P2_REMOTE_ADDTEST_LIMIT_STRIDE 1
#define IBU_P2_REMOTE_ADDTEST_LIMIT_DEPTH  1

#define IBU_P2_TS3_REV1_TT4_COUNTER_ADDR   0x0118003fL
#define IBU_P2_TS3_REV1_TT4_COUNTER_STRIDE 1
#define IBU_P2_TS3_REV1_TT4_COUNTER_DEPTH  1

#define IBU_P2_TS3_REV1_TT5_COUNTER_ADDR   0x01180040L
#define IBU_P2_TS3_REV1_TT5_COUNTER_STRIDE 1
#define IBU_P2_TS3_REV1_TT5_COUNTER_DEPTH  1

#define IBU_P2_TS3_REV1_TT6_COUNTER_ADDR   0x01180041L
#define IBU_P2_TS3_REV1_TT6_COUNTER_STRIDE 1
#define IBU_P2_TS3_REV1_TT6_COUNTER_DEPTH  1

#define IBU_P2_TS3_REV1_TT7_COUNTER_ADDR   0x01180042L
#define IBU_P2_TS3_REV1_TT7_COUNTER_STRIDE 1
#define IBU_P2_TS3_REV1_TT7_COUNTER_DEPTH  1

#define IBU_P2_TS3_REV1_TT8_COUNTER_ADDR   0x01180043L
#define IBU_P2_TS3_REV1_TT8_COUNTER_STRIDE 1
#define IBU_P2_TS3_REV1_TT8_COUNTER_DEPTH  1

#define IBU_P2_TS3_REV1_TT9_COUNTER_ADDR   0x01180044L
#define IBU_P2_TS3_REV1_TT9_COUNTER_STRIDE 1
#define IBU_P2_TS3_REV1_TT9_COUNTER_DEPTH  1

#define IBU_P2_TS3_REV1_TT10_COUNTER_ADDR   0x01180045L
#define IBU_P2_TS3_REV1_TT10_COUNTER_STRIDE 1
#define IBU_P2_TS3_REV1_TT10_COUNTER_DEPTH  1

#define IBU_P2_TS3_REV1_TT11_COUNTER_ADDR   0x01180046L
#define IBU_P2_TS3_REV1_TT11_COUNTER_STRIDE 1
#define IBU_P2_TS3_REV1_TT11_COUNTER_DEPTH  1

#define IBU_P2_TS3_REV1_TT12_COUNTER_ADDR   0x01180047L
#define IBU_P2_TS3_REV1_TT12_COUNTER_STRIDE 1
#define IBU_P2_TS3_REV1_TT12_COUNTER_DEPTH  1

#define IBU_P2_TS3_REV1_TT13_COUNTER_ADDR   0x01180048L
#define IBU_P2_TS3_REV1_TT13_COUNTER_STRIDE 1
#define IBU_P2_TS3_REV1_TT13_COUNTER_DEPTH  1

#define IBU_P2_TS3_REV1_TT14_COUNTER_ADDR   0x01180049L
#define IBU_P2_TS3_REV1_TT14_COUNTER_STRIDE 1
#define IBU_P2_TS3_REV1_TT14_COUNTER_DEPTH  1

#define IBU_P2_TS3_REV1_TT15_COUNTER_ADDR   0x0118004aL
#define IBU_P2_TS3_REV1_TT15_COUNTER_STRIDE 1
#define IBU_P2_TS3_REV1_TT15_COUNTER_DEPTH  1

#define IBU_P2_CONF_TEST_LANE_ERROR_LIMIT_ADDR   0x0118004bL
#define IBU_P2_CONF_TEST_LANE_ERROR_LIMIT_STRIDE 1
#define IBU_P2_CONF_TEST_LANE_ERROR_LIMIT_DEPTH  1

#define IBU_P2_CONF_TEST_IDLE_LIMIT_ADDR   0x0118004cL
#define IBU_P2_CONF_TEST_IDLE_LIMIT_STRIDE 1
#define IBU_P2_CONF_TEST_IDLE_LIMIT_DEPTH  1

#define IBU_P2_CONF_TEST2MS_SCT_ADDR   0x0118004dL
#define IBU_P2_CONF_TEST2MS_SCT_STRIDE 1
#define IBU_P2_CONF_TEST2MS_SCT_DEPTH  1

#define IBU_P2_CNT100_MS_HBR_ADDR   0x0118004eL
#define IBU_P2_CNT100_MS_HBR_STRIDE 1
#define IBU_P2_CNT100_MS_HBR_DEPTH  1

#define IBU_P2_PMAEQULANE0_STATUS_ADDR   0x0118004fL
#define IBU_P2_PMAEQULANE0_STATUS_STRIDE 1
#define IBU_P2_PMAEQULANE0_STATUS_DEPTH  1

#define IBU_P2_PMAEQULANE1_STATUS_ADDR   0x01180050L
#define IBU_P2_PMAEQULANE1_STATUS_STRIDE 1
#define IBU_P2_PMAEQULANE1_STATUS_DEPTH  1

#define IBU_P2_PMAEQULANE2_STATUS_ADDR   0x01180051L
#define IBU_P2_PMAEQULANE2_STATUS_STRIDE 1
#define IBU_P2_PMAEQULANE2_STATUS_DEPTH  1

#define IBU_P2_PMAEQULANE3_STATUS_ADDR   0x01180052L
#define IBU_P2_PMAEQULANE3_STATUS_STRIDE 1
#define IBU_P2_PMAEQULANE3_STATUS_DEPTH  1

#define IBU_P2_PMADDSLANE0_STATUS_ADDR   0x01180053L
#define IBU_P2_PMADDSLANE0_STATUS_STRIDE 1
#define IBU_P2_PMADDSLANE0_STATUS_DEPTH  1

#define IBU_P2_PMADDSLANE1_STATUS_ADDR   0x01180054L
#define IBU_P2_PMADDSLANE1_STATUS_STRIDE 1
#define IBU_P2_PMADDSLANE1_STATUS_DEPTH  1

#define IBU_P2_PMADDSLANE2_STATUS_ADDR   0x01180055L
#define IBU_P2_PMADDSLANE2_STATUS_STRIDE 1
#define IBU_P2_PMADDSLANE2_STATUS_DEPTH  1

#define IBU_P2_PMADDSLANE3_STATUS_ADDR   0x01180056L
#define IBU_P2_PMADDSLANE3_STATUS_STRIDE 1
#define IBU_P2_PMADDSLANE3_STATUS_DEPTH  1

#define IBU_P2_PHY_EDPL_ERR0_ADDR   0x01180057L
#define IBU_P2_PHY_EDPL_ERR0_STRIDE 1
#define IBU_P2_PHY_EDPL_ERR0_DEPTH  1

#define IBU_P2_PHY_EDPL_ERR1_ADDR   0x01180058L
#define IBU_P2_PHY_EDPL_ERR1_STRIDE 1
#define IBU_P2_PHY_EDPL_ERR1_DEPTH  1

#define IBU_P2_PHY_EDPL_ERR2_ADDR   0x01180059L
#define IBU_P2_PHY_EDPL_ERR2_STRIDE 1
#define IBU_P2_PHY_EDPL_ERR2_DEPTH  1

#define IBU_P2_PHY_EDPL_ERR3_ADDR   0x0118005aL
#define IBU_P2_PHY_EDPL_ERR3_STRIDE 1
#define IBU_P2_PHY_EDPL_ERR3_DEPTH  1

#define IBU_P2_PHY_BLK_TYPE_ERR_ADDR   0x0118005bL
#define IBU_P2_PHY_BLK_TYPE_ERR_STRIDE 1
#define IBU_P2_PHY_BLK_TYPE_ERR_DEPTH  1

#define IBU_P2_PHY_BLK_EOP_ERR_ADDR   0x0118005cL
#define IBU_P2_PHY_BLK_EOP_ERR_STRIDE 1
#define IBU_P2_PHY_BLK_EOP_ERR_DEPTH  1

#define IBU_P2_PHY_CIN_PKT_ERR_ADDR   0x0118005dL
#define IBU_P2_PHY_CIN_PKT_ERR_STRIDE 1
#define IBU_P2_PHY_CIN_PKT_ERR_DEPTH  1

#define IBU_P2_PHY_SYN_HDR_ERR_ADDR   0x0118005eL
#define IBU_P2_PHY_SYN_HDR_ERR_STRIDE 1
#define IBU_P2_PHY_SYN_HDR_ERR_DEPTH  1

#define IBU_P2_PHY_PRBS_ERR0_ADDR   0x0118005fL
#define IBU_P2_PHY_PRBS_ERR0_STRIDE 1
#define IBU_P2_PHY_PRBS_ERR0_DEPTH  1

#define IBU_P2_PHY_PRBS_ERR1_ADDR   0x01180060L
#define IBU_P2_PHY_PRBS_ERR1_STRIDE 1
#define IBU_P2_PHY_PRBS_ERR1_DEPTH  1

#define IBU_P2_PHY_PRBS_ERR2_ADDR   0x01180061L
#define IBU_P2_PHY_PRBS_ERR2_STRIDE 1
#define IBU_P2_PHY_PRBS_ERR2_DEPTH  1

#define IBU_P2_PHY_PRBS_ERR3_ADDR   0x01180062L
#define IBU_P2_PHY_PRBS_ERR3_STRIDE 1
#define IBU_P2_PHY_PRBS_ERR3_DEPTH  1

#define IBU_P2_PHY_DESKEW_STATUS_ADDR   0x01180063L
#define IBU_P2_PHY_DESKEW_STATUS_STRIDE 1
#define IBU_P2_PHY_DESKEW_STATUS_DEPTH  1

#define IBU_P2_PHY_FECUNC_ERR0_ADDR   0x01180064L
#define IBU_P2_PHY_FECUNC_ERR0_STRIDE 1
#define IBU_P2_PHY_FECUNC_ERR0_DEPTH  1

#define IBU_P2_PHY_FECUNC_ERR1_ADDR   0x01180065L
#define IBU_P2_PHY_FECUNC_ERR1_STRIDE 1
#define IBU_P2_PHY_FECUNC_ERR1_DEPTH  1

#define IBU_P2_PHY_FECUNC_ERR2_ADDR   0x01180066L
#define IBU_P2_PHY_FECUNC_ERR2_STRIDE 1
#define IBU_P2_PHY_FECUNC_ERR2_DEPTH  1

#define IBU_P2_PHY_FECUNC_ERR3_ADDR   0x01180067L
#define IBU_P2_PHY_FECUNC_ERR3_STRIDE 1
#define IBU_P2_PHY_FECUNC_ERR3_DEPTH  1

#define IBU_P2_PHY_FECCOR_ERR0_ADDR   0x01180068L
#define IBU_P2_PHY_FECCOR_ERR0_STRIDE 1
#define IBU_P2_PHY_FECCOR_ERR0_DEPTH  1

#define IBU_P2_PHY_FECCOR_ERR1_ADDR   0x01180069L
#define IBU_P2_PHY_FECCOR_ERR1_STRIDE 1
#define IBU_P2_PHY_FECCOR_ERR1_DEPTH  1

#define IBU_P2_PHY_FECCOR_ERR2_ADDR   0x0118006aL
#define IBU_P2_PHY_FECCOR_ERR2_STRIDE 1
#define IBU_P2_PHY_FECCOR_ERR2_DEPTH  1

#define IBU_P2_PHY_FECCOR_ERR3_ADDR   0x0118006bL
#define IBU_P2_PHY_FECCOR_ERR3_STRIDE 1
#define IBU_P2_PHY_FECCOR_ERR3_DEPTH  1

#define IBU_P2_PHY_SMSTATUS_ADDR   0x0118006cL
#define IBU_P2_PHY_SMSTATUS_STRIDE 1
#define IBU_P2_PHY_SMSTATUS_DEPTH  1

#define IBU_P2_PHY_TS3_NEGOTIATED_STATUS_ADDR   0x0118006dL
#define IBU_P2_PHY_TS3_NEGOTIATED_STATUS_STRIDE 1
#define IBU_P2_PHY_TS3_NEGOTIATED_STATUS_DEPTH  1

#define IBU_P2_PHY_TEST_ADDR   0x0118006eL
#define IBU_P2_PHY_TEST_STRIDE 1
#define IBU_P2_PHY_TEST_DEPTH  1

#define IBU_P2_EDR_FDR_RX_STATUS_REG0_ADDR   0x0118006fL
#define IBU_P2_EDR_FDR_RX_STATUS_REG0_STRIDE 1
#define IBU_P2_EDR_FDR_RX_STATUS_REG0_DEPTH  1

#define IBU_P2_EDR_FDR_RX_STATUS_REG1_ADDR   0x01180070L
#define IBU_P2_EDR_FDR_RX_STATUS_REG1_STRIDE 1
#define IBU_P2_EDR_FDR_RX_STATUS_REG1_DEPTH  1

#define IBU_P2_EDR_FDR_RX_STATUS_REG2_ADDR   0x01180071L
#define IBU_P2_EDR_FDR_RX_STATUS_REG2_STRIDE 1
#define IBU_P2_EDR_FDR_RX_STATUS_REG2_DEPTH  1

#define IBU_P2_EDR_FDR_TX_STATUS_REG0_ADDR   0x01180072L
#define IBU_P2_EDR_FDR_TX_STATUS_REG0_STRIDE 1
#define IBU_P2_EDR_FDR_TX_STATUS_REG0_DEPTH  1

#define IBU_P2_INT_PRIORITY_ADDR   0x01180073L
#define IBU_P2_INT_PRIORITY_STRIDE 1
#define IBU_P2_INT_PRIORITY_DEPTH  1

#define IBU_P2_INT_FATAL_ADDR   0x01180074L
#define IBU_P2_INT_FATAL_STRIDE 1
#define IBU_P2_INT_FATAL_DEPTH  1

#define IBU_P2_LINK_ROUND_TRIP_LATENCY_ADDR   0x01180075L
#define IBU_P2_LINK_ROUND_TRIP_LATENCY_STRIDE 1
#define IBU_P2_LINK_ROUND_TRIP_LATENCY_DEPTH  1

#define IBU_P2_PHY_FORCE_LEGACY_MODE_ADDR   0x01180076L
#define IBU_P2_PHY_FORCE_LEGACY_MODE_STRIDE 1
#define IBU_P2_PHY_FORCE_LEGACY_MODE_DEPTH  1

#define IBU_P2_SERDES_BYPASS_ADDR   0x01180077L
#define IBU_P2_SERDES_BYPASS_STRIDE 1
#define IBU_P2_SERDES_BYPASS_DEPTH  1

#define IBU_P2_LID_ADDR   0x01180100L
#define IBU_P2_LID_STRIDE 1
#define IBU_P2_LID_DEPTH  1

#define IBU_P2_LMC_ADDR   0x01180101L
#define IBU_P2_LMC_STRIDE 1
#define IBU_P2_LMC_DEPTH  1

#define IBU_P2_PORT_STATE_ADDR   0x01180102L
#define IBU_P2_PORT_STATE_STRIDE 1
#define IBU_P2_PORT_STATE_DEPTH  1

#define IBU_P2_VLCAP_ADDR   0x01180103L
#define IBU_P2_VLCAP_STRIDE 1
#define IBU_P2_VLCAP_DEPTH  1

#define IBU_P2_NEIGHBOR_MTU_ADDR   0x01180104L
#define IBU_P2_NEIGHBOR_MTU_STRIDE 1
#define IBU_P2_NEIGHBOR_MTU_DEPTH  1

#define IBU_P2_VLHIGH_LIMIT_ADDR   0x01180105L
#define IBU_P2_VLHIGH_LIMIT_STRIDE 1
#define IBU_P2_VLHIGH_LIMIT_DEPTH  1

#define IBU_P2_VLARBITRATION_HIGH_CAP_ADDR   0x01180106L
#define IBU_P2_VLARBITRATION_HIGH_CAP_STRIDE 1
#define IBU_P2_VLARBITRATION_HIGH_CAP_DEPTH  1

#define IBU_P2_VLARBITRATION_LOW_CAP_ADDR   0x01180107L
#define IBU_P2_VLARBITRATION_LOW_CAP_STRIDE 1
#define IBU_P2_VLARBITRATION_LOW_CAP_DEPTH  1

#define IBU_P2_MTUCAP_ADDR   0x01180108L
#define IBU_P2_MTUCAP_STRIDE 1
#define IBU_P2_MTUCAP_DEPTH  1

#define IBU_P2_OPERATIONAL_VLS_ADDR   0x01180109L
#define IBU_P2_OPERATIONAL_VLS_STRIDE 1
#define IBU_P2_OPERATIONAL_VLS_DEPTH  1

#define IBU_P2_PCPORT_RCV_ERROR_ADDR   0x0118010cL
#define IBU_P2_PCPORT_RCV_ERROR_STRIDE 1
#define IBU_P2_PCPORT_RCV_ERROR_DEPTH  1

#define IBU_P2_PCPORT_RCV_REMOTE_PHYSICAL_ERRORS_ADDR   0x0118010dL
#define IBU_P2_PCPORT_RCV_REMOTE_PHYSICAL_ERRORS_STRIDE 1
#define IBU_P2_PCPORT_RCV_REMOTE_PHYSICAL_ERRORS_DEPTH  1

#define IBU_P2_PCPORT_XMIT_DISCARDS_ADDR   0x0118010eL
#define IBU_P2_PCPORT_XMIT_DISCARDS_STRIDE 1
#define IBU_P2_PCPORT_XMIT_DISCARDS_DEPTH  1

#define IBU_P2_PCLOCAL_LINK_INTEGRITY_ERRORS_ADDR   0x0118010fL
#define IBU_P2_PCLOCAL_LINK_INTEGRITY_ERRORS_STRIDE 1
#define IBU_P2_PCLOCAL_LINK_INTEGRITY_ERRORS_DEPTH  1

#define IBU_P2_PCEXCESSIVE_BUFFER_OVERRUN_ERRORS_ADDR   0x01180110L
#define IBU_P2_PCEXCESSIVE_BUFFER_OVERRUN_ERRORS_STRIDE 1
#define IBU_P2_PCEXCESSIVE_BUFFER_OVERRUN_ERRORS_DEPTH  1

#define IBU_P2_PCVL15_DROPPED_ADDR   0x01180111L
#define IBU_P2_PCVL15_DROPPED_STRIDE 1
#define IBU_P2_PCVL15_DROPPED_DEPTH  1

#define IBU_P2_PCPORT_XMIT_WAIT_ADDR   0x01180112L
#define IBU_P2_PCPORT_XMIT_WAIT_STRIDE 1
#define IBU_P2_PCPORT_XMIT_WAIT_DEPTH  1

#define IBU_P2_PCPORT_XMIT_DATA_LSQW_ADDR   0x01180113L
#define IBU_P2_PCPORT_XMIT_DATA_LSQW_STRIDE 1
#define IBU_P2_PCPORT_XMIT_DATA_LSQW_DEPTH  1

#define IBU_P2_LINK_ERROR_CHECK_ENABLE_ADDR   0x01180114L
#define IBU_P2_LINK_ERROR_CHECK_ENABLE_STRIDE 1
#define IBU_P2_LINK_ERROR_CHECK_ENABLE_DEPTH  1

#define IBU_P2_PCPORT_RCV_DATA_LSQW_ADDR   0x01180115L
#define IBU_P2_PCPORT_RCV_DATA_LSQW_STRIDE 1
#define IBU_P2_PCPORT_RCV_DATA_LSQW_DEPTH  1

#define IBU_P2_PCPORT_RCV_DATA_HSQW_ADDR   0x01180116L
#define IBU_P2_PCPORT_RCV_DATA_HSQW_STRIDE 1
#define IBU_P2_PCPORT_RCV_DATA_HSQW_DEPTH  1

#define IBU_P2_PCPORT_XMIT_PKTS_LSQW_ADDR   0x01180117L
#define IBU_P2_PCPORT_XMIT_PKTS_LSQW_STRIDE 1
#define IBU_P2_PCPORT_XMIT_PKTS_LSQW_DEPTH  1

#define IBU_P2_PCPORT_XMIT_PKTS_HSQW_ADDR   0x01180118L
#define IBU_P2_PCPORT_XMIT_PKTS_HSQW_STRIDE 1
#define IBU_P2_PCPORT_XMIT_PKTS_HSQW_DEPTH  1

#define IBU_P2_PCPORT_RCV_PKTS_LSQW_ADDR   0x01180119L
#define IBU_P2_PCPORT_RCV_PKTS_LSQW_STRIDE 1
#define IBU_P2_PCPORT_RCV_PKTS_LSQW_DEPTH  1

#define IBU_P2_PCPORT_RCV_PKTS_HSQW_ADDR   0x0118011aL
#define IBU_P2_PCPORT_RCV_PKTS_HSQW_STRIDE 1
#define IBU_P2_PCPORT_RCV_PKTS_HSQW_DEPTH  1

#define IBU_P2_PCPORT_UCXMIT_PKTS_LSQW_ADDR   0x0118011bL
#define IBU_P2_PCPORT_UCXMIT_PKTS_LSQW_STRIDE 1
#define IBU_P2_PCPORT_UCXMIT_PKTS_LSQW_DEPTH  1

#define IBU_P2_PCPORT_UCXMIT_PKTS_HSQW_ADDR   0x0118011cL
#define IBU_P2_PCPORT_UCXMIT_PKTS_HSQW_STRIDE 1
#define IBU_P2_PCPORT_UCXMIT_PKTS_HSQW_DEPTH  1

#define IBU_P2_PCPORT_MCXMIT_PKTS_LSQW_ADDR   0x0118011dL
#define IBU_P2_PCPORT_MCXMIT_PKTS_LSQW_STRIDE 1
#define IBU_P2_PCPORT_MCXMIT_PKTS_LSQW_DEPTH  1

#define IBU_P2_PCPORT_MCXMIT_PKTS_HSQW_ADDR   0x0118011eL
#define IBU_P2_PCPORT_MCXMIT_PKTS_HSQW_STRIDE 1
#define IBU_P2_PCPORT_MCXMIT_PKTS_HSQW_DEPTH  1

#define IBU_P2_PCPORT_UCRCV_PKTS_LSQW_ADDR   0x0118011fL
#define IBU_P2_PCPORT_UCRCV_PKTS_LSQW_STRIDE 1
#define IBU_P2_PCPORT_UCRCV_PKTS_LSQW_DEPTH  1

#define IBU_P2_PCPORT_UCRCV_PKTS_HSQW_ADDR   0x01180120L
#define IBU_P2_PCPORT_UCRCV_PKTS_HSQW_STRIDE 1
#define IBU_P2_PCPORT_UCRCV_PKTS_HSQW_DEPTH  1

#define IBU_P2_PCPORT_MCRCV_PKTS_LSQW_ADDR   0x01180121L
#define IBU_P2_PCPORT_MCRCV_PKTS_LSQW_STRIDE 1
#define IBU_P2_PCPORT_MCRCV_PKTS_LSQW_DEPTH  1

#define IBU_P2_PCPORT_MCRCV_PKTS_HSQW_ADDR   0x01180122L
#define IBU_P2_PCPORT_MCRCV_PKTS_HSQW_STRIDE 1
#define IBU_P2_PCPORT_MCRCV_PKTS_HSQW_DEPTH  1

#define IBU_P2_PCPORT_XMIT_WAIT_VL0_ADDR   0x01180123L
#define IBU_P2_PCPORT_XMIT_WAIT_VL0_STRIDE 1
#define IBU_P2_PCPORT_XMIT_WAIT_VL0_DEPTH  1

#define IBU_P2_PCPORT_XMIT_WAIT_VL1_ADDR   0x01180124L
#define IBU_P2_PCPORT_XMIT_WAIT_VL1_STRIDE 1
#define IBU_P2_PCPORT_XMIT_WAIT_VL1_DEPTH  1

#define IBU_P2_PCPORT_XMIT_WAIT_VL2_ADDR   0x01180125L
#define IBU_P2_PCPORT_XMIT_WAIT_VL2_STRIDE 1
#define IBU_P2_PCPORT_XMIT_WAIT_VL2_DEPTH  1

#define IBU_P2_PCPORT_XMIT_WAIT_VL3_ADDR   0x01180126L
#define IBU_P2_PCPORT_XMIT_WAIT_VL3_STRIDE 1
#define IBU_P2_PCPORT_XMIT_WAIT_VL3_DEPTH  1

#define IBU_P2_PCPORT_XMIT_WAIT_VL4_ADDR   0x01180127L
#define IBU_P2_PCPORT_XMIT_WAIT_VL4_STRIDE 1
#define IBU_P2_PCPORT_XMIT_WAIT_VL4_DEPTH  1

#define IBU_P2_PCPORT_XMIT_WAIT_VL5_ADDR   0x01180128L
#define IBU_P2_PCPORT_XMIT_WAIT_VL5_STRIDE 1
#define IBU_P2_PCPORT_XMIT_WAIT_VL5_DEPTH  1

#define IBU_P2_PCPORT_XMIT_WAIT_VL6_ADDR   0x01180129L
#define IBU_P2_PCPORT_XMIT_WAIT_VL6_STRIDE 1
#define IBU_P2_PCPORT_XMIT_WAIT_VL6_DEPTH  1

#define IBU_P2_PCPORT_XMIT_WAIT_VL7_ADDR   0x0118012aL
#define IBU_P2_PCPORT_XMIT_WAIT_VL7_STRIDE 1
#define IBU_P2_PCPORT_XMIT_WAIT_VL7_DEPTH  1

#define IBU_P2_PCPORT_XMIT_WAIT_VL15_ADDR   0x0118012bL
#define IBU_P2_PCPORT_XMIT_WAIT_VL15_STRIDE 1
#define IBU_P2_PCPORT_XMIT_WAIT_VL15_DEPTH  1

#define IBU_P2_PCRX_LINK_CNT_RST_ADDR   0x0118012cL
#define IBU_P2_PCRX_LINK_CNT_RST_STRIDE 1
#define IBU_P2_PCRX_LINK_CNT_RST_DEPTH  1

#define IBU_P2_PCRX_LINK_CNT_LOAD_ADDR   0x0118012dL
#define IBU_P2_PCRX_LINK_CNT_LOAD_STRIDE 1
#define IBU_P2_PCRX_LINK_CNT_LOAD_DEPTH  1

#define IBU_P2_LOCAL_PHY_ERRORS_ADDR   0x0118012eL
#define IBU_P2_LOCAL_PHY_ERRORS_STRIDE 1
#define IBU_P2_LOCAL_PHY_ERRORS_DEPTH  1

#define IBU_P2_OVERRUN_ERRORS_ADDR   0x0118012fL
#define IBU_P2_OVERRUN_ERRORS_STRIDE 1
#define IBU_P2_OVERRUN_ERRORS_DEPTH  1

#define IBU_P2_PSLINK_DLID_ADDR   0x01180130L
#define IBU_P2_PSLINK_DLID_STRIDE 1
#define IBU_P2_PSLINK_DLID_DEPTH  1

#define IBU_P2_PSTICK_ADDR   0x01180131L
#define IBU_P2_PSTICK_STRIDE 1
#define IBU_P2_PSTICK_DEPTH  1

#define IBU_P2_PSSTATUS_ADDR   0x01180132L
#define IBU_P2_PSSTATUS_STRIDE 1
#define IBU_P2_PSSTATUS_DEPTH  1

#define IBU_P2_PSSTART_DELAY_ADDR   0x01180133L
#define IBU_P2_PSSTART_DELAY_STRIDE 1
#define IBU_P2_PSSTART_DELAY_DEPTH  1

#define IBU_P2_PSINTERVAL_ADDR   0x01180134L
#define IBU_P2_PSINTERVAL_STRIDE 1
#define IBU_P2_PSINTERVAL_DEPTH  1

#define IBU_P2_PSCNT_SEL0_ADDR   0x01180135L
#define IBU_P2_PSCNT_SEL0_STRIDE 1
#define IBU_P2_PSCNT_SEL0_DEPTH  1

#define IBU_P2_PSCNT_SEL1_ADDR   0x01180136L
#define IBU_P2_PSCNT_SEL1_STRIDE 1
#define IBU_P2_PSCNT_SEL1_DEPTH  1

#define IBU_P2_PSCNT_SEL2_ADDR   0x01180137L
#define IBU_P2_PSCNT_SEL2_STRIDE 1
#define IBU_P2_PSCNT_SEL2_DEPTH  1

#define IBU_P2_PSCNT_SEL3_ADDR   0x01180138L
#define IBU_P2_PSCNT_SEL3_STRIDE 1
#define IBU_P2_PSCNT_SEL3_DEPTH  1

#define IBU_P2_PSCNT0_ADDR   0x01180139L
#define IBU_P2_PSCNT0_STRIDE 1
#define IBU_P2_PSCNT0_DEPTH  1

#define IBU_P2_PSCNT1_ADDR   0x0118013aL
#define IBU_P2_PSCNT1_STRIDE 1
#define IBU_P2_PSCNT1_DEPTH  1

#define IBU_P2_PSCNT2_ADDR   0x0118013bL
#define IBU_P2_PSCNT2_STRIDE 1
#define IBU_P2_PSCNT2_DEPTH  1

#define IBU_P2_PSCNT3_ADDR   0x0118013cL
#define IBU_P2_PSCNT3_STRIDE 1
#define IBU_P2_PSCNT3_DEPTH  1

#define IBU_P2_PSINIT_SAMPLING_ADDR   0x0118013dL
#define IBU_P2_PSINIT_SAMPLING_STRIDE 1
#define IBU_P2_PSINIT_SAMPLING_DEPTH  1

#define IBU_P2_PSCNT_LOAD_ADDR   0x0118013eL
#define IBU_P2_PSCNT_LOAD_STRIDE 1
#define IBU_P2_PSCNT_LOAD_DEPTH  1

#define IBU_P2_PORT_STATE_CHANGE_ADDR   0x0118013fL
#define IBU_P2_PORT_STATE_CHANGE_STRIDE 1
#define IBU_P2_PORT_STATE_CHANGE_DEPTH  1

#define IBU_P2_LINK_VCONFIG0_ADDR   0x01180141L
#define IBU_P2_LINK_VCONFIG0_STRIDE 1
#define IBU_P2_LINK_VCONFIG0_DEPTH  1

#define IBU_P2_LINK_VCONFIG1_ADDR   0x01180142L
#define IBU_P2_LINK_VCONFIG1_STRIDE 1
#define IBU_P2_LINK_VCONFIG1_DEPTH  1

#define IBU_P2_LINK_VCONFIG2_ADDR   0x01180143L
#define IBU_P2_LINK_VCONFIG2_STRIDE 1
#define IBU_P2_LINK_VCONFIG2_DEPTH  1

#define IBU_P2_LINK_RX_CREDIT_VL1_0_ADDR   0x01180144L
#define IBU_P2_LINK_RX_CREDIT_VL1_0_STRIDE 1
#define IBU_P2_LINK_RX_CREDIT_VL1_0_DEPTH  1

#define IBU_P2_LINK_RX_CREDIT_VL3_2_ADDR   0x01180145L
#define IBU_P2_LINK_RX_CREDIT_VL3_2_STRIDE 1
#define IBU_P2_LINK_RX_CREDIT_VL3_2_DEPTH  1

#define IBU_P2_LINK_RX_CREDIT_VL5_4_ADDR   0x01180146L
#define IBU_P2_LINK_RX_CREDIT_VL5_4_STRIDE 1
#define IBU_P2_LINK_RX_CREDIT_VL5_4_DEPTH  1

#define IBU_P2_LINK_RX_CREDIT_VL7_6_ADDR   0x01180147L
#define IBU_P2_LINK_RX_CREDIT_VL7_6_STRIDE 1
#define IBU_P2_LINK_RX_CREDIT_VL7_6_DEPTH  1

#define IBU_P2_LINK_TX_CREDIT_VL1_0_ADDR   0x01180148L
#define IBU_P2_LINK_TX_CREDIT_VL1_0_STRIDE 1
#define IBU_P2_LINK_TX_CREDIT_VL1_0_DEPTH  1

#define IBU_P2_LINK_TX_CREDIT_VL3_2_ADDR   0x01180149L
#define IBU_P2_LINK_TX_CREDIT_VL3_2_STRIDE 1
#define IBU_P2_LINK_TX_CREDIT_VL3_2_DEPTH  1

#define IBU_P2_LINK_TX_CREDIT_VL5_4_ADDR   0x0118014aL
#define IBU_P2_LINK_TX_CREDIT_VL5_4_STRIDE 1
#define IBU_P2_LINK_TX_CREDIT_VL5_4_DEPTH  1

#define IBU_P2_LINK_TX_CREDIT_VL7_6_ADDR   0x0118014bL
#define IBU_P2_LINK_TX_CREDIT_VL7_6_STRIDE 1
#define IBU_P2_LINK_TX_CREDIT_VL7_6_DEPTH  1

#define IBU_P2_PCTX_LINK_CNT_RST_ADDR   0x0118014cL
#define IBU_P2_PCTX_LINK_CNT_RST_STRIDE 1
#define IBU_P2_PCTX_LINK_CNT_RST_DEPTH  1

#define IBU_P2_PCTX_LINK_CNT_LOAD_ADDR   0x0118014dL
#define IBU_P2_PCTX_LINK_CNT_LOAD_STRIDE 1
#define IBU_P2_PCTX_LINK_CNT_LOAD_DEPTH  1

#define IBU_P2_PSCNT_WIDTH_ADDR   0x0118014fL
#define IBU_P2_PSCNT_WIDTH_STRIDE 1
#define IBU_P2_PSCNT_WIDTH_DEPTH  1

#define IBU_P2_PSCNT_MASK_ADDR   0x01180150L
#define IBU_P2_PSCNT_MASK_STRIDE 1
#define IBU_P2_PSCNT_MASK_DEPTH  1

#define IBU_P2_PCICRC_RCV_ERRORS_ADDR   0x01180151L
#define IBU_P2_PCICRC_RCV_ERRORS_STRIDE 1
#define IBU_P2_PCICRC_RCV_ERRORS_DEPTH  1

#define IBU_P2_PCVCRC_RCV_ERRORS_ADDR   0x01180152L
#define IBU_P2_PCVCRC_RCV_ERRORS_STRIDE 1
#define IBU_P2_PCVCRC_RCV_ERRORS_DEPTH  1

#define IBU_P2_PCLEN_RCV_ERRORS_ADDR   0x01180153L
#define IBU_P2_PCLEN_RCV_ERRORS_STRIDE 1
#define IBU_P2_PCLEN_RCV_ERRORS_DEPTH  1

#define IBU_P2_PCDLID_RCV_ERRORS_ADDR   0x01180154L
#define IBU_P2_PCDLID_RCV_ERRORS_STRIDE 1
#define IBU_P2_PCDLID_RCV_ERRORS_DEPTH  1

#define IBU_P2_PCRCV_FCLEN_ERRORS_ADDR   0x01180155L
#define IBU_P2_PCRCV_FCLEN_ERRORS_STRIDE 1
#define IBU_P2_PCRCV_FCLEN_ERRORS_DEPTH  1

#define IBU_P2_PCRCV_FCVL_ERRORS_ADDR   0x01180156L
#define IBU_P2_PCRCV_FCVL_ERRORS_STRIDE 1
#define IBU_P2_PCRCV_FCVL_ERRORS_DEPTH  1

#define IBU_P2_PCRCV_FCCRC_ERRORS_ADDR   0x01180157L
#define IBU_P2_PCRCV_FCCRC_ERRORS_STRIDE 1
#define IBU_P2_PCRCV_FCCRC_ERRORS_DEPTH  1

#define IBU_P2_PORT_LOCAL_PHYSICAL_ERRORS_ADDR   0x01180158L
#define IBU_P2_PORT_LOCAL_PHYSICAL_ERRORS_STRIDE 1
#define IBU_P2_PORT_LOCAL_PHYSICAL_ERRORS_DEPTH  1

#define IBU_P2_PCMAL_FORMED_ERRORS_ADDR   0x01180159L
#define IBU_P2_PCMAL_FORMED_ERRORS_STRIDE 1
#define IBU_P2_PCMAL_FORMED_ERRORS_DEPTH  1

#define IBU_P2_PCBUF_OVER_ERRORS_ADDR   0x0118015aL
#define IBU_P2_PCBUF_OVER_ERRORS_STRIDE 1
#define IBU_P2_PCBUF_OVER_ERRORS_DEPTH  1

#define IBU_P2_PCVLMAP_ERRORS_ADDR   0x0118015bL
#define IBU_P2_PCVLMAP_ERRORS_STRIDE 1
#define IBU_P2_PCVLMAP_ERRORS_DEPTH  1

#define IBU_P2_PCVLINIT_CREDIT_VL1_VL0_ADDR   0x0118015cL
#define IBU_P2_PCVLINIT_CREDIT_VL1_VL0_STRIDE 1
#define IBU_P2_PCVLINIT_CREDIT_VL1_VL0_DEPTH  1

#define IBU_P2_PCVLINIT_CREDIT_VL3_VL2_ADDR   0x0118015dL
#define IBU_P2_PCVLINIT_CREDIT_VL3_VL2_STRIDE 1
#define IBU_P2_PCVLINIT_CREDIT_VL3_VL2_DEPTH  1

#define IBU_P2_PCVLINIT_CREDIT_VL5_VL4_ADDR   0x0118015eL
#define IBU_P2_PCVLINIT_CREDIT_VL5_VL4_STRIDE 1
#define IBU_P2_PCVLINIT_CREDIT_VL5_VL4_DEPTH  1

#define IBU_P2_PCVLINIT_CREDIT_VL7_VL6_ADDR   0x0118015fL
#define IBU_P2_PCVLINIT_CREDIT_VL7_VL6_STRIDE 1
#define IBU_P2_PCVLINIT_CREDIT_VL7_VL6_DEPTH  1

#define IBU_P2_PCRX_VL07_ECC_COR_ERR_CNT_ADDR   0x01180160L
#define IBU_P2_PCRX_VL07_ECC_COR_ERR_CNT_STRIDE 1
#define IBU_P2_PCRX_VL07_ECC_COR_ERR_CNT_DEPTH  1

#define IBU_P2_PCRX_VL07_ECC_UNC_ERR_CNT_ADDR   0x01180161L
#define IBU_P2_PCRX_VL07_ECC_UNC_ERR_CNT_STRIDE 1
#define IBU_P2_PCRX_VL07_ECC_UNC_ERR_CNT_DEPTH  1

#define IBU_P2_PCRX_VL15_ECC_COR_ERR_CNT_ADDR   0x01180162L
#define IBU_P2_PCRX_VL15_ECC_COR_ERR_CNT_STRIDE 1
#define IBU_P2_PCRX_VL15_ECC_COR_ERR_CNT_DEPTH  1

#define IBU_P2_PCRX_VL15_ECC_UNC_ERR_CNT_ADDR   0x01180163L
#define IBU_P2_PCRX_VL15_ECC_UNC_ERR_CNT_STRIDE 1
#define IBU_P2_PCRX_VL15_ECC_UNC_ERR_CNT_DEPTH  1

#define IBU_P2_PCRX_LOOP_ECC_COR_ERR_CNT_ADDR   0x01180164L
#define IBU_P2_PCRX_LOOP_ECC_COR_ERR_CNT_STRIDE 1
#define IBU_P2_PCRX_LOOP_ECC_COR_ERR_CNT_DEPTH  1

#define IBU_P2_PCRX_LOOP_ECC_UNC_ERR_CNT_ADDR   0x01180165L
#define IBU_P2_PCRX_LOOP_ECC_UNC_ERR_CNT_STRIDE 1
#define IBU_P2_PCRX_LOOP_ECC_UNC_ERR_CNT_DEPTH  1

#define IBU_P2_PCECCENA_ERR_ADDR   0x01180166L
#define IBU_P2_PCECCENA_ERR_STRIDE 1
#define IBU_P2_PCECCENA_ERR_DEPTH  1

#define IBU_P2_PCTX_ECC_COR_ERR_CNT_ADDR   0x01180167L
#define IBU_P2_PCTX_ECC_COR_ERR_CNT_STRIDE 1
#define IBU_P2_PCTX_ECC_COR_ERR_CNT_DEPTH  1

#define IBU_P2_PCTX_ECC_UNC_ERR_CNT_ADDR   0x01180168L
#define IBU_P2_PCTX_ECC_UNC_ERR_CNT_STRIDE 1
#define IBU_P2_PCTX_ECC_UNC_ERR_CNT_DEPTH  1

#define IBU_P2_TX_SRAMSTATUS_ADDR   0x01180169L
#define IBU_P2_TX_SRAMSTATUS_STRIDE 1
#define IBU_P2_TX_SRAMSTATUS_DEPTH  1

#define IBU_P2_TX_CACHE_STATUS_ADDR   0x0118016aL
#define IBU_P2_TX_CACHE_STATUS_STRIDE 1
#define IBU_P2_TX_CACHE_STATUS_DEPTH  1

#define IBU_P2_TX_DEBUG_ADDR   0x0118016bL
#define IBU_P2_TX_DEBUG_STRIDE 1
#define IBU_P2_TX_DEBUG_DEPTH  1

#define IBU_P2_RX_VL07_SRAMSTATUS_ADDR   0x0118016cL
#define IBU_P2_RX_VL07_SRAMSTATUS_STRIDE 1
#define IBU_P2_RX_VL07_SRAMSTATUS_DEPTH  1

#define IBU_P2_RX_VL15_SRAMSTATUS_ADDR   0x0118016dL
#define IBU_P2_RX_VL15_SRAMSTATUS_STRIDE 1
#define IBU_P2_RX_VL15_SRAMSTATUS_DEPTH  1

#define IBU_P2_LOOPSRAMSTATUS_ADDR   0x0118016eL
#define IBU_P2_LOOPSRAMSTATUS_STRIDE 1
#define IBU_P2_LOOPSRAMSTATUS_DEPTH  1

#define IBU_P2_RX_DEBUG_ADDR   0x0118016fL
#define IBU_P2_RX_DEBUG_STRIDE 1
#define IBU_P2_RX_DEBUG_DEPTH  1

#define IBU_P2_TX_ARB_LOOPBACK_SRAMSTATUS_ADDR   0x01180170L
#define IBU_P2_TX_ARB_LOOPBACK_SRAMSTATUS_STRIDE 1
#define IBU_P2_TX_ARB_LOOPBACK_SRAMSTATUS_DEPTH  1

#define IBU_P2_REMOTE_RX_BUFF_LIMIT_ADDR   0x01180171L
#define IBU_P2_REMOTE_RX_BUFF_LIMIT_STRIDE 1
#define IBU_P2_REMOTE_RX_BUFF_LIMIT_DEPTH  1

#define IBU_P2_FCTX_TIMER_ADDR   0x01180172L
#define IBU_P2_FCTX_TIMER_STRIDE 1
#define IBU_P2_FCTX_TIMER_DEPTH  1

#define IBU_P2_FCRX_TIMER_ADDR   0x01180173L
#define IBU_P2_FCRX_TIMER_STRIDE 1
#define IBU_P2_FCRX_TIMER_DEPTH  1

#define IBU_P2_PCPORT_XMIT_DATA_HSQW_ADDR   0x01180174L
#define IBU_P2_PCPORT_XMIT_DATA_HSQW_STRIDE 1
#define IBU_P2_PCPORT_XMIT_DATA_HSQW_DEPTH  1

#define IBU_P2_PCPORT_XMIT_VLDISCARDS_ADDR   0x01180175L
#define IBU_P2_PCPORT_XMIT_VLDISCARDS_STRIDE 1
#define IBU_P2_PCPORT_XMIT_VLDISCARDS_DEPTH  1

#define IBU_P2_PCPORT_COL_LIMIT_ADDR   0x01180176L
#define IBU_P2_PCPORT_COL_LIMIT_STRIDE 1
#define IBU_P2_PCPORT_COL_LIMIT_DEPTH  1

#define IBU_P2_VLARB_HI_PRI_TABLE_ADDR   0x01180180L
#define IBU_P2_VLARB_HI_PRI_TABLE_STRIDE 1
#define IBU_P2_VLARB_HI_PRI_TABLE_DEPTH  10

#define IBU_P2_VLARB_LO_PRI_TABLE_ADDR   0x011801c0L
#define IBU_P2_VLARB_LO_PRI_TABLE_STRIDE 1
#define IBU_P2_VLARB_LO_PRI_TABLE_DEPTH  10

#define IBU_P2_TX_TBSVL10_ADDR   0x011801d0L
#define IBU_P2_TX_TBSVL10_STRIDE 1
#define IBU_P2_TX_TBSVL10_DEPTH  1

#define IBU_P2_TX_TBSVL32_ADDR   0x011801d1L
#define IBU_P2_TX_TBSVL32_STRIDE 1
#define IBU_P2_TX_TBSVL32_DEPTH  1

#define IBU_P2_TX_TBSVL54_ADDR   0x011801d2L
#define IBU_P2_TX_TBSVL54_STRIDE 1
#define IBU_P2_TX_TBSVL54_DEPTH  1

#define IBU_P2_TX_TBSVL76_ADDR   0x011801d3L
#define IBU_P2_TX_TBSVL76_STRIDE 1
#define IBU_P2_TX_TBSVL76_DEPTH  1

#define IBU_P2_TX_TBSARB_VL10_ADDR   0x011801d4L
#define IBU_P2_TX_TBSARB_VL10_STRIDE 1
#define IBU_P2_TX_TBSARB_VL10_DEPTH  1

#define IBU_P2_TX_TBSARB_VL32_ADDR   0x011801d5L
#define IBU_P2_TX_TBSARB_VL32_STRIDE 1
#define IBU_P2_TX_TBSARB_VL32_DEPTH  1

#define IBU_P2_TX_TBSARB_VL54_ADDR   0x011801d6L
#define IBU_P2_TX_TBSARB_VL54_STRIDE 1
#define IBU_P2_TX_TBSARB_VL54_DEPTH  1

#define IBU_P2_TX_TBSARB_VL76_ADDR   0x011801d7L
#define IBU_P2_TX_TBSARB_VL76_STRIDE 1
#define IBU_P2_TX_TBSARB_VL76_DEPTH  1

#define IBU_P2_RX_TRACE_CAPTURE_ENABLE_ADDR   0x011801d8L
#define IBU_P2_RX_TRACE_CAPTURE_ENABLE_STRIDE 1
#define IBU_P2_RX_TRACE_CAPTURE_ENABLE_DEPTH  1

#define IBU_P2_RX_TRACE_CAPTURE_MODE_ADDR   0x011801d9L
#define IBU_P2_RX_TRACE_CAPTURE_MODE_STRIDE 1
#define IBU_P2_RX_TRACE_CAPTURE_MODE_DEPTH  1

#define IBU_P2_RX_TRACE_CAPTURE_RDY_ADDR   0x011801daL
#define IBU_P2_RX_TRACE_CAPTURE_RDY_STRIDE 1
#define IBU_P2_RX_TRACE_CAPTURE_RDY_DEPTH  1

#define IBU_P2_RX_TRACE_CAPTURE_TIMER_ADDR   0x011801dbL
#define IBU_P2_RX_TRACE_CAPTURE_TIMER_STRIDE 1
#define IBU_P2_RX_TRACE_CAPTURE_TIMER_DEPTH  1

#define IBU_P2_RX_TRACE_CAPTURE_START_ADDR   0x011801dcL
#define IBU_P2_RX_TRACE_CAPTURE_START_STRIDE 1
#define IBU_P2_RX_TRACE_CAPTURE_START_DEPTH  1

#define IBU_P2_RX_TRACE_CAPTURE_DATA1_ADDR   0x011801e0L
#define IBU_P2_RX_TRACE_CAPTURE_DATA1_STRIDE 1
#define IBU_P2_RX_TRACE_CAPTURE_DATA1_DEPTH  1

#define IBU_P2_RX_TRACE_CAPTURE_DATA2_ADDR   0x011801e1L
#define IBU_P2_RX_TRACE_CAPTURE_DATA2_STRIDE 1
#define IBU_P2_RX_TRACE_CAPTURE_DATA2_DEPTH  1

#define IBU_P2_RX_TRACE_CAPTURE_DATA3_ADDR   0x011801e2L
#define IBU_P2_RX_TRACE_CAPTURE_DATA3_STRIDE 1
#define IBU_P2_RX_TRACE_CAPTURE_DATA3_DEPTH  1

#define IBU_P2_RX_TRACE_CAPTURE_DATA4_ADDR   0x011801e3L
#define IBU_P2_RX_TRACE_CAPTURE_DATA4_STRIDE 1
#define IBU_P2_RX_TRACE_CAPTURE_DATA4_DEPTH  1

#define IBU_P2_RX_TRACE_CAPTURE_DATA5_ADDR   0x011801e4L
#define IBU_P2_RX_TRACE_CAPTURE_DATA5_STRIDE 1
#define IBU_P2_RX_TRACE_CAPTURE_DATA5_DEPTH  1

#define IBU_P2_RX_TRACE_CAPTURE_DATA6_ADDR   0x011801e5L
#define IBU_P2_RX_TRACE_CAPTURE_DATA6_STRIDE 1
#define IBU_P2_RX_TRACE_CAPTURE_DATA6_DEPTH  1

#define IBU_P2_RX_TRACE_CAPTURE_DATA7_ADDR   0x011801e6L
#define IBU_P2_RX_TRACE_CAPTURE_DATA7_STRIDE 1
#define IBU_P2_RX_TRACE_CAPTURE_DATA7_DEPTH  1

#define IBU_P2_RX_TRACE_CAPTURE_DATA8_ADDR   0x011801e7L
#define IBU_P2_RX_TRACE_CAPTURE_DATA8_STRIDE 1
#define IBU_P2_RX_TRACE_CAPTURE_DATA8_DEPTH  1

#define IBU_P2_RX_TRACE_CAPTURE_DATA9_ADDR   0x011801e8L
#define IBU_P2_RX_TRACE_CAPTURE_DATA9_STRIDE 1
#define IBU_P2_RX_TRACE_CAPTURE_DATA9_DEPTH  1

#define IBU_P2_RX_TRACE_CAPTURE_DATA10_ADDR   0x011801e9L
#define IBU_P2_RX_TRACE_CAPTURE_DATA10_STRIDE 1
#define IBU_P2_RX_TRACE_CAPTURE_DATA10_DEPTH  1

#define IBU_P2_LINK_RX_FCCL_VL1_0_ADDR   0x011801eaL
#define IBU_P2_LINK_RX_FCCL_VL1_0_STRIDE 1
#define IBU_P2_LINK_RX_FCCL_VL1_0_DEPTH  1

#define IBU_P2_LINK_RX_FCCL_VL3_2_ADDR   0x011801ebL
#define IBU_P2_LINK_RX_FCCL_VL3_2_STRIDE 1
#define IBU_P2_LINK_RX_FCCL_VL3_2_DEPTH  1

#define IBU_P2_LINK_RX_FCCL_VL5_4_ADDR   0x011801ecL
#define IBU_P2_LINK_RX_FCCL_VL5_4_STRIDE 1
#define IBU_P2_LINK_RX_FCCL_VL5_4_DEPTH  1

#define IBU_P2_LINK_RX_FCCL_VL7_6_ADDR   0x011801edL
#define IBU_P2_LINK_RX_FCCL_VL7_6_STRIDE 1
#define IBU_P2_LINK_RX_FCCL_VL7_6_DEPTH  1

#define IBU_P2_LINK_NEIGHBOR_JUMBO_MTU_ADDR   0x011801eeL
#define IBU_P2_LINK_NEIGHBOR_JUMBO_MTU_STRIDE 1
#define IBU_P2_LINK_NEIGHBOR_JUMBO_MTU_DEPTH  1

#define IBU_P2_ADD_DEFAULT_LANE0_ADDR   0x01180210L
#define IBU_P2_ADD_DEFAULT_LANE0_STRIDE 1
#define IBU_P2_ADD_DEFAULT_LANE0_DEPTH  1

#define IBU_P2_ADD_DEFAULT_LANE1_ADDR   0x01180211L
#define IBU_P2_ADD_DEFAULT_LANE1_STRIDE 1
#define IBU_P2_ADD_DEFAULT_LANE1_DEPTH  1

#define IBU_P2_ADD_DEFAULT_LANE2_ADDR   0x01180212L
#define IBU_P2_ADD_DEFAULT_LANE2_STRIDE 1
#define IBU_P2_ADD_DEFAULT_LANE2_DEPTH  1

#define IBU_P2_ADD_DEFAULT_LANE3_ADDR   0x01180213L
#define IBU_P2_ADD_DEFAULT_LANE3_STRIDE 1
#define IBU_P2_ADD_DEFAULT_LANE3_DEPTH  1

#define IBU_P2_PHY_ADD0_LANE0_ADDR   0x01180214L
#define IBU_P2_PHY_ADD0_LANE0_STRIDE 1
#define IBU_P2_PHY_ADD0_LANE0_DEPTH  1

#define IBU_P2_PHY_ADD0_LANE1_ADDR   0x01180215L
#define IBU_P2_PHY_ADD0_LANE1_STRIDE 1
#define IBU_P2_PHY_ADD0_LANE1_DEPTH  1

#define IBU_P2_PHY_ADD0_LANE2_ADDR   0x01180216L
#define IBU_P2_PHY_ADD0_LANE2_STRIDE 1
#define IBU_P2_PHY_ADD0_LANE2_DEPTH  1

#define IBU_P2_PHY_ADD0_LANE3_ADDR   0x01180217L
#define IBU_P2_PHY_ADD0_LANE3_STRIDE 1
#define IBU_P2_PHY_ADD0_LANE3_DEPTH  1

#define IBU_P2_PHY_ADD1_LANE0_ADDR   0x01180218L
#define IBU_P2_PHY_ADD1_LANE0_STRIDE 1
#define IBU_P2_PHY_ADD1_LANE0_DEPTH  1

#define IBU_P2_PHY_ADD1_LANE1_ADDR   0x01180219L
#define IBU_P2_PHY_ADD1_LANE1_STRIDE 1
#define IBU_P2_PHY_ADD1_LANE1_DEPTH  1

#define IBU_P2_PHY_ADD1_LANE2_ADDR   0x0118021aL
#define IBU_P2_PHY_ADD1_LANE2_STRIDE 1
#define IBU_P2_PHY_ADD1_LANE2_DEPTH  1

#define IBU_P2_PHY_ADD1_LANE3_ADDR   0x0118021bL
#define IBU_P2_PHY_ADD1_LANE3_STRIDE 1
#define IBU_P2_PHY_ADD1_LANE3_DEPTH  1

#define IBU_P2_PHY_ADD2_LANE0_ADDR   0x0118021cL
#define IBU_P2_PHY_ADD2_LANE0_STRIDE 1
#define IBU_P2_PHY_ADD2_LANE0_DEPTH  1

#define IBU_P2_PHY_ADD2_LANE1_ADDR   0x0118021dL
#define IBU_P2_PHY_ADD2_LANE1_STRIDE 1
#define IBU_P2_PHY_ADD2_LANE1_DEPTH  1

#define IBU_P2_PHY_ADD2_LANE2_ADDR   0x0118021eL
#define IBU_P2_PHY_ADD2_LANE2_STRIDE 1
#define IBU_P2_PHY_ADD2_LANE2_DEPTH  1

#define IBU_P2_PHY_ADD2_LANE3_ADDR   0x0118021fL
#define IBU_P2_PHY_ADD2_LANE3_STRIDE 1
#define IBU_P2_PHY_ADD2_LANE3_DEPTH  1

#define IBU_P2_PHY_ADD3_LANE0_ADDR   0x01180220L
#define IBU_P2_PHY_ADD3_LANE0_STRIDE 1
#define IBU_P2_PHY_ADD3_LANE0_DEPTH  1

#define IBU_P2_PHY_ADD3_LANE1_ADDR   0x01180221L
#define IBU_P2_PHY_ADD3_LANE1_STRIDE 1
#define IBU_P2_PHY_ADD3_LANE1_DEPTH  1

#define IBU_P2_PHY_ADD3_LANE2_ADDR   0x01180222L
#define IBU_P2_PHY_ADD3_LANE2_STRIDE 1
#define IBU_P2_PHY_ADD3_LANE2_DEPTH  1

#define IBU_P2_PHY_ADD3_LANE3_ADDR   0x01180223L
#define IBU_P2_PHY_ADD3_LANE3_STRIDE 1
#define IBU_P2_PHY_ADD3_LANE3_DEPTH  1

#define IBU_P2_PHY_ADD4_LANE0_ADDR   0x01180224L
#define IBU_P2_PHY_ADD4_LANE0_STRIDE 1
#define IBU_P2_PHY_ADD4_LANE0_DEPTH  1

#define IBU_P2_PHY_ADD4_LANE1_ADDR   0x01180225L
#define IBU_P2_PHY_ADD4_LANE1_STRIDE 1
#define IBU_P2_PHY_ADD4_LANE1_DEPTH  1

#define IBU_P2_PHY_ADD4_LANE2_ADDR   0x01180226L
#define IBU_P2_PHY_ADD4_LANE2_STRIDE 1
#define IBU_P2_PHY_ADD4_LANE2_DEPTH  1

#define IBU_P2_PHY_ADD4_LANE3_ADDR   0x01180227L
#define IBU_P2_PHY_ADD4_LANE3_STRIDE 1
#define IBU_P2_PHY_ADD4_LANE3_DEPTH  1

#define IBU_P2_PHY_ADD5_LANE0_ADDR   0x01180228L
#define IBU_P2_PHY_ADD5_LANE0_STRIDE 1
#define IBU_P2_PHY_ADD5_LANE0_DEPTH  1

#define IBU_P2_PHY_ADD5_LANE1_ADDR   0x01180229L
#define IBU_P2_PHY_ADD5_LANE1_STRIDE 1
#define IBU_P2_PHY_ADD5_LANE1_DEPTH  1

#define IBU_P2_PHY_ADD5_LANE2_ADDR   0x0118022aL
#define IBU_P2_PHY_ADD5_LANE2_STRIDE 1
#define IBU_P2_PHY_ADD5_LANE2_DEPTH  1

#define IBU_P2_PHY_ADD5_LANE3_ADDR   0x0118022bL
#define IBU_P2_PHY_ADD5_LANE3_STRIDE 1
#define IBU_P2_PHY_ADD5_LANE3_DEPTH  1

#define IBU_P2_PHY_ADD6_LANE0_ADDR   0x0118022cL
#define IBU_P2_PHY_ADD6_LANE0_STRIDE 1
#define IBU_P2_PHY_ADD6_LANE0_DEPTH  1

#define IBU_P2_PHY_ADD6_LANE1_ADDR   0x0118022dL
#define IBU_P2_PHY_ADD6_LANE1_STRIDE 1
#define IBU_P2_PHY_ADD6_LANE1_DEPTH  1

#define IBU_P2_PHY_ADD6_LANE2_ADDR   0x0118022eL
#define IBU_P2_PHY_ADD6_LANE2_STRIDE 1
#define IBU_P2_PHY_ADD6_LANE2_DEPTH  1

#define IBU_P2_PHY_ADD6_LANE3_ADDR   0x0118022fL
#define IBU_P2_PHY_ADD6_LANE3_STRIDE 1
#define IBU_P2_PHY_ADD6_LANE3_DEPTH  1

#define IBU_P2_PHY_ADD7_LANE0_ADDR   0x01180230L
#define IBU_P2_PHY_ADD7_LANE0_STRIDE 1
#define IBU_P2_PHY_ADD7_LANE0_DEPTH  1

#define IBU_P2_PHY_ADD7_LANE1_ADDR   0x01180231L
#define IBU_P2_PHY_ADD7_LANE1_STRIDE 1
#define IBU_P2_PHY_ADD7_LANE1_DEPTH  1

#define IBU_P2_PHY_ADD7_LANE2_ADDR   0x01180232L
#define IBU_P2_PHY_ADD7_LANE2_STRIDE 1
#define IBU_P2_PHY_ADD7_LANE2_DEPTH  1

#define IBU_P2_PHY_ADD7_LANE3_ADDR   0x01180233L
#define IBU_P2_PHY_ADD7_LANE3_STRIDE 1
#define IBU_P2_PHY_ADD7_LANE3_DEPTH  1

#define IBU_P2_PHY_ADD8_LANE0_ADDR   0x01180234L
#define IBU_P2_PHY_ADD8_LANE0_STRIDE 1
#define IBU_P2_PHY_ADD8_LANE0_DEPTH  1

#define IBU_P2_PHY_ADD8_LANE1_ADDR   0x01180235L
#define IBU_P2_PHY_ADD8_LANE1_STRIDE 1
#define IBU_P2_PHY_ADD8_LANE1_DEPTH  1

#define IBU_P2_PHY_ADD8_LANE2_ADDR   0x01180236L
#define IBU_P2_PHY_ADD8_LANE2_STRIDE 1
#define IBU_P2_PHY_ADD8_LANE2_DEPTH  1

#define IBU_P2_PHY_ADD8_LANE3_ADDR   0x01180237L
#define IBU_P2_PHY_ADD8_LANE3_STRIDE 1
#define IBU_P2_PHY_ADD8_LANE3_DEPTH  1

#define IBU_P2_PHY_ADD9_LANE0_ADDR   0x01180238L
#define IBU_P2_PHY_ADD9_LANE0_STRIDE 1
#define IBU_P2_PHY_ADD9_LANE0_DEPTH  1

#define IBU_P2_PHY_ADD9_LANE1_ADDR   0x01180239L
#define IBU_P2_PHY_ADD9_LANE1_STRIDE 1
#define IBU_P2_PHY_ADD9_LANE1_DEPTH  1

#define IBU_P2_PHY_ADD9_LANE2_ADDR   0x0118023aL
#define IBU_P2_PHY_ADD9_LANE2_STRIDE 1
#define IBU_P2_PHY_ADD9_LANE2_DEPTH  1

#define IBU_P2_PHY_ADD9_LANE3_ADDR   0x0118023bL
#define IBU_P2_PHY_ADD9_LANE3_STRIDE 1
#define IBU_P2_PHY_ADD9_LANE3_DEPTH  1

#define IBU_P2_PHY_ADD10_LANE0_ADDR   0x0118023cL
#define IBU_P2_PHY_ADD10_LANE0_STRIDE 1
#define IBU_P2_PHY_ADD10_LANE0_DEPTH  1

#define IBU_P2_PHY_ADD10_LANE1_ADDR   0x0118023dL
#define IBU_P2_PHY_ADD10_LANE1_STRIDE 1
#define IBU_P2_PHY_ADD10_LANE1_DEPTH  1

#define IBU_P2_PHY_ADD10_LANE2_ADDR   0x0118023eL
#define IBU_P2_PHY_ADD10_LANE2_STRIDE 1
#define IBU_P2_PHY_ADD10_LANE2_DEPTH  1

#define IBU_P2_PHY_ADD10_LANE3_ADDR   0x0118023fL
#define IBU_P2_PHY_ADD10_LANE3_STRIDE 1
#define IBU_P2_PHY_ADD10_LANE3_DEPTH  1

#define IBU_P2_PHY_ADD11_LANE0_ADDR   0x01180240L
#define IBU_P2_PHY_ADD11_LANE0_STRIDE 1
#define IBU_P2_PHY_ADD11_LANE0_DEPTH  1

#define IBU_P2_PHY_ADD11_LANE1_ADDR   0x01180241L
#define IBU_P2_PHY_ADD11_LANE1_STRIDE 1
#define IBU_P2_PHY_ADD11_LANE1_DEPTH  1

#define IBU_P2_PHY_ADD11_LANE2_ADDR   0x01180242L
#define IBU_P2_PHY_ADD11_LANE2_STRIDE 1
#define IBU_P2_PHY_ADD11_LANE2_DEPTH  1

#define IBU_P2_PHY_ADD11_LANE3_ADDR   0x01180243L
#define IBU_P2_PHY_ADD11_LANE3_STRIDE 1
#define IBU_P2_PHY_ADD11_LANE3_DEPTH  1

#define IBU_P2_PHY_ADD12_LANE0_ADDR   0x01180244L
#define IBU_P2_PHY_ADD12_LANE0_STRIDE 1
#define IBU_P2_PHY_ADD12_LANE0_DEPTH  1

#define IBU_P2_PHY_ADD12_LANE1_ADDR   0x01180245L
#define IBU_P2_PHY_ADD12_LANE1_STRIDE 1
#define IBU_P2_PHY_ADD12_LANE1_DEPTH  1

#define IBU_P2_PHY_ADD12_LANE2_ADDR   0x01180246L
#define IBU_P2_PHY_ADD12_LANE2_STRIDE 1
#define IBU_P2_PHY_ADD12_LANE2_DEPTH  1

#define IBU_P2_PHY_ADD12_LANE3_ADDR   0x01180247L
#define IBU_P2_PHY_ADD12_LANE3_STRIDE 1
#define IBU_P2_PHY_ADD12_LANE3_DEPTH  1

#define IBU_P2_PHY_ADD13_LANE0_ADDR   0x01180248L
#define IBU_P2_PHY_ADD13_LANE0_STRIDE 1
#define IBU_P2_PHY_ADD13_LANE0_DEPTH  1

#define IBU_P2_PHY_ADD13_LANE1_ADDR   0x01180249L
#define IBU_P2_PHY_ADD13_LANE1_STRIDE 1
#define IBU_P2_PHY_ADD13_LANE1_DEPTH  1

#define IBU_P2_PHY_ADD13_LANE2_ADDR   0x0118024aL
#define IBU_P2_PHY_ADD13_LANE2_STRIDE 1
#define IBU_P2_PHY_ADD13_LANE2_DEPTH  1

#define IBU_P2_PHY_ADD13_LANE3_ADDR   0x0118024bL
#define IBU_P2_PHY_ADD13_LANE3_STRIDE 1
#define IBU_P2_PHY_ADD13_LANE3_DEPTH  1

#define IBU_P2_PHY_ADD14_LANE0_ADDR   0x0118024cL
#define IBU_P2_PHY_ADD14_LANE0_STRIDE 1
#define IBU_P2_PHY_ADD14_LANE0_DEPTH  1

#define IBU_P2_PHY_ADD14_LANE1_ADDR   0x0118024dL
#define IBU_P2_PHY_ADD14_LANE1_STRIDE 1
#define IBU_P2_PHY_ADD14_LANE1_DEPTH  1

#define IBU_P2_PHY_ADD14_LANE2_ADDR   0x0118024eL
#define IBU_P2_PHY_ADD14_LANE2_STRIDE 1
#define IBU_P2_PHY_ADD14_LANE2_DEPTH  1

#define IBU_P2_PHY_ADD14_LANE3_ADDR   0x0118024fL
#define IBU_P2_PHY_ADD14_LANE3_STRIDE 1
#define IBU_P2_PHY_ADD14_LANE3_DEPTH  1

#define IBU_P2_PHY_ADD15_LANE0_ADDR   0x01180250L
#define IBU_P2_PHY_ADD15_LANE0_STRIDE 1
#define IBU_P2_PHY_ADD15_LANE0_DEPTH  1

#define IBU_P2_PHY_ADD15_LANE1_ADDR   0x01180251L
#define IBU_P2_PHY_ADD15_LANE1_STRIDE 1
#define IBU_P2_PHY_ADD15_LANE1_DEPTH  1

#define IBU_P2_PHY_ADD15_LANE2_ADDR   0x01180252L
#define IBU_P2_PHY_ADD15_LANE2_STRIDE 1
#define IBU_P2_PHY_ADD15_LANE2_DEPTH  1

#define IBU_P2_PHY_ADD15_LANE3_ADDR   0x01180253L
#define IBU_P2_PHY_ADD15_LANE3_STRIDE 1
#define IBU_P2_PHY_ADD15_LANE3_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD0_LANE0_ADDR   0x01180254L
#define IBU_P2_PHY_AMP1_ADD0_LANE0_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD0_LANE0_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD0_LANE1_ADDR   0x01180255L
#define IBU_P2_PHY_AMP1_ADD0_LANE1_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD0_LANE1_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD0_LANE2_ADDR   0x01180256L
#define IBU_P2_PHY_AMP1_ADD0_LANE2_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD0_LANE2_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD0_LANE3_ADDR   0x01180257L
#define IBU_P2_PHY_AMP1_ADD0_LANE3_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD0_LANE3_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD1_LANE0_ADDR   0x01180258L
#define IBU_P2_PHY_AMP1_ADD1_LANE0_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD1_LANE0_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD1_LANE1_ADDR   0x01180259L
#define IBU_P2_PHY_AMP1_ADD1_LANE1_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD1_LANE1_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD1_LANE2_ADDR   0x0118025aL
#define IBU_P2_PHY_AMP1_ADD1_LANE2_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD1_LANE2_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD1_LANE3_ADDR   0x0118025bL
#define IBU_P2_PHY_AMP1_ADD1_LANE3_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD1_LANE3_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD2_LANE0_ADDR   0x0118025cL
#define IBU_P2_PHY_AMP1_ADD2_LANE0_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD2_LANE0_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD2_LANE1_ADDR   0x0118025dL
#define IBU_P2_PHY_AMP1_ADD2_LANE1_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD2_LANE1_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD2_LANE2_ADDR   0x0118025eL
#define IBU_P2_PHY_AMP1_ADD2_LANE2_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD2_LANE2_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD2_LANE3_ADDR   0x0118025fL
#define IBU_P2_PHY_AMP1_ADD2_LANE3_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD2_LANE3_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD3_LANE0_ADDR   0x01180260L
#define IBU_P2_PHY_AMP1_ADD3_LANE0_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD3_LANE0_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD3_LANE1_ADDR   0x01180261L
#define IBU_P2_PHY_AMP1_ADD3_LANE1_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD3_LANE1_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD3_LANE2_ADDR   0x01180262L
#define IBU_P2_PHY_AMP1_ADD3_LANE2_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD3_LANE2_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD3_LANE3_ADDR   0x01180263L
#define IBU_P2_PHY_AMP1_ADD3_LANE3_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD3_LANE3_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD4_LANE0_ADDR   0x01180264L
#define IBU_P2_PHY_AMP1_ADD4_LANE0_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD4_LANE0_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD4_LANE1_ADDR   0x01180265L
#define IBU_P2_PHY_AMP1_ADD4_LANE1_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD4_LANE1_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD4_LANE2_ADDR   0x01180266L
#define IBU_P2_PHY_AMP1_ADD4_LANE2_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD4_LANE2_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD4_LANE3_ADDR   0x01180267L
#define IBU_P2_PHY_AMP1_ADD4_LANE3_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD4_LANE3_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD5_LANE0_ADDR   0x01180268L
#define IBU_P2_PHY_AMP1_ADD5_LANE0_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD5_LANE0_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD5_LANE1_ADDR   0x01180269L
#define IBU_P2_PHY_AMP1_ADD5_LANE1_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD5_LANE1_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD5_LANE2_ADDR   0x0118026aL
#define IBU_P2_PHY_AMP1_ADD5_LANE2_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD5_LANE2_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD5_LANE3_ADDR   0x0118026bL
#define IBU_P2_PHY_AMP1_ADD5_LANE3_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD5_LANE3_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD6_LANE0_ADDR   0x0118026cL
#define IBU_P2_PHY_AMP1_ADD6_LANE0_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD6_LANE0_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD6_LANE1_ADDR   0x0118026dL
#define IBU_P2_PHY_AMP1_ADD6_LANE1_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD6_LANE1_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD6_LANE2_ADDR   0x0118026eL
#define IBU_P2_PHY_AMP1_ADD6_LANE2_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD6_LANE2_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD6_LANE3_ADDR   0x0118026fL
#define IBU_P2_PHY_AMP1_ADD6_LANE3_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD6_LANE3_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD7_LANE0_ADDR   0x01180270L
#define IBU_P2_PHY_AMP1_ADD7_LANE0_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD7_LANE0_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD7_LANE1_ADDR   0x01180271L
#define IBU_P2_PHY_AMP1_ADD7_LANE1_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD7_LANE1_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD7_LANE2_ADDR   0x01180272L
#define IBU_P2_PHY_AMP1_ADD7_LANE2_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD7_LANE2_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD7_LANE3_ADDR   0x01180273L
#define IBU_P2_PHY_AMP1_ADD7_LANE3_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD7_LANE3_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD8_LANE0_ADDR   0x01180274L
#define IBU_P2_PHY_AMP1_ADD8_LANE0_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD8_LANE0_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD8_LANE1_ADDR   0x01180275L
#define IBU_P2_PHY_AMP1_ADD8_LANE1_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD8_LANE1_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD8_LANE2_ADDR   0x01180276L
#define IBU_P2_PHY_AMP1_ADD8_LANE2_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD8_LANE2_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD8_LANE3_ADDR   0x01180277L
#define IBU_P2_PHY_AMP1_ADD8_LANE3_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD8_LANE3_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD9_LANE0_ADDR   0x01180278L
#define IBU_P2_PHY_AMP1_ADD9_LANE0_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD9_LANE0_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD9_LANE1_ADDR   0x01180279L
#define IBU_P2_PHY_AMP1_ADD9_LANE1_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD9_LANE1_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD9_LANE2_ADDR   0x0118027aL
#define IBU_P2_PHY_AMP1_ADD9_LANE2_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD9_LANE2_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD9_LANE3_ADDR   0x0118027bL
#define IBU_P2_PHY_AMP1_ADD9_LANE3_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD9_LANE3_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD10_LANE0_ADDR   0x0118027cL
#define IBU_P2_PHY_AMP1_ADD10_LANE0_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD10_LANE0_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD10_LANE1_ADDR   0x0118027dL
#define IBU_P2_PHY_AMP1_ADD10_LANE1_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD10_LANE1_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD10_LANE2_ADDR   0x0118027eL
#define IBU_P2_PHY_AMP1_ADD10_LANE2_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD10_LANE2_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD10_LANE3_ADDR   0x0118027fL
#define IBU_P2_PHY_AMP1_ADD10_LANE3_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD10_LANE3_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD11_LANE0_ADDR   0x01180280L
#define IBU_P2_PHY_AMP1_ADD11_LANE0_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD11_LANE0_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD11_LANE1_ADDR   0x01180281L
#define IBU_P2_PHY_AMP1_ADD11_LANE1_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD11_LANE1_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD11_LANE2_ADDR   0x01180282L
#define IBU_P2_PHY_AMP1_ADD11_LANE2_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD11_LANE2_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD11_LANE3_ADDR   0x01180283L
#define IBU_P2_PHY_AMP1_ADD11_LANE3_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD11_LANE3_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD12_LANE0_ADDR   0x01180284L
#define IBU_P2_PHY_AMP1_ADD12_LANE0_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD12_LANE0_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD12_LANE1_ADDR   0x01180285L
#define IBU_P2_PHY_AMP1_ADD12_LANE1_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD12_LANE1_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD12_LANE2_ADDR   0x01180286L
#define IBU_P2_PHY_AMP1_ADD12_LANE2_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD12_LANE2_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD12_LANE3_ADDR   0x01180287L
#define IBU_P2_PHY_AMP1_ADD12_LANE3_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD12_LANE3_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD13_LANE0_ADDR   0x01180288L
#define IBU_P2_PHY_AMP1_ADD13_LANE0_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD13_LANE0_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD13_LANE1_ADDR   0x01180289L
#define IBU_P2_PHY_AMP1_ADD13_LANE1_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD13_LANE1_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD13_LANE2_ADDR   0x0118028aL
#define IBU_P2_PHY_AMP1_ADD13_LANE2_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD13_LANE2_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD13_LANE3_ADDR   0x0118028bL
#define IBU_P2_PHY_AMP1_ADD13_LANE3_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD13_LANE3_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD14_LANE0_ADDR   0x0118028cL
#define IBU_P2_PHY_AMP1_ADD14_LANE0_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD14_LANE0_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD14_LANE1_ADDR   0x0118028dL
#define IBU_P2_PHY_AMP1_ADD14_LANE1_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD14_LANE1_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD14_LANE2_ADDR   0x0118028eL
#define IBU_P2_PHY_AMP1_ADD14_LANE2_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD14_LANE2_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD14_LANE3_ADDR   0x0118028fL
#define IBU_P2_PHY_AMP1_ADD14_LANE3_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD14_LANE3_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD15_LANE0_ADDR   0x01180290L
#define IBU_P2_PHY_AMP1_ADD15_LANE0_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD15_LANE0_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD15_LANE1_ADDR   0x01180291L
#define IBU_P2_PHY_AMP1_ADD15_LANE1_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD15_LANE1_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD15_LANE2_ADDR   0x01180292L
#define IBU_P2_PHY_AMP1_ADD15_LANE2_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD15_LANE2_DEPTH  1

#define IBU_P2_PHY_AMP1_ADD15_LANE3_ADDR   0x01180293L
#define IBU_P2_PHY_AMP1_ADD15_LANE3_STRIDE 1
#define IBU_P2_PHY_AMP1_ADD15_LANE3_DEPTH  1

#define IBU_P2_REMOTE_DDS0_ADDR   0x01180294L
#define IBU_P2_REMOTE_DDS0_STRIDE 1
#define IBU_P2_REMOTE_DDS0_DEPTH  1

#define IBU_P2_REMOTE_DDS1_ADDR   0x01180295L
#define IBU_P2_REMOTE_DDS1_STRIDE 1
#define IBU_P2_REMOTE_DDS1_DEPTH  1

#define IBU_P2_REMOTE_DDS2_ADDR   0x01180296L
#define IBU_P2_REMOTE_DDS2_STRIDE 1
#define IBU_P2_REMOTE_DDS2_DEPTH  1

#define IBU_P2_REMOTE_DDS3_ADDR   0x01180297L
#define IBU_P2_REMOTE_DDS3_STRIDE 1
#define IBU_P2_REMOTE_DDS3_DEPTH  1

#define IBU_P2_REMOTE_DDS4_ADDR   0x01180298L
#define IBU_P2_REMOTE_DDS4_STRIDE 1
#define IBU_P2_REMOTE_DDS4_DEPTH  1

#define IBU_P2_REMOTE_DDS5_ADDR   0x01180299L
#define IBU_P2_REMOTE_DDS5_STRIDE 1
#define IBU_P2_REMOTE_DDS5_DEPTH  1

#define IBU_P2_REMOTE_DDS6_ADDR   0x0118029aL
#define IBU_P2_REMOTE_DDS6_STRIDE 1
#define IBU_P2_REMOTE_DDS6_DEPTH  1

#define IBU_P2_REMOTE_DDS7_ADDR   0x0118029bL
#define IBU_P2_REMOTE_DDS7_STRIDE 1
#define IBU_P2_REMOTE_DDS7_DEPTH  1

#define IBU_P2_REMOTE_DDS8_ADDR   0x0118029cL
#define IBU_P2_REMOTE_DDS8_STRIDE 1
#define IBU_P2_REMOTE_DDS8_DEPTH  1

#define IBU_P2_REMOTE_DDS9_ADDR   0x0118029dL
#define IBU_P2_REMOTE_DDS9_STRIDE 1
#define IBU_P2_REMOTE_DDS9_DEPTH  1

#define IBU_P2_REMOTE_DDS10_ADDR   0x0118029eL
#define IBU_P2_REMOTE_DDS10_STRIDE 1
#define IBU_P2_REMOTE_DDS10_DEPTH  1

#define IBU_P2_REMOTE_DDS11_ADDR   0x0118029fL
#define IBU_P2_REMOTE_DDS11_STRIDE 1
#define IBU_P2_REMOTE_DDS11_DEPTH  1

#define IBU_P2_REMOTE_DDS12_ADDR   0x011802a0L
#define IBU_P2_REMOTE_DDS12_STRIDE 1
#define IBU_P2_REMOTE_DDS12_DEPTH  1

#define IBU_P2_REMOTE_DDS13_ADDR   0x011802a1L
#define IBU_P2_REMOTE_DDS13_STRIDE 1
#define IBU_P2_REMOTE_DDS13_DEPTH  1

#define IBU_P2_REMOTE_DDS14_ADDR   0x011802a2L
#define IBU_P2_REMOTE_DDS14_STRIDE 1
#define IBU_P2_REMOTE_DDS14_DEPTH  1

#define IBU_P2_REMOTE_DDS15_ADDR   0x011802a3L
#define IBU_P2_REMOTE_DDS15_STRIDE 1
#define IBU_P2_REMOTE_DDS15_DEPTH  1

#define IBU_P2_BAD_CSR_ADDR   0x01180badL
#define IBU_P2_BAD_CSR_STRIDE 1
#define IBU_P2_BAD_CSR_DEPTH  1

	/* CETUS register */
#define IBU_P2_CETUS_CH0_000_ADDR   0x011c0000L
#define IBU_P2_CETUS_CH0_000_STRIDE 1
#define IBU_P2_CETUS_CH0_000_DEPTH  1

	/* CETUS register */
#define IBU_P2_CETUS_CH0_001_ADDR   0x011c0001L
#define IBU_P2_CETUS_CH0_001_STRIDE 1
#define IBU_P2_CETUS_CH0_001_DEPTH  1

	/* CETUS register */
#define IBU_P2_CETUS_CH0_002_ADDR   0x011c0002L
#define IBU_P2_CETUS_CH0_002_STRIDE 1
#define IBU_P2_CETUS_CH0_002_DEPTH  1

#define IBU_P2_CETUS_CH0_003_ADDR   0x011c0003L
#define IBU_P2_CETUS_CH0_003_STRIDE 1
#define IBU_P2_CETUS_CH0_003_DEPTH  1

#define IBU_P2_CETUS_CH0_004_ADDR   0x011c0004L
#define IBU_P2_CETUS_CH0_004_STRIDE 1
#define IBU_P2_CETUS_CH0_004_DEPTH  1

#define IBU_P2_CETUS_CH0_005_ADDR   0x011c0005L
#define IBU_P2_CETUS_CH0_005_STRIDE 1
#define IBU_P2_CETUS_CH0_005_DEPTH  1

#define IBU_P2_CETUS_CH0_006_ADDR   0x011c0006L
#define IBU_P2_CETUS_CH0_006_STRIDE 1
#define IBU_P2_CETUS_CH0_006_DEPTH  1

#define IBU_P2_CETUS_CH0_007_ADDR   0x011c0007L
#define IBU_P2_CETUS_CH0_007_STRIDE 1
#define IBU_P2_CETUS_CH0_007_DEPTH  1

#define IBU_P2_CETUS_CH0_008_ADDR   0x011c0008L
#define IBU_P2_CETUS_CH0_008_STRIDE 1
#define IBU_P2_CETUS_CH0_008_DEPTH  1

#define IBU_P2_CETUS_CH0_009_ADDR   0x011c0009L
#define IBU_P2_CETUS_CH0_009_STRIDE 1
#define IBU_P2_CETUS_CH0_009_DEPTH  1

#define IBU_P2_CETUS_CH0_010_ADDR   0x011c000aL
#define IBU_P2_CETUS_CH0_010_STRIDE 1
#define IBU_P2_CETUS_CH0_010_DEPTH  1

#define IBU_P2_CETUS_CH0_011_ADDR   0x011c000bL
#define IBU_P2_CETUS_CH0_011_STRIDE 1
#define IBU_P2_CETUS_CH0_011_DEPTH  1

#define IBU_P2_CETUS_CH0_012_ADDR   0x011c000cL
#define IBU_P2_CETUS_CH0_012_STRIDE 1
#define IBU_P2_CETUS_CH0_012_DEPTH  1

#define IBU_P2_CETUS_CH0_013_ADDR   0x011c000dL
#define IBU_P2_CETUS_CH0_013_STRIDE 1
#define IBU_P2_CETUS_CH0_013_DEPTH  1

#define IBU_P2_CETUS_CH0_014_ADDR   0x011c000eL
#define IBU_P2_CETUS_CH0_014_STRIDE 1
#define IBU_P2_CETUS_CH0_014_DEPTH  1

#define IBU_P2_CETUS_CH0_015_ADDR   0x011c000fL
#define IBU_P2_CETUS_CH0_015_STRIDE 1
#define IBU_P2_CETUS_CH0_015_DEPTH  1

#define IBU_P2_CETUS_CH0_016_ADDR   0x011c0010L
#define IBU_P2_CETUS_CH0_016_STRIDE 1
#define IBU_P2_CETUS_CH0_016_DEPTH  1

#define IBU_P2_CETUS_CH0_017_ADDR   0x011c0011L
#define IBU_P2_CETUS_CH0_017_STRIDE 1
#define IBU_P2_CETUS_CH0_017_DEPTH  1

#define IBU_P2_CETUS_CH0_018_ADDR   0x011c0012L
#define IBU_P2_CETUS_CH0_018_STRIDE 1
#define IBU_P2_CETUS_CH0_018_DEPTH  1

#define IBU_P2_CETUS_CH0_019_ADDR   0x011c0013L
#define IBU_P2_CETUS_CH0_019_STRIDE 1
#define IBU_P2_CETUS_CH0_019_DEPTH  1

#define IBU_P2_CETUS_CH0_020_ADDR   0x011c0014L
#define IBU_P2_CETUS_CH0_020_STRIDE 1
#define IBU_P2_CETUS_CH0_020_DEPTH  1

#define IBU_P2_CETUS_CH0_021_ADDR   0x011c0015L
#define IBU_P2_CETUS_CH0_021_STRIDE 1
#define IBU_P2_CETUS_CH0_021_DEPTH  1

#define IBU_P2_CETUS_CH0_022_ADDR   0x011c0016L
#define IBU_P2_CETUS_CH0_022_STRIDE 1
#define IBU_P2_CETUS_CH0_022_DEPTH  1

#define IBU_P2_CETUS_CH0_023_ADDR   0x011c0017L
#define IBU_P2_CETUS_CH0_023_STRIDE 1
#define IBU_P2_CETUS_CH0_023_DEPTH  1

#define IBU_P2_CETUS_CH0_024_ADDR   0x011c0018L
#define IBU_P2_CETUS_CH0_024_STRIDE 1
#define IBU_P2_CETUS_CH0_024_DEPTH  1

#define IBU_P2_CETUS_CH0_025_ADDR   0x011c0019L
#define IBU_P2_CETUS_CH0_025_STRIDE 1
#define IBU_P2_CETUS_CH0_025_DEPTH  1

#define IBU_P2_CETUS_CH0_026_ADDR   0x011c001aL
#define IBU_P2_CETUS_CH0_026_STRIDE 1
#define IBU_P2_CETUS_CH0_026_DEPTH  1

#define IBU_P2_CETUS_CH0_027_ADDR   0x011c001bL
#define IBU_P2_CETUS_CH0_027_STRIDE 1
#define IBU_P2_CETUS_CH0_027_DEPTH  1

#define IBU_P2_CETUS_CH0_028_ADDR   0x011c001cL
#define IBU_P2_CETUS_CH0_028_STRIDE 1
#define IBU_P2_CETUS_CH0_028_DEPTH  1

#define IBU_P2_CETUS_CH0_029_ADDR   0x011c001dL
#define IBU_P2_CETUS_CH0_029_STRIDE 1
#define IBU_P2_CETUS_CH0_029_DEPTH  1

#define IBU_P2_CETUS_CH0_030_ADDR   0x011c001eL
#define IBU_P2_CETUS_CH0_030_STRIDE 1
#define IBU_P2_CETUS_CH0_030_DEPTH  1

#define IBU_P2_CETUS_CH0_031_ADDR   0x011c001fL
#define IBU_P2_CETUS_CH0_031_STRIDE 1
#define IBU_P2_CETUS_CH0_031_DEPTH  1

#define IBU_P2_CETUS_CH0_032_ADDR   0x011c0020L
#define IBU_P2_CETUS_CH0_032_STRIDE 1
#define IBU_P2_CETUS_CH0_032_DEPTH  1

#define IBU_P2_CETUS_CH0_033_ADDR   0x011c0021L
#define IBU_P2_CETUS_CH0_033_STRIDE 1
#define IBU_P2_CETUS_CH0_033_DEPTH  1

#define IBU_P2_CETUS_CH0_034_ADDR   0x011c0022L
#define IBU_P2_CETUS_CH0_034_STRIDE 1
#define IBU_P2_CETUS_CH0_034_DEPTH  1

#define IBU_P2_CETUS_CH0_035_ADDR   0x011c0023L
#define IBU_P2_CETUS_CH0_035_STRIDE 1
#define IBU_P2_CETUS_CH0_035_DEPTH  1

#define IBU_P2_CETUS_CH0_036_ADDR   0x011c0024L
#define IBU_P2_CETUS_CH0_036_STRIDE 1
#define IBU_P2_CETUS_CH0_036_DEPTH  1

#define IBU_P2_CETUS_CH0_037_ADDR   0x011c0025L
#define IBU_P2_CETUS_CH0_037_STRIDE 1
#define IBU_P2_CETUS_CH0_037_DEPTH  1

#define IBU_P2_CETUS_CH0_038_ADDR   0x011c0026L
#define IBU_P2_CETUS_CH0_038_STRIDE 1
#define IBU_P2_CETUS_CH0_038_DEPTH  1

#define IBU_P2_CETUS_CH0_039_ADDR   0x011c0027L
#define IBU_P2_CETUS_CH0_039_STRIDE 1
#define IBU_P2_CETUS_CH0_039_DEPTH  1

#define IBU_P2_CETUS_CH0_040_ADDR   0x011c0028L
#define IBU_P2_CETUS_CH0_040_STRIDE 1
#define IBU_P2_CETUS_CH0_040_DEPTH  1

#define IBU_P2_CETUS_CH0_041_ADDR   0x011c0029L
#define IBU_P2_CETUS_CH0_041_STRIDE 1
#define IBU_P2_CETUS_CH0_041_DEPTH  1

#define IBU_P2_CETUS_CH0_042_ADDR   0x011c002aL
#define IBU_P2_CETUS_CH0_042_STRIDE 1
#define IBU_P2_CETUS_CH0_042_DEPTH  1

#define IBU_P2_CETUS_CH0_043_ADDR   0x011c002bL
#define IBU_P2_CETUS_CH0_043_STRIDE 1
#define IBU_P2_CETUS_CH0_043_DEPTH  1

#define IBU_P2_CETUS_CH0_044_ADDR   0x011c002cL
#define IBU_P2_CETUS_CH0_044_STRIDE 1
#define IBU_P2_CETUS_CH0_044_DEPTH  1

#define IBU_P2_CETUS_CH0_045_ADDR   0x011c002dL
#define IBU_P2_CETUS_CH0_045_STRIDE 1
#define IBU_P2_CETUS_CH0_045_DEPTH  1

#define IBU_P2_CETUS_CH0_046_ADDR   0x011c002eL
#define IBU_P2_CETUS_CH0_046_STRIDE 1
#define IBU_P2_CETUS_CH0_046_DEPTH  1

#define IBU_P2_CETUS_CH0_047_ADDR   0x011c002fL
#define IBU_P2_CETUS_CH0_047_STRIDE 1
#define IBU_P2_CETUS_CH0_047_DEPTH  1

#define IBU_P2_CETUS_CH0_048_ADDR   0x011c0030L
#define IBU_P2_CETUS_CH0_048_STRIDE 1
#define IBU_P2_CETUS_CH0_048_DEPTH  1

#define IBU_P2_CETUS_CH0_049_ADDR   0x011c0031L
#define IBU_P2_CETUS_CH0_049_STRIDE 1
#define IBU_P2_CETUS_CH0_049_DEPTH  1

#define IBU_P2_CETUS_CH0_050_ADDR   0x011c0032L
#define IBU_P2_CETUS_CH0_050_STRIDE 1
#define IBU_P2_CETUS_CH0_050_DEPTH  1

#define IBU_P2_CETUS_CH0_051_ADDR   0x011c0033L
#define IBU_P2_CETUS_CH0_051_STRIDE 1
#define IBU_P2_CETUS_CH0_051_DEPTH  1

#define IBU_P2_CETUS_CH0_052_ADDR   0x011c0034L
#define IBU_P2_CETUS_CH0_052_STRIDE 1
#define IBU_P2_CETUS_CH0_052_DEPTH  1

#define IBU_P2_CETUS_CH0_053_ADDR   0x011c0035L
#define IBU_P2_CETUS_CH0_053_STRIDE 1
#define IBU_P2_CETUS_CH0_053_DEPTH  1

#define IBU_P2_CETUS_CH0_054_ADDR   0x011c0036L
#define IBU_P2_CETUS_CH0_054_STRIDE 1
#define IBU_P2_CETUS_CH0_054_DEPTH  1

#define IBU_P2_CETUS_CH0_055_ADDR   0x011c0037L
#define IBU_P2_CETUS_CH0_055_STRIDE 1
#define IBU_P2_CETUS_CH0_055_DEPTH  1

#define IBU_P2_CETUS_CH0_056_ADDR   0x011c0038L
#define IBU_P2_CETUS_CH0_056_STRIDE 1
#define IBU_P2_CETUS_CH0_056_DEPTH  1

#define IBU_P2_CETUS_CH0_057_ADDR   0x011c0039L
#define IBU_P2_CETUS_CH0_057_STRIDE 1
#define IBU_P2_CETUS_CH0_057_DEPTH  1

#define IBU_P2_CETUS_CH0_058_ADDR   0x011c003aL
#define IBU_P2_CETUS_CH0_058_STRIDE 1
#define IBU_P2_CETUS_CH0_058_DEPTH  1

#define IBU_P2_CETUS_CH0_059_ADDR   0x011c003bL
#define IBU_P2_CETUS_CH0_059_STRIDE 1
#define IBU_P2_CETUS_CH0_059_DEPTH  1

#define IBU_P2_CETUS_CH0_060_ADDR   0x011c003cL
#define IBU_P2_CETUS_CH0_060_STRIDE 1
#define IBU_P2_CETUS_CH0_060_DEPTH  1

#define IBU_P2_CETUS_CH0_061_ADDR   0x011c003dL
#define IBU_P2_CETUS_CH0_061_STRIDE 1
#define IBU_P2_CETUS_CH0_061_DEPTH  1

#define IBU_P2_CETUS_CH0_062_ADDR   0x011c003eL
#define IBU_P2_CETUS_CH0_062_STRIDE 1
#define IBU_P2_CETUS_CH0_062_DEPTH  1

#define IBU_P2_CETUS_CH0_063_ADDR   0x011c003fL
#define IBU_P2_CETUS_CH0_063_STRIDE 1
#define IBU_P2_CETUS_CH0_063_DEPTH  1

#define IBU_P2_CETUS_CH0_064_ADDR   0x011c0040L
#define IBU_P2_CETUS_CH0_064_STRIDE 1
#define IBU_P2_CETUS_CH0_064_DEPTH  1

#define IBU_P2_CETUS_CH0_065_ADDR   0x011c0041L
#define IBU_P2_CETUS_CH0_065_STRIDE 1
#define IBU_P2_CETUS_CH0_065_DEPTH  1

#define IBU_P2_CETUS_CH0_066_ADDR   0x011c0042L
#define IBU_P2_CETUS_CH0_066_STRIDE 1
#define IBU_P2_CETUS_CH0_066_DEPTH  1

#define IBU_P2_CETUS_CH0_067_ADDR   0x011c0043L
#define IBU_P2_CETUS_CH0_067_STRIDE 1
#define IBU_P2_CETUS_CH0_067_DEPTH  1

#define IBU_P2_CETUS_CH0_068_ADDR   0x011c0044L
#define IBU_P2_CETUS_CH0_068_STRIDE 1
#define IBU_P2_CETUS_CH0_068_DEPTH  1

#define IBU_P2_CETUS_CH0_069_ADDR   0x011c0045L
#define IBU_P2_CETUS_CH0_069_STRIDE 1
#define IBU_P2_CETUS_CH0_069_DEPTH  1

#define IBU_P2_CETUS_CH0_070_ADDR   0x011c0046L
#define IBU_P2_CETUS_CH0_070_STRIDE 1
#define IBU_P2_CETUS_CH0_070_DEPTH  1

#define IBU_P2_CETUS_CH0_071_ADDR   0x011c0047L
#define IBU_P2_CETUS_CH0_071_STRIDE 1
#define IBU_P2_CETUS_CH0_071_DEPTH  1

#define IBU_P2_CETUS_CH0_072_ADDR   0x011c0048L
#define IBU_P2_CETUS_CH0_072_STRIDE 1
#define IBU_P2_CETUS_CH0_072_DEPTH  1

#define IBU_P2_CETUS_CH0_073_ADDR   0x011c0049L
#define IBU_P2_CETUS_CH0_073_STRIDE 1
#define IBU_P2_CETUS_CH0_073_DEPTH  1

#define IBU_P2_CETUS_CH0_074_ADDR   0x011c004aL
#define IBU_P2_CETUS_CH0_074_STRIDE 1
#define IBU_P2_CETUS_CH0_074_DEPTH  1

#define IBU_P2_CETUS_CH0_075_ADDR   0x011c004bL
#define IBU_P2_CETUS_CH0_075_STRIDE 1
#define IBU_P2_CETUS_CH0_075_DEPTH  1

#define IBU_P2_CETUS_CH0_076_ADDR   0x011c004cL
#define IBU_P2_CETUS_CH0_076_STRIDE 1
#define IBU_P2_CETUS_CH0_076_DEPTH  1

#define IBU_P2_CETUS_CH0_077_ADDR   0x011c004dL
#define IBU_P2_CETUS_CH0_077_STRIDE 1
#define IBU_P2_CETUS_CH0_077_DEPTH  1

#define IBU_P2_CETUS_CH0_078_ADDR   0x011c004eL
#define IBU_P2_CETUS_CH0_078_STRIDE 1
#define IBU_P2_CETUS_CH0_078_DEPTH  1

#define IBU_P2_CETUS_CH0_079_ADDR   0x011c004fL
#define IBU_P2_CETUS_CH0_079_STRIDE 1
#define IBU_P2_CETUS_CH0_079_DEPTH  1

#define IBU_P2_CETUS_CH0_080_ADDR   0x011c0050L
#define IBU_P2_CETUS_CH0_080_STRIDE 1
#define IBU_P2_CETUS_CH0_080_DEPTH  1

#define IBU_P2_CETUS_CH0_081_ADDR   0x011c0051L
#define IBU_P2_CETUS_CH0_081_STRIDE 1
#define IBU_P2_CETUS_CH0_081_DEPTH  1

#define IBU_P2_CETUS_CH0_082_ADDR   0x011c0052L
#define IBU_P2_CETUS_CH0_082_STRIDE 1
#define IBU_P2_CETUS_CH0_082_DEPTH  1

#define IBU_P2_CETUS_CH0_083_ADDR   0x011c0053L
#define IBU_P2_CETUS_CH0_083_STRIDE 1
#define IBU_P2_CETUS_CH0_083_DEPTH  1

#define IBU_P2_CETUS_CH0_084_ADDR   0x011c0054L
#define IBU_P2_CETUS_CH0_084_STRIDE 1
#define IBU_P2_CETUS_CH0_084_DEPTH  1

#define IBU_P2_CETUS_CH0_085_ADDR   0x011c0055L
#define IBU_P2_CETUS_CH0_085_STRIDE 1
#define IBU_P2_CETUS_CH0_085_DEPTH  1

#define IBU_P2_CETUS_CH0_086_ADDR   0x011c0056L
#define IBU_P2_CETUS_CH0_086_STRIDE 1
#define IBU_P2_CETUS_CH0_086_DEPTH  1

#define IBU_P2_CETUS_CH0_087_ADDR   0x011c0057L
#define IBU_P2_CETUS_CH0_087_STRIDE 1
#define IBU_P2_CETUS_CH0_087_DEPTH  1

#define IBU_P2_CETUS_CH0_088_ADDR   0x011c0058L
#define IBU_P2_CETUS_CH0_088_STRIDE 1
#define IBU_P2_CETUS_CH0_088_DEPTH  1

#define IBU_P2_CETUS_CH0_089_ADDR   0x011c0059L
#define IBU_P2_CETUS_CH0_089_STRIDE 1
#define IBU_P2_CETUS_CH0_089_DEPTH  1

#define IBU_P2_CETUS_CH0_090_ADDR   0x011c005aL
#define IBU_P2_CETUS_CH0_090_STRIDE 1
#define IBU_P2_CETUS_CH0_090_DEPTH  1

#define IBU_P2_CETUS_CH0_091_ADDR   0x011c005bL
#define IBU_P2_CETUS_CH0_091_STRIDE 1
#define IBU_P2_CETUS_CH0_091_DEPTH  1

#define IBU_P2_CETUS_CH0_092_ADDR   0x011c005cL
#define IBU_P2_CETUS_CH0_092_STRIDE 1
#define IBU_P2_CETUS_CH0_092_DEPTH  1

#define IBU_P2_CETUS_CH0_093_ADDR   0x011c005dL
#define IBU_P2_CETUS_CH0_093_STRIDE 1
#define IBU_P2_CETUS_CH0_093_DEPTH  1

#define IBU_P2_CETUS_CH0_094_ADDR   0x011c005eL
#define IBU_P2_CETUS_CH0_094_STRIDE 1
#define IBU_P2_CETUS_CH0_094_DEPTH  1

#define IBU_P2_CETUS_CH0_095_ADDR   0x011c005fL
#define IBU_P2_CETUS_CH0_095_STRIDE 1
#define IBU_P2_CETUS_CH0_095_DEPTH  1

#define IBU_P2_CETUS_CH0_096_ADDR   0x011c0060L
#define IBU_P2_CETUS_CH0_096_STRIDE 1
#define IBU_P2_CETUS_CH0_096_DEPTH  1

#define IBU_P2_CETUS_CH0_097_ADDR   0x011c0061L
#define IBU_P2_CETUS_CH0_097_STRIDE 1
#define IBU_P2_CETUS_CH0_097_DEPTH  1

#define IBU_P2_CETUS_CH0_098_ADDR   0x011c0062L
#define IBU_P2_CETUS_CH0_098_STRIDE 1
#define IBU_P2_CETUS_CH0_098_DEPTH  1

#define IBU_P2_CETUS_CH0_099_ADDR   0x011c0063L
#define IBU_P2_CETUS_CH0_099_STRIDE 1
#define IBU_P2_CETUS_CH0_099_DEPTH  1

#define IBU_P2_CETUS_CH0_100_ADDR   0x011c0064L
#define IBU_P2_CETUS_CH0_100_STRIDE 1
#define IBU_P2_CETUS_CH0_100_DEPTH  1

#define IBU_P2_CETUS_CH0_101_ADDR   0x011c0065L
#define IBU_P2_CETUS_CH0_101_STRIDE 1
#define IBU_P2_CETUS_CH0_101_DEPTH  1

#define IBU_P2_CETUS_CH0_102_ADDR   0x011c0066L
#define IBU_P2_CETUS_CH0_102_STRIDE 1
#define IBU_P2_CETUS_CH0_102_DEPTH  1

#define IBU_P2_CETUS_CH0_103_ADDR   0x011c0067L
#define IBU_P2_CETUS_CH0_103_STRIDE 1
#define IBU_P2_CETUS_CH0_103_DEPTH  1

#define IBU_P2_CETUS_CH0_104_ADDR   0x011c0068L
#define IBU_P2_CETUS_CH0_104_STRIDE 1
#define IBU_P2_CETUS_CH0_104_DEPTH  1

#define IBU_P2_CETUS_CH0_105_ADDR   0x011c0069L
#define IBU_P2_CETUS_CH0_105_STRIDE 1
#define IBU_P2_CETUS_CH0_105_DEPTH  1

#define IBU_P2_CETUS_CH0_106_ADDR   0x011c006aL
#define IBU_P2_CETUS_CH0_106_STRIDE 1
#define IBU_P2_CETUS_CH0_106_DEPTH  1

#define IBU_P2_CETUS_CH0_107_ADDR   0x011c006bL
#define IBU_P2_CETUS_CH0_107_STRIDE 1
#define IBU_P2_CETUS_CH0_107_DEPTH  1

#define IBU_P2_CETUS_CH0_108_ADDR   0x011c006cL
#define IBU_P2_CETUS_CH0_108_STRIDE 1
#define IBU_P2_CETUS_CH0_108_DEPTH  1

#define IBU_P2_CETUS_CH0_109_ADDR   0x011c006dL
#define IBU_P2_CETUS_CH0_109_STRIDE 1
#define IBU_P2_CETUS_CH0_109_DEPTH  1

#define IBU_P2_CETUS_CH0_110_ADDR   0x011c006eL
#define IBU_P2_CETUS_CH0_110_STRIDE 1
#define IBU_P2_CETUS_CH0_110_DEPTH  1

#define IBU_P2_CETUS_CH0_111_ADDR   0x011c006fL
#define IBU_P2_CETUS_CH0_111_STRIDE 1
#define IBU_P2_CETUS_CH0_111_DEPTH  1

#define IBU_P2_CETUS_CH0_112_ADDR   0x011c0070L
#define IBU_P2_CETUS_CH0_112_STRIDE 1
#define IBU_P2_CETUS_CH0_112_DEPTH  1

#define IBU_P2_CETUS_CH0_113_ADDR   0x011c0071L
#define IBU_P2_CETUS_CH0_113_STRIDE 1
#define IBU_P2_CETUS_CH0_113_DEPTH  1

#define IBU_P2_CETUS_CH0_114_ADDR   0x011c0072L
#define IBU_P2_CETUS_CH0_114_STRIDE 1
#define IBU_P2_CETUS_CH0_114_DEPTH  1

#define IBU_P2_CETUS_CH0_115_ADDR   0x011c0073L
#define IBU_P2_CETUS_CH0_115_STRIDE 1
#define IBU_P2_CETUS_CH0_115_DEPTH  1

#define IBU_P2_CETUS_CH0_116_ADDR   0x011c0074L
#define IBU_P2_CETUS_CH0_116_STRIDE 1
#define IBU_P2_CETUS_CH0_116_DEPTH  1

#define IBU_P2_CETUS_CH0_117_ADDR   0x011c0075L
#define IBU_P2_CETUS_CH0_117_STRIDE 1
#define IBU_P2_CETUS_CH0_117_DEPTH  1

#define IBU_P2_CETUS_CH0_118_ADDR   0x011c0076L
#define IBU_P2_CETUS_CH0_118_STRIDE 1
#define IBU_P2_CETUS_CH0_118_DEPTH  1

#define IBU_P2_CETUS_CH0_119_ADDR   0x011c0077L
#define IBU_P2_CETUS_CH0_119_STRIDE 1
#define IBU_P2_CETUS_CH0_119_DEPTH  1

#define IBU_P2_CETUS_CH0_120_ADDR   0x011c0078L
#define IBU_P2_CETUS_CH0_120_STRIDE 1
#define IBU_P2_CETUS_CH0_120_DEPTH  1

#define IBU_P2_CETUS_CH0_121_ADDR   0x011c0079L
#define IBU_P2_CETUS_CH0_121_STRIDE 1
#define IBU_P2_CETUS_CH0_121_DEPTH  1

#define IBU_P2_CETUS_CH0_122_ADDR   0x011c007aL
#define IBU_P2_CETUS_CH0_122_STRIDE 1
#define IBU_P2_CETUS_CH0_122_DEPTH  1

#define IBU_P2_CETUS_CH0_123_ADDR   0x011c007bL
#define IBU_P2_CETUS_CH0_123_STRIDE 1
#define IBU_P2_CETUS_CH0_123_DEPTH  1

#define IBU_P2_CETUS_CH0_124_ADDR   0x011c007cL
#define IBU_P2_CETUS_CH0_124_STRIDE 1
#define IBU_P2_CETUS_CH0_124_DEPTH  1

#define IBU_P2_CETUS_CH0_125_ADDR   0x011c007dL
#define IBU_P2_CETUS_CH0_125_STRIDE 1
#define IBU_P2_CETUS_CH0_125_DEPTH  1

#define IBU_P2_CETUS_CH0_126_ADDR   0x011c007eL
#define IBU_P2_CETUS_CH0_126_STRIDE 1
#define IBU_P2_CETUS_CH0_126_DEPTH  1

#define IBU_P2_CETUS_CH0_127_ADDR   0x011c007fL
#define IBU_P2_CETUS_CH0_127_STRIDE 1
#define IBU_P2_CETUS_CH0_127_DEPTH  1

#define IBU_P2_CETUS_CH0_128_ADDR   0x011c0080L
#define IBU_P2_CETUS_CH0_128_STRIDE 1
#define IBU_P2_CETUS_CH0_128_DEPTH  1

#define IBU_P2_CETUS_CH0_129_ADDR   0x011c0081L
#define IBU_P2_CETUS_CH0_129_STRIDE 1
#define IBU_P2_CETUS_CH0_129_DEPTH  1

#define IBU_P2_CETUS_CH0_130_ADDR   0x011c0082L
#define IBU_P2_CETUS_CH0_130_STRIDE 1
#define IBU_P2_CETUS_CH0_130_DEPTH  1

#define IBU_P2_CETUS_CH0_131_ADDR   0x011c0083L
#define IBU_P2_CETUS_CH0_131_STRIDE 1
#define IBU_P2_CETUS_CH0_131_DEPTH  1

#define IBU_P2_CETUS_CH0_132_ADDR   0x011c0084L
#define IBU_P2_CETUS_CH0_132_STRIDE 1
#define IBU_P2_CETUS_CH0_132_DEPTH  1

#define IBU_P2_CETUS_CH0_133_ADDR   0x011c0085L
#define IBU_P2_CETUS_CH0_133_STRIDE 1
#define IBU_P2_CETUS_CH0_133_DEPTH  1

#define IBU_P2_CETUS_CH0_134_ADDR   0x011c0086L
#define IBU_P2_CETUS_CH0_134_STRIDE 1
#define IBU_P2_CETUS_CH0_134_DEPTH  1

#define IBU_P2_CETUS_CH0_135_ADDR   0x011c0087L
#define IBU_P2_CETUS_CH0_135_STRIDE 1
#define IBU_P2_CETUS_CH0_135_DEPTH  1

#define IBU_P2_CETUS_CH0_136_ADDR   0x011c0088L
#define IBU_P2_CETUS_CH0_136_STRIDE 1
#define IBU_P2_CETUS_CH0_136_DEPTH  1

#define IBU_P2_CETUS_CH0_137_ADDR   0x011c0089L
#define IBU_P2_CETUS_CH0_137_STRIDE 1
#define IBU_P2_CETUS_CH0_137_DEPTH  1

#define IBU_P2_CETUS_CH0_138_ADDR   0x011c008aL
#define IBU_P2_CETUS_CH0_138_STRIDE 1
#define IBU_P2_CETUS_CH0_138_DEPTH  1

#define IBU_P2_CETUS_CH0_139_ADDR   0x011c008bL
#define IBU_P2_CETUS_CH0_139_STRIDE 1
#define IBU_P2_CETUS_CH0_139_DEPTH  1

	/* CETUS register */
#define IBU_P2_CETUS_CH1_000_ADDR   0x011c0100L
#define IBU_P2_CETUS_CH1_000_STRIDE 1
#define IBU_P2_CETUS_CH1_000_DEPTH  1

	/* CETUS register */
#define IBU_P2_CETUS_CH1_001_ADDR   0x011c0101L
#define IBU_P2_CETUS_CH1_001_STRIDE 1
#define IBU_P2_CETUS_CH1_001_DEPTH  1

	/* CETUS register */
#define IBU_P2_CETUS_CH1_002_ADDR   0x011c0102L
#define IBU_P2_CETUS_CH1_002_STRIDE 1
#define IBU_P2_CETUS_CH1_002_DEPTH  1

#define IBU_P2_CETUS_CH1_003_ADDR   0x011c0103L
#define IBU_P2_CETUS_CH1_003_STRIDE 1
#define IBU_P2_CETUS_CH1_003_DEPTH  1

#define IBU_P2_CETUS_CH1_004_ADDR   0x011c0104L
#define IBU_P2_CETUS_CH1_004_STRIDE 1
#define IBU_P2_CETUS_CH1_004_DEPTH  1

#define IBU_P2_CETUS_CH1_005_ADDR   0x011c0105L
#define IBU_P2_CETUS_CH1_005_STRIDE 1
#define IBU_P2_CETUS_CH1_005_DEPTH  1

#define IBU_P2_CETUS_CH1_006_ADDR   0x011c0106L
#define IBU_P2_CETUS_CH1_006_STRIDE 1
#define IBU_P2_CETUS_CH1_006_DEPTH  1

#define IBU_P2_CETUS_CH1_007_ADDR   0x011c0107L
#define IBU_P2_CETUS_CH1_007_STRIDE 1
#define IBU_P2_CETUS_CH1_007_DEPTH  1

#define IBU_P2_CETUS_CH1_008_ADDR   0x011c0108L
#define IBU_P2_CETUS_CH1_008_STRIDE 1
#define IBU_P2_CETUS_CH1_008_DEPTH  1

#define IBU_P2_CETUS_CH1_009_ADDR   0x011c0109L
#define IBU_P2_CETUS_CH1_009_STRIDE 1
#define IBU_P2_CETUS_CH1_009_DEPTH  1

#define IBU_P2_CETUS_CH1_010_ADDR   0x011c010aL
#define IBU_P2_CETUS_CH1_010_STRIDE 1
#define IBU_P2_CETUS_CH1_010_DEPTH  1

#define IBU_P2_CETUS_CH1_011_ADDR   0x011c010bL
#define IBU_P2_CETUS_CH1_011_STRIDE 1
#define IBU_P2_CETUS_CH1_011_DEPTH  1

#define IBU_P2_CETUS_CH1_012_ADDR   0x011c010cL
#define IBU_P2_CETUS_CH1_012_STRIDE 1
#define IBU_P2_CETUS_CH1_012_DEPTH  1

#define IBU_P2_CETUS_CH1_013_ADDR   0x011c010dL
#define IBU_P2_CETUS_CH1_013_STRIDE 1
#define IBU_P2_CETUS_CH1_013_DEPTH  1

#define IBU_P2_CETUS_CH1_014_ADDR   0x011c010eL
#define IBU_P2_CETUS_CH1_014_STRIDE 1
#define IBU_P2_CETUS_CH1_014_DEPTH  1

#define IBU_P2_CETUS_CH1_015_ADDR   0x011c010fL
#define IBU_P2_CETUS_CH1_015_STRIDE 1
#define IBU_P2_CETUS_CH1_015_DEPTH  1

#define IBU_P2_CETUS_CH1_016_ADDR   0x011c0110L
#define IBU_P2_CETUS_CH1_016_STRIDE 1
#define IBU_P2_CETUS_CH1_016_DEPTH  1

#define IBU_P2_CETUS_CH1_017_ADDR   0x011c0111L
#define IBU_P2_CETUS_CH1_017_STRIDE 1
#define IBU_P2_CETUS_CH1_017_DEPTH  1

#define IBU_P2_CETUS_CH1_018_ADDR   0x011c0112L
#define IBU_P2_CETUS_CH1_018_STRIDE 1
#define IBU_P2_CETUS_CH1_018_DEPTH  1

#define IBU_P2_CETUS_CH1_019_ADDR   0x011c0113L
#define IBU_P2_CETUS_CH1_019_STRIDE 1
#define IBU_P2_CETUS_CH1_019_DEPTH  1

#define IBU_P2_CETUS_CH1_020_ADDR   0x011c0114L
#define IBU_P2_CETUS_CH1_020_STRIDE 1
#define IBU_P2_CETUS_CH1_020_DEPTH  1

#define IBU_P2_CETUS_CH1_021_ADDR   0x011c0115L
#define IBU_P2_CETUS_CH1_021_STRIDE 1
#define IBU_P2_CETUS_CH1_021_DEPTH  1

#define IBU_P2_CETUS_CH1_022_ADDR   0x011c0116L
#define IBU_P2_CETUS_CH1_022_STRIDE 1
#define IBU_P2_CETUS_CH1_022_DEPTH  1

#define IBU_P2_CETUS_CH1_023_ADDR   0x011c0117L
#define IBU_P2_CETUS_CH1_023_STRIDE 1
#define IBU_P2_CETUS_CH1_023_DEPTH  1

#define IBU_P2_CETUS_CH1_024_ADDR   0x011c0118L
#define IBU_P2_CETUS_CH1_024_STRIDE 1
#define IBU_P2_CETUS_CH1_024_DEPTH  1

#define IBU_P2_CETUS_CH1_025_ADDR   0x011c0119L
#define IBU_P2_CETUS_CH1_025_STRIDE 1
#define IBU_P2_CETUS_CH1_025_DEPTH  1

#define IBU_P2_CETUS_CH1_026_ADDR   0x011c011aL
#define IBU_P2_CETUS_CH1_026_STRIDE 1
#define IBU_P2_CETUS_CH1_026_DEPTH  1

#define IBU_P2_CETUS_CH1_027_ADDR   0x011c011bL
#define IBU_P2_CETUS_CH1_027_STRIDE 1
#define IBU_P2_CETUS_CH1_027_DEPTH  1

#define IBU_P2_CETUS_CH1_028_ADDR   0x011c011cL
#define IBU_P2_CETUS_CH1_028_STRIDE 1
#define IBU_P2_CETUS_CH1_028_DEPTH  1

#define IBU_P2_CETUS_CH1_029_ADDR   0x011c011dL
#define IBU_P2_CETUS_CH1_029_STRIDE 1
#define IBU_P2_CETUS_CH1_029_DEPTH  1

#define IBU_P2_CETUS_CH1_030_ADDR   0x011c011eL
#define IBU_P2_CETUS_CH1_030_STRIDE 1
#define IBU_P2_CETUS_CH1_030_DEPTH  1

#define IBU_P2_CETUS_CH1_031_ADDR   0x011c011fL
#define IBU_P2_CETUS_CH1_031_STRIDE 1
#define IBU_P2_CETUS_CH1_031_DEPTH  1

#define IBU_P2_CETUS_CH1_032_ADDR   0x011c0120L
#define IBU_P2_CETUS_CH1_032_STRIDE 1
#define IBU_P2_CETUS_CH1_032_DEPTH  1

#define IBU_P2_CETUS_CH1_033_ADDR   0x011c0121L
#define IBU_P2_CETUS_CH1_033_STRIDE 1
#define IBU_P2_CETUS_CH1_033_DEPTH  1

#define IBU_P2_CETUS_CH1_034_ADDR   0x011c0122L
#define IBU_P2_CETUS_CH1_034_STRIDE 1
#define IBU_P2_CETUS_CH1_034_DEPTH  1

#define IBU_P2_CETUS_CH1_035_ADDR   0x011c0123L
#define IBU_P2_CETUS_CH1_035_STRIDE 1
#define IBU_P2_CETUS_CH1_035_DEPTH  1

#define IBU_P2_CETUS_CH1_036_ADDR   0x011c0124L
#define IBU_P2_CETUS_CH1_036_STRIDE 1
#define IBU_P2_CETUS_CH1_036_DEPTH  1

#define IBU_P2_CETUS_CH1_037_ADDR   0x011c0125L
#define IBU_P2_CETUS_CH1_037_STRIDE 1
#define IBU_P2_CETUS_CH1_037_DEPTH  1

#define IBU_P2_CETUS_CH1_038_ADDR   0x011c0126L
#define IBU_P2_CETUS_CH1_038_STRIDE 1
#define IBU_P2_CETUS_CH1_038_DEPTH  1

#define IBU_P2_CETUS_CH1_039_ADDR   0x011c0127L
#define IBU_P2_CETUS_CH1_039_STRIDE 1
#define IBU_P2_CETUS_CH1_039_DEPTH  1

#define IBU_P2_CETUS_CH1_040_ADDR   0x011c0128L
#define IBU_P2_CETUS_CH1_040_STRIDE 1
#define IBU_P2_CETUS_CH1_040_DEPTH  1

#define IBU_P2_CETUS_CH1_041_ADDR   0x011c0129L
#define IBU_P2_CETUS_CH1_041_STRIDE 1
#define IBU_P2_CETUS_CH1_041_DEPTH  1

#define IBU_P2_CETUS_CH1_042_ADDR   0x011c012aL
#define IBU_P2_CETUS_CH1_042_STRIDE 1
#define IBU_P2_CETUS_CH1_042_DEPTH  1

#define IBU_P2_CETUS_CH1_043_ADDR   0x011c012bL
#define IBU_P2_CETUS_CH1_043_STRIDE 1
#define IBU_P2_CETUS_CH1_043_DEPTH  1

#define IBU_P2_CETUS_CH1_044_ADDR   0x011c012cL
#define IBU_P2_CETUS_CH1_044_STRIDE 1
#define IBU_P2_CETUS_CH1_044_DEPTH  1

#define IBU_P2_CETUS_CH1_045_ADDR   0x011c012dL
#define IBU_P2_CETUS_CH1_045_STRIDE 1
#define IBU_P2_CETUS_CH1_045_DEPTH  1

#define IBU_P2_CETUS_CH1_046_ADDR   0x011c012eL
#define IBU_P2_CETUS_CH1_046_STRIDE 1
#define IBU_P2_CETUS_CH1_046_DEPTH  1

#define IBU_P2_CETUS_CH1_047_ADDR   0x011c012fL
#define IBU_P2_CETUS_CH1_047_STRIDE 1
#define IBU_P2_CETUS_CH1_047_DEPTH  1

#define IBU_P2_CETUS_CH1_048_ADDR   0x011c0130L
#define IBU_P2_CETUS_CH1_048_STRIDE 1
#define IBU_P2_CETUS_CH1_048_DEPTH  1

#define IBU_P2_CETUS_CH1_049_ADDR   0x011c0131L
#define IBU_P2_CETUS_CH1_049_STRIDE 1
#define IBU_P2_CETUS_CH1_049_DEPTH  1

#define IBU_P2_CETUS_CH1_050_ADDR   0x011c0132L
#define IBU_P2_CETUS_CH1_050_STRIDE 1
#define IBU_P2_CETUS_CH1_050_DEPTH  1

#define IBU_P2_CETUS_CH1_051_ADDR   0x011c0133L
#define IBU_P2_CETUS_CH1_051_STRIDE 1
#define IBU_P2_CETUS_CH1_051_DEPTH  1

#define IBU_P2_CETUS_CH1_052_ADDR   0x011c0134L
#define IBU_P2_CETUS_CH1_052_STRIDE 1
#define IBU_P2_CETUS_CH1_052_DEPTH  1

#define IBU_P2_CETUS_CH1_053_ADDR   0x011c0135L
#define IBU_P2_CETUS_CH1_053_STRIDE 1
#define IBU_P2_CETUS_CH1_053_DEPTH  1

#define IBU_P2_CETUS_CH1_054_ADDR   0x011c0136L
#define IBU_P2_CETUS_CH1_054_STRIDE 1
#define IBU_P2_CETUS_CH1_054_DEPTH  1

#define IBU_P2_CETUS_CH1_055_ADDR   0x011c0137L
#define IBU_P2_CETUS_CH1_055_STRIDE 1
#define IBU_P2_CETUS_CH1_055_DEPTH  1

#define IBU_P2_CETUS_CH1_056_ADDR   0x011c0138L
#define IBU_P2_CETUS_CH1_056_STRIDE 1
#define IBU_P2_CETUS_CH1_056_DEPTH  1

#define IBU_P2_CETUS_CH1_057_ADDR   0x011c0139L
#define IBU_P2_CETUS_CH1_057_STRIDE 1
#define IBU_P2_CETUS_CH1_057_DEPTH  1

#define IBU_P2_CETUS_CH1_058_ADDR   0x011c013aL
#define IBU_P2_CETUS_CH1_058_STRIDE 1
#define IBU_P2_CETUS_CH1_058_DEPTH  1

#define IBU_P2_CETUS_CH1_059_ADDR   0x011c013bL
#define IBU_P2_CETUS_CH1_059_STRIDE 1
#define IBU_P2_CETUS_CH1_059_DEPTH  1

#define IBU_P2_CETUS_CH1_060_ADDR   0x011c013cL
#define IBU_P2_CETUS_CH1_060_STRIDE 1
#define IBU_P2_CETUS_CH1_060_DEPTH  1

#define IBU_P2_CETUS_CH1_061_ADDR   0x011c013dL
#define IBU_P2_CETUS_CH1_061_STRIDE 1
#define IBU_P2_CETUS_CH1_061_DEPTH  1

#define IBU_P2_CETUS_CH1_062_ADDR   0x011c013eL
#define IBU_P2_CETUS_CH1_062_STRIDE 1
#define IBU_P2_CETUS_CH1_062_DEPTH  1

#define IBU_P2_CETUS_CH1_063_ADDR   0x011c013fL
#define IBU_P2_CETUS_CH1_063_STRIDE 1
#define IBU_P2_CETUS_CH1_063_DEPTH  1

#define IBU_P2_CETUS_CH1_064_ADDR   0x011c0140L
#define IBU_P2_CETUS_CH1_064_STRIDE 1
#define IBU_P2_CETUS_CH1_064_DEPTH  1

#define IBU_P2_CETUS_CH1_065_ADDR   0x011c0141L
#define IBU_P2_CETUS_CH1_065_STRIDE 1
#define IBU_P2_CETUS_CH1_065_DEPTH  1

#define IBU_P2_CETUS_CH1_066_ADDR   0x011c0142L
#define IBU_P2_CETUS_CH1_066_STRIDE 1
#define IBU_P2_CETUS_CH1_066_DEPTH  1

#define IBU_P2_CETUS_CH1_067_ADDR   0x011c0143L
#define IBU_P2_CETUS_CH1_067_STRIDE 1
#define IBU_P2_CETUS_CH1_067_DEPTH  1

#define IBU_P2_CETUS_CH1_068_ADDR   0x011c0144L
#define IBU_P2_CETUS_CH1_068_STRIDE 1
#define IBU_P2_CETUS_CH1_068_DEPTH  1

#define IBU_P2_CETUS_CH1_069_ADDR   0x011c0145L
#define IBU_P2_CETUS_CH1_069_STRIDE 1
#define IBU_P2_CETUS_CH1_069_DEPTH  1

#define IBU_P2_CETUS_CH1_070_ADDR   0x011c0146L
#define IBU_P2_CETUS_CH1_070_STRIDE 1
#define IBU_P2_CETUS_CH1_070_DEPTH  1

#define IBU_P2_CETUS_CH1_071_ADDR   0x011c0147L
#define IBU_P2_CETUS_CH1_071_STRIDE 1
#define IBU_P2_CETUS_CH1_071_DEPTH  1

#define IBU_P2_CETUS_CH1_072_ADDR   0x011c0148L
#define IBU_P2_CETUS_CH1_072_STRIDE 1
#define IBU_P2_CETUS_CH1_072_DEPTH  1

#define IBU_P2_CETUS_CH1_073_ADDR   0x011c0149L
#define IBU_P2_CETUS_CH1_073_STRIDE 1
#define IBU_P2_CETUS_CH1_073_DEPTH  1

#define IBU_P2_CETUS_CH1_074_ADDR   0x011c014aL
#define IBU_P2_CETUS_CH1_074_STRIDE 1
#define IBU_P2_CETUS_CH1_074_DEPTH  1

#define IBU_P2_CETUS_CH1_075_ADDR   0x011c014bL
#define IBU_P2_CETUS_CH1_075_STRIDE 1
#define IBU_P2_CETUS_CH1_075_DEPTH  1

#define IBU_P2_CETUS_CH1_076_ADDR   0x011c014cL
#define IBU_P2_CETUS_CH1_076_STRIDE 1
#define IBU_P2_CETUS_CH1_076_DEPTH  1

#define IBU_P2_CETUS_CH1_077_ADDR   0x011c014dL
#define IBU_P2_CETUS_CH1_077_STRIDE 1
#define IBU_P2_CETUS_CH1_077_DEPTH  1

#define IBU_P2_CETUS_CH1_078_ADDR   0x011c014eL
#define IBU_P2_CETUS_CH1_078_STRIDE 1
#define IBU_P2_CETUS_CH1_078_DEPTH  1

#define IBU_P2_CETUS_CH1_079_ADDR   0x011c014fL
#define IBU_P2_CETUS_CH1_079_STRIDE 1
#define IBU_P2_CETUS_CH1_079_DEPTH  1

#define IBU_P2_CETUS_CH1_080_ADDR   0x011c0150L
#define IBU_P2_CETUS_CH1_080_STRIDE 1
#define IBU_P2_CETUS_CH1_080_DEPTH  1

#define IBU_P2_CETUS_CH1_081_ADDR   0x011c0151L
#define IBU_P2_CETUS_CH1_081_STRIDE 1
#define IBU_P2_CETUS_CH1_081_DEPTH  1

#define IBU_P2_CETUS_CH1_082_ADDR   0x011c0152L
#define IBU_P2_CETUS_CH1_082_STRIDE 1
#define IBU_P2_CETUS_CH1_082_DEPTH  1

#define IBU_P2_CETUS_CH1_083_ADDR   0x011c0153L
#define IBU_P2_CETUS_CH1_083_STRIDE 1
#define IBU_P2_CETUS_CH1_083_DEPTH  1

#define IBU_P2_CETUS_CH1_084_ADDR   0x011c0154L
#define IBU_P2_CETUS_CH1_084_STRIDE 1
#define IBU_P2_CETUS_CH1_084_DEPTH  1

#define IBU_P2_CETUS_CH1_085_ADDR   0x011c0155L
#define IBU_P2_CETUS_CH1_085_STRIDE 1
#define IBU_P2_CETUS_CH1_085_DEPTH  1

#define IBU_P2_CETUS_CH1_086_ADDR   0x011c0156L
#define IBU_P2_CETUS_CH1_086_STRIDE 1
#define IBU_P2_CETUS_CH1_086_DEPTH  1

#define IBU_P2_CETUS_CH1_087_ADDR   0x011c0157L
#define IBU_P2_CETUS_CH1_087_STRIDE 1
#define IBU_P2_CETUS_CH1_087_DEPTH  1

#define IBU_P2_CETUS_CH1_088_ADDR   0x011c0158L
#define IBU_P2_CETUS_CH1_088_STRIDE 1
#define IBU_P2_CETUS_CH1_088_DEPTH  1

#define IBU_P2_CETUS_CH1_089_ADDR   0x011c0159L
#define IBU_P2_CETUS_CH1_089_STRIDE 1
#define IBU_P2_CETUS_CH1_089_DEPTH  1

#define IBU_P2_CETUS_CH1_090_ADDR   0x011c015aL
#define IBU_P2_CETUS_CH1_090_STRIDE 1
#define IBU_P2_CETUS_CH1_090_DEPTH  1

#define IBU_P2_CETUS_CH1_091_ADDR   0x011c015bL
#define IBU_P2_CETUS_CH1_091_STRIDE 1
#define IBU_P2_CETUS_CH1_091_DEPTH  1

#define IBU_P2_CETUS_CH1_092_ADDR   0x011c015cL
#define IBU_P2_CETUS_CH1_092_STRIDE 1
#define IBU_P2_CETUS_CH1_092_DEPTH  1

#define IBU_P2_CETUS_CH1_093_ADDR   0x011c015dL
#define IBU_P2_CETUS_CH1_093_STRIDE 1
#define IBU_P2_CETUS_CH1_093_DEPTH  1

#define IBU_P2_CETUS_CH1_094_ADDR   0x011c015eL
#define IBU_P2_CETUS_CH1_094_STRIDE 1
#define IBU_P2_CETUS_CH1_094_DEPTH  1

#define IBU_P2_CETUS_CH1_095_ADDR   0x011c015fL
#define IBU_P2_CETUS_CH1_095_STRIDE 1
#define IBU_P2_CETUS_CH1_095_DEPTH  1

#define IBU_P2_CETUS_CH1_096_ADDR   0x011c0160L
#define IBU_P2_CETUS_CH1_096_STRIDE 1
#define IBU_P2_CETUS_CH1_096_DEPTH  1

#define IBU_P2_CETUS_CH1_097_ADDR   0x011c0161L
#define IBU_P2_CETUS_CH1_097_STRIDE 1
#define IBU_P2_CETUS_CH1_097_DEPTH  1

#define IBU_P2_CETUS_CH1_098_ADDR   0x011c0162L
#define IBU_P2_CETUS_CH1_098_STRIDE 1
#define IBU_P2_CETUS_CH1_098_DEPTH  1

#define IBU_P2_CETUS_CH1_099_ADDR   0x011c0163L
#define IBU_P2_CETUS_CH1_099_STRIDE 1
#define IBU_P2_CETUS_CH1_099_DEPTH  1

#define IBU_P2_CETUS_CH1_100_ADDR   0x011c0164L
#define IBU_P2_CETUS_CH1_100_STRIDE 1
#define IBU_P2_CETUS_CH1_100_DEPTH  1

#define IBU_P2_CETUS_CH1_101_ADDR   0x011c0165L
#define IBU_P2_CETUS_CH1_101_STRIDE 1
#define IBU_P2_CETUS_CH1_101_DEPTH  1

#define IBU_P2_CETUS_CH1_102_ADDR   0x011c0166L
#define IBU_P2_CETUS_CH1_102_STRIDE 1
#define IBU_P2_CETUS_CH1_102_DEPTH  1

#define IBU_P2_CETUS_CH1_103_ADDR   0x011c0167L
#define IBU_P2_CETUS_CH1_103_STRIDE 1
#define IBU_P2_CETUS_CH1_103_DEPTH  1

#define IBU_P2_CETUS_CH1_104_ADDR   0x011c0168L
#define IBU_P2_CETUS_CH1_104_STRIDE 1
#define IBU_P2_CETUS_CH1_104_DEPTH  1

#define IBU_P2_CETUS_CH1_105_ADDR   0x011c0169L
#define IBU_P2_CETUS_CH1_105_STRIDE 1
#define IBU_P2_CETUS_CH1_105_DEPTH  1

#define IBU_P2_CETUS_CH1_106_ADDR   0x011c016aL
#define IBU_P2_CETUS_CH1_106_STRIDE 1
#define IBU_P2_CETUS_CH1_106_DEPTH  1

#define IBU_P2_CETUS_CH1_107_ADDR   0x011c016bL
#define IBU_P2_CETUS_CH1_107_STRIDE 1
#define IBU_P2_CETUS_CH1_107_DEPTH  1

#define IBU_P2_CETUS_CH1_108_ADDR   0x011c016cL
#define IBU_P2_CETUS_CH1_108_STRIDE 1
#define IBU_P2_CETUS_CH1_108_DEPTH  1

#define IBU_P2_CETUS_CH1_109_ADDR   0x011c016dL
#define IBU_P2_CETUS_CH1_109_STRIDE 1
#define IBU_P2_CETUS_CH1_109_DEPTH  1

#define IBU_P2_CETUS_CH1_110_ADDR   0x011c016eL
#define IBU_P2_CETUS_CH1_110_STRIDE 1
#define IBU_P2_CETUS_CH1_110_DEPTH  1

#define IBU_P2_CETUS_CH1_111_ADDR   0x011c016fL
#define IBU_P2_CETUS_CH1_111_STRIDE 1
#define IBU_P2_CETUS_CH1_111_DEPTH  1

#define IBU_P2_CETUS_CH1_112_ADDR   0x011c0170L
#define IBU_P2_CETUS_CH1_112_STRIDE 1
#define IBU_P2_CETUS_CH1_112_DEPTH  1

#define IBU_P2_CETUS_CH1_113_ADDR   0x011c0171L
#define IBU_P2_CETUS_CH1_113_STRIDE 1
#define IBU_P2_CETUS_CH1_113_DEPTH  1

#define IBU_P2_CETUS_CH1_114_ADDR   0x011c0172L
#define IBU_P2_CETUS_CH1_114_STRIDE 1
#define IBU_P2_CETUS_CH1_114_DEPTH  1

#define IBU_P2_CETUS_CH1_115_ADDR   0x011c0173L
#define IBU_P2_CETUS_CH1_115_STRIDE 1
#define IBU_P2_CETUS_CH1_115_DEPTH  1

#define IBU_P2_CETUS_CH1_116_ADDR   0x011c0174L
#define IBU_P2_CETUS_CH1_116_STRIDE 1
#define IBU_P2_CETUS_CH1_116_DEPTH  1

#define IBU_P2_CETUS_CH1_117_ADDR   0x011c0175L
#define IBU_P2_CETUS_CH1_117_STRIDE 1
#define IBU_P2_CETUS_CH1_117_DEPTH  1

#define IBU_P2_CETUS_CH1_118_ADDR   0x011c0176L
#define IBU_P2_CETUS_CH1_118_STRIDE 1
#define IBU_P2_CETUS_CH1_118_DEPTH  1

#define IBU_P2_CETUS_CH1_119_ADDR   0x011c0177L
#define IBU_P2_CETUS_CH1_119_STRIDE 1
#define IBU_P2_CETUS_CH1_119_DEPTH  1

#define IBU_P2_CETUS_CH1_120_ADDR   0x011c0178L
#define IBU_P2_CETUS_CH1_120_STRIDE 1
#define IBU_P2_CETUS_CH1_120_DEPTH  1

#define IBU_P2_CETUS_CH1_121_ADDR   0x011c0179L
#define IBU_P2_CETUS_CH1_121_STRIDE 1
#define IBU_P2_CETUS_CH1_121_DEPTH  1

#define IBU_P2_CETUS_CH1_122_ADDR   0x011c017aL
#define IBU_P2_CETUS_CH1_122_STRIDE 1
#define IBU_P2_CETUS_CH1_122_DEPTH  1

#define IBU_P2_CETUS_CH1_123_ADDR   0x011c017bL
#define IBU_P2_CETUS_CH1_123_STRIDE 1
#define IBU_P2_CETUS_CH1_123_DEPTH  1

#define IBU_P2_CETUS_CH1_124_ADDR   0x011c017cL
#define IBU_P2_CETUS_CH1_124_STRIDE 1
#define IBU_P2_CETUS_CH1_124_DEPTH  1

#define IBU_P2_CETUS_CH1_125_ADDR   0x011c017dL
#define IBU_P2_CETUS_CH1_125_STRIDE 1
#define IBU_P2_CETUS_CH1_125_DEPTH  1

#define IBU_P2_CETUS_CH1_126_ADDR   0x011c017eL
#define IBU_P2_CETUS_CH1_126_STRIDE 1
#define IBU_P2_CETUS_CH1_126_DEPTH  1

#define IBU_P2_CETUS_CH1_127_ADDR   0x011c017fL
#define IBU_P2_CETUS_CH1_127_STRIDE 1
#define IBU_P2_CETUS_CH1_127_DEPTH  1

#define IBU_P2_CETUS_CH1_128_ADDR   0x011c0180L
#define IBU_P2_CETUS_CH1_128_STRIDE 1
#define IBU_P2_CETUS_CH1_128_DEPTH  1

#define IBU_P2_CETUS_CH1_129_ADDR   0x011c0181L
#define IBU_P2_CETUS_CH1_129_STRIDE 1
#define IBU_P2_CETUS_CH1_129_DEPTH  1

#define IBU_P2_CETUS_CH1_130_ADDR   0x011c0182L
#define IBU_P2_CETUS_CH1_130_STRIDE 1
#define IBU_P2_CETUS_CH1_130_DEPTH  1

#define IBU_P2_CETUS_CH1_131_ADDR   0x011c0183L
#define IBU_P2_CETUS_CH1_131_STRIDE 1
#define IBU_P2_CETUS_CH1_131_DEPTH  1

#define IBU_P2_CETUS_CH1_132_ADDR   0x011c0184L
#define IBU_P2_CETUS_CH1_132_STRIDE 1
#define IBU_P2_CETUS_CH1_132_DEPTH  1

#define IBU_P2_CETUS_CH1_133_ADDR   0x011c0185L
#define IBU_P2_CETUS_CH1_133_STRIDE 1
#define IBU_P2_CETUS_CH1_133_DEPTH  1

#define IBU_P2_CETUS_CH1_134_ADDR   0x011c0186L
#define IBU_P2_CETUS_CH1_134_STRIDE 1
#define IBU_P2_CETUS_CH1_134_DEPTH  1

#define IBU_P2_CETUS_CH1_135_ADDR   0x011c0187L
#define IBU_P2_CETUS_CH1_135_STRIDE 1
#define IBU_P2_CETUS_CH1_135_DEPTH  1

#define IBU_P2_CETUS_CH1_136_ADDR   0x011c0188L
#define IBU_P2_CETUS_CH1_136_STRIDE 1
#define IBU_P2_CETUS_CH1_136_DEPTH  1

#define IBU_P2_CETUS_CH1_137_ADDR   0x011c0189L
#define IBU_P2_CETUS_CH1_137_STRIDE 1
#define IBU_P2_CETUS_CH1_137_DEPTH  1

#define IBU_P2_CETUS_CH1_138_ADDR   0x011c018aL
#define IBU_P2_CETUS_CH1_138_STRIDE 1
#define IBU_P2_CETUS_CH1_138_DEPTH  1

#define IBU_P2_CETUS_CH1_139_ADDR   0x011c018bL
#define IBU_P2_CETUS_CH1_139_STRIDE 1
#define IBU_P2_CETUS_CH1_139_DEPTH  1

#define IBU_P2_CETUS_PLLA_CONTROL0_ADDR   0x011c0200L
#define IBU_P2_CETUS_PLLA_CONTROL0_STRIDE 1
#define IBU_P2_CETUS_PLLA_CONTROL0_DEPTH  1

#define IBU_P2_CETUS_PLLA_CONTROL1_ADDR   0x011c0201L
#define IBU_P2_CETUS_PLLA_CONTROL1_STRIDE 1
#define IBU_P2_CETUS_PLLA_CONTROL1_DEPTH  1

#define IBU_P2_CETUS_PLLA_CONTROL2_ADDR   0x011c0202L
#define IBU_P2_CETUS_PLLA_CONTROL2_STRIDE 1
#define IBU_P2_CETUS_PLLA_CONTROL2_DEPTH  1

#define IBU_P2_CETUS_PLLA_EXTFB_CNTR_ADDR   0x011c0203L
#define IBU_P2_CETUS_PLLA_EXTFB_CNTR_STRIDE 1
#define IBU_P2_CETUS_PLLA_EXTFB_CNTR_DEPTH  1

#define IBU_P2_CETUS_PLLA_FBCNT_ATO_ADDR   0x011c0204L
#define IBU_P2_CETUS_PLLA_FBCNT_ATO_STRIDE 1
#define IBU_P2_CETUS_PLLA_FBCNT_ATO_DEPTH  1

#define IBU_P2_CETUS_PLLA_SPARE_USRCNTR_ADDR   0x011c0205L
#define IBU_P2_CETUS_PLLA_SPARE_USRCNTR_STRIDE 1
#define IBU_P2_CETUS_PLLA_SPARE_USRCNTR_DEPTH  1

#define IBU_P2_CETUS_PLLA_DIV_EN_ADDR   0x011c0206L
#define IBU_P2_CETUS_PLLA_DIV_EN_STRIDE 1
#define IBU_P2_CETUS_PLLA_DIV_EN_DEPTH  1

#define IBU_P2_CETUS_PLLA_VCO_WAIT_CNT_ADDR   0x011c0207L
#define IBU_P2_CETUS_PLLA_VCO_WAIT_CNT_STRIDE 1
#define IBU_P2_CETUS_PLLA_VCO_WAIT_CNT_DEPTH  1

#define IBU_P2_CETUS_PLLA_STATUS0_ADDR   0x011c0208L
#define IBU_P2_CETUS_PLLA_STATUS0_STRIDE 1
#define IBU_P2_CETUS_PLLA_STATUS0_DEPTH  1

#define IBU_P2_CETUS_PLLA_STATUS1_ADDR   0x011c0209L
#define IBU_P2_CETUS_PLLA_STATUS1_STRIDE 1
#define IBU_P2_CETUS_PLLA_STATUS1_DEPTH  1

#define IBU_P2_CETUS_PLLA_010_ADDR   0x011c020aL
#define IBU_P2_CETUS_PLLA_010_STRIDE 1
#define IBU_P2_CETUS_PLLA_010_DEPTH  1

#define IBU_P2_CETUS_PLLA_011_ADDR   0x011c020bL
#define IBU_P2_CETUS_PLLA_011_STRIDE 1
#define IBU_P2_CETUS_PLLA_011_DEPTH  1

#define IBU_P2_CETUS_PLLA_012_ADDR   0x011c020cL
#define IBU_P2_CETUS_PLLA_012_STRIDE 1
#define IBU_P2_CETUS_PLLA_012_DEPTH  1

#define IBU_P2_CETUS_PLLA_013_ADDR   0x011c020dL
#define IBU_P2_CETUS_PLLA_013_STRIDE 1
#define IBU_P2_CETUS_PLLA_013_DEPTH  1

#define IBU_P2_CETUS_PLLA_014_ADDR   0x011c020eL
#define IBU_P2_CETUS_PLLA_014_STRIDE 1
#define IBU_P2_CETUS_PLLA_014_DEPTH  1

#define IBU_P2_CETUS_PLLA_015_ADDR   0x011c020fL
#define IBU_P2_CETUS_PLLA_015_STRIDE 1
#define IBU_P2_CETUS_PLLA_015_DEPTH  1

#define IBU_P2_CETUS_PLLA_016_ADDR   0x011c0210L
#define IBU_P2_CETUS_PLLA_016_STRIDE 1
#define IBU_P2_CETUS_PLLA_016_DEPTH  1

#define IBU_P2_CETUS_PLLA_017_ADDR   0x011c0211L
#define IBU_P2_CETUS_PLLA_017_STRIDE 1
#define IBU_P2_CETUS_PLLA_017_DEPTH  1

#define IBU_P2_CETUS_PLLA_018_ADDR   0x011c0212L
#define IBU_P2_CETUS_PLLA_018_STRIDE 1
#define IBU_P2_CETUS_PLLA_018_DEPTH  1

#define IBU_P2_CETUS_PLLA_019_ADDR   0x011c0213L
#define IBU_P2_CETUS_PLLA_019_STRIDE 1
#define IBU_P2_CETUS_PLLA_019_DEPTH  1

#define IBU_P2_CETUS_PLLA_020_ADDR   0x011c0214L
#define IBU_P2_CETUS_PLLA_020_STRIDE 1
#define IBU_P2_CETUS_PLLA_020_DEPTH  1

#define IBU_P2_CETUS_PLLA_021_ADDR   0x011c0215L
#define IBU_P2_CETUS_PLLA_021_STRIDE 1
#define IBU_P2_CETUS_PLLA_021_DEPTH  1

#define IBU_P2_CETUS_PLLA_022_ADDR   0x011c0216L
#define IBU_P2_CETUS_PLLA_022_STRIDE 1
#define IBU_P2_CETUS_PLLA_022_DEPTH  1

#define IBU_P2_CETUS_PLLA_023_ADDR   0x011c0217L
#define IBU_P2_CETUS_PLLA_023_STRIDE 1
#define IBU_P2_CETUS_PLLA_023_DEPTH  1

#define IBU_P2_CETUS_PLLA_024_ADDR   0x011c0218L
#define IBU_P2_CETUS_PLLA_024_STRIDE 1
#define IBU_P2_CETUS_PLLA_024_DEPTH  1

	/* CETUS register */
#define IBU_P2_CETUS_CH2_000_ADDR   0x011c0300L
#define IBU_P2_CETUS_CH2_000_STRIDE 1
#define IBU_P2_CETUS_CH2_000_DEPTH  1

	/* CETUS register */
#define IBU_P2_CETUS_CH2_001_ADDR   0x011c0301L
#define IBU_P2_CETUS_CH2_001_STRIDE 1
#define IBU_P2_CETUS_CH2_001_DEPTH  1

	/* CETUS register */
#define IBU_P2_CETUS_CH2_002_ADDR   0x011c0302L
#define IBU_P2_CETUS_CH2_002_STRIDE 1
#define IBU_P2_CETUS_CH2_002_DEPTH  1

#define IBU_P2_CETUS_CH2_003_ADDR   0x011c0303L
#define IBU_P2_CETUS_CH2_003_STRIDE 1
#define IBU_P2_CETUS_CH2_003_DEPTH  1

#define IBU_P2_CETUS_CH2_004_ADDR   0x011c0304L
#define IBU_P2_CETUS_CH2_004_STRIDE 1
#define IBU_P2_CETUS_CH2_004_DEPTH  1

#define IBU_P2_CETUS_CH2_005_ADDR   0x011c0305L
#define IBU_P2_CETUS_CH2_005_STRIDE 1
#define IBU_P2_CETUS_CH2_005_DEPTH  1

#define IBU_P2_CETUS_CH2_006_ADDR   0x011c0306L
#define IBU_P2_CETUS_CH2_006_STRIDE 1
#define IBU_P2_CETUS_CH2_006_DEPTH  1

#define IBU_P2_CETUS_CH2_007_ADDR   0x011c0307L
#define IBU_P2_CETUS_CH2_007_STRIDE 1
#define IBU_P2_CETUS_CH2_007_DEPTH  1

#define IBU_P2_CETUS_CH2_008_ADDR   0x011c0308L
#define IBU_P2_CETUS_CH2_008_STRIDE 1
#define IBU_P2_CETUS_CH2_008_DEPTH  1

#define IBU_P2_CETUS_CH2_009_ADDR   0x011c0309L
#define IBU_P2_CETUS_CH2_009_STRIDE 1
#define IBU_P2_CETUS_CH2_009_DEPTH  1

#define IBU_P2_CETUS_CH2_010_ADDR   0x011c030aL
#define IBU_P2_CETUS_CH2_010_STRIDE 1
#define IBU_P2_CETUS_CH2_010_DEPTH  1

#define IBU_P2_CETUS_CH2_011_ADDR   0x011c030bL
#define IBU_P2_CETUS_CH2_011_STRIDE 1
#define IBU_P2_CETUS_CH2_011_DEPTH  1

#define IBU_P2_CETUS_CH2_012_ADDR   0x011c030cL
#define IBU_P2_CETUS_CH2_012_STRIDE 1
#define IBU_P2_CETUS_CH2_012_DEPTH  1

#define IBU_P2_CETUS_CH2_013_ADDR   0x011c030dL
#define IBU_P2_CETUS_CH2_013_STRIDE 1
#define IBU_P2_CETUS_CH2_013_DEPTH  1

#define IBU_P2_CETUS_CH2_014_ADDR   0x011c030eL
#define IBU_P2_CETUS_CH2_014_STRIDE 1
#define IBU_P2_CETUS_CH2_014_DEPTH  1

#define IBU_P2_CETUS_CH2_015_ADDR   0x011c030fL
#define IBU_P2_CETUS_CH2_015_STRIDE 1
#define IBU_P2_CETUS_CH2_015_DEPTH  1

#define IBU_P2_CETUS_CH2_016_ADDR   0x011c0310L
#define IBU_P2_CETUS_CH2_016_STRIDE 1
#define IBU_P2_CETUS_CH2_016_DEPTH  1

#define IBU_P2_CETUS_CH2_017_ADDR   0x011c0311L
#define IBU_P2_CETUS_CH2_017_STRIDE 1
#define IBU_P2_CETUS_CH2_017_DEPTH  1

#define IBU_P2_CETUS_CH2_018_ADDR   0x011c0312L
#define IBU_P2_CETUS_CH2_018_STRIDE 1
#define IBU_P2_CETUS_CH2_018_DEPTH  1

#define IBU_P2_CETUS_CH2_019_ADDR   0x011c0313L
#define IBU_P2_CETUS_CH2_019_STRIDE 1
#define IBU_P2_CETUS_CH2_019_DEPTH  1

#define IBU_P2_CETUS_CH2_020_ADDR   0x011c0314L
#define IBU_P2_CETUS_CH2_020_STRIDE 1
#define IBU_P2_CETUS_CH2_020_DEPTH  1

#define IBU_P2_CETUS_CH2_021_ADDR   0x011c0315L
#define IBU_P2_CETUS_CH2_021_STRIDE 1
#define IBU_P2_CETUS_CH2_021_DEPTH  1

#define IBU_P2_CETUS_CH2_022_ADDR   0x011c0316L
#define IBU_P2_CETUS_CH2_022_STRIDE 1
#define IBU_P2_CETUS_CH2_022_DEPTH  1

#define IBU_P2_CETUS_CH2_023_ADDR   0x011c0317L
#define IBU_P2_CETUS_CH2_023_STRIDE 1
#define IBU_P2_CETUS_CH2_023_DEPTH  1

#define IBU_P2_CETUS_CH2_024_ADDR   0x011c0318L
#define IBU_P2_CETUS_CH2_024_STRIDE 1
#define IBU_P2_CETUS_CH2_024_DEPTH  1

#define IBU_P2_CETUS_CH2_025_ADDR   0x011c0319L
#define IBU_P2_CETUS_CH2_025_STRIDE 1
#define IBU_P2_CETUS_CH2_025_DEPTH  1

#define IBU_P2_CETUS_CH2_026_ADDR   0x011c031aL
#define IBU_P2_CETUS_CH2_026_STRIDE 1
#define IBU_P2_CETUS_CH2_026_DEPTH  1

#define IBU_P2_CETUS_CH2_027_ADDR   0x011c031bL
#define IBU_P2_CETUS_CH2_027_STRIDE 1
#define IBU_P2_CETUS_CH2_027_DEPTH  1

#define IBU_P2_CETUS_CH2_028_ADDR   0x011c031cL
#define IBU_P2_CETUS_CH2_028_STRIDE 1
#define IBU_P2_CETUS_CH2_028_DEPTH  1

#define IBU_P2_CETUS_CH2_029_ADDR   0x011c031dL
#define IBU_P2_CETUS_CH2_029_STRIDE 1
#define IBU_P2_CETUS_CH2_029_DEPTH  1

#define IBU_P2_CETUS_CH2_030_ADDR   0x011c031eL
#define IBU_P2_CETUS_CH2_030_STRIDE 1
#define IBU_P2_CETUS_CH2_030_DEPTH  1

#define IBU_P2_CETUS_CH2_031_ADDR   0x011c031fL
#define IBU_P2_CETUS_CH2_031_STRIDE 1
#define IBU_P2_CETUS_CH2_031_DEPTH  1

#define IBU_P2_CETUS_CH2_032_ADDR   0x011c0320L
#define IBU_P2_CETUS_CH2_032_STRIDE 1
#define IBU_P2_CETUS_CH2_032_DEPTH  1

#define IBU_P2_CETUS_CH2_033_ADDR   0x011c0321L
#define IBU_P2_CETUS_CH2_033_STRIDE 1
#define IBU_P2_CETUS_CH2_033_DEPTH  1

#define IBU_P2_CETUS_CH2_034_ADDR   0x011c0322L
#define IBU_P2_CETUS_CH2_034_STRIDE 1
#define IBU_P2_CETUS_CH2_034_DEPTH  1

#define IBU_P2_CETUS_CH2_035_ADDR   0x011c0323L
#define IBU_P2_CETUS_CH2_035_STRIDE 1
#define IBU_P2_CETUS_CH2_035_DEPTH  1

#define IBU_P2_CETUS_CH2_036_ADDR   0x011c0324L
#define IBU_P2_CETUS_CH2_036_STRIDE 1
#define IBU_P2_CETUS_CH2_036_DEPTH  1

#define IBU_P2_CETUS_CH2_037_ADDR   0x011c0325L
#define IBU_P2_CETUS_CH2_037_STRIDE 1
#define IBU_P2_CETUS_CH2_037_DEPTH  1

#define IBU_P2_CETUS_CH2_038_ADDR   0x011c0326L
#define IBU_P2_CETUS_CH2_038_STRIDE 1
#define IBU_P2_CETUS_CH2_038_DEPTH  1

#define IBU_P2_CETUS_CH2_039_ADDR   0x011c0327L
#define IBU_P2_CETUS_CH2_039_STRIDE 1
#define IBU_P2_CETUS_CH2_039_DEPTH  1

#define IBU_P2_CETUS_CH2_040_ADDR   0x011c0328L
#define IBU_P2_CETUS_CH2_040_STRIDE 1
#define IBU_P2_CETUS_CH2_040_DEPTH  1

#define IBU_P2_CETUS_CH2_041_ADDR   0x011c0329L
#define IBU_P2_CETUS_CH2_041_STRIDE 1
#define IBU_P2_CETUS_CH2_041_DEPTH  1

#define IBU_P2_CETUS_CH2_042_ADDR   0x011c032aL
#define IBU_P2_CETUS_CH2_042_STRIDE 1
#define IBU_P2_CETUS_CH2_042_DEPTH  1

#define IBU_P2_CETUS_CH2_043_ADDR   0x011c032bL
#define IBU_P2_CETUS_CH2_043_STRIDE 1
#define IBU_P2_CETUS_CH2_043_DEPTH  1

#define IBU_P2_CETUS_CH2_044_ADDR   0x011c032cL
#define IBU_P2_CETUS_CH2_044_STRIDE 1
#define IBU_P2_CETUS_CH2_044_DEPTH  1

#define IBU_P2_CETUS_CH2_045_ADDR   0x011c032dL
#define IBU_P2_CETUS_CH2_045_STRIDE 1
#define IBU_P2_CETUS_CH2_045_DEPTH  1

#define IBU_P2_CETUS_CH2_046_ADDR   0x011c032eL
#define IBU_P2_CETUS_CH2_046_STRIDE 1
#define IBU_P2_CETUS_CH2_046_DEPTH  1

#define IBU_P2_CETUS_CH2_047_ADDR   0x011c032fL
#define IBU_P2_CETUS_CH2_047_STRIDE 1
#define IBU_P2_CETUS_CH2_047_DEPTH  1

#define IBU_P2_CETUS_CH2_048_ADDR   0x011c0330L
#define IBU_P2_CETUS_CH2_048_STRIDE 1
#define IBU_P2_CETUS_CH2_048_DEPTH  1

#define IBU_P2_CETUS_CH2_049_ADDR   0x011c0331L
#define IBU_P2_CETUS_CH2_049_STRIDE 1
#define IBU_P2_CETUS_CH2_049_DEPTH  1

#define IBU_P2_CETUS_CH2_050_ADDR   0x011c0332L
#define IBU_P2_CETUS_CH2_050_STRIDE 1
#define IBU_P2_CETUS_CH2_050_DEPTH  1

#define IBU_P2_CETUS_CH2_051_ADDR   0x011c0333L
#define IBU_P2_CETUS_CH2_051_STRIDE 1
#define IBU_P2_CETUS_CH2_051_DEPTH  1

#define IBU_P2_CETUS_CH2_052_ADDR   0x011c0334L
#define IBU_P2_CETUS_CH2_052_STRIDE 1
#define IBU_P2_CETUS_CH2_052_DEPTH  1

#define IBU_P2_CETUS_CH2_053_ADDR   0x011c0335L
#define IBU_P2_CETUS_CH2_053_STRIDE 1
#define IBU_P2_CETUS_CH2_053_DEPTH  1

#define IBU_P2_CETUS_CH2_054_ADDR   0x011c0336L
#define IBU_P2_CETUS_CH2_054_STRIDE 1
#define IBU_P2_CETUS_CH2_054_DEPTH  1

#define IBU_P2_CETUS_CH2_055_ADDR   0x011c0337L
#define IBU_P2_CETUS_CH2_055_STRIDE 1
#define IBU_P2_CETUS_CH2_055_DEPTH  1

#define IBU_P2_CETUS_CH2_056_ADDR   0x011c0338L
#define IBU_P2_CETUS_CH2_056_STRIDE 1
#define IBU_P2_CETUS_CH2_056_DEPTH  1

#define IBU_P2_CETUS_CH2_057_ADDR   0x011c0339L
#define IBU_P2_CETUS_CH2_057_STRIDE 1
#define IBU_P2_CETUS_CH2_057_DEPTH  1

#define IBU_P2_CETUS_CH2_058_ADDR   0x011c033aL
#define IBU_P2_CETUS_CH2_058_STRIDE 1
#define IBU_P2_CETUS_CH2_058_DEPTH  1

#define IBU_P2_CETUS_CH2_059_ADDR   0x011c033bL
#define IBU_P2_CETUS_CH2_059_STRIDE 1
#define IBU_P2_CETUS_CH2_059_DEPTH  1

#define IBU_P2_CETUS_CH2_060_ADDR   0x011c033cL
#define IBU_P2_CETUS_CH2_060_STRIDE 1
#define IBU_P2_CETUS_CH2_060_DEPTH  1

#define IBU_P2_CETUS_CH2_061_ADDR   0x011c033dL
#define IBU_P2_CETUS_CH2_061_STRIDE 1
#define IBU_P2_CETUS_CH2_061_DEPTH  1

#define IBU_P2_CETUS_CH2_062_ADDR   0x011c033eL
#define IBU_P2_CETUS_CH2_062_STRIDE 1
#define IBU_P2_CETUS_CH2_062_DEPTH  1

#define IBU_P2_CETUS_CH2_063_ADDR   0x011c033fL
#define IBU_P2_CETUS_CH2_063_STRIDE 1
#define IBU_P2_CETUS_CH2_063_DEPTH  1

#define IBU_P2_CETUS_CH2_064_ADDR   0x011c0340L
#define IBU_P2_CETUS_CH2_064_STRIDE 1
#define IBU_P2_CETUS_CH2_064_DEPTH  1

#define IBU_P2_CETUS_CH2_065_ADDR   0x011c0341L
#define IBU_P2_CETUS_CH2_065_STRIDE 1
#define IBU_P2_CETUS_CH2_065_DEPTH  1

#define IBU_P2_CETUS_CH2_066_ADDR   0x011c0342L
#define IBU_P2_CETUS_CH2_066_STRIDE 1
#define IBU_P2_CETUS_CH2_066_DEPTH  1

#define IBU_P2_CETUS_CH2_067_ADDR   0x011c0343L
#define IBU_P2_CETUS_CH2_067_STRIDE 1
#define IBU_P2_CETUS_CH2_067_DEPTH  1

#define IBU_P2_CETUS_CH2_068_ADDR   0x011c0344L
#define IBU_P2_CETUS_CH2_068_STRIDE 1
#define IBU_P2_CETUS_CH2_068_DEPTH  1

#define IBU_P2_CETUS_CH2_069_ADDR   0x011c0345L
#define IBU_P2_CETUS_CH2_069_STRIDE 1
#define IBU_P2_CETUS_CH2_069_DEPTH  1

#define IBU_P2_CETUS_CH2_070_ADDR   0x011c0346L
#define IBU_P2_CETUS_CH2_070_STRIDE 1
#define IBU_P2_CETUS_CH2_070_DEPTH  1

#define IBU_P2_CETUS_CH2_071_ADDR   0x011c0347L
#define IBU_P2_CETUS_CH2_071_STRIDE 1
#define IBU_P2_CETUS_CH2_071_DEPTH  1

#define IBU_P2_CETUS_CH2_072_ADDR   0x011c0348L
#define IBU_P2_CETUS_CH2_072_STRIDE 1
#define IBU_P2_CETUS_CH2_072_DEPTH  1

#define IBU_P2_CETUS_CH2_073_ADDR   0x011c0349L
#define IBU_P2_CETUS_CH2_073_STRIDE 1
#define IBU_P2_CETUS_CH2_073_DEPTH  1

#define IBU_P2_CETUS_CH2_074_ADDR   0x011c034aL
#define IBU_P2_CETUS_CH2_074_STRIDE 1
#define IBU_P2_CETUS_CH2_074_DEPTH  1

#define IBU_P2_CETUS_CH2_075_ADDR   0x011c034bL
#define IBU_P2_CETUS_CH2_075_STRIDE 1
#define IBU_P2_CETUS_CH2_075_DEPTH  1

#define IBU_P2_CETUS_CH2_076_ADDR   0x011c034cL
#define IBU_P2_CETUS_CH2_076_STRIDE 1
#define IBU_P2_CETUS_CH2_076_DEPTH  1

#define IBU_P2_CETUS_CH2_077_ADDR   0x011c034dL
#define IBU_P2_CETUS_CH2_077_STRIDE 1
#define IBU_P2_CETUS_CH2_077_DEPTH  1

#define IBU_P2_CETUS_CH2_078_ADDR   0x011c034eL
#define IBU_P2_CETUS_CH2_078_STRIDE 1
#define IBU_P2_CETUS_CH2_078_DEPTH  1

#define IBU_P2_CETUS_CH2_079_ADDR   0x011c034fL
#define IBU_P2_CETUS_CH2_079_STRIDE 1
#define IBU_P2_CETUS_CH2_079_DEPTH  1

#define IBU_P2_CETUS_CH2_080_ADDR   0x011c0350L
#define IBU_P2_CETUS_CH2_080_STRIDE 1
#define IBU_P2_CETUS_CH2_080_DEPTH  1

#define IBU_P2_CETUS_CH2_081_ADDR   0x011c0351L
#define IBU_P2_CETUS_CH2_081_STRIDE 1
#define IBU_P2_CETUS_CH2_081_DEPTH  1

#define IBU_P2_CETUS_CH2_082_ADDR   0x011c0352L
#define IBU_P2_CETUS_CH2_082_STRIDE 1
#define IBU_P2_CETUS_CH2_082_DEPTH  1

#define IBU_P2_CETUS_CH2_083_ADDR   0x011c0353L
#define IBU_P2_CETUS_CH2_083_STRIDE 1
#define IBU_P2_CETUS_CH2_083_DEPTH  1

#define IBU_P2_CETUS_CH2_084_ADDR   0x011c0354L
#define IBU_P2_CETUS_CH2_084_STRIDE 1
#define IBU_P2_CETUS_CH2_084_DEPTH  1

#define IBU_P2_CETUS_CH2_085_ADDR   0x011c0355L
#define IBU_P2_CETUS_CH2_085_STRIDE 1
#define IBU_P2_CETUS_CH2_085_DEPTH  1

#define IBU_P2_CETUS_CH2_086_ADDR   0x011c0356L
#define IBU_P2_CETUS_CH2_086_STRIDE 1
#define IBU_P2_CETUS_CH2_086_DEPTH  1

#define IBU_P2_CETUS_CH2_087_ADDR   0x011c0357L
#define IBU_P2_CETUS_CH2_087_STRIDE 1
#define IBU_P2_CETUS_CH2_087_DEPTH  1

#define IBU_P2_CETUS_CH2_088_ADDR   0x011c0358L
#define IBU_P2_CETUS_CH2_088_STRIDE 1
#define IBU_P2_CETUS_CH2_088_DEPTH  1

#define IBU_P2_CETUS_CH2_089_ADDR   0x011c0359L
#define IBU_P2_CETUS_CH2_089_STRIDE 1
#define IBU_P2_CETUS_CH2_089_DEPTH  1

#define IBU_P2_CETUS_CH2_090_ADDR   0x011c035aL
#define IBU_P2_CETUS_CH2_090_STRIDE 1
#define IBU_P2_CETUS_CH2_090_DEPTH  1

#define IBU_P2_CETUS_CH2_091_ADDR   0x011c035bL
#define IBU_P2_CETUS_CH2_091_STRIDE 1
#define IBU_P2_CETUS_CH2_091_DEPTH  1

#define IBU_P2_CETUS_CH2_092_ADDR   0x011c035cL
#define IBU_P2_CETUS_CH2_092_STRIDE 1
#define IBU_P2_CETUS_CH2_092_DEPTH  1

#define IBU_P2_CETUS_CH2_093_ADDR   0x011c035dL
#define IBU_P2_CETUS_CH2_093_STRIDE 1
#define IBU_P2_CETUS_CH2_093_DEPTH  1

#define IBU_P2_CETUS_CH2_094_ADDR   0x011c035eL
#define IBU_P2_CETUS_CH2_094_STRIDE 1
#define IBU_P2_CETUS_CH2_094_DEPTH  1

#define IBU_P2_CETUS_CH2_095_ADDR   0x011c035fL
#define IBU_P2_CETUS_CH2_095_STRIDE 1
#define IBU_P2_CETUS_CH2_095_DEPTH  1

#define IBU_P2_CETUS_CH2_096_ADDR   0x011c0360L
#define IBU_P2_CETUS_CH2_096_STRIDE 1
#define IBU_P2_CETUS_CH2_096_DEPTH  1

#define IBU_P2_CETUS_CH2_097_ADDR   0x011c0361L
#define IBU_P2_CETUS_CH2_097_STRIDE 1
#define IBU_P2_CETUS_CH2_097_DEPTH  1

#define IBU_P2_CETUS_CH2_098_ADDR   0x011c0362L
#define IBU_P2_CETUS_CH2_098_STRIDE 1
#define IBU_P2_CETUS_CH2_098_DEPTH  1

#define IBU_P2_CETUS_CH2_099_ADDR   0x011c0363L
#define IBU_P2_CETUS_CH2_099_STRIDE 1
#define IBU_P2_CETUS_CH2_099_DEPTH  1

#define IBU_P2_CETUS_CH2_100_ADDR   0x011c0364L
#define IBU_P2_CETUS_CH2_100_STRIDE 1
#define IBU_P2_CETUS_CH2_100_DEPTH  1

#define IBU_P2_CETUS_CH2_101_ADDR   0x011c0365L
#define IBU_P2_CETUS_CH2_101_STRIDE 1
#define IBU_P2_CETUS_CH2_101_DEPTH  1

#define IBU_P2_CETUS_CH2_102_ADDR   0x011c0366L
#define IBU_P2_CETUS_CH2_102_STRIDE 1
#define IBU_P2_CETUS_CH2_102_DEPTH  1

#define IBU_P2_CETUS_CH2_103_ADDR   0x011c0367L
#define IBU_P2_CETUS_CH2_103_STRIDE 1
#define IBU_P2_CETUS_CH2_103_DEPTH  1

#define IBU_P2_CETUS_CH2_104_ADDR   0x011c0368L
#define IBU_P2_CETUS_CH2_104_STRIDE 1
#define IBU_P2_CETUS_CH2_104_DEPTH  1

#define IBU_P2_CETUS_CH2_105_ADDR   0x011c0369L
#define IBU_P2_CETUS_CH2_105_STRIDE 1
#define IBU_P2_CETUS_CH2_105_DEPTH  1

#define IBU_P2_CETUS_CH2_106_ADDR   0x011c036aL
#define IBU_P2_CETUS_CH2_106_STRIDE 1
#define IBU_P2_CETUS_CH2_106_DEPTH  1

#define IBU_P2_CETUS_CH2_107_ADDR   0x011c036bL
#define IBU_P2_CETUS_CH2_107_STRIDE 1
#define IBU_P2_CETUS_CH2_107_DEPTH  1

#define IBU_P2_CETUS_CH2_108_ADDR   0x011c036cL
#define IBU_P2_CETUS_CH2_108_STRIDE 1
#define IBU_P2_CETUS_CH2_108_DEPTH  1

#define IBU_P2_CETUS_CH2_109_ADDR   0x011c036dL
#define IBU_P2_CETUS_CH2_109_STRIDE 1
#define IBU_P2_CETUS_CH2_109_DEPTH  1

#define IBU_P2_CETUS_CH2_110_ADDR   0x011c036eL
#define IBU_P2_CETUS_CH2_110_STRIDE 1
#define IBU_P2_CETUS_CH2_110_DEPTH  1

#define IBU_P2_CETUS_CH2_111_ADDR   0x011c036fL
#define IBU_P2_CETUS_CH2_111_STRIDE 1
#define IBU_P2_CETUS_CH2_111_DEPTH  1

#define IBU_P2_CETUS_CH2_112_ADDR   0x011c0370L
#define IBU_P2_CETUS_CH2_112_STRIDE 1
#define IBU_P2_CETUS_CH2_112_DEPTH  1

#define IBU_P2_CETUS_CH2_113_ADDR   0x011c0371L
#define IBU_P2_CETUS_CH2_113_STRIDE 1
#define IBU_P2_CETUS_CH2_113_DEPTH  1

#define IBU_P2_CETUS_CH2_114_ADDR   0x011c0372L
#define IBU_P2_CETUS_CH2_114_STRIDE 1
#define IBU_P2_CETUS_CH2_114_DEPTH  1

#define IBU_P2_CETUS_CH2_115_ADDR   0x011c0373L
#define IBU_P2_CETUS_CH2_115_STRIDE 1
#define IBU_P2_CETUS_CH2_115_DEPTH  1

#define IBU_P2_CETUS_CH2_116_ADDR   0x011c0374L
#define IBU_P2_CETUS_CH2_116_STRIDE 1
#define IBU_P2_CETUS_CH2_116_DEPTH  1

#define IBU_P2_CETUS_CH2_117_ADDR   0x011c0375L
#define IBU_P2_CETUS_CH2_117_STRIDE 1
#define IBU_P2_CETUS_CH2_117_DEPTH  1

#define IBU_P2_CETUS_CH2_118_ADDR   0x011c0376L
#define IBU_P2_CETUS_CH2_118_STRIDE 1
#define IBU_P2_CETUS_CH2_118_DEPTH  1

#define IBU_P2_CETUS_CH2_119_ADDR   0x011c0377L
#define IBU_P2_CETUS_CH2_119_STRIDE 1
#define IBU_P2_CETUS_CH2_119_DEPTH  1

#define IBU_P2_CETUS_CH2_120_ADDR   0x011c0378L
#define IBU_P2_CETUS_CH2_120_STRIDE 1
#define IBU_P2_CETUS_CH2_120_DEPTH  1

#define IBU_P2_CETUS_CH2_121_ADDR   0x011c0379L
#define IBU_P2_CETUS_CH2_121_STRIDE 1
#define IBU_P2_CETUS_CH2_121_DEPTH  1

#define IBU_P2_CETUS_CH2_122_ADDR   0x011c037aL
#define IBU_P2_CETUS_CH2_122_STRIDE 1
#define IBU_P2_CETUS_CH2_122_DEPTH  1

#define IBU_P2_CETUS_CH2_123_ADDR   0x011c037bL
#define IBU_P2_CETUS_CH2_123_STRIDE 1
#define IBU_P2_CETUS_CH2_123_DEPTH  1

#define IBU_P2_CETUS_CH2_124_ADDR   0x011c037cL
#define IBU_P2_CETUS_CH2_124_STRIDE 1
#define IBU_P2_CETUS_CH2_124_DEPTH  1

#define IBU_P2_CETUS_CH2_125_ADDR   0x011c037dL
#define IBU_P2_CETUS_CH2_125_STRIDE 1
#define IBU_P2_CETUS_CH2_125_DEPTH  1

#define IBU_P2_CETUS_CH2_126_ADDR   0x011c037eL
#define IBU_P2_CETUS_CH2_126_STRIDE 1
#define IBU_P2_CETUS_CH2_126_DEPTH  1

#define IBU_P2_CETUS_CH2_127_ADDR   0x011c037fL
#define IBU_P2_CETUS_CH2_127_STRIDE 1
#define IBU_P2_CETUS_CH2_127_DEPTH  1

#define IBU_P2_CETUS_CH2_128_ADDR   0x011c0380L
#define IBU_P2_CETUS_CH2_128_STRIDE 1
#define IBU_P2_CETUS_CH2_128_DEPTH  1

#define IBU_P2_CETUS_CH2_129_ADDR   0x011c0381L
#define IBU_P2_CETUS_CH2_129_STRIDE 1
#define IBU_P2_CETUS_CH2_129_DEPTH  1

#define IBU_P2_CETUS_CH2_130_ADDR   0x011c0382L
#define IBU_P2_CETUS_CH2_130_STRIDE 1
#define IBU_P2_CETUS_CH2_130_DEPTH  1

#define IBU_P2_CETUS_CH2_131_ADDR   0x011c0383L
#define IBU_P2_CETUS_CH2_131_STRIDE 1
#define IBU_P2_CETUS_CH2_131_DEPTH  1

#define IBU_P2_CETUS_CH2_132_ADDR   0x011c0384L
#define IBU_P2_CETUS_CH2_132_STRIDE 1
#define IBU_P2_CETUS_CH2_132_DEPTH  1

#define IBU_P2_CETUS_CH2_133_ADDR   0x011c0385L
#define IBU_P2_CETUS_CH2_133_STRIDE 1
#define IBU_P2_CETUS_CH2_133_DEPTH  1

#define IBU_P2_CETUS_CH2_134_ADDR   0x011c0386L
#define IBU_P2_CETUS_CH2_134_STRIDE 1
#define IBU_P2_CETUS_CH2_134_DEPTH  1

#define IBU_P2_CETUS_CH2_135_ADDR   0x011c0387L
#define IBU_P2_CETUS_CH2_135_STRIDE 1
#define IBU_P2_CETUS_CH2_135_DEPTH  1

#define IBU_P2_CETUS_CH2_136_ADDR   0x011c0388L
#define IBU_P2_CETUS_CH2_136_STRIDE 1
#define IBU_P2_CETUS_CH2_136_DEPTH  1

#define IBU_P2_CETUS_CH2_137_ADDR   0x011c0389L
#define IBU_P2_CETUS_CH2_137_STRIDE 1
#define IBU_P2_CETUS_CH2_137_DEPTH  1

#define IBU_P2_CETUS_CH2_138_ADDR   0x011c038aL
#define IBU_P2_CETUS_CH2_138_STRIDE 1
#define IBU_P2_CETUS_CH2_138_DEPTH  1

#define IBU_P2_CETUS_CH2_139_ADDR   0x011c038bL
#define IBU_P2_CETUS_CH2_139_STRIDE 1
#define IBU_P2_CETUS_CH2_139_DEPTH  1

	/* CETUS register */
#define IBU_P2_CETUS_CH3_000_ADDR   0x011c0400L
#define IBU_P2_CETUS_CH3_000_STRIDE 1
#define IBU_P2_CETUS_CH3_000_DEPTH  1

	/* CETUS register */
#define IBU_P2_CETUS_CH3_001_ADDR   0x011c0401L
#define IBU_P2_CETUS_CH3_001_STRIDE 1
#define IBU_P2_CETUS_CH3_001_DEPTH  1

	/* CETUS register */
#define IBU_P2_CETUS_CH3_002_ADDR   0x011c0402L
#define IBU_P2_CETUS_CH3_002_STRIDE 1
#define IBU_P2_CETUS_CH3_002_DEPTH  1

#define IBU_P2_CETUS_CH3_003_ADDR   0x011c0403L
#define IBU_P2_CETUS_CH3_003_STRIDE 1
#define IBU_P2_CETUS_CH3_003_DEPTH  1

#define IBU_P2_CETUS_CH3_004_ADDR   0x011c0404L
#define IBU_P2_CETUS_CH3_004_STRIDE 1
#define IBU_P2_CETUS_CH3_004_DEPTH  1

#define IBU_P2_CETUS_CH3_005_ADDR   0x011c0405L
#define IBU_P2_CETUS_CH3_005_STRIDE 1
#define IBU_P2_CETUS_CH3_005_DEPTH  1

#define IBU_P2_CETUS_CH3_006_ADDR   0x011c0406L
#define IBU_P2_CETUS_CH3_006_STRIDE 1
#define IBU_P2_CETUS_CH3_006_DEPTH  1

#define IBU_P2_CETUS_CH3_007_ADDR   0x011c0407L
#define IBU_P2_CETUS_CH3_007_STRIDE 1
#define IBU_P2_CETUS_CH3_007_DEPTH  1

#define IBU_P2_CETUS_CH3_008_ADDR   0x011c0408L
#define IBU_P2_CETUS_CH3_008_STRIDE 1
#define IBU_P2_CETUS_CH3_008_DEPTH  1

#define IBU_P2_CETUS_CH3_009_ADDR   0x011c0409L
#define IBU_P2_CETUS_CH3_009_STRIDE 1
#define IBU_P2_CETUS_CH3_009_DEPTH  1

#define IBU_P2_CETUS_CH3_010_ADDR   0x011c040aL
#define IBU_P2_CETUS_CH3_010_STRIDE 1
#define IBU_P2_CETUS_CH3_010_DEPTH  1

#define IBU_P2_CETUS_CH3_011_ADDR   0x011c040bL
#define IBU_P2_CETUS_CH3_011_STRIDE 1
#define IBU_P2_CETUS_CH3_011_DEPTH  1

#define IBU_P2_CETUS_CH3_012_ADDR   0x011c040cL
#define IBU_P2_CETUS_CH3_012_STRIDE 1
#define IBU_P2_CETUS_CH3_012_DEPTH  1

#define IBU_P2_CETUS_CH3_013_ADDR   0x011c040dL
#define IBU_P2_CETUS_CH3_013_STRIDE 1
#define IBU_P2_CETUS_CH3_013_DEPTH  1

#define IBU_P2_CETUS_CH3_014_ADDR   0x011c040eL
#define IBU_P2_CETUS_CH3_014_STRIDE 1
#define IBU_P2_CETUS_CH3_014_DEPTH  1

#define IBU_P2_CETUS_CH3_015_ADDR   0x011c040fL
#define IBU_P2_CETUS_CH3_015_STRIDE 1
#define IBU_P2_CETUS_CH3_015_DEPTH  1

#define IBU_P2_CETUS_CH3_016_ADDR   0x011c0410L
#define IBU_P2_CETUS_CH3_016_STRIDE 1
#define IBU_P2_CETUS_CH3_016_DEPTH  1

#define IBU_P2_CETUS_CH3_017_ADDR   0x011c0411L
#define IBU_P2_CETUS_CH3_017_STRIDE 1
#define IBU_P2_CETUS_CH3_017_DEPTH  1

#define IBU_P2_CETUS_CH3_018_ADDR   0x011c0412L
#define IBU_P2_CETUS_CH3_018_STRIDE 1
#define IBU_P2_CETUS_CH3_018_DEPTH  1

#define IBU_P2_CETUS_CH3_019_ADDR   0x011c0413L
#define IBU_P2_CETUS_CH3_019_STRIDE 1
#define IBU_P2_CETUS_CH3_019_DEPTH  1

#define IBU_P2_CETUS_CH3_020_ADDR   0x011c0414L
#define IBU_P2_CETUS_CH3_020_STRIDE 1
#define IBU_P2_CETUS_CH3_020_DEPTH  1

#define IBU_P2_CETUS_CH3_021_ADDR   0x011c0415L
#define IBU_P2_CETUS_CH3_021_STRIDE 1
#define IBU_P2_CETUS_CH3_021_DEPTH  1

#define IBU_P2_CETUS_CH3_022_ADDR   0x011c0416L
#define IBU_P2_CETUS_CH3_022_STRIDE 1
#define IBU_P2_CETUS_CH3_022_DEPTH  1

#define IBU_P2_CETUS_CH3_023_ADDR   0x011c0417L
#define IBU_P2_CETUS_CH3_023_STRIDE 1
#define IBU_P2_CETUS_CH3_023_DEPTH  1

#define IBU_P2_CETUS_CH3_024_ADDR   0x011c0418L
#define IBU_P2_CETUS_CH3_024_STRIDE 1
#define IBU_P2_CETUS_CH3_024_DEPTH  1

#define IBU_P2_CETUS_CH3_025_ADDR   0x011c0419L
#define IBU_P2_CETUS_CH3_025_STRIDE 1
#define IBU_P2_CETUS_CH3_025_DEPTH  1

#define IBU_P2_CETUS_CH3_026_ADDR   0x011c041aL
#define IBU_P2_CETUS_CH3_026_STRIDE 1
#define IBU_P2_CETUS_CH3_026_DEPTH  1

#define IBU_P2_CETUS_CH3_027_ADDR   0x011c041bL
#define IBU_P2_CETUS_CH3_027_STRIDE 1
#define IBU_P2_CETUS_CH3_027_DEPTH  1

#define IBU_P2_CETUS_CH3_028_ADDR   0x011c041cL
#define IBU_P2_CETUS_CH3_028_STRIDE 1
#define IBU_P2_CETUS_CH3_028_DEPTH  1

#define IBU_P2_CETUS_CH3_029_ADDR   0x011c041dL
#define IBU_P2_CETUS_CH3_029_STRIDE 1
#define IBU_P2_CETUS_CH3_029_DEPTH  1

#define IBU_P2_CETUS_CH3_030_ADDR   0x011c041eL
#define IBU_P2_CETUS_CH3_030_STRIDE 1
#define IBU_P2_CETUS_CH3_030_DEPTH  1

#define IBU_P2_CETUS_CH3_031_ADDR   0x011c041fL
#define IBU_P2_CETUS_CH3_031_STRIDE 1
#define IBU_P2_CETUS_CH3_031_DEPTH  1

#define IBU_P2_CETUS_CH3_032_ADDR   0x011c0420L
#define IBU_P2_CETUS_CH3_032_STRIDE 1
#define IBU_P2_CETUS_CH3_032_DEPTH  1

#define IBU_P2_CETUS_CH3_033_ADDR   0x011c0421L
#define IBU_P2_CETUS_CH3_033_STRIDE 1
#define IBU_P2_CETUS_CH3_033_DEPTH  1

#define IBU_P2_CETUS_CH3_034_ADDR   0x011c0422L
#define IBU_P2_CETUS_CH3_034_STRIDE 1
#define IBU_P2_CETUS_CH3_034_DEPTH  1

#define IBU_P2_CETUS_CH3_035_ADDR   0x011c0423L
#define IBU_P2_CETUS_CH3_035_STRIDE 1
#define IBU_P2_CETUS_CH3_035_DEPTH  1

#define IBU_P2_CETUS_CH3_036_ADDR   0x011c0424L
#define IBU_P2_CETUS_CH3_036_STRIDE 1
#define IBU_P2_CETUS_CH3_036_DEPTH  1

#define IBU_P2_CETUS_CH3_037_ADDR   0x011c0425L
#define IBU_P2_CETUS_CH3_037_STRIDE 1
#define IBU_P2_CETUS_CH3_037_DEPTH  1

#define IBU_P2_CETUS_CH3_038_ADDR   0x011c0426L
#define IBU_P2_CETUS_CH3_038_STRIDE 1
#define IBU_P2_CETUS_CH3_038_DEPTH  1

#define IBU_P2_CETUS_CH3_039_ADDR   0x011c0427L
#define IBU_P2_CETUS_CH3_039_STRIDE 1
#define IBU_P2_CETUS_CH3_039_DEPTH  1

#define IBU_P2_CETUS_CH3_040_ADDR   0x011c0428L
#define IBU_P2_CETUS_CH3_040_STRIDE 1
#define IBU_P2_CETUS_CH3_040_DEPTH  1

#define IBU_P2_CETUS_CH3_041_ADDR   0x011c0429L
#define IBU_P2_CETUS_CH3_041_STRIDE 1
#define IBU_P2_CETUS_CH3_041_DEPTH  1

#define IBU_P2_CETUS_CH3_042_ADDR   0x011c042aL
#define IBU_P2_CETUS_CH3_042_STRIDE 1
#define IBU_P2_CETUS_CH3_042_DEPTH  1

#define IBU_P2_CETUS_CH3_043_ADDR   0x011c042bL
#define IBU_P2_CETUS_CH3_043_STRIDE 1
#define IBU_P2_CETUS_CH3_043_DEPTH  1

#define IBU_P2_CETUS_CH3_044_ADDR   0x011c042cL
#define IBU_P2_CETUS_CH3_044_STRIDE 1
#define IBU_P2_CETUS_CH3_044_DEPTH  1

#define IBU_P2_CETUS_CH3_045_ADDR   0x011c042dL
#define IBU_P2_CETUS_CH3_045_STRIDE 1
#define IBU_P2_CETUS_CH3_045_DEPTH  1

#define IBU_P2_CETUS_CH3_046_ADDR   0x011c042eL
#define IBU_P2_CETUS_CH3_046_STRIDE 1
#define IBU_P2_CETUS_CH3_046_DEPTH  1

#define IBU_P2_CETUS_CH3_047_ADDR   0x011c042fL
#define IBU_P2_CETUS_CH3_047_STRIDE 1
#define IBU_P2_CETUS_CH3_047_DEPTH  1

#define IBU_P2_CETUS_CH3_048_ADDR   0x011c0430L
#define IBU_P2_CETUS_CH3_048_STRIDE 1
#define IBU_P2_CETUS_CH3_048_DEPTH  1

#define IBU_P2_CETUS_CH3_049_ADDR   0x011c0431L
#define IBU_P2_CETUS_CH3_049_STRIDE 1
#define IBU_P2_CETUS_CH3_049_DEPTH  1

#define IBU_P2_CETUS_CH3_050_ADDR   0x011c0432L
#define IBU_P2_CETUS_CH3_050_STRIDE 1
#define IBU_P2_CETUS_CH3_050_DEPTH  1

#define IBU_P2_CETUS_CH3_051_ADDR   0x011c0433L
#define IBU_P2_CETUS_CH3_051_STRIDE 1
#define IBU_P2_CETUS_CH3_051_DEPTH  1

#define IBU_P2_CETUS_CH3_052_ADDR   0x011c0434L
#define IBU_P2_CETUS_CH3_052_STRIDE 1
#define IBU_P2_CETUS_CH3_052_DEPTH  1

#define IBU_P2_CETUS_CH3_053_ADDR   0x011c0435L
#define IBU_P2_CETUS_CH3_053_STRIDE 1
#define IBU_P2_CETUS_CH3_053_DEPTH  1

#define IBU_P2_CETUS_CH3_054_ADDR   0x011c0436L
#define IBU_P2_CETUS_CH3_054_STRIDE 1
#define IBU_P2_CETUS_CH3_054_DEPTH  1

#define IBU_P2_CETUS_CH3_055_ADDR   0x011c0437L
#define IBU_P2_CETUS_CH3_055_STRIDE 1
#define IBU_P2_CETUS_CH3_055_DEPTH  1

#define IBU_P2_CETUS_CH3_056_ADDR   0x011c0438L
#define IBU_P2_CETUS_CH3_056_STRIDE 1
#define IBU_P2_CETUS_CH3_056_DEPTH  1

#define IBU_P2_CETUS_CH3_057_ADDR   0x011c0439L
#define IBU_P2_CETUS_CH3_057_STRIDE 1
#define IBU_P2_CETUS_CH3_057_DEPTH  1

#define IBU_P2_CETUS_CH3_058_ADDR   0x011c043aL
#define IBU_P2_CETUS_CH3_058_STRIDE 1
#define IBU_P2_CETUS_CH3_058_DEPTH  1

#define IBU_P2_CETUS_CH3_059_ADDR   0x011c043bL
#define IBU_P2_CETUS_CH3_059_STRIDE 1
#define IBU_P2_CETUS_CH3_059_DEPTH  1

#define IBU_P2_CETUS_CH3_060_ADDR   0x011c043cL
#define IBU_P2_CETUS_CH3_060_STRIDE 1
#define IBU_P2_CETUS_CH3_060_DEPTH  1

#define IBU_P2_CETUS_CH3_061_ADDR   0x011c043dL
#define IBU_P2_CETUS_CH3_061_STRIDE 1
#define IBU_P2_CETUS_CH3_061_DEPTH  1

#define IBU_P2_CETUS_CH3_062_ADDR   0x011c043eL
#define IBU_P2_CETUS_CH3_062_STRIDE 1
#define IBU_P2_CETUS_CH3_062_DEPTH  1

#define IBU_P2_CETUS_CH3_063_ADDR   0x011c043fL
#define IBU_P2_CETUS_CH3_063_STRIDE 1
#define IBU_P2_CETUS_CH3_063_DEPTH  1

#define IBU_P2_CETUS_CH3_064_ADDR   0x011c0440L
#define IBU_P2_CETUS_CH3_064_STRIDE 1
#define IBU_P2_CETUS_CH3_064_DEPTH  1

#define IBU_P2_CETUS_CH3_065_ADDR   0x011c0441L
#define IBU_P2_CETUS_CH3_065_STRIDE 1
#define IBU_P2_CETUS_CH3_065_DEPTH  1

#define IBU_P2_CETUS_CH3_066_ADDR   0x011c0442L
#define IBU_P2_CETUS_CH3_066_STRIDE 1
#define IBU_P2_CETUS_CH3_066_DEPTH  1

#define IBU_P2_CETUS_CH3_067_ADDR   0x011c0443L
#define IBU_P2_CETUS_CH3_067_STRIDE 1
#define IBU_P2_CETUS_CH3_067_DEPTH  1

#define IBU_P2_CETUS_CH3_068_ADDR   0x011c0444L
#define IBU_P2_CETUS_CH3_068_STRIDE 1
#define IBU_P2_CETUS_CH3_068_DEPTH  1

#define IBU_P2_CETUS_CH3_069_ADDR   0x011c0445L
#define IBU_P2_CETUS_CH3_069_STRIDE 1
#define IBU_P2_CETUS_CH3_069_DEPTH  1

#define IBU_P2_CETUS_CH3_070_ADDR   0x011c0446L
#define IBU_P2_CETUS_CH3_070_STRIDE 1
#define IBU_P2_CETUS_CH3_070_DEPTH  1

#define IBU_P2_CETUS_CH3_071_ADDR   0x011c0447L
#define IBU_P2_CETUS_CH3_071_STRIDE 1
#define IBU_P2_CETUS_CH3_071_DEPTH  1

#define IBU_P2_CETUS_CH3_072_ADDR   0x011c0448L
#define IBU_P2_CETUS_CH3_072_STRIDE 1
#define IBU_P2_CETUS_CH3_072_DEPTH  1

#define IBU_P2_CETUS_CH3_073_ADDR   0x011c0449L
#define IBU_P2_CETUS_CH3_073_STRIDE 1
#define IBU_P2_CETUS_CH3_073_DEPTH  1

#define IBU_P2_CETUS_CH3_074_ADDR   0x011c044aL
#define IBU_P2_CETUS_CH3_074_STRIDE 1
#define IBU_P2_CETUS_CH3_074_DEPTH  1

#define IBU_P2_CETUS_CH3_075_ADDR   0x011c044bL
#define IBU_P2_CETUS_CH3_075_STRIDE 1
#define IBU_P2_CETUS_CH3_075_DEPTH  1

#define IBU_P2_CETUS_CH3_076_ADDR   0x011c044cL
#define IBU_P2_CETUS_CH3_076_STRIDE 1
#define IBU_P2_CETUS_CH3_076_DEPTH  1

#define IBU_P2_CETUS_CH3_077_ADDR   0x011c044dL
#define IBU_P2_CETUS_CH3_077_STRIDE 1
#define IBU_P2_CETUS_CH3_077_DEPTH  1

#define IBU_P2_CETUS_CH3_078_ADDR   0x011c044eL
#define IBU_P2_CETUS_CH3_078_STRIDE 1
#define IBU_P2_CETUS_CH3_078_DEPTH  1

#define IBU_P2_CETUS_CH3_079_ADDR   0x011c044fL
#define IBU_P2_CETUS_CH3_079_STRIDE 1
#define IBU_P2_CETUS_CH3_079_DEPTH  1

#define IBU_P2_CETUS_CH3_080_ADDR   0x011c0450L
#define IBU_P2_CETUS_CH3_080_STRIDE 1
#define IBU_P2_CETUS_CH3_080_DEPTH  1

#define IBU_P2_CETUS_CH3_081_ADDR   0x011c0451L
#define IBU_P2_CETUS_CH3_081_STRIDE 1
#define IBU_P2_CETUS_CH3_081_DEPTH  1

#define IBU_P2_CETUS_CH3_082_ADDR   0x011c0452L
#define IBU_P2_CETUS_CH3_082_STRIDE 1
#define IBU_P2_CETUS_CH3_082_DEPTH  1

#define IBU_P2_CETUS_CH3_083_ADDR   0x011c0453L
#define IBU_P2_CETUS_CH3_083_STRIDE 1
#define IBU_P2_CETUS_CH3_083_DEPTH  1

#define IBU_P2_CETUS_CH3_084_ADDR   0x011c0454L
#define IBU_P2_CETUS_CH3_084_STRIDE 1
#define IBU_P2_CETUS_CH3_084_DEPTH  1

#define IBU_P2_CETUS_CH3_085_ADDR   0x011c0455L
#define IBU_P2_CETUS_CH3_085_STRIDE 1
#define IBU_P2_CETUS_CH3_085_DEPTH  1

#define IBU_P2_CETUS_CH3_086_ADDR   0x011c0456L
#define IBU_P2_CETUS_CH3_086_STRIDE 1
#define IBU_P2_CETUS_CH3_086_DEPTH  1

#define IBU_P2_CETUS_CH3_087_ADDR   0x011c0457L
#define IBU_P2_CETUS_CH3_087_STRIDE 1
#define IBU_P2_CETUS_CH3_087_DEPTH  1

#define IBU_P2_CETUS_CH3_088_ADDR   0x011c0458L
#define IBU_P2_CETUS_CH3_088_STRIDE 1
#define IBU_P2_CETUS_CH3_088_DEPTH  1

#define IBU_P2_CETUS_CH3_089_ADDR   0x011c0459L
#define IBU_P2_CETUS_CH3_089_STRIDE 1
#define IBU_P2_CETUS_CH3_089_DEPTH  1

#define IBU_P2_CETUS_CH3_090_ADDR   0x011c045aL
#define IBU_P2_CETUS_CH3_090_STRIDE 1
#define IBU_P2_CETUS_CH3_090_DEPTH  1

#define IBU_P2_CETUS_CH3_091_ADDR   0x011c045bL
#define IBU_P2_CETUS_CH3_091_STRIDE 1
#define IBU_P2_CETUS_CH3_091_DEPTH  1

#define IBU_P2_CETUS_CH3_092_ADDR   0x011c045cL
#define IBU_P2_CETUS_CH3_092_STRIDE 1
#define IBU_P2_CETUS_CH3_092_DEPTH  1

#define IBU_P2_CETUS_CH3_093_ADDR   0x011c045dL
#define IBU_P2_CETUS_CH3_093_STRIDE 1
#define IBU_P2_CETUS_CH3_093_DEPTH  1

#define IBU_P2_CETUS_CH3_094_ADDR   0x011c045eL
#define IBU_P2_CETUS_CH3_094_STRIDE 1
#define IBU_P2_CETUS_CH3_094_DEPTH  1

#define IBU_P2_CETUS_CH3_095_ADDR   0x011c045fL
#define IBU_P2_CETUS_CH3_095_STRIDE 1
#define IBU_P2_CETUS_CH3_095_DEPTH  1

#define IBU_P2_CETUS_CH3_096_ADDR   0x011c0460L
#define IBU_P2_CETUS_CH3_096_STRIDE 1
#define IBU_P2_CETUS_CH3_096_DEPTH  1

#define IBU_P2_CETUS_CH3_097_ADDR   0x011c0461L
#define IBU_P2_CETUS_CH3_097_STRIDE 1
#define IBU_P2_CETUS_CH3_097_DEPTH  1

#define IBU_P2_CETUS_CH3_098_ADDR   0x011c0462L
#define IBU_P2_CETUS_CH3_098_STRIDE 1
#define IBU_P2_CETUS_CH3_098_DEPTH  1

#define IBU_P2_CETUS_CH3_099_ADDR   0x011c0463L
#define IBU_P2_CETUS_CH3_099_STRIDE 1
#define IBU_P2_CETUS_CH3_099_DEPTH  1

#define IBU_P2_CETUS_CH3_100_ADDR   0x011c0464L
#define IBU_P2_CETUS_CH3_100_STRIDE 1
#define IBU_P2_CETUS_CH3_100_DEPTH  1

#define IBU_P2_CETUS_CH3_101_ADDR   0x011c0465L
#define IBU_P2_CETUS_CH3_101_STRIDE 1
#define IBU_P2_CETUS_CH3_101_DEPTH  1

#define IBU_P2_CETUS_CH3_102_ADDR   0x011c0466L
#define IBU_P2_CETUS_CH3_102_STRIDE 1
#define IBU_P2_CETUS_CH3_102_DEPTH  1

#define IBU_P2_CETUS_CH3_103_ADDR   0x011c0467L
#define IBU_P2_CETUS_CH3_103_STRIDE 1
#define IBU_P2_CETUS_CH3_103_DEPTH  1

#define IBU_P2_CETUS_CH3_104_ADDR   0x011c0468L
#define IBU_P2_CETUS_CH3_104_STRIDE 1
#define IBU_P2_CETUS_CH3_104_DEPTH  1

#define IBU_P2_CETUS_CH3_105_ADDR   0x011c0469L
#define IBU_P2_CETUS_CH3_105_STRIDE 1
#define IBU_P2_CETUS_CH3_105_DEPTH  1

#define IBU_P2_CETUS_CH3_106_ADDR   0x011c046aL
#define IBU_P2_CETUS_CH3_106_STRIDE 1
#define IBU_P2_CETUS_CH3_106_DEPTH  1

#define IBU_P2_CETUS_CH3_107_ADDR   0x011c046bL
#define IBU_P2_CETUS_CH3_107_STRIDE 1
#define IBU_P2_CETUS_CH3_107_DEPTH  1

#define IBU_P2_CETUS_CH3_108_ADDR   0x011c046cL
#define IBU_P2_CETUS_CH3_108_STRIDE 1
#define IBU_P2_CETUS_CH3_108_DEPTH  1

#define IBU_P2_CETUS_CH3_109_ADDR   0x011c046dL
#define IBU_P2_CETUS_CH3_109_STRIDE 1
#define IBU_P2_CETUS_CH3_109_DEPTH  1

#define IBU_P2_CETUS_CH3_110_ADDR   0x011c046eL
#define IBU_P2_CETUS_CH3_110_STRIDE 1
#define IBU_P2_CETUS_CH3_110_DEPTH  1

#define IBU_P2_CETUS_CH3_111_ADDR   0x011c046fL
#define IBU_P2_CETUS_CH3_111_STRIDE 1
#define IBU_P2_CETUS_CH3_111_DEPTH  1

#define IBU_P2_CETUS_CH3_112_ADDR   0x011c0470L
#define IBU_P2_CETUS_CH3_112_STRIDE 1
#define IBU_P2_CETUS_CH3_112_DEPTH  1

#define IBU_P2_CETUS_CH3_113_ADDR   0x011c0471L
#define IBU_P2_CETUS_CH3_113_STRIDE 1
#define IBU_P2_CETUS_CH3_113_DEPTH  1

#define IBU_P2_CETUS_CH3_114_ADDR   0x011c0472L
#define IBU_P2_CETUS_CH3_114_STRIDE 1
#define IBU_P2_CETUS_CH3_114_DEPTH  1

#define IBU_P2_CETUS_CH3_115_ADDR   0x011c0473L
#define IBU_P2_CETUS_CH3_115_STRIDE 1
#define IBU_P2_CETUS_CH3_115_DEPTH  1

#define IBU_P2_CETUS_CH3_116_ADDR   0x011c0474L
#define IBU_P2_CETUS_CH3_116_STRIDE 1
#define IBU_P2_CETUS_CH3_116_DEPTH  1

#define IBU_P2_CETUS_CH3_117_ADDR   0x011c0475L
#define IBU_P2_CETUS_CH3_117_STRIDE 1
#define IBU_P2_CETUS_CH3_117_DEPTH  1

#define IBU_P2_CETUS_CH3_118_ADDR   0x011c0476L
#define IBU_P2_CETUS_CH3_118_STRIDE 1
#define IBU_P2_CETUS_CH3_118_DEPTH  1

#define IBU_P2_CETUS_CH3_119_ADDR   0x011c0477L
#define IBU_P2_CETUS_CH3_119_STRIDE 1
#define IBU_P2_CETUS_CH3_119_DEPTH  1

#define IBU_P2_CETUS_CH3_120_ADDR   0x011c0478L
#define IBU_P2_CETUS_CH3_120_STRIDE 1
#define IBU_P2_CETUS_CH3_120_DEPTH  1

#define IBU_P2_CETUS_CH3_121_ADDR   0x011c0479L
#define IBU_P2_CETUS_CH3_121_STRIDE 1
#define IBU_P2_CETUS_CH3_121_DEPTH  1

#define IBU_P2_CETUS_CH3_122_ADDR   0x011c047aL
#define IBU_P2_CETUS_CH3_122_STRIDE 1
#define IBU_P2_CETUS_CH3_122_DEPTH  1

#define IBU_P2_CETUS_CH3_123_ADDR   0x011c047bL
#define IBU_P2_CETUS_CH3_123_STRIDE 1
#define IBU_P2_CETUS_CH3_123_DEPTH  1

#define IBU_P2_CETUS_CH3_124_ADDR   0x011c047cL
#define IBU_P2_CETUS_CH3_124_STRIDE 1
#define IBU_P2_CETUS_CH3_124_DEPTH  1

#define IBU_P2_CETUS_CH3_125_ADDR   0x011c047dL
#define IBU_P2_CETUS_CH3_125_STRIDE 1
#define IBU_P2_CETUS_CH3_125_DEPTH  1

#define IBU_P2_CETUS_CH3_126_ADDR   0x011c047eL
#define IBU_P2_CETUS_CH3_126_STRIDE 1
#define IBU_P2_CETUS_CH3_126_DEPTH  1

#define IBU_P2_CETUS_CH3_127_ADDR   0x011c047fL
#define IBU_P2_CETUS_CH3_127_STRIDE 1
#define IBU_P2_CETUS_CH3_127_DEPTH  1

#define IBU_P2_CETUS_CH3_128_ADDR   0x011c0480L
#define IBU_P2_CETUS_CH3_128_STRIDE 1
#define IBU_P2_CETUS_CH3_128_DEPTH  1

#define IBU_P2_CETUS_CH3_129_ADDR   0x011c0481L
#define IBU_P2_CETUS_CH3_129_STRIDE 1
#define IBU_P2_CETUS_CH3_129_DEPTH  1

#define IBU_P2_CETUS_CH3_130_ADDR   0x011c0482L
#define IBU_P2_CETUS_CH3_130_STRIDE 1
#define IBU_P2_CETUS_CH3_130_DEPTH  1

#define IBU_P2_CETUS_CH3_131_ADDR   0x011c0483L
#define IBU_P2_CETUS_CH3_131_STRIDE 1
#define IBU_P2_CETUS_CH3_131_DEPTH  1

#define IBU_P2_CETUS_CH3_132_ADDR   0x011c0484L
#define IBU_P2_CETUS_CH3_132_STRIDE 1
#define IBU_P2_CETUS_CH3_132_DEPTH  1

#define IBU_P2_CETUS_CH3_133_ADDR   0x011c0485L
#define IBU_P2_CETUS_CH3_133_STRIDE 1
#define IBU_P2_CETUS_CH3_133_DEPTH  1

#define IBU_P2_CETUS_CH3_134_ADDR   0x011c0486L
#define IBU_P2_CETUS_CH3_134_STRIDE 1
#define IBU_P2_CETUS_CH3_134_DEPTH  1

#define IBU_P2_CETUS_CH3_135_ADDR   0x011c0487L
#define IBU_P2_CETUS_CH3_135_STRIDE 1
#define IBU_P2_CETUS_CH3_135_DEPTH  1

#define IBU_P2_CETUS_CH3_136_ADDR   0x011c0488L
#define IBU_P2_CETUS_CH3_136_STRIDE 1
#define IBU_P2_CETUS_CH3_136_DEPTH  1

#define IBU_P2_CETUS_CH3_137_ADDR   0x011c0489L
#define IBU_P2_CETUS_CH3_137_STRIDE 1
#define IBU_P2_CETUS_CH3_137_DEPTH  1

#define IBU_P2_CETUS_CH3_138_ADDR   0x011c048aL
#define IBU_P2_CETUS_CH3_138_STRIDE 1
#define IBU_P2_CETUS_CH3_138_DEPTH  1

#define IBU_P2_CETUS_CH3_139_ADDR   0x011c048bL
#define IBU_P2_CETUS_CH3_139_STRIDE 1
#define IBU_P2_CETUS_CH3_139_DEPTH  1

#define IBU_P2_CETUS_PLLB_CONTROL0_ADDR   0x011c0600L
#define IBU_P2_CETUS_PLLB_CONTROL0_STRIDE 1
#define IBU_P2_CETUS_PLLB_CONTROL0_DEPTH  1

#define IBU_P2_CETUS_PLLB_CONTROL1_ADDR   0x011c0601L
#define IBU_P2_CETUS_PLLB_CONTROL1_STRIDE 1
#define IBU_P2_CETUS_PLLB_CONTROL1_DEPTH  1

#define IBU_P2_CETUS_PLLB_CONTROL2_ADDR   0x011c0602L
#define IBU_P2_CETUS_PLLB_CONTROL2_STRIDE 1
#define IBU_P2_CETUS_PLLB_CONTROL2_DEPTH  1

#define IBU_P2_CETUS_PLLB_EXTFB_CNTR_ADDR   0x011c0603L
#define IBU_P2_CETUS_PLLB_EXTFB_CNTR_STRIDE 1
#define IBU_P2_CETUS_PLLB_EXTFB_CNTR_DEPTH  1

#define IBU_P2_CETUS_PLLB_FBCNT_ATO_ADDR   0x011c0604L
#define IBU_P2_CETUS_PLLB_FBCNT_ATO_STRIDE 1
#define IBU_P2_CETUS_PLLB_FBCNT_ATO_DEPTH  1

#define IBU_P2_CETUS_PLLB_SPARE_USRCNTR_ADDR   0x011c0605L
#define IBU_P2_CETUS_PLLB_SPARE_USRCNTR_STRIDE 1
#define IBU_P2_CETUS_PLLB_SPARE_USRCNTR_DEPTH  1

#define IBU_P2_CETUS_PLLB_DIV_EN_ADDR   0x011c0606L
#define IBU_P2_CETUS_PLLB_DIV_EN_STRIDE 1
#define IBU_P2_CETUS_PLLB_DIV_EN_DEPTH  1

#define IBU_P2_CETUS_PLLB_VCO_WAIT_CNT_ADDR   0x011c0607L
#define IBU_P2_CETUS_PLLB_VCO_WAIT_CNT_STRIDE 1
#define IBU_P2_CETUS_PLLB_VCO_WAIT_CNT_DEPTH  1

#define IBU_P2_CETUS_PLLB_STATUS0_ADDR   0x011c0608L
#define IBU_P2_CETUS_PLLB_STATUS0_STRIDE 1
#define IBU_P2_CETUS_PLLB_STATUS0_DEPTH  1

#define IBU_P2_CETUS_PLLB_STATUS1_ADDR   0x011c0609L
#define IBU_P2_CETUS_PLLB_STATUS1_STRIDE 1
#define IBU_P2_CETUS_PLLB_STATUS1_DEPTH  1

#define IBU_P2_CETUS_PLLB_010_ADDR   0x011c060aL
#define IBU_P2_CETUS_PLLB_010_STRIDE 1
#define IBU_P2_CETUS_PLLB_010_DEPTH  1

#define IBU_P2_CETUS_PLLB_011_ADDR   0x011c060bL
#define IBU_P2_CETUS_PLLB_011_STRIDE 1
#define IBU_P2_CETUS_PLLB_011_DEPTH  1

#define IBU_P2_CETUS_PLLB_012_ADDR   0x011c060cL
#define IBU_P2_CETUS_PLLB_012_STRIDE 1
#define IBU_P2_CETUS_PLLB_012_DEPTH  1

#define IBU_P2_CETUS_PLLB_013_ADDR   0x011c060dL
#define IBU_P2_CETUS_PLLB_013_STRIDE 1
#define IBU_P2_CETUS_PLLB_013_DEPTH  1

#define IBU_P2_CETUS_PLLB_014_ADDR   0x011c060eL
#define IBU_P2_CETUS_PLLB_014_STRIDE 1
#define IBU_P2_CETUS_PLLB_014_DEPTH  1

#define IBU_P2_CETUS_PLLB_015_ADDR   0x011c060fL
#define IBU_P2_CETUS_PLLB_015_STRIDE 1
#define IBU_P2_CETUS_PLLB_015_DEPTH  1

#define IBU_P2_CETUS_PLLB_016_ADDR   0x011c0610L
#define IBU_P2_CETUS_PLLB_016_STRIDE 1
#define IBU_P2_CETUS_PLLB_016_DEPTH  1

#define IBU_P2_CETUS_PLLB_017_ADDR   0x011c0611L
#define IBU_P2_CETUS_PLLB_017_STRIDE 1
#define IBU_P2_CETUS_PLLB_017_DEPTH  1

#define IBU_P2_CETUS_PLLB_018_ADDR   0x011c0612L
#define IBU_P2_CETUS_PLLB_018_STRIDE 1
#define IBU_P2_CETUS_PLLB_018_DEPTH  1

#define IBU_P2_CETUS_PLLB_019_ADDR   0x011c0613L
#define IBU_P2_CETUS_PLLB_019_STRIDE 1
#define IBU_P2_CETUS_PLLB_019_DEPTH  1

#define IBU_P2_CETUS_PLLB_020_ADDR   0x011c0614L
#define IBU_P2_CETUS_PLLB_020_STRIDE 1
#define IBU_P2_CETUS_PLLB_020_DEPTH  1

#define IBU_P2_CETUS_PLLB_021_ADDR   0x011c0615L
#define IBU_P2_CETUS_PLLB_021_STRIDE 1
#define IBU_P2_CETUS_PLLB_021_DEPTH  1

#define IBU_P2_CETUS_PLLB_022_ADDR   0x011c0616L
#define IBU_P2_CETUS_PLLB_022_STRIDE 1
#define IBU_P2_CETUS_PLLB_022_DEPTH  1

#define IBU_P2_CETUS_PLLB_023_ADDR   0x011c0617L
#define IBU_P2_CETUS_PLLB_023_STRIDE 1
#define IBU_P2_CETUS_PLLB_023_DEPTH  1

#define IBU_P2_CETUS_PLLB_024_ADDR   0x011c0618L
#define IBU_P2_CETUS_PLLB_024_STRIDE 1
#define IBU_P2_CETUS_PLLB_024_DEPTH  1

	/* CETUS register */
#define IBU_P2_CETUS_ALL_000_ADDR   0x011c0f00L
#define IBU_P2_CETUS_ALL_000_STRIDE 1
#define IBU_P2_CETUS_ALL_000_DEPTH  1

	/* CETUS register */
#define IBU_P2_CETUS_ALL_001_ADDR   0x011c0f01L
#define IBU_P2_CETUS_ALL_001_STRIDE 1
#define IBU_P2_CETUS_ALL_001_DEPTH  1

	/* CETUS register */
#define IBU_P2_CETUS_ALL_002_ADDR   0x011c0f02L
#define IBU_P2_CETUS_ALL_002_STRIDE 1
#define IBU_P2_CETUS_ALL_002_DEPTH  1

#define IBU_P2_CETUS_ALL_003_ADDR   0x011c0f03L
#define IBU_P2_CETUS_ALL_003_STRIDE 1
#define IBU_P2_CETUS_ALL_003_DEPTH  1

#define IBU_P2_CETUS_ALL_004_ADDR   0x011c0f04L
#define IBU_P2_CETUS_ALL_004_STRIDE 1
#define IBU_P2_CETUS_ALL_004_DEPTH  1

#define IBU_P2_CETUS_ALL_005_ADDR   0x011c0f05L
#define IBU_P2_CETUS_ALL_005_STRIDE 1
#define IBU_P2_CETUS_ALL_005_DEPTH  1

#define IBU_P2_CETUS_ALL_006_ADDR   0x011c0f06L
#define IBU_P2_CETUS_ALL_006_STRIDE 1
#define IBU_P2_CETUS_ALL_006_DEPTH  1

#define IBU_P2_CETUS_ALL_007_ADDR   0x011c0f07L
#define IBU_P2_CETUS_ALL_007_STRIDE 1
#define IBU_P2_CETUS_ALL_007_DEPTH  1

#define IBU_P2_CETUS_ALL_008_ADDR   0x011c0f08L
#define IBU_P2_CETUS_ALL_008_STRIDE 1
#define IBU_P2_CETUS_ALL_008_DEPTH  1

#define IBU_P2_CETUS_ALL_009_ADDR   0x011c0f09L
#define IBU_P2_CETUS_ALL_009_STRIDE 1
#define IBU_P2_CETUS_ALL_009_DEPTH  1

#define IBU_P2_CETUS_ALL_010_ADDR   0x011c0f0aL
#define IBU_P2_CETUS_ALL_010_STRIDE 1
#define IBU_P2_CETUS_ALL_010_DEPTH  1

#define IBU_P2_CETUS_ALL_011_ADDR   0x011c0f0bL
#define IBU_P2_CETUS_ALL_011_STRIDE 1
#define IBU_P2_CETUS_ALL_011_DEPTH  1

#define IBU_P2_CETUS_ALL_012_ADDR   0x011c0f0cL
#define IBU_P2_CETUS_ALL_012_STRIDE 1
#define IBU_P2_CETUS_ALL_012_DEPTH  1

#define IBU_P2_CETUS_ALL_013_ADDR   0x011c0f0dL
#define IBU_P2_CETUS_ALL_013_STRIDE 1
#define IBU_P2_CETUS_ALL_013_DEPTH  1

#define IBU_P2_CETUS_ALL_014_ADDR   0x011c0f0eL
#define IBU_P2_CETUS_ALL_014_STRIDE 1
#define IBU_P2_CETUS_ALL_014_DEPTH  1

#define IBU_P2_CETUS_ALL_015_ADDR   0x011c0f0fL
#define IBU_P2_CETUS_ALL_015_STRIDE 1
#define IBU_P2_CETUS_ALL_015_DEPTH  1

#define IBU_P2_CETUS_ALL_016_ADDR   0x011c0f10L
#define IBU_P2_CETUS_ALL_016_STRIDE 1
#define IBU_P2_CETUS_ALL_016_DEPTH  1

#define IBU_P2_CETUS_ALL_017_ADDR   0x011c0f11L
#define IBU_P2_CETUS_ALL_017_STRIDE 1
#define IBU_P2_CETUS_ALL_017_DEPTH  1

#define IBU_P2_CETUS_ALL_018_ADDR   0x011c0f12L
#define IBU_P2_CETUS_ALL_018_STRIDE 1
#define IBU_P2_CETUS_ALL_018_DEPTH  1

#define IBU_P2_CETUS_ALL_019_ADDR   0x011c0f13L
#define IBU_P2_CETUS_ALL_019_STRIDE 1
#define IBU_P2_CETUS_ALL_019_DEPTH  1

#define IBU_P2_CETUS_ALL_020_ADDR   0x011c0f14L
#define IBU_P2_CETUS_ALL_020_STRIDE 1
#define IBU_P2_CETUS_ALL_020_DEPTH  1

#define IBU_P2_CETUS_ALL_021_ADDR   0x011c0f15L
#define IBU_P2_CETUS_ALL_021_STRIDE 1
#define IBU_P2_CETUS_ALL_021_DEPTH  1

#define IBU_P2_CETUS_ALL_022_ADDR   0x011c0f16L
#define IBU_P2_CETUS_ALL_022_STRIDE 1
#define IBU_P2_CETUS_ALL_022_DEPTH  1

#define IBU_P2_CETUS_ALL_023_ADDR   0x011c0f17L
#define IBU_P2_CETUS_ALL_023_STRIDE 1
#define IBU_P2_CETUS_ALL_023_DEPTH  1

#define IBU_P2_CETUS_ALL_024_ADDR   0x011c0f18L
#define IBU_P2_CETUS_ALL_024_STRIDE 1
#define IBU_P2_CETUS_ALL_024_DEPTH  1

#define IBU_P2_CETUS_ALL_025_ADDR   0x011c0f19L
#define IBU_P2_CETUS_ALL_025_STRIDE 1
#define IBU_P2_CETUS_ALL_025_DEPTH  1

#define IBU_P2_CETUS_ALL_026_ADDR   0x011c0f1aL
#define IBU_P2_CETUS_ALL_026_STRIDE 1
#define IBU_P2_CETUS_ALL_026_DEPTH  1

#define IBU_P2_CETUS_ALL_027_ADDR   0x011c0f1bL
#define IBU_P2_CETUS_ALL_027_STRIDE 1
#define IBU_P2_CETUS_ALL_027_DEPTH  1

#define IBU_P2_CETUS_ALL_028_ADDR   0x011c0f1cL
#define IBU_P2_CETUS_ALL_028_STRIDE 1
#define IBU_P2_CETUS_ALL_028_DEPTH  1

#define IBU_P2_CETUS_ALL_029_ADDR   0x011c0f1dL
#define IBU_P2_CETUS_ALL_029_STRIDE 1
#define IBU_P2_CETUS_ALL_029_DEPTH  1

#define IBU_P2_CETUS_ALL_030_ADDR   0x011c0f1eL
#define IBU_P2_CETUS_ALL_030_STRIDE 1
#define IBU_P2_CETUS_ALL_030_DEPTH  1

#define IBU_P2_CETUS_ALL_031_ADDR   0x011c0f1fL
#define IBU_P2_CETUS_ALL_031_STRIDE 1
#define IBU_P2_CETUS_ALL_031_DEPTH  1

#define IBU_P2_CETUS_ALL_032_ADDR   0x011c0f20L
#define IBU_P2_CETUS_ALL_032_STRIDE 1
#define IBU_P2_CETUS_ALL_032_DEPTH  1

#define IBU_P2_CETUS_ALL_033_ADDR   0x011c0f21L
#define IBU_P2_CETUS_ALL_033_STRIDE 1
#define IBU_P2_CETUS_ALL_033_DEPTH  1

#define IBU_P2_CETUS_ALL_034_ADDR   0x011c0f22L
#define IBU_P2_CETUS_ALL_034_STRIDE 1
#define IBU_P2_CETUS_ALL_034_DEPTH  1

#define IBU_P2_CETUS_ALL_035_ADDR   0x011c0f23L
#define IBU_P2_CETUS_ALL_035_STRIDE 1
#define IBU_P2_CETUS_ALL_035_DEPTH  1

#define IBU_P2_CETUS_ALL_036_ADDR   0x011c0f24L
#define IBU_P2_CETUS_ALL_036_STRIDE 1
#define IBU_P2_CETUS_ALL_036_DEPTH  1

#define IBU_P2_CETUS_ALL_037_ADDR   0x011c0f25L
#define IBU_P2_CETUS_ALL_037_STRIDE 1
#define IBU_P2_CETUS_ALL_037_DEPTH  1

#define IBU_P2_CETUS_ALL_038_ADDR   0x011c0f26L
#define IBU_P2_CETUS_ALL_038_STRIDE 1
#define IBU_P2_CETUS_ALL_038_DEPTH  1

#define IBU_P2_CETUS_ALL_039_ADDR   0x011c0f27L
#define IBU_P2_CETUS_ALL_039_STRIDE 1
#define IBU_P2_CETUS_ALL_039_DEPTH  1

#define IBU_P2_CETUS_ALL_040_ADDR   0x011c0f28L
#define IBU_P2_CETUS_ALL_040_STRIDE 1
#define IBU_P2_CETUS_ALL_040_DEPTH  1

#define IBU_P2_CETUS_ALL_041_ADDR   0x011c0f29L
#define IBU_P2_CETUS_ALL_041_STRIDE 1
#define IBU_P2_CETUS_ALL_041_DEPTH  1

#define IBU_P2_CETUS_ALL_042_ADDR   0x011c0f2aL
#define IBU_P2_CETUS_ALL_042_STRIDE 1
#define IBU_P2_CETUS_ALL_042_DEPTH  1

#define IBU_P2_CETUS_ALL_043_ADDR   0x011c0f2bL
#define IBU_P2_CETUS_ALL_043_STRIDE 1
#define IBU_P2_CETUS_ALL_043_DEPTH  1

#define IBU_P2_CETUS_ALL_044_ADDR   0x011c0f2cL
#define IBU_P2_CETUS_ALL_044_STRIDE 1
#define IBU_P2_CETUS_ALL_044_DEPTH  1

#define IBU_P2_CETUS_ALL_045_ADDR   0x011c0f2dL
#define IBU_P2_CETUS_ALL_045_STRIDE 1
#define IBU_P2_CETUS_ALL_045_DEPTH  1

#define IBU_P2_CETUS_ALL_046_ADDR   0x011c0f2eL
#define IBU_P2_CETUS_ALL_046_STRIDE 1
#define IBU_P2_CETUS_ALL_046_DEPTH  1

#define IBU_P2_CETUS_ALL_047_ADDR   0x011c0f2fL
#define IBU_P2_CETUS_ALL_047_STRIDE 1
#define IBU_P2_CETUS_ALL_047_DEPTH  1

#define IBU_P2_CETUS_ALL_048_ADDR   0x011c0f30L
#define IBU_P2_CETUS_ALL_048_STRIDE 1
#define IBU_P2_CETUS_ALL_048_DEPTH  1

#define IBU_P2_CETUS_ALL_049_ADDR   0x011c0f31L
#define IBU_P2_CETUS_ALL_049_STRIDE 1
#define IBU_P2_CETUS_ALL_049_DEPTH  1

#define IBU_P2_CETUS_ALL_050_ADDR   0x011c0f32L
#define IBU_P2_CETUS_ALL_050_STRIDE 1
#define IBU_P2_CETUS_ALL_050_DEPTH  1

#define IBU_P2_CETUS_ALL_051_ADDR   0x011c0f33L
#define IBU_P2_CETUS_ALL_051_STRIDE 1
#define IBU_P2_CETUS_ALL_051_DEPTH  1

#define IBU_P2_CETUS_ALL_052_ADDR   0x011c0f34L
#define IBU_P2_CETUS_ALL_052_STRIDE 1
#define IBU_P2_CETUS_ALL_052_DEPTH  1

#define IBU_P2_CETUS_ALL_053_ADDR   0x011c0f35L
#define IBU_P2_CETUS_ALL_053_STRIDE 1
#define IBU_P2_CETUS_ALL_053_DEPTH  1

#define IBU_P2_CETUS_ALL_054_ADDR   0x011c0f36L
#define IBU_P2_CETUS_ALL_054_STRIDE 1
#define IBU_P2_CETUS_ALL_054_DEPTH  1

#define IBU_P2_CETUS_ALL_055_ADDR   0x011c0f37L
#define IBU_P2_CETUS_ALL_055_STRIDE 1
#define IBU_P2_CETUS_ALL_055_DEPTH  1

#define IBU_P2_CETUS_ALL_056_ADDR   0x011c0f38L
#define IBU_P2_CETUS_ALL_056_STRIDE 1
#define IBU_P2_CETUS_ALL_056_DEPTH  1

#define IBU_P2_CETUS_ALL_057_ADDR   0x011c0f39L
#define IBU_P2_CETUS_ALL_057_STRIDE 1
#define IBU_P2_CETUS_ALL_057_DEPTH  1

#define IBU_P2_CETUS_ALL_058_ADDR   0x011c0f3aL
#define IBU_P2_CETUS_ALL_058_STRIDE 1
#define IBU_P2_CETUS_ALL_058_DEPTH  1

#define IBU_P2_CETUS_ALL_059_ADDR   0x011c0f3bL
#define IBU_P2_CETUS_ALL_059_STRIDE 1
#define IBU_P2_CETUS_ALL_059_DEPTH  1

#define IBU_P2_CETUS_ALL_060_ADDR   0x011c0f3cL
#define IBU_P2_CETUS_ALL_060_STRIDE 1
#define IBU_P2_CETUS_ALL_060_DEPTH  1

#define IBU_P2_CETUS_ALL_061_ADDR   0x011c0f3dL
#define IBU_P2_CETUS_ALL_061_STRIDE 1
#define IBU_P2_CETUS_ALL_061_DEPTH  1

#define IBU_P2_CETUS_ALL_062_ADDR   0x011c0f3eL
#define IBU_P2_CETUS_ALL_062_STRIDE 1
#define IBU_P2_CETUS_ALL_062_DEPTH  1

#define IBU_P2_CETUS_ALL_063_ADDR   0x011c0f3fL
#define IBU_P2_CETUS_ALL_063_STRIDE 1
#define IBU_P2_CETUS_ALL_063_DEPTH  1

#define IBU_P2_CETUS_ALL_064_ADDR   0x011c0f40L
#define IBU_P2_CETUS_ALL_064_STRIDE 1
#define IBU_P2_CETUS_ALL_064_DEPTH  1

#define IBU_P2_CETUS_ALL_065_ADDR   0x011c0f41L
#define IBU_P2_CETUS_ALL_065_STRIDE 1
#define IBU_P2_CETUS_ALL_065_DEPTH  1

#define IBU_P2_CETUS_ALL_066_ADDR   0x011c0f42L
#define IBU_P2_CETUS_ALL_066_STRIDE 1
#define IBU_P2_CETUS_ALL_066_DEPTH  1

#define IBU_P2_CETUS_ALL_067_ADDR   0x011c0f43L
#define IBU_P2_CETUS_ALL_067_STRIDE 1
#define IBU_P2_CETUS_ALL_067_DEPTH  1

#define IBU_P2_CETUS_ALL_068_ADDR   0x011c0f44L
#define IBU_P2_CETUS_ALL_068_STRIDE 1
#define IBU_P2_CETUS_ALL_068_DEPTH  1

#define IBU_P2_CETUS_ALL_069_ADDR   0x011c0f45L
#define IBU_P2_CETUS_ALL_069_STRIDE 1
#define IBU_P2_CETUS_ALL_069_DEPTH  1

#define IBU_P2_CETUS_ALL_070_ADDR   0x011c0f46L
#define IBU_P2_CETUS_ALL_070_STRIDE 1
#define IBU_P2_CETUS_ALL_070_DEPTH  1

#define IBU_P2_CETUS_ALL_071_ADDR   0x011c0f47L
#define IBU_P2_CETUS_ALL_071_STRIDE 1
#define IBU_P2_CETUS_ALL_071_DEPTH  1

#define IBU_P2_CETUS_ALL_072_ADDR   0x011c0f48L
#define IBU_P2_CETUS_ALL_072_STRIDE 1
#define IBU_P2_CETUS_ALL_072_DEPTH  1

#define IBU_P2_CETUS_ALL_073_ADDR   0x011c0f49L
#define IBU_P2_CETUS_ALL_073_STRIDE 1
#define IBU_P2_CETUS_ALL_073_DEPTH  1

#define IBU_P2_CETUS_ALL_074_ADDR   0x011c0f4aL
#define IBU_P2_CETUS_ALL_074_STRIDE 1
#define IBU_P2_CETUS_ALL_074_DEPTH  1

#define IBU_P2_CETUS_ALL_075_ADDR   0x011c0f4bL
#define IBU_P2_CETUS_ALL_075_STRIDE 1
#define IBU_P2_CETUS_ALL_075_DEPTH  1

#define IBU_P2_CETUS_ALL_076_ADDR   0x011c0f4cL
#define IBU_P2_CETUS_ALL_076_STRIDE 1
#define IBU_P2_CETUS_ALL_076_DEPTH  1

#define IBU_P2_CETUS_ALL_077_ADDR   0x011c0f4dL
#define IBU_P2_CETUS_ALL_077_STRIDE 1
#define IBU_P2_CETUS_ALL_077_DEPTH  1

#define IBU_P2_CETUS_ALL_078_ADDR   0x011c0f4eL
#define IBU_P2_CETUS_ALL_078_STRIDE 1
#define IBU_P2_CETUS_ALL_078_DEPTH  1

#define IBU_P2_CETUS_ALL_079_ADDR   0x011c0f4fL
#define IBU_P2_CETUS_ALL_079_STRIDE 1
#define IBU_P2_CETUS_ALL_079_DEPTH  1

#define IBU_P2_CETUS_ALL_080_ADDR   0x011c0f50L
#define IBU_P2_CETUS_ALL_080_STRIDE 1
#define IBU_P2_CETUS_ALL_080_DEPTH  1

#define IBU_P2_CETUS_ALL_081_ADDR   0x011c0f51L
#define IBU_P2_CETUS_ALL_081_STRIDE 1
#define IBU_P2_CETUS_ALL_081_DEPTH  1

#define IBU_P2_CETUS_ALL_082_ADDR   0x011c0f52L
#define IBU_P2_CETUS_ALL_082_STRIDE 1
#define IBU_P2_CETUS_ALL_082_DEPTH  1

#define IBU_P2_CETUS_ALL_083_ADDR   0x011c0f53L
#define IBU_P2_CETUS_ALL_083_STRIDE 1
#define IBU_P2_CETUS_ALL_083_DEPTH  1

#define IBU_P2_CETUS_ALL_084_ADDR   0x011c0f54L
#define IBU_P2_CETUS_ALL_084_STRIDE 1
#define IBU_P2_CETUS_ALL_084_DEPTH  1

#define IBU_P2_CETUS_ALL_085_ADDR   0x011c0f55L
#define IBU_P2_CETUS_ALL_085_STRIDE 1
#define IBU_P2_CETUS_ALL_085_DEPTH  1

#define IBU_P2_CETUS_ALL_086_ADDR   0x011c0f56L
#define IBU_P2_CETUS_ALL_086_STRIDE 1
#define IBU_P2_CETUS_ALL_086_DEPTH  1

#define IBU_P2_CETUS_ALL_087_ADDR   0x011c0f57L
#define IBU_P2_CETUS_ALL_087_STRIDE 1
#define IBU_P2_CETUS_ALL_087_DEPTH  1

#define IBU_P2_CETUS_ALL_088_ADDR   0x011c0f58L
#define IBU_P2_CETUS_ALL_088_STRIDE 1
#define IBU_P2_CETUS_ALL_088_DEPTH  1

#define IBU_P2_CETUS_ALL_089_ADDR   0x011c0f59L
#define IBU_P2_CETUS_ALL_089_STRIDE 1
#define IBU_P2_CETUS_ALL_089_DEPTH  1

#define IBU_P2_CETUS_ALL_090_ADDR   0x011c0f5aL
#define IBU_P2_CETUS_ALL_090_STRIDE 1
#define IBU_P2_CETUS_ALL_090_DEPTH  1

#define IBU_P2_CETUS_ALL_091_ADDR   0x011c0f5bL
#define IBU_P2_CETUS_ALL_091_STRIDE 1
#define IBU_P2_CETUS_ALL_091_DEPTH  1

#define IBU_P2_CETUS_ALL_092_ADDR   0x011c0f5cL
#define IBU_P2_CETUS_ALL_092_STRIDE 1
#define IBU_P2_CETUS_ALL_092_DEPTH  1

#define IBU_P2_CETUS_ALL_093_ADDR   0x011c0f5dL
#define IBU_P2_CETUS_ALL_093_STRIDE 1
#define IBU_P2_CETUS_ALL_093_DEPTH  1

#define IBU_P2_CETUS_ALL_094_ADDR   0x011c0f5eL
#define IBU_P2_CETUS_ALL_094_STRIDE 1
#define IBU_P2_CETUS_ALL_094_DEPTH  1

#define IBU_P2_CETUS_ALL_095_ADDR   0x011c0f5fL
#define IBU_P2_CETUS_ALL_095_STRIDE 1
#define IBU_P2_CETUS_ALL_095_DEPTH  1

#define IBU_P2_CETUS_ALL_096_ADDR   0x011c0f60L
#define IBU_P2_CETUS_ALL_096_STRIDE 1
#define IBU_P2_CETUS_ALL_096_DEPTH  1

#define IBU_P2_CETUS_ALL_097_ADDR   0x011c0f61L
#define IBU_P2_CETUS_ALL_097_STRIDE 1
#define IBU_P2_CETUS_ALL_097_DEPTH  1

#define IBU_P2_CETUS_ALL_098_ADDR   0x011c0f62L
#define IBU_P2_CETUS_ALL_098_STRIDE 1
#define IBU_P2_CETUS_ALL_098_DEPTH  1

#define IBU_P2_CETUS_ALL_099_ADDR   0x011c0f63L
#define IBU_P2_CETUS_ALL_099_STRIDE 1
#define IBU_P2_CETUS_ALL_099_DEPTH  1

#define IBU_P2_CETUS_ALL_100_ADDR   0x011c0f64L
#define IBU_P2_CETUS_ALL_100_STRIDE 1
#define IBU_P2_CETUS_ALL_100_DEPTH  1

#define IBU_P2_CETUS_ALL_101_ADDR   0x011c0f65L
#define IBU_P2_CETUS_ALL_101_STRIDE 1
#define IBU_P2_CETUS_ALL_101_DEPTH  1

#define IBU_P2_CETUS_ALL_102_ADDR   0x011c0f66L
#define IBU_P2_CETUS_ALL_102_STRIDE 1
#define IBU_P2_CETUS_ALL_102_DEPTH  1

#define IBU_P2_CETUS_ALL_103_ADDR   0x011c0f67L
#define IBU_P2_CETUS_ALL_103_STRIDE 1
#define IBU_P2_CETUS_ALL_103_DEPTH  1

#define IBU_P2_CETUS_ALL_104_ADDR   0x011c0f68L
#define IBU_P2_CETUS_ALL_104_STRIDE 1
#define IBU_P2_CETUS_ALL_104_DEPTH  1

#define IBU_P2_CETUS_ALL_105_ADDR   0x011c0f69L
#define IBU_P2_CETUS_ALL_105_STRIDE 1
#define IBU_P2_CETUS_ALL_105_DEPTH  1

#define IBU_P2_CETUS_ALL_106_ADDR   0x011c0f6aL
#define IBU_P2_CETUS_ALL_106_STRIDE 1
#define IBU_P2_CETUS_ALL_106_DEPTH  1

#define IBU_P2_CETUS_ALL_107_ADDR   0x011c0f6bL
#define IBU_P2_CETUS_ALL_107_STRIDE 1
#define IBU_P2_CETUS_ALL_107_DEPTH  1

#define IBU_P2_CETUS_ALL_108_ADDR   0x011c0f6cL
#define IBU_P2_CETUS_ALL_108_STRIDE 1
#define IBU_P2_CETUS_ALL_108_DEPTH  1

#define IBU_P2_CETUS_ALL_109_ADDR   0x011c0f6dL
#define IBU_P2_CETUS_ALL_109_STRIDE 1
#define IBU_P2_CETUS_ALL_109_DEPTH  1

#define IBU_P2_CETUS_ALL_110_ADDR   0x011c0f6eL
#define IBU_P2_CETUS_ALL_110_STRIDE 1
#define IBU_P2_CETUS_ALL_110_DEPTH  1

#define IBU_P2_CETUS_ALL_111_ADDR   0x011c0f6fL
#define IBU_P2_CETUS_ALL_111_STRIDE 1
#define IBU_P2_CETUS_ALL_111_DEPTH  1

#define IBU_P2_CETUS_ALL_112_ADDR   0x011c0f70L
#define IBU_P2_CETUS_ALL_112_STRIDE 1
#define IBU_P2_CETUS_ALL_112_DEPTH  1

#define IBU_P2_CETUS_ALL_113_ADDR   0x011c0f71L
#define IBU_P2_CETUS_ALL_113_STRIDE 1
#define IBU_P2_CETUS_ALL_113_DEPTH  1

#define IBU_P2_CETUS_ALL_114_ADDR   0x011c0f72L
#define IBU_P2_CETUS_ALL_114_STRIDE 1
#define IBU_P2_CETUS_ALL_114_DEPTH  1

#define IBU_P2_CETUS_ALL_115_ADDR   0x011c0f73L
#define IBU_P2_CETUS_ALL_115_STRIDE 1
#define IBU_P2_CETUS_ALL_115_DEPTH  1

#define IBU_P2_CETUS_ALL_116_ADDR   0x011c0f74L
#define IBU_P2_CETUS_ALL_116_STRIDE 1
#define IBU_P2_CETUS_ALL_116_DEPTH  1

#define IBU_P2_CETUS_ALL_117_ADDR   0x011c0f75L
#define IBU_P2_CETUS_ALL_117_STRIDE 1
#define IBU_P2_CETUS_ALL_117_DEPTH  1

#define IBU_P2_CETUS_ALL_118_ADDR   0x011c0f76L
#define IBU_P2_CETUS_ALL_118_STRIDE 1
#define IBU_P2_CETUS_ALL_118_DEPTH  1

#define IBU_P2_CETUS_ALL_119_ADDR   0x011c0f77L
#define IBU_P2_CETUS_ALL_119_STRIDE 1
#define IBU_P2_CETUS_ALL_119_DEPTH  1

#define IBU_P2_CETUS_ALL_120_ADDR   0x011c0f78L
#define IBU_P2_CETUS_ALL_120_STRIDE 1
#define IBU_P2_CETUS_ALL_120_DEPTH  1

#define IBU_P2_CETUS_ALL_121_ADDR   0x011c0f79L
#define IBU_P2_CETUS_ALL_121_STRIDE 1
#define IBU_P2_CETUS_ALL_121_DEPTH  1

#define IBU_P2_CETUS_ALL_122_ADDR   0x011c0f7aL
#define IBU_P2_CETUS_ALL_122_STRIDE 1
#define IBU_P2_CETUS_ALL_122_DEPTH  1

#define IBU_P2_CETUS_ALL_123_ADDR   0x011c0f7bL
#define IBU_P2_CETUS_ALL_123_STRIDE 1
#define IBU_P2_CETUS_ALL_123_DEPTH  1

#define IBU_P2_CETUS_ALL_124_ADDR   0x011c0f7cL
#define IBU_P2_CETUS_ALL_124_STRIDE 1
#define IBU_P2_CETUS_ALL_124_DEPTH  1

#define IBU_P2_CETUS_ALL_125_ADDR   0x011c0f7dL
#define IBU_P2_CETUS_ALL_125_STRIDE 1
#define IBU_P2_CETUS_ALL_125_DEPTH  1

#define IBU_P2_CETUS_ALL_126_ADDR   0x011c0f7eL
#define IBU_P2_CETUS_ALL_126_STRIDE 1
#define IBU_P2_CETUS_ALL_126_DEPTH  1

#define IBU_P2_CETUS_ALL_127_ADDR   0x011c0f7fL
#define IBU_P2_CETUS_ALL_127_STRIDE 1
#define IBU_P2_CETUS_ALL_127_DEPTH  1

#define IBU_P2_CETUS_ALL_128_ADDR   0x011c0f80L
#define IBU_P2_CETUS_ALL_128_STRIDE 1
#define IBU_P2_CETUS_ALL_128_DEPTH  1

#define IBU_P2_CETUS_ALL_129_ADDR   0x011c0f81L
#define IBU_P2_CETUS_ALL_129_STRIDE 1
#define IBU_P2_CETUS_ALL_129_DEPTH  1

#define IBU_P2_CETUS_ALL_130_ADDR   0x011c0f82L
#define IBU_P2_CETUS_ALL_130_STRIDE 1
#define IBU_P2_CETUS_ALL_130_DEPTH  1

#define IBU_P2_CETUS_ALL_131_ADDR   0x011c0f83L
#define IBU_P2_CETUS_ALL_131_STRIDE 1
#define IBU_P2_CETUS_ALL_131_DEPTH  1

#define IBU_P2_CETUS_ALL_132_ADDR   0x011c0f84L
#define IBU_P2_CETUS_ALL_132_STRIDE 1
#define IBU_P2_CETUS_ALL_132_DEPTH  1

#define IBU_P2_CETUS_ALL_133_ADDR   0x011c0f85L
#define IBU_P2_CETUS_ALL_133_STRIDE 1
#define IBU_P2_CETUS_ALL_133_DEPTH  1

#define IBU_P2_CETUS_ALL_134_ADDR   0x011c0f86L
#define IBU_P2_CETUS_ALL_134_STRIDE 1
#define IBU_P2_CETUS_ALL_134_DEPTH  1

#define IBU_P2_CETUS_ALL_135_ADDR   0x011c0f87L
#define IBU_P2_CETUS_ALL_135_STRIDE 1
#define IBU_P2_CETUS_ALL_135_DEPTH  1

#define IBU_P2_CETUS_ALL_136_ADDR   0x011c0f88L
#define IBU_P2_CETUS_ALL_136_STRIDE 1
#define IBU_P2_CETUS_ALL_136_DEPTH  1

#define IBU_P2_CETUS_ALL_137_ADDR   0x011c0f89L
#define IBU_P2_CETUS_ALL_137_STRIDE 1
#define IBU_P2_CETUS_ALL_137_DEPTH  1

#define IBU_P2_CETUS_ALL_138_ADDR   0x011c0f8aL
#define IBU_P2_CETUS_ALL_138_STRIDE 1
#define IBU_P2_CETUS_ALL_138_DEPTH  1

#define IBU_P2_CETUS_ALL_139_ADDR   0x011c0f8bL
#define IBU_P2_CETUS_ALL_139_STRIDE 1
#define IBU_P2_CETUS_ALL_139_DEPTH  1

#define IBU_P2_PMA_RESET_CSR_ADDR   0x011e0000L
#define IBU_P2_PMA_RESET_CSR_STRIDE 1
#define IBU_P2_PMA_RESET_CSR_DEPTH  1

#define IBU_P2_PMA_PLLA_CSR_ADDR   0x011e0001L
#define IBU_P2_PMA_PLLA_CSR_STRIDE 1
#define IBU_P2_PMA_PLLA_CSR_DEPTH  1

#define IBU_P2_PMA_PLLB_CSR_ADDR   0x011e0002L
#define IBU_P2_PMA_PLLB_CSR_STRIDE 1
#define IBU_P2_PMA_PLLB_CSR_DEPTH  1

#define IBU_P2_PMA_CMODE_CSR_ADDR   0x011e0003L
#define IBU_P2_PMA_CMODE_CSR_STRIDE 1
#define IBU_P2_PMA_CMODE_CSR_DEPTH  1

#define IBU_P2_PMA_LB_CSR_ADDR   0x011e0004L
#define IBU_P2_PMA_LB_CSR_STRIDE 1
#define IBU_P2_PMA_LB_CSR_DEPTH  1

#define IBU_P2_PMA_PWR_CSR_ADDR   0x011e0005L
#define IBU_P2_PMA_PWR_CSR_STRIDE 1
#define IBU_P2_PMA_PWR_CSR_DEPTH  1

#define IBU_P2_PMA_STATUS0_CSR_ADDR   0x011e0006L
#define IBU_P2_PMA_STATUS0_CSR_STRIDE 1
#define IBU_P2_PMA_STATUS0_CSR_DEPTH  1

#define IBU_P2_PMA_STATUS1_CSR_ADDR   0x011e0007L
#define IBU_P2_PMA_STATUS1_CSR_STRIDE 1
#define IBU_P2_PMA_STATUS1_CSR_DEPTH  1

#define IBU_P2_PMA_STATUS2_CSR_ADDR   0x011e0008L
#define IBU_P2_PMA_STATUS2_CSR_STRIDE 1
#define IBU_P2_PMA_STATUS2_CSR_DEPTH  1

#define IBU_P2_PMA_TXWCLK0_CNT_CSR_ADDR   0x011e0009L
#define IBU_P2_PMA_TXWCLK0_CNT_CSR_STRIDE 1
#define IBU_P2_PMA_TXWCLK0_CNT_CSR_DEPTH  1

#define IBU_P2_PMA_TXWCLK0_CNT_VAL_ADDR   0x011e000aL
#define IBU_P2_PMA_TXWCLK0_CNT_VAL_STRIDE 1
#define IBU_P2_PMA_TXWCLK0_CNT_VAL_DEPTH  1

#define IBU_P2_PMA_RXWCLK0_CNT_CSR_ADDR   0x011e000bL
#define IBU_P2_PMA_RXWCLK0_CNT_CSR_STRIDE 1
#define IBU_P2_PMA_RXWCLK0_CNT_CSR_DEPTH  1

#define IBU_P2_PMA_RXWCLK0_CNT_VAL_ADDR   0x011e000cL
#define IBU_P2_PMA_RXWCLK0_CNT_VAL_STRIDE 1
#define IBU_P2_PMA_RXWCLK0_CNT_VAL_DEPTH  1

#define IBU_P2_PMA_IRQ_STATUS_CSR_ADDR   0x011e000dL
#define IBU_P2_PMA_IRQ_STATUS_CSR_STRIDE 1
#define IBU_P2_PMA_IRQ_STATUS_CSR_DEPTH  1

#define IBU_P2_PMA_IRQ_MASK_CSR_ADDR   0x011e000eL
#define IBU_P2_PMA_IRQ_MASK_CSR_STRIDE 1
#define IBU_P2_PMA_IRQ_MASK_CSR_DEPTH  1

#define IBU_P2_PMA_BAD_CSR_ADDR   0x011efbadL
#define IBU_P2_PMA_BAD_CSR_STRIDE 1
#define IBU_P2_PMA_BAD_CSR_DEPTH  1

#define PEU_P_REQ_CREDIT_REG0_ADDR   0x01200000L
#define PEU_P_REQ_CREDIT_REG0_STRIDE 1
#define PEU_P_REQ_CREDIT_REG0_DEPTH  1

#define PEU_NP_REQ_CREDIT_REG0_ADDR   0x01200001L
#define PEU_NP_REQ_CREDIT_REG0_STRIDE 1
#define PEU_NP_REQ_CREDIT_REG0_DEPTH  1

#define PEU_P_RETURN_CREDIT_REG0_ADDR   0x01200002L
#define PEU_P_RETURN_CREDIT_REG0_STRIDE 1
#define PEU_P_RETURN_CREDIT_REG0_DEPTH  1

#define PEU_NP_RETURN_CREDIT_REG0_ADDR   0x01200003L
#define PEU_NP_RETURN_CREDIT_REG0_STRIDE 1
#define PEU_NP_RETURN_CREDIT_REG0_DEPTH  1

#define PEU_P_RETURN_INTERVAL_REG0_ADDR   0x01200004L
#define PEU_P_RETURN_INTERVAL_REG0_STRIDE 1
#define PEU_P_RETURN_INTERVAL_REG0_DEPTH  1

#define PEU_NP_RETURN_INTERVAL_REG0_ADDR   0x01200005L
#define PEU_NP_RETURN_INTERVAL_REG0_STRIDE 1
#define PEU_NP_RETURN_INTERVAL_REG0_DEPTH  1

#define PEU_Q_NP_TAG_CNT_THLD0_ADDR   0x01200006L
#define PEU_Q_NP_TAG_CNT_THLD0_STRIDE 1
#define PEU_Q_NP_TAG_CNT_THLD0_DEPTH  1

#define PEU_XADM_PH_CDTS_THLD0_ADDR   0x01200007L
#define PEU_XADM_PH_CDTS_THLD0_STRIDE 1
#define PEU_XADM_PH_CDTS_THLD0_DEPTH  1

#define PEU_XADM_PD_CDTS_THLD0_ADDR   0x01200008L
#define PEU_XADM_PD_CDTS_THLD0_STRIDE 1
#define PEU_XADM_PD_CDTS_THLD0_DEPTH  1

#define PEU_XADM_NPH_CDTS_THLD0_ADDR   0x01200009L
#define PEU_XADM_NPH_CDTS_THLD0_STRIDE 1
#define PEU_XADM_NPH_CDTS_THLD0_DEPTH  1

#define PEU_XADM_NPD_CDTS_THLD0_ADDR   0x0120000aL
#define PEU_XADM_NPD_CDTS_THLD0_STRIDE 1
#define PEU_XADM_NPD_CDTS_THLD0_DEPTH  1

#define PEU_P_REQ_CREDIT_REG1_ADDR   0x0120000bL
#define PEU_P_REQ_CREDIT_REG1_STRIDE 1
#define PEU_P_REQ_CREDIT_REG1_DEPTH  1

#define PEU_NP_REQ_CREDIT_REG1_ADDR   0x0120000cL
#define PEU_NP_REQ_CREDIT_REG1_STRIDE 1
#define PEU_NP_REQ_CREDIT_REG1_DEPTH  1

#define PEU_P_RETURN_CREDIT_REG1_ADDR   0x0120000dL
#define PEU_P_RETURN_CREDIT_REG1_STRIDE 1
#define PEU_P_RETURN_CREDIT_REG1_DEPTH  1

#define PEU_NP_RETURN_CREDIT_REG1_ADDR   0x0120000eL
#define PEU_NP_RETURN_CREDIT_REG1_STRIDE 1
#define PEU_NP_RETURN_CREDIT_REG1_DEPTH  1

#define PEU_P_RETURN_INTERVAL_REG1_ADDR   0x0120000fL
#define PEU_P_RETURN_INTERVAL_REG1_STRIDE 1
#define PEU_P_RETURN_INTERVAL_REG1_DEPTH  1

#define PEU_NP_RETURN_INTERVAL_REG1_ADDR   0x01200010L
#define PEU_NP_RETURN_INTERVAL_REG1_STRIDE 1
#define PEU_NP_RETURN_INTERVAL_REG1_DEPTH  1

#define PEU_Q_NP_TAG_CNT_THLD1_ADDR   0x01200011L
#define PEU_Q_NP_TAG_CNT_THLD1_STRIDE 1
#define PEU_Q_NP_TAG_CNT_THLD1_DEPTH  1

#define PEU_XADM_PH_CDTS_THLD1_ADDR   0x01200012L
#define PEU_XADM_PH_CDTS_THLD1_STRIDE 1
#define PEU_XADM_PH_CDTS_THLD1_DEPTH  1

#define PEU_XADM_PD_CDTS_THLD1_ADDR   0x01200013L
#define PEU_XADM_PD_CDTS_THLD1_STRIDE 1
#define PEU_XADM_PD_CDTS_THLD1_DEPTH  1

#define PEU_XADM_NPH_CDTS_THLD1_ADDR   0x01200014L
#define PEU_XADM_NPH_CDTS_THLD1_STRIDE 1
#define PEU_XADM_NPH_CDTS_THLD1_DEPTH  1

#define PEU_XADM_NPD_CDTS_THLD1_ADDR   0x01200015L
#define PEU_XADM_NPD_CDTS_THLD1_STRIDE 1
#define PEU_XADM_NPD_CDTS_THLD1_DEPTH  1

#define PEU_P_REQ_CREDIT_REG2_ADDR   0x01200016L
#define PEU_P_REQ_CREDIT_REG2_STRIDE 1
#define PEU_P_REQ_CREDIT_REG2_DEPTH  1

#define PEU_NP_REQ_CREDIT_REG2_ADDR   0x01200017L
#define PEU_NP_REQ_CREDIT_REG2_STRIDE 1
#define PEU_NP_REQ_CREDIT_REG2_DEPTH  1

#define PEU_P_RETURN_CREDIT_REG2_ADDR   0x01200018L
#define PEU_P_RETURN_CREDIT_REG2_STRIDE 1
#define PEU_P_RETURN_CREDIT_REG2_DEPTH  1

#define PEU_NP_RETURN_CREDIT_REG2_ADDR   0x01200019L
#define PEU_NP_RETURN_CREDIT_REG2_STRIDE 1
#define PEU_NP_RETURN_CREDIT_REG2_DEPTH  1

#define PEU_P_RETURN_INTERVAL_REG2_ADDR   0x0120001aL
#define PEU_P_RETURN_INTERVAL_REG2_STRIDE 1
#define PEU_P_RETURN_INTERVAL_REG2_DEPTH  1

#define PEU_NP_RETURN_INTERVAL_REG2_ADDR   0x0120001bL
#define PEU_NP_RETURN_INTERVAL_REG2_STRIDE 1
#define PEU_NP_RETURN_INTERVAL_REG2_DEPTH  1

#define PEU_Q_NP_TAG_CNT_THLD2_ADDR   0x0120001cL
#define PEU_Q_NP_TAG_CNT_THLD2_STRIDE 1
#define PEU_Q_NP_TAG_CNT_THLD2_DEPTH  1

#define PEU_XADM_PH_CDTS_THLD2_ADDR   0x0120001dL
#define PEU_XADM_PH_CDTS_THLD2_STRIDE 1
#define PEU_XADM_PH_CDTS_THLD2_DEPTH  1

#define PEU_XADM_PD_CDTS_THLD2_ADDR   0x0120001eL
#define PEU_XADM_PD_CDTS_THLD2_STRIDE 1
#define PEU_XADM_PD_CDTS_THLD2_DEPTH  1

#define PEU_XADM_NPH_CDTS_THLD2_ADDR   0x0120001fL
#define PEU_XADM_NPH_CDTS_THLD2_STRIDE 1
#define PEU_XADM_NPH_CDTS_THLD2_DEPTH  1

#define PEU_XADM_NPD_CDTS_THLD2_ADDR   0x01200020L
#define PEU_XADM_NPD_CDTS_THLD2_STRIDE 1
#define PEU_XADM_NPD_CDTS_THLD2_DEPTH  1

#define PEU_P_REQ_CREDIT_REG3_ADDR   0x01200021L
#define PEU_P_REQ_CREDIT_REG3_STRIDE 1
#define PEU_P_REQ_CREDIT_REG3_DEPTH  1

#define PEU_NP_REQ_CREDIT_REG3_ADDR   0x01200022L
#define PEU_NP_REQ_CREDIT_REG3_STRIDE 1
#define PEU_NP_REQ_CREDIT_REG3_DEPTH  1

#define PEU_P_RETURN_CREDIT_REG3_ADDR   0x01200023L
#define PEU_P_RETURN_CREDIT_REG3_STRIDE 1
#define PEU_P_RETURN_CREDIT_REG3_DEPTH  1

#define PEU_NP_RETURN_CREDIT_REG3_ADDR   0x01200024L
#define PEU_NP_RETURN_CREDIT_REG3_STRIDE 1
#define PEU_NP_RETURN_CREDIT_REG3_DEPTH  1

#define PEU_P_RETURN_INTERVAL_REG3_ADDR   0x01200025L
#define PEU_P_RETURN_INTERVAL_REG3_STRIDE 1
#define PEU_P_RETURN_INTERVAL_REG3_DEPTH  1

#define PEU_NP_RETURN_INTERVAL_REG3_ADDR   0x01200026L
#define PEU_NP_RETURN_INTERVAL_REG3_STRIDE 1
#define PEU_NP_RETURN_INTERVAL_REG3_DEPTH  1

#define PEU_Q_NP_TAG_CNT_THLD3_ADDR   0x01200027L
#define PEU_Q_NP_TAG_CNT_THLD3_STRIDE 1
#define PEU_Q_NP_TAG_CNT_THLD3_DEPTH  1

#define PEU_XADM_PH_CDTS_THLD3_ADDR   0x01200028L
#define PEU_XADM_PH_CDTS_THLD3_STRIDE 1
#define PEU_XADM_PH_CDTS_THLD3_DEPTH  1

#define PEU_XADM_PD_CDTS_THLD3_ADDR   0x01200029L
#define PEU_XADM_PD_CDTS_THLD3_STRIDE 1
#define PEU_XADM_PD_CDTS_THLD3_DEPTH  1

#define PEU_XADM_NPH_CDTS_THLD3_ADDR   0x0120002aL
#define PEU_XADM_NPH_CDTS_THLD3_STRIDE 1
#define PEU_XADM_NPH_CDTS_THLD3_DEPTH  1

#define PEU_XADM_NPD_CDTS_THLD3_ADDR   0x0120002bL
#define PEU_XADM_NPD_CDTS_THLD3_STRIDE 1
#define PEU_XADM_NPD_CDTS_THLD3_DEPTH  1

#define PEU_P_REQ_CREDIT_REG4_ADDR   0x0120002cL
#define PEU_P_REQ_CREDIT_REG4_STRIDE 1
#define PEU_P_REQ_CREDIT_REG4_DEPTH  1

#define PEU_NP_REQ_CREDIT_REG4_ADDR   0x0120002dL
#define PEU_NP_REQ_CREDIT_REG4_STRIDE 1
#define PEU_NP_REQ_CREDIT_REG4_DEPTH  1

#define PEU_P_RETURN_CREDIT_REG4_ADDR   0x0120002eL
#define PEU_P_RETURN_CREDIT_REG4_STRIDE 1
#define PEU_P_RETURN_CREDIT_REG4_DEPTH  1

#define PEU_NP_RETURN_CREDIT_REG4_ADDR   0x0120002fL
#define PEU_NP_RETURN_CREDIT_REG4_STRIDE 1
#define PEU_NP_RETURN_CREDIT_REG4_DEPTH  1

#define PEU_P_RETURN_INTERVAL_REG4_ADDR   0x01200030L
#define PEU_P_RETURN_INTERVAL_REG4_STRIDE 1
#define PEU_P_RETURN_INTERVAL_REG4_DEPTH  1

#define PEU_NP_RETURN_INTERVAL_REG4_ADDR   0x01200031L
#define PEU_NP_RETURN_INTERVAL_REG4_STRIDE 1
#define PEU_NP_RETURN_INTERVAL_REG4_DEPTH  1

#define PEU_Q_NP_TAG_CNT_THLD4_ADDR   0x01200032L
#define PEU_Q_NP_TAG_CNT_THLD4_STRIDE 1
#define PEU_Q_NP_TAG_CNT_THLD4_DEPTH  1

#define PEU_XADM_PH_CDTS_THLD4_ADDR   0x01200033L
#define PEU_XADM_PH_CDTS_THLD4_STRIDE 1
#define PEU_XADM_PH_CDTS_THLD4_DEPTH  1

#define PEU_XADM_PD_CDTS_THLD4_ADDR   0x01200034L
#define PEU_XADM_PD_CDTS_THLD4_STRIDE 1
#define PEU_XADM_PD_CDTS_THLD4_DEPTH  1

#define PEU_XADM_NPH_CDTS_THLD4_ADDR   0x01200035L
#define PEU_XADM_NPH_CDTS_THLD4_STRIDE 1
#define PEU_XADM_NPH_CDTS_THLD4_DEPTH  1

#define PEU_XADM_NPD_CDTS_THLD4_ADDR   0x01200036L
#define PEU_XADM_NPD_CDTS_THLD4_STRIDE 1
#define PEU_XADM_NPD_CDTS_THLD4_DEPTH  1

#define PEU_P_REQ_CREDIT_REG5_ADDR   0x01200037L
#define PEU_P_REQ_CREDIT_REG5_STRIDE 1
#define PEU_P_REQ_CREDIT_REG5_DEPTH  1

#define PEU_NP_REQ_CREDIT_REG5_ADDR   0x01200038L
#define PEU_NP_REQ_CREDIT_REG5_STRIDE 1
#define PEU_NP_REQ_CREDIT_REG5_DEPTH  1

#define PEU_P_RETURN_CREDIT_REG5_ADDR   0x01200039L
#define PEU_P_RETURN_CREDIT_REG5_STRIDE 1
#define PEU_P_RETURN_CREDIT_REG5_DEPTH  1

#define PEU_NP_RETURN_CREDIT_REG5_ADDR   0x0120003aL
#define PEU_NP_RETURN_CREDIT_REG5_STRIDE 1
#define PEU_NP_RETURN_CREDIT_REG5_DEPTH  1

#define PEU_P_RETURN_INTERVAL_REG5_ADDR   0x0120003bL
#define PEU_P_RETURN_INTERVAL_REG5_STRIDE 1
#define PEU_P_RETURN_INTERVAL_REG5_DEPTH  1

#define PEU_NP_RETURN_INTERVAL_REG5_ADDR   0x0120003cL
#define PEU_NP_RETURN_INTERVAL_REG5_STRIDE 1
#define PEU_NP_RETURN_INTERVAL_REG5_DEPTH  1

#define PEU_Q_NP_TAG_CNT_THLD5_ADDR   0x0120003dL
#define PEU_Q_NP_TAG_CNT_THLD5_STRIDE 1
#define PEU_Q_NP_TAG_CNT_THLD5_DEPTH  1

#define PEU_XADM_PH_CDTS_THLD5_ADDR   0x0120003eL
#define PEU_XADM_PH_CDTS_THLD5_STRIDE 1
#define PEU_XADM_PH_CDTS_THLD5_DEPTH  1

#define PEU_XADM_PD_CDTS_THLD5_ADDR   0x0120003fL
#define PEU_XADM_PD_CDTS_THLD5_STRIDE 1
#define PEU_XADM_PD_CDTS_THLD5_DEPTH  1

#define PEU_XADM_NPH_CDTS_THLD5_ADDR   0x01200040L
#define PEU_XADM_NPH_CDTS_THLD5_STRIDE 1
#define PEU_XADM_NPH_CDTS_THLD5_DEPTH  1

#define PEU_XADM_NPD_CDTS_THLD5_ADDR   0x01200041L
#define PEU_XADM_NPD_CDTS_THLD5_STRIDE 1
#define PEU_XADM_NPD_CDTS_THLD5_DEPTH  1

#define PEU_P_REQ_CREDIT_REG6_ADDR   0x01200042L
#define PEU_P_REQ_CREDIT_REG6_STRIDE 1
#define PEU_P_REQ_CREDIT_REG6_DEPTH  1

#define PEU_NP_REQ_CREDIT_REG6_ADDR   0x01200043L
#define PEU_NP_REQ_CREDIT_REG6_STRIDE 1
#define PEU_NP_REQ_CREDIT_REG6_DEPTH  1

#define PEU_P_RETURN_CREDIT_REG6_ADDR   0x01200044L
#define PEU_P_RETURN_CREDIT_REG6_STRIDE 1
#define PEU_P_RETURN_CREDIT_REG6_DEPTH  1

#define PEU_NP_RETURN_CREDIT_REG6_ADDR   0x01200045L
#define PEU_NP_RETURN_CREDIT_REG6_STRIDE 1
#define PEU_NP_RETURN_CREDIT_REG6_DEPTH  1

#define PEU_P_RETURN_INTERVAL_REG6_ADDR   0x01200046L
#define PEU_P_RETURN_INTERVAL_REG6_STRIDE 1
#define PEU_P_RETURN_INTERVAL_REG6_DEPTH  1

#define PEU_NP_RETURN_INTERVAL_REG6_ADDR   0x01200047L
#define PEU_NP_RETURN_INTERVAL_REG6_STRIDE 1
#define PEU_NP_RETURN_INTERVAL_REG6_DEPTH  1

#define PEU_Q_NP_TAG_CNT_THLD6_ADDR   0x01200048L
#define PEU_Q_NP_TAG_CNT_THLD6_STRIDE 1
#define PEU_Q_NP_TAG_CNT_THLD6_DEPTH  1

#define PEU_XADM_PH_CDTS_THLD6_ADDR   0x01200049L
#define PEU_XADM_PH_CDTS_THLD6_STRIDE 1
#define PEU_XADM_PH_CDTS_THLD6_DEPTH  1

#define PEU_XADM_PD_CDTS_THLD6_ADDR   0x0120004aL
#define PEU_XADM_PD_CDTS_THLD6_STRIDE 1
#define PEU_XADM_PD_CDTS_THLD6_DEPTH  1

#define PEU_XADM_NPH_CDTS_THLD6_ADDR   0x0120004bL
#define PEU_XADM_NPH_CDTS_THLD6_STRIDE 1
#define PEU_XADM_NPH_CDTS_THLD6_DEPTH  1

#define PEU_XADM_NPD_CDTS_THLD6_ADDR   0x0120004cL
#define PEU_XADM_NPD_CDTS_THLD6_STRIDE 1
#define PEU_XADM_NPD_CDTS_THLD6_DEPTH  1

#define PEU_P_REQ_CREDIT_REG7_ADDR   0x0120004dL
#define PEU_P_REQ_CREDIT_REG7_STRIDE 1
#define PEU_P_REQ_CREDIT_REG7_DEPTH  1

#define PEU_NP_REQ_CREDIT_REG7_ADDR   0x0120004eL
#define PEU_NP_REQ_CREDIT_REG7_STRIDE 1
#define PEU_NP_REQ_CREDIT_REG7_DEPTH  1

#define PEU_P_RETURN_CREDIT_REG7_ADDR   0x0120004fL
#define PEU_P_RETURN_CREDIT_REG7_STRIDE 1
#define PEU_P_RETURN_CREDIT_REG7_DEPTH  1

#define PEU_NP_RETURN_CREDIT_REG7_ADDR   0x01200050L
#define PEU_NP_RETURN_CREDIT_REG7_STRIDE 1
#define PEU_NP_RETURN_CREDIT_REG7_DEPTH  1

#define PEU_P_RETURN_INTERVAL_REG7_ADDR   0x01200051L
#define PEU_P_RETURN_INTERVAL_REG7_STRIDE 1
#define PEU_P_RETURN_INTERVAL_REG7_DEPTH  1

#define PEU_NP_RETURN_INTERVAL_REG7_ADDR   0x01200052L
#define PEU_NP_RETURN_INTERVAL_REG7_STRIDE 1
#define PEU_NP_RETURN_INTERVAL_REG7_DEPTH  1

#define PEU_Q_NP_TAG_CNT_THLD7_ADDR   0x01200053L
#define PEU_Q_NP_TAG_CNT_THLD7_STRIDE 1
#define PEU_Q_NP_TAG_CNT_THLD7_DEPTH  1

#define PEU_XADM_PH_CDTS_THLD7_ADDR   0x01200054L
#define PEU_XADM_PH_CDTS_THLD7_STRIDE 1
#define PEU_XADM_PH_CDTS_THLD7_DEPTH  1

#define PEU_XADM_PD_CDTS_THLD7_ADDR   0x01200055L
#define PEU_XADM_PD_CDTS_THLD7_STRIDE 1
#define PEU_XADM_PD_CDTS_THLD7_DEPTH  1

#define PEU_XADM_NPH_CDTS_THLD7_ADDR   0x01200056L
#define PEU_XADM_NPH_CDTS_THLD7_STRIDE 1
#define PEU_XADM_NPH_CDTS_THLD7_DEPTH  1

#define PEU_XADM_NPD_CDTS_THLD7_ADDR   0x01200057L
#define PEU_XADM_NPD_CDTS_THLD7_STRIDE 1
#define PEU_XADM_NPD_CDTS_THLD7_DEPTH  1

#define PEU_P_REQ_CREDIT_REG8_ADDR   0x01200058L
#define PEU_P_REQ_CREDIT_REG8_STRIDE 1
#define PEU_P_REQ_CREDIT_REG8_DEPTH  1

#define PEU_NP_REQ_CREDIT_REG8_ADDR   0x01200059L
#define PEU_NP_REQ_CREDIT_REG8_STRIDE 1
#define PEU_NP_REQ_CREDIT_REG8_DEPTH  1

#define PEU_P_RETURN_CREDIT_REG8_ADDR   0x0120005aL
#define PEU_P_RETURN_CREDIT_REG8_STRIDE 1
#define PEU_P_RETURN_CREDIT_REG8_DEPTH  1

#define PEU_NP_RETURN_CREDIT_REG8_ADDR   0x0120005bL
#define PEU_NP_RETURN_CREDIT_REG8_STRIDE 1
#define PEU_NP_RETURN_CREDIT_REG8_DEPTH  1

#define PEU_P_RETURN_INTERVAL_REG8_ADDR   0x0120005cL
#define PEU_P_RETURN_INTERVAL_REG8_STRIDE 1
#define PEU_P_RETURN_INTERVAL_REG8_DEPTH  1

#define PEU_NP_RETURN_INTERVAL_REG8_ADDR   0x0120005dL
#define PEU_NP_RETURN_INTERVAL_REG8_STRIDE 1
#define PEU_NP_RETURN_INTERVAL_REG8_DEPTH  1

#define PEU_Q_NP_TAG_CNT_THLD8_ADDR   0x0120005eL
#define PEU_Q_NP_TAG_CNT_THLD8_STRIDE 1
#define PEU_Q_NP_TAG_CNT_THLD8_DEPTH  1

#define PEU_XADM_PH_CDTS_THLD8_ADDR   0x0120005fL
#define PEU_XADM_PH_CDTS_THLD8_STRIDE 1
#define PEU_XADM_PH_CDTS_THLD8_DEPTH  1

#define PEU_XADM_PD_CDTS_THLD8_ADDR   0x01200060L
#define PEU_XADM_PD_CDTS_THLD8_STRIDE 1
#define PEU_XADM_PD_CDTS_THLD8_DEPTH  1

#define PEU_XADM_NPH_CDTS_THLD8_ADDR   0x01200061L
#define PEU_XADM_NPH_CDTS_THLD8_STRIDE 1
#define PEU_XADM_NPH_CDTS_THLD8_DEPTH  1

#define PEU_XADM_NPD_CDTS_THLD8_ADDR   0x01200062L
#define PEU_XADM_NPD_CDTS_THLD8_STRIDE 1
#define PEU_XADM_NPD_CDTS_THLD8_DEPTH  1

#define PEU_P_REQ_CREDIT_REG9_ADDR   0x01200063L
#define PEU_P_REQ_CREDIT_REG9_STRIDE 1
#define PEU_P_REQ_CREDIT_REG9_DEPTH  1

#define PEU_NP_REQ_CREDIT_REG9_ADDR   0x01200064L
#define PEU_NP_REQ_CREDIT_REG9_STRIDE 1
#define PEU_NP_REQ_CREDIT_REG9_DEPTH  1

#define PEU_P_RETURN_CREDIT_REG9_ADDR   0x01200065L
#define PEU_P_RETURN_CREDIT_REG9_STRIDE 1
#define PEU_P_RETURN_CREDIT_REG9_DEPTH  1

#define PEU_NP_RETURN_CREDIT_REG9_ADDR   0x01200066L
#define PEU_NP_RETURN_CREDIT_REG9_STRIDE 1
#define PEU_NP_RETURN_CREDIT_REG9_DEPTH  1

#define PEU_P_RETURN_INTERVAL_REG9_ADDR   0x01200067L
#define PEU_P_RETURN_INTERVAL_REG9_STRIDE 1
#define PEU_P_RETURN_INTERVAL_REG9_DEPTH  1

#define PEU_NP_RETURN_INTERVAL_REG9_ADDR   0x01200068L
#define PEU_NP_RETURN_INTERVAL_REG9_STRIDE 1
#define PEU_NP_RETURN_INTERVAL_REG9_DEPTH  1

#define PEU_Q_NP_TAG_CNT_THLD9_ADDR   0x01200069L
#define PEU_Q_NP_TAG_CNT_THLD9_STRIDE 1
#define PEU_Q_NP_TAG_CNT_THLD9_DEPTH  1

#define PEU_XADM_PH_CDTS_THLD9_ADDR   0x0120006aL
#define PEU_XADM_PH_CDTS_THLD9_STRIDE 1
#define PEU_XADM_PH_CDTS_THLD9_DEPTH  1

#define PEU_XADM_PD_CDTS_THLD9_ADDR   0x0120006bL
#define PEU_XADM_PD_CDTS_THLD9_STRIDE 1
#define PEU_XADM_PD_CDTS_THLD9_DEPTH  1

#define PEU_XADM_NPH_CDTS_THLD9_ADDR   0x0120006cL
#define PEU_XADM_NPH_CDTS_THLD9_STRIDE 1
#define PEU_XADM_NPH_CDTS_THLD9_DEPTH  1

#define PEU_XADM_NPD_CDTS_THLD9_ADDR   0x0120006dL
#define PEU_XADM_NPD_CDTS_THLD9_STRIDE 1
#define PEU_XADM_NPD_CDTS_THLD9_DEPTH  1

#define PEU_P_REQ_CREDIT_REG10_ADDR   0x0120006eL
#define PEU_P_REQ_CREDIT_REG10_STRIDE 1
#define PEU_P_REQ_CREDIT_REG10_DEPTH  1

#define PEU_NP_REQ_CREDIT_REG10_ADDR   0x0120006fL
#define PEU_NP_REQ_CREDIT_REG10_STRIDE 1
#define PEU_NP_REQ_CREDIT_REG10_DEPTH  1

#define PEU_P_RETURN_CREDIT_REG10_ADDR   0x01200070L
#define PEU_P_RETURN_CREDIT_REG10_STRIDE 1
#define PEU_P_RETURN_CREDIT_REG10_DEPTH  1

#define PEU_NP_RETURN_CREDIT_REG10_ADDR   0x01200071L
#define PEU_NP_RETURN_CREDIT_REG10_STRIDE 1
#define PEU_NP_RETURN_CREDIT_REG10_DEPTH  1

#define PEU_P_RETURN_INTERVAL_REG10_ADDR   0x01200072L
#define PEU_P_RETURN_INTERVAL_REG10_STRIDE 1
#define PEU_P_RETURN_INTERVAL_REG10_DEPTH  1

#define PEU_NP_RETURN_INTERVAL_REG10_ADDR   0x01200073L
#define PEU_NP_RETURN_INTERVAL_REG10_STRIDE 1
#define PEU_NP_RETURN_INTERVAL_REG10_DEPTH  1

#define PEU_Q_NP_TAG_CNT_THLD10_ADDR   0x01200074L
#define PEU_Q_NP_TAG_CNT_THLD10_STRIDE 1
#define PEU_Q_NP_TAG_CNT_THLD10_DEPTH  1

#define PEU_XADM_PH_CDTS_THLD10_ADDR   0x01200075L
#define PEU_XADM_PH_CDTS_THLD10_STRIDE 1
#define PEU_XADM_PH_CDTS_THLD10_DEPTH  1

#define PEU_XADM_PD_CDTS_THLD10_ADDR   0x01200076L
#define PEU_XADM_PD_CDTS_THLD10_STRIDE 1
#define PEU_XADM_PD_CDTS_THLD10_DEPTH  1

#define PEU_XADM_NPH_CDTS_THLD10_ADDR   0x01200077L
#define PEU_XADM_NPH_CDTS_THLD10_STRIDE 1
#define PEU_XADM_NPH_CDTS_THLD10_DEPTH  1

#define PEU_XADM_NPD_CDTS_THLD10_ADDR   0x01200078L
#define PEU_XADM_NPD_CDTS_THLD10_STRIDE 1
#define PEU_XADM_NPD_CDTS_THLD10_DEPTH  1

#define PEU_P_REQ_CREDIT_REG11_ADDR   0x01200079L
#define PEU_P_REQ_CREDIT_REG11_STRIDE 1
#define PEU_P_REQ_CREDIT_REG11_DEPTH  1

#define PEU_NP_REQ_CREDIT_REG11_ADDR   0x0120007aL
#define PEU_NP_REQ_CREDIT_REG11_STRIDE 1
#define PEU_NP_REQ_CREDIT_REG11_DEPTH  1

#define PEU_P_RETURN_CREDIT_REG11_ADDR   0x0120007bL
#define PEU_P_RETURN_CREDIT_REG11_STRIDE 1
#define PEU_P_RETURN_CREDIT_REG11_DEPTH  1

#define PEU_NP_RETURN_CREDIT_REG11_ADDR   0x0120007cL
#define PEU_NP_RETURN_CREDIT_REG11_STRIDE 1
#define PEU_NP_RETURN_CREDIT_REG11_DEPTH  1

#define PEU_P_RETURN_INTERVAL_REG11_ADDR   0x0120007dL
#define PEU_P_RETURN_INTERVAL_REG11_STRIDE 1
#define PEU_P_RETURN_INTERVAL_REG11_DEPTH  1

#define PEU_NP_RETURN_INTERVAL_REG11_ADDR   0x0120007eL
#define PEU_NP_RETURN_INTERVAL_REG11_STRIDE 1
#define PEU_NP_RETURN_INTERVAL_REG11_DEPTH  1

#define PEU_Q_NP_TAG_CNT_THLD11_ADDR   0x0120007fL
#define PEU_Q_NP_TAG_CNT_THLD11_STRIDE 1
#define PEU_Q_NP_TAG_CNT_THLD11_DEPTH  1

#define PEU_XADM_PH_CDTS_THLD11_ADDR   0x01200080L
#define PEU_XADM_PH_CDTS_THLD11_STRIDE 1
#define PEU_XADM_PH_CDTS_THLD11_DEPTH  1

#define PEU_XADM_PD_CDTS_THLD11_ADDR   0x01200081L
#define PEU_XADM_PD_CDTS_THLD11_STRIDE 1
#define PEU_XADM_PD_CDTS_THLD11_DEPTH  1

#define PEU_XADM_NPH_CDTS_THLD11_ADDR   0x01200082L
#define PEU_XADM_NPH_CDTS_THLD11_STRIDE 1
#define PEU_XADM_NPH_CDTS_THLD11_DEPTH  1

#define PEU_XADM_NPD_CDTS_THLD11_ADDR   0x01200083L
#define PEU_XADM_NPD_CDTS_THLD11_STRIDE 1
#define PEU_XADM_NPD_CDTS_THLD11_DEPTH  1

#define PEU_P_REQ_CREDIT_REG12_ADDR   0x01200084L
#define PEU_P_REQ_CREDIT_REG12_STRIDE 1
#define PEU_P_REQ_CREDIT_REG12_DEPTH  1

#define PEU_NP_REQ_CREDIT_REG12_ADDR   0x01200085L
#define PEU_NP_REQ_CREDIT_REG12_STRIDE 1
#define PEU_NP_REQ_CREDIT_REG12_DEPTH  1

#define PEU_P_RETURN_CREDIT_REG12_ADDR   0x01200086L
#define PEU_P_RETURN_CREDIT_REG12_STRIDE 1
#define PEU_P_RETURN_CREDIT_REG12_DEPTH  1

#define PEU_NP_RETURN_CREDIT_REG12_ADDR   0x01200087L
#define PEU_NP_RETURN_CREDIT_REG12_STRIDE 1
#define PEU_NP_RETURN_CREDIT_REG12_DEPTH  1

#define PEU_P_RETURN_INTERVAL_REG12_ADDR   0x01200088L
#define PEU_P_RETURN_INTERVAL_REG12_STRIDE 1
#define PEU_P_RETURN_INTERVAL_REG12_DEPTH  1

#define PEU_NP_RETURN_INTERVAL_REG12_ADDR   0x01200089L
#define PEU_NP_RETURN_INTERVAL_REG12_STRIDE 1
#define PEU_NP_RETURN_INTERVAL_REG12_DEPTH  1

#define PEU_Q_NP_TAG_CNT_THLD12_ADDR   0x0120008aL
#define PEU_Q_NP_TAG_CNT_THLD12_STRIDE 1
#define PEU_Q_NP_TAG_CNT_THLD12_DEPTH  1

#define PEU_XADM_PH_CDTS_THLD12_ADDR   0x0120008bL
#define PEU_XADM_PH_CDTS_THLD12_STRIDE 1
#define PEU_XADM_PH_CDTS_THLD12_DEPTH  1

#define PEU_XADM_PD_CDTS_THLD12_ADDR   0x0120008cL
#define PEU_XADM_PD_CDTS_THLD12_STRIDE 1
#define PEU_XADM_PD_CDTS_THLD12_DEPTH  1

#define PEU_XADM_NPH_CDTS_THLD12_ADDR   0x0120008dL
#define PEU_XADM_NPH_CDTS_THLD12_STRIDE 1
#define PEU_XADM_NPH_CDTS_THLD12_DEPTH  1

#define PEU_XADM_NPD_CDTS_THLD12_ADDR   0x0120008eL
#define PEU_XADM_NPD_CDTS_THLD12_STRIDE 1
#define PEU_XADM_NPD_CDTS_THLD12_DEPTH  1

#define PEU_P_REQ_CREDIT_REG13_ADDR   0x0120008fL
#define PEU_P_REQ_CREDIT_REG13_STRIDE 1
#define PEU_P_REQ_CREDIT_REG13_DEPTH  1

#define PEU_NP_REQ_CREDIT_REG13_ADDR   0x01200090L
#define PEU_NP_REQ_CREDIT_REG13_STRIDE 1
#define PEU_NP_REQ_CREDIT_REG13_DEPTH  1

#define PEU_P_RETURN_CREDIT_REG13_ADDR   0x01200091L
#define PEU_P_RETURN_CREDIT_REG13_STRIDE 1
#define PEU_P_RETURN_CREDIT_REG13_DEPTH  1

#define PEU_NP_RETURN_CREDIT_REG13_ADDR   0x01200092L
#define PEU_NP_RETURN_CREDIT_REG13_STRIDE 1
#define PEU_NP_RETURN_CREDIT_REG13_DEPTH  1

#define PEU_P_RETURN_INTERVAL_REG13_ADDR   0x01200093L
#define PEU_P_RETURN_INTERVAL_REG13_STRIDE 1
#define PEU_P_RETURN_INTERVAL_REG13_DEPTH  1

#define PEU_NP_RETURN_INTERVAL_REG13_ADDR   0x01200094L
#define PEU_NP_RETURN_INTERVAL_REG13_STRIDE 1
#define PEU_NP_RETURN_INTERVAL_REG13_DEPTH  1

#define PEU_Q_NP_TAG_CNT_THLD13_ADDR   0x01200095L
#define PEU_Q_NP_TAG_CNT_THLD13_STRIDE 1
#define PEU_Q_NP_TAG_CNT_THLD13_DEPTH  1

#define PEU_XADM_PH_CDTS_THLD13_ADDR   0x01200096L
#define PEU_XADM_PH_CDTS_THLD13_STRIDE 1
#define PEU_XADM_PH_CDTS_THLD13_DEPTH  1

#define PEU_XADM_PD_CDTS_THLD13_ADDR   0x01200097L
#define PEU_XADM_PD_CDTS_THLD13_STRIDE 1
#define PEU_XADM_PD_CDTS_THLD13_DEPTH  1

#define PEU_XADM_NPH_CDTS_THLD13_ADDR   0x01200098L
#define PEU_XADM_NPH_CDTS_THLD13_STRIDE 1
#define PEU_XADM_NPH_CDTS_THLD13_DEPTH  1

#define PEU_XADM_NPD_CDTS_THLD13_ADDR   0x01200099L
#define PEU_XADM_NPD_CDTS_THLD13_STRIDE 1
#define PEU_XADM_NPD_CDTS_THLD13_DEPTH  1

#define PEU_P_REQ_CREDIT_REG14_ADDR   0x0120009aL
#define PEU_P_REQ_CREDIT_REG14_STRIDE 1
#define PEU_P_REQ_CREDIT_REG14_DEPTH  1

#define PEU_NP_REQ_CREDIT_REG14_ADDR   0x0120009bL
#define PEU_NP_REQ_CREDIT_REG14_STRIDE 1
#define PEU_NP_REQ_CREDIT_REG14_DEPTH  1

#define PEU_P_RETURN_CREDIT_REG14_ADDR   0x0120009cL
#define PEU_P_RETURN_CREDIT_REG14_STRIDE 1
#define PEU_P_RETURN_CREDIT_REG14_DEPTH  1

#define PEU_NP_RETURN_CREDIT_REG14_ADDR   0x0120009dL
#define PEU_NP_RETURN_CREDIT_REG14_STRIDE 1
#define PEU_NP_RETURN_CREDIT_REG14_DEPTH  1

#define PEU_P_RETURN_INTERVAL_REG14_ADDR   0x0120009eL
#define PEU_P_RETURN_INTERVAL_REG14_STRIDE 1
#define PEU_P_RETURN_INTERVAL_REG14_DEPTH  1

#define PEU_NP_RETURN_INTERVAL_REG14_ADDR   0x0120009fL
#define PEU_NP_RETURN_INTERVAL_REG14_STRIDE 1
#define PEU_NP_RETURN_INTERVAL_REG14_DEPTH  1

#define PEU_Q_NP_TAG_CNT_THLD14_ADDR   0x012000a0L
#define PEU_Q_NP_TAG_CNT_THLD14_STRIDE 1
#define PEU_Q_NP_TAG_CNT_THLD14_DEPTH  1

#define PEU_XADM_PH_CDTS_THLD14_ADDR   0x012000a1L
#define PEU_XADM_PH_CDTS_THLD14_STRIDE 1
#define PEU_XADM_PH_CDTS_THLD14_DEPTH  1

#define PEU_XADM_PD_CDTS_THLD14_ADDR   0x012000a2L
#define PEU_XADM_PD_CDTS_THLD14_STRIDE 1
#define PEU_XADM_PD_CDTS_THLD14_DEPTH  1

#define PEU_XADM_NPH_CDTS_THLD14_ADDR   0x012000a3L
#define PEU_XADM_NPH_CDTS_THLD14_STRIDE 1
#define PEU_XADM_NPH_CDTS_THLD14_DEPTH  1

#define PEU_XADM_NPD_CDTS_THLD14_ADDR   0x012000a4L
#define PEU_XADM_NPD_CDTS_THLD14_STRIDE 1
#define PEU_XADM_NPD_CDTS_THLD14_DEPTH  1

#define PEU_P_REQ_CREDIT_REG15_ADDR   0x012000a5L
#define PEU_P_REQ_CREDIT_REG15_STRIDE 1
#define PEU_P_REQ_CREDIT_REG15_DEPTH  1

#define PEU_NP_REQ_CREDIT_REG15_ADDR   0x012000a6L
#define PEU_NP_REQ_CREDIT_REG15_STRIDE 1
#define PEU_NP_REQ_CREDIT_REG15_DEPTH  1

#define PEU_P_RETURN_CREDIT_REG15_ADDR   0x012000a7L
#define PEU_P_RETURN_CREDIT_REG15_STRIDE 1
#define PEU_P_RETURN_CREDIT_REG15_DEPTH  1

#define PEU_NP_RETURN_CREDIT_REG15_ADDR   0x012000a8L
#define PEU_NP_RETURN_CREDIT_REG15_STRIDE 1
#define PEU_NP_RETURN_CREDIT_REG15_DEPTH  1

#define PEU_P_RETURN_INTERVAL_REG15_ADDR   0x012000a9L
#define PEU_P_RETURN_INTERVAL_REG15_STRIDE 1
#define PEU_P_RETURN_INTERVAL_REG15_DEPTH  1

#define PEU_NP_RETURN_INTERVAL_REG15_ADDR   0x012000aaL
#define PEU_NP_RETURN_INTERVAL_REG15_STRIDE 1
#define PEU_NP_RETURN_INTERVAL_REG15_DEPTH  1

#define PEU_Q_NP_TAG_CNT_THLD15_ADDR   0x012000abL
#define PEU_Q_NP_TAG_CNT_THLD15_STRIDE 1
#define PEU_Q_NP_TAG_CNT_THLD15_DEPTH  1

#define PEU_XADM_PH_CDTS_THLD15_ADDR   0x012000acL
#define PEU_XADM_PH_CDTS_THLD15_STRIDE 1
#define PEU_XADM_PH_CDTS_THLD15_DEPTH  1

#define PEU_XADM_PD_CDTS_THLD15_ADDR   0x012000adL
#define PEU_XADM_PD_CDTS_THLD15_STRIDE 1
#define PEU_XADM_PD_CDTS_THLD15_DEPTH  1

#define PEU_XADM_NPH_CDTS_THLD15_ADDR   0x012000aeL
#define PEU_XADM_NPH_CDTS_THLD15_STRIDE 1
#define PEU_XADM_NPH_CDTS_THLD15_DEPTH  1

#define PEU_XADM_NPD_CDTS_THLD15_ADDR   0x012000afL
#define PEU_XADM_NPD_CDTS_THLD15_STRIDE 1
#define PEU_XADM_NPD_CDTS_THLD15_DEPTH  1

#define PEU_HPRI_Q_REG_ADDR   0x012000b0L
#define PEU_HPRI_Q_REG_STRIDE 1
#define PEU_HPRI_Q_REG_DEPTH  1

#define PEU_HPRI_RR_WEIGHT_REG_ADDR   0x012000b1L
#define PEU_HPRI_RR_WEIGHT_REG_STRIDE 1
#define PEU_HPRI_RR_WEIGHT_REG_DEPTH  1

#define PEU_MAX_RD_REQ_SIZE_REG_ADDR   0x012000b2L
#define PEU_MAX_RD_REQ_SIZE_REG_STRIDE 1
#define PEU_MAX_RD_REQ_SIZE_REG_DEPTH  1

#define PEU_DIRTY_PCI_TAG_CTL_REG_ADDR   0x012000b3L
#define PEU_DIRTY_PCI_TAG_CTL_REG_STRIDE 1
#define PEU_DIRTY_PCI_TAG_CTL_REG_DEPTH  1

#define PEU_MASTER_VEC_ST_REG_ADDR   0x012000b4L
#define PEU_MASTER_VEC_ST_REG_STRIDE 1
#define PEU_MASTER_VEC_ST_REG_DEPTH  1

#define PEU_MASTER_VEC_MSK_REG_ADDR   0x012000b5L
#define PEU_MASTER_VEC_MSK_REG_STRIDE 1
#define PEU_MASTER_VEC_MSK_REG_DEPTH  1

#define PEU_FLR_REQ_DBG_REG_ADDR   0x012000b6L
#define PEU_FLR_REQ_DBG_REG_STRIDE 1
#define PEU_FLR_REQ_DBG_REG_DEPTH  1

#define PEU_FLR_DONE_DBG_REG_ADDR   0x012000b7L
#define PEU_FLR_DONE_DBG_REG_STRIDE 1
#define PEU_FLR_DONE_DBG_REG_DEPTH  1

#define PEU_FLR_REQ_VEC_ST_REG_ADDR   0x012000b8L
#define PEU_FLR_REQ_VEC_ST_REG_STRIDE 1
#define PEU_FLR_REQ_VEC_ST_REG_DEPTH  1

#define PEU_FLR_DONE_VEC_ST_REG_ADDR   0x012000b9L
#define PEU_FLR_DONE_VEC_ST_REG_STRIDE 1
#define PEU_FLR_DONE_VEC_ST_REG_DEPTH  1

#define PEU_TAG_POOL_DBG_REG_ADDR   0x012000baL
#define PEU_TAG_POOL_DBG_REG_STRIDE 1
#define PEU_TAG_POOL_DBG_REG_DEPTH  1

#define PEU_LTSSM_DBG_REG_ADDR   0x012000bbL
#define PEU_LTSSM_DBG_REG_STRIDE 1
#define PEU_LTSSM_DBG_REG_DEPTH  1

#define PEU_TSU_REQ_DBG_REG_ADDR   0x012000bcL
#define PEU_TSU_REQ_DBG_REG_STRIDE 1
#define PEU_TSU_REQ_DBG_REG_DEPTH  1

#define PEU_EPS_REQ_DBG_REG_ADDR   0x012000bdL
#define PEU_EPS_REQ_DBG_REG_STRIDE 1
#define PEU_EPS_REQ_DBG_REG_DEPTH  1

#define PEU_P_REQ_DBG_REG_ADDR   0x012000beL
#define PEU_P_REQ_DBG_REG_STRIDE 1
#define PEU_P_REQ_DBG_REG_DEPTH  1

#define PEU_NP_REQ_DBG_REG_ADDR   0x012000bfL
#define PEU_NP_REQ_DBG_REG_STRIDE 1
#define PEU_NP_REQ_DBG_REG_DEPTH  1

#define PEU_DBI_CSR_WDAT_REG_ADDR   0x012000c0L
#define PEU_DBI_CSR_WDAT_REG_STRIDE 1
#define PEU_DBI_CSR_WDAT_REG_DEPTH  1

#define PEU_DBI_CSR_CMD_REG_ADDR   0x012000c1L
#define PEU_DBI_CSR_CMD_REG_STRIDE 1
#define PEU_DBI_CSR_CMD_REG_DEPTH  1

#define PEU_DBI_CSR_STATUS_REG_ADDR   0x012000c2L
#define PEU_DBI_CSR_STATUS_REG_STRIDE 1
#define PEU_DBI_CSR_STATUS_REG_DEPTH  1

#define PEU_DBI_CSR_RDAT_REG_ADDR   0x012000c3L
#define PEU_DBI_CSR_RDAT_REG_STRIDE 1
#define PEU_DBI_CSR_RDAT_REG_DEPTH  1

#define PEU_CPL_BUF_WATER_MARK_REG_ADDR   0x012000c4L
#define PEU_CPL_BUF_WATER_MARK_REG_STRIDE 1
#define PEU_CPL_BUF_WATER_MARK_REG_DEPTH  1

#define PEU_ARB_CPL_BUF_THLD_REG_ADDR   0x012000c5L
#define PEU_ARB_CPL_BUF_THLD_REG_STRIDE 1
#define PEU_ARB_CPL_BUF_THLD_REG_DEPTH  1

#define PEU_CPL_BUF_CREDIT_REG_ADDR   0x012000c6L
#define PEU_CPL_BUF_CREDIT_REG_STRIDE 1
#define PEU_CPL_BUF_CREDIT_REG_DEPTH  1

#define PEU_CPL_MAX_CREDIT_REG_ADDR   0x012000c7L
#define PEU_CPL_MAX_CREDIT_REG_STRIDE 1
#define PEU_CPL_MAX_CREDIT_REG_DEPTH  1

#define PEU_PCIE_PHY_CTL_REG_ADDR   0x012000c8L
#define PEU_PCIE_PHY_CTL_REG_STRIDE 1
#define PEU_PCIE_PHY_CTL_REG_DEPTH  1

#define PEU_FORCE_ERR_REG_ADDR   0x012000c9L
#define PEU_FORCE_ERR_REG_STRIDE 1
#define PEU_FORCE_ERR_REG_DEPTH  1

#define PEU_MSG_GEN_QW0_REG_ADDR   0x012000caL
#define PEU_MSG_GEN_QW0_REG_STRIDE 1
#define PEU_MSG_GEN_QW0_REG_DEPTH  1

#define PEU_MSG_GEN_QW1_REG_ADDR   0x012000cbL
#define PEU_MSG_GEN_QW1_REG_STRIDE 1
#define PEU_MSG_GEN_QW1_REG_DEPTH  1

#define PEU_MSG_STATUS_REG_ADDR   0x012000ccL
#define PEU_MSG_STATUS_REG_STRIDE 1
#define PEU_MSG_STATUS_REG_DEPTH  1

#define PEU_ATS_MSG_QW0_REG_ADDR   0x012000cdL
#define PEU_ATS_MSG_QW0_REG_STRIDE 1
#define PEU_ATS_MSG_QW0_REG_DEPTH  1

#define PEU_ATS_MSG_QW1_REG_ADDR   0x012000ceL
#define PEU_ATS_MSG_QW1_REG_STRIDE 1
#define PEU_ATS_MSG_QW1_REG_DEPTH  1

#define PEU_SRAM_CORR_ERR_STATUS_REG_ADDR   0x012000cfL
#define PEU_SRAM_CORR_ERR_STATUS_REG_STRIDE 1
#define PEU_SRAM_CORR_ERR_STATUS_REG_DEPTH  1

#define PEU_HI_PRI_MSK_REG_ADDR   0x012000d0L
#define PEU_HI_PRI_MSK_REG_STRIDE 1
#define PEU_HI_PRI_MSK_REG_DEPTH  1

#define PEU_HI_PRI_INTR_VEC_REG_ADDR   0x012000d1L
#define PEU_HI_PRI_INTR_VEC_REG_STRIDE 1
#define PEU_HI_PRI_INTR_VEC_REG_DEPTH  1

#define PEU_FATAL_INTR_MSK_REG_ADDR   0x012000d2L
#define PEU_FATAL_INTR_MSK_REG_STRIDE 1
#define PEU_FATAL_INTR_MSK_REG_DEPTH  1

#define PEU_FATAL_INTR_VEC_REG_ADDR   0x012000d3L
#define PEU_FATAL_INTR_VEC_REG_STRIDE 1
#define PEU_FATAL_INTR_VEC_REG_DEPTH  1

#define PEU_INTR_REQ_DBG_REG_ADDR   0x012000d4L
#define PEU_INTR_REQ_DBG_REG_STRIDE 1
#define PEU_INTR_REQ_DBG_REG_DEPTH  1

#define PEU_TSU_PIO_REQ_DBG_REG_ADDR   0x012000d5L
#define PEU_TSU_PIO_REQ_DBG_REG_STRIDE 1
#define PEU_TSU_PIO_REQ_DBG_REG_DEPTH  1

#define PEU_EPRM_PIO_REQ_DBG_REG_ADDR   0x012000d6L
#define PEU_EPRM_PIO_REQ_DBG_REG_STRIDE 1
#define PEU_EPRM_PIO_REQ_DBG_REG_DEPTH  1

#define PEU_INTR_PIO_REQ_DBG_REG_ADDR   0x012000d7L
#define PEU_INTR_PIO_REQ_DBG_REG_STRIDE 1
#define PEU_INTR_PIO_REQ_DBG_REG_DEPTH  1

#define PEU_CPL_FLUSH_DBG_REG_ADDR   0x012000d8L
#define PEU_CPL_FLUSH_DBG_REG_STRIDE 1
#define PEU_CPL_FLUSH_DBG_REG_DEPTH  1

#define PEU_EP_DIAG_DBG_REG_ADDR   0x012000d9L
#define PEU_EP_DIAG_DBG_REG_STRIDE 1
#define PEU_EP_DIAG_DBG_REG_DEPTH  1

#define PEU_CXPL_EI_DBG_REG_ADDR   0x012000daL
#define PEU_CXPL_EI_DBG_REG_STRIDE 1
#define PEU_CXPL_EI_DBG_REG_DEPTH  1

#define PEU_CXPL_DBG_REG_ADDR   0x012000dbL
#define PEU_CXPL_DBG_REG_STRIDE 1
#define PEU_CXPL_DBG_REG_DEPTH  1

#define PEU_FF_DC_1_DBG_REG_ADDR   0x012000dcL
#define PEU_FF_DC_1_DBG_REG_STRIDE 1
#define PEU_FF_DC_1_DBG_REG_DEPTH  1

#define PEU_FF_DC_2_DBG_REG_ADDR   0x012000ddL
#define PEU_FF_DC_2_DBG_REG_STRIDE 1
#define PEU_FF_DC_2_DBG_REG_DEPTH  1

#define PEU_FORCE_FLR_REG_ADDR   0x012000deL
#define PEU_FORCE_FLR_REG_STRIDE 1
#define PEU_FORCE_FLR_REG_DEPTH  1

#define PEU_CSR_PEU_CTL_ST_REG_ADDR   0x01200100L
#define PEU_CSR_PEU_CTL_ST_REG_STRIDE 1
#define PEU_CSR_PEU_CTL_ST_REG_DEPTH  1

#define PEU_CSR_PEU_INT_ST_REG_ADDR   0x01200101L
#define PEU_CSR_PEU_INT_ST_REG_STRIDE 1
#define PEU_CSR_PEU_INT_ST_REG_DEPTH  1

#define PEU_CSR_PEU_INT_MSK_REG_ADDR   0x01200102L
#define PEU_CSR_PEU_INT_MSK_REG_STRIDE 1
#define PEU_CSR_PEU_INT_MSK_REG_DEPTH  1

#define PEU_CSR_LP_INTR_VEC_REG_ADDR   0x01200103L
#define PEU_CSR_LP_INTR_VEC_REG_STRIDE 1
#define PEU_CSR_LP_INTR_VEC_REG_DEPTH  1

#define PEU_CSR_LPRI_INT_MSK_REG_ADDR   0x01200104L
#define PEU_CSR_LPRI_INT_MSK_REG_STRIDE 1
#define PEU_CSR_LPRI_INT_MSK_REG_DEPTH  1

#define PEU_CSR_SER_INT_ST_REG_ADDR   0x01200105L
#define PEU_CSR_SER_INT_ST_REG_STRIDE 1
#define PEU_CSR_SER_INT_ST_REG_DEPTH  1

#define PEU_TSU_FLR_REQ_DBG_REG_ADDR   0x012001b0L
#define PEU_TSU_FLR_REQ_DBG_REG_STRIDE 1
#define PEU_TSU_FLR_REQ_DBG_REG_DEPTH  1

#define PEU_TSU_FLR_DONE_DBG_REG_ADDR   0x012001b1L
#define PEU_TSU_FLR_DONE_DBG_REG_STRIDE 1
#define PEU_TSU_FLR_DONE_DBG_REG_DEPTH  1

#define PEU_EPS_FLR_REQ_DBG_REG_ADDR   0x012001b2L
#define PEU_EPS_FLR_REQ_DBG_REG_STRIDE 1
#define PEU_EPS_FLR_REQ_DBG_REG_DEPTH  1

#define PEU_EPS_FLR_DONE_DBG_REG_ADDR   0x012001b3L
#define PEU_EPS_FLR_DONE_DBG_REG_STRIDE 1
#define PEU_EPS_FLR_DONE_DBG_REG_DEPTH  1

#define PEU_PIPE_CSR_WDAT_REG_ADDR   0x012001b4L
#define PEU_PIPE_CSR_WDAT_REG_STRIDE 1
#define PEU_PIPE_CSR_WDAT_REG_DEPTH  1

#define PEU_PIPE_CSR_CMD_REG_ADDR   0x012001b5L
#define PEU_PIPE_CSR_CMD_REG_STRIDE 1
#define PEU_PIPE_CSR_CMD_REG_DEPTH  1

#define PEU_PIPE_CSR_STATUS_REG_ADDR   0x012001b6L
#define PEU_PIPE_CSR_STATUS_REG_STRIDE 1
#define PEU_PIPE_CSR_STATUS_REG_DEPTH  1

#define PEU_PIPE_CSR_RDAT_REG_ADDR   0x012001b7L
#define PEU_PIPE_CSR_RDAT_REG_STRIDE 1
#define PEU_PIPE_CSR_RDAT_REG_DEPTH  1

#define PEU_SER_CSR_WDAT_REG_ADDR   0x012001b8L
#define PEU_SER_CSR_WDAT_REG_STRIDE 1
#define PEU_SER_CSR_WDAT_REG_DEPTH  1

#define PEU_SER_CSR_CMD_REG_ADDR   0x012001b9L
#define PEU_SER_CSR_CMD_REG_STRIDE 1
#define PEU_SER_CSR_CMD_REG_DEPTH  1

#define PEU_SER_CSR_STATUS_REG_ADDR   0x012001baL
#define PEU_SER_CSR_STATUS_REG_STRIDE 1
#define PEU_SER_CSR_STATUS_REG_DEPTH  1

#define PEU_SER_CSR_RDAT_REG_ADDR   0x012001bbL
#define PEU_SER_CSR_RDAT_REG_STRIDE 1
#define PEU_SER_CSR_RDAT_REG_DEPTH  1

#define PEU_SER_1_CSR_WDAT_REG_ADDR   0x012001bcL
#define PEU_SER_1_CSR_WDAT_REG_STRIDE 1
#define PEU_SER_1_CSR_WDAT_REG_DEPTH  1

#define PEU_SER_1_CSR_CMD_REG_ADDR   0x012001bdL
#define PEU_SER_1_CSR_CMD_REG_STRIDE 1
#define PEU_SER_1_CSR_CMD_REG_DEPTH  1

#define PEU_SER_1_CSR_STATUS_REG_ADDR   0x012001beL
#define PEU_SER_1_CSR_STATUS_REG_STRIDE 1
#define PEU_SER_1_CSR_STATUS_REG_DEPTH  1

#define PEU_SER_1_CSR_RDAT_REG_ADDR   0x012001bfL
#define PEU_SER_1_CSR_RDAT_REG_STRIDE 1
#define PEU_SER_1_CSR_RDAT_REG_DEPTH  1

#define PEU_SER_DFE_ST_SEL_REG_ADDR   0x012001c0L
#define PEU_SER_DFE_ST_SEL_REG_STRIDE 1
#define PEU_SER_DFE_ST_SEL_REG_DEPTH  1

#define PEU_SER_DFE_ST_0_REG_ADDR   0x012001c1L
#define PEU_SER_DFE_ST_0_REG_STRIDE 1
#define PEU_SER_DFE_ST_0_REG_DEPTH  1

#define PEU_SER_DFE_ST_1_REG_ADDR   0x012001c2L
#define PEU_SER_DFE_ST_1_REG_STRIDE 1
#define PEU_SER_DFE_ST_1_REG_DEPTH  1

#define PEU_SER_DFE_ST_2_REG_ADDR   0x012001c3L
#define PEU_SER_DFE_ST_2_REG_STRIDE 1
#define PEU_SER_DFE_ST_2_REG_DEPTH  1

#define PEU_SER_DFE_ST_3_REG_ADDR   0x012001c4L
#define PEU_SER_DFE_ST_3_REG_STRIDE 1
#define PEU_SER_DFE_ST_3_REG_DEPTH  1

#define PEU_SER_POWERDOWN_CTL_REG_ADDR   0x012001f0L
#define PEU_SER_POWERDOWN_CTL_REG_STRIDE 1
#define PEU_SER_POWERDOWN_CTL_REG_DEPTH  1

#define PEU_SER_CFG0_REG_ADDR   0x012001f1L
#define PEU_SER_CFG0_REG_STRIDE 1
#define PEU_SER_CFG0_REG_DEPTH  1

#define PEU_SER_CFG1_REG_ADDR   0x012001f2L
#define PEU_SER_CFG1_REG_STRIDE 1
#define PEU_SER_CFG1_REG_DEPTH  1

#define PEU_SER_CFG2_REG_ADDR   0x012001f3L
#define PEU_SER_CFG2_REG_STRIDE 1
#define PEU_SER_CFG2_REG_DEPTH  1

#define PEU_SER_CFG3_REG_ADDR   0x012001f4L
#define PEU_SER_CFG3_REG_STRIDE 1
#define PEU_SER_CFG3_REG_DEPTH  1

#define PEU_CSR_SER_CTL_REG_ADDR   0x012001f5L
#define PEU_CSR_SER_CTL_REG_STRIDE 1
#define PEU_CSR_SER_CTL_REG_DEPTH  1

#define PEU_CSR_SER_ST_REG_ADDR   0x012001f6L
#define PEU_CSR_SER_ST_REG_STRIDE 1
#define PEU_CSR_SER_ST_REG_DEPTH  1

#ifdef __cplusplus
}
#endif


#endif	/* _PSIF_FW_ADDR_H */
