#include "progress.h"

#include <iostream>

namespace learn_boost {

	std::string ProgressTimer::Description() const {
		std::string des = " [usecase][progress][progress_timer] ";
		return des;
	}

	void ProgressTimer::Run()
	{
		std::string des = Description();
		std::cout << des << " start " << std::endl;

		{
			// 声明一个计时器, 他在析构时会自动输出时间到stdout中，如果是控制台可以看到输出打印时间
			boost::progress_timer t;
			// progress_timer 继承了timer所有功能
			std::cout << " 测量的最大时间范围 elapsed_max " << t.elapsed_max() << " 单位秒 " << " 换算成小时 " << t.elapsed_max() / 3600 << std::endl;
			std::cout << " 时间精度 elapsed_min " << t.elapsed_min() << " 单位秒 " << " 结果是0.001 即1毫秒 " << std::endl;
			std::cout << " 接下来do something 然后 progress_timer 析构会自动输出时间 " << std::endl;
			// do something
			for (unsigned int i = 0; i < 10000; i++) {
				;
			}
		}


		std::cout << des << " end " << std::endl;
	}

} // namespace learn_boost