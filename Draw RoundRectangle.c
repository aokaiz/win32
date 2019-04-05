#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);

TCHAR szClassName[] = TEXT("Graph4");

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
			TEXT("Neko demo Draw Round Rectangles"),		//Window Name
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
	int iOldMode;
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;
	COLORREF crOldColor;
	RECT rc1 = {30, 30, 210, 50}, rc2 = {30, 50, 210, 110};
	LPCTSTR lpszTxt1 = TEXT("Kafka"),
			lpszTxt2 = TEXT("nekodemo\nProgram");
	
	switch (msg){
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
		
		hPen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));		//(Style, Width, Color)
		hOldPen = (HPEN)SelectObject(hdc, hPen);
		hBrush = CreateSolidBrush(RGB(255, 200, 255));
		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		RoundRect(hdc, 20, 20, 220, 120, 10, 10);		//(x1, y1, x2, y2, RoundWidth, RoundHeight)
		
		//Draw Text
		crOldColor = SetTextColor(hdc, RGB(0, 0, 255));
		DrawText(hdc, lpszTxt1, -1, &rc1, DT_CENTER);
		iOldMode = SetBkMode(hdc, TRANSPARENT);			//Change Background Mode
		DrawText(hdc, lpszTxt2, -1, &rc2, DT_CENTER);
		
		DeleteObject(hPen);
		DeleteObject(hBrush);
		
		SelectObject(hdc, hOldPen);
		SelectObject(hdc, hOldBrush);
		SetTextColor(hdc, crOldColor);
		SetBkMode(hdc, iOldMode);
		
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