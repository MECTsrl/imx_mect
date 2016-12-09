/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef GENERICPROJECTCONSTANTS_H
#define GENERICPROJECTCONSTANTS_H

namespace GenericProjectManager {
namespace Constants {

const char PROJECTCONTEXT[]     = "GenericProject.ProjectContext";
const char GENERICMIMETYPE[]    = "text/x-generic-project"; // ### FIXME

// Contexts
const char C_FILESEDITOR[]      = ".files Editor";
const char FILES_EDITOR_ID[]    = "QT4.FilesEditor";

const char FILES_MIMETYPE[]     = "application/vnd.qtcreator.generic.files";
const char INCLUDES_MIMETYPE[]  = "application/vnd.qtcreator.generic.includes";
const char CONFIG_MIMETYPE[]    = "application/vnd.qtcreator.generic.config";

// Project
const char GENERICPROJECT_ID[]  = "GenericProjectManager.GenericProject";

const char HIDE_FILE_FILTER_SETTING[] = "GenericProject/FileFilter";
const char HIDE_FILE_FILTER_DEFAULT[] = "Makefile*; *.o; *.obj; *~; *.files; *.config; *.creator; *.user; *.includes";

const char SHOW_FILE_FILTER_SETTING[] = "GenericProject/ShowFileFilter";
const char SHOW_FILE_FILTER_DEFAULT[] = "*.c; *.cc; *.cpp; *.cp; *.cxx; *.c++; *.h; *.hh; *.hpp; *.hxx;";

} // namespace Constants
} // namespace GenericProjectManager

#endif // GENERICPROJECTCONSTANTS_H
