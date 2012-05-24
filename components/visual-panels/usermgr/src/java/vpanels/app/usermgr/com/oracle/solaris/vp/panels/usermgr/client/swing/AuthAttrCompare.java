/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright (c) 1998, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panels.usermgr.client.swing;


import java.util.*;

/**
 * SMC code adapted for Visual Panels
 *
 * The AuthAttrCompare class implements the Compare interface
 * for the QuickSort sorting class.  This implementation of compare
 * compares two AuthAttrObj objects based upon comparing the
 * authorization names in each object.
 *
 */

public class AuthAttrCompare implements Compare {

    /**
     * The compare method compares two AuthAttrObj objects by comparing
     * their authorization names.  The parameters are specified as Object class
     * objects for QuickSort.  Special handling is required for header entry
     * objects so that the headers with fewer name elements precede headers
     * with more name elements, when the name elements match.
     *
     * @param	a   The first AuthAttrObj object.
     * @param	b   The second AuthAttrObj object.
     *
     */
    public final int doCompare(Object a, Object b) {

	AuthAttrObj e1, e2;
	StringTokenizer e1Tok, e2Tok;
	String e1Name, e2Name;
	int e1Count, e2Count;

	e1 = (AuthAttrObj)a;
	e2 = (AuthAttrObj)b;
	e1Name = e1.getAuthName();
	e2Name = e2.getAuthName();
	e1Count = 0;
	e2Count = 0;

	// headers must immediately precede their authorizations
	if (e1Name.endsWith("."))
	    e1Count = 1;
	if (e2Name.endsWith("."))
	    e2Count = 1;

	// The entries must have the same
	// number of components (dots) to be lexically compared
	e1Tok = new StringTokenizer(e1Name, ".", true);
	e2Tok = new StringTokenizer(e2Name, ".", true);
	e1Count += e1Tok.countTokens();
	e2Count += e2Tok.countTokens();
	if (e1Count == e2Count)
	    return (e1Name.compareTo(e2Name));
	else if (e1Count > e2Count)
	    return 1;
	else
	    return -1;
    }

}
