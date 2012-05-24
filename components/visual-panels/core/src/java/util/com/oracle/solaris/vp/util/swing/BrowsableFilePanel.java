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

package com.oracle.solaris.vp.util.swing;

import java.awt.EventQueue;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.plaf.ComponentUI;
import com.oracle.solaris.vp.util.misc.IOUtil;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public class BrowsableFilePanel extends JPanel {
    //
    // Instance data
    //

    private JTextField field;
    private JButton browseButton;
    private JFileChooser chooser;

    //
    // Constructors
    //

    public BrowsableFilePanel(final boolean readOnly) {
	chooser = new JFileChooser() {
	    @Override
	    protected void setUI(ComponentUI newUI) {
		UIManager.put("FileChooser.readOnly", readOnly);
		super.setUI(newUI);
	    }
	};

	field = new JTextField(GUIUtil.getTextFieldWidth());
	browseButton = new JButton(Finder.getString("filepanel.button"));

	browseButton.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    EventQueue.invokeLater(
			new Runnable() {
			    @Override
			    public void run() {
				JTextField field = getField();
				JFileChooser chooser = getFileChooser();
				chooser.setSelectedFile(
				    chooser.getFileSystemView().
				    createFileObject(field.getText()));

				int option = chooser.showDialog(field, null);

				if (option == JFileChooser.APPROVE_OPTION) {
				    field.setText(IOUtil.getFullName(
					chooser.getSelectedFile()));
				}
			    }
			});
		}
	    });

	setLayout(new RowLayout());

	RowLayoutConstraint r = new RowLayoutConstraint(
	    VerticalAnchor.CENTER, GUIUtil.getHalfGap());

	add(field, r.setWeight(1));
	add(browseButton, r.setWeight(0));
    }

    public BrowsableFilePanel() {
	this(true);
    }

    //
    // BrowsableFilePanel methods
    //

    public JTextField getField() {
	return field;
    }

    public JFileChooser getFileChooser() {
	return chooser;
    }

    public JButton getBrowseButton() {
	return browseButton;
    }
}
