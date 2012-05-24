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

package com.oracle.solaris.vp.util.swing.time;

import java.beans.PropertyChangeListener;
import java.util.*;

@SuppressWarnings({"serial"})
public interface TimeModel {
    /**
     * The name of the property changed with {@link #setTimeOffset}.
     */
    String PROPERTY_TIME_OFFSET = "timeOffset";

    /**
     * The name of the property changed when the {@link #updateTime} is called.
     */
    String PROPERTY_TIME = "time";

    /**
     * The name of the property changed when the {@link #setTimeZone time zone}
     * is set.
     */
    String PROPERTY_TIME_ZONE = "timeZone";

    /**
     * Adds a {@code PropertyChangeListener} to be notified upon changes in all
     * properties.
     */
    void addPropertyChangeListener(PropertyChangeListener listener);

    /**
     * Adds a {@code PropertyChangeListener} to be notified upon changes in the
     * property of the given name.
     */
    void addPropertyChangeListener(String propertyName,
	PropertyChangeListener listener);

    /**
     * Gets a clone of this {@code TimeModel}'s {@code Calendar} at the point
     * that it was last {@link #updateTime updated}.
     */
    Calendar getCalendar();

    /**
     * Gets the offset from the system clock.
     *
     * @return	    the offset, in milliseconds, from the system time
     */
    long getTimeOffset();

    /**
     * Gets the time zone for this model.
     */
    TimeZone getTimeZone();

    /**
     * Removes a {@code PropertyChangeListener} from notification.
     */
    void removePropertyChangeListener(PropertyChangeListener listener);

    /**
     * Sets the offset from the system clock.  To ensure that this {@code
     * TimeModel} reflects the system time when it is {@link #updateTime
     * updated}, {@code timeOffset} should be zero.
     * <p/>
     * This method causes a property change notification for the {@link
     * #PROPERTY_TIME_OFFSET} property.
     *
     * @param	    timeOffset
     *		    the offset, in milliseconds, from the system time
     */
    void setTimeOffset(long timeOffset);

    /**
     * Sets the time zone for this model.
     * <p/>
     * This method causes a property change notification for the {@link
     * #PROPERTY_TIME_ZONE} property.
     */
    void setTimeZone(TimeZone timeZone);

    /**
     * Calculates this {@code TimeModel}'s time based on the {@link
     * #getTimeOffset time offset} and the system time.
     */
    void updateTime();
}
