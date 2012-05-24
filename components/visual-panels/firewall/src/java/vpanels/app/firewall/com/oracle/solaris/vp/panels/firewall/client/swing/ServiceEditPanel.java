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

package com.oracle.solaris.vp.panels.firewall.client.swing;

import java.awt.EventQueue;
import com.oracle.solaris.vp.util.misc.finder.Finder;

@SuppressWarnings({"serial"})
public class ServiceEditPanel extends CommonEditPanel {
    //
    // Static data
    //

    private static final String SVC_POLICY_DESC =
        Finder.getString("description.policy.service.default");

    public ServiceEditPanel() {
	super(true, SVC_POLICY_DESC);
    }

    //
    // ServiceEditPanel
    //

    public void init(ServiceManagedObject service) {
	// Sanity check -- the UI should be updated only on the event thread
	assert EventQueue.isDispatchThread();

	getAccessProperty().update(null, false);

	getHelpField().setText(Finder.getString("description.policy.service",
	    service.getName()));

	super.init(service.getAccessPolicy());

	AccessPolicy parentPolicy =
	    service.getPanelDescriptor().getAccessPolicy();
	getAccessProperty().getPanel().getDefaultInfoLabel().setToolTipText(
	    AccessPolicyUtil.toString(parentPolicy, true));
    }
}
