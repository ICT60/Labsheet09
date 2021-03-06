#include "stdafx.h"
#include "labsheet09.h"

HINSTANCE hInst;
BOOL isQuit = false;


INT_PTR CALLBACK    DialogProc(HWND, UINT, WPARAM, LPARAM);

void Initialize(HWND hWnd);
void ShowMessageLength(HWND hWnd);
void UpdateMinusResult(HWND hWnd);
void SwapEditBoxText(HWND hWnd);


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
		Initialize(hDlg);
        return (INT_PTR)TRUE;

    case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTONRUN:
		{
			ShowMessageLength(hDlg);
			UpdateMinusResult(hDlg);
			break;
		}

		case IDC_BUTTONSWAP:
		{
			SwapEditBoxText(hDlg);
			UpdateMinusResult(hDlg);
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

void Initialize(HWND hWnd)
{
	SetDlgItemInt(hWnd, IDC_NUM1, 0, false);
	SetDlgItemInt(hWnd, IDC_NUM2, 0, false);
	SetDlgItemText(hWnd, IDC_LABELRESULT, _T("0"));
}

void ShowMessageLength(HWND hWnd)
{
	LRESULT length = SendDlgItemMessage(
		hWnd,
		IDC_INPUTMESSAGE,
		EM_LINELENGTH,
		0,
		0
	);

	CString message;
	message.Format(_T("Total input text length : %d"), length);

	MessageBox(
		hWnd,
		message, 
		_T("Result"),
		MB_OK | MB_DEFBUTTON1 | MB_ICONINFORMATION | MB_SYSTEMMODAL
	);
}

void UpdateMinusResult(HWND hWnd)
{
	int num1 = 0;
	int num2 = 0;

	BOOL isNum1Success;
	BOOL isNum2Success;

	num1 = GetDlgItemInt(hWnd, IDC_NUM1, &isNum1Success, FALSE);
	num2 = GetDlgItemInt(hWnd, IDC_NUM2, &isNum2Success, FALSE);

	if (isNum1Success && isNum2Success) {
		int result = num1 - num2;

		CString resultText;
		resultText.Format(_T("%d"), result);

		SetDlgItemText(hWnd, IDC_LABELRESULT, resultText);
	}
}

void SwapEditBoxText(HWND hWnd)
{
	int num1 = 0;
	int num2 = 0;

	BOOL isNum1Success;
	BOOL isNum2Success;

	num1 = GetDlgItemInt(hWnd, IDC_NUM1, &isNum1Success, FALSE);
	num2 = GetDlgItemInt(hWnd, IDC_NUM2, &isNum2Success, FALSE);

	if (isNum1Success && isNum2Success) {
		SetDlgItemInt(hWnd, IDC_NUM1, num2, false);
		SetDlgItemInt(hWnd, IDC_NUM2, num1, false);
	}
}
