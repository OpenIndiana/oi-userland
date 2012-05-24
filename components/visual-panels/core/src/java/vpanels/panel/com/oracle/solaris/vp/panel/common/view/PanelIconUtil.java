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

package com.oracle.solaris.vp.panel.common.view;

import java.util.*;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.model.ManagedObjectStatus;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.misc.finder.*;
import com.oracle.solaris.vp.util.swing.*;

public class PanelIconUtil {
    //
    // Static data
    //

    private static final Map<String, Icon> badgeCache =
	new HashMap<String, Icon>();

    private static final Map<String, Icon> mimeCache =
	new HashMap<String, Icon>();

    private static final List<ImageIcon> defaultIcons = Finder.getIcons(
	"images/general/default-16.png",
	"images/general/default-24.png",
	"images/general/default-32.png",
	"images/general/default-48.png",
	"images/general/default-96.png");

    private static final Map<ManagedObjectStatus, Icon> statusIcons =
	new HashMap<ManagedObjectStatus, Icon>();

    static {
	statusIcons.put(ManagedObjectStatus.WARNING,
	    Finder.getIcon("images/badge/dialog-warning.png"));

	statusIcons.put(ManagedObjectStatus.ERROR,
	    Finder.getIcon("images/badge/dialog-error.png"));
    }

    private static final List<ImageIcon> genericMimeIcons = Finder.getIcons(
	"images/mime/16/generic-mimetype.png",
	"images/mime/24/generic-mimetype.png",
	"images/mime/32/generic-mimetype.png",
	"images/mime/36/generic-mimetype.png",
	"images/mime/48/generic-mimetype.png",
	"images/mime/72/generic-mimetype.png",
	"images/mime/96/generic-mimetype.png",
	"images/mime/192/generic-mimetype.png");

    //
    // Static methods
    //

    /**
     * Clear the cache of badged {@code Icon}s.
     */
    public static void clearBadgeCache() {
	synchronized (badgeCache) {
	    badgeCache.clear();
	}
    }

    /**
     * Clear the cache of mimed {@code Icon}s.
     */
    public static void clearMimeCache() {
	synchronized (mimeCache) {
	    mimeCache.clear();
	}
    }

    public static Icon getBadgedIcon(final Icon icon,
	ManagedObjectStatus status) {

	if (icon == null) {
	    return null;
	}

	synchronized (badgeCache) {
	    String key = Integer.toString(icon.hashCode()) + status;
	    Icon cIcon = badgeCache.get(key);
	    if (cIcon != null) {
		return cIcon;
	    }

	    final Icon sIcon = getStatusIcon(status);
	    if (sIcon == null) {
		return icon;
	    }

	    cIcon = IconUtil.getBadgedIcon(icon, sIcon);
	    badgeCache.put(key, cIcon);

	    return cIcon;
	}
    }

    public static Icon getDefaultIcon(int height) {
	Icon icon = IconUtil.getClosestIcon(defaultIcons, height);
	return IconUtil.ensureIconHeight(icon, height);
    }

    public static List<ImageIcon> getGenericMimeIcons() {
	return Collections.unmodifiableList(genericMimeIcons);
    }

    public static Icon getIcon(Object o, int height,
	boolean useDefaultIfNotFound) {

	Icon icon = null;

	if (o != null && o instanceof HasIcon) {
	    icon = ((HasIcon)o).getIcon(height);
	}

	if (icon == null && o != null && o instanceof HasIcons) {
	    icon = IconUtil.getClosestIcon(((HasIcons)o).getIcons(), height);
	}

	if (icon == null && useDefaultIfNotFound) {
	    icon = getDefaultIcon(height);
	}

	return IconUtil.ensureIconHeight(icon, height);
    }

    public static Icon getClosestMimeIcon(
	String type, String subtype, int height) {

	Icon icon = null;
	String key = height + '/' + type + '/'+ subtype;

	synchronized (mimeCache) {
	    if (mimeCache.containsKey(key)) {
		// May be null
		icon = mimeCache.get(key);
	    } else {
		icon = GnomeUtil.getMimeIcon(type, subtype, height, true);
		mimeCache.put(key, icon);
	    }
	}

	if (icon == null) {
	    icon = IconUtil.getClosestIcon(genericMimeIcons, height);
	}

	return icon;
    }

    public static Icon getStatusIcon(ManagedObjectStatus status) {
	return statusIcons.get(status);
    }
}
