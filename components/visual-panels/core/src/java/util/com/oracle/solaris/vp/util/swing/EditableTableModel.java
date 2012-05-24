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

import javax.swing.table.TableModel;

public interface EditableTableModel extends TableModel {
    boolean attemptAddRow(Object[] rowData);

    boolean attemptInsertRow(int row, Object[] rowData);

    boolean canAddRow(Object[] rowData);

    /**
     * Gets the column of a {@link #getTemplateRow template row} to edit
     * immediately after it is added to the model.
     *
     * @return	    a column index &gt; 0, or -1 if no cell should be edited
     *		    initially
     */
    int getAutoEditedColumn();

    Object[] getTemplateRow();

    void moveRow(int start, int end, int to);

    void removeRow(int row);

    /**
     * Sets the number of rows in the model.  If the new size is greater than
     * the current size, new rows are added to the end of the model.  If the new
     * size is less than the current size, all rows at index {@code rowCount}
     * and greater are discarded.
     *
     * @param	    rowCount
     *		    an integer &gt;= 0
     */
    void setRowCount(int rowCount);
}
