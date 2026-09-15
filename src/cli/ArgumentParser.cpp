#include "cli/ArgumentParser.hpp"

namespace vog {

flags parse_flags(int argc, char* argv[]) {
    flags result;

    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            result.show_help = true;
        }
        else if (arg == "-V" || arg == "--version") {
            result.show_version = true;
        }
        else if (arg == "-v" || arg == "--verbose") {
            result.verbose = true;
        }
        else if (arg == "-o" || arg == "--output") {
            if (i + 1 >= argc) {
                throw std::runtime_error("expected output file after " + arg);
            }
            result.output_file = argv[++i];
        }
        else if (arg == "--emit") {
            if (i + 1 >= argc) {
                throw std::runtime_error("expected emit type after --emit");
            }

            result.emit = argv[++i];
            if (result.emit != "exe" && result.emit != "obj" && result.emit != "asm") {
                throw std::runtime_error("invalid emit type: " + result.emit);
            }
        }
        else if (arg == "--target") {
            if (i + 1 >= argc) {
                throw std::runtime_error("expected target after --target");
            }
            result.target = argv[++i];
        }
        else if (arg == "-O0") {
            result.optimization_level = 0;
        }
        else if (arg == "-O1") {
            result.optimization_level = 1;
        }
        else if (arg == "-O2") {
            result.optimization_level = 2;
        }
        else if (arg == "-O3") {
            result.optimization_level = 3;
        }
        else if (arg == "-g" || arg == "--debug") {
            result.debug = true;
        }
        else if (arg == "-d" || arg == "--debugger") {
            result.enable_debugger = true;
        }
        else if (arg == "-Wall") {
            result.Wall = true;
        }
        else if (arg == "-Wextra") {
            result.Wextra = true;
        }
        else if (arg == "-Werror") {
            result.Werror = true;
        }
        else if (arg == "--tokens") {
            result.show_tokens = true;
        }
        else if (arg == "--ast") {
            result.show_ast = true;
        }
        else if (arg == "--ir") {
            result.show_ir = true;
        }
        else if (arg == "--color") {
            result.color = true;
        }
        else if (arg == "--no-color") {
            result.color = false;
        }
        else if (arg == "--error-limit") {
            if (i + 1 >= argc) {
                throw std::runtime_error("expected number after --error-limit");
            }

            try {
                result.error_limit = static_cast<unsigned int>(std::stoul(argv[++i]));
            }
            catch (...) {
                throw std::runtime_error("invalid value for --error-limit");
            }
        }
        else if (!arg.empty() && arg[0] != '-') {
            if (!result.input_file.empty()) {
                throw std::runtime_error("multiple input files are not supported");
            }
            result.input_file = arg;
        }
        else {
            throw std::runtime_error("unknown option: " + arg);
        }
    }

    return result;
}

}