/**
* 学习boost smart_ptr 库
*/
#ifndef LEARN_BOOST_MEMORY_SMART_PRT_H__
#define LEARN_BOOST_MEMORY_SMART_PRT_H__

#include "../../index.h"

#include <iostream>

// 头文件包含
#include <boost/smart_ptr.hpp>
using namespace boost;

// 惯用法
#include <boost/enable_shared_from_this.hpp>

namespace learn_boost {

	struct posix_file {
		posix_file(const char * file_name) {
			std::cout << "open file" << file_name << std::endl;
		}

		~posix_file() {
			std::cout << "close file" << std::endl;
		}
	};

	// 
	class AbstractInterface
	{
	public:
		virtual void f1() = 0;
		virtual void f2() = 0;

		virtual void des() {
			std::cout << "base" << std::endl;
		}
	protected:
		// c++ 11 default
		virtual ~AbstractInterface() = default;
	};

	class ImpInterface : public AbstractInterface
	{
	public:
		// c++ 11 default
		ImpInterface() = default;
		virtual ~ImpInterface() = default;
	public:
		// c++ 11 override
		virtual void f1() override {

		}

		virtual void f2() override {

		}


	};

	class SimpleFactory {
	public:
		// 使用shared_ptr 的简单工厂模式实现
		static shared_ptr<AbstractInterface> create() {
			return boost::make_shared<ImpInterface>();
		}
	};

	// 使用shared_ptr 自我管理的类
	class self_shared : public boost::enable_shared_from_this<self_shared>
	{
	public:
		self_shared(int n):x_(n){}
		void print() {
			std::cout << "self_shared:" << x_ << std::endl;
		}
	private:
		int x_;
	};


	// 智能指针
	class SmartPtr : public IRunUseCase {
	public:
		virtual std::string Description() const override;
		virtual void Run() override;
	private:
		void RAII();
		void ScopedPtr();
		void ScopedArray();
		void SharedPtr();
		void SharedArray();
		void WeakPtr();
	};

} // namespace learn_boost

#endif // LEARN_BOOST_MEMORY_SMART_PRT_H__