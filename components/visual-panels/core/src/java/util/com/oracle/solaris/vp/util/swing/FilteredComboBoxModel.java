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

import java.util.Collection;
import javax.swing.ComboBoxModel;
import com.oracle.solaris.vp.util.misc.ObjectUtil;
import com.oracle.solaris.vp.util.misc.predicate.Predicate;

public class FilteredComboBoxModel<T> extends FilteredListModel<T>
    implements ComboBoxModel {

    //
    // Instance data
    //

    private T selected;

    //
    // Constructors
    //

    public FilteredComboBoxModel(Collection<T> items, Predicate<T> predicate) {
	super(items, predicate);
    }

    public FilteredComboBoxModel(Collection<T> items) {
	super(items);
    }

    //
    // ComboBoxModel methods
    //

    @Override
    public T getSelectedItem() {
	return selected;
    }

    @Override
    @SuppressWarnings({"unchecked"})
    public void setSelectedItem(Object selected) {
	if (!ObjectUtil.equals(this.selected, selected)) {
	    this.selected = (T)selected;
	    fireContentsChanged(-1, -1);
	}
    }
}
