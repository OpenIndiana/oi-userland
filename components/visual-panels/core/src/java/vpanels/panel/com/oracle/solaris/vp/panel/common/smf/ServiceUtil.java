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

package com.oracle.solaris.vp.panel.common.smf;

import java.text.DateFormat;
import java.util.*;
import javax.management.*;
import com.oracle.solaris.scf.common.FMRI;
import com.oracle.solaris.vp.panel.common.api.panel.MBeanUtil;
import com.oracle.solaris.vp.panel.common.api.smf_old.SmfState;
import com.oracle.solaris.vp.panel.common.model.ManagedObjectStatus;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class ServiceUtil {
    //
    // Static data
    //

    public static final String SERVICE_DOMAIN =
	MBeanUtil.VP_DOMAIN + ".smf_old";

    //
    // Static methods
    //

    public static ObjectName getServiceObjectName(
	String service, String instance) throws MalformedObjectNameException {

	/*
	 * We don't use ObjectName.quote() because we can be called to
	 * construct a pattern, and no valid FMRI characters require quoting
	 * in a quoted ObjectName values.
	 */
	String namestr = String.format("%s:type=service,service=\"%s\"",
	    SERVICE_DOMAIN, service);
	if (instance != null)
	    namestr = String.format("%s,instance=\"%s\"", namestr, instance);

	return (new ObjectName(namestr));
    }

    public static ObjectName toObjectName(String service, String instance)
    {
	try {
		return (getServiceObjectName(service, instance));
	} catch (MalformedObjectNameException e) {
		throw (new IllegalArgumentException(e));
	}
    }

    public static ObjectName toObjectName(FMRI fmri)
    {
	switch (fmri.getSvcType()) {
	case INSTANCE:
	    return (toObjectName(fmri.getService(), fmri.getInstance()));
	case SERVICE:
	    return (toObjectName(fmri.getService(), null));
	default:
	    return (null);
	}
    }

    public static String toFMRI(ObjectName on)
    {
	String service = ObjectName.unquote(on.getKeyProperty("service"));
	String instance = ObjectName.unquote(on.getKeyProperty("instance"));

	if (!on.getDomain().equals(SERVICE_DOMAIN) || service == null)
	    throw (new IllegalArgumentException("Not an SMF ObjectName"));

	service = service.replace('+', ',');
	if (instance != null)
		instance = instance.replace('+', ',');

	return ("svc:/" + (instance == null ?
	    service : service + ":" + instance));
    }

    public static String toService(ObjectName on)
    {
	try {
	    String service = on.getKeyProperty("service");
	    if (on.getDomain().equals(SERVICE_DOMAIN) && service != null)
		return ObjectName.unquote(service);
	} catch (IllegalArgumentException e) {
	}
	throw new IllegalArgumentException("Not an SMF ObjectName");
    }

    public static ManagedObjectStatus getPanelStatus(SmfState state) {
	ManagedObjectStatus status = ManagedObjectStatus.ERROR;

	if (state != null) {
	    switch (state) {
		case ONLINE:
		case OFFLINE:
		case DISABLED:
		    status = ManagedObjectStatus.HEALTHY;
		    break;

		case UNINIT:
		case DEGRADED:
		    status = ManagedObjectStatus.WARNING;
	    }
	}

	return status;
    }

    public static String getStateString(SmfState state) {
	if (state == null) {
	    return null;
	}

	String lower = state.toString().toLowerCase();
	String key = "service.state." + lower;
	String text = Finder.getString(key);
	if (text == null) {
	    text = lower;
	}

	return text;
    }

    public static String getStateSynopsis(SmfState state, SmfState nextState) {
	String synopsis;

	if (state == null) {
	    synopsis = Finder.getString("service.state.synopsis.unknown");

	} else if (nextState == null || nextState == SmfState.NONE) {
	    String key =
		"service.state.synopsis." + state.toString().toLowerCase();

	    synopsis = Finder.getString(key);
	    if (synopsis == null) {
		key = "service.state.synopsis.default";
		synopsis = Finder.getString(key, state);
	    }
	} else {
	    String stateString = getStateString(state);
	    String nextStateString = getStateString(nextState);

	    synopsis = Finder.getString("service.state.synopsis.transitioning",
		stateString, nextStateString);
	}

	return synopsis;
    }

    public static String getStateDetails(
	SmfState state, SmfState nextState, String auxState, Date changed) {

	String details = null;

	if (state == null) {
	    details = Finder.getString("service.state.details.unknown");
	} else {
	    Calendar now = Calendar.getInstance();
	    Calendar then = Calendar.getInstance();
	    then.setTime(changed);

	    DateFormat formatter;

	    // Do these times refer to the same day?
	    if (now.get(Calendar.YEAR) == then.get(Calendar.YEAR) &&
		now.get(Calendar.DAY_OF_YEAR) ==
		then.get(Calendar.DAY_OF_YEAR)) {
		formatter = DateFormat.getTimeInstance(DateFormat.SHORT);
	    } else {
		formatter = DateFormat.getDateInstance(DateFormat.FULL);
	    }

	    String date = formatter.format(changed);

	    if (nextState == null || nextState == SmfState.NONE) {
		String key =
		    "service.state.details." + state.toString().toLowerCase();

		if (state == SmfState.MAINT) {
		    if (auxState != null) {
			key += "." + auxState.toLowerCase();
			details = Finder.getString(key, date);
		    }
		    if (details == null) {
			details = Finder.getString(
			    "service.state.details.maint.unknown", date);
		    }
		} else {
		    details = Finder.getString(key, date);
		    if (details == null) {
			key = "service.state.details.default";
			details = Finder.getString(key, state, date);
		    }
		}
	    } else {
		String stateString = getStateString(state);
		String nextStateString = getStateString(nextState);

		details = Finder.getString(
		    "service.state.details.transitioning",
		    stateString, nextStateString, date);
	    }
	}

	return details;
    }

    public static String getRecommendation(SmfState state) {
	String recommendation = null;

	if (state != null) {
	    String key = "service.state.recommendation." +
		state.toString().toLowerCase();

	    recommendation = Finder.getString(key);
	}

	return recommendation;
    }
}
