#include <BigNumber.h>
#include <tuple>
#include <vector>


// THIS IS ALL UNTESTED

BigNumber encodeMixedRadix(const std::vector<std::tuple<uint16_t, uint16_t>>& digits_and_bases)
{
    BigNumber encoded = 0;
    BigNumber multiplier = 1;

    for (const auto& [digit, base] : digits_and_bases)
    {
        encoded += static_cast<BigNumber>(digit) * multiplier;
        multiplier *= static_cast<BigNumber>(base);
    }

    return encoded;
}
