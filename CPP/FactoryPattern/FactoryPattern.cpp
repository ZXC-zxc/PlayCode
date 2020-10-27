// factoryTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <map>
#include <string>

using namespace std;


class IAnimal
{
public:
	virtual int GetNumberOfLegs() const = 0;
	virtual void Speak() = 0;
	virtual void Free() = 0;
};


// IAnimal implementations
class Cat : public IAnimal
{
public:
	int GetNumberOfLegs() const { return 4; }
	void Speak() { cout << "Meow" << endl; }
	void Free() { delete this; }

	static IAnimal* __stdcall Create() { return new Cat(); }
};

class Dog : public IAnimal
{
public:
	int GetNumberOfLegs() const { return 4; }
	void Speak() { cout << "Woof" << endl; }
	void Free() { delete this; }

	static IAnimal* __stdcall Create() { return new Dog(); }
};

class Spider : public IAnimal // Yeah it isn’t really an animal…
{
public:
	int GetNumberOfLegs() const { return 8; }
	void Speak() { cout << endl; }
	void Free() { delete this; }

	static IAnimal* __stdcall Create() { return new Spider(); }
};

class Horse : public IAnimal
{
public:
	int GetNumberOfLegs() const { return 4; }
	void Speak() { cout << "A horse is a horse, of course, of course." << endl; }
	void Free() { delete this; }

	static IAnimal* __stdcall Create() { return new Horse(); }
};


typedef IAnimal* (__stdcall* CreateAnimalFn)(void);


template<typename I, typename T, typename F>
class xFactory {

protected:
	typedef map<T, F> FactoryMap;
	FactoryMap m_FactoryMap;

public:
	~xFactory() { m_FactoryMap.clear(); }


	void Register(const T& name, F pfnCreate) {
		m_FactoryMap[name] = pfnCreate;
	};

	template<typename... Args>
	I* Create(const T& name, Args&&... args) {
		auto it = m_FactoryMap.find(name);
		if (it != m_FactoryMap.end())
			return it->second(std::forward<Args>(args)...);
		return NULL;
	}
};

class AnimalFactory :public xFactory<IAnimal, std::string, CreateAnimalFn> {
public:
	AnimalFactory();
};


AnimalFactory::AnimalFactory()
{
	Register("Horse", &Horse::Create);
	Register("Cat", &Cat::Create);
	Register("Dog", &Dog::Create);
	Register("Spider", &Spider::Create);
}

int main()
{
	IAnimal* pAnimal = NULL;
	string animalName;

	while (pAnimal == NULL)
	{
		cout << "Type the name of an animal or ‘q’ to quit: ";
		cin >> animalName;

		if (animalName == "q")
			break;

		AnimalFactory af;

		IAnimal* pAnimal = af.Create(animalName);
		if (pAnimal)
		{
			cout << "Your animal has " << pAnimal->GetNumberOfLegs() << " legs." << endl;
			cout << "Your animal says: ";
			pAnimal->Speak();
		}
		else
		{
			cout << "That animal doesn’t exist in the farm! Choose another!" << endl;
		}
		if (pAnimal)
			pAnimal->Free();
		pAnimal = NULL;
		animalName.clear();
	}
	return 0;
}

