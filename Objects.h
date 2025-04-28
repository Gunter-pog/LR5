#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED

#include <vector>
#include <list>

using namespace std;

template <typename T>
class Iterator
{
public:
    virtual ~Iterator() {}
    virtual void first_object() = 0;
    virtual void next_object() = 0;
    virtual bool last_object() const = 0;
    virtual T actual_object() const = 0;
};

template <typename T>
class ListValue : public Iterator<T>
{
private:
    list<T>* listic;
    typename list<T>::iterator j;
public:
    ListValue(list<T>* l) : listic(l), j(l->begin()) {}

    void first_object() override {j = listic->begin();}
    void next_object() override {j++;}
    bool last_object() const override {return j == listic->end();}
    T actual_object() const override {return *j;}
};

template <typename T>
class VecValue: public Iterator<T>
{
private:
    vector<T>* vec;
    size_t i;

public:
    VecValue(vector<T>* v) : vec(v), i(0) {}
    void first_object() override {i = 0;}
    void next_object() override {i++;}
    bool last_object() const override {return i >= vec->size();}
    T actual_object() const override {return (*vec)[i];}
};

template<typename T>
class Iterator_Container
{
public:
    virtual ~Iterator_Container() {}
    virtual Iterator<T>* GetIterator() = 0;
};

template <typename T>
class VecContainer : public Iterator_Container<T>
{
private:
    vector<T> objects;
public:
    void add_object(T&& object) {objects.push_back(move(object));}
    size_t count() const {return objects.size();}
    auto begin() {return VecValue<T>(&objects);}
    auto end() {return VecValue<T>(&objects);}

    Iterator<T>* GetIterator() override
    {
        return new VecValue<T>(&objects);
    }
};

template <typename T>
class ListContainer : public Iterator_Container<T>
{
private:
    list<T> objects;
public:
    void add_object(T&& object) {objects.push_back(move(object));}
    size_t count() const {return objects.size();}
    auto begin() {return ListValue<T>(&objects);}
    auto end() {return ListValue<T>(&objects);}

    Iterator<T>* GetIterator() override
    {
        return new ListValue<T>(&objects);
    }
};

template<typename T>
class IteratorDecorator : public Iterator<T>
{
protected:
    Iterator<T> *I;

public:
    IteratorDecorator(Iterator<T> *i) : I(i) {}
    virtual ~IteratorDecorator() { delete I; }
    virtual void first_object() { I->first_object(); }
    virtual void next_object() { I->next_object(); }
    virtual bool last_object() const { return I->last_object(); }
    virtual T actual_object() const { return I->actual_object(); }
};

template<typename ContainerType, typename ItemType>
class ConstIteratorAdapter : public Iterator<ItemType>
{
protected:
    ContainerType *Container;
    typename ContainerType::const_iterator I;

public:
    ConstIteratorAdapter(ContainerType *container)
        : Container(container), I(container->begin()) {}

    virtual void first_object() { I = Container->begin(); }
    virtual void next_object() { ++I; }
    virtual bool last_object() const { return I == Container -> end(); }
    virtual ItemType actual_object() const { return *I; }
};

#endif // OBJECTS_H_INCLUDED
