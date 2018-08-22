#include <fstream>
#include <iostream>
#include <InputUtils.h>

int main(int argc, char *argv[])
{
    std::string inputFilename("test.in");
    std::ifstream inputFile;
    inputFile.exceptions(std::ifstream::badbit);
    inputFile.open(inputFilename);
    std::vector<unsigned> numbers(getLineOfIntegers(inputFile));
    for(const auto num : numbers)
        std::cout << num << std::endl;
    return 0;
}
