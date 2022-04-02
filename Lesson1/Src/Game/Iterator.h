#pragma once

template<class T>
class Iterator 
{
    using ObjectsVector = std::vector<std::shared_ptr<DynamicObject>>;

public:
    Iterator(const ObjectsVector& vec) :
        objects{ vec },
        index{ -1 },
        ptr{ nullptr }
    {
        ++(*this);
    }

    Iterator& operator= (const Iterator& it)
    {
        objects = it.objects;
        index = it.index;
        ptr = it.ptr;

        return *this;
    }

    void reset()
    {
        index = -1;
        ptr = nullptr;
    }

    Iterator& operator ++()
    {
        ++index;

        if(index == std::numeric_limits<int>::min()) {
            LoggerProxy::Instance().WriteToLog(std::string(__FUNCTION__) + " Out of range index: " + std::to_string(index));
            index--;
            return *this;
        }

        for(; index < objects.size(); ++index) {
            T* bobj = dynamic_cast<T*>(objects[index].get());
            if(bobj != nullptr) {
                DynamicObject* obj = objects[index].get();
                ptr = &obj;
                break;
            }
        }

        if(index == objects.size()) {
            index = -1;
            ptr = nullptr;
        }

        return *this;
    }

    Iterator& operator --()
    {
        --index;

        if(index == -1)
            index = objects.size() - 1;

        for(; index >= 0; --index) {
            T* bobj = dynamic_cast<T*>(objects[index].get());
            if(bobj != nullptr) {
                DynamicObject* obj = objects[index].get();
                ptr = &obj;
                break;
            }
        }

        if(index == -1) {
            ptr = nullptr;
        }

        return *this;
    }

    T* operator*() const
    {
        auto obj = dynamic_cast<T*>(objects.at(index).get());
        if(obj == nullptr) {
            LoggerProxy::Instance().WriteToLog(std::string(__FUNCTION__) + " Unknown object");
        }
        return obj;
    };

    bool operator == (const Iterator& it) const
    {
        return std::tie(index, ptr, objects) == std::tie(it.index, it.ptr, it.objects);
    }

    bool operator != (const Iterator& it) const
    {
        return !(*this == it);
    }

    Iterator begin()
    {
        Iterator it(objects);
        return it;
    }

    Iterator end()
    {
        Iterator it(objects);
        it.reset();
        return it;
    }

private:
    ObjectsVector objects;
    int index;
    DynamicObject** ptr;
};

