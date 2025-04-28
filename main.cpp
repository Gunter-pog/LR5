#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Objects.h"

using namespace std;

class Wine
{
protected:
    string type;
    double degree;
    int volume;
public:
    Wine(const string& type, int degree, int volume): type(type), degree(degree), volume(volume){}

    virtual void characteristic_out()
    {
        cout << "Type of wine: " << type
        << "; Classic degree: " << degree
        << "; Classic volume: " << volume << " ml" << endl << endl;
    }
    virtual void amount_of_etyl_alcohol()
    {
        cout << "Amount of ethyl alcohol: " << volume * (degree / 100) << " ml"<< endl << endl;
    }

    string GetType() const { return type; }
    double GetDegree() const { return degree; }
    int GetVolume() const { return volume; }
};

class White_Wine : public Wine
{
private:
    string my_attitude;
public:
    White_Wine(const string& type, int degree, int volume, const string& my_attitude):Wine(type, degree, volume), my_attitude(my_attitude){}

    void characteristic_out()
    {
        Wine::characteristic_out();
        cout << "My attitude to this wine: " << my_attitude << endl << endl;
    }

    void attitude()
    {
        string att;
        cout << "What is your attitude to white wine?" << endl;
        cin >> att;
        cout << endl;
    }
};

class Red_Wine : public Wine
{
private:
    int popularity_in_russia;
public:
    Red_Wine(const string& type, int degree, int volume, int popularity_in_russia):Wine(type, degree, volume), popularity_in_russia(popularity_in_russia){}

    void characteristic_out()
    {
        Wine::characteristic_out();
        cout << "In Russia, the popularity of this type of wine is " << popularity_in_russia << " percent" << endl << endl;
    }

    void info()
    {
        cout << "Italy is a leader in red wine production" << endl << endl;
    }
};

class Sparkling_Wine : public Wine
{
private:
    bool sparkling;
public:
    Sparkling_Wine(const string& type, int degree, int volume, bool sparkling):Wine(type, degree, volume), sparkling(sparkling){}

    void characteristic_out()
    {
        Wine::characteristic_out();
        cout << "Sparkling: " << boolalpha << sparkling << endl << endl;
    }

    void champagne()
    {
        for (int i = 0; i < 1; i++)
        {
            sleep(1);
            cout << "\bC" << flush;
            sleep(1);
            cout << "\bh" << flush;
            sleep(1);
            cout << "\ba" << flush;
            sleep(1);
            cout << "\bm" << flush;
            sleep(1);
            cout << "\bp" << flush;
            sleep(1);
            cout << "\ba" << flush;
            sleep(1);
            cout << "\bg" << flush;
            sleep(1);
            cout << "\bn" << flush;
            sleep(1);
            cout << "\be" << flush;
        }
    }
};

Wine* create_type_of_wine(int type)
{
    switch (type)
    {
    case 0:
        return new White_Wine("White wine", 15, 750, "my favorite wine");
    case 1:
        return new Red_Wine("Red wine", 13, 750, 52);
    case 2:
        return new Sparkling_Wine("Sparcling wine", 11, 750, true);
    default:
        return nullptr;
    }
}

class TypeOfWineDecorator : public IteratorDecorator<class Wine*>
{
private:
    string Type;

public:
    TypeOfWineDecorator(Iterator<Wine*> *i, string type)
    : IteratorDecorator<Wine*>(i), Type(type) {}

    void First()
    {
        I->first_object();
        while(!I->last_object() && I->actual_object() -> GetType() != Type)
        {
            I->next_object();
        }
    }

    void next_object()
    {
        do
        {
            I->next_object();

        } while(!I->last_object() && I->actual_object() -> GetType() != Type);
    }
};

class DegreeOfWineDecorator : public IteratorDecorator<class Wine*>
{
private:
    double Degree;

public:
    DegreeOfWineDecorator(Iterator<Wine*> *i, double degree)
    : IteratorDecorator<Wine*>(i), Degree(degree) {}

    void First()
    {
        I->first_object();
        while(!I->last_object() && I->actual_object() -> GetDegree() != Degree)
        {
            I->next_object();
        }
    }

    void next_object()
    {
        do
        {
            I->next_object();

        } while(!I->last_object() && I->actual_object() -> GetDegree() != Degree);
    }
};

class VolumeOfWineDecorator : public IteratorDecorator<class Wine*>
{
private:
    int Volume;

public:
    VolumeOfWineDecorator(Iterator<Wine*> *i, int volume)
    : IteratorDecorator<Wine*>(i), Volume(volume) {}

    void First()
    {
        I->first_object();
        while(!I->last_object() && I->actual_object() -> GetVolume() != Volume)
        {
            I->next_object();
        }
    }

    void Next()
    {
        do
        {
            I->next_object();

        } while(!I->last_object() && I->actual_object() -> GetVolume() != Volume);
    }
};

template<typename Container>
void output(Container& container)
{
    for (auto i = container.begin(); !i.last_object(); i.next_object())
    {
        i.actual_object()->characteristic_out();
        i.actual_object()->amount_of_etyl_alcohol();
    }
}

void Alcohol(Iterator<Wine*> *i)
{
    for(i->first_object(); !i->last_object(); i->next_object())
    {
        Wine *actual_wine = i -> actual_object();
        actual_wine -> amount_of_etyl_alcohol();
    }
}

int main()
{
    VecContainer<Wine*> vec_container;
    ListContainer<Wine*> listic_container;

    srand(time(0));
    for (int i = 0; i < 4; i++)
    {
        int type = rand() % 3;
        vec_container.add_object(create_type_of_wine(type));

        type = rand() % 3;
        listic_container.add_object(create_type_of_wine(type));
    }

    cout << "Demo of decorator";
    Iterator<Wine*> *adapted_sparkling_i = new DegreeOfWineDecorator(listic_container.GetIterator(), 13);
    Alcohol(adapted_sparkling_i);

    cout << "Vector Container" << endl;
    output(vec_container);

    cout << endl << "List container" << endl;
    output(listic_container);

    size_t n = 25;

    list<Wine*> wine_list;
    for(size_t j = 0; j < n; j++)
    {
        int wine_num = rand() % 3;
        Wine *new_wine = create_type_of_wine(wine_num);
        wine_list.push_back(new_wine);
    }

    cout << "We calculate the amount of etyl alcohol of all red wines" << endl;
    Iterator<Wine*> *adapted_i = new ConstIteratorAdapter<std::list<Wine*>, Wine*>(&wine_list);
    Iterator<Wine*> *adapted_red_i2 = new DegreeOfWineDecorator(adapted_i, 13);

    Alcohol(adapted_red_i2);
    delete adapted_red_i2;
}
