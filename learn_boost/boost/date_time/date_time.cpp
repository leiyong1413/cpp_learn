#include "date_time.h"

namespace learn_boost {

	std::string DateTimeGregorian::Description() const
	{
		std::string des = " [usecase][date_time][gregorian] ";
		return des;
	}
	void DateTimeGregorian::Run()
	{
		std::string des = Description();
		std::cout << des << " start " << std::endl;

#pragma region ���ڶ���
		{
			// ����һ����Ч���ڶ���
			boost::gregorian::date date_valid;
			// ����һ����Ч���ڶ��� ʹ��special_values 
			boost::gregorian::date not_a_date_time = boost::gregorian::date(boost::date_time::special_values::not_a_date_time);
			if (date_valid == not_a_date_time) {
				std::cout << " ����һ����Ч���ڶ��� " << std::endl;
			}

			// ʹ�������մ���,����·ݣ�������Ч���׳��쳣 
			// ��Ҫ�ж϶�Ӧ�����Ƿ���ڸ���
			// ��Ӧ���ꡢ���Ƿ���ڸ���
			boost::gregorian::date date_2000_11_30(2000, 11, 30);
			std::cout << date_2000_11_30.year() << ":" << date_2000_11_30.month() << ":" << date_2000_11_30.day() << std::endl;

			// �·ݿ���ʹ���·�ö��
			boost::gregorian::date date_2018_5_15(2018, boost::gregorian::May, 15);

			// ֧�ֿ�������
			boost::gregorian::date clone_date(date_2018_5_15);
			std::cout << clone_date.year() << ":" << clone_date.month() << ":" << clone_date.day() << std::endl;

			// ʹ���ַ�����ʽ����
			boost::gregorian::date date_by_str1 = boost::gregorian::from_simple_string("2010-May-15");
			boost::gregorian::date date_by_str2 = boost::gregorian::from_simple_string("2010-5-15");
			boost::gregorian::date date_by_ios_str = boost::gregorian::date_from_iso_string("20100515");

			// ע�⣺day_clock �ڲ�ʵ�֣�ʹ�� c ��׼�� localtime() ��gmtime() ��˽�������ϵͳ���õ�ʱ�������й�ϵ

			// �õ���ǰ���ڶ���
			boost::gregorian::date local_day = boost::gregorian::day_clock::local_day();
			std::cout << "day_clock::local_day() " << local_day.year() << "-" << local_day.month() << "-" << local_day.day() << std::endl;

			// �õ���ǰ���ڵ�UTC���ڶ���
			boost::gregorian::date utc_day = boost::gregorian::day_clock::universal_day();
			std::cout << "day_clock::universal_day() " << utc_day.year() << "-" << utc_day.month() << "-" << utc_day.day() << std::endl;

			// ����ʹ��special_values ���������������ڶ���
			// ����һ������������
			boost::gregorian::date neg_inf_date(boost::date_time::special_values::neg_infin);
			// ����һ������������
			boost::gregorian::date pos_inf_date(boost::date_time::special_values::pos_infin);
			// ����������� 9999-Dec-31
			boost::gregorian::date max_date(boost::date_time::special_values::max_date_time);
			// ������С���� 1400-Jan-01
			boost::gregorian::date min_date(boost::date_time::special_values::min_date_time);
			std::cout << "������С����" << min_date << " �������" << max_date << std::endl;
		}
#pragma endregion

#pragma region ��������
		{
			// ymd_type�ṹ a date split into components ������
			// struct
			//{
			// int year;
			// int month;
			// int day;
			//} ymd_type;
			boost::gregorian::date min_date = boost::gregorian::date(boost::gregorian::special_values::min_date_time);
			boost::gregorian::date::ymd_type ymd = min_date.year_month_day();
			std::cout << " �ṹymd_type " << ymd.year << ymd.month << ymd.day << std::endl;

			// �õ����ڵ�������Ŀ 0 ��ʾ������
			std::cout << " ���ڼ� " << min_date.day_of_week() << std::endl;
			// һ��ĵڶ��������366
			std::cout << " һ��ĵڶ�����" << min_date.day_of_year() << std::endl;

			// �ǵڶ����� ��Χ 0 - 53
			std::cout << " �ڼ���" << boost::gregorian::day_clock::local_day().week_number() << std::endl;

			boost::gregorian::date neg_inf_date(boost::date_time::special_values::neg_infin);
			// date �� is_xxx() ������ ��������Ƿ���һ����������
			std::cout << " ����Ƿ����������� " << neg_inf_date.is_neg_infinity() << std::endl;
		}
#pragma endregion

#pragma region ���ڵ����
		{
			boost::gregorian::date local_day = boost::gregorian::day_clock::local_day();
			std::cout << " ��date����ת����YYYY-mmm-DD��ʽ�ַ��� , mmm ��3����ĸ��Ӣ���·���" << boost::gregorian::to_simple_string(local_day) << std::endl;

			std::cout << " ��date����ת����YYYMMDD��ʽ�����ַ��� " << boost::gregorian::to_iso_string(local_day) << std::endl;
		}
#pragma endregion

#pragma region date ��c��׼�� tm�ṹ�໥ת��
		{
			std::cout << " date ת tm , tm_house, tm_min, tm_sec ����0" << std::endl;
			tm t = boost::gregorian::to_tm(boost::gregorian::day_clock::local_day());
			std::cout << t.tm_year << t.tm_mon << t.tm_mday << std::endl;
			// �����1970 00:00:00��ʼ��ʱ���
			printf("%d-%d-%d %d:%d:%d", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

			// tm ת date���� ֻʹ�������� tm_year tm_mon tm_mday ������Ա���������
			tm t2;
			t2.tm_year = 2018 - 1900;
			t2.tm_mon = 1 - 1;
			t2.tm_mday = 20;
			boost::gregorian::date t2d = boost::gregorian::date_from_tm(t2);
			std::cout << " tm ת date " << t2d << std::endl;
		}
#pragma endregion

#pragma region ���ڳ���
		// ���ڳ��ȣ�����Ϊ��λ�� ע�ⳤ��ֵ��һ�����������������ɸ�
		// ������ date_duration
		// 10��
		boost::gregorian::date_duration duration(10);

		//����ʱ��������
		std::cout << duration.days() << std::endl;
		// �ж��Ƿ�����ʱ��
		std::cout << "�Ƿ�����" << duration.is_special() << "�Ƿ�" << duration.is_negative() << std::endl;
		// date_duration һ������days ���õ�˵��������һ�������ļ���
		boost::gregorian::days d1(10), d2(-100), d3(255);

		// ��date_duration days ���Ƶ�ʱ��
		boost::gregorian::months m1(10);
		std::cout << "������" << m1.number_of_months() << std::endl;

#pragma endregion

#pragma region ���ڵļ���
		{
			// 1.֧�ּӼ�
			boost::gregorian::date d1(2000, 1, 1), d2(2018, 5, 15);
			// ����������
			std::cout << "�������" << d2 - d1 << std::endl;
			// ��duration ʱ�����
			d1 += days(10);
			std::cout << "����������" << d1 << std::endl;

			d1 += months(2);
			d1 -= years(10);
			std::cout << "�Ӽ� ���� �� �� ��" << d1 << std::endl;

		}
#pragma endregion

#pragma region ��������
		// 1.date_period ����ʾʱ������һ������ҿ����䣬�˵�������date����
		// ��� ����С���ұߣ���������Ч������
		{
			boost::gregorian::date_period dp1(boost::gregorian::date(2018,5, 17), days(20));
			if (!dp1.is_null()) {
				// ���������˵�
				std::cout << dp1.begin() << " " << dp1.last() << std::endl;
				// end() �͵�������end���ƣ�����last��ĵ�һ���date����
				std::cout << dp1.end() << std::endl;
				// length() �������� ����
				std::cout << dp1.length() << std::endl;
			}

			// ��� �����С �� ������Ч ����ʹ�� is_null() �ж�
			boost::gregorian::date_period dp2(boost::gregorian::date(2018, 5, 17), days(-20));
			if (dp2.is_null()) {
				std::cout << "��Ч��������" << std::endl;
			}

			// �ж������Ƿ���ĳ��date֮ǰ �� ֮��
			date_period dp3(date(2018, 5, 15), days(20));
			if (!dp3.is_null()) {
				std::cout << " " << dp3.is_before(date(2019, 5, 1)) << std::endl;
			}
		}
#pragma endregion

#pragma region ���ڵ�����
		// ʹ�ü򵥵ĵ������ݼ�����������date
		// day_iterator
		// week_iterator
		// month_iterator
		// year_iterator
		// �������൱��һ��date�����ָ�룬��ʹ��*��ȡ��������ǰdate����
		{
			boost::gregorian::date d1(2006, 11, 26);
			boost::gregorian::day_iterator d_iter(d1); // Ĭ�ϲ���1
			++d_iter; // ����һ��
			std::cout << "" << *d_iter << std::endl;

			boost::gregorian::year_iterator(d1, 8);	// ��������8��


			date d_start(d1.year(), d1.month(), 1); // ���µ�һ��
			date d_end = d1.end_of_month();	// �������һ��
			// ����ÿһ��
			for (day_iterator d_iter(d_start); d_iter != d_end; ++d_iter) {
				std::cout << *d_iter << " " << d_iter->day_of_week() << std::endl;
			}
		}


#pragma endregion




		std::cout << des << " end " << std::endl;
	}	

	std::string DateTimePosixtime::Description() const
	{
		std::string des = " [usecase][date_time][posixtime] ";
		return des;
	}
	void DateTimePosixtime::Run()
	{
		std::string des = Description();
		std::cout << des << " start " << std::endl;
		// 1.���ȿ��Դﵽ����
#pragma region ʱ�䳤��
		// ʹ��time_duration ����ʱ�䳤�� Ĭ�Ͼ�ȷ��΢��
		// �޸ĺ�BOOST_DATE_TIEM_POSIX_TIME_STD_CONFIG �����Ծ�ȷ������
		// time_duration ��һЩ���� �� houses minutes seconds milliseconds micorseconds nanoseconds
		
		// 
		boost::posix_time::time_duration td(1, 10, 30, 1000);

		// ͨ�����ഴ��
		hours h(1);
		minutes m(10);
		seconds s(30);
		millisec ms(1);
		time_duration td1 = h + m + s + ms;

		// ͨ���ַ�����ʽ����
		time_duration td2 = boost::posix_time::duration_from_string("1:10:30:001");
		
		// �޸ľ���
//#define BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG // �������뾫��
//#include <boost/date_time/posix_time/posix_time.hpp>


		// ��μ�⵱ǰ����
		std::cout <<"��ǰʱ�䳤�ȵľ���" << td2.resolution() << std::endl;
		std::cout << "��ǰʱ�䳤�ȵľ��� С������λ�� ΢��6λ ����9λ " << td2.num_fractional_digits() << std::endl;
#pragma endregion

#pragma region ʱ���
		// 
		// ʱ������ ptime ���ں�ʱ��Ľ��
		// ���캯����ָ��date �� time_duration ���� ��ptime����һ�����ڼ��ϵ�ǰ��ʱ��ƫ����
		// ptimeʹ��64λ��΢��� 96λ�����뼶�𣩵������洢ʱ������
		
		{
			boost::posix_time::ptime pt(boost::gregorian::date(2018, 5, 15), boost::posix_time::time_duration(1, 10, 30, 1000));
			std::cout << "ptime" << pt << std::endl;

			// ʹ���ַ�����ʽ
			boost::posix_time::ptime pt1 = boost::posix_time::time_from_string("2014-6-8 01:00:00");
			std::cout << "ptime" << pt1 << std::endl;


			// ��ȡ��ǰʱ�� ʹ�� second_clock�� �뼶��
			ptime c_pt_s = boost::posix_time::second_clock::local_time();
			// UTC ʱ��
			ptime c_pt_s_utc = boost::posix_time::second_clock::universal_time();
			// ��ȡ��ǰʱ�� ʹ�� second_clock�� ΢�뼶��
			ptime c_pt_ms = boost::posix_time::microsec_clock::local_time();
			// ��������ֵ
			// ��Чʱ��
			ptime pt2(boost::posix_time::not_a_date_time);
			std::cout << "��Чʱ��" << pt2.is_not_a_date_time() << std::endl;
			// ������ʱ��
			ptime pt_pos_infin(boost::posix_time::pos_infin);
			std::cout << "�ж��Ƿ���һ������ʱ��" << pt_pos_infin.is_infinity() << pt_pos_infin.is_special() << std::endl;

			// ��ptime�Ĳ���
			// ʱ��� ���� 2018-May-17
			std::cout << c_pt_ms.date() << std::endl;
			// ʱ��� ʱ�䳤�� 14:52:03.3587935
			std::cout << c_pt_ms.time_of_day() << std::endl;
			
			// ptime ת�ַ���
			std::cout << "ptime to string" << boost::posix_time::to_simple_string(c_pt_ms) << std::endl;

		}
#pragma endregion

#pragma region ʱ������
		// ������date_period ʹ��time_period ʹ��ptime��Ϊ����������˵㣬���ұ�
		// begin() last() ���������˵�
		// length() �������䳤��
		{
			ptime p(date(2014, 1, 1), hours(12));
			time_period tp1(p, hours(8));	// 8Сʱ����
			time_period tp2(p + hours(8), hours(1)); // 1Сʱ����

		}
#pragma endregion

#pragma region ʱ�������
		// time_iterator ʱ�������
		// 
		ptime p(date(2018, 5, 17), hours(10));
		// 10 ���ӵ���һ��
		for (time_iterator t_iter(p, minutes(10)); t_iter < p + hours(1); ++t_iter) {
			std::cout << *t_iter << t_iter->time_of_day() << std::endl;
		}
#pragma endregion



		std::cout << des << " end " << std::endl;
	}



} // namespace learn_boost