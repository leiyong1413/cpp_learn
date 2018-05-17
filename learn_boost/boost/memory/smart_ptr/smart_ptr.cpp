#include "smart_ptr.h"

#include <iostream>
#include <string>
#include <vector>

namespace learn_boost {

	std::string SmartPtr::Description() const {
		std::string des = " [usecase][memory][smart_ptr]";
		return des;
	}

	void SmartPtr::Run() {
		std::string des = Description();
		std::cout << des << " start " << std::endl;
#pragma region RAII����
		RAII();
#pragma endregion

#pragma region smartptr

		// 1. ����ָ�룬���������������뿪���쳣�뿪�����ǵ���delete�������ڶѣ�heap���϶�̬����Ķ���
		// 2. ����ָ�룬ͨ�����ģʽ-proxy ����ģʽ
		// 3. boost 6������ָ�� �쳣��ȫ��exception safe��
#pragma endregion

#pragma region scoped_ptr
		// 1. ��װ��new�������ڶ��Ϸ���Ķ�̬�����ܹ���֤��̬�����Ķ������κ�ʱ�򶼿��Ա���ȷ��ɾ��
		// 2. scoped_ptr������Ȩ�����ϸ񣬲���ת�ã�һ��scoped_pstr��ȡ�˶���Ĺ���Ȩ������޷��ٴ�������ȡ����
		// 3. �������ָ��ֻ������������ʹ�ã���ϣ����ת��
		ScopedPtr();
#pragma endregion

#pragma region scoped_array
		// 1. ��װ��new[]���� �ڶ��Ϸ��䶯̬����
		ScopedArray();
#pragma endregion


#pragma region shared_ptr
		// 1.shared_ptr ����ָ��ġ�����ָ��" ��scoped_ptr һ����װ��new�ڶ��Ϸ���Ķ�̬����
		// ��ͬ���ǣ����������ü��������Կ����͸�ֵ������
		// �����ü���Ϊ0�ǲ�ɾ������װ�Ķ�̬�������
		SharedPtr();
#pragma endregion

#pragma region ʹ�ù�������������ʽnew
		// �ڴ���scoped_ptr �� shared_ptr �� ���� ��ʽnew����Ϊ
		// ʹ��smart_ptr �Ĺ��� boost::make_shared() ��������
		// ͨ��make_shared �� new��ʽ����Ч

		// make_shared ���������ǿɱ�ģ�����������
		// make_shared���� ����һ��shared_ptr<T> ���󲢷���
		{
			auto sp = boost::make_shared<std::string>("make_shared");
			auto spv = boost::make_shared<std::vector<int> >(10, 20);
		}
#pragma endregion


#pragma region ����ָ��Ӧ���ڱ�׼����

		{
			// 1. ������ ��Ϊ shared_ptr����Ķ���
			auto spv = boost::make_shared<std::vector<std::string> >();

			// 2. �� shared_ptr ��Ϊ������Ԫ�� ����Ϊshared_ptr ֧�ֿ����ͱȽ�
			// ���Կ����������а�ȫ������Ԫ�ص�ָ��
			
			// 3. ��Ϊscoped_ptr ���ܿ����͸�ֵ�����Բ�����Ϊ������Ԫ��

			// ����һ��ӵ��10��Ԫ�ص�����
			std::vector<boost::shared_ptr<int> > vs(10);

			int i = 0;
			for (auto pos = vs.begin(); pos != vs.end(); ++pos) {
				(*pos) = boost::make_shared<int>(++i);
				std::cout << "" << *(*pos)<< ", ";
			}
			std::cout << std::endl;
			
			// ��ֵ
			boost::shared_ptr<int> p = vs[9];
			*p = 100;
			std::cout << *vs[9] << std::endl;


			// c++11 for ѭ��
			for (auto & ptr : vs) {	// ע����������ʽ
				std::cout << *ptr << ", ";
			}
			std::cout << std::endl;
		}

#pragma endregion






		std::cout << des << " end " << std::endl;
	}

	void SmartPtr::RAII() {
		// �������Դ�ڴ����ʽ,RAII(��Դ��ȡ����ʼ��)
		// 1.��ʹ����Դ�Ĺ��캯����������Դ
		// 2.Ȼ��ʹ��
		// 3.�������������ͷ���Դ

		// ���⣺�����Դ����ջ�ϴ���(һ���ֲ�����) RAII �������Զ��������������ͷ�
		// ʹ�� new �����ڶѣ�heap���ϣ������������������Զ����������������ֶ�����delete
		// ���delete δ��ȷִ�л�δִ�У���Դ�ڴ�й©

		// new delete ָ��Ĳ�Ǣ��ʹ�ö��������Դ��ȡ���ͷ�����

		auto p = new int; // ���󴴽�����ȡ��Դ
		{
			// ���ܷ����쳣����й©
		}
		delete p;	// �����ͷ���Դ
	}

	void SmartPtr::ScopedPtr()
	{
		// 2. ����ָ�� swap()

		// ���캯�� ����һ������ΪT*��ָ��p
		// ע��p ������new����Ľ�� �� ��ָ��
		
		int *org_i_ptr = new int(10);
		boost::scoped_ptr<int> s_i_ptr(org_i_ptr);

		// �����ŵ�д��,����¶ָ��
		boost::scoped_ptr<std::string> s_str_ptr(new std::string("test scoped ptr"));

		// scoped_ptr ������bool�ﾳ���Զ�ת����boolֵ
		// ������������scoped_ptr�Ƿ����һ����Ч��ָ�루�ǿգ�
		// ������nullָ��Ƚ�
		if (s_i_ptr) {
			// ����ָͨ��һ���Ĳ��� *T �õ�����
			std::cout << *s_i_ptr << std::endl;
		}

		// ע�� scoped_ptr ֻ֧���� c++11��nullptr NULL ��0 �Ƚ�
		// ��nullptr �Ƚ�
		if (s_str_ptr != nullptr) {
			// ʹ�� -> ����
			std::cout << "�ַ������� �ֽ� " << s_str_ptr->size() << std::endl;
		}

 		// 1. ��ȡscoped_ptr �ڲ������ԭʼָ�� get()
		// ��ԭʼָ������ scoped_ptr�Ŀ���
		// ע�ⲻ��ɾ����ָ�룬����scoped_ptr ����ʱ����Ѿ�ɾ����ָ����ɾ������
		// ����δ������Ϊ��ͨ��������
		int* org_pt = s_i_ptr.get();



		// Ϊʲô���ܱ�ת�ã�
		// scoped_ptr �ѿ������캯���͸�ֵ����������Ϊ˽�У�����������ֵ
		// �ܾ�������Ȩ��ת�ã�ֻ����scoped_ptr ����������������ʹ��
		// ����scoped_ptr ���������޷����ʱ������ָ�룬 ��ָ֤��ľ��԰�ȫ
		// ����������
		//boost::scoped_ptr<std::string> sp2 = s_str_ptr;		

		std::cout << "test scoped ptr start" << std::endl;
		{
			boost::scoped_ptr<posix_file> fp(new posix_file("/tmp/a.txt"));
			boost::scoped_ptr<int> p(new int);

			if (p) {
				*p = 100;
				std::cout << *p << std::endl;
			}
		}
		// ���Կ�������� �������д���ǰ���ӡ���½��
		// open file/tmp/a.txt
		// 100
		// close file
		// ���Կ���scoped_ptr������

		std::cout << "test scoped ptr end " << std::endl;
	}

	void SmartPtr::ScopedArray() {
		// 1. ���캯������ָ��p ������new[] �Ľ��
		boost::scoped_array<int> sa(new int[100]);

		// 2. �ṩoperator[] ���������أ��������±����
		sa[0] = 100;

		// 3. û��begin() end() �����������ĵ�������������
		// 4. û���ṩ����������Χ��飬���out of range �ᷢ��δ������Ϊ
		// ֻ��һ�� ���㡱����ӿڣ� Ӧ����ʹ�ã����Ƽ�
	}

	void SmartPtr::SharedPtr() {
		boost::shared_ptr<int> spi(new int);
		// bool �ﾳ�Զ�ת����boolֵ
		if (spi) {
			// ʹ�� �����ò�����*
			*spi = 123;
		}

		// �� scoped_ptr ��ͬ�ģ���ȫ���� ������������ֵ��ָ��Ƚ�

		// 1.����һ�����п�ָ���shared_ptr ����Ϊ��
		boost::shared_ptr<int> a_null_ptr;
		if (a_null_ptr == nullptr) {
			std::cout << "����һ���յ� shared_ptr" << std::endl;
		}

		// shared_ptr(Y *p) ����һ��ָ��T��ָ��p�Ĺ���Ȩ(Y ����ת����T)
		// ���ü�������Ϊ1
		boost::shared_ptr<int> not_a_null_ptr(new int);

		// �������� ���ü�����1
		// clone_ptr �� not_a_null_ptr ����һ��ָ��Ĺ���Ȩ
		boost::shared_ptr<int> clone_ptr(not_a_null_ptr);

		// ʹ��reset ���ü�����С1

		// ʹ��unique���� �ж�shared_ptr �Ƿ���ָ���Ψһ�����ߣ� true ��ʾΨһ
		// ������� ���0
		std::cout << not_a_null_ptr.unique() << std::endl;

		// �ṩ�Ȼ򲻵ȱȽ�
		// �������ڲ�ָ��ıȽ�
		if (not_a_null_ptr == clone_ptr) {
			std::cout << "����ͬһָ��" << std::endl;
		}
	}

} // namespace learn_boost