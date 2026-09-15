#include "app/SourceLoader.hpp"

#include <filesystem>
#include <fstream>
#include <iterator>
#include <stdexcept>

namespace vog::app {

std::string load_source(const Flags& options) {
    if (options.input_file.empty()) {
        return R"(
        fn main() {
            i32 x = 42;
            i32 y = x + 10;
            return y;
        }
    )";
    }

    const std::filesystem::path input_path(options.input_file);
    std::ifstream input(input_path, std::ios::binary);
    if (!input) {
        throw std::runtime_error(
            "failed to open input file: " + input_path.string()
            + " (working directory: " + std::filesystem::current_path().string() + ")"
        );
    }

    return std::string(
        std::istreambuf_iterator<char>(input),
        std::istreambuf_iterator<char>()
    );
}

}
