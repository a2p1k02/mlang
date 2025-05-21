#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>

#include <iostream>
#include <string>
#include <complex>

template <typename Iterator>
bool parse_complex(Iterator first, Iterator last, std::complex<double>& c)
{
    using boost::spirit::qi::double_;
    using boost::spirit::qi::_1;
    using boost::spirit::qi::phrase_parse;
    using boost::spirit::ascii::space;
    using boost::phoenix::ref;

    double rN = 0.0;
    double iN = 0.0;

    bool r = phrase_parse(first, last, 
            (
                '(' >> double_[ref(rN) = _1]
                    >> -(',' >> double_[ref(iN) = _1]) >> ')'
                | double_[ref(rN) = _1]
            ),
            space);
    
    if (!r || first != last) return false;

    c = std::complex<double>(rN, iN);
    return r;
}

int main()
{
    std::cout << "Give me a complex number of the form like r or (r) or (r, i)\n";
    std::cout << "Type [e or E] to exit\n\n";

    std::string input;
    while (true) {
        std::cout << ">>> ";
        std::cin >> input;

        if (input.empty() || tolower(input[0]) == 'e')
            break;

        std::complex<double> d;
        if (parse_complex(input.begin(), input.end(), d)) {
            std::cout << "got: " << d << std::endl;
        } else {
            std::cout << "parsing failed\n";
        }
    }

    return 0;
}
