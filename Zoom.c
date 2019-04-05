#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
TCHAR szClassName[] = TEXT("Bitmap1");
HINSTANCE hInst;

//windows prgram entry point
int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, 
				   LPSTR lpsCmdLine, int nCmdShow)
{
	MSG msg;
	BOOL bRet;
	hInst = hCurInst;
	
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
	wc.hIcon = NULL;
	wc.hCursor = (HCURSOR)LoadImage(
	NULL, MAKEINTRESOURCE(IDC_ARROW),
	IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.hIconSm = NULL;
	
	return (RegisterClassEx(&wc));
}

//Generage Window
BOOL InitInstance(HINSTANCE hInst, int nCmdShow)
{
	HWND hWnd;
	
	hWnd = CreateWindow(szClassName, //Class Name
			TEXT("Neko demo BitMap"),		//Window Name
			WS_OVERLAPPEDWINDOW,	//Window Style
			CW_USEDEFAULT,			//x position
			CW_USEDEFAULT,			//y position
			CW_USEDEFAULT,			//Window Width
			CW_USEDEFAULT,			//Window Height
			NULL, NULL,	hInst, NULL);
			if (!hWnd)
				return FALSE;
			ShowWindow(hWnd, nCmdShow);
			UpdateWindow(hWnd);
			return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	HDC hdc, hdc_mem;
	PAINTSTRUCT ps;
	HBITMAP hBmp;
	BITMAP bmp_info;
	int w, h;
	
	switch (msg){
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			//Read Bitmap Resource
			hBmp = LoadBitmap(hInst, TEXT("MYBMP"));
			//Get Bitmap Information
			GetObject(hBmp, (int)sizeof(BITMAP), &bmp_info);
			w = bmp_info.bmWidth;
			h = bmp_info.bmHeight;
			
			//Create MemoryDevice Content
			hdc_mem = CreateCompatibleDC(hdc);
			//Select
			SelectObject(hdc_mem, hBmp);
			BitBlt(hdc, 0, 0, w, h, hdc_mem, 0, 0, SRCCOPY);
			StretchBlt(hdc, w, 0, w * 2, h * 2,
						hdc_mem, 0, 0, w, h, SRCCOPY);
			
			DeleteDC(hdc_mem);
			DeleteObject(hBmp);
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
