#include <iostream>
#include <Windows.h>
#include "MemMan.h"
#include "Console.h"

MemMan MemClass;
namespace con = JadedHoboConsole;

//offsets, 5 July 2022
struct offsets
{
    DWORD localPlayer = 0xDBF4CC; //dwLocalPlayer
    DWORD flashDuration = 0x10470; //m_flFlashDuration
} offset;

//variables
struct variables
{
    DWORD localPlayer;
    DWORD gameModule;
} val;

int main()
{
    SetConsoleTitleA(""); //Console title
    int flashDur = 0; //Flash Duration
    int procID = MemClass.getProcess("csgo.exe"); //process id
    val.gameModule = MemClass.getModule(procID, "client.dll"); //module
    val.localPlayer = MemClass.readMem<DWORD>(val.gameModule + offset.localPlayer);

    //output
    std::cout << con::fg_white << "[" << con::fg_green << "+" << con::fg_white << "]" << con::fg_magenta << " Gold on my wrist, phone in my pocket\n" << con::fg_white;
    std::cout << "[" << con::fg_green << "+" << con::fg_white << "]" << con::fg_magenta << " Anti-Flash - Activated!\n\n" << con::fg_white;

    std::cout << "[" << con::fg_green << "+" << con::fg_white << "]" << con::fg_magenta << " Build: July 5\n" << con::fg_white;
    std::cout << "[" << con::fg_green << "+" << con::fg_white << "]" << con::fg_magenta << " Made by hj.#0010\n" << con::fg_white;

    //loop
    if (val.localPlayer == NULL)
        while (val.localPlayer == NULL)
            val.localPlayer = MemClass.readMem<DWORD>(val.gameModule + offset.localPlayer);
    //main loop
    while (true)
    {
        flashDur = MemClass.readMem<int>(val.localPlayer + offset.flashDuration);
        if (flashDur > 0)
            MemClass.writeMem<int>(val.localPlayer + offset.flashDuration, 0);
        Sleep(1);
    }
    return 0;
}