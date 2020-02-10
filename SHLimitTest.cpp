#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include "CDummyFolder.hpp"

static CDummyFolder *s_pFolder1 = NULL;
static CDummyFolder *s_pFolder2 = NULL;

BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    s_pFolder1 = new CDummyFolder(L"/:*?\"<>|", NULL);
    s_pFolder2 = new CDummyFolder(NULL, L"ABCabc");

    HWND hEdt1 = GetDlgItem(hwnd, edt1);
    HWND hEdt2 = GetDlgItem(hwnd, edt2);

    SHLimitInputEdit(hEdt1, s_pFolder1);
    SHLimitInputEdit(hEdt2, s_pFolder2);
    return TRUE;
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
    case IDOK:
    case IDCANCEL:
        s_pFolder1->Release();
        s_pFolder2->Release();
        EndDialog(hwnd, id);
        break;
    }
}

INT_PTR CALLBACK
DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        HANDLE_MSG(hwnd, WM_INITDIALOG, OnInitDialog);
        HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
    }
    return 0;
}

INT WINAPI
WinMain(HINSTANCE   hInstance,
        HINSTANCE   hPrevInstance,
        LPSTR       lpCmdLine,
        INT         nCmdShow)
{
    InitCommonControls();
    DialogBox(hInstance, MAKEINTRESOURCE(1), NULL, DialogProc);
    return 0;
}
