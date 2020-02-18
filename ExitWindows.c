#include "ExitWindows.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int PASCAL WinMain(HANDLE hInstance, HANDLE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    /* parse command line for the following:
     * /s - shutdown Windows
     * /r - restart Windows
     * /b - reboot computer
     */

    long ExitWindowsOption = -1;
    int i;
    char temp;
    for (i = 0; i < 128; i++)
    {
        if (lpCmdLine[i] == '/')
        {
            i++;
            temp = tolower(lpCmdLine[i]);
            if (temp == 's')
            {
                ExitWindowsOption = EW_EXITWINDOWS;
                break;
            }
            if (temp == 'r')
            {
                ExitWindowsOption = EW_RESTARTWINDOWS;
                break;
            }
            if (temp == 'b')
            {
                ExitWindowsOption = EW_REBOOTSYSTEM;
                break;
            }
        }
        if (lpCmdLine[i] == '\0')
            break;
    }

    if (ExitWindowsOption == -1)
    {
        MessageBox(NULL, "Usage:  /s  - Exit Windows\r\n        /r  - Restart Windows\r\n        /b  - Reboot Computer","ExitWindows prog",MB_OK);
        return FALSE;
    }

    if (ExitWindows(ExitWindowsOption, 0) == 0)
    {
        MessageBox(NULL, "One or more programs denied the request.", "ExitWindows prog",MB_OK);
        return FALSE;
    }

    return FALSE;
}
