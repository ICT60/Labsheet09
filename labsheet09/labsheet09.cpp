#include "stdafx.h"
#include "labsheet09.h"


#define MAX_LOADSTRING 100

HINSTANCE hInst;
INT_PTR CALLBACK    DialogProc(HWND, UINT, WPARAM, LPARAM);

BOOL isQuit = false;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));
	INT_PTR mainDialog = DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAINDIALOG), NULL, DialogProc);

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0) && !isQuit)
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);

    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTONRUN:
		{
			LRESULT length = SendDlgItemMessage(
				hDlg,
				IDC_INPUTMESSAGE,
				EM_LINELENGTH,
				0,
				0
			);

			CString message;
			message.Format(_T("Total input text length : %d"), length);

			MessageBox(
				hDlg,
				message, 
				_T("Result"),
				MB_OK | MB_DEFBUTTON1 | MB_ICONINFORMATION | MB_SYSTEMMODAL
			);

			break;
		}

		case IDC_BUTTONSWAP:
		{

			break;
		}

		case IDCANCEL:
		{
			int dialogResult = MessageBox(
				hDlg,
				_T("Want to quit program?"),
				_T("Quit"),
				MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2 | MB_SYSTEMMODAL
			);

			if (dialogResult == IDYES) {
				EndDialog(hDlg, LOWORD(wParam));
				isQuit = true;
			}
            return (INT_PTR)TRUE;
			break;
		}

		default:
			break;
		}

        break;
    }
    return (INT_PTR)FALSE;
}
