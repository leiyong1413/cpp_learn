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

#pragma region Ӧ���ڹ���ģʽ
		// 1.����ģʽ�� new������ģ�ͨ�������һ������Ȼ�󷵻ض����ָ��
		// ��������һ���ܲ���ȫ������
		// ��ô���죺����һ��shared_ptr ��װ������ָ��

		{
			SimpleFactory sf;
			auto ret_sp = SimpleFactory::create();
			if (ret_sp) {
				ret_sp->f1();
				ret_sp->f2();
			}

			// AbstractInterface ���������Ǳ����ģ������û��������κζ�ָ����ƻ�
			// ��ʹʹ��ret_sp.get() ��ȡ��ԭʼָ��
			AbstractInterface *org_p = ret_sp.get();
			// ��������ڱ��벻��
			// ��Ϊorg_p ���������Ǳ�����
			// delete org_p;
		}
#pragma endregion

#pragma region ָ��ת�ͺ���
		// ������ʹ������ָ��ʱ�������Ҫ���������ϵ�������ת��ʱ��
		// ����ʹ��boost::static_pointer_cast��boost::dynamic_pointer_cast
		// ��ͬ�㣺dynamic_cast�ڽ�������ת����ʱ�򣨼����ൽ�����ࣩ�������ͼ�鹦��

		// ����ת�� �������ൽ���ࣩ
		boost::shared_ptr<ImpInterface> spImp;
		boost::shared_ptr<AbstractInterface> spInf;
		spImp = boost::make_shared<ImpInterface>();
		spInf = boost::static_pointer_cast<AbstractInterface>(spImp);
		// ִ��base
		spInf->des();

		// ʹ�� boost::const_pointer_cast ��ͨתconst


		// shared_ptr<void> �ܹ��洢void* �͵�ָ�룬 ���shared_ptr<void> �ܹ������������͵�����

#pragma endregion

#pragma region SharedArray
		// 1. ��װ new[] �������ڶ��Ϸ���Ķ�̬�ڴ�
		// 2. ���ü���ʵ��, ֱ��û���κ����ò��ͷ�
		{
			SharedArray();
		}
#pragma endregion

#pragma region weakptr
		// 1. Ϊ���shared_ptr �����һ������ָ��
		// ������shared_ptr��һ�����֣���Ϊ��û����ָͨ����Ϊ

		// ���ã��۲�shared_ptr ��ʹ�����
		{
			WeakPtr();
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

	void SmartPtr::SharedArray(){
		// 1. ���캯�������� new[] �Ľ��
		boost::shared_array<int> sa(new int[100]);
		// �ж��Ƿ�Ψһ����
		if (sa.unique()) {
			std::cout << " Ψһ����" << std::endl;
		}
		// ���ü�����1
		shared_array<int> sa2 = sa;

		// ���Ƽ� shared_array ʹ�� std::vector<shared_ptr> ����
	}

	void SmartPtr::WeakPtr() {
		// ���캯����������һ��shared_ptr ���� , ��Ϊweak_ptr û�й�����Դ�����Ĺ��첻������ָ�����ü�������

		// 1. use_count() �õ� ���ü�������

		// 2. expired() �ж��Ƿ�ʧЧָ�� �� use_count() == 0 ,��ʾ ���۲���Դ�Ѿ�������

		// 3. û�� operator* �� -> ������ָ�룬���ܲ�����Դ ���Խ� "weak"


		// 1.ͨ�� lock() ���� ��ȡһ�����õ� shared_ptr����
		// ��� expired() == true ͨ�� lock() �õ�һ���洢��ָ��� shared_ptr

		boost::shared_ptr<int> sp(new int(10));
		std::cout << "sp.use_count() == 1 " << sp.use_count() << std::endl;

		boost::weak_ptr<int> wp(sp);
		if (wp.use_count() == 1) {
			std::cout << "wp.use_count() == 1 " << "yes" << std::endl;
		}

		if (!wp.expired())
		{
			// sp �����ü�����1
			shared_ptr<int> sp2 = wp.lock();
			*sp2 = 100;
			// sp �����ü�����1 �������������ӡ2
			std::cout << sp2.use_count() << std::endl;
		}

		// ����sp2�˳������� sp �����ü�����1 ����������1
		std::cout << sp.use_count() << " " << *sp <<std::endl;

		// shared_ptr ʧЧ
		sp.reset();

		// �ж��Ƿ�ʧЧ
		if (wp.expired()) {
			if (nullptr == wp.lock()) {
				std::cout << "sp ʧЧ lock ��ȡֵ��nullptr " << std::endl;
			}
		}


		// weak_ptr ��һ����Ҫ��;:
		// ��� thisָ��� shared_ptr  , ʹ�ö����ܹ�����shared_ptr �������Լ�
		// ʵ����һ�ֹ��÷���enable_shared_from_this<T> 
		// ������ͨ�� return this ���ַ�ʽ
		boost::shared_ptr<self_shared> sp_s = boost::make_shared<self_shared>(100);
		// ���ü���1
		std::cout << sp_s.use_count() << std::endl;
		sp_s->print();
		
		// ��ȡsp_s �Լ���ָ�� 
		boost::shared_ptr<self_shared> sp_s_2 = sp_s->shared_from_this();
		// ����������ü�����1 ��Ϊ2
		std::cout << sp_s_2.use_count() << std::endl;
		sp_s_2->print();
	}
} // namespace learn_boost