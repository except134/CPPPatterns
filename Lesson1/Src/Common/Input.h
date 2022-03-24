#pragma once

class InputHandler
{
public:
    InputHandler();
    uint16_t Update();
    uint32_t GetInput(INPUT_RECORD* eventBuffer);
    void Reset() { FlushConsoleInputBuffer(mInputHandle); }

private:
    HANDLE mInputHandle{};
};