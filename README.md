# Phonix
My first C++ work.

Allows the changing of your default audio output device on Spotify.

Works with the current version (1.0.64.399).

# Installation
Copy dsound.dll to your Spotify.exe's path to override the native System32\dsound.dll calls.

Path ex: %APPDATA%\Spotify\

# Usage
Creates a tray icon on startup of spotify, right click to list the audio drivers and click to select.

![alt text](https://image.prntscr.com/image/AqKz1SvzTmSXBMSs729GIw.png)

# How it works
Spotify.exe does not specify the absolute path to its dependency dsound.dll which is usually located within System32.

By placing the Phonix dsound.dll in the Spotify folder it loads it into memory rather than the actual dsound.dll

The Phonix dll acts as a wrapper redirects all calls to the System32 dsound.dll after changing the output driver addresses. 




Please help me improve the effectiveness of this program.