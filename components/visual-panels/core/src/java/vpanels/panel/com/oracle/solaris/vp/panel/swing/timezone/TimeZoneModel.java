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

package com.oracle.solaris.vp.panel.swing.timezone;

import com.oracle.solaris.rad.ObjectException;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.api.time.HasTimeMXBean;
import com.oracle.solaris.vp.panel.common.model.AbstractModel;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class TimeZoneModel extends AbstractModel<HasTimeMXBean> {
    //
    // Instance data
    //

    private static final String DEFAULT_TZ = "US/Pacific";
    private String timeZone;

    //
    // Constructors
    //

    public TimeZoneModel(HasTimeMXBean descriptor) {
	super(descriptor);
    }

    public TimeZoneModel(TimeZoneModel model) {
	super(model.getSource());
	timeZone = model.timeZone;
    }

    //
    // Model methods
    //

    public boolean isInitialized() {
	return (timeZone != null);
    }

    @Override
    public void init() {
	setTimeZone(DEFAULT_TZ);
    }

    public void load() {
	try {
	    setTimeZone(getSource().getTimeMXBean().getdefaultTimeZone());
	} catch (ObjectException e) {
	    setTimeZone("UTC");
	}
    }

    @Override
    public void save() throws ActionFailedException,
	ActionUnauthorizedException {

	validate();

	try {
	    getSource().getTimeMXBean().setdefaultTimeZone(timeZone);

	} catch (SecurityException e) {
	    throw new ActionUnauthorizedException(e);

	} catch (ObjectException e) {
	    throw new ActionFailedException(Finder.getString(
		"timezone.error.syserror"), e);
	}
    }

    @Override
    public void validate() throws ActionFailedException {
	if (timeZone == null) {
	    throw new ActionFailedException(
		Finder.getString("timezone.error.unset"));
	}
    }

    //
    // TimeZoneModel methods
    //

    public String getTimeZone() {
	return timeZone;
    }

    public void setTimeZone(String timeZone) {
	this.timeZone = timeZone;
    }
}
