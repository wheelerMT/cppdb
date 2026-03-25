#include <iostream>
#include <ostream>
#include <print>

int main() {
    try {
        std::print("cppdb v0.1.0 starting...");
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "unknown exception" << '\n';
        return 1;
    }

    return EXIT_SUCCESS;
}