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

package com.oracle.solaris.vp.panel.common.api.panel;

import javax.management.ObjectName;
import com.oracle.solaris.adr.Stability;
import com.oracle.solaris.vp.panel.common.*;

public class PanelMXBeanTracker extends MXBeanTracker<PanelMXBean> {
    //
    // Static data
    //

    private static final String DOMAIN = MBeanUtil.VP_DOMAIN + ".panel";
    public static final ObjectName OBJECT_NAME =
	MBeanUtil.makeObjectName(DOMAIN, "Panel");

    //
    // Constructors
    //

    public PanelMXBeanTracker() {
	super(OBJECT_NAME, PanelMXBean.class, Stability.PRIVATE);
    }

    public PanelMXBeanTracker(ClientContext context)
	throws TrackerException {

	this();
	setClientContext(context);
    }
}
