
#include <windows.h>
#include <time.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

TCHAR szClassName[] = TEXT("Graph1");

//windows prgram entry point
int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, 
				   LPSTR lpsCmdLine, int nCmdShow)
{
	MSG msg;
	BOOL bRet;
	
	if(!InitApp(hCurInst))
		return FALSE;
	if(!InitInstance(hCurInst, nCmdShow))
		return FALSE;
	
	//Get Message
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0){
		if (bRet == -1){
			break;
		}else{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}

//register window class
ATOM InitApp(HINSTANCE hInst)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = (HICON)LoadImage(
	NULL, MAKEINTRESOURCE(IDI_APPLICATION),
	IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wc.hCursor = (HCURSOR)LoadImage(
	NULL, MAKEINTRESOURCE(IDC_ARROW),
	IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wc.hbrBackground = 
		(HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.hIconSm = (HICON)LoadImage(
		NULL, MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	
	return (RegisterClassEx(&wc));
}

//Generage Window
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
	HWND hWnd;
	
	hWnd = CreateWindow(szClassName, //Class Name
			TEXT("Neko demo Draw Lines"),		//Window Name
			WS_OVERLAPPEDWINDOW,	//Window Style
			CW_USEDEFAULT,			//x position
			CW_USEDEFAULT,			//y position
			CW_USEDEFAULT,			//Window Width
			CW_USEDEFAULT,			//Window Height
			NULL,
			NULL,
			hInst,
			NULL
			);
			if (!hWnd)
				return FALSE;
			ShowWindow(hWnd, nCmdShow);
			UpdateWindow(hWnd);
			return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen1, hPen2, hPen3;
	
	switch (msg){
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
		
		hPen1 = CreatePen(
		PS_SOLID, 3, RGB(255, 0, 0));		//(Style, Width, Color)
		SelectObject(hdc, hPen1);
		MoveToEx(hdc, 20, 20, NULL);
		LineTo(hdc, 250, 20);
		
		hPen2 = CreatePen(
		PS_DASH, 0, RGB(0, 0, 255));
		SelectObject(hdc, hPen2);
		MoveToEx(hdc, 20, 40, NULL);
		LineTo(hdc, 250, 40);
		
		hPen3 = CreatePen(
		PS_DOT, 0, RGB(0, 255, 0));
		SelectObject(hdc, hPen3);
		MoveToEx(hdc, 20, 60, NULL);
		LineTo(hdc, 250, 60);
		
		DeleteObject(hPen1);
		DeleteObject(hPen2);
		DeleteObject(hPen3);
		
		EndPaint(hWnd, &ps);
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return (DefWindowProc(hWnd, msg, wp, lp));
	}
	return 0;
}
