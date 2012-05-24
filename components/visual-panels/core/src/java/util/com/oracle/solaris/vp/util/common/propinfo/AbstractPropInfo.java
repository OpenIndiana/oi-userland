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
 * Copyright (c) 2008, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.util.common.propinfo;

import java.util.Comparator;

public abstract class AbstractPropInfo<M, T> implements PropInfo<M, T> {
    //
    // Instance data
    //

    private String description;
    private String label;
    private boolean sortable;
    private boolean editable;

    //
    // Constructors
    //

    public AbstractPropInfo(
	String label, String description, boolean sortable, boolean editable) {

	this.label = label;
	this.description = description;
	this.sortable = sortable;
	this.editable = editable;
    }

    //
    // PropInfo methods
    //

    /**
     * Default implementation that returns {@code null}.
     */
    @Override
    public Comparator<T> getComparator() {
	return null;
    }

    @Override
    public String getDescription() {
	return description;
    }

    @Override
    public String getLabel() {
	return label;
    }

    @Override
    public boolean isEditable(M o) {
	return editable;
    }

    /**
     * Default implementation that returns {@code true}.
     */
    @Override
    public boolean isEnabled(M o) {
	return true;
    }

    @Override
    public boolean isSortable() {
	return sortable;
    }

    /**
     * Default implementation that does nothing.
     */
    @Override
    public void setValue(M o, T value) {
    }
}
