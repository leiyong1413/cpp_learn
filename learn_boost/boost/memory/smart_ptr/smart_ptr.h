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

namespace learn_boost {

	struct posix_file {
		posix_file(const char * file_name) {
			std::cout << "open file" << file_name << std::endl;
		}

		~posix_file() {
			std::cout << "close file" << std::endl;
		}
	};

	// 低精度计时器
	class SmartPtr : public IRunUseCase {
	public:
		virtual std::string Description() const override;
		virtual void Run() override;
	private:
		void RAII();
		void ScopedPtr();
		void ScopedArray();
		void SharedPtr();
	};

} // namespace learn_boost

#endif // LEARN_BOOST_MEMORY_SMART_PRT_H__