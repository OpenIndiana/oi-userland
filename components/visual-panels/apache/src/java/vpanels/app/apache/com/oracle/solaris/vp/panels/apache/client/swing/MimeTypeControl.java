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

import java.util.Map;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.swing.control.SettingsControl;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class MimeTypeControl
    extends SettingsControl<ApachePanelDescriptor, MimeTypePanel> {

    //
    // Static data
    //

    public static final String ID = "mimetype";
    public static final String PARAM_MIMETYPE = "mimetype";

    //
    // Instance data
    //

    private MimeTypesControl parent;
    private MimeType mimeType;

    //
    // Constructors
    //

    public MimeTypeControl(ApachePanelDescriptor descriptor,
	MimeTypesControl parent) {

	super(ID, null, descriptor);

	this.parent = parent;
    }

    //
    // Control methods
    //

    @Override
    protected UnsavedChangesAction getUnsavedChangesAction() {
	// Automatically save changes to the MimeType -- let MainControl
	// prompt the user to save them to the repo
	return UnsavedChangesAction.SAVE;
    }

    @Override
    public boolean isBrowsable() {
	// This Control requires init parameters
	return false;
    }

    @Override
    protected boolean isChanged() {
	// Save unconditionally, since a property that reports itself as
	// unchanged in the panel may still be changed from the corresponding
	// property in the MimeType.  Alternatively, we could compare each panel
	// property to its MimeType counterpart and save only if there are
	// differences, but this is easier and save() has low overhead.
	return true;
    }

    @Override
    protected void save() throws ActionAbortedException, ActionFailedException,
	ActionUnauthorizedException {

	setPropertyChangeIgnore(true);

	try {
	    MimeTypePanel panel = getComponent();

	    String type = panel.getTypeProperty().getValue();
	    String subtype = panel.getSubtypeProperty().getValue();

	    validate(type, subtype);

	    MimeType child = mimeType.getParent().getMimeType(type, subtype);
	    if (child != null && child != mimeType) {
		throw new ActionFailedException(Finder.getString(
		    "mimetype.error.duplicate", type, subtype));
	    }

	    mimeType.getTypeProperty().setValue(type);
	    mimeType.getSubtypeProperty().setValue(subtype);
	    mimeType.getExtensionsProperty().setValue(
		panel.getExtensionsProperty().getValue());
	} finally {
	    setPropertyChangeIgnore(false);
	}
    }

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	String param = getParameter(parameters, PARAM_MIMETYPE);

	MimeType mimeType = parent.getHasMimeTypes().getMimeTypes().
	    getMimeType(param);
	if (mimeType == null) {
	    throw new InvalidParameterException(getId(), PARAM_MIMETYPE, param);
	}

	this.mimeType = mimeType;
	setName(mimeType.getName());

	setPropertyChangeSource(mimeType);
	super.start(navigator, parameters);
    }

    @Override
    public void stop(boolean isCancel) throws NavigationAbortedException {
	super.stop(isCancel);

	// Remove reference so it can be garbage collected if deleted
	mimeType = null;
    }

    //
    // SwingControl methods
    //

    @Override
    protected MimeTypePanel createComponent() {
	return new MimeTypePanel();
    }

    @Override
    protected void initComponent() {
	MimeTypePanel panel = getComponent();
	panel.getChangeableAggregator().reset();
	panel.init(mimeType);
    }

    //
    // MimeTypeControl methods
    //

    public MimeType getMimeType() {
	return mimeType;
    }

    //
    // Static methods
    //

    /**
     * Validates the entered data in the UI.
     *
     * @exception   ActionFailedException
     *		    if the entered data is invalid (the thrown exception will
     *		    contain a localized error message)
     */
    public static void validate(String type, String subtype)
	throws ActionFailedException {

	if (type.isEmpty()) {
	    throw new ActionFailedException(Finder.getString(
		"mimetype.error.type.empty", type));
	}

	if (!MimeType.isValidToken(type)) {
	    throw new ActionFailedException(Finder.getString(
		"mimetype.error.type.invalid", type));
	}

	if (subtype.isEmpty()) {
	    throw new ActionFailedException(Finder.getString(
		"mimetype.error.subtype.empty", subtype));
	}

	if (!MimeType.isValidToken(subtype)) {
	    throw new ActionFailedException(Finder.getString(
		"mimetype.error.subtype.invalid", subtype));
	}
    }
}
