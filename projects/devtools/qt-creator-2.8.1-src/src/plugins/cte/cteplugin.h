/****************************************************************************
**
** Copyright (C) 2016 MECT srl.
** Contact: http://www.mect.it/
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General
** Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 3.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
****************************************************************************/

#ifndef CTEPLUGIN_H
#define CTEPLUGIN_H

#include <coreplugin/imode.h>
#include <extensionsystem/iplugin.h>
#include "ctedit.h"

namespace CTE {
namespace Internal {

class CTEPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "CTE.json")

public:
    CTEPlugin();
    ~CTEPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage);

    void extensionsInitialized();

private:
    Core::IMode *m_cteMode;

private slots:
    void enableIfCT();
};

} // namespace Internal

namespace Constants {

    const char * const CT_PROJ_REL_PATH = "config";
    const char * const CT_FILE_NAME = "Crosstable.csv";
} // namespace Constants
} // namespace CTE

#endif // CTEPLUGIN_H
