gtk3 needs to be installed.

Compiler command:
gcc `pkg-config --cflags gtk+-3.0` -o flash_eol_app flash_eol_app.c `pkg-config --libs gtk+-3.0` -std=c11
