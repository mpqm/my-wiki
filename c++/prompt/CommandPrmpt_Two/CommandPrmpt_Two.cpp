/*
    CommandPrmpt_Two.cpp
    ���α׷� ����: ���� ������Ʈ 2��.
*/

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <locale.h>
#include <windows.h> 

#define STR_LEN    256
#define CMD_TOKEN_NUM  10

TCHAR ERROR_CMD[]= _T("'%s'��(��) ������ �� �ִ� ���α׷��� �ƴմϴ�. \n");

int CmdProcessing(void);
TCHAR* StrLower(TCHAR*);

//int tmain(int agrc, TCHAR* argv[])
int _tmain(int agrc, TCHAR* argv[]) 
{
    _tsetlocale(LC_ALL, _T("Korean"));

    DWORD isExit;
    while (1)
    {
        isExit = CmdProcessing();
        if (isExit == TRUE)
        {
            _fputts(_T("���ɾ� ó���� �����մϴ�. \n"), stdout);
            break;
        }
    }

    return 0;
}

TCHAR cmdString[STR_LEN];
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
TCHAR seps[] = _T(" ,\t\n");

int CmdProcessing(void)
{
    _fputts(_T("Best command prompt>> "), stdout);
    //_getts(cmdString);
    _getts_s(cmdString);
    TCHAR* context = NULL;
    //TCHAR* token = _tcstok(cmdString, seps);
    TCHAR* token = _tcstok_s(cmdString, seps, &context);
    
    int tokenNum = 0;
    while (token != NULL)
    {
        //_tcscpy(cmdTokenList[tokenNum++], StrLower(token));
        _tcscpy_s(cmdTokenList[tokenNum++], _countof(cmdTokenList), StrLower(token));
        //token = _tcstok(NULL, seps);
        token = _tcstok_s(NULL, seps, &context);
    }

    if (!_tcscmp(cmdTokenList[0], _T("exit")))
    {
        return TRUE;
    }
    else if (!_tcscmp(cmdTokenList[0], _T("�߰� �Ǵ� ���ɾ� 1")))
    {
    }
    else if (!_tcscmp(cmdTokenList[0], _T("�߰� �Ǵ� ���ɾ� 2")))
    {
    }
    else
    {
        STARTUPINFO si = { 0, };//���μ����� �Ӽ��� �����ϴ¿뵵
        PROCESS_INFORMATION pi;

        si.cb = sizeof(si);//����ü������ũ��
        BOOL isRun = CreateProcess(NULL, cmdTokenList[0], NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);//�ι�° ���ڿ� ���������� �����Ұ�� ǥ�ذ˻���ο� �����ϴ� �������Ϸ� �����ϰ� ���μ��� ����
        CloseHandle(pi.hThread);  //�߰��Ѻκ�
        CloseHandle(pi.hProcess); //�߰��Ѻκ�
        if (isRun == FALSE)
            _tprintf(ERROR_CMD, cmdTokenList[0]);
    }

    return 0;
}

TCHAR* StrLower(TCHAR* pStr)
{
    TCHAR* ret = pStr;

    while (*pStr)
    {
        if (_istupper(*pStr))
            *pStr = _totlower(*pStr);
        pStr++;
    }

    return ret;
}