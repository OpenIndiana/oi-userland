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

import java.util.*;
import javax.swing.DefaultListSelectionModel;

public class ValidatingListSelectionModel extends DefaultListSelectionModel {
    //
    // Instance data
    //

    private List<Integer> selection = new LinkedList<Integer>();
    private int anchor = -1;
    private int lead = -1;

    //
    // DefaultListSelectionModel methods
    //

    @Override
    protected void fireValueChanged(int firstIndex, int lastIndex,
	boolean isAdjusting) {

	if (!isAdjusting) {
	    if (validateSelection()) {
		save();
		super.fireValueChanged(firstIndex, lastIndex, isAdjusting);
	    } else {
		setValueIsAdjusting(true);
		revert();
		setValueIsAdjusting(false);
	    }
	}
    }

    //
    // ValidatingListSelectionModel methods
    //

    /**
     * Verifies that the current selection is valid.  This default
     * implementation returns {@code true}.
     *
     * @return	    {@code true} if the selection is valid, {@code false}
     *		    otherwise
     */
    protected boolean validateSelection() {
	return true;
    }

    protected void revert() {
	clearSelection();
	for (int i = 0, n = selection.size(); i < n; i++) {
	    int first = selection.get(i);
	    int last = first;
	    if (i < n - 1 && selection.get(i + 1) == null) {
		i += 2;
		last = selection.get(i);
	    }
	    addSelectionInterval(first, last);
	}
	setAnchorSelectionIndex(anchor);
	setLeadSelectionIndex(lead);
    }

    @SuppressWarnings({"fallthrough"})
    protected void save() {
	anchor = getAnchorSelectionIndex();
	lead = getLeadSelectionIndex();
	int min = getMinSelectionIndex();
	int max = getMaxSelectionIndex();

	selection.clear();
	if (min < 0 || max < 0) {
	    return;
	}

	for (int i = min; i <= max; i++) {
	    if (isSelectedIndex(i)) {
		int first = i;
		selection.add(first);
		for (i++; i <= max && isSelectedIndex(i); i++);
		int last = i - 1;

		switch (last - first) {
		default:
		    selection.add(null);

		case 1:
		    selection.add(last);

		case 0:
		}
	    }
	}
    }
}
