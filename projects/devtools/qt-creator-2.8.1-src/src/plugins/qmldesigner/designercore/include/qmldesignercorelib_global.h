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

#ifndef CORELIB_GLOBAL_H
#define CORELIB_GLOBAL_H

#include <QtGlobal>
#include <QList>

#include <utils/qtcoverride.h>

// Unnecessary since core isn't a dll any more.

#define TEST_CORESHARED_EXPORT

#if defined(DESIGNER_CORE_LIBRARY)
#  define QMLDESIGNERCORE_EXPORT Q_DECL_EXPORT
#else
#  define QMLDESIGNERCORE_EXPORT Q_DECL_IMPORT
#endif
namespace QmlDesigner {
typedef QByteArray PropertyName;
typedef QList<PropertyName> PropertyNameList;
typedef QByteArray TypeName;
typedef QByteArray IdName;
}
//#if defined(TEST_EXPORTS)
//#if defined(CORE_LIBRARY)
//#  define TEST_CORESHARED_EXPORT Q_DECL_EXPORT
//#else
//#  define TEST_CORESHARED_EXPORT Q_DECL_IMPORT
//#endif
//#else
//#  define TEST_CORESHARED_EXPORT
//#endif

#include <qglobal.h>

#endif // CORELIB_GLOBAL_H
