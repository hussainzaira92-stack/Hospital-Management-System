#ifndef STORAGE_H
#define STORAGE_H

template <class T>
class Storage 
{
private:
    T data[100];
    int count;
public:

    Storage() 
    {
        count = 0;
    }
    void add(const T& obj) 
    {

        if (count < 100) {
            data[count] = obj;
            count++;
        }
    }
    bool removeByID(int id) {

        for (int i = 0; i < count; i++) 
        {

            if (data[i].getID() == id) 
            {

                for (int j = i; j < count - 1; j++) 
                {
                    data[j] = data[j + 1];
                }

                count--;
                return true;
            }
        }

        return false;
    }
    T* findByID(int id)
    {

        for (int i = 0; i < count; i++) 
        {

            if (data[i].getID() == id) 
            {
                return &data[i];
            }
        }

        return nullptr;
    }
   
    T* getAll() {
        return data;
    }

    const T* getAll() const {
        return data;
    }
    int size() const 
    {
        return count;
    }
};

#endif
