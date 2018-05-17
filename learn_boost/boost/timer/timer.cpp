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
		
		boost::timer t; // ����һ����ʱ��
		std::cout << " ���������ʱ�䷶Χ elapsed_max " << t.elapsed_max() << " ��λ�� " << " �����Сʱ " << t.elapsed_max() / 3600 << std::endl;
		std::cout << " ʱ�侫�� elapsed_min " << t.elapsed_min() << " ��λ�� " << " �����0.001 ��1���� " << std::endl;
		std::cout << " �Ѿ���ʧ��ʱ�� elapsed,����ͨ����ֵ������������еĺ�ʱ " << t.elapsed() << " ��λ�� " << std::endl;


		std::cout << des << " end " << std::endl;
	}

} // namespace learn_boost