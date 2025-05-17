# Installer Script for Bedrock Tools

OutFile "BedrockTools-portable.exe"
SilentInstall silent
RequestExecutionLevel user
SetCompressor lzma

AutoCloseWindow true
ShowInstDetails nevershow
Icon "..\..\src\win\assets\app_icon.ico"
InstallDir "$TEMP\BedrockTools"

Section
  SetOutPath $INSTDIR
  File /r "..\..\build\release\bin\*.*"

  # Cleanup after app exits
  ExecShellWait "open" "$INSTDIR\BedrockTools.exe"
  RMDir /r $INSTDIR
SectionEnd