#include <stdio.h>

#include "Windows.h"

#define APPNAME "Base"

#define ID_MYICON 100

BOOL RegisterMainWindow( HINSTANCE hInstance );
HWND CreateMainWindow( char *szTitle, HINSTANCE hInstance );
LRESULT CALLBACK WindowProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
void CenterWindow( HWND hwnd_self );
