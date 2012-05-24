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

package com.oracle.solaris.vp.util.misc.finder;

import java.util.*;
import javax.swing.*;
import com.oracle.solaris.vp.util.misc.IconUtil;

public class GnomeUtil {
    //
    // Inner classes
    //

    public static interface GnomeIconProvider {
	String getVersion();

	String getIconFileName(String name, int height);

	String getMimeIconFileName(String type, String subtype, int height);
    }

    //
    // Static data
    //

    private static List<GnomeIconProvider> providers =
	new ArrayList<GnomeIconProvider>();

    private static List<GnomeIconProvider> roProviders =
	Collections.unmodifiableList(providers);

    static {
	try {
	    // providers.add(new GnomeIconProviderV2());
	} catch (NoClassDefFoundError e) {
	    // Java Gnome version 2 not installed or not in classpath
	}
    }

    private static ObjectCache<String, Icon> cache =
	new ObjectCache<String, Icon>();

    //
    // Static methods
    //

    /**
     * Clear the cache of retrieved {@code Icon}s.
     */
    public void clearCache() {
	synchronized (cache) {
	    cache.clear();
	}
    }

    /**
     * Gets a Gnome {@code Icon} of the given name and height.
     *
     * @param	    name
     *		    the name of the icon as known to Gnome (e.g. "gtk-cancel")
     *
     * @param	    height
     *		    the preferred height of the icon
     *
     * @param	    force
     *		    whether to resize the retrieved Gnome icon if is not the
     *		    exact height
     */
    public static Icon getIcon(String name, int height, boolean force) {
	String key = height + ":" + force + ":" + name;
	Icon icon = cache.get(key);
	if (icon == null) {
	    String file = getIconFileName(name, height);
	    icon = getIconFromFileName(file, height, force);
	    cache.put(key, icon);
	}
	return icon;
    }

    public static String getIconFileName(String name, int height) {
	for (GnomeIconProvider provider : providers) {
	    String file = provider.getIconFileName(name, height);
	    if (file != null) {
		return file;
	    }
	}

	return null;
    }

    public static List<GnomeIconProvider> getIconProviders() {
	return roProviders;
    }

    /**
     * Gets a Gnome MIME {@code Icon} of the given type, subtype, and height.
     *
     * @param	    type
     *		    the type portion of the MIME type
     *
     * @param	    subtype
     *		    the subtype portion of the MIME type
     *
     * @param	    height
     *		    the preferred height of the icon
     *
     * @param	    force
     *		    whether to resize the retrieved Gnome icon if is not the
     *		    exact height
     */
    public static Icon getMimeIcon(String type, String subtype, int height,
	boolean force) {

	String key = height + ":" + force + ":" + type + "/" + subtype;
	Icon icon = cache.get(key);
	if (icon == null) {
	    String file = getMimeIconFileName(type, subtype, height);
	    icon = getIconFromFileName(file, height, force);
	    cache.put(key, icon);
	}
	return icon;
    }

    public static String getMimeIconFileName(String type, String subtype,
	int height) {

	for (GnomeIconProvider provider : providers) {
	    String file = provider.getMimeIconFileName(type, subtype, height);
	    if (file != null) {
		return file;
	    }
	}

	return null;
    }

    //
    // Private methods
    //

    private static Icon getIconFromFileName(String file, int height,
	boolean force) {

	Icon icon = null;
	if (file != null) {
	    icon = new ImageIcon(file);
	    if (force) {
		icon = IconUtil.ensureIconHeight(icon, height);
	    }
	}
	return icon;
    }
}
