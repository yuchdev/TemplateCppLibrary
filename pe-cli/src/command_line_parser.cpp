#include <pe-cli/command_line_parser.h>

#include <string>
#include <list>
#include <iostream>
#include <algorithm>
#include <boost/filesystem.hpp>

using namespace pe_cli;

namespace po = boost::program_options;

using std::string;

CommandLineParams::CommandLineParams() : cmd_options_description("Command-line interface has the following options")
{}

void CommandLineParams::read_params(int argc, char* argv[])
{
    cmd_options_description.add_options()
        ("help,h", "Print usage")
        ("version,V", "Print version")
        ("filename,f", po::value<string>(&_analyze_filename), "File to analyze")
        ;

    // command line params processing
    po::variables_map cmd_variables_map;
    po::store(parse_command_line(argc, argv, cmd_options_description), cmd_variables_map);
    po::notify(cmd_variables_map);

    set_flag(cmd_variables_map, _help, "help");
    set_flag(cmd_variables_map, _version, "version");
}

/**@brief Set some logical param */
void CommandLineParams::set_flag(const po::variables_map& vm, bool& flag, const char* str)
{
    if (vm.count(str)) {
        flag = true;
    }
}
