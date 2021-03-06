#include <stdafx.h>
////////////////////////////////////////////////////////////////////////////
//
//  Plain calculator example.
//
//  [ JDG 5/10/2002 ]
//
////////////////////////////////////////////////////////////////////////////
#include "boost/spirit/core.hpp"
#include <iostream>
#include <string>

////////////////////////////////////////////////////////////////////////////
using namespace std;
using namespace spirit;

////////////////////////////////////////////////////////////////////////////
//
//  Semantic actions
//
////////////////////////////////////////////////////////////////////////////
namespace {

	void    do_int(char const* str, char const* end)
	{
		string  s(str, end);
		cout << "PUSH(" << s << ')' << endl;
	}

	void    do_add(char const*, char const*)    { cout << "ADD\n"; }
	void    do_subt(char const*, char const*)   { cout << "SUBTRACT\n"; }
	void    do_mult(char const*, char const*)   { cout << "MULTIPLY\n"; }
	void    do_div(char const*, char const*)    { cout << "DIVIDE\n"; }
	void    do_neg(char const*, char const*)    { cout << "NEGATE\n"; }
}

////////////////////////////////////////////////////////////////////////////
//
//  Our calculator grammar
//
////////////////////////////////////////////////////////////////////////////
struct calculator : public grammar<calculator>
{
	template <typename ScannerT>
	struct definition
	{
		definition(calculator const& self)
		{
			expression
				=   term
				>> *(   ('+' >> term)[&do_add]
				|   ('-' >> term)[&do_subt]
				)
					;

				term
					=   factor
					>> *(   ('*' >> factor)[&do_mult]
					|   ('/' >> factor)[&do_div]
					)
						;

					factor
						=   lexeme_d[(+digit_p)[&do_int]]
						|   '(' >> expression >> ')'
							|   ('-' >> factor)[&do_neg]
							|   ('+' >> factor)
								;
		}

		rule<ScannerT> expression, term, factor;

		rule<ScannerT> const&
			start() const { return expression; }
	};
};

////////////////////////////////////////////////////////////////////////////
//
//  Main program
//
////////////////////////////////////////////////////////////////////////////
int main_calc_plain()
{
	cout << "/////////////////////////////////////////////////////////\n\n";
	cout << "\t\tExpression parser...\n\n";
	cout << "/////////////////////////////////////////////////////////\n\n";
	cout << "Type an expression...or [q or Q] to quit\n\n";

	calculator calc;    //  Our parser

	for (;;)
	{
		char str[256];
		cin.getline(str, 256);
		if (str[0] == 'q' || str[0] == 'Q')
			break;

		parse_info<> info = parse(str, calc, space_p);

		if (info.full)
		{
			cout << "-------------------------\n";
			cout << "Parsing succeeded\n";
			cout << "-------------------------\n";
		}
		else
		{
			cout << "-------------------------\n";
			cout << "Parsing failed\n";
			cout << "stopped at: \": " << info.stop << "\"\n";
			cout << "-------------------------\n";
		}
	}

	cout << "Bye... :-) \n\n";
	return 0;
}
