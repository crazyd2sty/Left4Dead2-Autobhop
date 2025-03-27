#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

#include <TlHelp32.h>
#include <Windows.h>

int main() {
    // Parameter fixed value
    const DWORD player_base_offset = 0x726BD8;
    const DWORD m_flags_offset = 0xF0;
    printf("Preset base address parameters:\r\n  PlayerBase offset = %lX\r\n  mFlags offset = %lX\r\n  Windows title = Left 4 Dead 2 - Direct3D 9\r\n  ",
        player_base_offset, m_flags_offset);

    puts("Launch the game from Steam.");

  // Keep looping until we find the l4d2 window.
  HWND l4d2_hwnd = NULL;
  while ((l4d2_hwnd = FindWindow(NULL, TEXT("Left 4 Dead 2 - Direct3D 9"))) == NULL) {
    Sleep(1000);
  }

  puts("Game found!");

  // Get the process id from the window.
  DWORD l4d2_process_id = 0;
  GetWindowThreadProcessId(l4d2_hwnd, &l4d2_process_id);

  // Get a handle to the process with virtual memory read permissions.
  HANDLE l4d2_process = OpenProcess(PROCESS_VM_READ, FALSE, l4d2_process_id);
  if (l4d2_process == NULL || l4d2_process_id == 0) {
    error("Could not open process or get process id!");
  }

  // Get a handle for looping through loaded modules in the process.
  HANDLE hSnapshot = CreateToolhelp32Snapshot(
      TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, l4d2_process_id);
  if (hSnapshot == NULL) {
    error("Could not create snapshot!");
  }

  // Get the client.dll base address.
  const DWORD client_base_address = get_client_dll_base_address(hSnapshot);
  CloseHandle(hSnapshot);
  if (client_base_address == 0) {
    error("Could not get client.dll base address!");
  }

  puts("Autobhop is now functional!");

  // Hide the console
  Sleep(5000);
  HWND console_window = GetConsoleWindow();
  ShowWindow(console_window, SW_HIDE);

  // Bhop loop
  DWORD player_base_pointer = 0;
  DWORD m_flags = 0;
  while (TRUE) {
      // Check if the window exists
      if (!IsWindow(l4d2_hwnd)) {
          // Exit the program
          ExitProcess(0);
      }

      // Check if the spacebar is pressed.
      if (GetAsyncKeyState(' ') & 0x8000) {
          // Read the player base pointer
          ReadProcessMemory(
              l4d2_process, (char*)client_base_address + player_base_offset,
              &player_base_pointer, sizeof(player_base_pointer), NULL);
          // Read the mFlags variable from l4d2
          ReadProcessMemory(l4d2_process,
              (char*)player_base_pointer + m_flags_offset, &m_flags,
              sizeof(m_flags), NULL);

          // Autobhop main program
          if (m_flags != 0x80 && m_flags != 0x82 && m_flags != 0x280 &&
              m_flags != 0x282) {
              SendMessage(l4d2_hwnd, WM_KEYDOWN, ' ', 0x390000);
          }
          else if (m_flags == 0x80 || m_flags == 0x82 || m_flags == 0x280 ||
              m_flags == 0x282) {
              SendMessage(l4d2_hwnd, WM_KEYUP, ' ', 0x390000);
          }
      }

      Sleep(0);
  }
}

