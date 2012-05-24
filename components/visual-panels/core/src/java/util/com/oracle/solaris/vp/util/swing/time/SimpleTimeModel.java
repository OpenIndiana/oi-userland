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

import java.beans.*;
import java.util.*;
import com.oracle.solaris.vp.util.misc.event.PropertyChangeListeners;

@SuppressWarnings({"serial"})
public class SimpleTimeModel implements TimeModel {
    //
    // Instance data
    //

    private Calendar cal = Calendar.getInstance();
    private long timeOffset;

    private PropertyChangeListeners listeners =
	new PropertyChangeListeners();

    //
    // Constructors
    //

    /**
     * Constructs a {@code SimpleTimeModel} with the specified {@link
     * #setTimeOffset offset}.
     */
    public SimpleTimeModel(long timeOffset) {
	setTimeOffset(timeOffset);
    }

    /**
     * Constructs a {@code SimpleTimeModel} with a zero {@link #setTimeOffset
     * offset} from the system clock.
     */
    public SimpleTimeModel() {
	this(0);
    }

    //
    // TimeModel methods
    //

    @Override
    public void addPropertyChangeListener(PropertyChangeListener listener) {
	listeners.add(listener);
    }

    @Override
    public void addPropertyChangeListener(String propertyName,
	PropertyChangeListener listener) {

	listeners.add(propertyName, listener);
    }

    @Override
    public Calendar getCalendar() {
	return (Calendar)cal.clone();
    }

    @Override
    public long getTimeOffset() {
	return timeOffset;
    }

    @Override
    public TimeZone getTimeZone() {
	return cal.getTimeZone();
    }

    @Override
    public void removePropertyChangeListener(PropertyChangeListener listener) {
	listeners.remove(listener);
    }

    @Override
    public void setTimeOffset(long timeOffset) {
	if (this.timeOffset != timeOffset) {
	    long oldValue = this.timeOffset;
	    this.timeOffset = timeOffset;
	    updateTime();
	    firePropertyChange(PROPERTY_TIME_OFFSET, (Long)oldValue,
		(Long)timeOffset);
	}
    }

    @Override
    public void setTimeZone(TimeZone timeZone) {
	TimeZone oldValue = cal.getTimeZone();
	if (!oldValue.equals(timeZone)) {
	    cal.setTimeZone(timeZone);
	    updateTime();
	    firePropertyChange(PROPERTY_TIME_ZONE, oldValue, timeZone);
	}
    }

    @Override
    public void updateTime() {
	long oldValue = cal.getTimeInMillis();
	long newValue = System.currentTimeMillis() + timeOffset;
	cal.setTimeInMillis(newValue);
	firePropertyChange(PROPERTY_TIME, (Long)oldValue, (Long)newValue);
    }

    //
    // SimpleTimeModel methods
    //

    public void firePropertyChange(String propertyName, Object oldValue,
	Object newValue) {

	PropertyChangeEvent event = new PropertyChangeEvent(
	    this, propertyName, oldValue, newValue);
	listeners.propertyChange(event);
    }

    public Calendar getModelCalendar() {
	return cal;
    }
}
