#ifndef LEARNDESIGNPATTERN_CREATIONAL_CREATIONAL_H__
#define LEARNDESIGNPATTERN_CREATIONAL_CREATIONAL_H__

namespace learn_design_pattern {

	// �����ͣ��������Ĳ���
	// �����ͳ��������ʵ�������̣���װ����Ĵ�������

	// ���󹤳���abstract factory
	// 1.����Ĵ�����װ��һ�����У������Ψһ������ǰ����������ֶ���
	// ͨ����������ķ�ʽ����������ͬϵ�еġ����׵Ķ���
	// 2. �������ǵ���, ��֤ϵͳȫ�ֿ��Է���
	// 3. �������ÿ�������ǹ���������

	// �򵥹�����simple factory 
	// ���󹤳��˻���һ��û������ļ򵥹���

	// ����������factory method
	// 1.�Ѷ���Ĵ�����װ��һ�������У�������Ըı乤��������������Ϊ������ͬ�Ķ���
	// boost �е� make_shared() make_optional() make_tuple() �Ⱥ������ǹ�������ģʽ


	// ԭ��ģʽ��prototype
	// 1.ʹ�����ʵ��ͨ�������ķ�ʽ�������󣬾���Ŀ�����Ϊ���Զ���
	// ����ķ�ʽ��ʵ��һ��clone()����
	// boost�е� enable_shared_from_this ������һ��ԭ��ģʽ������һ��ָ�������shared_ptr


	// ����ģʽ�� singleton
	// 1. ��֤һ�������ҽ���һ��ʵ�У��ṩһ��ȫ�ַ��ʵ㡣
	// boost �� serialization �����ṩ��һ�����õ�ʵ��

	// ������: builder
	// 1. �ֽ⸴�Ӷ���Ĵ������̣��������̿��Ա�����ı䣬ʹͬ���Ĺ��̿�����������ͬ�Ķ���
	// 2. �빤��ģʽ�Ĳ�ͬ�� ����һ���ԵĴ�������Ʒ�� ���Ƿֲ���װ���������˿��ԶԴ������̸���ϸ�Ŀ���

} // namespace learn_design_pattern

#endif // LEARNDESIGNPATTERN_CREATIONAL_CREATIONAL_H__