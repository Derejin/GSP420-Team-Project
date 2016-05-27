#include "GSPWindow.h"

//created 5/17/2016, 6:00 PM, by Derek Baumgartner
//Definitions for GSPWindow class methods.

//namespace setup
namespace {
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 	{
		if (message == WM_DESTROY) {PostQuitMessage(0); return 0;}
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

//constructor
GSPWindow::GSPWindow(std::wstring title, int width, int height) : WIDTH(width), HEIGHT(height),
className(L"DefaultWindowTitle"){

	//window style - can be modified here
	static const long STYLE = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;

	//window class declaration and definition
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(WNDCLASS));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = className.c_str();
	assert(RegisterClass(&wc) && "Failed to register window class.");

	//handle setup
	int x = CW_USEDEFAULT;
	int y = CW_USEDEFAULT;
	RECT wr = { 0, 0, width, height };
	AdjustWindowRect(&wr, STYLE, FALSE);
	int adjWide = wr.right - wr.left;
	int adjTall = wr.bottom - wr.top;

	//handle definition
	handle = CreateWindow(className.c_str(), title.c_str(), STYLE, x, y, adjWide, adjTall,
		NULL, NULL, wc.hInstance, NULL);
}

//destructor
GSPWindow::~GSPWindow() {
	UnregisterClass(className.c_str(), GetModuleHandle(NULL));
}

//update function, for processing messages
bool GSPWindow::update() {
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT) { return false; }
	}

	return true;
}

//getter function for handle
HWND GSPWindow::getHandle() const{
	return handle;
}