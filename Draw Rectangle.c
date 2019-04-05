#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

TCHAR szClassName[] = TEXT("Graph3");

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
			TEXT("Neko demo Draw Rectangles"),		//Window Name
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
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;
	
	switch (msg){
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
		
		hPen = CreatePen(PS_SOLID, 0, RGB(255, 0, 0));		//(Style, Width, Color)
		hOldPen = (HPEN)SelectObject(hdc, hPen);
		hBrush = CreateSolidBrush(RGB(0, 255, 0));
		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, 10, 10, 100, 100);
		DeleteObject(hBrush);
		
		hBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(255, 0, 0));
		SelectObject(hdc, hBrush);
		Rectangle(hdc, 50, 50, 150, 150);
		DeleteObject(hBrush);
		
		hBrush = CreateHatchBrush(HS_FDIAGONAL, RGB(0, 0, 255));
		SelectObject(hdc, hBrush);
		Rectangle(hdc, 100, 100, 200, 200);
		DeleteObject(hBrush);
		
		hBrush = CreateHatchBrush(HS_CROSS, RGB(255, 0, 255));
		SelectObject(hdc, hBrush);
		Rectangle(hdc, 150, 150, 250, 250);
		DeleteObject(hBrush);
		
		hBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 255, 0));
		SelectObject(hdc, hBrush);
		Rectangle(hdc, 200, 200, 300, 300);
		DeleteObject(hBrush);
		
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		SelectObject(hdc, hBrush);
		Rectangle(hdc, 250, 250, 350, 350);
		DeleteObject(hPen);
		
		//Return Enviroment
		SelectObject(hdc, hOldPen);
		SelectObject(hdc, hOldBrush);		
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