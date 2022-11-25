#include "catch2/catch.hpp"
#include "utils/math/randutils.h"

#include <cstdint>
#include <fstream>
#include <limits>
#include <string>
#include <tuple>
#include <vector>

namespace GOOM::UNIT_TESTS
{

#ifndef NDEBUG
using Catch::Matchers::StartsWith;
#endif
using UTILS::MATH::RAND::GetRand;
using UTILS::MATH::RAND::GetRandInRange;
using UTILS::MATH::RAND::GetRandSeed;
using UTILS::MATH::RAND::RestoreRandState;
using UTILS::MATH::RAND::SaveRandState;
using UTILS::MATH::RAND::SetRandSeed;

TEST_CASE("save/restore random state")
{
  const uint64_t seed = 1000;

  SetRandSeed(seed);
  REQUIRE(seed == GetRandSeed());

  const uint32_t r1 = GetRand();
  const uint32_t r2 = GetRand();
  REQUIRE(r1 != r2);

  const std::string saveFile = "/tmp/rand.txt";
  std::ofstream fout{saveFile, std::ofstream::out};
  SaveRandState(fout);
  fout.close();
  const uint32_t r_justAfterSave = GetRand();

  // Scramble things a bit
  SetRandSeed(seed + 10);
  uint32_t r = 0;
  for (size_t i = 0; i < 1000; i++)
  {
    r = GetRand();
  }
  REQUIRE(seed != GetRandSeed());
  REQUIRE(r != r_justAfterSave);

  std::ifstream fin{saveFile, std::ifstream::in};
  RestoreRandState(fin);
  r = GetRand();
  REQUIRE(seed == GetRandSeed());
  REQUIRE(r == r_justAfterSave);
}

TEST_CASE("repeatable random sequence")
{
  const uint64_t seed = 1000;

  SetRandSeed(seed);
  REQUIRE(seed == GetRandSeed());
  std::vector<uint32_t> seq1(1000);
  std::vector<float> fseq1(1000);
  for (size_t i = 0; i < 1000; i++)
  {
    seq1[i] = GetRand();
    fseq1[i] = GetRandInRange(0.0F, 1.0F);
  }

  SetRandSeed(seed);
  REQUIRE(seed == GetRandSeed());
  std::vector<uint32_t> seq2(1000);
  std::vector<float> fseq2(1000);
  for (size_t i = 0; i < 1000; i++)
  {
    seq2[i] = GetRand();
    fseq2[i] = GetRandInRange(0.0F, 1.0F);
  }

  SetRandSeed(seed + 1);
  REQUIRE(seed + 1 == GetRandSeed());
  std::vector<uint32_t> seq3(1000);
  std::vector<float> fseq3(1000);
  for (size_t i = 0; i < 1000; i++)
  {
    seq3[i] = GetRand();
    fseq3[i] = GetRandInRange(0.0F, 1.0F);
  }

  REQUIRE(seq1 == seq2);
  REQUIRE(seq1 != seq3);

  REQUIRE(fseq1 == fseq2);
  REQUIRE(fseq1 != fseq3);
}

template<typename Valtype>
auto GetMinMax(const size_t numLoop, const Valtype& nMin, const Valtype& nMax)
    -> std::tuple<Valtype, Valtype>
{
  Valtype min = std::numeric_limits<Valtype>::max();
  Valtype max = std::numeric_limits<Valtype>::min();
  for (size_t i = 0; i < numLoop; i++)
  {
    Valtype r = GetRandInRange(nMin, nMax);
    if (r < min)
    {
      min = r;
    }
    if (r > max)
    {
      max = r;
    }
  }

  return std::make_tuple(min, max);
}

TEST_CASE("uint32_t min max get random")
{
  // After a big enough loop, a good random distribution should have
  // covered the entire range: nMin <= n < nMax
  static constexpr size_t NUM_LOOP = 100000;

  static constexpr uint32_t N_MIN1 = 999;
  static constexpr uint32_t N_MAX1 = 10001;
  const auto [min1, max1] = GetMinMax(NUM_LOOP, N_MIN1, N_MAX1);
  REQUIRE(min1 == N_MIN1);
  REQUIRE(max1 == N_MAX1 - 1);

  static constexpr uint32_t N_MIN2 = 0;
  static constexpr uint32_t N_MAX2 = 120;
  const auto [min2, max2] = GetMinMax(NUM_LOOP, N_MIN2, N_MAX2);
  REQUIRE(min2 == N_MIN2);
  REQUIRE(max2 == N_MAX2 - 1);

  REQUIRE_NOTHROW(GetRandInRange(5U, 6U));
#ifndef NDEBUG
  REQUIRE_THROWS_WITH(GetRandInRange(5U, 1U), StartsWith("uint n0"));
#endif
}

TEST_CASE("int32_t min max get random")
{
  // After a big enough loop, a good random distribution should have
  // covered the entire range: nMin <= n < nMax
  static constexpr size_t NUM_LOOP = 100000;

  static constexpr int32_t N_MIN1 = -999;
  static constexpr int32_t N_MAX1 = 10001;
  const auto [min1, max1] = GetMinMax(NUM_LOOP, N_MIN1, N_MAX1);
  REQUIRE(min1 == N_MIN1);
  REQUIRE(max1 == N_MAX1 - 1);

  static constexpr int32_t N_MIN2 = -999;
  static constexpr int32_t N_MAX2 = -50;
  const auto [min2, max2] = GetMinMax(NUM_LOOP, N_MIN2, N_MAX2);
  REQUIRE(min2 == N_MIN2);
  REQUIRE(max2 == N_MAX2 - 1);

  static constexpr int32_t N_MIN3 = 1;
  static constexpr int32_t N_MAX3 = 999;
  const auto [min3, max3] = GetMinMax(NUM_LOOP, N_MIN3, N_MAX3);
  REQUIRE(min3 == N_MIN3);
  REQUIRE(max3 == N_MAX3 - 1);

  static constexpr int32_t N_MIN4 = 0;
  static constexpr int32_t N_MAX4 = 635;
  const auto [min4, max4] = GetMinMax(NUM_LOOP, N_MIN4, N_MAX4);
  REQUIRE(min4 == N_MIN4);
  REQUIRE(max4 == N_MAX4 - 1);

  REQUIRE_NOTHROW(GetRandInRange(5, 6));
  REQUIRE_NOTHROW(GetRandInRange(-6, -5));
  REQUIRE_NOTHROW(GetRandInRange(-6, 10));
#ifndef NDEBUG
  REQUIRE_THROWS_WITH(GetRandInRange(-5, -6), StartsWith("int n0"));
  REQUIRE_THROWS_WITH(GetRandInRange(5, 1), StartsWith("int n0"));
  REQUIRE_THROWS_WITH(GetRandInRange(5, -1), StartsWith("int n0"));
#endif
}

TEST_CASE("float min max get random")
{
  // After a big enough loop, a good random distribution should have
  // covered the entire range: nMin <= n < nMax
  static constexpr size_t NUM_LOOP = 1000000;

  static constexpr float N_MIN1 = 0;
  static constexpr float N_MAX1 = 1;
  const auto [min1, max1] = GetMinMax(NUM_LOOP, N_MIN1, N_MAX1);
  REQUIRE(std::fabs(min1 - N_MIN1) < 0.0001F);
  REQUIRE(std::fabs(max1 - N_MAX1) < 0.0001F);

  static constexpr float N_MIN2 = -1;
  static constexpr float N_MAX2 = 0;
  const auto [min2, max2] = GetMinMax(NUM_LOOP, N_MIN2, N_MAX2);
  REQUIRE(std::fabs(min2 - N_MIN2) < 0.0001F);
  REQUIRE(std::fabs(max2 - N_MAX2) < 0.0001F);

  static constexpr float N_MIN3 = -10;
  static constexpr float N_MAX3 = +10;
  const auto [min3, max3] = GetMinMax(NUM_LOOP, N_MIN3, N_MAX3);
  REQUIRE(std::fabs(min3 - N_MIN3) < 0.0001F);
  REQUIRE(std::fabs(max3 - N_MAX3) < 0.0001F);

  REQUIRE_NOTHROW(GetRandInRange(5.0F, 6.0F));
  REQUIRE_NOTHROW(GetRandInRange(-6.0F, -5.0F));
  REQUIRE_NOTHROW(GetRandInRange(-6.0F, 10.0F));
#ifndef NDEBUG
  REQUIRE_THROWS_WITH(GetRandInRange(-5.0F, -6.0F), StartsWith("float x0"));
  REQUIRE_THROWS_WITH(GetRandInRange(5.0F, 1.0F), StartsWith("float x0"));
  REQUIRE_THROWS_WITH(GetRandInRange(5.0F, -1.0F), StartsWith("float x0"));
#endif
}

} // namespace GOOM::UNIT_TESTS
