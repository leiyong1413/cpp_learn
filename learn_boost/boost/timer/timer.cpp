#include "timer.h"

#include <iostream>

namespace learn_boost {

	std::string Timer::Description() const {
		std::string des = " [usecase][timer][timer] ";
		return des;
	}

	void Timer::Run()
	{
		std::string des = Description();
		std::cout << des << " start " << std::endl;
		
		boost::timer t; // 声明一个计时器
		std::cout << " 测量的最大时间范围 elapsed_max " << t.elapsed_max() << " 单位秒 " << " 换算成小时 " << t.elapsed_max() / 3600 << std::endl;
		std::cout << " 时间精度 elapsed_min " << t.elapsed_min() << " 单位秒 " << " 结果是0.001 即1毫秒 " << std::endl;
		std::cout << " 已经流失的时间 elapsed,可以通过该值来计算程序运行的耗时 " << t.elapsed() << " 单位秒 " << std::endl;


		std::cout << des << " end " << std::endl;
	}

} // namespace learn_boost