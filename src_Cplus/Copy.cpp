#include <iostream>
#include <cstring>
using namespace std;

class Person
{
	char * name;	// Pointer �ɹ�����  
	int age;
public:
	// ������ ���� ; �����Ҵ��� ���� member ���� �Ҵ� ; 
	Person(const char * myname, int myage)
	{
		cout << "Constructor!" << endl;
		int len = strlen(myname) + 1;	// �����ڸ� ���� ������ ��� ������ ���� �Ҵ��� ���� Heap ������ ����Ű�� �����Ͽ���. 
		name = new char[len];
		strcpy_s(name, len, myname);
		age = myage;
	}

	// ���� ������ ���� ; ���� ������ �Ҷ� �ڵ����� ȣ�� 
#if 1	// Deep Copy 
	Person(const Person& copy) :age(copy.age)				// ���Կ���� �ڵ����� call 
	{
		cout << "Copy Constructor!" << endl;
		name = new char[strlen(copy.name) + 1];				// �Ǵٸ� Heap ���� �Ҵ�
		strcpy_s(name, strlen(copy.name) + 1, copy.name);
	}
#else	// Shaloow Copy
	Person(const Person& copy) : age(copy.age), name(copy.name) { }
#endif

#if 2	// Deep ���� ������ 
	Person& operator=(const Person& ref)
	{
		cout << "Assignment Operator!" << endl;
		delete[]name;	//���� ������ �ִ� name ����! 

		int len = strlen(ref.name) + 1;
		name = new char[len];		// Deep copy�� ���� Heap ������ ���ο� �Ҵ� 
		strcpy_s(name, strlen(ref.name) + 1, ref.name);
		age = ref.age;
		return *this;
	}
#else	// shallow ���� ������(default ���Կ���)
	Person& operator=(const Person& ref)
	{
		age = ref.age;
		name = ref.name;

		return *this;
	}
#endif


	void ShowPersonInfo() const
	{
		cout << "�̸�: " << name << endl;
		cout << "����: " << age << endl;
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
	Person man2 = man1;					// Default ���� �����ڸ� �̿��Ͽ� �Ҵ� ����(Copy)�� �ϰ� �Ǵµ� �̶�, ���� ������ ����Ű�� ���� �߻�
	Person man3("Yoon Ji yul", 22);
	man3 = man1;							// ���ǵ� Deep ���� �����ڰ� ���ٸ�, default ���� �����ڸ� ���� ���� �ȴ�.

	man1.ShowPersonInfo();
	man2.ShowPersonInfo();
	man3.ShowPersonInfo();
	return 0;							// ��ü�� 2���ε�, Deep copy�� �̷�� ���� ������, �Ҹ��ڴ� 1�� �ۿ� Call ���� �ʴ´�. : ������ ���� �߻�! �ϳ��� ��ü�� �Ҹ� �� ������ ��ü�� ����Ű�� ���� ������
}
