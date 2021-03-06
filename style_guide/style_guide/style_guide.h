#ifndef STYLEGUIDE_STYLEGUIDE_STYLEGUIDE_H_
#define STYLEGUIDE_STYLEGUIDE_STYLEGUIDE_H_

/// 1. 头文件 

// 1.1 #define 保护
// 所有头文件都应该使用 #define 来防止头文件被多重包含
// 命名格式当是: <PROJECT>_<PATH>_<FILE>_H_
// 头文件的命名应该基于所在项目源代码树的全路径(目录层级)

// 1.2 前置声明
// 尽可能地避免使用前置声明。使用 #include 包含需要的头文件即可
// 为什么？
//	1.2.1 前置声明隐藏了依赖关系，头文件改动时，用户的代码会跳过必要的重新编译过程
//  1.2.2 前置声明可能会被库的后续更改所破坏


// 1.3 内联函数
// 只有当函数只有 10 行甚至更少时才将其定义为内联函数

// 内联函数定义：当函数被声明为内联函数之后, 编译器会将其内联展开, 而不是按通常的函数调用机制进行调用.
// 优点: 只要内联的函数体较小, 内联该函数可以令目标代码更加高效. 对于存取函数以及其它函数体比较短, 性能关键的函数, 鼓励使用内联
// 缺点: 滥用内联将导致程序变得更慢.内联可能使目标代码量或增或减, 这取决于内联函数的大小

// 一个实用的经验准则: 内联那些包含循环或 switch 语句的函数常常是得不偿失 
// 有些函数即使声明为内联的也不一定会被编译器内联, 这点很重要; 比如虚函数和递归函数


// 1.4 #include 的路径及顺序
// 相关头文件, C 库, C++ 库, 其他库的 .h, 本项目内的 .h
// 项目内头文件应按照项目源代码目录树结构排列
// 避免使用 UNIX 特殊的快捷目录 . (当前目录) 或 .. (上级目录)
// 在 #include 中插入空行以分割相关头文件

// 相关头文件 ， 如 foo.cc 中 第一行 foo.h




/// 2. 命名空间 和作用域
// 1. 小写 无下划线
// 2. 在命名空间的最后注释出命名空间的名字
// 3. 命名空间中不#include 文件
// 4. 不要在头文件中使用 命名空间别名 除非显式标记内部命名空间使用 
namespace mynamesapce {
	// 相比单纯为了封装若干不共享任何静态数据的静态成员函数而创建类, 不如使用命名空间
	void Function1();
	void Function2();
} // namespace mynamesapce


// 局部变量
// 1. 将函数变量尽可能置于最小作用域内, 并在变量声明时进行初始化
// int j = g(); 
// vector<int> v = {1, 2}
// 2. 注意别在循环犯大量构造和析构的低级错误
// 如变量是一个对象， 在for while 等循环外声明提高效率

// 尽量不用全局函数和全局变量, 考虑作用域和命名空间限制, 尽量单独形成编译单元



/// 类
// 1.构造函数
// 不要在构造函数中调用虚函数
// 2.隐式类型转换
// 不要定义隐式类型转换.对于转换运算符和单参数构造函数, 请使用 explicit 关键字
// 什么是隐式类型转换：
// 隐式类型转换允许一个某种类型(称作 源类型) 的对象被用于需要另一种类型(称作 目的类型) 的位置, 例如, 将一个 int 类型的参数传递给需要 double 类型的函数
// explicit 关键字可以用于构造函数或 (在 C++11 引入) 类型转换运算符, 以保证只有当目的类型在调用点被显式写明时才能进行类型转换, 如cast
// 默认隐式类型转换
// 结论：在类型定义中, 类型转换运算符和单参数构造函数都应当用 explicit 进行标记


// 类与结构体
// 结论：仅当只有数据成员时使用 struct, 其它一概使用 class

// struct 用来定义包含数据的被动式对象, 也可以包含相关的常量, 但除了存取数据成员之外, 没有别的函数功能.
// 并且存取功能是通过直接访问 位域, 而非函数调用.
// 除了构造函数, 析构函数, Initialize(), Reset(), Validate() 等类似的用于设定数据成员的函数外, 不能提供其它功能的函数

// 继承
// 1.使用组合常常比使用继承更合理 (设计模式)
// 如果使用继承， 定义为public

// C++ 实践中, 继承主要用于两种场合: 实现继承, 子类继承父类的实现代码; 接口继承, 子类仅继承父类的方法名称
// 尽量做到只在 “是一个“的情况下使用继承
// 必要的话, 析构函数声明为 virtual 如果你的类有虚函数, 则析构函数也应该为虚函数
// 重载的虚函数或虚析构函数, 使用 override 显示标记


// 接口：接口是指满足特定条件的类, 这些类以 Interface 为后缀
// 纯接口：
// 只有纯虚函数 (“=0”) 和静态函数 (虚析构函数)
// 没有非静态数据成员
// 接口类不能被直接实例化, 因为它声明了纯虚函数
// 为确保接口类的所有实现可被正确销毁, 必须为之声明虚析构函数


// 存取控制
// 所有 数据成员声明为 private, 除非是 static const 类型成员
// 存取函数一般内联在头文件中


// 类中声明顺序：
// 类定义一般应以 public: 开始, 后跟 protected:, 最后是 private:.省略空部分
// 建议将类似的声明放在一起, 并且建议以如下的顺序: 类型 (包括 typedef, using 和嵌套的结构体与类), 常量, 工厂函数, 构造函数, 赋值运算符, 析构函数, 其它函数, 数据成员


// 不在构造函数中做太多逻辑相关的初始化
// 默认构造函数：编译器提供的默认构造函数不会对变量进行初始化如果定义了其他构造函数, 编译器不再提供, 需要编码者自行提供默认构造函数
// 为避免隐式转换, 需将单参数构造函数声明为 explicit
// 组合 > 实现继承 > 接口继承 > 私有继承, 子类重载的虚函数也要声明 virtual 关键字
// 避免使用多重继承
// 存取函数一般内联在头文件中
// 函数体尽量短小, 紧凑, 功能单一




/// 函数
// 1. 参数顺序
// 函数的参数顺序为: 输入参数在先, 后跟输出参数
// 输入参数通常是值参或 const 引用
// 

// 2. 编写简短函数 
// 如果函数超过 40 行, 可以思索一下能不能在不影响程序结构的前提下对其进行分割

// 3.引用参数
// 按引用传递的参数必须加上 const
// 输入参数是值参或 const 引用, 输出参数为指针.
// void Foo(const string &in, string *out)

// 4. 函数重载
// 若要使用函数重载, 则必须能让读者一看调用点就胸有成竹, 而不用花心思猜测调用的重载函数到底是哪一种. 这一规则也适用于构造函数
// 

// 5.  缺省参数
// 只允许在非虚函数中使用缺省参数, 且必须保证缺省参数的值始终一致
// 对于虚函数, 不允许使用缺省参数, 因为在虚函数中缺省参数不一定能正常工作

// 6. 函数返回类型后置语法
// 定义：C++ 现在允许两种不同的函数声明方式. 以往的写法是将返回类型置于函数名之前
// int foo(int x);
// C++11 引入了这一新的形式.现在可以在函数名前使用 auto 关键字, 在参数列表之后后置返回类型
// auto foo(int x) -> int;
// 后置返回类型为函数作用域


//6. 所有权与智能指针
// 动态分配出的对象最好有单一且固定的所有主, 并通过智能指针传递所有权
// 如果必须使用动态分配, 那么更倾向于将所有权保持在分配者手中. 如果其他地方要使用这个对象, 最好传递它的拷贝, 或者传递一个不用改变所有权的指针或引用. 倾向于使用 std::unique_ptr 来明确所有权传递
// std::unique_ptr<Foo> FooFactory();
// void FooConsumer(std::unique_ptr<Foo> ptr);
// 如果没有很好的理由, 则不要使用共享所有权
// 如果确实要使用共享所有权, 建议于使用 std::shared_ptr
// 不要使用 std::auto_ptr, 使用 std::unique_ptr 代替它


// 引用参数
// 所有按引用传递的参数必须加上 const
// 

// 类型转换
// 使用 C++ 的类型转换, 如 static_cast<>(). 不要使用 int y = (int)x 或 int y = int(x) 等转换方式
// 用 static_cast 替代 C 风格的值转换
// 用 const_cast 去掉 const 限定符
// 

// 流
// 只在记录日志时使用流. 流用来替代 printf() 和 scanf()
// 

// 前置自增和自减
// 对于迭代器和其他模板对象使用前缀形式 (++i) 的自增, 自减运算符
// 不考虑返回值的话, 前置自增 (++i) 通常要比后置自增 (i++) 效率更高

// 因为后置自增 (或自减) 需要对表达式的值 i 进行一次拷贝

// const 用法
// 任何可能的情况下都要使用 const
// 在声明的变量或参数前加上关键字 const 用于指明变量值不可被篡改



// c++11 constexpr用法 
// 在 C++11 里，用 constexpr 来定义真正的常量，或实现常量初始化


// 整型
// C++ 内建整型中, 仅使用 int. 如果程序中需要不同大小的变量, 可以使用 <stdint.h> 中长度精确的整型, 如 int16_t.如果您的变量可能不小于 2^31 (2GiB), 就用 64 位变量比如 int64_t.
// C++ 没有指定整型的大小. 通常人们假定 short 是 16 位, int 是 32 位, long 是 32 位, long long 是 64 位
// C++ 中整型大小因编译器和体系结构的不同而不同.
// 关于无符号整数:
// 使用断言来指出变量为非负数, 而不是使用无符号型
// 有些教科书都推荐使用无符号类型来表示非负数
// 但是, 在 C 语言中, 这一优点被由其导致的 bug 所淹没
// for (unsigned int i = foo.Length()-1; i >= 0; --i) 永远不会退出


// nullptr 和 NULL
// 整数用 0, 实数用 0.0, 指针用 nullptr 或 NULL, 字符 (串) 用 '\0'
// 对于指针 (地址值), 到底是用 0, NULL 还是 nullptr. C++11 项目用 nullptr; C++03 项目则用 NULL, 毕竟它看起来像指针。实际上，一些 C++ 编译器对 NULL 的定义比较特殊，可以输出有用的警告，特别是 sizeof(NULL) 就和 sizeof(0) 不一样
// 字符 (串) 用 '\0', 不仅类型正确而且可读性好

// sizeof
// 尽可能用 sizeof(varname) 代替 sizeof(type)
// 使用 sizeof(varname) 是因为当代码中变量类型改变时会自动更新
// Struct data;
// Struct data; memset(&data, 0, sizeof(data));


// auto
// 用 auto 绕过烦琐的类型名，只要可读性好就继续用，别用在局部变量之外的地方
// C++11 中，若变量被声明成 auto, 那它的类型就会被自动匹配成初始化表达式的类型


// Boost 库
// 只使用 Boost 中被认可的库



// 关于注释
// 用 // 或 /* */, 统一就好
// 但 // 更 常用

// 文件注释
// 在每一个文件开头加入版权公告

// 类注释
// 每个类的定义都要附带一份注释, 描述类的功能和用法, 除非它的功能相当明显.
// Returns an iterator for this table.  It is the client's
// responsibility to delete the iterator when it is done with it,
// and it must not use the iterator once the GargantuanTable object
// on which the iterator was created has been deleted.
// this mehtod is equivalent to :
//    Iterator* iter = table->NewIterator();
//    iter->Seek("");
//    return iter;


// 函数注释
// 函数声明处的注释描述函数功能; 定义处的注释描述函数实现
//函数声明处注释的内容:
//函数的输入输出.
//对类成员函数而言 : 函数调用期间对象是否需要保持引用参数, 是否会释放这些参数.
//	函数是否分配了必须由调用者释放的空间.
//	参数是否可以为空指针.
//	是否存在函数使用上的性能隐患.
//	如果函数是可重入的, 其同步前提是什么 ? 

// Returns true if the table cannot hold any more entries.
//bool IsTableFull();


// 变量注释
// 每个类数据成员 (也叫实例变量或成员变量) 都应该用注释说明用途
// // used to bounds-check table accesses
// int num_total_entries_;

// 全局变量注释
// 和数据成员一样, 所有全局变量也要注释说明含义及用途
// The total number of tests cases that we run through in this regression test.
// const int kNumTestCases = 6;

// 代码前注释
// 巧妙或复杂的代码段前要加注释

// 实现中，行注释
// 比较隐晦的地方要在行尾加入注释.在行尾空两格进行注释


// TODO 注释
// 对那些临时的, 短期的解决方案, 或已经够好但仍不完美的代码使用 TODO 注释


// 关于格式
// 行长度 每一行代码字符数不超过 80
// 非 ASCII 字符 尽量不使用非 ASCII 字符, 使用时必须使用 UTF-8 编码
// 空格还是制表位 只使用空格, 每次缩进 2 个空格
// 函数声明与定义 返回类型和函数名在同一行, 参数也尽量放在同一行, 如果放不下就对形参分行, 分行方式与 函数调用 一致
// 函数调用 要么一行写完函数调用, 要么在圆括号里对参数分行
// 条件语句 关键字 if 和 else 另起一行
//if (condition) {  // 圆括号里没有空格.
//	...  // 2 空格缩进.
//}
//else if (...) {  // else 与 if 的右括号同一行.
//	...
//}
//else {
//	...
//}

// 循环和开关选择语句
// switch 语句可以使用大括号分段
//switch (var) {
//case 0: {  // 2 空格缩进
//	...      // 4 空格缩进
//		break;
//}
//case 1: {
//	...
//		break;
//}
//default: {
//	assert(false);
//}
//}

// 函数返回值
//不要在 return 表达式里加上非必须的圆括号


// 命名空间格式化
// 命名空间内容不缩进

// Google 强调有一对 if-else 时, 不论有没有嵌套, 都要有大括号

// 不要使用匈牙利命名法 (比如把整型变量命名成 iNum)
// 不要使用 #pragma once; 而应该使用 Google 的头文件保护规则.
// 除非万不得已, 不要使用任何非标准的扩展, 如 #pragma 和 __declspec




// 命名规则
// 1.通用
// 函数命名, 变量命名, 文件命名要有描述性; 少用缩写 别心疼空间
//int price_count_reader;    // 无缩写
//int num_errors;            // "num" 是一个常见的写法
//int num_dns_connections;   // 人人都知道 "DNS" 是什么

// 文件命名
// 文件名要全部小写, 可以包含下划线 (_)  如果没有约定, 那么 “_” 更好
// C++ 文件要以 .cc 结尾, 头文件以 .h 结尾
// 通常应尽量让文件名更加明确.http_server_logs.h 就比 logs.h 要好
// 内联函数必须放在 .h 文件中.

// 类型命名
// 类型名称的每个单词首字母均大写, 不包含下划线: MyExcitingClass, MyExcitingEnum
// 类型
// typedef hash_map<UrlTableProperties *, string> PropertiesMap;
// 别名
// using PropertiesMap = hash_map<UrlTableProperties *, string>;

// 变量命名
// 变量 (包括函数参数) 和数据成员名一律小写, 单词之间用下划线连接 但结构体的就不用,
// 类的成员变量以下划线结尾
// a_local_variable
// a_struct_data_member
// a_class_data_member_

// 类数据成员
// 不管是静态的还是非静态的, 类数据成员都可以和普通变量一样, 但要接下划线
// string table_name_;
// static Pool<TableInfo>* pool_;

// 常量命名
// 声明为 constexpr 或 const 的变量, 或在程序运行期间其值始终保持不变的, 命名时以 “k” 开头, 大小写混合
// const int kDaysInAWeek = 7;
// 所有具有静态存储类型的变量 (例如静态变量或全局变量, 参见 存储类型) 都应当以此方式命名.


// 函数命名
// 常规函数使用大小写混合, 取值和设值函数则要求与变量名匹配
// MyExcitingFunction(), MyExcitingMethod(),  大写字母开头 一般来说, 函数名的每个单词首字母大写 (即 “驼峰变量名” 或 “帕斯卡变量名”), 没有下划线
// 对于首字母缩写的单词, 更倾向于将它们视作一个单词进行首字母大写 (例如, 写作 StartRpc() 而非 StartRPC())
// my_exciting_member_variable() 取值函数与变量名字匹配用小写加下划线方式
// set_my_exciting_member_variable() set开头

// 命名空间命名
// 命名空间以小写字母命名
// 最高级命名空间的名字取决于项目名称
// frobber_internal

// 枚举命名
// 枚举的命名应当和 常量 kEnumName 或是 ENUM_NAME
// 单独的枚举值应该优先采用 常量 的命名方式
// enum UrlTableErrors {
// kOK = 0,
// kErrorOutOfMemory,
// kErrorMalformedInput,
// };
// 2009 年 1 月之前, 我们一直建议采用 宏 的方式命名枚举值. 由于枚举值和宏之间的命名冲突, 直接导致了很多问题

// 宏定义
//  通常 不应该 使用宏. 如果不得不用, 其命名全部大写, 使用下划线
// #define PI_ROUNDED 3.0


#endif // STYLEGUIDE_STYLEGUIDE_STYLEGUIDE_H_