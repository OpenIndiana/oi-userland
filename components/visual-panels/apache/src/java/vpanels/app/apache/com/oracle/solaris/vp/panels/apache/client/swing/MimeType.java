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

package com.oracle.solaris.vp.panels.apache.client.swing;

import javax.swing.Icon;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.panel.common.view.PanelIconUtil;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.HasIcon;

@SuppressWarnings({"serial"})
public class MimeType extends AbstractManagedObject<ManagedObject>
    implements HasIcon, Cloneable, SmfPropertyInfo {

    //
    // Static data
    //

    public static final String PROPERTY_TYPE = "type";
    public static final String PROPERTY_SUBTYPE = "subtype";
    public static final String PROPERTY_EXTENSIONS = "extensions";

    public static final String SMF_PROPERTY_PREFIX = "mime-";
    public static final String SEPARATOR = "/";

    // See RFC 1341
    private static final String TSPECIALS = "()<>@,;:\\\"/[]?=";

    //
    // Instance data
    //

    private MimeTypes parent;
    private String propertyName;

    private MutableProperty<String> typeProperty =
	new BasicMutableProperty<String>(PROPERTY_TYPE);

    private MutableProperty<String> subtypeProperty =
	new BasicMutableProperty<String>(PROPERTY_SUBTYPE);

    private MutableProperty<String[]> extensionsProperty =
	new StringArrayProperty(PROPERTY_EXTENSIONS);

    // This is the property that does the actual work of persisting this
    // MimeType's data to the SMF repository
    private BasicSmfMutableProperty<String> smfProperty =
	new StringSmfProperty(null, this);

    //
    // Constructors
    //

    public MimeType(MimeTypes parent) {
	this.parent = parent;

	typeProperty.setValue("");
	addProperties(typeProperty);

	subtypeProperty.setValue("");
	addProperties(subtypeProperty);

	extensionsProperty.setValue(new String[0]);
	addProperties(extensionsProperty);

	// Synchronize the properties holding this MimeType's data with the
	// property responsible for persisting it to the SMF repository
	new MimeTypePropertySynchronizer(smfProperty, this, false);
    }

    public MimeType(MimeTypes parent, String propertyName) throws ScfException {
	this(parent);
	this.propertyName = propertyName;
	refresh(true);
    }

    //
    // HasService methods
    //

    @Override
    public AggregatedRefreshService getService() {
	return parent.getApacheInfo().getService();
    }

    //
    // SmfPropertyGroupInfo methods
    //

    @Override
    public String getPropertyGroupName() throws ScfException {
	return parent.getApacheInfo().getPropertyGroupName();
    }

    //
    // SmfPropertyInfo methods
    //

    @Override
    public String getPropertyName() throws ScfException {
	if (propertyName == null) {
	    propertyName = ApacheUtil.getNextAvailablePropertyName(
		parent.getApacheInfo(), SMF_PROPERTY_PREFIX);
	}
	return propertyName;
    }

    //
    // Object methods
    //

    @Override
    public MimeType clone() {
	MimeType clone = new MimeType(getParent());
	for (MutableProperty<?> property : getProperties()) {
	    String name = property.getPropertyName();

	    @SuppressWarnings({"unchecked"})
	    MutableProperty<Object> oldProperty =
		(MutableProperty<Object>)property;

	    @SuppressWarnings({"unchecked"})
	    MutableProperty<Object> newProperty =
		(MutableProperty<Object>)clone.getProperty(name);

	    newProperty.setValue(oldProperty.getValue());
	}

	return clone;
    }

    //
    // ManagedObject methods
    //

    @Override
    public String getId() {
	return toId(typeProperty.getValue(), subtypeProperty.getValue());
    }

    @Override
    public String getName() {
	return getId();
    }

    //
    // HasIcon methods
    //

    @Override
    public Icon getIcon(int height) {
	return PanelIconUtil.getClosestMimeIcon(typeProperty.getValue(),
	    subtypeProperty.getValue(), height);
    }

    //
    // MimeType methods
    //

    public MutableProperty<String[]> getExtensionsProperty() {
	return extensionsProperty;
    }

    public MimeTypes getParent() {
	return parent;
    }

    public MutableProperty<String> getSubtypeProperty() {
	return subtypeProperty;
    }

    public MutableProperty<String> getTypeProperty() {
	return typeProperty;
    }

    public boolean isInRepo() {
	return propertyName != null;
    }

    public void refresh(boolean force) throws ScfException {
	smfProperty.updateFromRepo(force);
    }

    protected void removeFromRepo() throws ScfException {
	if (isInRepo()) {
	    smfProperty.removeFromRepo();
	}
    }

    public void saveToRepo() throws ScfException {
	ApacheUtil.saveToRepo(getService(),
	    new ScfRunnable() {
		@Override
		public void run() throws ScfException {
		    if (smfProperty.isChanged()) {
			smfProperty.saveToRepo();
		    }
		}
	    });
    }

    //
    // Static methods
    //

    public static boolean isTokenChar(char c) {
	return c > 0x20 && c < 0x7F && TSPECIALS.indexOf(c) == -1;
    }

    public static boolean isValidToken(String token) {
	int length = token.length();
	if (length == 0) {
	    return false;
	}

	for (int i = 0; i < length; i++) {
	    if (!isTokenChar(token.charAt(i))) {
		return false;
	    }
	}

	return true;
    }

    public static String toId(String type, String subtype) {
	return type + SEPARATOR + subtype;
    }
}
