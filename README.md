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

From root folder run: powershell buildscripts\win-x64\generateProject.ps1

