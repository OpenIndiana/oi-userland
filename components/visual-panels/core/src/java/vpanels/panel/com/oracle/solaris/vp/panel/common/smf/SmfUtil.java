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

import javax.management.*;
import com.oracle.solaris.rad.jmx.RadNotification;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.api.smf_old.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class SmfUtil {
    //
    // Static data
    //

    public static final NotificationFilter NOTIFY_FILTER_STATE_CHANGE =
	new NotificationFilter() {
	    @Override
	    public boolean isNotificationEnabled(Notification n) {
		return n instanceof RadNotification &&
		    n.getType().equals("statechange") &&
		    ((RadNotification)n).getPayload(StateChange.class) != null;
	    }
	};

    //
    // Static methods
    //

    public static void throwActionException(ScfException e)
	throws ActionFailedException, ActionUnauthorizedException {

	if (e.getError() == SmfErrorCode.PERMISSION_DENIED) {
	    throw new ActionUnauthorizedException(e);
	}

	throw new ActionFailedException(
	    Finder.getString("error.repository.write"), e);
    }
}
