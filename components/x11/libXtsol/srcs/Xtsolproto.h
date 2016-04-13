/* Copyright (c) 2004, 2013, Oracle and/or its affiliates. All rights reserved.
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
 * X Server Trusted Extensions
 */

#ifndef _XTSOLPROTO_H
#define _XTSOLPROTO_H

#define TSOL_NUM_EVENTS		0	/* New events defined by this extension */
#define TSOL_NUM_ERRORS		0	/* New errors defined by this extension */

/* extension request minor codes */
#define X_SetClearance            2
#define X_SetPolyInstInfo         3
#define X_SetPropLabel            4
#define X_SetPropUID              5
#define X_SetResLabel             6    
#define X_SetResUID               7
#define X_SetTrusted              8
#define X_GetClientAttributes     9
#define X_GetClientLabel         10
#define X_GetPropAttributes      11
#define X_GetResAttributes       12
#define X_MakeTPWindow           13
#define X_MakeTrustedWindow      14
#define X_MakeUntrustedWindow    15
#define X_TSOLIntern             16

/* extension request sizes */
#define sz_xSetClearanceReq           0
#define sz_xSetPolyInstInfoReq       16
#define sz_xSetPropLabelReq          20
#define sz_xSetPropUIDReq            16
#define sz_xSetResLabelReq           16
#define sz_xSetResUIDReq             16
#define sz_xSetTrustedReq             0
#define sz_xGetClientAttributesReq    8
#define sz_xGetClientLabelReq        12
#define sz_xGetPropAttributesReq     16
#define sz_xGetResAttributesReq      12
#define sz_xMakeTPWindowReq           8
#define sz_xMakeTrustedWindowReq      8
#define sz_xMakeUntrustedWindowReq    8
#define sz_xTSOLInternReq             0


/* extension reply sizes */
#define sz_xGetClientAttributesReply  32
#define sz_xGetClientLabelReply       32
#define sz_xGetPropAttributesReply    32
#define sz_xGetResAttributesReply     32
#define sz_xTSOLInternReply            0


/* extension request encoding format */
typedef struct {
    CARD8  reqType;                      /* extension major code */
    BYTE   minorCode;                    /* = 3                  */
    CARD16 length                B16;    /* = 18; packet size=72 */
    CARD32 uid                   B32;    /* user id              */
    CARD32 enabled               B32;    /* enable matching      */
    CARD16 sllength              B16;    /* length of SL         */
    CARD16 pad1                  B16;    /* padding              */
} xSetPolyInstInfoReq;

typedef struct {
    CARD8  reqType;                      /* extension major code */
    BYTE   minorCode;                    /* = 4                  */
    CARD16 length                B16;    /* = 18; packet size=72 */
    CARD32 id                    B32;    /* resource ID          */
    CARD32 atom                  B32;    /* atom ID              */
    CARD16 labelType             B16;
    CARD16 pad1                  B16;
    CARD16 sllength              B16;    /* length of SL         */
    CARD16 illength              B16;    /* length of IL         */
} xSetPropLabelReq;

typedef struct {
    CARD8  reqType;                      /* extension major code */
    BYTE   minorCode;                    /* = 5                  */
    CARD16 length                B16;    /* = 4; packet size= 16 */
    CARD32 id                    B32;    /* resource ID          */
    CARD32 atom                  B32;    /* atom  ID             */
    CARD32 uid                   B16;    /* UID                  */
} xSetPropUIDReq;

typedef struct {
    CARD8  reqType;                      /* extension major code */
    BYTE   minorCode;                    /* = 6                  */
    CARD16 length                B16;    /* = 17; packet size=68 */
    CARD32 id                    B32;    /* resource ID          */
    CARD16 resourceType          B16;    /* 0:window, 1:pixmap   */
    CARD16 labelType             B16;    /*                      */
    CARD16 sllength              B16;    /* length of SL         */
    CARD16 illength              B16;    /* length of IL or IIL  */
} xSetResLabelReq;

typedef struct {
    CARD8  reqType;                      /* extension major code */
    BYTE   minorCode;                    /* = 7                  */
    CARD16 length                B16;    /* = 4; packet size= 16 */
    CARD32 id                    B32;    /* resource ID          */
    CARD16 resourceType          B16;    /* 0:window, 1:pixmap   */
    CARD16 pad1                  B16;    /* not used             */
    CARD32 uid                   B16;
} xSetResUIDReq;

typedef struct {
    CARD8  reqType;                      /* Extension major code */
    BYTE   minorCode;                    /* = 9                  */
    CARD16 length                B16;    /* = 4; packet size=16  */
    CARD32 id                    B32;    /* Client ID            */
} xGetClientAttributesReq;

typedef struct {
    CARD8  reqType;                      /* extension major code */
    BYTE   minorCode;                    /* = 10                 */
    CARD16 length                B16;    /* = 4; packet size= 16 */
    CARD32 id                    B32;    /* client ID            */
    CARD16 mask                  B16;
    CARD16 pad;
} xGetClientLabelReq;

typedef struct {
    CARD8  reqType;                      /* Extension major code */
    BYTE   minorCode;                    /* = 11                 */
    CARD16 length                B16;    /* = 4; packet size=16  */
    CARD32 id                    B32;    /* resource ID          */
    CARD32 atom                  B32;    /* resource ID          */
    CARD16 mask                  B16;
    CARD16 pad                   B16;    /* not used             */
} xGetPropAttributesReq;

typedef struct {
    CARD8  reqType;                      /* Extension major code */
    BYTE   minorCode;                    /* = 12                 */
    CARD16 length                B16;    /* = 3; packet size=12  */
    CARD32 id                    B32;    /* resource ID          */
    CARD16 resourceType          B16;    /* 0:window; 1:pixmap   */
    CARD16 mask                  B16;
} xGetResAttributesReq;

typedef struct {
    CARD8  reqType;                      /* extension major code */
    BYTE   minorCode;                    /* = 13                 */
    CARD16 length                B16;    /* = 4; packet size= 16 */
    CARD32 id                    B32;    /* resource ID          */
} xMakeTPWindowReq;

typedef struct {
    CARD8  reqType;                      /* extension major code */
    BYTE   minorCode;                    /* = 14                 */
    CARD16 length                B16;    /* = 4; packet size= 16 */
    CARD32 id                    B32;    /* resource ID          */
} xMakeTrustedWindowReq;

typedef struct {
    CARD8  reqType;                      /* extension major code */
    BYTE   minorCode;                    /* = 15                 */
    CARD16 length                B16;    /* = 4; packet size= 16 */
    CARD32 id                    B32;    /* resource ID          */
} xMakeUntrustedWindowReq;
 
/* extension reply encoding format */
typedef struct {
    BYTE   type;                         /* = X_Reply            */
    BYTE   trustflag;                    /* set if client masked as trusted */
    CARD16 sequenceNumber        B16;
    CARD32 length                B32;    /* = 4;                 */
    CARD32 uid                   B32;
    CARD32 pid                   B32;
    CARD32 gid                   B32;
    CARD32 auditid               B32;
    CARD32 sessionid             B32;
    CARD32 iaddr;                        /* internet address    */
} xGetClientAttributesReply;

typedef struct {
    BYTE   type;                         /* = X_Reply            */
    BYTE   pad1;                         /* not used             */
    CARD16 sequenceNumber        B16;
    CARD32 length                B32;    /* = blabel_bytes / 4;  */
    CARD32 blabel_bytes          B32;    /* = blabel_size()      */
    CARD32 pad2                  B32;
    CARD32 pad3                  B32;
    CARD32 pad4                  B32;
    CARD32 pad5                  B32;
    CARD32 pad6                  B32;
} xGetClientLabelReply;

typedef struct {
    BYTE   type;                         /* = X_Reply            */
    BYTE   pad1;                         /* not used             */
    CARD16 sequenceNumber        B16;
    CARD32 length                B32;    /* = 4;                 */
    CARD32 uid                   B32;
    CARD16 sllength              B16;
    CARD16 illength              B16;
    CARD32 pad2                  B32;
    CARD32 pad3                  B32;
    CARD32 pad4                  B32;
    CARD32 pad5                  B32;
} xGetPropAttributesReply;

typedef struct {
    BYTE   type;                         /* = X_Reply            */
    BYTE   pad1;                         /* not used             */
    CARD16 sequenceNumber        B16;
    CARD32 length                B32;    /* = 4;                 */
    CARD32 uid                   B32;
    CARD32 owneruid              B32;
    CARD16 sllength              B16;
    CARD16 illength              B16;
    CARD16 iillength             B16;
    CARD16 pad2                  B16;
    CARD32 pad3                  B32;
    CARD32 pad4                  B32;
} xGetResAttributesReply;


#define DOOWNERUID       1000
#define SESSIONHI        1010
#define SESSIONLO        1020
#define STRIPEHEIGHT     1030
#define INPUTIL          1040

#endif /* _XTSOLPROTO_H */
