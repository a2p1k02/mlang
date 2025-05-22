#include <boost/spirit/home/qi/detail/parse_auto.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>

#include <iostream>
#include <string>

template <typename Iterator>
bool add(Iterator first, Iterator last, double& n)
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    namespace phoenix = boost::phoenix;

    using qi::double_;
    using qi::_1;
    using phoenix::ref;

    bool r = qi::phrase_parse(first, last, 
            (
                double_[ref(n) = _1] >> *(' ' >> double_[ref(n) += _1])
            ),
            ";");
    
    if (first != last) return false;
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

        double n;
        if (add(input.begin(), input.end(), n)) {
            std::cout << "sum: " << n << std::endl; 
        } else {
            std::cout << "parsing error\n";
        }
    }

    return 0;
}
