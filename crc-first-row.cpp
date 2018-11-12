#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

bool pieces_well_placed(const std::string& first_row, bool no_adjacent_bishops)
{
    const int size = first_row.size();

    int first_bishop = -1;
    int first_archbishop_or_queen = -1;
    int num_rooks = 0;

    for (auto i = 0; i < size; i++) {
        switch (first_row[i]) {
        case 'B':
            if (first_bishop == -1)
                first_bishop = i;
            else if ((i - first_bishop) % 2 == 0)
                return false;  // same color bishops
            else if (no_adjacent_bishops && i - first_bishop == 1)
                return false;  // adjacent bishops (with --no-adjacent-bishops)
            break;

        case 'A':
        case 'Q':
            if (first_archbishop_or_queen == -1)
                first_archbishop_or_queen = i;
            else if ((i - first_archbishop_or_queen) % 2 == 0)
                return false;  // same color archbishop/queen
            break;

        case 'R':
            num_rooks += 1;
            break;

        case 'K':
            if (num_rooks != 1)
                return false;  // king not between the rooks
            break;
        }
    }

    return true;
}

bool second_row_protected(const std::string& first_row)
{
    const int size = first_row.size();

    std::vector<bool> second_row(size);

    for (auto i = 0; i < size; i++) {
        // knight component
        if (first_row[i] == 'A' || first_row[i] == 'C' || first_row[i] == 'N') {
            if (i-2 >= 0)
                second_row[i-2] = true;
            if (i+2 < size)
                second_row[i+2] = true;
        }

        // ferz component
        if (first_row[i] == 'A' || first_row[i] == 'B' || 
                first_row[i] == 'K' || first_row[i] == 'Q') {
            if (i-1 >= 0)
                second_row[i-1] = true;
            if (i+1 < size)
                second_row[i+1] = true;
        }

        // wazir component
        if (first_row[i] == 'C' || first_row[i] == 'R' ||
                first_row[i] == 'K' || first_row[i] == 'Q') {
            second_row[i] = true;
        }
    }

    return std::all_of(second_row.begin(), second_row.end(),
                       [](bool i) { return i; });
}

int main(int argc, char **argv)
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("no-adjacent-bishops", "prevent adjacent bishops")
    ;

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    } catch (po::unknown_option& e) {
        std::cerr << desc;
        return 1;
    }

    if (vm.count("help")) {
        std::cerr << desc;
        return 1;
    }

    // piece abbreviations come from
    //  https://en.wikipedia.org/wiki/Capablanca_Random_Chess
    std::string first_row("RNABQKBCNR");
    std::sort(first_row.begin(), first_row.end());

    const bool no_adjacent_bishops = vm.count("no-adjacent-bishops");
    do {
        if (pieces_well_placed(first_row, no_adjacent_bishops) &&
                second_row_protected(first_row))
            std::cout << first_row << '\n';
    } while (std::next_permutation(first_row.begin(), first_row.end()));
 
    return 0;
}
