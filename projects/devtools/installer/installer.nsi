# FIXME REMOVE!
SetCompress off

# Definitions
#

!define VERSION         "${VERSIONMAJOR}.${VERSIONMINOR}.${VERSIONBUILD}"
!define UNINSTKEY       "${COMPANYNAME} ${APPNAME} v${VERSION}"

!define MECTSUITEBAT    "${APPNAME}-${VERSION}-run.bat"
!define MECTSUITEVBS    "${APPNAME}-${VERSION}-exec.vbs"
!define MECTSUITEMAIN   "qtcreator.exe"

!define ICONNAME        "mect.ico"
!define COMPANYNAME     "MECT"
!define DESCRIPTION     "Development suite for MECT TPAC devices"
!define HELPURL         "http://www.mect.it/"
!define UPDATEURL       "http://www.mect.it/"
!define ABOUTURL        "http://www.mect.it/"
!define RUNNAME         "${APPNAME}-v${VERSION}"
!define UNINSTNAME      "${APPNAME}-v${VERSION}-uninstall.exe"
!define ARMCCSETUP      "arm-2011.03-41-arm-none-linux-gnueabi.exe"
!define MECTAPPSBALL	"MECTAPPS.zip"
!define MECTAPPS_DIR	"MectApps"
!define CANBALL		"ATCM.zip"
!define CAN_DIR		"ATCM"
!define PLCBALL		"PLC.zip"
!define QTHINI          "${QTH_DIR}\bin\qt.conf"
!define QTHARMINI       "${QTH_ARM_DIR}\bin\qt.conf"
!define QTTINI          "${EMB_DIR}\usr\bin\qt.conf"
!define ROAMINGAPPDATA  "$LOCALAPPDATA\..\Roaming"
!define QTPROJECT	"QtProject"

Var PLCWININSTPATH	# PLC Engineering executable and path
Var PLCUNIXINSTPATH	# PLC Engineering executable and path with forward slashes
#Var PLCWINUNINST	# PLC Engineering uninstaller
Var PLCWINBINPATH	# PLC Engineering binary path
Var ARMCCWININSTPATH	# Target toolchain installation path
Var ARMCCUNIXINSTPATH	# Target compiler install directory with forward slashes
Var ARMCCWINUNINST	# Target toolchain uninstaller
Var UNIXINSTDIR		# MinGW install directory with forward slashes
Var QTCUNIX_DIR		# Qt Creator install directory with forward slashes
Var QTHUNIX_DIR		# Qt host (x86) install directory with forward slashes
Var EMBUNIX_DIR		# Embedded root file system install directory

!define QTPRJSETUPBAT   "$TEMP\QTPRJSETUP.BAT"
!define QTPRJSETUPSH    "$TEMP\qtprjsetup.sh"

!define QTPOSTINSTBAT   "$TEMP\QTPOSTINST.BAT"
!define QTPOSTINSTSH    "$TEMP\qtpostinst.sh"

!define QTARMPOSTINSTBAT "$TEMP\QTARMPOSTINST.BAT"
!define QTARMPOSTINSTSH  "$TEMP\qtarmpostinst.sh"

# Need to write shared locations in file system and registry.
RequestExecutionLevel admin
 
# Installation directory
InstallDir "C:\${COMPANYNAME}\${APPNAME}-v${VERSION}"

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
page directory "" "" "DirectoryLeave"
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

Function DirectoryLeave
 
    # Call the CheckForSpaces function.
    Push $INSTDIR
        Call CheckForSpaces
    Pop $R0

    # No forbidden characters in $INSTDIR?
    StrCmp $R0 0 NoSpaces
        # Show message box then go back to the directory page.
        messageBox MB_OK|MB_ICONEXCLAMATION \
            'Error: The installation path cannot contain$\n\
            spaces or ! @ # $$ % ^ & * , ;$\n\
            $\n\
            Please select a suitable installation path.'
        Abort

    NoSpaces:

    ${If} ${FileExists} '$INSTDIR\*'
        messageBox MB_YESNO|MB_ICONEXCLAMATION \
	    '$INSTDIR exists and will be deleted.$\n\
	    Continue the installation?' IDYES yep
	    Abort
	yep:
	    rmDir /r '$INSTDIR'
    ${EndIf}

FunctionEnd

Function CheckForSpaces

    Exch $R0
    Push $R1
    Push $R2
    Push $R3
    StrCpy $R1 -1
    StrCpy $R3 $R0
    StrCpy $R0 0
    loop:
	StrCpy $R2 $R3 1 $R1
	IntOp $R1 $R1 - 1
	StrCmp $R2 "" done
	StrCmp $R2 "!" found
	StrCmp $R2 "@" found
	StrCmp $R2 "#" found
	StrCmp $R2 "$$" found
	StrCmp $R2 "%" found
	StrCmp $R2 "^" found
	StrCmp $R2 "&" found
	StrCmp $R2 "*" found
	StrCmp $R2 "," found
	StrCmp $R2 ";" found
	StrCmp $R2 " " found
	Goto loop
    found:
        IntOp $R0 $R0 + 1
    Goto loop
    done:
    Pop $R3
    Pop $R2
    Pop $R1
    Exch $R0

FunctionEnd


# Slash to Backslash bidirectional converter.
# 
# Usage:
# Push $windowsPath (e.g., 'c:\this\and\that\filename.htm')
# Push "\" (or "/")
# Call strSlash
# Pop $R0	# $R0 contains 'c:/this/and/that/filename.htm'
Function strSlash
   Exch $R3	; $R3 = needle ("\" or "/")
   Exch
   Exch $R1	; $R1 = String to replacement in (haystack)
   Push $R2	; Replaced haystack
   Push $R4	; $R4 = not $R3 ("/" or "\")
   Push $R6
   Push $R7	; Scratch reg
   StrCpy $R2 ""
   StrLen $R6 $R1
   StrCpy $R4 "\"
   StrCmp $R3 "/" loop
   StrCpy $R4 "/"  
loop:
   StrCpy $R7 $R1 1
   StrCpy $R1 $R1 $R6 1
   StrCmp $R7 $R3 found
   StrCpy $R2 "$R2$R7"
   StrCmp $R1 "" done loop
found:
   StrCpy $R2 "$R2$R4"
   StrCmp $R1 "" done loop
done:
   StrCpy $R3 $R2
   Pop $R7
   Pop $R6
   Pop $R4
   Pop $R2
   Pop $R1
   Exch $R3
FunctionEnd


 
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

    # Install the icon(s).
    #
    file ${ICONNAME}

    # Install the main archive.
    #
    # FIXME Install using an external ZIP archive.

    # unzip
    file '/oname=$TEMP\unzip.exe' unzip.exe

    # CAN
    file '/oname=$TEMP\${CANBALL}' '${CANBALL}'
    ClearErrors
    execWait '"$TEMP\unzip.exe" -o "$TEMP\${CANBALL}"'
    ifErrors 0 CANnoError
	messageBox MB_OK|MB_ICONEXCLAMATION 'Error extracting$\n$TEMP\${CANBALL}$\n$\nPress OK to abort the installation.'
	quit
CANnoError:
    delete '$TEMP\${CANBALL}'

    # MECT apps
    file '/oname=$TEMP\${MECTAPPSBALL}' '${MECTAPPSBALL}'
    rmDir /r "$TEMP\MECTAPPS_TMPDIR"
    createDirectory "$TEMP\MECTAPPS_TMPDIR"
    ClearErrors
    execWait '"$TEMP\unzip.exe" -o "$TEMP\${MECTAPPSBALL}" -d "$TEMP\MECTAPPS_TMPDIR"'
    ifErrors 0 APPSnoError
	messageBox MB_OK|MB_ICONEXCLAMATION 'Error extracting$\n$TEMP\${MECTAPPSBALL}$\n$\nPress OK to abort the installation.'
	quit
APPSnoError:
    delete '$TEMP\${MECTAPPSBALL}'
    ClearErrors
    rmDir /r '$INSTDIR\${MECTAPPS_DIR}'
    execWait 'xcopy "$TEMP\MECTAPPS_TMPDIR" "$INSTDIR\" /E /Y /B'
    ifErrors 0 COPYAPPSnoError
	messageBox MB_OK|MB_ICONEXCLAMATION 'Error installing in$\n$INSTDIR\${MECTAPPS_DIR}$\n$\nPress OK to abort the installation.'
	quit
COPYAPPSnoError:
    rmDir /r "$TEMP\MECTAPPS_TMPDIR"

    # Bulk: Qt host, Qt Creator, root FS target, qmake target, etc.
    file '/oname=$TEMP\${ARCHNAME}' '${ARCHNAME}'
    ClearErrors
    execWait '"$TEMP\unzip.exe" -o "$TEMP\${ARCHNAME}"'
    ifErrors 0 INSTnoError
	messageBox MB_OK|MB_ICONEXCLAMATION 'Error extracting$\n$TEMP\${ARCHNAME}$\n$\nPress OK to abort the installation.'
	quit
INSTnoError:
    delete '$TEMP\${ARCHNAME}'

    # FIXME Compress all files within the installer.
    ### file /r install-them-all/*

    #
    # Install PLC Engineering.
    #

    file '/oname=$TEMP\${PLCBALL}' '${PLCBALL}'
    rmDir /r "$TEMP\PLC"
    ClearErrors
    execWait '"$TEMP\unzip.exe" -o "$TEMP\${PLCBALL}" -d "$TEMP"'
    ifErrors 0 PLCEXnoError
	messageBox MB_OK|MB_ICONEXCLAMATION 'Error extracting$\n$TEMP\${PLCBALL}$\n$\nPress OK to abort the installation.'
	quit
PLCEXnoError:
    delete '$TEMP\${PLCBALL}'
    ClearErrors
    execWait '$TEMP\PLC\ATCMcontrol_Engineering_v2.20.02.4018\Setup.exe'
    ifErrors 0 PLCnoError
	messageBox MB_OK|MB_ICONEXCLAMATION 'Error installing PLC Engineering.$\n$\nPress OK to abort the installation.'
	quit
PLCnoError:
    rmDir /r '$TEMP\PLC'

    # Collect the PLC Engineering executable and full path.
    readRegStr $PLCWININSTPATH HKLM "Software\Classes\4CProjectFile\shell\open\command" ""
    readRegStr $PLCWINBINPATH HKLM "Software\Softing\4ControlV2\2.0" "BinPath"

    # Fix PLC Engineering installation.
    delete '$PLCWINBINPATH\ATHW119\${PLC_ATHW}'
    file '/oname=$PLCWINBINPATH\ATHW119\${PLC_ATHW}' ${PLC_ATHW}

    #
    # Install the target compilation toolchain.
    #

    file '/oname=$TEMP\${ARMCCSETUP}' ${ARMCCSETUP}
    ClearErrors
    execWait '"$TEMP\${ARMCCSETUP}" -i GUI'
    ifErrors 0 ARMCCnoError
	messageBox MB_OK|MB_ICONEXCLAMATION 'Error installing Code SOurcery toolchain.$\n$\nPress OK to abort the installation.'
	quit
ARMCCnoError:
    delete '$TEMP\${ARMCCSETUP}'

    # Collect the compiler install path.
    readRegStr $ARMCCWININSTPATH HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Sourcery G++ Lite for ARM GNU/Linux" "InstallLocation"

    #
    # Install additional fonts.
    #

    file '/oname=$TEMP\${FONTS_ARC}' ${FONTS_ARC}
    rmDir /r '$TEMP\MSfonts'
    ClearErrors
    execWait '"$TEMP\unzip.exe" -o "$TEMP\${FONTS_ARC}" -d "$TEMP\MSfonts"'
    ifErrors 0 FONTEXnoError
	messageBox MB_OK|MB_ICONEXCLAMATION 'Error installing additional fonts.$\n$\nPress OK to continue.'
FONTEXnoError:
    delete '$TEMP\${FONTS_ARC}'
    ClearErrors
    execWait '"$SYSDIR\CScript.exe" $TEMP\MSfonts\Fonts\install.vbs $TEMP\MSfonts //e:vbscript //B //NOLOGO'
    ifErrors 0 FONTINnoError
	messageBox MB_OK|MB_ICONEXCLAMATION 'Error installing additional fonts.$\n$\nPress OK to continue.'
FONTINnoError:
    rmDir /r '$TEMP\Fonts'

    #
    # Cleanup
    #

    delete '$TEMP\unzip.exe'

    #
    # Post-install setup
    #

    # Set up the Start menu and the Desktop.
    #
    createDirectory "$SMPROGRAMS\${COMPANYNAME}"
    createShortCut "$SMPROGRAMS\${COMPANYNAME}\${RUNNAME}.lnk" "$INSTDIR\${MECTSUITEVBS}" "" "$INSTDIR\${ICONNAME}"
    createShortCut "$SMPROGRAMS\${COMPANYNAME}\${UNINSTNAME}.lnk" "$INSTDIR\${UNINSTNAME}" "" "$INSTDIR\${ICONNAME}"
    createShortCut "$DESKTOP\${RUNNAME}.lnk" "$INSTDIR\${MECTSUITEVBS}" "" "$INSTDIR\${ICONNAME}"

    # Set up the registry.
    #
    writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${UNINSTKEY}" "DisplayName" "${APPNAME} v${VERSION} - ${DESCRIPTION}"
    writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${UNINSTKEY}" "UninstallString" "$\"$INSTDIR\${UNINSTNAME}$\""
    writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${UNINSTKEY}" "QuietUninstallString" "$\"$INSTDIR\${UNINSTNAME}$\" /S"
    writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${UNINSTKEY}" "InstallLocation" "$INSTDIR"
    writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${UNINSTKEY}" "DisplayIcon" "$\"$INSTDIR\${ICONNAME}$\""
    writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${UNINSTKEY}" "Publisher" "${COMPANYNAME}"
    writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${UNINSTKEY}" "HelpLink" "${HELPURL}"
    writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${UNINSTKEY}" "URLUpdateInfo" "${UPDATEURL}"
    writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${UNINSTKEY}" "URLInfoAbout" "${ABOUTURL}"
    writeRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${UNINSTKEY}" "DisplayVersion" "${VERSION}"
    writeRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${UNINSTKEY}" "VersionMajor" ${VERSIONMAJOR}
    writeRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${UNINSTKEY}" "VersionMinor" ${VERSIONMINOR}
    writeRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${UNINSTKEY}" "VersionBuild" ${VERSIONBUILD}
    # There is no option to modify or repair the install.
    writeRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${UNINSTKEY}" "NoModify" 1
    writeRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${UNINSTKEY}" "NoRepair" 1
    writeRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${UNINSTKEY}" "EstimatedSize" ${INSTALLSIZE}
    writeRegStr HKLM "Software\ATCM" "CAN" "$\"$INSTDIR\ATCM\CANOpen\$\""
    writeRegStr HKLM "Software\ATCM" "EDS" "$\"$INSTDIR\ATCM\CANOpen\eds\$\""
    writeRegStr HKLM "Software\ATCM" "TEMPLATE" "$\"$INSTDIR$\""
    writeRegStr HKLM "Software\ATCM" "IPADDR" "$\"192.168.0.210$\""
    writeRegStr HKLM "Software\ATCM" "NETMASK" "$\"255.255.255.0$\""
    writeRegStr HKLM "Software\ATCM" "user" "$\"root$\""
    writeRegStr HKLM "Software\ATCM" "pwd" "$\"root$\""
    writeRegDWORD HKLM "Software\ATCM" "LANG" 1


    #
    # Script to run the MECT Suite in the proper environment.
    #

    # Get the MinGW installation path suitable for Qt (forward slashes).
    push $INSTDIR
    push "\"
    call strSlash
    pop $R0
    strCpy $UNIXINSTDIR $R0

    # Get the target compilation chain installation path suitable for Qt (forward slashes).
    push $ARMCCWININSTPATH
    push "\"
    call strSlash
    pop $R0
    strCpy $ARMCCUNIXINSTPATH $R0

    # Get the PLC Engineering executable and path suitable for Qt (forward slashes).
    push $PLCWININSTPATH
    push "\"
    call strSlash
    pop $R0
    strCpy $PLCUNIXINSTPATH $R0

    # Get the Qt Creator install directory suitable for Qt (forward slashes).
    push $INSTDIR\${QTC_DIR}
    push "\"
    call strSlash
    pop $R0
    strCpy $QTCUNIX_DIR $R0

    # Get the Qt x86 install directory suitable for Qt (forward slashes).
    push $INSTDIR\${QTH_DIR}
    push "\"
    call strSlash
    pop $R0
    strCpy $QTHUNIX_DIR $R0

    # Get the Qt x86 install directory suitable for Qt (forward slashes).
    push $INSTDIR\${EMB_DIR}
    push "\"
    call strSlash
    pop $R0
    strCpy $EMBUNIX_DIR $R0

    # Create the actual launcher script that sets up the environment.
    push $9
    fileOpen $9 "$INSTDIR\${MECTSUITEBAT}" w
    fileWrite $9 "@echo off$\r$\n"
    fileWrite $9 "$\r$\n"
    fileWrite $9 'setlocal EnableDelayedExpansion$\r$\n'
    fileWrite $9 "$\r$\n"
    fileWrite $9 'set PATH=$ARMCCWININSTPATH\bin;%PATH%$\r$\n'
    fileWrite $9 'set PATH=$INSTDIR\${MINGW_DIR}\bin;%PATH%$\r$\n'
    fileWrite $9 'set PATH=$INSTDIR\${MINGW_DIR}\msys\1.0\bin;%PATH%$\r$\n'
    fileWrite $9 'set PATH=$INSTDIR\${QTC_DIR}\bin;%PATH%$\r$\n'
    fileWrite $9 'set PATH=$INSTDIR\${QTH_DIR}\bin;%PATH%$\r$\n'
    fileWrite $9 'set PATH=$INSTDIR\${QTH_DIR}\lib;%PATH%$\r$\n'
    fileWrite $9 "$\r$\n"
    fileWrite $9 'set PLCUNIXINSTPATH=$PLCUNIXINSTPATH$\r$\n'
    fileWrite $9 "$\r$\n"
    fileWrite $9 'set MECT_QTC_INSTALL_DIR=$QTCUNIX_DIR$\r$\n'
    fileWrite $9 'set MECT_QTH_INSTALL_DIR=$QTHUNIX_DIR$\r$\n'
    fileWrite $9 'set MECT_QTT_INSTALL_DIR=$EMBUNIX_DIR$\r$\n'
    fileWrite $9 "$\r$\n"
    fileWrite $9 '"$INSTDIR\${QTC_DIR}\bin\qtcreator.exe" -settingspath "$INSTDIR"$\r$\n'
    fileWrite $9 "$\r$\n"
    fileWrite $9 "exit$\r$\n"
    fileClose $9
    pop $9
    # Create the "silent" (no cmd window) launcher.
    push $9
    fileOpen $9 "$INSTDIR\${MECTSUITEVBS}" w
    fileWrite $9 'Set WshShell = CreateObject("WScript.Shell")$\r$\n'
    fileWrite $9 'WshShell.Run chr(34) & "$INSTDIR\${MECTSUITEBAT}" & Chr(34), 0$\r$\n'
    fileWrite $9 "$\r$\n"
    fileWrite $9 "Set WshShell = Nothing$\r$\n"
    pop $9

    # Create the uninstaller (see the function un.onInit and the section "uninstall").
    writeUninstaller "$INSTDIR\${UNINSTNAME}"


    #
    # Post-install configurations
    #

    # Configure the Qt Creator configuration templates (QtProject).
    #
    delete "${QTPRJSETUPSH}"
    delete "${QTPRJSETUPBAT}"
    # Create the worker shell script.
    push $9
    fileOpen $9 '${QTPRJSETUPSH}' w
    fileWrite $9 '#!/bin/sh$\n'
    fileWrite $9 '$\n'
    fileWrite $9 'set -x$\n'
    fileWrite $9 '$\n'
    fileWrite $9 'cd "$INSTDIR"$\n'
    fileWrite $9 'for f in $$(find ${QTPROJECT} -type f -print); do$\n'
    fileWrite $9 "    sed -i '$\n"
    fileWrite $9 "        s|@@_TARGETCC_INSTALL_PATH_@@|$ARMCCUNIXINSTPATH|;$\n"
    fileWrite $9 "        s|@@_MECTSUITE_INSTALL_PATH_@@|$UNIXINSTDIR|;$\n"
    fileWrite $9 "    ' $$f$\n"
    fileWrite $9 'done$\n'
    pop $9
    # Create the launcher batch script for the worker script.
    push $9
    fileOpen $9 '${QTPRJSETUPBAT}' w
    fileWrite $9 '@echo off$\r$\n'
    fileWrite $9 'set PATH=$INSTDIR\${MINGW_DIR}\bin;%PATH%$\r$\n'
    fileWrite $9 'set PATH=$INSTDIR\${MINGW_DIR}\msys\1.0\bin;%PATH%$\r$\n'
    fileWrite $9 'set PATH=$INSTDIR\${QTC_DIR}\bin;%PATH%$\r$\n'
    fileWrite $9 'set PATH=$INSTDIR\${QTH_DIR}\bin;%PATH%$\r$\n'
    fileWrite $9 'set PATH=$INSTDIR\${QTH_DIR}\lib;%PATH%$\r$\n'
    fileWrite $9 '@echo on$\r$\n'
    fileWrite $9 '$\r$\n'
    fileWrite $9 'bash "${QTPRJSETUPSH}"$\r$\n'
    fileWrite $9 '$\r$\n'
    fileWrite $9 'exit$\r$\n'
    fileClose $9
    pop $9
    # Do configure the Qt Creator configuration templates.
    execWait "${QTPRJSETUPBAT}"
    # Clean up.
    delete "${QTPRJSETUPSH}"
    delete "${QTPRJSETUPBAT}"
    execWait 'xcopy "$INSTDIR\${QTPROJECT}" "$INSTDIR\${QTPROJECT}-default\" /E /Y /B'
    # Correct file attributes
    delete "$INSTDIR\${QTPROJECT}"
    execWait 'robocopy "$INSTDIR\${QTPROJECT}-default" "$INSTDIR\${QTPROJECT}\" /E /S '

    # Configure the host Qt and Qt Creator.
    #
    writeINIStr "${QTHINI}" "Paths" "Prefix" "$UNIXINSTDIR/${QTH_DIR}"
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

    delete "${QTPOSTINSTSH}"
    delete "${QTPOSTINSTBAT}"
    # Create the worker shell script.
    push $9
    fileOpen $9 '${QTPOSTINSTSH}' w
    fileWrite $9 '#!/bin/sh$\n'
    fileWrite $9 '$\n'
    fileWrite $9 'set -x$\n'
    fileWrite $9 '$\n'
    fileWrite $9 'cd "$INSTDIR\${QTH_DIR}\lib"$\n'
    fileWrite $9 'for f in $$(find . -type f -name \*.prl -print); do$\n'
    fileWrite $9 "    sed -i 's|@@_QT_INSTALL_DIR_@@|$UNIXINSTDIR/${QTH_DIR}|' $$f$\n"
    fileWrite $9 'done$\n'
    fileWrite $9 '$\n'
    fileWrite $9 'cd "$INSTDIR\${MECTAPPS_DIR}"$\n'
    fileWrite $9 'for f in $$(find . -type f -name systemicons.qrc -print); do$\n'
    fileWrite $9 "    sed -i 's|@@_MECTAPPS_SYSTEMICONS_PREFIX_@@|$UNIXINSTDIR/${QTC_DIR}|' $$f$\n"
    fileWrite $9 'done$\n'
    pop $9
    # Create the launcher batch script for the worker script.
    push $9
    fileOpen $9 '${QTPOSTINSTBAT}' w
    fileWrite $9 '@echo off$\r$\n'
    fileWrite $9 'set PATH=$INSTDIR\${MINGW_DIR}\bin;%PATH%$\r$\n'
    fileWrite $9 'set PATH=$INSTDIR\${MINGW_DIR}\msys\1.0\bin;%PATH%$\r$\n'
    fileWrite $9 'set PATH=$INSTDIR\${QTC_DIR}\bin;%PATH%$\r$\n'
    fileWrite $9 'set PATH=$INSTDIR\${QTH_DIR}\bin;%PATH%$\r$\n'
    fileWrite $9 'set PATH=$INSTDIR\${QTH_DIR}\lib;%PATH%$\r$\n'
    fileWrite $9 '@echo on$\r$\n'
    fileWrite $9 '$\r$\n'
    fileWrite $9 'bash "${QTPOSTINSTSH}"$\r$\n'
    fileWrite $9 '$\r$\n'
    fileWrite $9 'exit$\r$\n'
    fileClose $9
    pop $9
    # Configure the host Qt.
    execWait "${QTPOSTINSTBAT}"
    # Clean up.
    delete "${QTPOSTINSTSH}"
    delete "${QTPOSTINSTBAT}"

    # Configure the target (ARM) Qt.
    #
    writeINIStr "${QTHARMINI}" "Paths" "Prefix" "$UNIXINSTDIR/${QTH_ARM_DIR}"
    writeINIStr "${QTHARMINI}" "Paths" "Documentation" "doc"
    writeINIStr "${QTHARMINI}" "Paths" "Headers" "include"
    writeINIStr "${QTHARMINI}" "Paths" "Libraries" "lib"
    writeINIStr "${QTHARMINI}" "Paths" "Binaries" "bin"
    writeINIStr "${QTHARMINI}" "Paths" "Plugins" "plugins"
    writeINIStr "${QTHARMINI}" "Paths" "Imports" "imports"
    writeINIStr "${QTHARMINI}" "Paths" "Data" "."
    writeINIStr "${QTHARMINI}" "Paths" "Translations" "translations"
    writeINIStr "${QTHARMINI}" "Paths" "Settings" "."
    writeINIStr "${QTHARMINI}" "Paths" "Examples" "examples"
    writeINIStr "${QTHARMINI}" "Paths" "Demos" "demos"
    flushINI "${QTHARMINI}"

    delete "${QTARMPOSTINSTSH}"
    delete "${QTARMPOSTINSTBAT}"
    # Create the worker shell script.
    push $9
    fileOpen $9 '${QTARMPOSTINSTSH}' w
    fileWrite $9 '#!/bin/sh$\n'
    fileWrite $9 '$\n'
    fileWrite $9 'set -x$\n'
    fileWrite $9 '$\n'
    fileWrite $9 'cd "$INSTDIR\${QTH_ARM_DIR}\lib"$\n'
    fileWrite $9 'for f in $$(find . -type f -name \*.prl -print); do$\n'
    fileWrite $9 "    sed -i 's|@@_QT_INSTALL_DIR_@@|$UNIXINSTDIR/${QTH_ARM_DIR}|' $$f$\n"
    fileWrite $9 'done$\n'
    fileWrite $9 '$\n'
    fileWrite $9 'cd "$UNIXINSTDIR/${QTH_ARM_DIR}"$\n'
    fileWrite $9 'if test -d mkspecs/qws/linux-g++-mx; then$\n'
    fileWrite $9 "    sed -i 's|@@_MECT_QTTUNIX_INSTALL_DIR_@@|$EMBUNIX_DIR|g' mkspecs/qws/linux-g++-mx/qmake.conf$\n"
    fileWrite $9 "    sed -i 's|C:|../../..|g' mkspecs/qws/linux-g++-mx/qmake.conf$\n"
    fileWrite $9 'fi$\n'
    fileWrite $9 '$\n'
    fileWrite $9 'if test -f mkspecs/common/mect.conf; then$\n'
    fileWrite $9 "    sed -i 's|@@_MECT_QTTUNIX_INSTALL_DIR_@@|$EMBUNIX_DIR|g' mkspecs/common/mect.conf$\n"
    fileWrite $9 "    sed -i 's|C:|../../..|g' mkspecs/common/mect.conf$\n"
    fileWrite $9 'fi$\n'
    pop $9
    # Create the launcher batch script.
    push $9
    fileOpen $9 '${QTARMPOSTINSTBAT}' w
    fileWrite $9 '@echo off$\r$\n'
    fileWrite $9 'set PATH=$INSTDIR\${MINGW_DIR}\bin;%PATH%$\r$\n'
    fileWrite $9 'set PATH=$INSTDIR\${MINGW_DIR}\msys\1.0\bin;%PATH%$\r$\n'
    fileWrite $9 'set PATH=$INSTDIR\${QTC_DIR}\bin;%PATH%$\r$\n'
    fileWrite $9 'set PATH=$INSTDIR\${QTH_DIR}\bin;%PATH%$\r$\n'
    fileWrite $9 'set PATH=$INSTDIR\${QTH_DIR}\lib;%PATH%$\r$\n'
    fileWrite $9 '@echo on$\r$\n'
    fileWrite $9 '$\r$\n'
    fileWrite $9 'bash "${QTARMPOSTINSTSH}"$\r$\n'
    fileWrite $9 '$\r$\n'
    fileWrite $9 'exit$\r$\n'
    fileClose $9
    pop $9
    # Configure the host Qt.
    execWait "${QTARMPOSTINSTBAT}"
    # Clean up.
    delete "${QTARMPOSTINSTSH}"
    delete "${QTARMPOSTINSTBAT}"

    # Configure the embeddded Qt. [ TODO Is this really needed? ]
    #
    writeINIStr "${QTTINI}" "Paths" "Prefix" "$UNIXINSTDIR/${EMB_DIR}/usr"
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

sectionEnd


# Uninstaller
#

function un.onInit

    setShellVarContext all

    #Verify the uninstaller - last chance to back out
    messageBox MB_OKCANCEL "Do you want to permanantly remove ${APPNAME}?" IDOK next
	abort
next:
    !insertmacro VerifyUserIsAdmin

functionEnd

section "uninstall"

    # Get the actual install path.
    readRegStr $INSTDIR HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${UNINSTKEY}" "InstallLocation"

    # Remove all files.
    #
    delete "$INSTDIR\${ICONNAME}"
    delete "${QTHINI}"
    delete "${QTTINI}"
    delete "$INSTDIR\${MECTSUITEBAT}"
    delete "$INSTDIR\${MECTSUITEVBS}"
    # NOTE Keep in sync with the contents of the installs.
    rmDir /r "$INSTDIR\${QTC_DIR}"
    rmDir /r "$INSTDIR\${EMB_DIR}"
    rmDir /r "$INSTDIR\${QTH_DIR}"
    rmDir /r "$INSTDIR\${QTH_ARM_DIR}"
    rmDir /r "$INSTDIR\${MINGW_DIR}"
    rmDir /r "$INSTDIR\${CAN_DIR}"
    rmDir /r "$INSTDIR\${MECTAPPS_DIR}"
    rmDir /r "$INSTDIR\${QTPROJECT}"
    rmDir /r "$INSTDIR\${QTPROJECT}-default"

    # Clean up the Start Menu.
    #
    delete "$SMPROGRAMS\${COMPANYNAME}\${RUNNAME}.lnk"
    delete "$SMPROGRAMS\${COMPANYNAME}\${UNINSTNAME}.lnk"
    delete "$DESKTOP\${RUNNAME}.lnk"
    rmDir "$SMPROGRAMS\${COMPANYNAME}"

    # Clean up the registry.
    #
    deleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${UNINSTKEY}"
    deleteRegKey HKLM "Software\ATCM"

    # LAST: delete the uninstaller.
    delete "$INSTDIR\${UNINSTNAME}"

    # Uninstall PLC Engineering.
    # [ FIXME: the key has a random component, e.g.,
    # Software\Microsoft\Windows\CurrentVersion\Uninstall\{E5493DB8-035F-11D5-B8FA-002018641833}\UninstallString
    #readRegStr $PLCWINUNINST HKLM "" "UninstallString"

    # Uninstall the target toolchain.
    readRegStr $ARMCCWINUNINST HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Sourcery G++ Lite for ARM GNU/Linux" "UninstallString"
    execWait "$ARMCCWINUNINST"

    # Remove the install directory (if empty).
    rmDir "$INSTDIR"

sectionEnd
