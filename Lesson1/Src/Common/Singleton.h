#pragma once

template<typename T>
class SingletonStatic
{
public:
    static T& Instance()
    {
        static T instance;
        return instance;
    }
};

