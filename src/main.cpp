#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/stl.hpp>

#include <iostream>
#include <vector>
#include <string>

namespace mlang 
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    namespace phoenix = boost::phoenix;

    using qi::double_;
    using qi::_1;
    using phoenix::push_back;

    template <typename Iterator>
    bool parse_numbers(Iterator first, Iterator last, std::vector<double>& nums)
    {
        bool r = qi::phrase_parse(first, last, 
            (
                double_[push_back(phoenix::ref(nums), _1)] 
                    >> *(double_[push_back(phoenix::ref(nums), _1)])
            ),
            ascii::space);
    
        if (first != last) return false;
        return r;
    }   

    double count(std::vector<double> nums, char op)
    {
        double res = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            if (op == '+') {
                res += nums[i];
            } else if (op == '-') {
                res -= nums[i];
            } else if (op == '*') {
                res *= nums[i];
            } else if (op == '/') {
                res /= nums[i];
            }
        }
        return res;
    }
}

int main()
{
    std::cout << "Type [q or Q] to quit\n\n";

    std::string input;
    while (true) {
        std::cout << ">>> ";
        getline(std::cin, input);

        if (input.empty() || tolower(input[0]) == 'q')
            break;

        std::vector<double> nums;
        char op = input[0];
        input = input.erase(0, 1);

        if (mlang::parse_numbers(input.begin(), input.end(), nums)) {
            std::cout << mlang::count(nums, op) << std::endl; 
        } else {
            std::cout << "parsing error\n";
        }
    }

    return 0;
}

