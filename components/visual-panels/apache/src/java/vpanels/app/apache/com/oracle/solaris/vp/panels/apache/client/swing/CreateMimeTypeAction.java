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
import java.awt.event.*;
import java.util.List;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.swing.action.AddManagedObjectAction;
import com.oracle.solaris.vp.util.misc.ObjectUtil;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;
import com.oracle.solaris.vp.util.swing.property.
    TextComponentPropertySynchronizer;

@SuppressWarnings({"serial"})
public class CreateMimeTypeAction extends AddManagedObjectAction
    <MimeType, CreateMimeTypeAction.Data, MimeType> {

    //
    // Inner classes
    //

    protected class Data {
	//
	// Instance data
	//

	public StringProperty typeProperty = new StringProperty();
	public StringProperty subtypeProperty = new StringProperty();
	public StringArrayProperty extProperty = new StringArrayProperty();
	public JOptionPane pane;
	public JDialog dialog;

	//
	// Constructors
	//

	public Data() {
	    ActionListener listener =
		new ActionListener() {
		    @Override
		    public void actionPerformed(ActionEvent e) {
			pane.setValue(JOptionPane.OK_OPTION);
		    }
		};

	    JLabel typeLabel = new JLabel(
		Finder.getString("mimetype.edit.type"));
	    JTextField typeField = GUIUtil.createTextField();
	    typeField.addActionListener(listener);
	    new TextComponentPropertySynchronizer<String, JTextField>(
		typeProperty, typeField, false);

	    JLabel subtypeLabel = new JLabel(
		Finder.getString("mimetype.edit.subtype"));
	    JTextField subtypeField = GUIUtil.createTextField();
	    subtypeField.addActionListener(listener);
	    new TextComponentPropertySynchronizer<String, JTextField>(
		subtypeProperty, subtypeField, false);

	    JLabel extLabel = new JLabel(
		Finder.getString("mimetype.edit.extensions"));
	    JTextField extField = GUIUtil.createTextField();
	    extField.addActionListener(listener);
	    new TextComponentPropertySynchronizer<String[], JTextField>(
		extProperty, extField, false);

	    JPanel formPanel = new JPanel();
	    formPanel.setOpaque(false);
	    Form form = new Form(formPanel, VerticalAnchor.TOP);

	    int gap = GUIUtil.getHalfGap();

	    ColumnLayoutConstraint c = new ColumnLayoutConstraint(
		HorizontalAnchor.FILL, gap);

	    HasAnchors a = new SimpleHasAnchors(
		HorizontalAnchor.LEFT, VerticalAnchor.CENTER);

	    form.addTable(2, gap, gap, HorizontalAnchor.LEFT, c);

	    form.add(typeLabel, a);
	    form.add(typeField, a);

	    form.add(subtypeLabel, a);
	    form.add(subtypeField, a);

	    form.add(extLabel, a);
	    form.add(extField, a);

	    pane = new JOptionPane(formPanel, JOptionPane.PLAIN_MESSAGE,
		JOptionPane.OK_CANCEL_OPTION);

	    dialog = pane.createDialog(getHasComponent().getComponent(),
		Finder.getString("mimetypes.action.create.title"));
	}
    }

    //
    // Static data
    //

    private static final String TEXT = Finder.getString(
	"mimetypes.action.create.button");

    //
    // Instance data
    //

    private MimeTypesControl control;

    //
    // Constructors
    //

    public CreateMimeTypeAction(MimeTypesControl control) {
	super(TEXT, null, control);
	this.control = control;
	setLoops(true);
    }

    //
    // StructuredAction methods
    //

    @Override
    public Data getRuntimeInput(List<MimeType> selection, Data data)
	throws ActionAbortedException {

	// Since this action navigates to the new object once created, we must
	// first navigate to control so that any outstanding changes in the
	// current Control are handled.
	try {
	    control.getNavigator().goToAsyncAndWait(false, control);
	} catch (NavigationException e) {
	    throw new ActionAbortedException(e);
	}

	if (data == null) {
	    data = new Data();
	}

	// Blocks until dismissed
	data.dialog.setVisible(true);

	if (!ObjectUtil.equals(data.pane.getValue(), JOptionPane.OK_OPTION)) {
	    throw new ActionAbortedException();
	}

	return data;
    }

    //
    // DefaultStructuredAction methods
    //

    @Override
    public MimeType workBusy(List<MimeType> selection, Data data)
	throws ActionAbortedException, ActionFailedException,
	ActionUnauthorizedException {

	String type = data.typeProperty.getValue();
	String subtype = data.subtypeProperty.getValue();
	String[] extensions = data.extProperty.getValue();

	// Throws ActionFailedException
	MimeTypeControl.validate(type, subtype);

	MimeTypes mimeTypes = control.getHasMimeTypes().getMimeTypes();

	if (mimeTypes.getMimeType(type, subtype) != null) {
	    throw new ActionFailedException(Finder.getString(
		"mimetype.error.duplicate", type, subtype));
	}

	MimeType mimeType = new MimeType(mimeTypes);
	mimeType.getTypeProperty().setValue(type);
	mimeType.getSubtypeProperty().setValue(subtype);
	mimeType.getExtensionsProperty().setValue(extensions);

	mimeTypes.addChildren(mimeType);

	// Navigate to the new MIME type
	Navigable navigable = new SimpleNavigable(
	    MimeTypeControl.ID, null,
	    MimeTypeControl.PARAM_MIMETYPE, mimeType.getId());

	control.getNavigator().goToAsync(false, control, navigable);

	return mimeType;
    }
}
