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
!define MECTAPPSBALL	"MectApps.zip"
!define CANARCH		"ATCM.zip"
!define CAN_DIR		"ATCM"
!define PLCARCH		"PLC.zip"
!define ROAMINGAPPDATA  "$LOCALAPPDATA\..\Roaming"

#Var PLCWINUNINST	# PLC Engineering uninstaller
Var PLCWINBINPATH	# PLC Engineering binary path
Var ARMCCWININSTPATH	# Target toolchain installation path
Var ARMCCWINUNINST	# Target toolchain uninstaller

# Need to write shared locations in file system and registry.
RequestExecutionLevel admin
 
# Installation directory
#InstallDir "C:\${COMPANYNAME}\${APPNAME}-v${VERSION}"
InstallDir              "C:\Qt485"      # FIXME: FORCED

# NOTE: always in DOS format
LicenseData "license.txt"

Name "${COMPANYNAME} - ${APPNAME}"
Icon "${ICONNAME}"
OutFile "${INSTALLPRG}"

!include LogicLib.nsh

# Pages
#

# License agreement
Page license
# Install location
Page directory "" "" "DirectoryLeave"
# Installation progress
Page instfiles

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

    # FIXME Other installation paths should be supported as well.
    ${If} $INSTDIR != "C:\Qt485"
        messageBox MB_OK|MB_ICONEXCLAMATION \
            'Error: Only the installation in C:\Qt485 is supported.$\n\
            $\n\
            Please select C:\Qt485 for the installation path and retry.'
        Abort
    ${EndIf}
 
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

    # 7zip
    file '/oname=$TEMP\7za.exe' 7za.exe

    # CAN
    file '/oname=$TEMP\${CANARCH}' '${CANARCH}'
    ClearErrors
    execWait '"$TEMP\unzip.exe" -o "$TEMP\${CANARCH}"'
    ifErrors 0 CANnoError
	messageBox MB_OK|MB_ICONEXCLAMATION 'Error extracting$\n$TEMP\${CANARCH}$\n$\nPress OK to abort the installation.'
	quit
CANnoError:
    delete '$TEMP\${CANARCH}'

    # MECT apps
    file '${MECTAPPSBALL}'

    # Bulk base: Qt host, Qt Creator, root FS target, qmake target, etc.
    file '/oname=$TEMP\${BULK_ARC_BASE}' '${BULK_ARC_BASE}'
    ClearErrors
    execWait '"$TEMP\7za.exe" x -y "$TEMP\${BULK_ARC_BASE}"'
    ifErrors 0 INSTBASEnoError
	messageBox MB_OK|MB_ICONEXCLAMATION 'Error extracting$\n$TEMP\${BULK_ARC_BASE}$\n$\nPress OK to abort the installation.'
	quit
INSTBASEnoError:
    delete '$TEMP\${BULK_ARC_BASE}'

    # Bulk update: Qt host, Qt Creator, root FS target, qmake target, etc.
    file '/oname=$TEMP\${BULK_ARC_UPDATE}' '${BULK_ARC_UPDATE}'
    ClearErrors
    execWait '"$TEMP\7za.exe" x -y "$TEMP\${BULK_ARC_UPDATE}"'
    ifErrors 0 INSTUPDATEnoError
	messageBox MB_OK|MB_ICONEXCLAMATION 'Error extracting$\n$TEMP\${BULK_ARC_UPDATE}$\n$\nPress OK to abort the installation.'
	quit
INSTUPDATEnoError:
    delete '$TEMP\${BULK_ARC_UPDATE}'

    # Patch Qt x86 installation.
    setOutPath $INSTDIR\${QTH_DIR}
# NOTE Apparently qtbinpatcher exits with error if it has nothing to do.
###     ClearErrors
    execWait 'qtbinpatcher.exe --nobackup --verbose'
###     ifErrors 0 QTHSETnoError
### 	messageBox MB_OK|MB_ICONEXCLAMATION 'Qt x86 configuration error.$\n$\nPress OK to abort the installation.'
### 	quit
### QTHSETnoError:
    setOutPath $INSTDIR

    # Patch Qt ARM installation.
    setOutPath $INSTDIR\${QTH_ARM_DIR}
# NOTE Apparently qtbinpatcher exits with error if it has nothing to do.
###     ClearErrors
    execWait '..\qtbinpatcher.exe --nobackup'
###     ifErrors 0 QTTSETnoError
### 	messageBox MB_OK|MB_ICONEXCLAMATION 'Qt ARM configuration error.$\n$\nPress OK to abort the installation.'
### 	quit
### QTTSETnoError:
    setOutPath $INSTDIR

    # Qt Creator default setup
    file '/oname=$TEMP\${QTPROJECT}.7z' '${QTPROJECT}.7z'
    ClearErrors
    execWait '"$TEMP\7za.exe" x -y "$TEMP\${QTPROJECT}.7z"'
    ifErrors 0 QTPnoError
	messageBox MB_OK|MB_ICONEXCLAMATION 'Error extracting$\n$TEMP\${QTPROJECT}.7z$\n$\nPress OK to abort the installation.'
	quit
QTPnoError:
    delete '$TEMP\${QTPROJECT}.7z'

    # Perl 5.24.0 (MECT repack).
    file '/oname=$TEMP\${PERL_ARC}' '${PERL_ARC}'
    ClearErrors
    execWait '"$TEMP\7za.exe" x -y "$TEMP\${PERL_ARC}"'
    ifErrors 0 PERLnoError
	messageBox MB_OK|MB_ICONEXCLAMATION 'Error extracting$\n$TEMP\${PERL_ARC}$\n$\nPress OK to abort the installation.'
	quit
PERLnoError:
    delete '$TEMP\${PERL_ARC}'

    # FIXME Compress all files within the installer.
    ### file /r install-them-all/*

    #
    # Install PLC Engineering.
    #

    file '/oname=$TEMP\${PLCARCH}' '${PLCARCH}'
    rmDir /r "$TEMP\PLC"
    ClearErrors
    execWait '"$TEMP\unzip.exe" -o "$TEMP\${PLCARCH}" -d "$TEMP"'
    ifErrors 0 PLCEXnoError
	messageBox MB_OK|MB_ICONEXCLAMATION 'Error extracting$\n$TEMP\${PLCARCH}$\n$\nPress OK to abort the installation.'
	quit
PLCEXnoError:
    delete '$TEMP\${PLCARCH}'
    ClearErrors
    execWait '$TEMP\PLC\ATCMcontrol_Engineering_v2.20.02.4018\Setup.exe'
    ifErrors 0 PLCnoError
	messageBox MB_OK|MB_ICONEXCLAMATION 'Error installing PLC Engineering.$\n$\nPress OK to abort the installation.'
	quit
PLCnoError:
    rmDir /r '$TEMP\PLC'

    # Collect the PLC Engineering executable and full path.
    readRegStr $PLCWINBINPATH HKLM "Software\Softing\4ControlV2\2.0" "BinPath"

    # Fix PLC Engineering installation.
    delete '$PLCWINBINPATH\ATHW119\${PLC_ATHW}'
    file '/oname=$PLCWINBINPATH\ATHW119\${PLC_ATHW}' ${PLC_ATHW}

    # PLC Engineering help files
    file '/oname=$TEMP\${PLCHELP_ARC}' '${PLCHELP_ARC}'
    ClearErrors
    # FIXME: use the actual PLC Engineering install path for -d below.
    execWait '"$TEMP\unzip.exe" -j -o -d "C:/ATCMControl/Engineering/Help" "$TEMP\${PLCHELP_ARC}"'
    ifErrors 0 PLCHELPnoError
	messageBox MB_OK|MB_ICONEXCLAMATION 'Error extracting$\n$TEMP\${PLCHELP_ARC}$\n$\nPress OK to abort the installation.'
	quit
PLCHELPnoError:
    delete '$TEMP\${PLCHELP_ARC}'

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
    # Install the additional fonts.
    #

    file '/oname=$TEMP\${FONTS_ARC}' ${FONTS_ARC}
    rmDir /r '$TEMP\Fonts'
    ClearErrors
    execWait '"$TEMP\7za.exe" x -y -o"$TEMP" "$TEMP\${FONTS_ARC}"'
    ifErrors 0 FONTEXnoError
	messageBox MB_OK|MB_ICONEXCLAMATION 'Cannot install the fonts.$\n$\nPress OK to continue.'
FONTEXnoError:
    delete '$TEMP\${FONTS_ARC}'
    ClearErrors
    execWait '"$SYSDIR\CScript.exe" $TEMP\Fonts\install.vbs $TEMP\Fonts //e:vbscript //B //NOLOGO'
    ifErrors 0 FONTINnoError
	messageBox MB_OK|MB_ICONEXCLAMATION 'Cannot install the fonts.$\n$\nPress OK to continue.'
FONTINnoError:
    rmDir /r '$TEMP\Fonts'



    #
    # Cleanup
    #

    delete '$TEMP\unzip.exe'
    delete '$TEMP\7za.exe'

    #
    # Post-install setup
    #

    # Set up the Start menu and the Desktop.
    #
    createDirectory "$SMPROGRAMS\${COMPANYNAME}"
    createShortCut "$SMPROGRAMS\${COMPANYNAME}\${RUNNAME}.lnk" "$INSTDIR\${QTC_DIR}\${MECTSUITEVBS}" "" "$INSTDIR\${ICONNAME}"
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

    # Set up the path.
    #
    #nsExec::ExecToLog 'echo "%PATH%"|findstr /i /c:"C:\Qt485\desktop\mingw32\bin">nul || C:\Qt485\desktop\bin\pathman /au "C:\Qt485\desktop\mingw32\bin"'
    execWait '"$INSTDIR\desktop\bin\pathman" /au "$INSTDIR\desktop\mingw32\bin"'


    #
    # Script to setup the MECT Suite at first run.
    #

    # The actual launcher script
    push $9
    fileOpen $9 "$INSTDIR\${MECTSUITEBAT}" w
    fileWrite $9 "@echo off$\r$\n"
    fileWrite $9 "$\r$\n"
    fileWrite $9 'If Not Exist "$INSTDIR\${QTPROJECT}" GoTo setup_done$\r$\n'
    fileWrite $9 '    If Not Exist "${ROAMINGAPPDATA}\${QTPROJECT}\*" xcopy "$INSTDIR\${QTPROJECT}" "${ROAMINGAPPDATA}\${QTPROJECT}\" /E /Y /B$\r$\n'
    fileWrite $9 ':setup_done$\r$\n'
    fileWrite $9 "$\r$\n"
    fileWrite $9 '"$INSTDIR\${QTC_DIR}\bin\${MECTSUITEMAIN}"$\r$\n'
    fileWrite $9 "$\r$\n"
    fileWrite $9 "exit$\r$\n"
    fileClose $9
    pop $9
    # "Silent" (no cmd window) launcher.
    push $9
    fileOpen $9 "$INSTDIR\${MECTSUITEVBS}" w
    fileWrite $9 'Set WshShell = CreateObject("WScript.Shell")$\r$\n'
    fileWrite $9 'WshShell.Run chr(34) & "$INSTDIR\${MECTSUITEBAT}" & Chr(34), 0$\r$\n'
    fileWrite $9 "$\r$\n"
    fileWrite $9 "Set WshShell = Nothing$\r$\n"
    pop $9


    #
    # Create the uninstaller (see the function un.onInit and the section "uninstall").
    #

    writeUninstaller "$INSTDIR\${UNINSTNAME}"


    #
    # Post-install configuration
    #

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

    # Clean up the path.
    #
    execWait '"$INSTDIR\desktop\bin\pathman" /ru "$INSTDIR\desktop\mingw32\bin"'

    # Remove all files.
    #
    delete "$INSTDIR\${ICONNAME}"
    delete "$INSTDIR\${MECTSUITEBAT}"
    delete "$INSTDIR\${MECTSUITEVBS}"
    delete "$INSTDIR\${MECTAPPSBALL}"
    rmDir /r "$INSTDIR\${CAN_DIR}"
    rmDir /r "$INSTDIR\${QTPROJECT}"
    rmDir /r "$INSTDIR\${QTH_DIR}"
    rmDir /r "$INSTDIR\${QTH_IMX_DIR}"

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
    # [ FIXME: Cannot.  The registry key has a random component, e.g.,
    # Software\Microsoft\Windows\CurrentVersion\Uninstall\{E5493DB8-035F-11D5-B8FA-002018641833}\UninstallString
    #readRegStr $PLCWINUNINST HKLM "" "UninstallString"

    # Uninstall the target toolchain.
    readRegStr $ARMCCWINUNINST HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Sourcery G++ Lite for ARM GNU/Linux" "UninstallString"
    execWait "$ARMCCWINUNINST"

    # Remove the install directory (if empty).
    rmDir "$INSTDIR"

sectionEnd
