#include <concepts>
#include <ranges>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <string_view>
#include <type_traits> // For std::decay_t and std::is_same_v

// 1. Concept for Printable Types
template<typename T>
concept Printable = requires(std::ostream& os, const T& value){
    // 1) Check if 'os << value' is a valid expression.
    // 2) Check if the expression returns something convertibale to std::ostream&
    { os << value } -> std::convertible_to<std::ostream&>;
};


// 2. Concept for Numeric Types
template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

// 3. Concept for Terminal Types (stops recursion)
// This applies to things we just want to print as-is, like strings or string views. 
// This is needed for std::list<std::string>.
template<typename T>
concept Terminal = std::same_as<std::decay_t<T>, std::string> || 
                   std::same_as<std::decay_t<T>, std::string_view> ||
                   std::same_as<std::decay_t<T>, const char*>; 

// 4. Concept for Range Types
template<typename T>
concept Container = std::ranges::range<T> && 
                    !Terminal<T> && 
                    !std::convertible_to<T, std::string>; // Exclude types that convert easily to std::string

// 1. Overload for Printable types
template<Printable T>
void print_object(const T& obj) {
    std::cout << "Printing: " << obj << std::endl;
}

// 2. Overload for Numeric types
// Uses 'requires' clause
template<typename T>
requires Numeric<T>
std::string format_data(const T& value){
    // SImple conversion
    return "Numeric: " + std::to_string(value);
}

// Terminal Types (Strings/String Views/C-strings)
// This is the base case for all non-numeric, non-container text types.
template<typename T>
requires Terminal<T>
std::string format_data(const T& value) {
    // Uses std::string(value) to handle conversion from C-string/string_view safely.
    return "'" + std::string(value) + "'";
}

// 3. Overload container types
template<Container T>
std::string format_data(const T& range){
    // Serialize the contents of teh range
    std::stringstream ss;
    ss << "[";
    bool first = true;

    for (const auto& item : range)
    {
        if (!first){
            ss << ", ";
        }
        ss << format_data(item);
        first = false;
    }
    ss << "]";
    return "Container: " + ss.str();
}

// Main
int main() {
    
    print_object(5);
    // print_object(Unprintable{}); // This fails.

    // 1. Numeric Call (Base Case 1)
    int x = 42;
    std::cout << format_data(x) << std::endl;

    // 2. Container of Numerics Call 
    std::vector<double> v = {3.14, 2.718, 1.414};
    std::cout << format_data(v) << std::endl;

    // 3. Container of Strings Call 
    std::list<std::string> l = {"apple", "banana", "cat"};
    std::cout << format_data(l) << std::endl;

    // 4. C-Style String Call
    const char* c_str = "C-string";
    std::cout << format_data(c_str) << std::endl;

    // 5. Nested Container Call 
    std::vector<std::vector<int>> nested = {{1, 2}, {3, 4}};
    std::cout << format_data(nested) << std::endl; 

    // 6. Non container, non Numeric
    // This will fail to compile, giving a clear error
    // because it satisfies neither Numeric nor Container
    // struct MyClass {};
    // MyClass m;
    // std::cout << format_data(m) << std::endl; 

    // 7. string_view
    std::string_view sv = "text_view";
    std::cout << format_data(sv) << std::endl; 

    std::cout << "Compilation successful." << std::endl;

    return 0;
}