#include "main.h"

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	MSG msg;
	BOOL bRet;
	HWND hwnd;
	
	if ( RegisterMainWindow( hInstance ) )
	{
		hwnd = CreateMainWindow( "Main Window", hInstance );
		ShowWindow( hwnd, nCmdShow );
	}

	while( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
	{ 
		if (bRet == -1)
		{
			// handle the error and possibly exit
		}
		else
		{
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		}
	}
	
	// Return the exit code to the system.
	
	return msg.wParam;
	
}

BOOL RegisterMainWindow( HINSTANCE hInstance )
{
	WNDCLASSEX wc;
	char szAppName[] = APPNAME;
		
	ZeroMemory( &wc, sizeof(wc) );
	
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hIcon = (HICON)LoadImage( GetModuleHandle(NULL), MAKEINTRESOURCE(ID_MYICON), IMAGE_ICON, 32, 32, 0 );
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
	wc.lpszClassName = szAppName;
	wc.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(ID_MYICON), IMAGE_ICON, 16, 16, 0);
	
	return( RegisterClassEx( &wc ) );
}

HWND CreateMainWindow( char *szTitle, HINSTANCE hInstance )
{
	HWND hwnd;
	char szAppName[] = APPNAME;
	
	hwnd = CreateWindow( szAppName, szTitle,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		360,
		240,
		HWND_DESKTOP,
		NULL,
		hInstance,
		NULL );
	
	return( hwnd );
}

LRESULT CALLBACK WindowProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	printf( "message received %d %d %d\n", uMsg, wParam, (int)lParam );
	
	switch( uMsg )
	{
		case WM_CREATE:
		{
			CenterWindow( hwnd );
			break;
		}			
		case WM_DESTROY:
		{
			PostQuitMessage( 0 );
			break;
		}
		case WM_KEYDOWN:
		{
			if (wParam==VK_ESCAPE)
			{
				DestroyWindow( hwnd );
			}
			break;
		}
		
		default:
		{
			return( DefWindowProc( hwnd, uMsg, wParam, lParam ) );
		}
	}
	
	return( 0 );
}

void CenterWindow( HWND hwnd_self )
{
	RECT rw_self, rc_parent, rw_parent;
	HWND hwnd_parent;
	
	hwnd_parent = GetParent( hwnd_self );
	if (NULL==hwnd_parent) hwnd_parent = GetDesktopWindow();
	GetWindowRect( hwnd_parent, &rw_parent );
	GetClientRect( hwnd_parent, &rc_parent );
	GetWindowRect( hwnd_self, &rw_self) ;
	SetWindowPos( hwnd_self, NULL,
		rw_parent.left + (rc_parent.right + rw_self.left - rw_self.right) / 2,
		rw_parent.top  + (rc_parent.bottom + rw_self.top - rw_self.bottom) / 2,
		0, 0,
		SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE
		);
}