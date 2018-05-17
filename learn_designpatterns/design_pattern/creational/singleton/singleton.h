#ifndef LEARN_DESIGN_PATTERN_CREATIONAL_SINGLETON_SINGLETON_H__
#define LEARN_DESIGN_PATTERN_CREATIONAL_SINGLETON_SINGLETON_H__

#include <iostream>
#include <mutex>

namespace learn {
	namespace design_pattern {
		namespace creational {

			// 懒汉实现：故名思义，不到万不得已就不会去实例化类，也就是说在第一次用到类实例的时候才会去实例化
			// 非线程安全,两个线程同时首次调用Instance方法且同时检测到p是NULL值，则两个线程会同时构造一个实例给p
			class Singleton {
			public:
				// 普通函数命名：
				// 大写单词开头
				static Singleton* Instance();

				// 存储函数命名，取：同变量名， 存：函数名set_varname
				// 短小的存取函数可用内联
				int num_student() const {
					return num_student_;
				}
				
				void set_num_student(const int num_student) {
					num_student_ = num_student;
				}

				int age() const {
					return age_;
				}

				void set_age(const int age) {
					age_ = age;
				}
			protected:
				// singleton 不可以实列化，构造函数声明为protected 或 private
				Singleton();
			private:
				// 变量命令规则：全小写，有意义的单词和下划线
				// 类成员变量下划线结尾
				static Singleton* instance_;

				int num_student_;
				int age_;
			};

			// 饿汉实现，饿了肯定要饥不择食。所以在单例类定义的时候就进行实例化
			// 线程安全
			class SingletonReference {
			public:
				// 使用引用
				static SingletonReference& Instance() {
					static SingletonReference instance;
					return instance;
				}
			private:
				// C++11标准引入了一个新特性：defaulted函数。
				// 只需在函数声明后加上”=default;”，就可将该函数声明为defaulted函数，编译器将为显式声明的defaulted函数自动生成函数体
				// defaulted函数特性仅适用于类的特殊成员函数，且该特殊成员函数没有默认参数
				SingletonReference() = default;
				~SingletonReference() = default;

				// c++11标准引入新特性：明确表达虽然声明了某函数，但是又禁止它们被使用的意思
				// 禁止生成该函数，拷贝构造
				SingletonReference(const SingletonReference&) = delete;
				// 禁止生成该函数，赋值运算符
				SingletonReference& operator=(const SingletonReference&) = delete;
			};

			// 普通的懒汉和饿汉方式，比较？
			// 饿汉：要进行线程同步，所以在访问量比较大，或者可能访问的线程比较多时，采用饿汉实现，可以实现更好的性能(空间换时间)
			// 因为静态实例初始化在程序开始时进入主函数之前就由主线程以单线程方式完成了初始化，所以线程安全
			// 懒汉：在访问量较小时，采用懒汉实现。这是以时间换空间

			// 线程安全的实现
			// 1.加锁
			class SingletonWithLock{
			public:
				static SingletonWithLock* Instance();
			protected:
				SingletonWithLock();
			private:
				// 注意 类静态成员变量必须在类外初始化
				// 所以必须在cpp中初始化
				static SingletonWithLock* instance_;
			};

		} // namespace creational
	} // namespace design_pattern
} // namespace learn

#endif // LEARN_DESIGN_PATTERN_CREATIONAL_SINGLETON_SINGLETON_H__