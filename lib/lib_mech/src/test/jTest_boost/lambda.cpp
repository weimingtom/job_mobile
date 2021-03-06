#include <stdafx.h>
int g__test_lambda=0;
struct _test_lambda
{
	_test_lambda() { i = g__test_lambda++; }
	int i;
	int get(){ return i;}
};

int main_lambda()
{
	using namespace boost::lambda;
	vector<int> vec;
	vec.push_back(10);
	vec.push_back(23);
	vec.push_back(45);
	vec.push_back(76);
	vec.push_back(98);

	// 5稽 蟹寛 恭嬢走壱 30左陥 笛 推社研 達澗陥.
	vector<int>::iterator it = find_if( vec.begin(), vec.end(), _1%5==0 && _1>30 );
	cout << "found:" << *it << endl;

	// 唖唖税 推社拭 企背辞 2稽蟹寛走澗走拭 魚虞 五室走研 妊獣.
	std::for_each( vec.begin(), vec.end(),
		if_( _1 % 2 == 0 )
		[
			cout << _1 << "(精)澗 側呪\n"
		]
		.else_
			[
				cout << _1 << "(精)澗 筈呪\n"
			]
			);

			vector<_test_lambda> vec1;
			vec1.push_back(_test_lambda());
			vec1.push_back(_test_lambda());
			vec1.push_back(_test_lambda());
			vec1.push_back(_test_lambda());
			vec1.push_back(_test_lambda());
			vec1.push_back(_test_lambda());
			vec1.push_back(_test_lambda());
			/*
			std::for_each( vec1.begin(), vec1.end(),
			if_( 2 % 2 == 0 )
			[
			cout << _1 << "(精)澗 側呪\n"
			]
			.else_
			[
			cout << _1 << "(精)澗 筈呪\n"
			]
			);
			*/

			return 0;
}
/*
窒径森
found:45
10
(精)澗 側呪
23
(精)澗 筈呪
45
(精)澗 筈呪
76
(精)澗 側呪
98
(精)澗 側呪

*/

/// lambda。

// gcc-3.0.4 に怒られました。
// #include <boost/lambda/algorithm.hpp>

// まあエラーが見たければ外して下さい。
// #define WATCH_ERROR

int plus_one(int x) { return x+1; }

int plus_another(int x, int y) { return x+y; }

int one(int val ) 
{ 
	cout << "one() called = " << val*10 << endl;
	return val*10; 
}

void throw_func(int x) {
	if (x == 8) throw std::runtime_error("8が来たから");
	else if (x == 12) throw std::exception();
}

class myClass {
public:
	explicit myClass(int id) : id_(id) {}

	void func0() const {
		std::cout << "func0: " << id_ << std::endl;
	}
	void func1(const myClass& c1) const {
		std::cout << "func1: " << id_ << "(" << c1.id_ << ")" << std::endl;
	}
	void func2(const myClass& c1, const myClass& c2) const {
		std::cout << "func2: " << id_ << "("
			<< c1.id_ << ", " << c2.id_ << ")" << std::endl;
	}
	void func3(const myClass& c1, const myClass& c2, const myClass& c3) const {
		std::cout << "func3: " << id_ << "(" << c1.id_ << ", "
			<< c2.id_ << ", " << c3.id_ << ")" << std::endl;
	}

	void funcNoRef(int i) const {
		std::cout << "funcNoRef: " << id_ << "(" << i << ")" << std::endl;
	}

	int id_;
};

int main_lambda2() {
	using namespace boost::lambda;
	{
		std::vector<int> is;
		is.resize(3);
		cout <<endl << "std::for_each(is.begin(), is.end(), _1 = 1);" <<endl ;
		std::for_each(is.begin(), is.end(), _1 = 1);
		std::copy(is.begin(), is.end(), 
			std::ostream_iterator<int>(cout, "-- \n"));

		cout <<endl << "std::for_each(is.begin(), is.end(), _1 = one(20));" <<endl ;
		std::for_each(is.begin(), is.end(), _1 = bind(one, _1) );
		std::copy(is.begin(), is.end(), 
			std::ostream_iterator<int>(cout, "-- \n"));

	}

	std::vector<int> is;
	is.clear();
	is.push_back(0);
	is.push_back(1);
	is.push_back(2);

	std::for_each(is.begin(), is.end(), _1 = bind(plus_one, _1));
	std::for_each(is.begin(), is.end(), _1 = bind(plus_another, _1, _1));

	myClass c1(1), c2(2);
	(bind(&myClass::func1, c1, _1))(c2);

	std::for_each(is.begin(), is.end(),
		_1 = bind(std_functor(std::plus<int>()), _1, _1));

	std::sort(is.begin(), is.end(), _1 < _2);
	std::sort(is.begin(), is.end(), ret<bool>(_1 < _2));
	std::for_each(is.begin(), is.end(), std::cout << _1 << ' ');
	std::for_each(is.begin(), is.end(), std::cout << constant(' ') << _1);
	std::cout << std::endl;

	int index = 0;
#ifdef WATCH_ERROR
	std::for_each(is.begin(), is.end(),
		std::cout << ++index << ':' << _1 << '\n');
#else
	// これ、gcc-2.96 では通りません、gcc-3.0.4 なら OK でした。
	// ここから先は gcc-3.0.4 でしか確認してません。
	std::for_each(is.begin(), is.end(),
		std::cout << ++var(index) << ':' << _1 << '\n');
#endif

	// 条件分岐やってみよう。
	std::for_each(is.begin(), is.end(),
		if_then(_1 % 3 == 0,
		(std::cout << _1 << " : これだけ3の倍数\n")));

	std::for_each(is.begin(), is.end(),
		if_(_1 % 3 == 0)[std::cout << _1 << " : 3 の倍数\n"].
		else_[std::cout << _1 << " : 3 の倍数じゃない\n"]);

	// ループ

	int i;
	std::for_each(is.begin(), is.end(),
		for_loop( var(i) = 0, var(i) < _1, ++var(i),
			(
				std::cout << var(i) << ' '
			)
		)//for_loop 魁
	);
	std::cout << std::endl;

	int x = 0;
	std::for_each(is.begin(), is.end(),
		while_((var(x)+=_1) < _1 * 10 )
		[
			std::cout << var(x) << ' '
		]
	);

	std::cout << std::endl;

	// switch
	std::for_each(is.begin(), is.end()
		,(
			switch_statement(	_1,
				case_statement<4>
				(
					std::cout << constant("baba")
				),
				case_statement<8>
				(
					std::cout << constant("mulba")
				),
				case_statement<12>
				(
					std::cout << constant("malma")
				)
			)//switch_statement 魁
		, std::cout << constant("\n")
		)
	);//  std::for_each魁

	std::for_each(is.begin(), is.end(),
		try_catch
		(
			bind(throw_func, _1)
			, catch_exception<std::runtime_error>
			(
				std::cout	<< _1
				<< constant(" : runtime が出た理由は、")
				<< bind(&std::exception::what, _e) << '\n'
			),
			catch_all
			(
				std::cout << _1
				<< constant(" : それ以外は 12\n")
			)
		) //try_catch 魁
	);

	// new, delete、めんどいからコピ?
	// コンストラ??、デストラ??も似たようなもん。

	int* a[10];
	std::for_each(a, a+10, _1 = bind(new_ptr<int>()));
	std::for_each(a, a+10, bind(delete_ptr(), _1));

#if 0
	// でもこれ、gcc-2.96, gcc-3.0.4, gcc-3.1, gcc-3.2 のどれでも?メでしたが。
	int b[100][200];
	int sum = 0;
	std::for_each(b, b + 100,
		bind(ll::for_each(), _1, _1 + 200, protect(sum += _1)));
#endif
		return 0;

}


