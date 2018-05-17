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

#pragma region 日期对象
		{
			// 创建一个无效日期对象
			boost::gregorian::date date_valid;
			// 创建一个无效日期对象 使用special_values 
			boost::gregorian::date not_a_date_time = boost::gregorian::date(boost::date_time::special_values::not_a_date_time);
			if (date_valid == not_a_date_time) {
				std::cout << " 创建一个无效日期对象 " << std::endl;
			}

			// 使用年月日创建,如果月份，日期无效会抛出异常 
			// 主要判断对应的年是否存在该月
			// 对应的年、月是否存在该日
			boost::gregorian::date date_2000_11_30(2000, 11, 30);
			std::cout << date_2000_11_30.year() << ":" << date_2000_11_30.month() << ":" << date_2000_11_30.day() << std::endl;

			// 月份可以使用月份枚举
			boost::gregorian::date date_2018_5_15(2018, boost::gregorian::May, 15);

			// 支持拷贝构造
			boost::gregorian::date clone_date(date_2018_5_15);
			std::cout << clone_date.year() << ":" << clone_date.month() << ":" << clone_date.day() << std::endl;

			// 使用字符串形式创建
			boost::gregorian::date date_by_str1 = boost::gregorian::from_simple_string("2010-May-15");
			boost::gregorian::date date_by_str2 = boost::gregorian::from_simple_string("2010-5-15");
			boost::gregorian::date date_by_ios_str = boost::gregorian::date_from_iso_string("20100515");

			// 注意：day_clock 内部实现，使用 c 标准库 localtime() 和gmtime() 因此结果与操作系统设置的时区设置有关系

			// 得到当前日期对象
			boost::gregorian::date local_day = boost::gregorian::day_clock::local_day();
			std::cout << "day_clock::local_day() " << local_day.year() << "-" << local_day.month() << "-" << local_day.day() << std::endl;

			// 得到当前日期的UTC日期对象
			boost::gregorian::date utc_day = boost::gregorian::day_clock::universal_day();
			std::cout << "day_clock::universal_day() " << utc_day.year() << "-" << utc_day.month() << "-" << utc_day.day() << std::endl;

			// 可以使用special_values 创建其他特殊日期对象
			// 创建一个负无限日期
			boost::gregorian::date neg_inf_date(boost::date_time::special_values::neg_infin);
			// 创建一个正无限日期
			boost::gregorian::date pos_inf_date(boost::date_time::special_values::pos_infin);
			// 创建最大日期 9999-Dec-31
			boost::gregorian::date max_date(boost::date_time::special_values::max_date_time);
			// 创建最小日期 1400-Jan-01
			boost::gregorian::date min_date(boost::date_time::special_values::min_date_time);
			std::cout << "创建最小日期" << min_date << " 最大日期" << max_date << std::endl;
		}
#pragma endregion

#pragma region 访问日期
		{
			// ymd_type结构 a date split into components 类似于
			// struct
			//{
			// int year;
			// int month;
			// int day;
			//} ymd_type;
			boost::gregorian::date min_date = boost::gregorian::date(boost::gregorian::special_values::min_date_time);
			boost::gregorian::date::ymd_type ymd = min_date.year_month_day();
			std::cout << " 结构ymd_type " << ymd.year << ymd.month << ymd.day << std::endl;

			// 得到日期的星期数目 0 表示星期天
			std::cout << " 星期几 " << min_date.day_of_week() << std::endl;
			// 一年的第多少天最多366
			std::cout << " 一年的第多少天" << min_date.day_of_year() << std::endl;

			// 是第多少周 范围 0 - 53
			std::cout << " 第几周" << boost::gregorian::day_clock::local_day().week_number() << std::endl;

			boost::gregorian::date neg_inf_date(boost::date_time::special_values::neg_infin);
			// date 的 is_xxx() 函数， 检测日期是否是一个特殊日期
			std::cout << " 检测是否是特殊日期 " << neg_inf_date.is_neg_infinity() << std::endl;
		}
#pragma endregion

#pragma region 日期的输出
		{
			boost::gregorian::date local_day = boost::gregorian::day_clock::local_day();
			std::cout << " 将date对象转换成YYYY-mmm-DD格式字符串 , mmm 是3个字母的英文月份名" << boost::gregorian::to_simple_string(local_day) << std::endl;

			std::cout << " 将date对象转换成YYYMMDD格式数字字符串 " << boost::gregorian::to_iso_string(local_day) << std::endl;
		}
#pragma endregion

#pragma region date 与c标准库 tm结构相互转换
		{
			std::cout << " date 转 tm , tm_house, tm_min, tm_sec 均置0" << std::endl;
			tm t = boost::gregorian::to_tm(boost::gregorian::day_clock::local_day());
			std::cout << t.tm_year << t.tm_mon << t.tm_mday << std::endl;
			// 相对于1970 00:00:00开始的时间戳
			printf("%d-%d-%d %d:%d:%d", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

			// tm 转 date对象 只使用年月日 tm_year tm_mon tm_mday 三个成员，其余忽略
			tm t2;
			t2.tm_year = 2018 - 1900;
			t2.tm_mon = 1 - 1;
			t2.tm_mday = 20;
			boost::gregorian::date t2d = boost::gregorian::date_from_tm(t2);
			std::cout << " tm 转 date " << t2d << std::endl;
		}
#pragma endregion

#pragma region 日期长度
		// 日期长度，以天为单位， 注意长度值是一个任意整数，可正可负
		// 长度类 date_duration
		// 10天
		boost::gregorian::date_duration duration(10);

		//返回时长的天数
		std::cout << duration.days() << std::endl;
		// 判断是否特殊时长
		std::cout << "是否特殊" << duration.is_special() << "是否负" << duration.is_negative() << std::endl;
		// date_duration 一个别名days 更好的说明了他是一个天数的计量
		boost::gregorian::days d1(10), d2(-100), d3(255);

		// 与date_duration days 类似的时常
		boost::gregorian::months m1(10);
		std::cout << "几个月" << m1.number_of_months() << std::endl;

#pragma endregion

#pragma region 日期的计算
		{
			// 1.支持加减
			boost::gregorian::date d1(2000, 1, 1), d2(2018, 5, 15);
			// 计算间隔天数
			std::cout << "间隔天数" << d2 - d1 << std::endl;
			// 与duration 时常配合
			d1 += days(10);
			std::cout << "增加天数后" << d1 << std::endl;

			d1 += months(2);
			d1 -= years(10);
			std::cout << "加减 天数 月 年 后" << d1 << std::endl;

		}
#pragma endregion

#pragma region 日期区间
		// 1.date_period ，表示时间轴上一个左闭右开区间，端点是两个date对象
		// 左边 必须小于右边，否在是无效的区间
		{
			boost::gregorian::date_period dp1(boost::gregorian::date(2018,5, 17), days(20));
			if (!dp1.is_null()) {
				// 返回两个端点
				std::cout << dp1.begin() << " " << dp1.last() << std::endl;
				// end() 和迭代器的end类似，返回last后的第一天的date对象
				std::cout << dp1.end() << std::endl;
				// length() 返回区间 天数
				std::cout << dp1.length() << std::endl;
			}

			// 如果 左大右小 则 区间无效 可以使用 is_null() 判断
			boost::gregorian::date_period dp2(boost::gregorian::date(2018, 5, 17), days(-20));
			if (dp2.is_null()) {
				std::cout << "无效日期区间" << std::endl;
			}

			// 判断区间是否在某个date之前 或 之后
			date_period dp3(date(2018, 5, 15), days(20));
			if (!dp3.is_null()) {
				std::cout << " " << dp3.is_before(date(2019, 5, 1)) << std::endl;
			}
		}
#pragma endregion

#pragma region 日期迭代器
		// 使用简单的递增、递减操作连续的date
		// day_iterator
		// week_iterator
		// month_iterator
		// year_iterator
		// 迭代器相当于一个date对象的指针，可使用*获取迭代器当前date对象
		{
			boost::gregorian::date d1(2006, 11, 26);
			boost::gregorian::day_iterator d_iter(d1); // 默认步长1
			++d_iter; // 递增一天
			std::cout << "" << *d_iter << std::endl;

			boost::gregorian::year_iterator(d1, 8);	// 递增步长8年


			date d_start(d1.year(), d1.month(), 1); // 当月第一天
			date d_end = d1.end_of_month();	// 当月最后一天
			// 遍历每一天
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
		// 1.精度可以达到纳秒
#pragma region 时间长度
		// 使用time_duration 处理时间长度 默认精确到微秒
		// 修改宏BOOST_DATE_TIEM_POSIX_TIME_STD_CONFIG ，可以精确到纳秒
		// time_duration 有一些子类 如 houses minutes seconds milliseconds micorseconds nanoseconds
		
		// 
		boost::posix_time::time_duration td(1, 10, 30, 1000);

		// 通过子类创建
		hours h(1);
		minutes m(10);
		seconds s(30);
		millisec ms(1);
		time_duration td1 = h + m + s + ms;

		// 通过字符串格式创建
		time_duration td2 = boost::posix_time::duration_from_string("1:10:30:001");
		
		// 修改精度
//#define BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG // 定义纳秒精度
//#include <boost/date_time/posix_time/posix_time.hpp>


		// 如何检测当前精度
		std::cout <<"当前时间长度的精度" << td2.resolution() << std::endl;
		std::cout << "当前时间长度的精度 小数部分位数 微妙6位 纳秒9位 " << td2.num_fractional_digits() << std::endl;
#pragma endregion

#pragma region 时间点
		// 
		// 时间点对象 ptime 日期和时间的结合
		// 构造函数中指定date 和 time_duration 对象， 让ptime等于一个日期加上当前的时间偏移量
		// ptime使用64位（微妙级别） 96位（纳秒级别）的整数存储时间数据
		
		{
			boost::posix_time::ptime pt(boost::gregorian::date(2018, 5, 15), boost::posix_time::time_duration(1, 10, 30, 1000));
			std::cout << "ptime" << pt << std::endl;

			// 使用字符串格式
			boost::posix_time::ptime pt1 = boost::posix_time::time_from_string("2014-6-8 01:00:00");
			std::cout << "ptime" << pt1 << std::endl;


			// 获取当前时间 使用 second_clock类 秒级别
			ptime c_pt_s = boost::posix_time::second_clock::local_time();
			// UTC 时间
			ptime c_pt_s_utc = boost::posix_time::second_clock::universal_time();
			// 获取当前时间 使用 second_clock类 微秒级别
			ptime c_pt_ms = boost::posix_time::microsec_clock::local_time();
			// 构造特殊值
			// 无效时间
			ptime pt2(boost::posix_time::not_a_date_time);
			std::cout << "无效时间" << pt2.is_not_a_date_time() << std::endl;
			// 正无限时间
			ptime pt_pos_infin(boost::posix_time::pos_infin);
			std::cout << "判断是否是一个特殊时间" << pt_pos_infin.is_infinity() << pt_pos_infin.is_special() << std::endl;

			// 对ptime的操作
			// 时间点 日期 2018-May-17
			std::cout << c_pt_ms.date() << std::endl;
			// 时间点 时间长度 14:52:03.3587935
			std::cout << c_pt_ms.time_of_day() << std::endl;
			
			// ptime 转字符串
			std::cout << "ptime to string" << boost::posix_time::to_simple_string(c_pt_ms) << std::endl;

		}
#pragma endregion

#pragma region 时间区间
		// 类似于date_period 使用time_period 使用ptime作为区间的两个端点，左开右闭
		// begin() last() 返回两个端点
		// length() 返回区间长度
		{
			ptime p(date(2014, 1, 1), hours(12));
			time_period tp1(p, hours(8));	// 8小时区间
			time_period tp2(p + hours(8), hours(1)); // 1小时区间

		}
#pragma endregion

#pragma region 时间迭代器
		// time_iterator 时间迭代器
		// 
		ptime p(date(2018, 5, 17), hours(10));
		// 10 分钟迭代一次
		for (time_iterator t_iter(p, minutes(10)); t_iter < p + hours(1); ++t_iter) {
			std::cout << *t_iter << t_iter->time_of_day() << std::endl;
		}
#pragma endregion



		std::cout << des << " end " << std::endl;
	}



} // namespace learn_boost