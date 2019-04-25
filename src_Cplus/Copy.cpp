#include <iostream>
#include <cstring>
using namespace std;

class Person
{
	char * name;	// Pointer 맴버변수  
	int age;
public:
	// 생성자 정의 ; 동적할당을 통해 member 변수 할당 ; 
	Person(const char * myname, int myage)
	{
		cout << "Constructor!" << endl;
		int len = strlen(myname) + 1;	// 생성자를 통해 포인터 멤버 변수가 동적 할당을 통해 Heap 영역을 가리키게 정의하였다. 
		name = new char[len];
		strcpy_s(name, len, myname);
		age = myage;
	}

	// 복사 생성자 정의 ; 대입 연산을 할때 자동으로 호출 
#if 1	// Deep Copy 
	Person(const Person& copy) :age(copy.age)				// 대입연산시 자동으로 call 
	{
		cout << "Copy Constructor!" << endl;
		name = new char[strlen(copy.name) + 1];				// 또다른 Heap 공간 할당
		strcpy_s(name, strlen(copy.name) + 1, copy.name);
	}
#else	// Shaloow Copy
	Person(const Person& copy) : age(copy.age), name(copy.name) { }
#endif

#if 2	// Deep 대입 연산자 
	Person& operator=(const Person& ref)
	{
		cout << "Assignment Operator!" << endl;
		delete[]name;	//원래 가지고 있던 name 제거! 

		int len = strlen(ref.name) + 1;
		name = new char[len];		// Deep copy를 위한 Heap 영역에 새로운 할당 
		strcpy_s(name, strlen(ref.name) + 1, ref.name);
		age = ref.age;
		return *this;
	}
#else	// shallow 대입 연산자(default 대입연산)
	Person& operator=(const Person& ref)
	{
		age = ref.age;
		name = ref.name;

		return *this;
	}
#endif


	void ShowPersonInfo() const
	{
		cout << "이름: " << name << endl;
		cout << "나이: " << age << endl;
	}
	~Person()
	{
		delete[]name;
		cout << "called destructor!" << endl;
	}
};

int main(void)
{
	Person man1("Lee dong woo", 29);
	Person man2 = man1;					// Default 복사 생성자를 이용하여 할당 연산(Copy)를 하게 되는데 이때, 같은 공간을 가리키는 문제 발생
	Person man3("Yoon Ji yul", 22);
	man3 = man1;							// 정의된 Deep 대입 연산자가 없다면, default 대입 연산자를 통해 연산 된다.

	man1.ShowPersonInfo();
	man2.ShowPersonInfo();
	man3.ShowPersonInfo();
	return 0;							// 객체는 2개인데, Deep copy가 이루어 지지 않으면, 소멸자는 1번 밖에 Call 되지 않는다. : 심한한 문제 발생! 하나의 객체가 소멸 후 나머지 객체가 가리키는 공간 없어짐
}
