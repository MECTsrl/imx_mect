import qbs.base 1.0

import "../QtcPlugin.qbs" as QtcPlugin

QtcPlugin {
    name: "CTE"

    Depends { name: "Core" }
    Depends { name: "Qt"; submodules: ["widgets", "xml", "network", "script"] }

    files: [
        "cteplugin.cpp",
        "cteplugin.h",
        "ctewindow.cpp",
        "ctewindow.h",
    ]
}

