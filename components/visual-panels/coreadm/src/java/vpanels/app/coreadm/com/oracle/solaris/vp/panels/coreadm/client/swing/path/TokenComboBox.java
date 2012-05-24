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

package com.oracle.solaris.vp.panels.coreadm.client.swing.path;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.Border;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.Spacer;

@SuppressWarnings({"serial"})
public class TokenComboBox extends JComboBox {
    //
    // Inner classes
    //

    public static class TokenListCellRenderer extends JPanel
	implements ListCellRenderer {

	//
	// Static data
	//

	protected static final Border BORDER =
	    BorderFactory.createEmptyBorder(1, 1, 1, 1);

	protected static final String CARD_INSERT = "insert";
	protected static final String CARD_IN_LIST = "inlist";

	//
	// Instance data
	//

	private TokenLabel token;
	private JLabel text;
	private Spacer spacer = new Spacer();

	//
	// Constructors
	//

	public TokenListCellRenderer() {
	    setBorder(BORDER);
	    setBackground(Color.white);

	    Dimension d = null;
	    token = new TokenLabel();
	    for (String t : PathDocument.TOKENS) {
		token.setText(t);
		Dimension p = token.getPreferredSize();
		if (d == null || p.width > d.width) {
		    d = p;
		}
	    }
	    token.setPreferredSize(d);
	    token.setHorizontalAlignment(SwingConstants.CENTER);

	    text = new JLabel();
	    text.setBackground(UIManager.getColor(
		"List.selectionBackground"));

	    JPanel inListPanel = new JPanel(
		new BorderLayout(text.getIconTextGap(), 0));
	    inListPanel.setOpaque(false);

	    inListPanel.add(token, BorderLayout.WEST);
	    inListPanel.add(text, BorderLayout.CENTER);

	    JTextField insertLabel = new JTextField(
		Finder.getString("path.combo.insert"));
	    insertLabel.setHorizontalAlignment(SwingConstants.CENTER);

	    setLayout(new CardLayout());
	    add(insertLabel, CARD_INSERT);
	    add(inListPanel, CARD_IN_LIST);
	    setOpaque(false);
	}

	//
	// ListCellRenderer methods
	//

	@Override
	public Component getListCellRendererComponent(JList list, Object value,
	    int index, boolean isSelected, boolean cellHasFocus) {

	    token.setText((String)value);
	    text.setText(token.getToolTipText());
	    text.setOpaque(isSelected);
	    text.setForeground(UIManager.getColor(isSelected ?
		"List.selectionForeground" :
		"List.foreground"));

	    if (index == -1) {
		((CardLayout)getLayout()).show(this, CARD_INSERT);
	    } else {
		if (value == null) {
		    return spacer;
		}

		((CardLayout)getLayout()).show(this, CARD_IN_LIST);
	    }

	    return this;
	}
    }

    //
    // Static data
    //

    protected static final String[] DATA;
    static {
	DATA = new String[PathDocument.TOKENS.length + 1];
	System.arraycopy(PathDocument.TOKENS, 0, DATA, 1,
	    PathDocument.TOKENS.length);
    }

    //
    // Constructors
    //

    public TokenComboBox() {
	super(DATA);
	setRenderer(new TokenListCellRenderer());

	// Continuously reset selected item to null (-- Insert --)
	addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    if (getSelectedItem() != null) {
			// Change selection *after* notification of the current
			// selection is done
			EventQueue.invokeLater(
			    new Runnable() {
				@Override
				public void run() {
				    setSelectedItem(null);
				}
			    });
		    }
		}
	    });
    }

    //
    // Static methods
    //

    // XXX - Test, remove
    public static void main(String args[]) {
	TokenComboBox combo = new TokenComboBox();

	JPanel p = new JPanel(new BorderLayout());
	p.add(combo);
	p.setBorder(BorderFactory.createEmptyBorder(15, 15, 15, 15));

	JFrame frame = new JFrame();
	Container c = frame.getContentPane();
	c.setLayout(new BorderLayout());
	c.add(p, BorderLayout.CENTER);
	frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	frame.pack();
	frame.setVisible(true);
    }
}
