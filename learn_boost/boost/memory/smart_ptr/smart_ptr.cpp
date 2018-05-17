#include "smart_ptr.h"

#include <iostream>
#include <string>
#include <vector>

namespace learn_boost {

	std::string SmartPtr::Description() const {
		std::string des = " [usecase][memory][smart_ptr]";
		return des;
	}

	void SmartPtr::Run() {
		std::string des = Description();
		std::cout << des << " start " << std::endl;
#pragma region RAII机制
		RAII();
#pragma endregion

#pragma region smartptr

		// 1. 智能指针，不管是正常流程离开或异常离开，总是调用delete来析构在堆（heap）上动态分配的对象
		// 2. 智能指针，通过设计模式-proxy 代理模式
		// 3. boost 6中智能指针 异常安全（exception safe）
#pragma endregion

#pragma region scoped_ptr
		// 1. 包装了new操作符在堆上分配的动态对象，能够保证动态创建的对象在任何时候都可以被正确的删除
		// 2. scoped_ptr的所有权更加严格，不能转让，一旦scoped_pstr获取了对象的管理权，你就无法再从它那里取回来
		// 3. 这个智能指针只能在作用域里使用，不希望被转让
		ScopedPtr();
#pragma endregion

#pragma region scoped_array
		// 1. 包装了new[]操作 在堆上分配动态数组
		ScopedArray();
#pragma endregion


#pragma region shared_ptr
		// 1.shared_ptr 最像指针的“智能指针" 和scoped_ptr 一样包装了new在堆上分配的动态对象
		// 不同的是，它采用引用计数，可以拷贝和赋值，共享
		// 当引用计数为0是才删除被包装的动态分配对象
		SharedPtr();
#pragma endregion

#pragma region 使用工厂函数消除显式new
		// 在创建scoped_ptr 和 shared_ptr 中 存在 显式new的行为
		// 使用smart_ptr 的工厂 boost::make_shared() 工厂函数
		// 通常make_shared 比 new方式更高效

		// make_shared 函数参数是可变的，可以任意多个
		// make_shared函数 创建一个shared_ptr<T> 对象并返回
		{
			auto sp = boost::make_shared<std::string>("make_shared");
			auto spv = boost::make_shared<std::vector<int> >(10, 20);
		}
#pragma endregion


#pragma region 智能指针应用于标准容器

		{
			// 1. 将容器 作为 shared_ptr管理的对象
			auto spv = boost::make_shared<std::vector<std::string> >();

			// 2. 将 shared_ptr 作为容器的元素 ，因为shared_ptr 支持拷贝和比较
			// 所以可以在容器中安全的容纳元素的指针
			
			// 3. 因为scoped_ptr 不能拷贝和赋值，所以不能作为容器的元素

			// 声明一个拥有10个元素的容器
			std::vector<boost::shared_ptr<int> > vs(10);

			int i = 0;
			for (auto pos = vs.begin(); pos != vs.end(); ++pos) {
				(*pos) = boost::make_shared<int>(++i);
				std::cout << "" << *(*pos)<< ", ";
			}
			std::cout << std::endl;
			
			// 赋值
			boost::shared_ptr<int> p = vs[9];
			*p = 100;
			std::cout << *vs[9] << std::endl;


			// c++11 for 循环
			for (auto & ptr : vs) {	// 注意是引用形式
				std::cout << *ptr << ", ";
			}
			std::cout << std::endl;
		}

#pragma endregion






		std::cout << des << " end " << std::endl;
	}

	void SmartPtr::RAII() {
		// 最常见的资源内存管理方式,RAII(资源获取即初始化)
		// 1.在使用资源的构造函数中申请资源
		// 2.然后使用
		// 3.在析构函数中释放资源

		// 问题：如果资源是在栈上创建(一个局部变量) RAII 正常，自动调用析构函数释放
		// 使用 new 创建在堆（heap）上，它的析构函数不会自动调用析构，必须手动调用delete
		// 如果delete 未正确执行或未执行，资源内存泄漏

		// new delete 指针的不洽当使用都会造成资源获取、释放问题

		auto p = new int; // 对象创建，获取资源
		{
			// 可能发生异常导致泄漏
		}
		delete p;	// 析构释放资源
	}

	void SmartPtr::ScopedPtr()
	{
		// 2. 交换指针 swap()

		// 构造函数 接受一个类型为T*的指针p
		// 注意p 必须是new分配的结果 或 空指针
		
		int *org_i_ptr = new int(10);
		boost::scoped_ptr<int> s_i_ptr(org_i_ptr);

		// 更优雅的写法,不暴露指针
		boost::scoped_ptr<std::string> s_str_ptr(new std::string("test scoped ptr"));

		// scoped_ptr 可以在bool语境中自动转换成bool值
		// 可以用来测试scoped_ptr是否持有一个有效的指针（非空）
		// 代替与null指针比较
		if (s_i_ptr) {
			// 与普通指针一样的操作 *T 得到变量
			std::cout << *s_i_ptr << std::endl;
		}

		// 注意 scoped_ptr 只支持与 c++11的nullptr NULL 或0 比较
		// 与nullptr 比较
		if (s_str_ptr != nullptr) {
			// 使用 -> 操作
			std::cout << "字符串长度 字节 " << s_str_ptr->size() << std::endl;
		}

 		// 1. 获取scoped_ptr 内部保存的原始指针 get()
		// 让原始指针脱离 scoped_ptr的控制
		// 注意不能删除该指针，否则scoped_ptr 析构时会对已经删除的指针在删除操作
		// 发生未定义行为（通常崩溃）
		int* org_pt = s_i_ptr.get();



		// 为什么不能被转让？
		// scoped_ptr 把拷贝构造函数和赋值函数都声明为私有，不允许拷贝或赋值
		// 拒绝了所有权的转让，只能在scoped_ptr 被声明的作用域中使用
		// 除了scoped_ptr 其他对象都无法访问被管理的指针， 保证指针的绝对安全
		// 下面代码错误
		//boost::scoped_ptr<std::string> sp2 = s_str_ptr;		

		std::cout << "test scoped ptr start" << std::endl;
		{
			boost::scoped_ptr<posix_file> fp(new posix_file("/tmp/a.txt"));
			boost::scoped_ptr<int> p(new int);

			if (p) {
				*p = 100;
				std::cout << *p << std::endl;
			}
		}
		// 可以看到在输出 下面这行代码前会打印以下结果
		// open file/tmp/a.txt
		// 100
		// close file
		// 可以看出scoped_ptr的作用

		std::cout << "test scoped ptr end " << std::endl;
	}

	void SmartPtr::ScopedArray() {
		// 1. 构造函数接受指针p 必须是new[] 的结果
		boost::scoped_array<int> sa(new int[100]);

		// 2. 提供operator[] 操作符重载，可以用下标访问
		sa[0] = 100;

		// 3. 没有begin() end() 等类似容器的迭代器操作函数
		// 4. 没有提供数组索引范围检查，如果out of range 会发生未定义行为
		// 只是一个 “裸”数组接口， 应避免使用，不推荐
	}

	void SmartPtr::SharedPtr() {
		boost::shared_ptr<int> spi(new int);
		// bool 语境自动转换成bool值
		if (spi) {
			// 使用 解引用操作符*
			*spi = 123;
		}

		// 与 scoped_ptr 不同的：安全共享， 正常拷贝、赋值，指针比较

		// 1.创建一个持有空指针的shared_ptr 参数为空
		boost::shared_ptr<int> a_null_ptr;
		if (a_null_ptr == nullptr) {
			std::cout << "创建一个空的 shared_ptr" << std::endl;
		}

		// shared_ptr(Y *p) 创建一个指向T的指针p的管理权(Y 可以转换成T)
		// 引用计数设置为1
		boost::shared_ptr<int> not_a_null_ptr(new int);

		// 拷贝构造 引用计数加1
		// clone_ptr 和 not_a_null_ptr 共享一个指针的管理权
		boost::shared_ptr<int> clone_ptr(not_a_null_ptr);

		// 使用reset 引用计数减小1

		// 使用unique函数 判断shared_ptr 是否是指针的唯一所有者， true 表示唯一
		// 下面代码 输出0
		std::cout << not_a_null_ptr.unique() << std::endl;

		// 提供等或不等比较
		// 本质是内部指针的比较
		if (not_a_null_ptr == clone_ptr) {
			std::cout << "管理同一指针" << std::endl;
		}
	}

} // namespace learn_boost