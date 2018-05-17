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
			// ����һ����ʱ��, ��������ʱ���Զ����ʱ�䵽stdout�У�����ǿ���̨���Կ��������ӡʱ��
			boost::progress_timer t;
			// progress_timer �̳���timer���й���
			std::cout << " ���������ʱ�䷶Χ elapsed_max " << t.elapsed_max() << " ��λ�� " << " �����Сʱ " << t.elapsed_max() / 3600 << std::endl;
			std::cout << " ʱ�侫�� elapsed_min " << t.elapsed_min() << " ��λ�� " << " �����0.001 ��1���� " << std::endl;
			std::cout << " ������do something Ȼ�� progress_timer �������Զ����ʱ�� " << std::endl;
			// do something
			for (unsigned int i = 0; i < 10000; i++) {
				;
			}
		}


		std::cout << des << " end " << std::endl;
	}

} // namespace learn_boost