@echo off

IF "%~1"=="" GOTO default
powershell -ExecutionPolicy ByPass -File downloadDependencies.ps1 -vcpkgDir %1
GOTO end
:default
powershell -ExecutionPolicy ByPass -File downloadDependencies.ps1
:end

