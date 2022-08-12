#include<iostream>

using namespace std;


//单例设计模式
//意图是保证一个类仅有一个实例,并提供一个访问它的全局访问点,该实例被所有程序模块共享

std::mutex mtx;
class Singleton
{
public:
	static Singleton* get_instance()
	{
		if (p_instance == NULL)//第一次调用要判断指针是否为空
		{
			mtx.lock();
			p_instance = new Singleton();
			cout << "唯一创建(访问)实例的方法" << endl;
			mtx.unlock();
		}
		return p_instance;
	}
 
private:
	Singleton(){}; //构造函数设计成私有的
 
	static Singleton *p_instance;  //用类的指针指向唯一的实例
 
	class GC
	{
	public:
		~GC()
		{
			if (p_instance != NULL)
			{
                cout<<"call ~GC"<<endl;
				delete p_instance;
				p_instance=nullptr;
			}
		}
	};
	static GC gc;
};
 
Singleton* Singleton::p_instance = NULL;
Singleton::GC Singleton::gc;



//单例2.0
#include <iostream>
using namespace std;
 
class Singleton
{
public:
	static Singleton* get_instance()
	{
		static Singleton instance;
		return &instance;
	}
 
private:
	Singleton(){}; //构造函数设计成私有的
 
	Singleton(const Singleton&);
 
	Singleton& operator==(const Singleton&);
 
};
 
int main(int argc, char*argv[])
{
	Singleton *object = Singleton::get_instance();
 
	return 0;
}