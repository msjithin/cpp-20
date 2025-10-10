#include <ranges>
#include <iostream>
#include <vector>
#include <algorithm> // Required for std::copy_if
#include <iterator> // Required for std::back_inserter

// Pre C++ 20
void special_function_preCpp20(const std::vector<int>& input){

    std::vector<int> intermediate, output;

    std::copy_if(input.begin(), input.end(), std::back_inserter(intermediate), [](const int i) { return i%3 == 0 ;} );
    std::transform(intermediate.begin(), intermediate.end(), std::back_inserter(output), [](const int i) {return i*i;} );

    for (int n: output){
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

// C++ 20 and above
void special_function(const std::vector<int>& input){

    auto output = input 
        | std::views::filter([](const int n) {return n % 3 == 0; })
        | std::views::transform([](const int n) { return n*n; } );

    for (int n: output){
        std::cout << n << " ";
    }
    std::cout << std::endl;
}


// Main
int main() {
    
    std::vector<int> input = { 0,1,2,3,4,5,6,7,8,9 };

    special_function_preCpp20(input);
    special_function(input);
   
    return 0;
}