#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <TlHelp32.h>
#include <Windows.h>

int main() {
    // �����̶�ֵ
    const DWORD player_base_offset = 0x724B58;
    const DWORD m_flags_offset = 0xF0;

    printf("Ԥ�õĻ�ַ����:\r\n  PlayerBase offset = %lX\r\n  mFlags offset = %lX\r\n  Windows title = Left 4 Dead 2 - Direct3D 9\r\n  ",
        player_base_offset, m_flags_offset);

    puts("��Steam������Ϸ.");


    // ѭ����ȡ��Ϸ����
    HWND l4d2_hwnd = NULL;
    while ((l4d2_hwnd = FindWindow(NULL, TEXT("Left 4 Dead 2 - Direct3D 9"))) == NULL) {
        Sleep(1000);
    }

    puts("�ҵ����ڣ���ر���Ϸ������10���ע��!");
    Sleep(10000);
    // ��ȡ����ID
    DWORD l4d2_process_id = 0;
    GetWindowThreadProcessId(l4d2_hwnd, &l4d2_process_id);

    // �򿪽���
  HANDLE l4d2_process = OpenProcess(PROCESS_VM_READ, FALSE, l4d2_process_id);
  if (l4d2_process == NULL || l4d2_process_id == 0) {
    error("���ܻ�ȡ������ID!");
  }

  // ��ȡһ������������ڽ�����ѭ�������Ѽ��ص�ģ�顣
  HANDLE hSnapshot = CreateToolhelp32Snapshot(
      TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, l4d2_process_id);
  if (hSnapshot == NULL) {
    error("�޷���������!");
  }

  // ��ȡclient.dll��ַ
  const DWORD client_base_address = get_client_dll_base_address(hSnapshot);
  CloseHandle(hSnapshot);
  if (client_base_address == 0) {
    error("�����ҵ�client.dll�Ļ�ַ!");
  }

  puts("ע��ɹ�!��������ؽ���!");
  // ���ؿ���̨
  Sleep(5000);
  HWND console_window = GetConsoleWindow();
  ShowWindow(console_window, SW_HIDE);
  // Bhop ѭ��
  DWORD player_base_pointer = 0;
  DWORD m_flags = 0;
  while (TRUE) {
      // ��鴰���Ƿ����
      if (!IsWindow(l4d2_hwnd)) {
          // �˳�����
          ExitProcess(0);
      }

    // ���ո���Ƿ���.
    if (GetAsyncKeyState(' ') & 0x8000) {
      // ��ȡ��һ���ָ��
      ReadProcessMemory(
          l4d2_process, (char *)client_base_address + player_base_offset,
          &player_base_pointer, sizeof(player_base_pointer), NULL);
      // ��l4d2��ȡmFlags����
      ReadProcessMemory(l4d2_process,
                        (char *)player_base_pointer + m_flags_offset, &m_flags,
                        sizeof(m_flags), NULL);

      // autobhop ������
      if (m_flags != 0x80 && m_flags != 0x82 && m_flags != 0x280 &&
          m_flags != 0x282) {
        SendMessage(l4d2_hwnd, WM_KEYDOWN, ' ', 0x390000);
      } else if (m_flags == 0x80 || m_flags == 0x82 || m_flags == 0x280 ||
                 m_flags == 0x282) {
        SendMessage(l4d2_hwnd, WM_KEYUP, ' ', 0x390000);
      }
    }

    Sleep(0);
  }
}
