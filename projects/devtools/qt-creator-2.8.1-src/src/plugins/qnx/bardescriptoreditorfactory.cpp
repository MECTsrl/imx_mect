/**************************************************************************
**
** Copyright (C) 2011 - 2013 Research In Motion
**
** Contact: Research In Motion (blackberry-qt@qnx.com)
** Contact: KDAB (info@kdab.com)
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

#include "bardescriptoreditorfactory.h"

#include "qnxconstants.h"
#include "bardescriptoreditorwidget.h"

#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/editormanager/ieditor.h>

using namespace Qnx;
using namespace Qnx::Internal;

BarDescriptorEditorFactory::BarDescriptorEditorFactory(QObject *parent)
    : Core::IEditorFactory(parent)
    , m_mimeTypes(QStringList() << QLatin1String(Constants::QNX_BAR_DESCRIPTOR_MIME_TYPE))
{
}

QStringList BarDescriptorEditorFactory::mimeTypes() const
{
    return m_mimeTypes;
}

Core::Id BarDescriptorEditorFactory::id() const
{
    return Constants::QNX_BAR_DESCRIPTOR_EDITOR_ID;
}

QString BarDescriptorEditorFactory::displayName() const
{
    return tr("Bar descriptor editor");
}

Core::IEditor *BarDescriptorEditorFactory::createEditor(QWidget *parent)
{
    BarDescriptorEditorWidget *editorWidget = new BarDescriptorEditorWidget(parent);
    return editorWidget->editor();
}
