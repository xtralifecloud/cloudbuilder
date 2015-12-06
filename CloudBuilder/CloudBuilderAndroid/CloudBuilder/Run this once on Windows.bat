@echo Run this in your NDK installation directory (for instance C:\android-ndk-r9)
@echo You should have Cygwin/MinGW tools as well as the NDK installation directory in your PATH
@pause
@echo #include ^<stdlib.h^> > __ndk-build.c
@echo void main() { system("ndk-build.cmd"); } >> __ndk-build.c
gcc __ndk-build.c -o ndk-build.exe
del __ndk-build.c
if exist ndk-build mv ndk-build ndk-build-unix
@pause
