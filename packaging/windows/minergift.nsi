#
# Minergift nsis installer script
#

# Include

    # Include modern UI
    !include "MUI2.nsh"


# General 

    # Program version
    !define MINERGIFT_VERSION "0.0.1"

    # VIProductVersion requires version in x.x.x.x format
    !define MINERGIFT_VIPRODUCTVERSION "0.0.1.0"

    # Installer name and filename
    Name "Minergift"
    Caption "Minergift ${MINERGIFT_VERSION} Setup"
    OutFile "minergift-${MINERGIFT_VERSION}.exe"

    # Icon to use for installer
    !define MUI_ICON "minergift.ico"

    # Default installation folder
    InstallDir "$PROGRAMFILES\Minergift"


# Version information

    VIProductVersion "${MINERGIFT_VIPRODUCTVERSION}"
    VIAddVersionKey "ProductName" "Minergift"
    VIAddVersionKey "FileDescription" "Minergift - an open source miner."
    VIAddVersionKey "FileVersion" "${MINERGIFT_VERSION}"
    VIAddVersionKey "LegalCopyright" "GPL v.3"
    VIAddVersionKey "ProductVersion" "${MINERGIFT_VERSION}"


# Settings

    # Show a warn on aborting installation
    !define MUI_ABORTWARNING

    # Defines the target start menu folder
    !define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU"
    !define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\Minergift"
    !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"


# Variables

    Var StartMenuFolder


# Pages

    # Installer pages
    !insertmacro MUI_PAGE_LICENSE "gpl-3.0.txt"
    !insertmacro MUI_PAGE_DIRECTORY
    !insertmacro MUI_PAGE_STARTMENU Application $StartMenuFolder
    !insertmacro MUI_PAGE_INSTFILES

    # Uninstaller pages
    !insertmacro MUI_UNPAGE_CONFIRM
    !insertmacro MUI_UNPAGE_INSTFILES


# Languages

    !insertmacro MUI_LANGUAGE "English"


Section
    SetShellVarContext all

    # Installation path
    SetOutPath "$INSTDIR"

    # Delete any already installed DLLs to avoid buildup of various
    # versions of the same library when upgrading
    Delete "$INSTDIR\*.dll"

    # Files to include in installer
    # now that we install into the staging directory and try to only have
    # the DLLs there that we depend on, this is much easier
    File uiminergift.exe
#    File xmrig.exe
#    File /r theme
#    File /r images
#    File *.dll
#    File minergift.ico
#    File qt.conf
#    File miner.json

    # Store installation folder in registry
    WriteRegStr HKCU "Software\Minergift" "" $INSTDIR

    # Create shortcuts
    !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
        CreateDirectory "$SMPROGRAMS\$StartMenuFolder"
        CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Minergift.lnk" "$INSTDIR\uiminergift.exe" "" "$INSTDIR\minergift.ico" 0
        CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Uninstall Minergift.lnk" "$INSTDIR\Uninstall.exe"
        CreateShortCut "$DESKTOP\Minergift.lnk" "$INSTDIR\uiminergift.exe" "" "$INSTDIR\minergift.ico" 0
    !insertmacro MUI_STARTMENU_WRITE_END

    # Create the uninstaller
    WriteUninstaller "$INSTDIR\Uninstall.exe"

    WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Minergift" \
        "DisplayName" "Minergift"
    WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Minergift" \
        "DisplayIcon" "$INSTDIR\minergift.ico"
    WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Minergift" \
        "UninstallString" "$INSTDIR\Uninstall.exe"
    WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Minergift" \
        "DisplayVersion" ${MINERGIFT_VERSION}

SectionEnd


# Uninstaller section

Section "Uninstall"
    SetShellVarContext all

    # Delete installed files
    Delete "$INSTDIR\*.dll"
    Delete "$INSTDIR\uiminergift.exe"
    Delete "$INSTDIR\minergift.ico"
    Delete "$INSTDIR\Uninstall.exe"
   # RMDir /r "$INSTDIR\theme"
   # RMDir /r "$INSTDIR\images"
    RMDir "$INSTDIR"

    # Remove shortcuts
    !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuFolder
    Delete "$SMPROGRAMS\$StartMenuFolder\Minergift.lnk"
    Delete "$SMPROGRAMS\$StartMenuFolder\Uninstall Minergift.lnk"
    RMDir "$SMPROGRAMS\$StartMenuFolder"
    Delete "$DESKTOP\Minergift.lnk"

    # remove the registry entires
    ${If} $Checkbox_Reg_State == 1
        DeleteRegKey HKCU "Software\Minergift"
    ${EndIf}

    # remove the user directory
  #  ${If} $Checkbox_UserDir_State == 1
  #  ${AndIf} $UserDir != ""
  #  ${AndIf} ${FileExists} "$UserDir\*.*"
  #      RMDir /r $UserDir
  #  ${EndIf}

    # remove the uninstaller entry
    DeleteRegKey HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\Minergift"

SectionEnd


