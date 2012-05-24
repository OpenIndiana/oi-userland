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

package com.oracle.solaris.vp.util.misc;

import javax.swing.event.ChangeListener;

public interface Changeable {
    /**
     * Adds a {@code ChangeListener} to listen for changes in this property.
     */
    void addChangeListener(ChangeListener listener);

    /**
     * Determines whether the current value has changed since it was saved.
     */
    boolean isChanged();

    /**
     * Removes a {@code ChangeListener} from notifications of changes in this
     * property.
     */
    boolean removeChangeListener(ChangeListener listener);

    /**
     * Resets this {@code Changeable}'s saved value to its current value.
     */
    void reset();

    /**
     * Sets this {@code Changeable}'s current value to its saved value.
     */
    void save();
}
