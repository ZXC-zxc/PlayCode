// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <assert.h>
#include <memory>

using namespace std;

class BaseToken {

public:
	virtual ~BaseToken() {};

};

class JubiterBld : public BaseToken {

};

class JubiterBio : public JubiterBld {

public:
	bool isBio = { true };
	explicit operator JubiterBio* () const {
		if (isBio) return  const_cast<JubiterBio*>(this);
		return nullptr;
	}

	explicit operator JubiterBld* () const {
		return  dynamic_cast<JubiterBld*>(const_cast<JubiterBio*>(this));
	}
};

template <class T>
class MyPointer : public shared_ptr<T> {

public:
	using shared_ptr<T>::shared_ptr;

	template <class To, class Self>
	shared_ptr<To> check_cast() {
		Self* imp = dynamic_cast<Self*>(this->get());
		if (imp == nullptr) return nullptr;

		To* to = static_cast<To*>(*imp);
		if (to == nullptr) return nullptr;

		return std::dynamic_pointer_cast<To>(*this);
	}

};

int main()
{
	//模拟enum接口转成基类指针存起来
	MyPointer<BaseToken> base = std::make_shared<JubiterBio>();

	//模拟connect接口修改状态。当前不是一个bio设备
	{
		std::shared_ptr<JubiterBio> bio = base.check_cast<JubiterBio, JubiterBio>();
		assert(bio != nullptr);
		bio->isBio = false;
	}

	//模拟trans接口读取token指针，只能取出JubiterBld指针，不能取出JubiterBio指针，虽然他确实是一个JubiterBio指针
	{
		std::shared_ptr<JubiterBld> bld = base.check_cast<JubiterBld, JubiterBio>();
		std::shared_ptr<JubiterBio> bio = base.check_cast<JubiterBio, JubiterBio>();

		assert(bld != nullptr);
		assert(bio == nullptr);
	}

	//使用裸指针的时候
	{
		BaseToken* base = new JubiterBio();
		JubiterBio* bio1 = dynamic_cast<JubiterBio*>(base);
		assert(bio1 != nullptr);


		//只能用static_cast ， dynamic_cast直接走内存转换，不走自定义的cast operator
		bio1->isBio = false;
		JubiterBld* bld = static_cast<JubiterBld*>(*bio1);
		JubiterBio* bio2 = static_cast<JubiterBio*>(*bio1);

		assert(bld != nullptr);
		assert(bio2 == nullptr);

		delete base;
	}
	cout << "Hello CMake." << endl;
	return 0;
}

