#pragma once

class NonCopyable
{
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

class NonMoveable
{
public:
    NonMoveable() = default;
    NonMoveable(NonMoveable&&) = delete;
    NonMoveable& operator=(NonMoveable&&) = delete;
};

template<class T, size_t N>
void ZeroArray(T(&arr)[N])
{
    std::memset(arr, 0, sizeof(T) * N);
}

template<class T>
void ZeroArray(T* arr, size_t count)
{
    assert(arr != nullptr);
    std::memset(arr, 0, sizeof(T) * count);
}

