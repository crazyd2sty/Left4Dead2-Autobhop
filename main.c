#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <TlHelp32.h>
#include <Windows.h>

int main() {
    // 参数固定值
    const DWORD player_base_offset = 0x724B58;
    const DWORD m_flags_offset = 0xF0;

    printf("预置的基址参数:\r\n  PlayerBase offset = %lX\r\n  mFlags offset = %lX\r\n  Windows title = Left 4 Dead 2 - Direct3D 9\r\n  ",
        player_base_offset, m_flags_offset);

    puts("从Steam启动游戏.");


    // 循环获取游戏窗口
    HWND l4d2_hwnd = NULL;
    while ((l4d2_hwnd = FindWindow(NULL, TEXT("Left 4 Dead 2 - Direct3D 9"))) == NULL) {
        Sleep(1000);
    }

    puts("找到窗口，请关闭游戏动画，10秒后注入!");
    Sleep(10000);
    // 获取进程ID
    DWORD l4d2_process_id = 0;
    GetWindowThreadProcessId(l4d2_hwnd, &l4d2_process_id);

    // 打开进程
  HANDLE l4d2_process = OpenProcess(PROCESS_VM_READ, FALSE, l4d2_process_id);
  if (l4d2_process == NULL || l4d2_process_id == 0) {
    error("不能获取到进程ID!");
  }

  // 获取一个句柄，用于在进程中循环遍历已加载的模块。
  HANDLE hSnapshot = CreateToolhelp32Snapshot(
      TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, l4d2_process_id);
  if (hSnapshot == NULL) {
    error("无法创建快照!");
  }

  // 获取client.dll基址
  const DWORD client_base_address = get_client_dll_base_address(hSnapshot);
  CloseHandle(hSnapshot);
  if (client_base_address == 0) {
    error("不能找到client.dll的基址!");
  }

  puts("注入成功!五秒后隐藏进程!");
  // 隐藏控制台
  Sleep(5000);
  HWND console_window = GetConsoleWindow();
  ShowWindow(console_window, SW_HIDE);
  // Bhop 循环
  DWORD player_base_pointer = 0;
  DWORD m_flags = 0;
  while (TRUE) {
      // 检查窗口是否存在
      if (!IsWindow(l4d2_hwnd)) {
          // 退出程序
          ExitProcess(0);
      }

    // 检查空格键是否按下.
    if (GetAsyncKeyState(' ') & 0x8000) {
      // 读取玩家基本指针
      ReadProcessMemory(
          l4d2_process, (char *)client_base_address + player_base_offset,
          &player_base_pointer, sizeof(player_base_pointer), NULL);
      // 从l4d2读取mFlags变量
      ReadProcessMemory(l4d2_process,
                        (char *)player_base_pointer + m_flags_offset, &m_flags,
                        sizeof(m_flags), NULL);

      // autobhop 主程序
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
