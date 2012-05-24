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

package com.oracle.solaris.vp.util.misc.property;

import java.beans.PropertyChangeListener;
import com.oracle.solaris.vp.util.misc.Changeable;
import com.oracle.solaris.vp.util.misc.converter.DualConverter;

public interface MutableProperty<T> extends Changeable {
    /**
     * Adds a {@code PropertyChangeListener} to listen for changes in the {@link
     * #getValue current} or {@link #getSavedValue saved} value of this
     * property.
     */
    void addPropertyChangeListener(PropertyChangeListener listener);

    /**
     * Removes a {@code PropertyChangeListener} from notifications of changes in
     * the {@link #getValue value} of this property.
     */
    boolean removePropertyChangeListener(PropertyChangeListener listener);

    /**
     * Gets a {@link DualConverter} to convert the value of this {@code
     * MutableProperty} to and from a {@code String}.
     *
     * @return	    a {@link DualConverter}, or {@code null} if the value of
     *		    this {@code MutableProperty} cannot be converted to and from
     *		    a {@code String}.
     */
    DualConverter<String, T> getConverter();

    /**
     * Gets the name of this property.
     *
     * @return	    a {@code String}, or {@code null} if this property has no
     *		    name
     */
    String getPropertyName();

    /**
     * Gets the wrapped model's saved value.
     */
    T getSavedValue();

    /**
     * Gets the wrapped model's current value.
     */
    T getValue();

    /**
     * Sets the wrapped model's saved value.
     */
    void setSavedValue(T saved);

    /**
     * Sets the wrapped model's current value.
     */
    void setValue(T t);

    /**
     * Sets the given value as the {@link #getSavedValue saved value}, then
     * {@link #reset reset}s this {@code MutableProperty} if the current and
     * saved values hadn't differed prior to this update.
     *
     * @param	    value
     *		    the new saved value
     *
     * @param	    force
     *		    if {@code true}, {@link #reset reset}s unconditionally after
     *		    setting the new saved value
     */
    void update(T value, boolean force);
}
