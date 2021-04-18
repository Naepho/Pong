# How to compile

This tutorial explains how to compile the code on your local computer.

---

## Windows

1. Install MinGw builds 7.3.0 (64-bit), link to download [here](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/7.3.0/threads-posix/seh/x86_64-7.3.0-release-posix-seh-rt_v5-rev0.7z/download) (mingw-w64, scroll down a bit to the MinGW-W64 GCC-7.3.0 section and download x86_64-win32-seh).
2. Download SFML 2.5.1 for GCC 7.3.0 MinGW (SEH) - 64-bit, link [here](https://www.sfml-dev.org/download/sfml/2.5.1/).
3. Create a lib folder at the root of the project and put the content of the archive's lib folder into the new one.
4. Put the content of the archive's include folder into the project's one.
5. Put the content of the archive's bin folder into the project's one.
6. Install GNU make, update your path if needed, reboot.
7. Type make into the terminal.
8. Look into the bin folder !

## Linux

1. Do the step 2 to 5 for Windows.
2. Type make in the terminal.
3. Look into the bin folder !

## MacOs

No idea, I've never worked on a Mac.
