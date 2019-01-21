// constructorCompare.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>

using namespace std;

struct Data {
	static constexpr int ItemSize = 100;
	char* data1;

	Data()  {		
		data1 = new char[ItemSize];

		char pointerValue[10];
		
		sprintf_s(pointerValue, 10, "%p", &data1);
		cout << ItemSize << " items set : " << pointerValue << endl;
		memset(data1, 0, ItemSize);
	}

	~Data() {
		delete[] data1;
	}

	Data& operator=(const Data& origin) {
		cout << ItemSize << " items copied" << endl;
		memcpy(this->data1, origin.data1, sizeof(origin.data1));
		return *this;
	}

	Data& operator=(Data&& origin) {
		cout << ItemSize << " items moved" << endl;
		this->data1 = origin.data1;
		origin.data1 = nullptr;
		return *this;
	}
};

class A {
public:
	A() { cout << "constructor default:" << __FUNCTION__ << endl; }
	A(const A& a) {
		cout << "constructor copy:" << __FUNCTION__ << endl;
		char pointerValue[10];
		sprintf_s(pointerValue, sizeof(pointerValue), "%p", &mData);
		cout << "check internal-data : " << pointerValue << endl;
	}
	void print() const { cout << "I am A" << endl; }

	A& operator=(const A& origin) {
		this->mData = origin.mData;
		return *this;
	}

private:
	struct Data mData;
};

class B {
public:
	B() { cout << "constructor default:" << __FUNCTION__ << endl; }
	B(const B& b) {
		cout << "constructor copy:" << __FUNCTION__ << endl;
		char pointerValue[10];
		sprintf_s(pointerValue, sizeof(pointerValue), "%p", &mData);
		cout << "check internal-data : " << pointerValue << endl;
	}
	void print() const { cout << "I am B" << endl; }

	B& operator=(const B& origin) {
		this->mData = origin.mData;
		return *this;
	}

private:
	struct Data mData;
};

class C {
public:
	C() { cout << "constructor default:" << __FUNCTION__ << endl; }
	C(const C& c) {
		cout << "constructor copy:" << __FUNCTION__ << endl;
		char pointerValue[10];
		sprintf_s(pointerValue, sizeof(pointerValue), "%p", &mData);
		cout << "check internal-data : " << pointerValue << endl;
	}
	C(C&& c) {
		cout << "construct move:" << __FUNCTION__ << endl;
		char pointerValue[10];
		sprintf_s(pointerValue, sizeof(pointerValue), "%p", &mData);
		cout << "check internal-data : " << pointerValue << endl;
		this->mData = std::forward<Data>(c.mData);
	}
	void print() const { cout << "I am C" << endl; }

	C& operator=(const C& origin) {
		this->mData = origin.mData;
		return *this;
	}

private:
	struct Data mData;
};

#define TEST_CONST
#ifndef TEST_CONST
void pass(A a) {
	cout << "func: " << __FUNCTION__ << endl;
	a.print();
	A temp;
	temp = a;
}

void pass(B b) {
	cout << "func: " << __FUNCTION__ << endl;
	b.print();
	B temp = b;
}

void pass(C c) {
	cout << "func: " << __FUNCTION__ << endl;
	c.print();
	C temp(std::move(c));
}
#else

void pass(const A& a) {
	cout << "func: " << __FUNCTION__ << endl;
	a.print();
	A temp;
	temp = a;
}

void pass(const B& b) {
	cout << "func: " << __FUNCTION__ << endl;
	b.print();
	B temp = b;
}

void pass(const C& c) {
	cout << "func: " << __FUNCTION__ << endl;
	c.print();
	C temp(std::move(c));
}

void pass(C&& c) {
	cout << "func: move, " << __FUNCTION__ << endl;
	c.print();
	C temp = std::forward<C>(c);
}
#endif

int main()
{
	A a;
	pass(a);
	cout << endl;
	B b;
	pass(b);
	cout << endl;
	C c;
	pass(c);
	cout << endl;
	pass(std::move(c));
	return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
