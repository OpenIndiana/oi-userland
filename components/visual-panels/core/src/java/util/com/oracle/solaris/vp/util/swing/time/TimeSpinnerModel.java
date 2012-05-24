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
import java.util.Calendar;
import javax.swing.AbstractSpinnerModel;

@SuppressWarnings({"serial"})
public class TimeSpinnerModel extends AbstractSpinnerModel {
    //
    // Instance data
    //

    private TimeModel model;
    private TimeSelectionModel selModel;

    private PropertyChangeListener timeListener =
	new PropertyChangeListener() {
	    @Override
	    public void propertyChange(PropertyChangeEvent event) {
		fireStateChanged();
	    }
	};

    //
    // Constructors
    //

    /**
     * Constructs a {@code TimeSpinnerModel} for the given model.
     */
    public TimeSpinnerModel(TimeModel model) {
	setTimeSelectionModel(new SimpleTimeSelectionModel());
	setTimeModel(model);
    }

    /**
     * Constructs a {@code TimeSpinnerModel} with a zero {@link
     * TimeModel#getTimeOffset offset} from the system clock.
     */
    public TimeSpinnerModel() {
	this(new SimpleTimeModel());
    }

    //
    // SpinnerModel methods
    //

    @Override
    public void setValue(Object value) {
	model.setTimeOffset((Long)value);
    }

    @Override
    public Object getNextValue() {
        return getPreviousOrNextValue(true);
    }

    @Override
    public Object getPreviousValue() {
        return getPreviousOrNextValue(false);
    }

    @Override
    public Object getValue() {
        return model.getTimeOffset();
    }

    //
    // TimeSpinnerModel methods
    //

    public TimeModel getTimeModel() {
	return model;
    }

    public TimeSelectionModel getTimeSelectionModel() {
	return selModel;
    }

    public void setTimeModel(TimeModel model) {
	if (this.model != model) {
	    if (this.model != null) {
		this.model.removePropertyChangeListener(timeListener);
	    }

	    model.addPropertyChangeListener(TimeModel.PROPERTY_TIME,
		timeListener);

	    this.model = model;
	    fireStateChanged();
	}
    }

    public void setTimeSelectionModel(TimeSelectionModel selModel) {
	this.selModel = selModel;
    }

    //
    // Private methods
    //

    private long getPreviousOrNextValue(boolean next) {
	long delta = 0;
	int field = selModel.getSelectedField();

	if (field >= 0 && field < Calendar.FIELD_COUNT) {
	    if (field == Calendar.AM_PM) {
		// AM_PM is a special field -- toggle regardless of direction
		next = model.getCalendar().get(field) == Calendar.AM;
	    }

	    Calendar cal = model.getCalendar();
	    long before = cal.getTimeInMillis();
	    cal.add(field, next ? 1 : -1);
	    long after = cal.getTimeInMillis();
	    delta = after - before;
	}

        return model.getTimeOffset() + delta;
    }
}
