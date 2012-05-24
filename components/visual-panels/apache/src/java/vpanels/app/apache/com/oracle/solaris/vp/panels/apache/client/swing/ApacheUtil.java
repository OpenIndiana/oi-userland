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

package com.oracle.solaris.vp.panels.apache.client.swing;

import java.util.*;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.util.misc.property.MutableProperty;

@SuppressWarnings({"serial"})
public class ApacheUtil {
    //
    // Static methods
    //

    public static String getNextAvailablePropertyName(SmfPropertyGroupInfo info,
	String prefix) throws ScfException {

	ServiceMXBean service = info.getService();
	String group = info.getPropertyGroupName();

	List<String> names = new ArrayList<String>(
	    service.getPropertyNames(group));

	Collections.sort(names);

	String name = null;
	int i = 1;

	// Property names take the form <prefix><n>, where n > 0
	do {
	    name = prefix + i++;
	} while (Collections.binarySearch(names, name) >= 0);

	return name;
    }

    public static void saveToRepo(AggregatedRefreshService service,
	ScfRunnable runnable) throws ScfException {

	synchronized (service) {
	    boolean needLock = !service.isPaused();
	    if (needLock) {
		service.pause();
	    }

	    boolean success = false;
	    try {
		// Throws ScfException
		runnable.run();
		success = true;
	    } finally {
		if (needLock) {
		    if (success) {
			// Throws ScfException
			service.unpause();
		    } else {
			// Unlock, refresh if needed, ignore any exceptions
			// since we are already in the midst of throwing one
			try {
			    service.unpause();
			} catch (Throwable ignore) {
			}
		    }
		}
	    }
	}
    }

    public static <T> void update(MutableProperty<T> src,
	MutableProperty<T> dest) {

	boolean changed = dest.isChanged();
	dest.setSavedValue(src.getSavedValue());

	if (!changed) {
	    dest.setValue(src.getValue());
	}
    }

    public static <T> void update(BasicSmfMutableProperty<T> src,
	MutableProperty<T> dest) {

	boolean changed = dest.isChanged();
	dest.setSavedValue(src.getFirstSavedValue());

	if (!changed) {
	    dest.setValue(src.getFirstValue());
	}
    }
}
