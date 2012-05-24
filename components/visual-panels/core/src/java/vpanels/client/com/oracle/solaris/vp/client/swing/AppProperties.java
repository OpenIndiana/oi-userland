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

package com.oracle.solaris.vp.client.swing;

import java.awt.Color;
import java.io.IOException;
import java.util.*;
import javax.swing.UIManager;
import com.oracle.solaris.vp.util.misc.TypedPropertiesWrapper;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;

@SuppressWarnings({"serial"})
public class AppProperties extends Properties {
    //
    // Static data
    //

    public static final String RESOURCE_NAME = "runtime.properties";

    public static final AppProperties singleton = new AppProperties();

    //
    // Instance data
    //

    private TypedPropertiesWrapper wrapper;

    //
    // Constructors
    //

    private AppProperties() {
	wrapper = new TypedPropertiesWrapper(this);

	try {
	    load(Finder.getResource(RESOURCE_NAME).openStream());

	    // Load common defaults if available
	    try {
		Color c = wrapper.getColor(HyperlinkLabel.KEY_UNVISITED);
		UIManager.put(HyperlinkLabel.KEY_UNVISITED, c);
	    } catch (NoSuchElementException ignore) {
	    }

	    try {
		Color c = wrapper.getColor(HyperlinkLabel.KEY_VISITED);
		UIManager.put(HyperlinkLabel.KEY_VISITED, c);
	    } catch (NoSuchElementException ignore) {
	    }

	    try {
		String value = getProperty(HyperlinkLabel.KEY_UNDERLINE_POLICY);
		HyperlinkLabel.UnderlinePolicy policy =
		    HyperlinkLabel.UnderlinePolicy.valueOf(value);
		UIManager.put(HyperlinkLabel.KEY_UNDERLINE_POLICY, policy);
	    } catch (Throwable ignore) {
	    }
	} catch (IOException e) {
	    // Unlikely -- the resource should always exist and be accessible
	}

	GUIUtil.setUIPreferences(this);
    }

    //
    // AppProperties methods
    //

    public TypedPropertiesWrapper getWrapper() {
	return wrapper;
    }
}
