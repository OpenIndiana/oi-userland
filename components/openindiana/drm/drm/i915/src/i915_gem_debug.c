/*
 * Copyright (c) 2006, 2013, Oracle and/or its affiliates. All rights reserved.
 */

/*
 * Copyright (c) 2009, 2013, Intel Corporation.
 * All Rights Reserved.
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
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Keith Packard <keithp@keithp.com>
 *
 */

#include "drmP.h"
#include "drm.h"
#include "i915_drm.h"
#include "i915_drv.h"

int gpu_dump = B_TRUE;
int gpu_panic_on_hang = B_FALSE;

#define BUFFER_FAIL(_count, _len, _name) { 			\
	DRM_ERROR("Buffer size too small in %s (%d < %d)",	\
	    (_name), (_count), (_len));				\
	(*failures)++;						\
	return count;						\
}


static uint32_t saved_s2 = 0, saved_s4 = 0;
static char saved_s2_set = 0, saved_s4_set = 0;


#define MAX_INSTDONE_BITS            100

struct instdone_bit {
	uint32_t reg;
	uint32_t bit;
	const char *name;
};

struct instdone_bit instdone_bits[MAX_INSTDONE_BITS];
int num_instdone_bits = 0;

static void
add_instdone_bit(uint32_t reg, uint32_t bit, const char *name)
{
	instdone_bits[num_instdone_bits].reg = reg;
	instdone_bits[num_instdone_bits].bit = bit;
	instdone_bits[num_instdone_bits].name = name;
	num_instdone_bits++;
}

static void
gen3_instdone_bit(uint32_t bit, const char *name)
{
	add_instdone_bit(INST_DONE, bit, name);
}

static void
gen4_instdone_bit(uint32_t bit, const char *name)
{
	add_instdone_bit(INST_DONE_I965, bit, name);
}

static void
gen4_instdone1_bit(uint32_t bit, const char *name)
{
	add_instdone_bit(INST_DONE_1, bit, name);
}

static void
gen6_instdone1_bit(uint32_t bit, const char *name)
{
	add_instdone_bit(GEN6_INSTDONE_1, bit, name);
}

static void
gen6_instdone2_bit(uint32_t bit, const char *name)
{
	add_instdone_bit(GEN6_INSTDONE_2, bit, name);
}

static void
init_g965_instdone1(void)
{
	gen4_instdone1_bit(I965_GW_CS_DONE_CR, "GW CS CR");
	gen4_instdone1_bit(I965_SVSM_CS_DONE_CR, "SVSM CS CR");
	gen4_instdone1_bit(I965_SVDW_CS_DONE_CR, "SVDW CS CR");
	gen4_instdone1_bit(I965_SVDR_CS_DONE_CR, "SVDR CS CR");
	gen4_instdone1_bit(I965_SVRW_CS_DONE_CR, "SVRW CS CR");
	gen4_instdone1_bit(I965_SVRR_CS_DONE_CR, "SVRR CS CR");
	gen4_instdone1_bit(I965_SVTW_CS_DONE_CR, "SVTW CS CR");
	gen4_instdone1_bit(I965_MASM_CS_DONE_CR, "MASM CS CR");
	gen4_instdone1_bit(I965_MASF_CS_DONE_CR, "MASF CS CR");
	gen4_instdone1_bit(I965_MAW_CS_DONE_CR, "MAW CS CR");
	gen4_instdone1_bit(I965_EM1_CS_DONE_CR, "EM1 CS CR");
	gen4_instdone1_bit(I965_EM0_CS_DONE_CR, "EM0 CS CR");
	gen4_instdone1_bit(I965_UC1_CS_DONE, "UC1 CS");
	gen4_instdone1_bit(I965_UC0_CS_DONE, "UC0 CS");
	gen4_instdone1_bit(I965_URB_CS_DONE, "URB CS");
	gen4_instdone1_bit(I965_ISC_CS_DONE, "ISC CS");
	gen4_instdone1_bit(I965_CL_CS_DONE, "CL CS");
	gen4_instdone1_bit(I965_GS_CS_DONE, "GS CS");
	gen4_instdone1_bit(I965_VS0_CS_DONE, "VS0 CS");
	gen4_instdone1_bit(I965_VF_CS_DONE, "VF CS");
}

static void
init_g4x_instdone1(void)
{
	gen4_instdone1_bit(G4X_BCS_DONE, "BCS");
	gen4_instdone1_bit(G4X_CS_DONE, "CS");
	gen4_instdone1_bit(G4X_MASF_DONE, "MASF");
	gen4_instdone1_bit(G4X_SVDW_DONE, "SVDW");
	gen4_instdone1_bit(G4X_SVDR_DONE, "SVDR");
	gen4_instdone1_bit(G4X_SVRW_DONE, "SVRW");
	gen4_instdone1_bit(G4X_SVRR_DONE, "SVRR");
	gen4_instdone1_bit(G4X_ISC_DONE, "ISC");
	gen4_instdone1_bit(G4X_MT_DONE, "MT");
	gen4_instdone1_bit(G4X_RC_DONE, "RC");
	gen4_instdone1_bit(G4X_DAP_DONE, "DAP");
	gen4_instdone1_bit(G4X_MAWB_DONE, "MAWB");
	gen4_instdone1_bit(G4X_MT_IDLE, "MT idle");
	//gen4_instdone1_bit(G4X_GBLT_BUSY, "GBLT");
	gen4_instdone1_bit(G4X_SVSM_DONE, "SVSM");
	gen4_instdone1_bit(G4X_MASM_DONE, "MASM");
	gen4_instdone1_bit(G4X_QC_DONE, "QC");
	gen4_instdone1_bit(G4X_FL_DONE, "FL");
	gen4_instdone1_bit(G4X_SC_DONE, "SC");
	gen4_instdone1_bit(G4X_DM_DONE, "DM");
	gen4_instdone1_bit(G4X_FT_DONE, "FT");
	gen4_instdone1_bit(G4X_DG_DONE, "DG");
	gen4_instdone1_bit(G4X_SI_DONE, "SI");
	gen4_instdone1_bit(G4X_SO_DONE, "SO");
	gen4_instdone1_bit(G4X_PL_DONE, "PL");
	gen4_instdone1_bit(G4X_WIZ_DONE, "WIZ");
	gen4_instdone1_bit(G4X_URB_DONE, "URB");
	gen4_instdone1_bit(G4X_SF_DONE, "SF");
	gen4_instdone1_bit(G4X_CL_DONE, "CL");
	gen4_instdone1_bit(G4X_GS_DONE, "GS");
	gen4_instdone1_bit(G4X_VS0_DONE, "VS0");
	gen4_instdone1_bit(G4X_VF_DONE, "VF");
}

void
init_instdone_definitions(struct drm_device *dev)
{
	if (IS_GEN6(dev)) {
		/* Now called INSTDONE_1 in the docs. */
		gen6_instdone1_bit(GEN6_MA_3_DONE, "Message Arbiter 3");
		gen6_instdone1_bit(GEN6_EU_32_DONE, "EU 32");
		gen6_instdone1_bit(GEN6_EU_31_DONE, "EU 31");
		gen6_instdone1_bit(GEN6_EU_30_DONE, "EU 30");
		gen6_instdone1_bit(GEN6_MA_3_DONE, "Message Arbiter 2");
		gen6_instdone1_bit(GEN6_EU_22_DONE, "EU 22");
		gen6_instdone1_bit(GEN6_EU_21_DONE, "EU 21");
		gen6_instdone1_bit(GEN6_EU_20_DONE, "EU 20");
		gen6_instdone1_bit(GEN6_MA_3_DONE, "Message Arbiter 1");
		gen6_instdone1_bit(GEN6_EU_12_DONE, "EU 12");
		gen6_instdone1_bit(GEN6_EU_11_DONE, "EU 11");
		gen6_instdone1_bit(GEN6_EU_10_DONE, "EU 10");
		gen6_instdone1_bit(GEN6_MA_3_DONE, "Message Arbiter 0");
		gen6_instdone1_bit(GEN6_EU_02_DONE, "EU 02");
		gen6_instdone1_bit(GEN6_EU_01_DONE, "EU 01");
		gen6_instdone1_bit(GEN6_EU_00_DONE, "EU 00");

		gen6_instdone1_bit(GEN6_IC_3_DONE, "IC 3");
		gen6_instdone1_bit(GEN6_IC_2_DONE, "IC 2");
		gen6_instdone1_bit(GEN6_IC_1_DONE, "IC 1");
		gen6_instdone1_bit(GEN6_IC_0_DONE, "IC 0");
		gen6_instdone1_bit(GEN6_ISC_10_DONE, "ISC 1/0");
		gen6_instdone1_bit(GEN6_ISC_32_DONE, "ISC 3/2");

		gen6_instdone1_bit(GEN6_VSC_DONE, "VSC");
		gen6_instdone1_bit(GEN6_IEF_DONE, "IEF");
		gen6_instdone1_bit(GEN6_VFE_DONE, "VFE");
		gen6_instdone1_bit(GEN6_TD_DONE, "TD");
		gen6_instdone1_bit(GEN6_TS_DONE, "TS");
		gen6_instdone1_bit(GEN6_GW_DONE, "GW");
		gen6_instdone1_bit(GEN6_HIZ_DONE, "HIZ");
		gen6_instdone1_bit(GEN6_AVS_DONE, "AVS");

		/* Now called INSTDONE_2 in the docs. */
		gen6_instdone2_bit(GEN6_GAM_DONE, "GAM");
		gen6_instdone2_bit(GEN6_CS_DONE, "CS");
		gen6_instdone2_bit(GEN6_WMBE_DONE, "WMBE");
		gen6_instdone2_bit(GEN6_SVRW_DONE, "SVRW");
		gen6_instdone2_bit(GEN6_RCC_DONE, "RCC");
		gen6_instdone2_bit(GEN6_SVG_DONE, "SVG");
		gen6_instdone2_bit(GEN6_ISC_DONE, "ISC");
		gen6_instdone2_bit(GEN6_MT_DONE, "MT");
		gen6_instdone2_bit(GEN6_RCPFE_DONE, "RCPFE");
		gen6_instdone2_bit(GEN6_RCPBE_DONE, "RCPBE");
		gen6_instdone2_bit(GEN6_VDI_DONE, "VDI");
		gen6_instdone2_bit(GEN6_RCZ_DONE, "RCZ");
		gen6_instdone2_bit(GEN6_DAP_DONE, "DAP");
		gen6_instdone2_bit(GEN6_PSD_DONE, "PSD");
		gen6_instdone2_bit(GEN6_IZ_DONE, "IZ");
		gen6_instdone2_bit(GEN6_WMFE_DONE, "WMFE");
		gen6_instdone2_bit(GEN6_SVSM_DONE, "SVSM");
		gen6_instdone2_bit(GEN6_QC_DONE, "QC");
		gen6_instdone2_bit(GEN6_FL_DONE, "FL");
		gen6_instdone2_bit(GEN6_SC_DONE, "SC");
		gen6_instdone2_bit(GEN6_DM_DONE, "DM");
		gen6_instdone2_bit(GEN6_FT_DONE, "FT");
		gen6_instdone2_bit(GEN6_DG_DONE, "DG");
		gen6_instdone2_bit(GEN6_SI_DONE, "SI");
		gen6_instdone2_bit(GEN6_SO_DONE, "SO");
		gen6_instdone2_bit(GEN6_PL_DONE, "PL");
		gen6_instdone2_bit(GEN6_VME_DONE, "VME");
		gen6_instdone2_bit(GEN6_SF_DONE, "SF");
		gen6_instdone2_bit(GEN6_CL_DONE, "CL");
		gen6_instdone2_bit(GEN6_GS_DONE, "GS");
		gen6_instdone2_bit(GEN6_VS0_DONE, "VS0");
		gen6_instdone2_bit(GEN6_VF_DONE, "VF");
	} else if (IS_GEN5(dev)) {
		gen4_instdone_bit(ILK_ROW_0_EU_0_DONE, "Row 0, EU 0");
		gen4_instdone_bit(ILK_ROW_0_EU_1_DONE, "Row 0, EU 1");
		gen4_instdone_bit(ILK_ROW_0_EU_2_DONE, "Row 0, EU 2");
		gen4_instdone_bit(ILK_ROW_0_EU_3_DONE, "Row 0, EU 3");
		gen4_instdone_bit(ILK_ROW_1_EU_0_DONE, "Row 1, EU 0");
		gen4_instdone_bit(ILK_ROW_1_EU_1_DONE, "Row 1, EU 1");
		gen4_instdone_bit(ILK_ROW_1_EU_2_DONE, "Row 1, EU 2");
		gen4_instdone_bit(ILK_ROW_1_EU_3_DONE, "Row 1, EU 3");
		gen4_instdone_bit(ILK_ROW_2_EU_0_DONE, "Row 2, EU 0");
		gen4_instdone_bit(ILK_ROW_2_EU_1_DONE, "Row 2, EU 1");
		gen4_instdone_bit(ILK_ROW_2_EU_2_DONE, "Row 2, EU 2");
		gen4_instdone_bit(ILK_ROW_2_EU_3_DONE, "Row 2, EU 3");
		gen4_instdone_bit(ILK_VCP_DONE, "VCP");
		gen4_instdone_bit(ILK_ROW_0_MATH_DONE, "Row 0 math");
		gen4_instdone_bit(ILK_ROW_1_MATH_DONE, "Row 1 math");
		gen4_instdone_bit(ILK_ROW_2_MATH_DONE, "Row 2 math");
		gen4_instdone_bit(ILK_VC1_DONE, "VC1");
		gen4_instdone_bit(ILK_ROW_0_MA_DONE, "Row 0 MA");
		gen4_instdone_bit(ILK_ROW_1_MA_DONE, "Row 1 MA");
		gen4_instdone_bit(ILK_ROW_2_MA_DONE, "Row 2 MA");
		gen4_instdone_bit(ILK_ROW_0_ISC_DONE, "Row 0 ISC");
		gen4_instdone_bit(ILK_ROW_1_ISC_DONE, "Row 1 ISC");
		gen4_instdone_bit(ILK_ROW_2_ISC_DONE, "Row 2 ISC");
		gen4_instdone_bit(ILK_VFE_DONE, "VFE");
		gen4_instdone_bit(ILK_TD_DONE, "TD");
		gen4_instdone_bit(ILK_SVTS_DONE, "SVTS");
		gen4_instdone_bit(ILK_TS_DONE, "TS");
		gen4_instdone_bit(ILK_GW_DONE, "GW");
		gen4_instdone_bit(ILK_AI_DONE, "AI");
		gen4_instdone_bit(ILK_AC_DONE, "AC");
		gen4_instdone_bit(ILK_AM_DONE, "AM");

		init_g4x_instdone1();
	} else if (IS_GEN4(dev)) {
		gen4_instdone_bit(I965_ROW_0_EU_0_DONE, "Row 0, EU 0");
		gen4_instdone_bit(I965_ROW_0_EU_1_DONE, "Row 0, EU 1");
		gen4_instdone_bit(I965_ROW_0_EU_2_DONE, "Row 0, EU 2");
		gen4_instdone_bit(I965_ROW_0_EU_3_DONE, "Row 0, EU 3");
		gen4_instdone_bit(I965_ROW_1_EU_0_DONE, "Row 1, EU 0");
		gen4_instdone_bit(I965_ROW_1_EU_1_DONE, "Row 1, EU 1");
		gen4_instdone_bit(I965_ROW_1_EU_2_DONE, "Row 1, EU 2");
		gen4_instdone_bit(I965_ROW_1_EU_3_DONE, "Row 1, EU 3");
		gen4_instdone_bit(I965_SF_DONE, "Strips and Fans");
		gen4_instdone_bit(I965_SE_DONE, "Setup Engine");
		gen4_instdone_bit(I965_WM_DONE, "Windowizer");
		gen4_instdone_bit(I965_DISPATCHER_DONE, "Dispatcher");
		gen4_instdone_bit(I965_PROJECTION_DONE, "Projection and LOD");
		gen4_instdone_bit(I965_DG_DONE, "Dependent address generator");
		gen4_instdone_bit(I965_QUAD_CACHE_DONE, "Texture fetch");
		gen4_instdone_bit(I965_TEXTURE_FETCH_DONE, "Texture fetch");
		gen4_instdone_bit(I965_TEXTURE_DECOMPRESS_DONE, "Texture decompress");
		gen4_instdone_bit(I965_SAMPLER_CACHE_DONE, "Sampler cache");
		gen4_instdone_bit(I965_FILTER_DONE, "Filtering");
		gen4_instdone_bit(I965_BYPASS_DONE, "Bypass FIFO");
		gen4_instdone_bit(I965_PS_DONE, "Pixel shader");
		gen4_instdone_bit(I965_CC_DONE, "Color calculator");
		gen4_instdone_bit(I965_MAP_FILTER_DONE, "Map filter");
		gen4_instdone_bit(I965_MAP_L2_IDLE, "Map L2");
		gen4_instdone_bit(I965_MA_ROW_0_DONE, "Message Arbiter row 0");
		gen4_instdone_bit(I965_MA_ROW_1_DONE, "Message Arbiter row 1");
		gen4_instdone_bit(I965_IC_ROW_0_DONE, "Instruction cache row 0");
		gen4_instdone_bit(I965_IC_ROW_1_DONE, "Instruction cache row 1");
		gen4_instdone_bit(I965_CP_DONE, "Command Processor");

		if (IS_G4X(dev)) {
			init_g4x_instdone1();
		} else {
			init_g965_instdone1();
		}
	} else if (IS_GEN3(dev)) {
		gen3_instdone_bit(IDCT_DONE, "IDCT");
		gen3_instdone_bit(IQ_DONE, "IQ");
		gen3_instdone_bit(PR_DONE, "PR");
		gen3_instdone_bit(VLD_DONE, "VLD");
		gen3_instdone_bit(IP_DONE, "Instruction parser");
		gen3_instdone_bit(FBC_DONE, "Framebuffer Compression");
		gen3_instdone_bit(BINNER_DONE, "Binner");
		gen3_instdone_bit(SF_DONE, "Strips and fans");
		gen3_instdone_bit(SE_DONE, "Setup engine");
		gen3_instdone_bit(WM_DONE, "Windowizer");
		gen3_instdone_bit(IZ_DONE, "Intermediate Z");
		gen3_instdone_bit(PERSPECTIVE_INTERP_DONE, "Perspective interpolation");
		gen3_instdone_bit(DISPATCHER_DONE, "Dispatcher");
		gen3_instdone_bit(PROJECTION_DONE, "Projection and LOD");
		gen3_instdone_bit(DEPENDENT_ADDRESS_DONE, "Dependent address calculation");
		gen3_instdone_bit(TEXTURE_FETCH_DONE, "Texture fetch");
		gen3_instdone_bit(TEXTURE_DECOMPRESS_DONE, "Texture decompression");
		gen3_instdone_bit(SAMPLER_CACHE_DONE, "Sampler Cache");
		gen3_instdone_bit(FILTER_DONE, "Filtering");
		gen3_instdone_bit(BYPASS_FIFO_DONE, "Bypass FIFO");
		gen3_instdone_bit(PS_DONE, "Pixel shader");
		gen3_instdone_bit(CC_DONE, "Color calculator");
		gen3_instdone_bit(MAP_FILTER_DONE, "Map filter");
		gen3_instdone_bit(MAP_L2_IDLE, "Map L2");
	} else {
		gen3_instdone_bit(I830_GMBUS_DONE, "GMBUS");
		gen3_instdone_bit(I830_FBC_DONE, "FBC");
		gen3_instdone_bit(I830_BINNER_DONE, "BINNER");
		gen3_instdone_bit(I830_MPEG_DONE, "MPEG");
		gen3_instdone_bit(I830_MECO_DONE, "MECO");
		gen3_instdone_bit(I830_MCD_DONE, "MCD");
		gen3_instdone_bit(I830_MCSTP_DONE, "MCSTP");
		gen3_instdone_bit(I830_CC_DONE, "CC");
		gen3_instdone_bit(I830_DG_DONE, "DG");
		gen3_instdone_bit(I830_DCMP_DONE, "DCMP");
		gen3_instdone_bit(I830_FTCH_DONE, "FTCH");
		gen3_instdone_bit(I830_IT_DONE, "IT");
		gen3_instdone_bit(I830_MG_DONE, "MG");
		gen3_instdone_bit(I830_MEC_DONE, "MEC");
		gen3_instdone_bit(I830_PC_DONE, "PC");
		gen3_instdone_bit(I830_QCC_DONE, "QCC");
		gen3_instdone_bit(I830_TB_DONE, "TB");
		gen3_instdone_bit(I830_WM_DONE, "WM");
		gen3_instdone_bit(I830_EF_DONE, "EF");
		gen3_instdone_bit(I830_BLITTER_DONE, "Blitter");
		gen3_instdone_bit(I830_MAP_L2_DONE, "Map L2 cache");
		gen3_instdone_bit(I830_SECONDARY_RING_3_DONE, "Secondary ring 3");
		gen3_instdone_bit(I830_SECONDARY_RING_2_DONE, "Secondary ring 2");
		gen3_instdone_bit(I830_SECONDARY_RING_1_DONE, "Secondary ring 1");
		gen3_instdone_bit(I830_SECONDARY_RING_0_DONE, "Secondary ring 0");
		gen3_instdone_bit(I830_PRIMARY_RING_1_DONE, "Primary ring 1");
		gen3_instdone_bit(I830_PRIMARY_RING_0_DONE, "Primary ring 0");
	}
}
#define ring_read(ring, reg)	I915_READ(ring->mmio + reg)
#define MAX_NUM_TOP_BITS            100
#define SAMPLES_PER_SEC             10000
#define SAMPLES_TO_PERCENT_RATIO    (SAMPLES_PER_SEC / 100)

#define HAS_STATS_REGS(dev)		(IS_GEN4(dev) || \
				 IS_GEN5(dev) || \
				 IS_GEN6(dev))
struct top_bit {
	struct instdone_bit *bit;
	int count;
} top_bits[MAX_NUM_TOP_BITS];
struct top_bit *top_bits_sorted[MAX_NUM_TOP_BITS];
static uint32_t instdone, instdone1;

struct ring {
	const char *name;
	uint32_t mmio, size;
	int head, tail;
	uint64_t full;
	int idle;
};

enum stats_counts {
	IA_VERTICES,
	IA_PRIMITIVES,
	VS_INVOCATION,
	GS_INVOCATION,
	GS_PRIMITIVES,
	CL_INVOCATION,
	CL_PRIMITIVES,
	PS_INVOCATION,
	PS_DEPTH,
	STATS_COUNT
};

const uint32_t stats_regs[STATS_COUNT] = {
	IA_VERTICES_COUNT_QW,
	IA_PRIMITIVES_COUNT_QW,
	VS_INVOCATION_COUNT_QW,
	GS_INVOCATION_COUNT_QW,
	GS_PRIMITIVES_COUNT_QW,
	CL_INVOCATION_COUNT_QW,
	CL_PRIMITIVES_COUNT_QW,
	PS_INVOCATION_COUNT_QW,
	PS_DEPTH_COUNT_QW,
};

const char *stats_reg_names[STATS_COUNT] = {
	"vert fetch",
	"prim fetch",
	"VS invocations",
	"GS invocations",
	"GS prims",
	"CL invocations",
	"CL prims",
	"PS invocations",
	"PS depth pass",
};

uint64_t stats[STATS_COUNT];
uint64_t last_stats[STATS_COUNT];

static unsigned long
gettime(void)
{
    struct timeval t;
    do_gettimeofday(&t);
    return (t.tv_usec + (t.tv_sec * 1000000));
}

static int
top_bits_sort(const void *a, const void *b)
{
	struct top_bit * const *bit_a = a;
	struct top_bit * const *bit_b = b;
	int a_count = (*bit_a)->count;
	int b_count = (*bit_b)->count;

	if (a_count < b_count)
		return 1;
	else if (a_count == b_count)
		return 0;
	else
		return -1;
}

static void
update_idle_bit(struct top_bit *top_bit)
{
	uint32_t reg_val;

	if (top_bit->bit->reg == INST_DONE_1)
		reg_val = instdone1;
	else
		reg_val = instdone;

	if ((reg_val & top_bit->bit->bit) == 0)
		top_bit->count++;
}

static void
print_clock(char *name, int clock) {
	if (clock == -1)
		DRM_ERROR("%s clock: unknown", name);
	else
		DRM_ERROR("%s clock: %d Mhz", name, clock);
}

static void
print_clock_info(struct drm_device *dev)
{
	uint16_t gcfgc;

	if (IS_GM45(dev)) {
		int core_clock = -1;

		(void) pci_read_config_word(dev->pdev, I915_GCFGC, &gcfgc);

		switch (gcfgc & 0xf) {
		case 8:
			core_clock = 266;
			break;
		case 9:
			core_clock = 320;
			break;
		case 11:
			core_clock = 400;
			break;
		case 13:
			core_clock = 533;
			break;
		}
		print_clock("core", core_clock);
	} else if (INTEL_INFO(dev)->gen >= 4 && IS_MOBILE(dev)) {
		int render_clock = -1, sampler_clock = -1;

		(void) pci_read_config_word(dev->pdev, I915_GCFGC, &gcfgc);

		switch (gcfgc & 0xf) {
		case 2:
			render_clock = 250; sampler_clock = 267;
			break;
		case 3:
			render_clock = 320; sampler_clock = 333;
			break;
		case 4:
			render_clock = 400; sampler_clock = 444;
			break;
		case 5:
			render_clock = 500; sampler_clock = 533;
			break;
		}

		print_clock("render", render_clock);
		print_clock("sampler", sampler_clock);
	} else if (IS_I945GM(dev) && IS_MOBILE(dev)) {
		int render_clock = -1, display_clock = -1;

		(void) pci_read_config_word(dev->pdev, I915_GCFGC, &gcfgc);

		switch (gcfgc & 0x7) {
		case 0:
			render_clock = 166;
			break;
		case 1:
			render_clock = 200;
			break;
		case 3:
			render_clock = 250;
			break;
		case 5:
			render_clock = 400;
			break;
		}

		switch (gcfgc & 0x70) {
		case 0:
			display_clock = 200;
			break;
		case 4:
			display_clock = 320;
			break;
		}
		if (gcfgc & (1 << 7))
		    display_clock = 133;

		print_clock("render", render_clock);
		print_clock("display", display_clock);
	} else if (IS_I915GM(dev) && IS_MOBILE(dev)) {
		int render_clock = -1, display_clock = -1;

		(void) pci_read_config_word(dev->pdev, I915_GCFGC, &gcfgc);

		switch (gcfgc & 0x7) {
		case 0:
			render_clock = 160;
			break;
		case 1:
			render_clock = 190;
			break;
		case 4:
			render_clock = 333;
			break;
		}
		if (gcfgc & (1 << 13))
		    render_clock = 133;

		switch (gcfgc & 0x70) {
		case 0:
			display_clock = 190;
			break;
		case 4:
			display_clock = 333;
			break;
		}
		if (gcfgc & (1 << 7))
		    display_clock = 133;

		print_clock("render", render_clock);
		print_clock("display", display_clock);
	}
}

static void gen6_force_wake_get(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int count;

	if (!IS_GEN6(dev))
		return;

	/* This will probably have undesirable side-effects upon the system. */
	count = 0;
	while (count++ < 50 && (I915_READ(FORCEWAKE_ACK) & 1))
		udelay(10);

	I915_WRITE(FORCEWAKE, 1);
	POSTING_READ(FORCEWAKE);

	count = 0;
	while (count++ < 50 && (I915_READ(FORCEWAKE_ACK) & 1) == 0)
		udelay(10);
}

static void gen6_force_wake_put(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	if (!IS_GEN6(dev))
		return;

	I915_WRITE(FORCEWAKE, 0);
	POSTING_READ(FORCEWAKE);
}

static void ring_init(struct drm_device *dev, struct ring *ring)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	gen6_force_wake_get(dev);
	ring->size = (((ring_read(ring, _RING_LEN) & RING_NR_PAGES) >> 12) + 1) * 4096;
	gen6_force_wake_put(dev);
}

static void ring_reset(struct ring *ring)
{
	ring->idle = ring->full = 0;
}

static void ring_sample(struct drm_device *dev, struct ring *ring)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int full;

	if (!ring->size)
		return;

	gen6_force_wake_get(dev);
	ring->head = ring_read(ring, _RING_HEAD) & HEAD_ADDR;
	ring->tail = ring_read(ring, _RING_TAIL) & TAIL_ADDR;
	gen6_force_wake_put(dev);

	if (ring->tail == ring->head)
		ring->idle++;

	full = ring->tail - ring->head;
	if (full < 0)
		full += ring->size;
	ring->full += full;
}

static void ring_print(struct ring *ring, unsigned long samples_per_sec)
{
	int samples_to_percent_ratio, percent;

	/* Calculate current value of samples_to_percent_ratio */
	samples_to_percent_ratio = (ring->idle * 100) / samples_per_sec;
	percent = 100 - samples_to_percent_ratio;

		if (!ring->size)
			return;

		DRM_ERROR("%25s busy: %3d%%: ", ring->name, percent);
		DRM_ERROR("%24s space: %d/%d (%d%%)",
			   ring->name,
			   (int)(ring->full / samples_per_sec),
			   ring->size,
			   (int)((ring->full / samples_to_percent_ratio) / ring->size));
}


void i915_gpu_top(struct drm_device *dev)
{
	struct ring render_ring = {
		.name = "render",
		.mmio = 0x2030,
	}, bsd_ring = {
		.name = "bitstream",
		.mmio = 0x4030,
	}, bsd6_ring = {
		.name = "bitstream",
		.mmio = 0x12030,
	}, blt_ring = {
		.name = "blitter",
		.mmio = 0x22030,
	};
	struct drm_i915_private *dev_priv = dev->dev_private;
	uint32_t samples_per_sec = SAMPLES_PER_SEC;
	struct timeval elapsed_time;
	int i,j, k;
	struct timeval t1, ti, tf, t2;
	uint64_t def_sleep;
	uint64_t last_samples_per_sec;
	int percent;

	init_instdone_definitions(dev);

	for (i = 0; i < num_instdone_bits; i++) {
		top_bits[i].bit = &instdone_bits[i];
		top_bits[i].count = 0;
		top_bits_sorted[i] = &top_bits[i];
	}

	ring_init(dev, &render_ring);
	if (IS_GEN4(dev) || IS_GEN5(dev))
		ring_init(dev, &bsd_ring);
	if (IS_GEN6(dev)) {
		ring_init(dev, &bsd6_ring);
		ring_init(dev, &blt_ring);
	}

	/* Initialize GPU stats */
	if (HAS_STATS_REGS(dev)) {
		for (i = 0; i < STATS_COUNT; i++) {
			uint32_t stats_high, stats_low, stats_high_2;

			do {
				stats_high = I915_READ(stats_regs[i] + 4);
				stats_low = I915_READ(stats_regs[i]);
				stats_high_2 = I915_READ(stats_regs[i] + 4);
			} while (stats_high != stats_high_2);

			last_stats[i] = (uint64_t)stats_high << 32 |
				stats_low;
		}
	}
	//start record
	for (k = 0; k < 200000; k++) {
		def_sleep = (1000000 / samples_per_sec);
		last_samples_per_sec = samples_per_sec;

//		t1 = gettime();
		do_gettimeofday(&t1);

		ring_reset(&render_ring);
		ring_reset(&bsd_ring);
		ring_reset(&bsd6_ring);
		ring_reset(&blt_ring);

		for (i = 0; i < samples_per_sec; i++) {
			long interval;
			long t_diff;
			do_gettimeofday(&ti);
			if (INTEL_INFO(dev)->gen >= 4) {
				instdone = I915_READ(INST_DONE_I965);
				instdone1 = I915_READ(INST_DONE_1);
			} else
				instdone = I915_READ(INST_DONE);

			for (j = 0; j < num_instdone_bits; j++)
				update_idle_bit(&top_bits[j]);

			ring_sample(dev, &render_ring);
			ring_sample(dev, &bsd_ring);
			ring_sample(dev, &bsd6_ring);
			ring_sample(dev, &blt_ring);

			do_gettimeofday(&tf);
			t_diff = (tf.tv_sec - t1.tv_sec) * 1000000 + tf.tv_usec - t1.tv_usec;
			if (t_diff >= 1000000) {
				/* We are out of sync, bail out */
				last_samples_per_sec = i+1;
				break;
			}
			t_diff = (tf.tv_sec - ti.tv_sec) * 1000000 + tf.tv_usec - ti.tv_usec;
			interval = def_sleep - t_diff;
			if (interval > 0)
				udelay(interval);
		}

		if (HAS_STATS_REGS(dev)) {
			for (i = 0; i < STATS_COUNT; i++) {
				uint32_t stats_high, stats_low, stats_high_2;

				do {
					stats_high = I915_READ(stats_regs[i] + 4);
					stats_low = I915_READ(stats_regs[i]);
					stats_high_2 = I915_READ(stats_regs[i] + 4);
				} while (stats_high != stats_high_2);

				stats[i] = (uint64_t)stats_high << 32 |
					stats_low;
			}
		}



		//sort
//		qsort(top_bits_sorted, num_instdone_bits,
//		      sizeof(struct top_bit *), top_bits_sort);
		struct top_bit tmp_top;
		for (i = 0; i < num_instdone_bits; i++) {
			for (j = i+1; j < num_instdone_bits; j++) {
				if (top_bits_sort(&top_bits_sorted[i], &top_bits_sorted[j]) == 1) {
					tmp_top.bit = top_bits_sorted[i]->bit;
					tmp_top.count = top_bits_sorted[i]->count;

					top_bits_sorted[i]->bit = top_bits_sorted[j]->bit;
					top_bits_sorted[i]->count = top_bits_sorted[j]->count;

					top_bits_sorted[j]->bit = tmp_top.bit;
					top_bits_sorted[j]->count = tmp_top.count;
				}
			}
		}
		//print info
		int max_lines = -1;
		max_lines = num_instdone_bits;

		max_lines = 15;

		do_gettimeofday(&t2);
		timevalsub(&t2, &t1);
		timevaladd(&elapsed_time, &t2);
		long ttt = t2.tv_sec * 1000000 + t2.tv_usec;
		DRM_ERROR("caculate time %ld usec!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", ttt);

		print_clock_info(dev);

		ring_print(&render_ring, last_samples_per_sec);
		ring_print(&bsd_ring, last_samples_per_sec);
		ring_print(&bsd6_ring, last_samples_per_sec);
		ring_print(&blt_ring, last_samples_per_sec);

		for (i = 0; i < max_lines; i++) {
			if (top_bits_sorted[i]->count > 0) {
				percent = (top_bits_sorted[i]->count * 100) /
					last_samples_per_sec;
				DRM_ERROR("%30s: %3d%%: ",
						 top_bits_sorted[i]->bit->name,
						 percent);
			} else {
				DRM_ERROR("  ");
			}

			if (i < STATS_COUNT && HAS_STATS_REGS(dev)) {
				DRM_ERROR("%13s: %lu (%ld/sec)",
					   stats_reg_names[i],
					   stats[i],
					   stats[i] - last_stats[i]);
				last_stats[i] = stats[i];
			} else {
				if (!top_bits_sorted[i]->count)
					break;
			}
		}

		for (i = 0; i < num_instdone_bits; i++) {
			top_bits_sorted[i]->count = 0;

			if (i < STATS_COUNT)
				last_stats[i] = stats[i];
		}
		udelay(4000000);
	}
}

void gpu_top_handler(void *data)
{
	struct drm_device *dev = (struct drm_device *)data;
	struct timeval t;
	do_gettimeofday(&t);
	DRM_ERROR("in %ld", t.tv_sec);
	i915_gpu_top(dev);
/*
	mod_timer(&dev_priv->gpu_top_timer,
		  jiffies + msecs_to_jiffies(5000));
*/
}

void ring_dump(struct drm_device *dev, struct intel_ring_buffer *ring)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (ring) {
		/* dump ring infor*/
		unsigned int *virt;
		u32 tail, head;
		head = I915_READ_HEAD(ring) & HEAD_ADDR;
		tail = I915_READ_TAIL(ring) & TAIL_ADDR;

		DRM_ERROR("Dump %s ring", ring->name);
		DRM_ERROR("HEAD 0x%x TAIL 0x%x", head, tail);
		DRM_ERROR("seq %d", ring->get_seqno(ring, true));

		if (head == tail)
			return;

		for (int i = 0; i < 200; i++) {
			virt = (unsigned int *)((intptr_t)ring->virtual_start + head + (i-180)*4);
			DRM_ERROR("%s[0x%x]: 0x%x", ring->name, head + (i-180)*4, virt[0]);
		}


	}
}

void gtt_dump(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int ret;

	if (gpu_panic_on_hang) {
		dev->gtt_dump = kmem_zalloc(gtt_total_entries(dev_priv->gtt) * sizeof (uint32_t), KM_NOSLEEP);
		ret = drm_agp_rw_gtt(dev, gtt_total_entries(dev_priv->gtt),
				0, (void *) dev->gtt_dump, 0);
		if (ret)
			DRM_ERROR("failed to dump whole gtt");
		panic("gpu hang");
	}
}

void register_dump(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	DRM_ERROR("PGTBL_ER: 0x%lx", I915_READ(PGTBL_ER));
	DRM_ERROR("INSTPM: 0x%lx", I915_READ(INSTPM));
	DRM_ERROR("EIR: 0x%lx", I915_READ(EIR));
	DRM_ERROR("ERROR_GEN6: 0x%lx", I915_READ(ERROR_GEN6));

	DRM_ERROR("Blitter command stream:");
	DRM_ERROR("  IPEIR: 0x%08x",
		I915_READ(0x22064));
	DRM_ERROR("  IPEHR: 0x%08x",
		I915_READ(0x22068));
	DRM_ERROR("  INSTDONE: 0x%08x",
		I915_READ(0x2206C));
	DRM_ERROR("  ACTHD: 0x%08x",
		I915_READ(0x22074));
	DRM_ERROR("Render command stream:");
	DRM_ERROR("  IPEIR: 0x%08x",
		I915_READ(IPEIR_I965));
	DRM_ERROR("  IPEHR: 0x%08x",
		I915_READ(IPEHR_I965));
	DRM_ERROR("  INSTDONE: 0x%08x",
		I915_READ(INSTDONE_I965));
	DRM_ERROR("  INSTPS: 0x%08x",
		I915_READ(INSTPS));
	DRM_ERROR("  INSTDONE1: 0x%08x",
		I915_READ(INSTDONE1));
	DRM_ERROR("  ACTHD: 0x%08x",
		I915_READ(ACTHD_I965));
	DRM_ERROR("  DMA_FADD_P: 0x%08x",
		I915_READ(0x2078));

	DRM_ERROR("Graphics Engine Fault 0x%lx",
		I915_READ(0x04094));
	DRM_ERROR("Media Engine Fault 0x%lx",
		I915_READ(0x04194));
	DRM_ERROR("Blitter  Engine Fault 0x%lx",
		I915_READ(0x04294));
}
