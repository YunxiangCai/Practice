//pull 记录索引的状态

//This is an example to show the constructor and destructor of a derived class
//子类执行构造函数时，先执行父类的构造函数
//子类执行析构函数时，先执行自己的析构，再执行父类的析构函数

#include  <iostream>
using namespace std;

class People{
protected:
	char* name;
	int age;
public:
	People(const char* s, int a){
		name = new char[strlen(s)+1];
		strcpy(name,s);
		age = a;
		cout<<"People constructor:"<<"["<<name<<"]"<<"["<<age<<"]"<<endl;
	}

	~People(){
		delete name;
		cout<<"People destructor:"<<"["<<name<<"]"<<"["<<age<<"]"<<endl;	}
};

class Student:public People
{
public:
	Student(const char* s,int a, int stuNo, const char *cls) : People(s,a){
		s_no=stuNo;
		class_no=new char[strlen(cls)+1];
		strcpy(class_no,cls);
		cout<<"Student constructor:"<<"["<<stuNo<<"]"<<"["<<class_no<<"]"<<endl;
	}
	void showname(){
		cout<<name<<endl;
	}

	~Student(){
		delete class_no;
		cout<<"People destructor:"<<"["<<s_no<<"]"<<"["<<class_no<<"]"<<endl;
	}

private:
	int s_no;
	char * class_no;

};

int main()
{
	{People("Zhangsan",25);}
	Student s1("Lisi",25,100000,"123");
	Student s2("Wangwu",23,100001,"132");
	s1.showname();
}


