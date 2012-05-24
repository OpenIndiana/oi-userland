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

import java.awt.Component;
import java.util.List;
import javax.swing.JOptionPane;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.Control;
import com.oracle.solaris.vp.panel.swing.action.DeleteManagedObjectAction;
import com.oracle.solaris.vp.panel.swing.control.SwingControl;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.GUIUtil;

@SuppressWarnings({"serial"})
public class DeleteMimeTypeAction
    extends DeleteManagedObjectAction<MimeType, Object, List<MimeType>> {

    //
    // Static data
    //

    private static final String TEXT = Finder.getString(
	"mimetypes.action.delete.button");

    //
    // Instance data
    //

    private SwingControl control;

    //
    // Constructors
    //

    public DeleteMimeTypeAction(SwingControl control) {
	super(TEXT, null, control);
	this.control = control;
    }

    //
    // StructuredAction methods
    //

    @Override
    public Object getRuntimeInput(List<MimeType> selection, Object input)
	throws ActionAbortedException {

	int count = selection.size();
	if (count == 0) {
	    throw new ActionAbortedException();
	}

	String message = Finder.getString(
	    "mimetypes.action.delete.confirm." + count,
	    selection.get(0).getName(), count);

	int response = GUIUtil.showConfirmation(
	    getHasComponent().getComponent(), null, message,
	    JOptionPane.YES_NO_OPTION);

	if (response != JOptionPane.YES_OPTION) {
	    throw new ActionAbortedException();
	}

	return null;
    }

    /**
     * Enables this {@code Action} iff the selection is not empty.
     */
    @Override
    public void refresh() {
	setEnabled(getPresetInput().size() != 0);
    }

    //
    // DefaultStructuredAction methods
    //

    @Override
    public List<MimeType> workBusy(List<MimeType> selection, Object input)
	throws ActionAbortedException, ActionFailedException,
	ActionUnauthorizedException {

	if (!selection.isEmpty()) {
	    MimeTypes mimeTypes = selection.get(0).getParent();

	    for (MimeType mimeType : selection) {
		mimeTypes.scheduleRemove(mimeType);
	    }

	    // If the running Control is a MimeTypeControl for a just-deleted
	    // MimeType, reset the Control and navigate back to its parent
	    Control child = control.getRunningChild();
	    if (child instanceof MimeTypeControl) {
		MimeType mimeType = ((MimeTypeControl)child).getMimeType();
		if (selection.contains(mimeType)) {
		    child.doCancel();
		}
	    }
	}

	return selection;
    }
}
