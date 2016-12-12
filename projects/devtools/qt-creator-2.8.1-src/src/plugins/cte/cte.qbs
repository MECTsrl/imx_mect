import qbs.base 1.0

import "../QtcPlugin.qbs" as QtcPlugin

QtcPlugin {
    name: "CTE"

    Depends { name: "Core" }
    Depends { name: "Qt"; submodules: ["widgets"] }

    files: [
	"ctedit.cpp",
	"ctedit.h",
	"cteplugin.cpp",
	"cteplugin.h",
	"parser.c",
	"parser.h"
    ]
}

