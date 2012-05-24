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

package com.oracle.solaris.vp.util.misc.event;

import java.beans.PropertyChangeListener;

public interface PropertyChangeEventSource {
    /**
     * Adds a {@code PropertyChangeListener} for all properties.
     */
    void addPropertyChangeListener(PropertyChangeListener l);

    /**
     * Adds a {@code PropertyChangeListener} for the given property.
     */
    void addPropertyChangeListener(String property, PropertyChangeListener l);

    /**
     * Removes a {@code PropertyChangeListener} for the given property.
     *
     * @return	    {@code true} if the given listener was in the list, {@code
     *		    false} otherwise
     */
    boolean removePropertyChangeListener(String property,
	PropertyChangeListener l);

    /**
     * Removes a {@code PropertyChangeListener} for all properties.
     *
     * @return	    {@code true} if the given listener was in the list, {@code
     *		    false} otherwise
     */
    boolean removePropertyChangeListener(PropertyChangeListener l);
}
