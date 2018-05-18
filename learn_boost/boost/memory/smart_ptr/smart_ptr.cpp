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

#pragma region 应用于工厂模式
		// 1.工厂模式中 new是最常见的，通常会分配一个对象，然后返回对象的指针
		// 但是这是一个很不安全的做法
		// 怎么改造：返回一个shared_ptr 包装的智能指针

		{
			SimpleFactory sf;
			auto ret_sp = SimpleFactory::create();
			if (ret_sp) {
				ret_sp->f1();
				ret_sp->f2();
			}

			// AbstractInterface 析构函数是保护的，所以用户不能做任何对指针的破坏
			// 即使使用ret_sp.get() 获取了原始指针
			AbstractInterface *org_p = ret_sp.get();
			// 下面代码在编译不过
			// 因为org_p 析构函数是保护的
			// delete org_p;
		}
#pragma endregion

#pragma region 指针转型函数
		// 当我们使用智能指针时，如果需要进行类层次上的上下行转换时，
		// 可以使用boost::static_pointer_cast和boost::dynamic_pointer_cast
		// 不同点：dynamic_cast在进行下行转换的时候（即基类到派生类）具有类型检查功能

		// 上行转换 （派生类到基类）
		boost::shared_ptr<ImpInterface> spImp;
		boost::shared_ptr<AbstractInterface> spInf;
		spImp = boost::make_shared<ImpInterface>();
		spInf = boost::static_pointer_cast<AbstractInterface>(spImp);
		// 执行base
		spInf->des();

		// 使用 boost::const_pointer_cast 普通转const


		// shared_ptr<void> 能够存储void* 型的指针， 因此shared_ptr<void> 能够容纳任意类型的能力

#pragma endregion

#pragma region SharedArray
		// 1. 包装 new[] 操作符在堆上分配的动态内存
		// 2. 引用计数实现, 直到没有任何引用才释放
		{
			SharedArray();
		}
#pragma endregion

#pragma region weakptr
		// 1. 为配合shared_ptr 引入的一种智能指针
		// 更像是shared_ptr的一种助手，因为它没有普通指针行为

		// 作用：观测shared_ptr 的使用情况
		{
			WeakPtr();
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

	void SmartPtr::SharedArray(){
		// 1. 构造函数必须是 new[] 的结果
		boost::shared_array<int> sa(new int[100]);
		// 判断是否唯一引用
		if (sa.unique()) {
			std::cout << " 唯一持有" << std::endl;
		}
		// 引用计数加1
		shared_array<int> sa2 = sa;

		// 不推荐 shared_array 使用 std::vector<shared_ptr> 代替
	}

	void SmartPtr::WeakPtr() {
		// 构造函数：参数是一个shared_ptr 对象 , 因为weak_ptr 没有共享资源，它的构造不会引起指针引用计数增加

		// 1. use_count() 得到 引用计数个数

		// 2. expired() 判断是否失效指针 即 use_count() == 0 ,表示 被观察资源已经不存在

		// 3. 没有 operator* 和 -> 不共享指针，不能操作资源 所以叫 "weak"


		// 1.通过 lock() 函数 获取一个可用的 shared_ptr对象
		// 如果 expired() == true 通过 lock() 得到一个存储空指针的 shared_ptr

		boost::shared_ptr<int> sp(new int(10));
		std::cout << "sp.use_count() == 1 " << sp.use_count() << std::endl;

		boost::weak_ptr<int> wp(sp);
		if (wp.use_count() == 1) {
			std::cout << "wp.use_count() == 1 " << "yes" << std::endl;
		}

		if (!wp.expired())
		{
			// sp 的引用计数加1
			shared_ptr<int> sp2 = wp.lock();
			*sp2 = 100;
			// sp 的引用计数加1 所以下面这里打印2
			std::cout << sp2.use_count() << std::endl;
		}

		// 上面sp2退出作用域 sp 的引用计数减1 所以这里是1
		std::cout << sp.use_count() << " " << *sp <<std::endl;

		// shared_ptr 失效
		sp.reset();

		// 判断是否失效
		if (wp.expired()) {
			if (nullptr == wp.lock()) {
				std::cout << "sp 失效 lock 获取值是nullptr " << std::endl;
			}
		}


		// weak_ptr 的一个重要用途:
		// 获得 this指针的 shared_ptr  , 使用对象能够生产shared_ptr 来管理自己
		// 实现中一种惯用法：enable_shared_from_this<T> 
		// 而不是通过 return this 这种方式
		boost::shared_ptr<self_shared> sp_s = boost::make_shared<self_shared>(100);
		// 引用计数1
		std::cout << sp_s.use_count() << std::endl;
		sp_s->print();
		
		// 获取sp_s 自己的指针 
		boost::shared_ptr<self_shared> sp_s_2 = sp_s->shared_from_this();
		// 上面代码引用计数加1 变为2
		std::cout << sp_s_2.use_count() << std::endl;
		sp_s_2->print();
	}
} // namespace learn_boost