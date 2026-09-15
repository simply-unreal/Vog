#pragma once

#include "Flags.hpp"

#include <stdexcept>
#include <string>

namespace vog {

flags parse_flags(int argc, char* argv[]);

}