import qbs.base 1.0

import "../QtcPlugin.qbs" as QtcPlugin

QtcPlugin {
    name: "Android"

    Depends { name: "Core" }
    Depends { name: "ProjectExplorer" }
    Depends { name: "Qt4ProjectManager" }
    Depends { name: "Debugger" }
    Depends { name: "QmlDebug" }
    Depends { name: "QtSupport" }
    Depends { name: "TextEditor" }
    Depends { name: "AnalyzerBase" }
    Depends { name: "Qt"; submodules: ["widgets", "xml", "network"] }

    property bool enable: false
    pluginspecreplacements: ({"ANDROID_EXPERIMENTAL_STR": (enable ? "false": "true")})

    cpp.includePaths: base.concat("../../shared")

    files: [
        "addnewavddialog.ui",
        "android.qrc",
        "androidanalyzesupport.cpp",
        "androidanalyzesupport.h",
        "androidconfigurations.cpp",
        "androidconfigurations.h",
        "androidconstants.h",
        "androidcreatekeystorecertificate.cpp",
        "androidcreatekeystorecertificate.h",
        "androidcreatekeystorecertificate.ui",
        "androiddebugsupport.cpp",
        "androiddebugsupport.h",
        "androiddeployconfiguration.cpp",
        "androiddeployconfiguration.h",
        "androiddeploystep.cpp",
        "androiddeploystep.h",
        "androiddeploystepfactory.cpp",
        "androiddeploystepfactory.h",
        "androiddeploystepwidget.cpp",
        "androiddeploystepwidget.h",
        "androiddeploystepwidget.ui",
        "androiddevice.cpp",
        "androiddevice.h",
        "androiddevicefactory.cpp",
        "androiddevicefactory.h",
        "androidgdbserverkitinformation.cpp",
        "androidgdbserverkitinformation.h",
        "androidglobal.h",
        "androidmanager.cpp",
        "androidmanager.h",
        "androidmanifestdocument.cpp",
        "androidmanifestdocument.h",
        "androidmanifesteditor.cpp",
        "androidmanifesteditor.h",
        "androidmanifesteditorfactory.cpp",
        "androidmanifesteditorfactory.h",
        "androidmanifesteditorwidget.cpp",
        "androidmanifesteditorwidget.h",
        "androidpackagecreationfactory.cpp",
        "androidpackagecreationfactory.h",
        "androidpackagecreationstep.cpp",
        "androidpackagecreationstep.h",
        "androidpackagecreationwidget.cpp",
        "androidpackagecreationwidget.h",
        "androidpackagecreationwidget.ui",
        "androidpackageinstallationfactory.cpp",
        "androidpackageinstallationfactory.h",
        "androidpackageinstallationstep.cpp",
        "androidpackageinstallationstep.h",
        "androidplugin.cpp",
        "androidplugin.h",
        "androidqtversion.cpp",
        "androidqtversion.h",
        "androidqtversionfactory.cpp",
        "androidqtversionfactory.h",
        "androidrunconfiguration.cpp",
        "androidrunconfiguration.h",
        "androidruncontrol.cpp",
        "androidruncontrol.h",
        "androidrunfactories.cpp",
        "androidrunfactories.h",
        "androidrunner.cpp",
        "androidrunner.h",
        "androidrunsupport.cpp",
        "androidrunsupport.h",
        "androidsettingspage.cpp",
        "androidsettingspage.h",
        "androidsettingswidget.cpp",
        "androidsettingswidget.h",
        "androidsettingswidget.ui",
        "androidtoolchain.cpp",
        "androidtoolchain.h",
        "javaparser.cpp",
        "javaparser.h",
    ]
}
