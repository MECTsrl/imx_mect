#############################################################################
##
## Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
## Contact: http://www.qt-project.org/legal
##
## This file is part of Qt Creator.
##
## Commercial License Usage
## Licensees holding valid commercial Qt licenses may use this file in
## accordance with the commercial license agreement provided with the
## Software or, alternatively, in accordance with the terms contained in
## a written agreement between you and Digia.  For licensing terms and
## conditions see http://qt.digia.com/licensing.  For further information
## use the contact form at http://qt.digia.com/contact-us.
##
## GNU Lesser General Public License Usage
## Alternatively, this file may be used under the terms of the GNU Lesser
## General Public License version 2.1 as published by the Free Software
## Foundation and appearing in the file LICENSE.LGPL included in the
## packaging of this file.  Please review the following information to
## ensure the GNU Lesser General Public License version 2.1 requirements
## will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
##
## In addition, as a special exception, Digia gives you certain additional
## rights.  These rights are described in the Digia Qt LGPL Exception
## version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
##
#############################################################################

source("../../shared/qtcreator.py")

def main():
    startApplication("qtcreator" + SettingsPath)
    if not startedWithoutPluginError():
        return
    createProject_Qt_GUI(tempDir(), "DesignerTestApp")
    selectFromLocator("mainwindow.ui")
    widgetIndex = "{container=':qdesigner_internal::WidgetBoxCategoryListView' text='%s' type='QModelIndex'}"
    widgets = {"Push Button": 50,
               "Check Box": 100}
    for current in widgets.keys():
        dragAndDrop(waitForObject(widgetIndex % current), 5, 5,
                    ":FormEditorStack_qdesigner_internal::FormWindow", 20, widgets[current], Qt.CopyAction)
    connections = []
    for record in testData.dataset("connections.tsv"):
        connections.append([testData.field(record, col) for col in ["widget", "signal", "slot"]])
    for con in connections:
        selectFromLocator("mainwindow.ui")
        openContextMenu(waitForObject(con[0]), 5, 5, 0)
        activateItem(waitForObjectItem("{type='QMenu' unnamed='1' visible='1'}", "Go to slot..."))
        waitForObjectItem(":Select signal.signalList_QTreeWidget", con[1])
        clickItem(":Select signal.signalList_QTreeWidget", con[1], 5, 5, 0, Qt.LeftButton)
        clickButton(waitForObject(":Go to slot.OK_QPushButton"))
        editor = waitForObject(":Qt Creator_CppEditor::Internal::CPPEditorWidget")
        type(editor, "<Up>")
        type(editor, "<Up>")
        test.verify(waitFor('str(lineUnderCursor(editor)).strip() == con[2]', 1000),
                    'Comparing line "%s" to expected "%s"' % (lineUnderCursor(editor), con[2]))
    invokeMenuItem("File", "Save All")
    invokeMenuItem("File", "Exit")
