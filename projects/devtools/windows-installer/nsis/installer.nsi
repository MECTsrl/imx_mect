# Definitions
#

!define INSTALLBALL     "${ARCHNAME}"
!define MECTSUITEBAT    "${APPNAME}-${VERSIONMAJOR}.${VERSIONMINOR}.${VERSIONBUILD}-run.bat"
!define MECTSUITEMAIN   "qtcreator.exe"

!define ICONNAME        "mect.ico"
!define COMPANYNAME     "MECT"
!define DESCRIPTION     "Development suite for MECT TPAC devices"
!define HELPURL         "http://www.mect.it/"
!define UPDATEURL       "http://www.mect.it/"
!define ABOUTURL        "http://www.mect.it/"
!define UNINSTNAME      "${APPNAME}-${VERSIONMAJOR}.${VERSIONMINOR}.${VERSIONBUILD}-uninstaller.exe"
!define ARMCCSETUP      "arm-2011.03-41-arm-none-linux-gnueabi.exe"
!define QTHINI          "${QTH_DIR}\bin\qt.conf"
!define QTTINI          "${EMB_DIR}\usr\bin\qt.conf"
Var ARMCCPATH           # Target toolchain installation path
Var ARMCCUNINST         # Target toolchain uninstaller
 
# Need to write shared locations in file system and registry.
RequestExecutionLevel admin
 
# Installation directory
InstallDir "$PROGRAMFILES\${COMPANYNAME}\${APPNAME}"

# NOTE: always in DOS format
LicenseData "license.txt"

Name "${COMPANYNAME} - ${APPNAME}"
Icon "${ICONNAME}"
OutFile "${INSTALLPRG}"

!include LogicLib.nsh

# Pages
#

# License agreement
page license
# Install location
page directory
# Installation progress
page instfiles

# Utility
!macro VerifyUserIsAdmin
UserInfo::GetAccountType
pop $0
${If} $0 != "admin"             # Require admin rights on NT4+
    messageBox mb_iconstop "Administrator rights are required to continue."

    setErrorLevel 740           # ERROR_ELEVATION_REQUIRED

    quit
${EndIf}
!macroend
 
# Startup
#

function .onInit

    setShellVarContext all

    !insertmacro VerifyUserIsAdmin

functionEnd

# Installer
#

section "install"

    setOutPath $INSTDIR

    # Install main archive.
    #
    file "/oname=$TEMP\${INSTALLBALL}" ${INSTALLBALL}
    file "/oname=$TEMP\unzip.exe" "unzip.exe"
    execWait '"$TEMP\unzip.exe" -o $TEMP\${INSTALLBALL}'
    delete "$TEMP\${INSTALLBALL}"
    delete "$TEMP\unzip.exe"

    # Configure host Qt.
    #
    writeINIStr "${QTHINI}" "Paths" "Prefix" "$INSTDIR\${QTH_DIR}"
    writeINIStr "${QTHINI}" "Paths" "Documentation" "doc"
    writeINIStr "${QTHINI}" "Paths" "Headers" "include"
    writeINIStr "${QTHINI}" "Paths" "Libraries" "lib"
    writeINIStr "${QTHINI}" "Paths" "Binaries" "bin"
    writeINIStr "${QTHINI}" "Paths" "Plugins" "plugins"
    writeINIStr "${QTHINI}" "Paths" "Imports" "imports"
    writeINIStr "${QTHINI}" "Paths" "Data" "."
    writeINIStr "${QTHINI}" "Paths" "Translations" "translations"
    writeINIStr "${QTHINI}" "Paths" "Settings" "."
    writeINIStr "${QTHINI}" "Paths" "Examples" "examples"
    writeINIStr "${QTHINI}" "Paths" "Demos" "demos"
    flushINI "${QTHINI}"

    # Configure host Qt.
    #
    writeINIStr "${QTTINI}" "Paths" "Prefix" "$INSTDIR\${EMB_DIR}\usr"
    writeINIStr "${QTTINI}" "Paths" "Documentation" "doc"
    writeINIStr "${QTTINI}" "Paths" "Headers" "include"
    writeINIStr "${QTTINI}" "Paths" "Libraries" "lib"
    writeINIStr "${QTTINI}" "Paths" "Binaries" "bin"
    writeINIStr "${QTTINI}" "Paths" "Plugins" "plugins"
    writeINIStr "${QTTINI}" "Paths" "Imports" "imports"
    writeINIStr "${QTTINI}" "Paths" "Data" "."
    writeINIStr "${QTTINI}" "Paths" "Translations" "translations"
    writeINIStr "${QTTINI}" "Paths" "Settings" "."
    writeINIStr "${QTTINI}" "Paths" "Examples" "examples"
    writeINIStr "${QTTINI}" "Paths" "Demos" "demos"
    flushINI "${QTTINI}"

    # Install target compilation toolchain.
    #
    file "/oname=$TEMP\${ARMCCSETUP}" ${ARMCCSETUP}
    execWait '"$TEMP\${ARMCCSETUP}" -i GUI'
    delete "$TEMP\${ARMCCSETUP}"

    # Install icon(s).
    #
    file ${ICONNAME}


    # Grab compiler install path defined at installation time.
    readRegStr $ARMCCPATH HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Sourcery G++ Lite for ARM GNU/Linux" "InstallLocation"

    # Uninstaller (see function un.onInit and section "uninstall")
    writeUninstaller "$INSTDIR\${UNINSTNAME}"

    # Set up Start menu and Desktop.
    #
    createDirectory "$SMPROGRAMS\${COMPANYNAME}"
    createShortCut "$SMPROGRAMS\${COMPANYNAME}\${APPNAME}.lnk" "$INSTDIR\${QTC_DIR}\bin\${MECTSUITEMAIN}" "" "$INSTDIR\${ICONNAME}"
    createShortCut "$SMPROGRAMS\${COMPANYNAME}\${UNINSTNAME}.lnk" "$INSTDIR\${UNINSTNAME}" "" "$INSTDIR\${ICONNAME}"
    createShortCut "$DESKTOP\${APPNAME}.lnk" "$INSTDIR\${QTC_DIR}\bin\${MECTSUITEMAIN}" "" "$INSTDIR\${ICONNAME}"

    # Set up registry.
    #
    writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "DisplayName" "${APPNAME} v${VERSIONMAJOR}.${VERSIONMINOR}.${VERSIONBUILD} - ${DESCRIPTION}"
    writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "UninstallString" "$\"$INSTDIR\${UNINSTNAME}$\""
    writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "QuietUninstallString" "$\"$INSTDIR\${UNINSTNAME}$\" /S"
    writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "InstallLocation" "$INSTDIR"
    writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "DisplayIcon" "$\"$INSTDIR\${ICONNAME}$\""
    writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "Publisher" "${COMPANYNAME}"
    writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "HelpLink" "${HELPURL}"
    writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "URLUpdateInfo" "${UPDATEURL}"
    writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "URLInfoAbout" "${ABOUTURL}"
    writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "DisplayVersion" "${VERSIONMAJOR}.${VERSIONMINOR}.${VERSIONBUILD}"
    writeRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "VersionMajor" ${VERSIONMAJOR}
    writeRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "VersionMinor" ${VERSIONMINOR}
    # No option to modify or repair the install
    writeRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "NoModify" 1
    writeRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "NoRepair" 1
    writeRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "EstimatedSize" ${INSTALLSIZE}


    # Update %PATH%
    # 
    # Add new paths

    # Remove duplicate paths.
    file "/oname=$TEMP\RemoveDupfromPATH.ps1" "RemoveDupfromPATH.ps1"
    #execWait '"powershell.exe" -NoProfile -ExecutionPolicy Bypass -File $TEMP\RemoveDupfromPATH.ps1'

    # Script to run the MECTSuite in the proper environment.
    #
    # Create.
    push $9
    fileOpen $9 "$INSTDIR\${MECTSUITEBAT}" w
    fileWrite $9 "@echo off$\r$\n"
    fileWrite $9 "powershell.exe -NoProfile -ExecutionPolicy Bypass -File $TEMP\RemoveDupfromPATH.ps1$\r$\n"
    fileWrite $9 'setlocal EnableDelayedExpansion$\r$\n'
    fileWrite $9 'reg.exe add "HKLM\System\CurrentControlSet\Control\Session Manager\Environment" /v Path /t REG_SZ /d "%path%;$INSTDIR\${MINGW_DIR}\bin;$INSTDIR\${MINGW_DIR}\msys\1.0\bin;$INSTDIR\${QTC_DIR}\bin;$INSTDIR\${QTH_DIR}\bin;$INSTDIR\${QTH_DIR}\lib" /f$\r$\n'
    fileWrite $9 "powershell.exe -NoProfile -ExecutionPolicy Bypass -File $TEMP\RemoveDupfromPATH.ps1$\r$\n"
    fileWrite $9 "exit$\r$\n"
    fileClose $9
    pop $9
    # Run.
    execWait "$INSTDIR\${MECTSUITEBAT}"
    # Discard.
    delete "$INSTDIR\${MECTSUITEBAT}"
    delete "$TEMP\RemoveDupfromPATH.ps1"

sectionEnd

# Uninstaller
#

function un.onInit

    setShellVarContext all

    #Verify the uninstaller - last chance to back out
    messageBox MB_OKCANCEL "Permanantly remove ${APPNAME}?" IDOK next
	abort
next:
    !insertmacro VerifyUserIsAdmin

functionEnd

section "uninstall"

    # Get the actual install path.
    readRegStr $INSTDIR HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "InstallLocation"

    # Remove all files.
    #
    delete "$INSTDIR\${ICONNAME}"
    delete "$INSTDIR\${MECTSUITEBAT}"
    delete "${QTHINI}"
    delete "${QTTINI}"
    # NOTE Keep in sync with the contents of the installs.
    rmDir /r "$INSTDIR\${QTC_DIR}"
    rmDir /r "$INSTDIR\${EMB_DIR}"
    rmDir /r "$INSTDIR\${QTH_DIR}"
    rmDir /r "$INSTDIR\${MINGW_DIR}"

    # Clean up the Start Menu.
    #
    delete "$SMPROGRAMS\${COMPANYNAME}\${APPNAME}.lnk"
    delete "$SMPROGRAMS\${COMPANYNAME}\${UNINSTNAME}.lnk"
    delete "$DESKTOP\${APPNAME}.lnk"
    rmDir "$SMPROGRAMS\${COMPANYNAME}"

    # Clean up the registry.
    #
    deleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}"

    # LAST: delete the uninstaller.
    delete "$INSTDIR\${UNINSTNAME}"

    # Uninstall the target toolchain.
    readRegStr $ARMCCUNINST HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Sourcery G++ Lite for ARM GNU/Linux" "UninstallString"
    execWait "$ARMCCUNINST"

    # Remove the install directory (if empty).
    rmDir "$INSTDIR"

sectionEnd
