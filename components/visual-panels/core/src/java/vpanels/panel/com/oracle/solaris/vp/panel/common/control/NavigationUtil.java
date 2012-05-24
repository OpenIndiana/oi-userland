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
 * Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panel.common.control;

import com.oracle.solaris.vp.panel.common.model.PanelDescriptor;

public class NavigationUtil {
    /**
     * Gets the {@link PanelDescriptor}, if any, started by the given {@link
     * Navigator}.
     */
    public static PanelDescriptor getRunningPanel(Navigator navigator) {
	for (Control control : navigator.getPath()) {
	    if (control instanceof DefaultControl) {
                PanelDescriptor descriptor =
		    ((DefaultControl)control).getPanelDescriptor();

		if (descriptor != null) {
		    return descriptor;
		}
	    }
	}
	return null;
    }

    /**
     * Indicates whether the given {@link Navigator} has started a panel.
     */
    public static boolean isPanelStarted(Navigator navigator) {
	return getRunningPanel(navigator) != null;
    }
}
