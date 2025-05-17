!include MUI2.nsh
# Installer Script for Bedrock Tools

OutFile "BedrockTools-installer.exe"
RequestExecutionLevel user
SetCompressor lzma
Unicode True

Name "Bedrock Tools"
Icon "..\..\src\win\assets\app_icon.ico"
InstallDir "$LOCALAPPDATA\com.xkingdark.bedrocktools"
ShowInstDetails nevershow
ShowUninstDetails nevershow
BrandingText "xKingDark - Bedrock Tools"

!define MUI_ICON "..\..\src\win\assets\app_icon.ico"
!define MUI_UNICON "..\..\src\win\assets\app_icon.ico"

!define MUI_HEADERIMAGE ;No value
!define MUI_HEADERIMAGE_BITMAP "..\..\src\win\assets\app_icon.bmp"
!define MUI_HEADERIMAGE_BITMAP_STRETCH AspectFitHeight

!define MUI_INSTFILESPAGE_FINISHHEADER_TEXT "Bedrock Tools!"

!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_LANGUAGE "English"

!define UNINSTALL_REG_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\com.xkingdark.bedrocktools"
Section "Install"
    SetOutPath $INSTDIR
    File /r "..\..\build\release\bin\*.*"
  
    WriteUninstaller "$INSTDIR\Uninstall.exe"

    CreateShortcut "$DESKTOP\Bedrock Tools.lnk" "$INSTDIR\BedrockTools.exe"
    
    ; Create Start Menu shortcut
    CreateShortcut "$SMPROGRAMS\Bedrock Tools.lnk" "$INSTDIR\BedrockTools.exe"
  
    ; Registry entry for Control Panel
    WriteRegStr HKCU "${UNINSTALL_REG_KEY}" "DisplayIcon" "$INSTDIR\BedrockTools.exe"
    WriteRegStr HKCU "${UNINSTALL_REG_KEY}" "DisplayName" "Bedrock Tools"
    WriteRegStr HKCU "${UNINSTALL_REG_KEY}" "DisplayVersion" "1.0.0"
    WriteRegStr HKCU "${UNINSTALL_REG_KEY}" "Publisher" "xKingDark"
    WriteRegStr HKCU "${UNINSTALL_REG_KEY}" "InstallLocation" "$INSTDIR"
    WriteRegStr HKCU "${UNINSTALL_REG_KEY}" "UninstallString" "$INSTDIR\Uninstall.exe"
    WriteRegDWORD HKCU "${UNINSTALL_REG_KEY}" "NoModify" 1
    WriteRegDWORD HKCU "${UNINSTALL_REG_KEY}" "NoRepair" 1
SectionEnd

Section "Uninstall"
    Delete "$INSTDIR\*.*"
    RMDir /r "$INSTDIR"

    Delete "$DESKTOP\Bedrock Tools.lnk"
    Delete "$SMPROGRAMS\Bedrock Tools.lnk"

    DeleteRegKey HKCU "${UNINSTALL_REG_KEY}"
SectionEnd