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
 * Copyright (c) 2009, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.util.swing;

import javax.swing.DefaultListModel;
import com.oracle.solaris.vp.util.misc.ObjectUtil;

@SuppressWarnings({"serial"})
public class SortedListModel extends DefaultListModel {
    @Override
    public void add(int index, Object element) {
	throw new IllegalArgumentException(
	    "unsupported method in sorted model");
    }

    @Override
    public void addElement(Object obj) {
	int i = 0;
	try {
	    for (int n = getSize(); i < n; i++) {

		Object listObj = getElementAt(i);
		if (listObj instanceof Comparable) {

		    @SuppressWarnings({"unchecked"})
		    Comparable<Object> comparable = (Comparable<Object>)listObj;
		    if (ObjectUtil.compare(comparable, obj) >= 0) {
			break;
		    }
		}
	    }

	// Thrown by Comparable.compareTo()
	} catch (ClassCastException e) {
	    i = getSize();
	}

	super.add(i, obj);
    }

    @Override
    public void insertElementAt(Object obj, int index) {
	throw new IllegalArgumentException(
	    "unsupported method in sorted model");
    }
}
