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

package com.oracle.solaris.vp.util.misc.finder;

import java.net.URL;
import javax.swing.ImageIcon;

public class IconFinder extends ResourceFinder {
    //
    // Instance data
    //

    private ObjectCache<String, ImageIcon> cache =
	new ObjectCache<String, ImageIcon>();

    //
    // IconFinder methods
    //

    /**
     * Clear the cache of retrieved {@code ImageIcon}s.
     */
    public void clearCache() {
	synchronized (cache) {
	    cache.clear();
	}
    }

    /**
     * Return an {@code ImageIcon} for the given resource name.  All packages
     * in the hierarchy above the given package are searched, using the given
     * {@code ClassLoader}.  See the class notes for details on the search
     * algorithm.
     *
     * @param	    loader
     *		    the {@code ClassLoader} to load the resource, or {@code
     *		    null} to use the system {@code ClassLoader}
     *
     * @param	    pkg
     *		    a point in the package hierarchy to search for the resource
     *
     * @param	    name
     *		    the name of the resource
     *
     * @return	    a {@code URL} object, or {@code null} if no resource with
     *		    this name is found
     */
    public ImageIcon getIcon(ClassLoader loader, String pkg, String name) {
	URL url = getResource(loader, pkg, name);
	return url == null ? null : getIcon(url);
    }

    /**
     * Return an {@code ImageIcon} for the given resource name.  All packages in
     * the hierarchy above the given package are searched, using the caller's
     * {@code ClassLoader}.  See the class notes for details on the search
     * algorithm.
     *
     * @param	    pkg
     *		    a point in the package hierarchy to search for the resource
     *
     * @param	    name
     *		    the name of the resource
     *
     * @return	    a {@code URL} object, or {@code null} if no resource with
     *		    this name is found
     */
    public ImageIcon getIcon(String pkg, String name) {
	URL url = getResource(pkg, name);
	return url == null ? null : getIcon(url);
    }

    /**
     * Return an {@code ImageIcon} for the given resource name.  All packages in
     * the hierarchy above the calling class are searched, using the caller's
     * {@code ClassLoader}.  See the class notes for details on the search
     * algorithm.
     *
     * @param	    name
     *		    the name of the resource
     *
     * @return	    a {@code URL} object, or {@code null} if no resource with
     *		    this name is found
     */
    public ImageIcon getIcon(String name) {
	URL url = getResource(name);
	return url == null ? null : getIcon(url);
    }

    //
    // Private methods
    //

    /**
     * Retrieve from cache, or create, an {@code ImageIcon} for the given {@code
     * URL}.
     */
    private ImageIcon getIcon(URL url) {
	String key = url.toString();
	ImageIcon icon = null;

	synchronized (cache) {
	    if (cache.containsKey(key)) {
		// May be null
		icon = cache.get(key);
	    } else {
		icon = new ImageIcon(url);
		cache.put(key, icon);
	    }
	}

	return icon;
    }
}
