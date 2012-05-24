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

package com.oracle.solaris.vp.panel.common.model;

import java.io.Serializable;
import java.util.*;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.misc.converter.Converter;
import com.oracle.solaris.vp.util.misc.event.*;

public interface ManagedObject<C extends ManagedObject>
    extends IntervalEventSource, PropertyChangeEventSource, HasId, HasName,
    Serializable {

    //
    // Inner classes
    //

    class Util {
	//
	// Static data
	//

	private static final Converter<ManagedObject, ManagedObjectStatus>
	    toPanelStatus = new Converter<ManagedObject, ManagedObjectStatus>()
	    {
		@Override
		public ManagedObjectStatus convert(ManagedObject o) {
		    return o.getStatus();
		}
	    };

	//
	// Static methods
	//

	public static ManagedObjectStatus getMostSevereStatus(
	    Collection<? extends ManagedObject> objs) {

	    return ManagedObjectStatus.getMostSevere(CollectionUtil.convert(
		objs, toPanelStatus));
	}
    }

    //
    // Static data
    //

    /**
     * The name of the property that is {@link #addPropertyChangeListener
     * updated} when the enabled status of this {@code ManagedObject} changes.
     */
    String PROPERTY_ENABLED = "enabled";

    /**
     * The name of the property that is {@link #addPropertyChangeListener
     * updated} when the value of {@link #getName} changes.
     */
    String PROPERTY_NAME = "name";

    /**
     * The name of the property that is {@link #addPropertyChangeListener
     * updated} when the value of {@link #getStatus} changes.
     */
    String PROPERTY_STATUS = "status";

    /**
     * The name of the property that is {@link #addPropertyChangeListener
     * updated} when the value of {@link #getStatusText} changes.
     */
    String PROPERTY_STATUS_TEXT = "statusText";

    //
    // HasId methods
    //

    /**
     * Gets a unique identifier for this {@code ManagedObject}.  This identifier
     * should uniquely distinguish this {@code ManagedObject} from its peers,
     * and should be consistent across all locales and invocations of the JVM.
     *
     * @return	    a non-{@code null} identifier
     */
    @Override
    String getId();

    //
    // ManagedObject methods
    //

    /**
     * Disposes of any resources in use by this {@code ManagedObject}.
     */
    void dispose();

    /**
     * Gets the description of this {@code ManagedObject}.
     *
     * @return	    the localized description, or {@code null} if no description
     *		    is available for this {@code ManagedObject}.
     */
    String getDescription();

    /**
     * Gets the "child" {@code ManagedObject}s contained by this {@code
     * ManagedObject}.
     */
    List<C> getChildren();

    /**
     * Gets the object which consumers of {@code getChildren()} can use to
     * synchronize access to the list of children.
     *
     * @return	    the object that can be synchronized against to prevent
     *		    changes to the children list
     */
    Object getChildrenLock();

    /**
     * Gets the status of this {@code ManagedObject}.
     *
     * @return	    a non-{@code null} status
     */
    ManagedObjectStatus getStatus();

    /**
     * Gets status text of this {@code ManagedObject}.
     *
     * @return	    the localized status text, or {@code null} if no status text
     *		    is appropriate for this {@code ManagedObject}.
     */
    String getStatusText();
}
