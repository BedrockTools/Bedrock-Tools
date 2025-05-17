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

  Exec "$INSTDIR\BedrockTools.exe"

  # Cleanup after app exits
  ExecWait "$INSTDIR\BedrockTools.exe"
  RMDir /r $INSTDIR
SectionEnd