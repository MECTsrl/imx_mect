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

#ifndef CPPSEMANTICINFO_H
#define CPPSEMANTICINFO_H

#include "cpptools_global.h"

#include <texteditor/semantichighlighter.h>

#include <cplusplus/CppDocument.h>

#include <QHash>

namespace CppTools {

class CPPTOOLS_EXPORT SemanticInfo
{
public:
    struct Source
    {
        const CPlusPlus::Snapshot snapshot;
        const QString fileName;
        const QString code;
        const int line;
        const int column;
        const unsigned revision;
        const bool force;

        Source()
            : line(0), column(0), revision(0), force(false)
        { }

        Source(const CPlusPlus::Snapshot &snapshot,
               const QString &fileName,
               const QString &code,
               int line, int column,
               unsigned revision,
               bool force)
            : snapshot(snapshot), fileName(fileName),
              code(code), line(line), column(column),
              revision(revision), force(force)
        { }
    };

public:
    typedef TextEditor::HighlightingResult Use;

    typedef QHash<CPlusPlus::Symbol *, QList<Use> > LocalUseMap;
    typedef QHashIterator<CPlusPlus::Symbol *, QList<Use> > LocalUseIterator;

    SemanticInfo();

    unsigned revision;
    bool forced: 1;
    CPlusPlus::Snapshot snapshot;
    CPlusPlus::Document::Ptr doc;
    LocalUseMap localUses;
};

} // namespace CppTools

#endif // CPPSEMANTICINFO_H
