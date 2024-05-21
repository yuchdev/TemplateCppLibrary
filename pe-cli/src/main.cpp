#include <pe-cli/command_line_parser.h>
#include <pe/pe_analyzer.h>

#include <fmt/format.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#include <iostream>
#include <string>
#include <string_view>
#include <filesystem>

using namespace pe_cli;
using namespace pe;
using std::string_view;

constexpr std::string_view VER_PRODUCTVERSION_STR = "1.0.0";

static CommandLineParams& get_params()
{
    static CommandLineParams p;
    return p;
}

void usage()
{
    std::cout << get_params().options_descript() << '\n';
    std::exit(EXIT_SUCCESS);
}

void print_version()
{
    fmt::print("PE Editor (c) version: {}\n", VER_PRODUCTVERSION_STR);
    std::exit(EXIT_SUCCESS);
}

void process_cli(const CommandLineParams& cmd_line_params)
{
    if (cmd_line_params.is_help()){
        usage();
    }

    if (cmd_line_params.is_version()) {
        print_version();
    }

    if (cmd_line_params.analyze_filename().empty()) {
        fmt::print("No file to analyze\n");
        usage();
    }
}

int main(int argc, char* argv[])
{
    setlocale(0, "");
    get_params().read_params(argc, argv);
    process_cli(get_params());
    return 0;
}
