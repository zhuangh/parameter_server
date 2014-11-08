#include "gtest/gtest.h"
#include "base/bloom_filter.h"
#include "base/shared_array_inl.h"

DEFINE_int32(m, 100, "");
DEFINE_int32(k, 2, "");
TEST(BloomFilter, Speed) {

using namespace PS;
  // see src/test/prepare_test_data to get the data
  SArray<Key> key1; key1.readFromFile("../data/test/key.1");
  SArray<Key> key2; key2.readFromFile("../data/test/key.2");
  BloomFilter<Key> bloom(FLAGS_m, FLAGS_k);
  auto tv = tic();
  for (auto k : key1)  bloom.insert(k);
  LL << key1.size() / toc(tv) << " insert per sec";

  tv = tic();
  int res = 0;
  for (auto k : key2)  res += bloom[k];
  LL << key2.size() / toc(tv) << " query per sec";

  LL << "FPR: " << (double) res / (double) key2.size();
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  google::ParseCommandLineFlags(&argc, &argv, true);
  FLAGS_logtostderr = 1;

  return RUN_ALL_TESTS();
}
