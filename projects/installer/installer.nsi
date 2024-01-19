# FIXME REMOVE!
SetCompress off

# Definitions
#

!define COMPANYNAME     "MECT"
!define ICONNAME        "mect.ico"
!define DESCRIPTION     "Development suite for MECT TPAC devices"

!define VERSION         "${VERSIONMAJOR}.${VERSIONMINOR}.${VERSIONBUILD}"
!define UNINSTKEYPRE    "${COMPANYNAME} ${APPNAME} v"
!define UNINSTKEY       "${UNINSTKEYPRE}${VERSION}"

!define MECTSUITEBAT    "${APPNAME}-${VERSION}-run.bat"         # SYNC WITH $OLD_MECTSUITEBAT
!define MECTSUITEVBS    "${APPNAME}-${VERSION}-exec.vbs"        # SYNC WITH $OLD_MECTSUITEVBS
!define MECTSUITEMAIN   "qtcreator.exe"

!define HELPURL         "http://www.mect.it/"
!define UPDATEURL       "http://www.mect.it/"
!define ABOUTURL        "http://www.mect.it/"
!define RUNNAME         "${APPNAME}-v${VERSION}"
!define UNINSTNAME      "${APPNAME}-v${VERSION}-uninstall.exe"  # SYNC WITH $OLD_UNINSTNAME
!define MECTAPPSBALL    "MectApps.zip"
!define CANARCH         "ATCM.zip"
!define CAN_DIR         "ATCM"
!define PLCARCH         "PLC.zip"
!define ROAMINGAPPDATA  "%USERPROFILE%\AppData\Roaming"
!define ROAMINGAPPDATAD "$PROFILE\AppData\Roaming"

#Var PLCWINUNINST       # PLC Engineering uninstaller
Var PLCWINBINPATH       # PLC Engineering binary path
Var PLCWINBIN           # Full path PLC Engineering executable
Var PLCINSTDIR          # PLC Engineering install path
Var PLCUNINSTID1        # PLC Engineering uninstaller ID main
Var PLCUNINSTID2        # PLC Engineering uninstaller ID ATHW119...

# Existing install data
Var DO_UPDATE           # We update an older version.
Var OLD_UNINSTKEY       # Uninstall key for the old version
Var OLD_VERSION         # Old version number
Var OLD_RUNNAME         # Old version program name
Var OLD_UNINSTPROG      # Old version uninstaller
Var OLD_UNINSTNAME      # Old version uninstaller name
Var OLD_MECTSUITEBAT    # Old version script name
Var OLD_MECTSUITEVBS    # Old version script name

# Need to write shared locations in file system and registry.
RequestExecutionLevel admin
 
# Installation directory
#InstallDir "C:\${COMPANYNAME}\${APPNAME}-v${VERSION}"
InstallDir              "C:\Qt487"      # FIXME: FORCED

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
Page directory "DirectoryEnter" "" "DirectoryLeave"
# Installation progress
Page instfiles

#
# Utilities
#

!macro VerifyUserIsAdmin
UserInfo::GetAccountType
pop $0
${If} $0 != "admin"             # Require admin rights on NT4+
    messageBox mb_iconstop "Administrator rights are required to continue."

    setErrorLevel 740           # ERROR_ELEVATION_REQUIRED

    quit
${EndIf}
!macroend

# Get the last part of a string after a specified
# character. Useful to get file extensions, last file name or
# last directory part.
#
# Usage
# 
# Push "C:\program files\geoffrey\files"
# Push "\"
# Call GetAfterChar
# Pop $R0
# 
# $R0 is now "files" Push "." instead of "\" to get a file
# extension or perhaps "/" for URL.
# 
# The return value is empty "" if the input char was not found.
Function GetAfterChar
    Exch $0 ; chop char
    Exch
    Exch $1 ; input string
    Push $2
    Push $3
    StrCpy $2 0
    loop:
        IntOp $2 $2 - 1
        StrCpy $3 $1 1 $2
        StrCmp $3 "" 0 +3
            StrCpy $0 ""
            Goto exit2
        StrCmp $3 $0 exit1
        Goto loop
    exit1:
        IntOp $2 $2 + 1
        StrCpy $0 $1 "" $2
    exit2:
        Pop $3
        Pop $2
        Pop $1
        Exch $0 ; output
FunctionEnd

# Check if there are spaces (" ") in the path.
#
# Usage
#
# Push "C:\program files\geoffrey\files"
# Call CheckForSpaces
# Pop $R0	# Number of spaces
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

# outputs the relative index position from the start or end
# of a string, where a substring is located. (Case insensitive)
#
# Syntax
#
# ${StrLoc} "ResultVar" "String" "SubString" "StartPoint"
# 
# ResultVar
#     Variable where the relative position index of SubString
#     inside String is returned, according to StartPoint. This
#     value is always smaller or equal than String's length. If
#     SubString is not found, an empty value is returned.
# 
# String
#     String where to search for SubString.
# 
# SubString
#     String to search in String.
# 
# StartPoint(>|<)
#     Start position where the search begins and the counter
#     starts. > = String's start, < = String's end. Default
#     is >.
#
!define StrLoc "!insertmacro StrLoc"
!macro StrLoc ResultVar String SubString StartPoint
    Push "${String}"
    Push "${SubString}"
    Push "${StartPoint}"
    Call StrLoc
    Pop "${ResultVar}"
!macroend
Function StrLoc
/* After this point:
   ------------------------------------------
   $R0 = StartPoint (input)
   $R1 = SubString (input)
   $R2 = String (input)
   $R3 = SubStringLen (temp)
   $R4 = StrLen (temp)
   $R5 = StartCharPos (temp)
   $R6 = TempStr (temp)
*/
 
    ;Get input from user
    Exch $R0
    Exch
    Exch $R1
    Exch 2
    Exch $R2
    Push $R3
    Push $R4
    Push $R5
    Push $R6
 
    ;Get "String" and "SubString" length
    StrLen $R3 $R1
    StrLen $R4 $R2
    ;Start "StartCharPos" counter
    StrCpy $R5 0
 
    ;Loop until "SubString" is found or "String" reaches its end
    ${Do}
        ;Remove everything before and after the searched part ("TempStr")
        StrCpy $R6 $R2 $R3 $R5
 
        ;Compare "TempStr" with "SubString"
        ${If} $R6 == $R1
            ${If} $R0 == `<`
                IntOp $R6 $R3 + $R5
                IntOp $R0 $R4 - $R6
            ${Else}
                StrCpy $R0 $R5
            ${EndIf}
            ${ExitDo}
        ${EndIf}
        ;If not "SubString", this could be "String"'s end
        ${If} $R5 >= $R4
            StrCpy $R0 ``
            ${ExitDo}
        ${EndIf}
        ;If not, continue the loop
        IntOp $R5 $R5 + 1
    ${Loop}
 
    ;Return output to user
    Pop $R6
    Pop $R5
    Pop $R4
    Pop $R3
    Pop $R2
    Exch
    Pop $R1
    Exch $R0
FunctionEnd

# Customize the behavior of the default NSIS diretory page.
Function DirectoryEnter
    Var /GLOBAL OLD_KEY_POS

    ClearErrors
    strCpy $0 0
    reg_search_loop_next_key:
        enumRegKey $OLD_UNINSTKEY HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall" $0
        # If no (more) keys, we will install anew.
        strCmp $OLD_UNINSTKEY "" reg_search_loop_install

        # If we find a key with our prefix, then we update.
        ${strLoc} $OLD_KEY_POS $OLD_UNINSTKEY "${UNINSTKEYPRE}" ">"
        ${If} $OLD_KEY_POS == "0"
            readRegStr $OLD_VERSION HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$OLD_UNINSTKEY" "DisplayVersion"

            ${If} $OLD_VERSION == ${VERSION}
                messageBox MB_OK|MB_ICONEXCLAMATION \
                    'Version ${VERSION} already installed.$\n$\n\
                    Nothing to do.'

                    quit
            ${EndIf}

            readRegStr $INSTDIR HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$OLD_UNINSTKEY" "InstallLocation"

            strCpy $OLD_RUNNAME "${APPNAME}-v$OLD_VERSION"              # SYNC WITH ${UNINSTNAME}

            readRegStr $OLD_UNINSTPROG HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$OLD_UNINSTKEY" "UninstallString"
            push $OLD_UNINSTPROG
            push "\"
            call GetAfterChar
            pop $OLD_UNINSTNAME

            strCpy $OLD_MECTSUITEBAT "${APPNAME}-$OLD_VERSION-run.bat"  # SYNC WITH ${MECTSUITEBAT}

            strCpy $OLD_MECTSUITEVBS "${APPNAME}-$OLD_VERSION-exec.vbs" # SYNC WITH ${MECTSUITEVBS}

            strCpy $DO_UPDATE "1"

            messageBox MB_YESNO|MB_ICONEXCLAMATION \
                'Will upgrade the software$\nfrom v$OLD_VERSION to v${VERSION}.$\n$\n\
                Continue?' IDYES ok_to_update
                quit
            ok_to_update:

            ${If} ${FileExists} '${ROAMINGAPPDATAD}\${QTPROJECT}\*'
                messageBox MB_YESNO|MB_ICONEXCLAMATION \
                    'The upgrade will delete the configuration data in:$\n$\n${ROAMINGAPPDATAD}\${QTPROJECT}$\n$\n$\n\
                    Continue?' IDYES ok_to_remove_qtc_configuration
                    quit
                ok_to_remove_qtc_configuration:
            ${EndIf}

            abort
        ${EndIf}

        intOp $0 $0 + 1
        Goto reg_search_loop_next_key

    reg_search_loop_install:
    strCpy $DO_UPDATE "0"
FunctionEnd

# Checks the user input on the default NSIS diretory page.
Function DirectoryLeave
    # FIXME Other installation paths should be supported as well.
    ${If} $INSTDIR != "C:\Qt487"
        messageBox MB_OK|MB_ICONEXCLAMATION \
            'Error: Only the installation in C:\Qt487 is supported.$\n\
            $\n\
            Please select C:\Qt487 for the installation path and retry.'
        Abort
    ${EndIf}
 
    # Call the CheckForSpaces function.
    Push $INSTDIR
        Call CheckForSpaces
    Pop $R0

    # Forbidden characters in $INSTDIR?
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
            'Will delete the installation directory:$\n$\n$INSTDIR$\n$\n$\n\
            Continue?' IDYES yep
            Abort
        yep:
    ${EndIf}
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

    rmDir /r '$INSTDIR'

    setOutPath $INSTDIR

    # Install the icon(s).
    #
    file ${ICONNAME}

    # Install utilities
    #
    # unzip
    file '/oname=$TEMP\unzip.exe' unzip.exe

    # 7zip
    file '/oname=$TEMP\7zG.exe' 7zG.exe
    file '/oname=$TEMP\7z.dll' 7z.dll

    # Skip these if we just update.
    #
    ${If} $DO_UPDATE != "1"
        ##########################################
        ###                                    ###
        ### Run only for setup, NOT for update ###
        ###                                    ###
        ##########################################

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
        readRegStr $PLCWINBIN HKLM "Software\Softing\Products\61" "VersionFile"

        # Fix PLC Engineering installation.
        writeRegStr HKLM "Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers" "$PLCWINBIN" "WIN7RTM RUNASADMIN"
        delete '$PLCWINBINPATH\ATHW119\${PLC_ATHW}'
        file '/oname=$PLCWINBINPATH\ATHW119\${PLC_ATHW}' ${PLC_ATHW}
        file '/oname=$PLCWINBINPATH\..\Lib\${PLC_ATCM_COMMON}' ${PLC_ATCM_COMMON}
        delete '$PLCWINBINPATH\..\Lib\ATCM_CANopen.4cl'
        delete '$PLCWINBINPATH\..\Lib\ATCM_ProfibusDP.4cl'
        delete '$PLCWINBINPATH\..\Lib\ATCM_SerialComm.4cl'
        delete '$PLCWINBINPATH\..\Lib\ATCM_Socket.4cl'
        delete '$PLCWINBINPATH\..\Lib\ATCM_Utility2.4cl'
        delete '$PLCWINBINPATH\..\Lib\ATCM_XMLfile.4cl'
        delete '$PLCWINBINPATH\..\Lib\Datalogger.4cl'
        delete '$PLCWINBINPATH\..\Lib\HW119.4cl'
        delete '$PLCWINBINPATH\..\Lib\MBRTU.4cl'
        delete '$PLCWINBINPATH\..\Lib\MECT.4cl'
        delete '$PLCWINBINPATH\..\Lib\MectUserUtility.4cl'
        delete '$PLCWINBINPATH\..\Lib\Modbus.4cl'
        delete '$PLCWINBINPATH\..\Lib\SDOCAN.4cl'
        delete '$PLCWINBINPATH\..\Lib\USBManager.4cl'

        # PLC Engineering help files
        file '/oname=$TEMP\${PLCHELP_ARC}' '${PLCHELP_ARC}'
        delete "$PLCWINBINPATH\..\Help\*.*"
        ClearErrors
        execWait '"$TEMP\unzip.exe" -j -o -d "C:/ATCMControl/Engineering/Help" "$TEMP\${PLCHELP_ARC}"'
        ifErrors 0 PLCHELPnoError
            messageBox MB_OK|MB_ICONEXCLAMATION 'Error extracting$\n$TEMP\${PLCHELP_ARC}$\n$\nPress OK to abort the installation.'
            quit
        PLCHELPnoError:
        delete '$TEMP\${PLCHELP_ARC}'

        # Install Active Perl.
        #
        file '/oname=$TEMP\${PERL_INST}' '${PERL_INST}'
        ClearErrors
        execWait '"msiexec" /i "$TEMP\${PERL_INST}"'
        ifErrors 0 PERLnoError
            messageBox MB_OK|MB_ICONEXCLAMATION 'Error installing Perl.$\n$\nPress OK to abort the installation.'
            quit
        PERLnoError:
        rmDir /r '$TEMP\${PERL_INST}'
    ${Else}
        readRegStr $PLCWINBIN HKLM "Software\Softing\Products\61" "VersionFile"
    ${EndIf}

    #################################################
    ###                                           ###
    ### Common installs for BOTH setup and update ###
    ###                                           ###
    #################################################

    # Install the target compilation toolchain.
    #
    file '/oname=$TEMP\${CSXC_ARC}' '${CSXC_ARC}'
    ClearErrors
    execWait '"$TEMP\7zG.exe" x -y "$TEMP\${CSXC_ARC}"'
    ifErrors 0 INSTCSXCnoError
        messageBox MB_OK|MB_ICONEXCLAMATION 'Error extracting$\n$TEMP\${CSXC_ARC}$\n$\nPress OK to abort the installation.'
        quit
    INSTCSXCnoError:
    delete '$TEMP\${CSXC_ARC}'

    # Install CAN configurator
    #
    file '/oname=$TEMP\${CANARCH}' '${CANARCH}'
    ClearErrors
    execWait '"$TEMP\unzip.exe" -o "$TEMP\${CANARCH}"'
    ifErrors 0 CANnoError
        messageBox MB_OK|MB_ICONEXCLAMATION 'Error extracting$\n$TEMP\${CANARCH}$\n$\nPress OK to abort the installation.'
        quit
    CANnoError:
    delete '$TEMP\${CANARCH}'

    # Install MECT apps
    #
    file '${MECTAPPSBALL}'

    # Install bulk base: Qt host, Qt Creator, root FS target, qmake target, etc.
    #
    file '/oname=$TEMP\${BULK_ARC_BASE}' '${BULK_ARC_BASE}'
    ClearErrors
    execWait '"$TEMP\7zG.exe" x -y "$TEMP\${BULK_ARC_BASE}"'
    ifErrors 0 INSTBASEnoError
        messageBox MB_OK|MB_ICONEXCLAMATION 'Error extracting$\n$TEMP\${BULK_ARC_BASE}$\n$\nPress OK to abort the installation.'
        quit
    INSTBASEnoError:
    delete '$TEMP\${BULK_ARC_BASE}'

    # Install bulk update: Qt host, Qt Creator, root FS target, qmake target, etc.
    #
    file '/oname=$TEMP\${BULK_ARC_UPDATE}' '${BULK_ARC_UPDATE}'
    ClearErrors
    execWait '"$TEMP\7zG.exe" x -y "$TEMP\${BULK_ARC_UPDATE}"'
    ifErrors 0 INSTUPDATEnoError
        messageBox MB_OK|MB_ICONEXCLAMATION 'Error extracting$\n$TEMP\${BULK_ARC_UPDATE}$\n$\nPress OK to abort the installation.'
        quit
    INSTUPDATEnoError:
    delete '$TEMP\${BULK_ARC_UPDATE}'

    # Patch Qt x86 installation.
    #
    setOutPath $INSTDIR\${QTH_DIR}
# NOTE Apparently qtbinpatcher exits with error if it has nothing to do.
###     ClearErrors
    execWait 'qtbinpatcher.exe --nobackup --verbose'
###     ifErrors 0 QTHSETnoError
###     messageBox MB_OK|MB_ICONEXCLAMATION 'Qt x86 configuration error.$\n$\nPress OK to abort the installation.'
###     quit
### QTHSETnoError:
    setOutPath $INSTDIR

    # Patch Qt ARM installation.
    #
    setOutPath $INSTDIR\${QTH_ARM_DIR}
# NOTE Apparently qtbinpatcher exits with error if it has nothing to do.
###     ClearErrors
    execWait '..\qtbinpatcher.exe --nobackup'
###     ifErrors 0 QTTSETnoError
###     messageBox MB_OK|MB_ICONEXCLAMATION 'Qt ARM configuration error.$\n$\nPress OK to abort the installation.'
###     quit
### QTTSETnoError:
    setOutPath $INSTDIR

    # Qt Creator default setup
    #
    file '/oname=$TEMP\${QTPROJECT}.7z' '${QTPROJECT}.7z'
    ClearErrors
    execWait '"$TEMP\7zG.exe" x -y "$TEMP\${QTPROJECT}.7z"'
    ifErrors 0 QTPnoError
        messageBox MB_OK|MB_ICONEXCLAMATION 'Error extracting$\n$TEMP\${QTPROJECT}.7z$\n$\nPress OK to abort the installation.'
        quit
    QTPnoError:
    delete '$TEMP\${QTPROJECT}.7z'

    # Install the additional fonts.
    #
    file '/oname=$TEMP\${FONTS_ARC}' ${FONTS_ARC}
    rmDir /r '$TEMP\Fonts'
    ClearErrors
    execWait '"$TEMP\7zG.exe" x -y -o"$TEMP" "$TEMP\${FONTS_ARC}"'
    ifErrors 0 FONTEXnoError
        messageBox MB_OK|MB_ICONEXCLAMATION 'Cannot install the fonts.$\n$\nPress OK to continue.'
    FONTEXnoError:
    delete '$TEMP\${FONTS_ARC}'
    ClearErrors
    execWait '"$SYSDIR\CScript.exe" $TEMP\Fonts\install.vbs $TEMP\ //e:vbscript //B //NOLOGO'
    ifErrors 0 FONTINnoError
        messageBox MB_OK|MB_ICONEXCLAMATION 'Cannot install the fonts.$\n$\nPress OK to continue.'
    FONTINnoError:
    rmDir /r '$TEMP\Fonts'

    # Remove old or empty Qt Creator configuration.
    #
    ${If} $DO_UPDATE == "1"
	rmDir /r "${ROAMINGAPPDATAD}\${QTPROJECT}"
    ${Else}
	rmDir "${ROAMINGAPPDATAD}\${QTPROJECT}"
    ${EndIf}

    # Cleanup
    #
    delete '$TEMP\unzip.exe'
    delete '$TEMP\7zG.exe'
    delete '$TEMP\7z.dll'

    #
    # Post-install setup
    #

    # Set up the Start menu and the Desktop.
    #
    ${If} $DO_UPDATE == "1"
        rmDir /r "$SMPROGRAMS\${COMPANYNAME}"

        delete "$DESKTOP\$OLD_RUNNAME.lnk"
	sleep 5000              # Allow Windows to update the desktop.

        delete "$OLD_UNINSTNAME"
    ${EndIf}

    createDirectory "$SMPROGRAMS\${COMPANYNAME}"
    createShortCut "$SMPROGRAMS\${COMPANYNAME}\${RUNNAME}.lnk" "$INSTDIR\${MECTSUITEVBS}" "" "$INSTDIR\${ICONNAME}"
    createShortCut "$SMPROGRAMS\${COMPANYNAME}\${UNINSTNAME}.lnk" "$INSTDIR\${UNINSTNAME}" "" "$INSTDIR\${ICONNAME}"
    createShortCut "$DESKTOP\${RUNNAME}.lnk" "$INSTDIR\${MECTSUITEVBS}" "" "$INSTDIR\${ICONNAME}"

    # Set up the registry.
    #
    ${If} $DO_UPDATE == "1"
        deleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$OLD_UNINSTKEY"
    ${EndIf}
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

    ${If} $DO_UPDATE != "1"
        writeRegStr HKLM "Software\ATCM" "CAN" "$\"$INSTDIR\ATCM\CANOpen\$\""
        writeRegStr HKLM "Software\ATCM" "EDS" "$\"$INSTDIR\ATCM\CANOpen\eds\$\""
        writeRegStr HKLM "Software\ATCM" "TEMPLATE" "$\"$INSTDIR$\""
        writeRegStr HKLM "Software\ATCM" "IPADDR" "$\"192.168.0.210$\""
        writeRegStr HKLM "Software\ATCM" "NETMASK" "$\"255.255.255.0$\""
        writeRegStr HKLM "Software\ATCM" "user" "$\"root$\""
        writeRegStr HKLM "Software\ATCM" "pwd" "$\"root$\""
        writeRegDWORD HKLM "Software\ATCM" "LANG" 1
    ${EndIf}

    #
    # Script to set up the MECT Suite at first run.
    #

    ${If} $DO_UPDATE == "1"
        delete "$INSTDIR\$OLD_MECTSUITEBAT"
        delete "$INSTDIR\$OLD_MECTSUITEVBS"
    ${EndIf}

    # The actual launcher script
    push $9
    fileOpen $9 "$INSTDIR\${MECTSUITEBAT}" w
    fileWrite $9 "@echo off$\r$\n"
    fileWrite $9 "$\r$\n"
    fileWrite $9 'If Not Exist "$INSTDIR\${QTPROJECT}" GoTo setup_done$\r$\n'
    fileWrite $9 '    rmdir "${ROAMINGAPPDATA}\${QTPROJECT}" /q$\r$\n'
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
    fileClose $9
    pop $9


    #
    # Create the uninstaller (see the function un.onInit and the section "uninstall").
    #

    ${If} $DO_UPDATE == "1"
        delete "$INSTDIR\$OLD_UNINSTNAME"
    ${EndIf}

    writeUninstaller "$INSTDIR\${UNINSTNAME}"


    #
    # Post-install configuration
    #

    # Set up the path.
    #
    #nsExec::ExecToLog 'echo "%PATH%"|findstr /i /c:"C:\Qt487\desktop\mingw32\bin">nul || C:\Qt487\desktop\bin\pathman /au "C:\Qt487\desktop\mingw32\bin"'
    execWait '"$INSTDIR\desktop\bin\pathman" /au "$INSTDIR\desktop\mingw32\bin"'
    execWait '"$INSTDIR\desktop\bin\pathman" /au "$INSTDIR\${CSXC_DIR}\bin"'

sectionEnd


# Uninstaller
#

function un.onInit
    setShellVarContext all

    #Verify the uninstaller - last chance to back out
    messageBox MB_OKCANCEL|MB_ICONQUESTION \
	"Do you want to permanantly remove ${APPNAME} v${VERSION}?" IDOK next
        abort
    next:
    !insertmacro VerifyUserIsAdmin
functionEnd

section "uninstall"

    # Get the install paths.
    readRegStr $INSTDIR HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${UNINSTKEY}" "InstallLocation"
    readRegStr $PLCINSTDIR HKLM "Software\Softing\Setup4C" "Path"

    # Uninstall PLC Engineering.
    readRegStr $PLCUNINSTID2 HKLM "Software\Softing\Products\52\Setup\52" "Deinstall"
    execWait 'MsiExec.exe /X$PLCUNINSTID2'
    readRegStr $PLCUNINSTID1 HKLM "Software\Softing\Products\61\Setup\61" "Deinstall"
    execWait 'MsiExec.exe /X$PLCUNINSTID1'

    # Remove all files.
    #
    delete "$INSTDIR\${ICONNAME}"
    delete "$INSTDIR\${MECTSUITEBAT}"
    delete "$INSTDIR\${MECTSUITEVBS}"
    delete "$INSTDIR\${MECTAPPSBALL}"
    rmDir /r "$INSTDIR\${CAN_DIR}"
    rmDir /r "$PLCINSTDIR"
    rmDir /r "$INSTDIR\${QTPROJECT}"
    rmDir /r "$INSTDIR\${QTH_DIR}"
    rmDir /r "$INSTDIR\${QTH_IMX_DIR}"
    rmDir /r "$INSTDIR\${CSXC_DIR}"

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
    deleteRegValue HKLM "Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers" "$PLCWINBIN"

    # LAST: delete the uninstaller.
    delete "$INSTDIR\${UNINSTNAME}"

    # Uninstall PLC Engineering.
    # [ FIXME: Cannot.  The registry key has a random component, e.g.,
    # Software\Microsoft\Windows\CurrentVersion\Uninstall\{E5493DB8-035F-11D5-B8FA-002018641833}\UninstallString
    #readRegStr $PLCWINUNINST HKLM "" "UninstallString"

    # Remove the install directory (if empty).
    rmDir "$INSTDIR"

    # Clean up the path.
    #
    execWait '"$INSTDIR\desktop\bin\pathman" /ru "$INSTDIR\${CSXC_DIR}\bin"'
    execWait '"$INSTDIR\desktop\bin\pathman" /ru "$INSTDIR\desktop\mingw32\bin"'

sectionEnd
