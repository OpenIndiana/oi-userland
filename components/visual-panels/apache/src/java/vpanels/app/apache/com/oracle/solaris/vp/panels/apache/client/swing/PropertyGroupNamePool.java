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
import com.oracle.solaris.vp.panel.common.api.smf_old.*;
import com.oracle.solaris.vp.panel.common.smf.ServiceMXBean;

public class PropertyGroupNamePool {
    //
    // Static data
    //

    private static final int MINIMUM = 1;

    //
    // Instance data
    //

    private ServiceMXBean service;
    private String prefix;
    private List<Integer> existing = new LinkedList<Integer>();
    private List<Integer> reserved = new LinkedList<Integer>();
    private int next;

    //
    // Constructors
    //

    public PropertyGroupNamePool(ServiceMXBean service, String prefix)
	throws ScfException {

	this.service = service;
	this.prefix = prefix;

	refresh();
    }

    //
    // PropertyGroupNamePool methods
    //

    public String get() {
	String name = prefix + next;

	int index = Collections.binarySearch(reserved, next);
	assert index < 0;
	index = -1 - index;
	reserved.add(index, next);

	next = getNext(next);

	return name;
    }

    @SuppressWarnings({"unchecked"})
    public boolean put(int ord) {
	boolean found = false;
	List[] lists = {
	    reserved, existing
	};

	for (List<Integer> list : lists) {
	    int index = Collections.binarySearch(list, ord);
	    found = index >= 0;
	    if (found) {
		list.remove(index);
		if (ord < next) {
		    next = ord;
		}
		break;
	    }
	}

	return found;
    }

    public boolean put(String name) {
	try {
	    return put(toOrd(name));
	} catch (NumberFormatException e) {
	    return false;
	}
    }

    public void refresh() throws ScfException {
	existing.clear();
	for (PropertyGroup pg : service.getPropertyGroups()) {
	    String name = pg.getName();
	    try {
		int ord = toOrd(name);
		int index = Collections.binarySearch(existing, ord);
		if (index < 0) {
		    index = -1 - index;
		    existing.add(index, ord);
		}
		index = Collections.binarySearch(reserved, ord);
		if (index >= 0) {
		    reserved.remove(index);
		}
	    } catch (NumberFormatException skip) {
	    }
	}
	next = getNext(MINIMUM);
    }

    //
    // Private methods
    //

    private int getNext(int from) {
	while (Collections.binarySearch(existing, from) >= 0 ||
	    Collections.binarySearch(reserved, from) >= 0) {
	    from++;
	}
	return from;
    }

    private int toOrd(String name) {
	if (name.startsWith(prefix)) {
	    return Integer.parseInt(name.substring(prefix.length()));
	}
	throw new NumberFormatException();
    }
}
