#include<Windows.h>
#include"resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//#define MSG_BOX

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
#ifdef MSG_BOX
	MessageBox(
		NULL,
		"Привет!",
		"Заголовок окна",
		MB_YESNOCANCEL | MB_HELP 
		| MB_ICONASTERISK	
		| MB_DEFBUTTON3		
		| MB_SYSTEMMODAL	
		| MB_SETFOREGROUND
	);
#endif // MSG_BOX

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:	//Создание элементов окна
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), (LPSTR)IDI_ICON1);
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
	}
	break;
	case WM_COMMAND:	//Обработка команд нажатия кнопок
		switch (LOWORD(wParam))
		{
		case IDOK:MessageBox(NULL, "OK", "Info", MB_OK | MB_ICONINFORMATION); 
			break;
		case IDCANCEL:EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:	
		EndDialog(hwnd, 0);
	}
	return FALSE;
}