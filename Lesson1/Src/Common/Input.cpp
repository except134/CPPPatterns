// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "LessonPCH.h"

InputHandler::InputHandler()
{
    mInputHandle = GetStdHandle(STD_INPUT_HANDLE);
}

uint16_t InputHandler::Update()
{
    INPUT_RECORD eventBuffer[128];
    uint32_t numEventsRead = GetInput(&eventBuffer[0]);

    for(uint32_t i = 0; i < numEventsRead; ++i) {
        switch(eventBuffer[i].EventType) {
            case KEY_EVENT:
            {
                if(!eventBuffer[i].Event.KeyEvent.bKeyDown)
                    return eventBuffer[i].Event.KeyEvent.wVirtualKeyCode;
            }break;
        }
    }
    return 0;
}

uint32_t InputHandler::GetInput(INPUT_RECORD* eventBuffer)
{
    uint32_t numEvents = 0;
    uint32_t numEventsRead = 0;

    GetNumberOfConsoleInputEvents(mInputHandle, (LPDWORD)&numEvents);

    if(numEvents) {
        ReadConsoleInput(mInputHandle, eventBuffer, 128, (LPDWORD)&numEventsRead);
    }

    return numEventsRead;
}
