# C++面试考点总结



## 1.关键字汇总

##### 1.1 static

作用

1. 修饰**普通变量**，修改变量的存储区域和生命周期，使变量存储在静态区，在 main 函数运行前就分配了空间，如果有初始值就用初始值初始化它，如果没有初始值系统用默认值初始化它。
2. 修饰**普通函数**，表明函数的作用范围，仅在定义该函数的文件内才能使用。在多人开发项目时，为了防止与他人命名空间里的函数重名，可以将函数定位为 static。
3. 修饰成员变量，**修饰成员变量使所有的对象只保存一个该变量，而且不需要生成对象就可以访问该成员**。
4. 修饰成员函数，**修饰成员函数使得不需要生成对象就可以访问该函数**，但是**在 static 函数内不能访问非静态成员**。

```C++
class mycls{
private:
    int data;
    static int nums; //静态变量不能在类中初始化

public:
    mycls(int data_)
    {
        data = data_;
    }
    void print()
    {
        std::cout<<"data:"<<data<<std::endl;
        num++;
        std::cout<<"static nums:"<<nums<<std::endl;
        
    }
    static void process()
    {
        nums++;
        std::cout<<"After static function process nums:"<<nums<<std::endl;
    }
};
//静态变量需要先在类外部进行初始化，才能被类的成员函数访问
//静态成员变量或静态成员函数 在外部进行定义的时候不能带static
int mycls::nums=0;
int main()
{
    mycls tmp = mycls(7);
    tmp.print();
}
```



##### 1.2 const

1. 修饰变量，说明该变量不可以被改变；

2. 修饰指针，分为**指向常量的指针**（pointer to const）和**自身是常量的指针**（常量指针，const pointer）

   ```c++
   char greeting[] = "Hello";
   char* p1 = greeting;      // 指针变量，指向字符数组变量
   const char* p2 = greeting;// 指针变量，指向字符数组常量（const 后面是 char，说明指向的字符（char）不可改变）
   char* const p3 = greeting;// 自身是常量的指针，指向字符数组变量（const 后面是 p3，说明 p3 指针自身不可改变）
   const char* const p4 = greeting;// 自身是常量的指针，指向字符数组常量
   ```

   

3. 修饰引用，指向常量的引用（reference to const），用于形参类型，**即避免了拷贝，又避免了函数对值的修改**；

   ```c++
   void function4(const int& Var);          // 引用参数在函数内为常量
   ```

4. **修饰成员函数，说明该成员函数内不能修改成员变量。 也就是常函数**



##### 1.3 extern

* 声明extern关键字的全局变量和函数可以使得它们能够跨文件被访问。
* 被 `extern "C"` 修饰的变量和函数是按照 C 语言方式编译和链接的

##### 1.4 volatile

```cpp
volatile int i = 10; 
```

* volatile 关键字是一种类型修饰符，用它声明的类型变量表示可以被某些编译器未知的因素（操作系统、硬件、其它线程等）更改。所以使用 volatile 告诉编译器不应对这样的对象进行优化。
* **volatile 关键字声明的变量，每次访问时都必须从内存中取出值（没有被 volatile 修饰的变量，可能由于编译器的优化，从 CPU 寄存器中取值）**
* const 可以是 volatile （如只读的状态寄存器）
* 指针可以是 volatile

##### 1.5 decltype

auto和decltype关键字都可以自动推导出变量的类型，但是他们的用法是有区别的：

```c++
auto varname = value;
decltype(exp) varname = value; //exp 表示一个表达式
```

auto根据'='右边的初始值value推导出变量的类型，而decltype根据exp表达式推导出变量的类型，跟"="右边的value没有关系。另外，auto要求变量必须初始化，而decltype不要求。这很容易理解，auto是根据变量的初始值来推导出变量类型的，如果不初始化，变量的类型也就无法推导。

##### 1.6 assert()

断言，是宏，而非函数。assert 宏的原型定义在 `<assert.h>`（C）、`<cassert>`（C++）中，其作用是如果它的条件返回错误，则终止程序执行。可以通过定义 `NDEBUG` 来关闭 assert，但是需要在源代码的开头，`include <assert.h>` 之前。

assert() 使用

```cpp
#define NDEBUG          // 加上这行，则 assert 不可用
#include <assert.h>

assert( p != NULL );    // assert 不可用
```

##### 1.7 explicit(显式)关键字

* explicit 修饰构造函数时，可以防止隐式转换和复制初始化
* explicit 修饰转换函数时，可以防止隐式转换，但 [按语境转换](https://zh.cppreference.com/w/cpp/language/implicit_conversion) 除外

```c++
struct A
{
	A(int) { }
	operator bool() const { return true; }
};

struct B
{
	explicit B(int) {}
	explicit operator bool() const { return true; }
};

void doA(A a) {}

void doB(B b) {}

int main()
{
	A a1(1);		// OK：直接初始化
	A a2 = 1;		// OK：复制初始化
	A a3{ 1 };		// OK：直接列表初始化
	A a4 = { 1 };		// OK：复制列表初始化
	A a5 = (A)1;		// OK：允许 static_cast 的显式转换 
	doA(1);			// OK：允许从 int 到 A 的隐式转换
	if (a1);		// OK：使用转换函数 A::operator bool() 的从 A 到 bool 的隐式转换
	bool a6(a1);		// OK：使用转换函数 A::operator bool() 的从 A 到 bool 的隐式转换
	bool a7 = a1;		// OK：使用转换函数 A::operator bool() 的从 A 到 bool 的隐式转换
	bool a8 = static_cast<bool>(a1);  // OK ：static_cast 进行直接初始化

	B b1(1);		// OK：直接初始化
	B b2 = 1;		// 错误：被 explicit 修饰构造函数的对象不可以复制初始化
	B b3{ 1 };		// OK：直接列表初始化
	B b4 = { 1 };		// 错误：被 explicit 修饰构造函数的对象不可以复制列表初始化
	B b5 = (B)1;		// OK：允许 static_cast 的显式转换
	doB(1);			// 错误：被 explicit 修饰构造函数的对象不可以从 int 到 B 的隐式转换
	if (b1);		// OK：被 explicit 修饰转换函数 B::operator bool() 的对象可以从 B 到 bool 的按语境转换
	bool b6(b1);		// OK：被 explicit 修饰转换函数 B::operator bool() 的对象可以从 B 到 bool 的按语境转换
	bool b7 = b1;		// 错误：被 explicit 修饰转换函数 B::operator bool() 的对象不可以隐式转换
	bool b8 = static_cast<bool>(b1);  // OK：static_cast 进行直接初始化

	return 0;
}
```

##### 1.8 using

* using 声明：一条`using 声明` 语句一次只引入命名空间的一个成员。

  ```c++
  using namespace_name::name;
  ```

* using 指示：`using 指示` 使得某个特定命名空间中所有名字都可见，这样我们就无需再为它们添加任何前缀限定符了。

  ```c++
  using namespace name;
  ```

  尽量少使用 `using 指示`

  ```cpp
  using namespace std;
  ```

  应该多使用 `using 声明`

  ```cpp
  int x;
  std::cin >> x ;
  std::cout << x << std::endl;
  ```

  或者

  ```cpp
  using std::cin;
  using std::cout;
  using std::endl;
  int x;
  cin >> x;
  cout << x << endl;
  ```

* using 指定别名

  ```c++
  typedef int T; // 用 T 代替 int
  using T = int; // 用 T 代替 int
  ```

  

​       



## 2. C++11

#### 2.1 override和final

> https://zhuanlan.zhihu.com/p/258383836

override ： 子类必须要重写的虚函数，这个用在子类的虚函数后

final ： 子类不能重写虚函数，这个紧跟类名

#### 2.2  C++中四种类型转换

> https://blog.csdn.net/ydar95/article/details/69822540

C++中四种类型转换分别为**const_cast、static_cast、dynamic_cast、reinterpret_cast**,四种转换功能如下：

1. const_cast ： **将const变量转为非const**

2. static_cast：**最常用**，**可以用于各种隐式转换，比如非const转const**，static_cast可以用于类向上转换，但向下转换能成功但不安全

3. dynamic_cast : **只能用于含有虚函数的类转换，用于类向上和向下转换**

   向上转换：子类向基类转换

   向下转换：基类向子类转换

   这两种转换，子类包含父类，当父类转换为子类时可能出现非法内存访问的问题。dynamic_cast通过判断变量运行时类型和要转换的类型是否相同来判断是否能够进行向下转换。dynamic_cast可以做类之间上下转换，转换的时候会进行类型检查，类型相等成功转换，类型不等转换失败。运用RTTI(RunTime Type Information)技术提供了运行时确定对象类型的方法。

4. reinterpret_cast：**几乎什么都可以转**，比如将int转指针，可能会出问题，尽量少用；

 

#### 2.3 智能指针

四个智能指针：auto_ptr, shared_ptr, weak_ptr, unique_ptr 其中后三个是c++11支持，并且第一个已经被11弃用。

**智能指针的作用是管理一个指针，因为存在以下这种情况：申请的空间在函数结束时忘记释放，造成内存泄漏。使用智能指针可以避免这个问题，因为智能指针就是一个类，当超出了类的作用域是，类会自动调用析构函数，析构函数会自动释放资源。**所以智能指针的作用原理就是在函数结束时自动释放内存空间，不需要手动释放内存空间。

1. auto_ptr

   auto_ptr指针存在的问题是，两个智能指针同时指向一块内存，就会两次释放同一块资源，自然报错，已被C++11 弃用

2. unique_ptr

   unique_ptr规定一个智能指针独占一块内存资源。当两个智能指针同时指向一块内存，编译报错

   > 实现原理：将拷贝构造函数和赋值拷贝构造函数声明为private或delete。不允许拷贝和赋值操作，但是支持移动构造函数，通过move把一个对象指针变成右值之后可以移动给另一个unique_ptr

3. shared_ptr

   shared_ptr可以实现多个智能指针指向相同对象，该对象和其相关资源会在引用为0时被销毁释放。

   > 实现原理：有一个引用计数的指针类型变量，专门用于引用计数，使用拷贝构造函数和赋值拷贝构造函数时，引用计数+1 ，当引用计数为0时，释放资源
   >
   > https://cloud.tencent.com/developer/article/1688444

4. weak_ptr : 是用来解决shared_ptr相互引用导致死锁的智能指针

**线程安全性**

多线程读写shared_ptr所指的同一个对象，不管是相同的shared_ptr对象，还是不同的shared_ptr对象，都需要加锁保护



#### 2.4 右值引用、move语义、完美转发

> 参考链接：
>
> https://blog.csdn.net/qq_38410730/article/details/105517378
>
> https://codinfox.github.io/dev/2014/06/03/move-semantic-perfect-forward/

右值就是运算符右侧的值，**凡是取地址（`&`）操作可以成功的都是左值，其余都是右值**。

对于引用这块总结一下，假设T是个**具体类型**：

* 左值引用(T&)：只能绑定到左值(非const左值)；
* 右值引用(T&&)：只能绑定到右值(非const右值)；
*   常量左值引用(const T&)：常量左值引用是个万能的引用类型。它既可以绑定到左值也可以绑定到右值。它像右值引用一样可以延长右值的生命期。不过相比于右值引用所引用的右值，常量左值引用的右值在它的余生中只能是只读的；
* 常量右值引用(const T&&)：可绑定到右值或const右值。一般很少使用，基本没有实际用处。

> **若T&&在发生自动类型推断的时候，它是未定的引用类型，如果被一个左值初始化，它就是一个左值引用；如果它被一个右值初始化，它就是一个右值引用，它是左值引用还是右值引用取决于它的初始化。因此，也被称为万能引用**。

而针对有的时候的构造对象时会导致多次调用复制构造函数，就需要使用**移动语义**+**移动构造函数**

```c++
Test createTest() {
    return Test();
}

int main() {
    Test t(createTest());
}
```

所谓移动语义也就是通过`std::move`来把左值转化为右值，从而方便应用移动语义。它实际上将左值变成右值引用，然后应用移动语义，调用移动构造函数，就避免了拷贝，提高了程序性能。而对于移动构造函数也就是**将指针的所有者转移到了另外一个对象，同时，将原对象的指针置为空**

**完美转发**：则是在传递参数时会导致数据从右值变为左值，而我们又需要它不改变类型时，可以使用`std::forward<T>()`来保证类型不变

#### 2.5 Lambda匿名函数

> 参考链接 ：https://www.cnblogs.com/DswCnblog/p/5629165.html

Lambda表达式完整表达式

```c++
[capture list] (params list) mutable exception-> return type { function body }
```

各项具体含义如下

1. capture list：捕获外部变量列表
2. params list：形参列表
3. mutable指示符：用来说用是否可以修改捕获的变量
4. exception：异常设定
5. return type：返回类型
6. function body：函数体

此外，我们还可以省略其中的某些成分来声明“不完整”的Lambda表达式，常见的有以下几种：

| 序号 | 格式                                                        |
| ---- | ----------------------------------------------------------- |
| 1    | [capture list] (params list) -> return type {function body} |
| 2    | [capture list] (params list) {function body}                |
| 3    | [capture list] {function body}                              |

其中：

- 格式1声明了const类型的表达式，这种类型的表达式不能修改捕获列表中的值。

- 格式2省略了返回值类型，但编译器可以根据以下规则推断出Lambda表达式的返回类型： （1）：如果function body中存在return语句，则该Lambda表达式的返回类型由return语句的返回类型确定； （2）：如果function body中没有return语句，则返回值为void类型。

- 格式3中省略了参数列表，类似普通函数中的无参函数。

  讲了这么多，我们还没有看到Lambda表达式的庐山真面目，下面我们就举一个实例。

```c++
bool cmp(int a, int b)
{
    return  a < b;
}

int main()
{
    vector<int> myvec{ 3, 2, 5, 7, 3, 2 };
    vector<int> lbvec(myvec);

    sort(myvec.begin(), myvec.end(), cmp); // 旧式做法
    cout << "predicate function:" << endl;
    for (int it : myvec)
        cout << it << ' ';
    cout << endl;

    sort(lbvec.begin(), lbvec.end(), [](int a, int b) -> bool { return a < b; });   // Lambda表达式
    cout << "lambda expression:" << endl;
    for (int it : lbvec)
        cout << it << ' ';
}
```

关于捕获外部变量的情况

1. **值捕获**(与函数按值传递参数)

   ```c++
   int main()
   {
       int a = 123;
       auto f = [a] { cout << a << endl; }; 
       a = 321;
       f(); // 输出：123
   }
   ```

2. **引用捕获**

   ```c++
   int main()
   {
       int a = 123;
       auto f = [&a] { cout << a << endl; }; 
       a = 321;
       f(); // 输出：321
   }
   ```

3. **隐式捕获**

   上面的值捕获和引用捕获都需要我们在捕获列表中显示列出Lambda表达式中使用的外部变量。除此之外，我们还可以让编译器根据函数体中的代码来推断需要捕获哪些变量，这种方式称之为隐式捕获。隐式捕获有两种方式，分别是[=]和[&]。[=]表示以值捕获的方式捕获外部变量，[&]表示以引用捕获的方式捕获外部变量。

最后 lambda表达式的参数： 1.参数列表中不能有默认参数     2. 不支持可变参数  3. 所有参数必须有参数名

## 3. 面向对象

#### 3.1 构造函数汇总

面试题：实现一个矩阵类 写出构造/拷贝构造/赋值操作符重载/移动构造/矩阵加函数

> 







#### 3.2 继承

三种继承方式：

| 继承方式      | 基类的public成员  | 基类的protected成员 | 基类的private成员 |
| ------------- | ----------------- | ------------------- | ----------------- |
| pubilc继承    | 仍为public成员    | 仍为protected成员   | 不可见            |
| protected继承 | 变为protected成员 | 仍为protected成员   | 不可见            |
| private继承   | 变为private成员   | 变为private成员     | 不可见            |

1. 子类对象可以赋值给父类对象(切片)；父类对象不可以赋值给子类对象
2. 父类指针或者引用可以指向子类对象；子类的指针或者引用不可以指向父类对象

总结：父(->/=) 子（可以） ，子(->/=)父(不行)；基类引用(指针)可以 = 子类对象 ，反之则不行，

#### 3.3 C++的重载和重写

1. 重写：是指派生类中存在重新定义的函数。其函数名，参数列表，返回值类型都必须要同基类中被重写的函数一致。只有**函数体**不同，**派生类对象调用时会调用派生类的重写函数，不会调用被重写函数**。且重写的基类中被重写的函数必须有virtual修饰
2. 重载：函数名相同，但**参数列表不同**，函数体实现也不同

> 为什么C语言不支持重载而C++支持呢？
>
> 主要原因是c和c++的编译器在对函数进行重命名的时候用的方法不一样，比如同一个函数int ADD(int a,int b)
>
> C编译器处理后 将这个函数重命名为_ ADD，而C++编译器处理后，将这个函数重新命名为_ ADD _ int _ int
>
> 所以说函数重载的本质是：参数列表不同：1.参数的类型不同 2.参数个数不同 3. 参数的顺序不同
>
> 这三点引起的编译器修饰函数名的不同

##### 函数后加const构不构成重载

> https://blog.csdn.net/qq_38408573/article/details/116061377

> 值传递不构成，指针和引用传递构成，成员函数加const构成





#### 3.4  C++中的多态

静态多态：函数重载

动态多态：虚函数

#### 3.5  说说为什么要虚析构，为什么不能虚构造

1. 虚析构：将可能会被继承的父类的析构函数设置为虚函数，可以保证当我们new一个子类，然后使用基类指针指向该子类对象，释放基类指针时可以释放掉子类的空间，防止内存泄漏。如果基类的析构函数不是虚函数，在特定情况下会导致派生类无法被析构

   * 用派生类类型指针绑定派生类实例，析构时，不管基类析构是不是虚函数，都会正常析构
   * **用基类类型指针绑定派生类实例，析构的时候，如果基类析构函数不是虚函数，则只会析构基类，不会析构派生类对象，从而造成内存泄漏。**为什么会出现这种现象呢，个人认为析构的时候如果没有虚函数的动态绑定功能，就只能一句指针的类型来进行，而不是根据指针绑定的对象来进行，所以只是调用了基类的析构函数；如果基类的析构函数是虚函数，则析构的时候就要根据指针绑定的对象来调用对应的析构函数了。

   C++默认的析构函数不是虚函数是因为虚函数需要额外的虚函数表和虚表指针，占用额外的内存。对于不会被继承的类来说，其析构函数如果是虚函数就会浪费内存

2. 不能虚构造：

   * 从存储空间角度：虚函数对应一个vtable，这个表**的地址是存储在对象的内存空间的。**如果将构造函数设置为虚函数，就需要到vtable中调用，可是对象还没有实例化，没有分配内存空间，如何调用？
   * 虚函数的作用在于通过父类的指针或者引用来调用它的时候能够变成调用子类的那个成员函数。而构造函数是在创建对象时自动调用的，不可能通过父类的指针或者引用去调用，因此也就规定构造函数不能是虚函数。

   

#### 3.6  虚表指针

> **虚表指针问题**：https://zhuanlan.zhihu.com/p/75172640



#### 3.7  C++中哪些函数不能被声明为虚函数

常见的不能声明为虚函数的有：普通函数(非成员函数)、静态成员函数、内联成员函数、构造函数、友元函数。

1. 为什么不支持内联成员函数为虚函数？

   inline在函数编译时被展开，虚函数在运行时才能动态绑定

2. 为什么不支持静态成员函数为虚函数？（待定）

   静态成员函数对每个类来说只有一份代码，所有的对象都共享这一份代码，他也没有要动态绑定的必要性。静态成员函数属于一个类而非某一对象，没有this指针，它无法进行对象的判别

3. 为什么不支持友元函数为虚函数？

   因为C++不支持友元函数的继承，对于没有继承特性的函数没有虚函数的说法。



#### 3.11 模版

##### 函数模版

```c++
template <typename AnyType>
void Swap(AnyType &a,AnyType &b)
{
    AnyType temp;
    temp = a;
    a=b;
    b=temp;
}
```

> **模板并不创建任何函数，只是告诉编译器如何定义函数。最终仍将两个独立的函数定义，就像以手工的方式定义了这些函数一样。**最终的代码不包含任何模板，而只包含了为程序生成的实际函数。使用模板的好处是，它使生成多个函数定义更简单、更可靠。
>
> **常见的情形是，将模板放在头文件中，并在需要使用模板的文件中包含头文件**

 第一行指出，要建立一个模板，并将其类型命名为AnyType(这个类型名任意，只要符合C++命名规则)。关键字template和typename是必需的。除非可以用class替换typename (这里就记使用typename)。

> **模板并不创建任何函数，只是告诉编译器如何定义函数。最终仍将两个独立的函数定义，就像以手工的方式定义了这些函数一样。**最终的代码不包含任何模板，而只包含了为程序生成的实际函数。使用模板的好处是，它使生成多个函数定义更简单、更可靠。
>
> **常见的情形是，将模板放在头文件中，并在需要使用模板的文件中包含头文件**

######  重载的模板

**需要多个对不同类型使用同一种算法的函数时，可使用模板。**但是并非所有类型都使用相同的算法，所以为了满足这个需求可以像重载常规函数那样重载模板定义。

> 函数重载：函数名相同，但是特征标一定不同，返回值类型可能不同，用于处理不同情况下同一种需求。
>
> 函数模板：不同类型使用相同算法的函数
>
> 函数模板的重载：**不同类型族使用不同的算法**，**同一类型族的不同类型使用相同算法**，举个例子，如下两个函数模板，第一个Swap模板，主要是用来交换常规变量类型如int、double等；而第二Swap模板则是用来交换数组类型的数据

```c++
template <typename T>
void Swap(T &a,T &b)
{
    T temp;
    temp = a;
    a=b;
    b=temp;
}

template <typename T>
void Swap(T a[],T b[],int n)    //这里并非函数模板中的参数都为模板参数类型，也可以是具体类型
{
    T temp;
    for(int i=0;i<n;i++)
    {
        temp = a[i];
        a[i]=b[i];
        b[i]=temp;
    }
}
```

###### 具体化

对于**某种特定的情况，我们希望生成其特定的模板，就需要用到显示具体化的一个操作**。比如某种特定的数据类型，如果还使用原始模板就不能满足，通过函数重载也不能解决。举个例子

```c++
strcut job{
  char name[40];
  double salary;
  int floor;
};
template <typename T>
void Swap(T &a,T &b)
{
    T temp;
    temp =a;
    a=b;
    b=temp;
}
/*
C++允许将一个结构体赋值给另一个，因此即使T是一个job的结构体，上述代码也依然适用。然而，假设只想交换salary和floor两个成员，那么就需要不同的代码，而假设我们要函数的参数不变，依然是两个结构体，那么函数的重载就不能用了，因此使用别的方式。
*/
```

在进入显示具体化的规则之前，我们需要先来了解一下，什么是具体化。

**具体化**，主要分为三个方面：隐式实例化、显式实例化、显示具体化。我们用如下这个模板来解释三者的区别。

```c++
template <typename T>
void Swap(T &a,T &b)
{
    T temp;
    temp =a;
    a=b;
    b=temp;
}
```

* 隐式实例化

简单的模板调用。就是有上述这样一个常规的函数模板，然后我们在程序要使用该模板来定义具体函数的时候，就调用它

```c++
int i,j;
Swap(i,j); // --->编译器就会生成Swap()的一个实例，该实例使用int类型。模板并非函数定义，但使用int的模板实例是函数定义。
```

* 显式实例化

也是通过模板生成具体的函数定义，但是与隐式实例化所不同的是，**它不是在需要用的时候调用，而是无论你用不用，我都先利用函数模板生成一个特定类型的函数。**

```c++
template  void  Swap<int>(int,int);   //显式实例化的方式，后面不带函数体，当编译器遇到这句时，就会根据函数模板创建一个int的具体化Swap函数
```

> 注意：template后无<>

* 显式具体化

显式具体化，就是针对那种特定的情况(不能重载)。其声明方式如下：

```c++
template <>Swap<int>(int &,int &);
template <>Swap(int &,int &);   //这两种方式是等价的
```

> 注意：对于显式具体化，**既然是具体化，那么就一定要有函数体！否则编译器会报错！**
>
> 显式具体化与显式实例化的区别在于：1、显式具体化是相当于模板函数所定义的方式之外的一种特殊方式，所以他与模板函数一样，不是真的定义了一个函数，而是告诉编译器这类函数该怎么定义。2、而对于显式实例化，则是根据原始的函数模板，显式的定义一种具体函数类型的函数，所以显式实例化是已经定义好了。

--------

* 三者的区别

| 具体化     | 说明                                                         |
| ---------- | ------------------------------------------------------------ |
| 隐式实例化 | 后面有程序用了，编译器才会根据模板生成一个实例函数           |
| 显式实例化 | 是无论是否有程序用，编译器都会生成一个实例函数               |
| 显示具体化 | 因为对于某些特殊类型，可能不适合模板实现，需要重新定义实现，此时就是使用显示具体化的场景 |

######  重载解析

上述章节说了那么多函数重载、函数模板、函数模板的重载。那么在具体执行时编译器该如何选择呢？这个过程就叫重载解析。

##### 类模版



#### 3.12 转换

C++ 允许指定在类和基本类型之间进行转换。

##### 5.3.1 基础类型赋值给类

**任何接受唯一一个参数的构造函数都可被用作转换函数**，将类型与该参数类型相同的值转换成类。

```c++
class Stonewt{
   double pounds;
   public:
    	Stonewt(double lbs);
    	Stonewt();
};
Stonewt::Stonewt(double lbs)
{
    pounds=lbs;
}
Stonewt::Stonewt()
{
    pounds=0;
}
```

```c++
Stonewt mycat;
mycat=19.6;    //这里就会调用构造函数进行转换
```

##### 5.3.2转换函数  类给基本类型

```c++
Stonewt wof(285.7);
double host=wof;
```

* 转换函数**必须是类方法**
* 转换函数**不能指定返回类型**
* 转换函数**不能有参数**

```c++
//转换为double类型的函数原型
operator double();
```

```c++
class Stone{
    double pounds;
    public:
    	....
        operator double()const;
};
Stone::operator double()const
{
    return pounds;
}
Stone pop(9);
double p_wt = pop;
```

---

对于类型转换的时候最好是使用显示类型转换，为了避免使用隐式类型转换，所以可以在转换函数和构造函数前加上explicit关键字。这个关键字就会使得隐式类型转换不合法，但是显示类型转换依然合法。

> C++98不允许explicit用于转换函数，C++11可以

#### 3.13 深拷贝与浅拷贝

1. 浅拷贝：将源对象的值拷贝到目标对象中去，本质上来说源对象和目标对象公用一份实体，**只是所引用的变量名不同，地址其实还是相同的**。

2. 深拷贝：拷贝的时候先开辟出和源对象大小一样的空间，然后将源对象里的内容拷贝到目标对象中去，这样两个指针就指向不同的内存位置。

3. 深拷贝的实现：深拷贝的**拷贝构造函数**和**赋值运算符**的重载传统实现：

   ```c++
   //对于复制构造函数就是重新开辟一块空间
   STRING(const STRING& s)
   {
      //_str = s._str
      _str = new char[strlen(s._str)+1];
      strcpy_s(_str,strlen(s._str)+1,s._str);
   }
   
   STRING& operator=(const STRING& s)
   {
       if(this!=&s)
       {
          delete[] _str;
          this->_str = new char[strlen(s._str)+1];
          strcpy_s(this->_str,strlen(s._str)+1,s._str);
       }
       return *this;
   }
   ```

   

## 4. 内存管理

#### 4.1 结构体内存对齐问题

> https://zhuanlan.zhihu.com/p/30007037

字节对齐的原因：尽管内存是以字节为单位的，但大部分处理器并不是按照字节块来存取内存的。一般会以双字节、四字节、8、16等来存取内存

结构体大小计算方法：

>  有效对其值：是给定值**#pragma pack(n)**和结构体中**最长数据类型长度**中较小的那个。有效对齐值也叫**对齐单位**。

* 结构体第一个成员的**偏移量（offset）**为0，以后每个成员相对于结构体首地址的 offset 都是**该成员大小与有效对齐值中较小那个**的整数倍，如有需要编译器会在成员之间加上填充字节。
* **结构体的总大小**为 有效对齐值 的**整数倍**，如有需要编译器会在最末一个成员之后加上填充字节。



#### 4.2 类的大小

> https://zhuanlan.zhihu.com/p/105779156

* 空类为1字节
* 一般类按字节对齐来算字节，如果类只有普通函数，没有数据成员，那么还是1
* 有虚函数的要算上一个虚表指针，在64位机器上指针占8字节
* 对于子类问题



#### 4.3 栈溢出

在Windows下，栈的大小是2M(也有的说是1M，总之是一个编译时就确定的常数)，如果申请的空间超过了栈的剩余空间时，将提示内存溢出。

> 栈溢出的原因有很多，比如无限递归，死循环，或者定义的局部变量过大













## 5. 设计模式

* 单例设计模式 https://blog.csdn.net/chenxun_2010/article/details/48273723
