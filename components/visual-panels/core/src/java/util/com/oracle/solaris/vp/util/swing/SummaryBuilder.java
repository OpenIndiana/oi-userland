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

import java.util.*;
import javax.swing.*;

/**
 * Utility class for building a JComponent that contains
 * nicely-formatted "label: data" entries.
 */
public class SummaryBuilder
{
	private class RowData
	{
		String label_;
		String data_;

		RowData(String label, String data)
		{
			label_ = label;
			data_ = data;
		}
	}

	private java.util.List<RowData> rows_ = new LinkedList<RowData>();

	public SummaryBuilder()
	{
		/* Do nothing */
	}

	public void addRow(String label, String data)
	{
		rows_.add(new RowData(label, data));
	}

	public int getSize()
	{
		return (rows_.size());
	}

	public JComponent getComponent()
	{
		StringBuilder str = new StringBuilder(
		    "<html><table valign=\"top\">");
		for (RowData row : rows_) {
			str.append("<tr><td><b>");
			str.append(row.label_);
			str.append(":</b></td><td>");
			str.append(row.data_);
			str.append("</td></tr>");
		}
		str.append("</table></html>");

		JEditorPane result = new JEditorPane("text/html",
		    str.toString());
		result.setEditable(false);

		return (result);
	}
}
