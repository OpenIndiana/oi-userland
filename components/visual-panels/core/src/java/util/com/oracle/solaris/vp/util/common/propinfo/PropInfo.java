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

public interface PropInfo<M, T> {
    /**
     * Retrieve a {@code Comparator} for this property.  This allows multiple
     * values of this property to be sorted.
     *
     * @return	    a {@code Comparator}, or {@code null} to use a default
     *		    {@code Comparator} for this type.
     */
    Comparator<? extends T> getComparator();

    /**
     * Retrieve a description for this property.
     *
     * @return	    a {@code String}, or {@code null} if no description is
     *		    appropriate
     */
    String getDescription();

    /**
     * Retrieve a label for this property.
     *
     * @return	    a non-{@code null} {@code String}
     */
    String getLabel();

    /**
     * Retrieve this property from the given object.
     */
    T getValue(M o);

    /**
     * Determines whether this property is editable in the given object.
     */
    boolean isEditable(M o);

    /**
     * Determines whether this property should be displayed as enabled.
     */
    boolean isEnabled(M o);

    /**
     * Indicates whether this property can be sorted.
     */
    boolean isSortable();

    /**
     * Sets the given value of this property in the given object (optional
     * operation).
     */
    void setValue(M o, T value);
}
