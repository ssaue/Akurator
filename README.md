# Akurator

Application for controlling sound installations

This will be the new control application replacing the Soundspace project. Important changes are:
* Platform independence 
* Csound for sound playback and processing (through OSC - OpenSoundControl)
* Boost for logging and serialization
* Juce as GUI platform
* Cmake as build tool

## Build instructions

The application has been built for windows only, so there could be issues with other platforms

### Windows

* Install Visual Studio 2022 IDE. Make sure to install the “Desktop development with C++” workload.
* Install CMake (minimum required version 3.21.0). Remember to add CMake to the system PATH (install option).
* From root folder run: powershell buildscripts\win-x64\generateProject.ps1

