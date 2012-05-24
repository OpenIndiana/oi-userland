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

package com.oracle.solaris.vp.panels.time.client.swing;

import java.util.*;
import com.oracle.solaris.rad.ObjectException;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.api.smf_old.SmfState;
import com.oracle.solaris.vp.panel.common.model.AbstractModel;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.panels.time.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class NTPModel extends AbstractModel<TimePanelDescriptor> {

    private boolean enabled_ = false;
    private List<ServerInfo> servers_ = null;

    private SmfState state_;
    private SmfState nextState_;

    public NTPModel(TimePanelDescriptor source) {
	super(source);
    }

    //
    // Model methods
    //

    public boolean isInitialized() {
	return (servers_ != null && state_ != null && nextState_ != null);
    }

    public void validate() throws ActionFailedException {
	assert (isInitialized());
    }

    public void load() {
	// XXX generic NTPModel shouldn't assume a ServicePanelDescriptor
	enabled_ = getSource().isEnabled();
	try {
	    servers_ = getSource().getTimeMXBean().getntpServers();
	} catch (ObjectException e) {
	    servers_ = Collections.emptyList();
	}

	// Read only state
	ServiceMXBean service = getSource().getService();
	try {
	    state_ = service.getState();
	    nextState_ = service.getNextState();
	} catch (ScfException ignore) {
	}
    }

    public void save() throws ActionFailedException,
	ActionUnauthorizedException {

	validate();

	TimePanelDescriptor descriptor = getSource();
	TimeMXBean bean = descriptor.getTimeMXBean();

	try {
	    bean.setntpServers(servers_);

	} catch (SecurityException e) {
	    throw new ActionUnauthorizedException(e);

	} catch (ObjectException e) {
	    throw new ActionFailedException(
		Finder.getString("ntp.error.syserror"), e);
	}

	try {
	    SmfEnabledProperty smfEnabledProp = descriptor.getEnabledProperty();

	    smfEnabledProp.setValue(enabled_);
	    smfEnabledProp.saveToRepo();

	} catch (SecurityException e) {
	    throw new ActionUnauthorizedException(e);

	} catch (ScfException e) {
	    SmfUtil.throwActionException(e);
	    throw new ActionFailedException(Finder.getString(
		"ntp.error.service." + (enabled_ ? "start" : "stop")), e);
	}
    }

    //
    // NTPModel methods
    //

    public boolean isEnabled() {
	return enabled_;
    }

    public void setEnabled(boolean enabled) {
	enabled_ = enabled;
    }

    public ServerInfo[] getServers() {
	return servers_.toArray(new ServerInfo[0]);
    }

    public void setServers(ServerInfo[] servers) {
	servers_ = Arrays.asList(servers);
    }

    public SmfState getState() {
	return (state_);
    }

    public SmfState getNextState() {
	return (nextState_);
    }
}
