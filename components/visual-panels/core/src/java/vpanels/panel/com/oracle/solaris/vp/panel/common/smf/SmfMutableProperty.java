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

package com.oracle.solaris.vp.panel.common.smf;

import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.util.misc.property.MutableProperty;

/**
 * The {@code SmfMutableProperty} interface represents any {@link
 * MutableProperty} whose value is taken from the SMF repository.
 */
public interface SmfMutableProperty<T> extends MutableProperty<T> {
    /**
     * Gets the value of this {@code SmfMutableProperty} from the SMF
     * repository.
     *
     * @exception   ScfException
     *		    if an error occurs when reading from the repository
     */
    T getRepoValue() throws ScfException;

    /**
     * Sets this {@link MutableProperty}'s current value in the SMF
     * repository, then calls {@link #save}.  Note that the order of these two
     * steps is critical, since the latter should not be done until the former
     * succeeds.
     *
     * @exception   ScfException
     *		    if an error occurs when writing to the repository
     */
    void saveToRepo() throws ScfException;

    /**
     * Sets the given value in the SMF repository.
     *
     * @exception   ScfException
     *		    if an error occurs when writing to the repository
     */
    void setRepoValue(T values) throws ScfException;

    /**
     * Populates this {@link MutableProperty}'s saved value from the SMF
     * repository, then calls {@link #update update}{@code (force)}.
     *
     * @exception   ScfException
     *		    if an error occurs when reading from the repository
     */
    void updateFromRepo(boolean force) throws ScfException;
}
