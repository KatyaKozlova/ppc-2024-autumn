// Copyright 2023 Nesterov Alexander
#include <gtest/gtest.h>

#include <random>
#include <vector>

#include "seq/kozlova_e_radix_batcher_sort/include/ops_seq.hpp"

TEST(kozlova_e_radix_batcher_sort_seq, test_simple_mas) {
  const int count = 10;

  std::vector<double> mas = {2.354, -4.789, 1, -1.456, 3.987, -0.456, 7.234, -8.654, 9.876, 5.432};
  std::vector<double> res(count, 0);

  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(mas.data()));
  taskDataSeq->inputs_count.emplace_back(mas.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(res.data()));
  taskDataSeq->outputs_count.emplace_back(res.size());

  kozlova_e_radix_batcher_sort_seq::RadixSortSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();

  for (int i = 1; i < count; i++) {
    ASSERT_LE(res[i - 1], res[i]);
  }
}

TEST(kozlova_e_radix_batcher_sort_seq, test_remainder_vector) {
  const int count = 10;

  std::vector<double> mas = {3.175, 3.141, 3.256, 3.879, 3.334, 3.667, 3.987, 3.432, 3.254, 3.876};
  std::vector<double> res(count, 0);

  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(mas.data()));
  taskDataSeq->inputs_count.emplace_back(mas.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(res.data()));
  taskDataSeq->outputs_count.emplace_back(res.size());

  kozlova_e_radix_batcher_sort_seq::RadixSortSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();

  for (int i = 1; i < count; i++) {
    ASSERT_LE(res[i - 1], res[i]);
  }
}

TEST(kozlova_e_radix_batcher_sort_seq, test_empty_mas) {
  const int count = 0;

  std::vector<double> mas;
  std::vector<double> res(count, 0);

  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(mas.data()));
  taskDataSeq->inputs_count.emplace_back(mas.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(res.data()));
  taskDataSeq->outputs_count.emplace_back(res.size());

  kozlova_e_radix_batcher_sort_seq::RadixSortSequential testTaskSequential(taskDataSeq);

  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();

  ASSERT_EQ(res.size(), 0);
}

TEST(kozlova_e_radix_batcher_sort_seq, test_single_element) {
  const int count = 1;

  std::vector<double> mas = {3.1415};
  std::vector<double> res(count, 0);

  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(mas.data()));
  taskDataSeq->inputs_count.emplace_back(mas.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(res.data()));
  taskDataSeq->outputs_count.emplace_back(res.size());

  kozlova_e_radix_batcher_sort_seq::RadixSortSequential testTaskSequential(taskDataSeq);

  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();

  ASSERT_EQ(res[0], 3.1415);
}

TEST(kozlova_e_radix_batcher_sort_seq, test_negative_numbers) {
  const int count = 6;

  std::vector<double> mas = {-1.234, -3.456, -2.345, -0.123, -5.678, -4.567};
  std::vector<double> res(count, 0);

  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(mas.data()));
  taskDataSeq->inputs_count.emplace_back(mas.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(res.data()));
  taskDataSeq->outputs_count.emplace_back(res.size());

  kozlova_e_radix_batcher_sort_seq::RadixSortSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();

  for (int i = 1; i < count; i++) {
    ASSERT_LE(res[i - 1], res[i]);
  }
}

TEST(kozlova_e_radix_batcher_sort_seq, Test_LargeDataSet) {
  const int count = 1000;

  std::vector<double> mas(count);
  std::generate(mas.begin(), mas.end(), []() { return (rand() % 1000) / 1000.0; });
  std::vector<double> res(count, 0);

  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(mas.data()));
  taskDataSeq->inputs_count.emplace_back(mas.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(res.data()));
  taskDataSeq->outputs_count.emplace_back(res.size());

  kozlova_e_radix_batcher_sort_seq::RadixSortSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();

  for (int i = 1; i < count; i++) {
    ASSERT_LE(res[i - 1], res[i]);
  }
}

TEST(kozlova_e_radix_batcher_sort_seq, test_remaind) {
  const int count = 2;

  std::vector<double> mas = {1.0001, 1};
  std::vector<double> res(count, 0);
  std::vector<double> expect = {1, 1.0001};

  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(mas.data()));
  taskDataSeq->inputs_count.emplace_back(mas.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(res.data()));
  taskDataSeq->outputs_count.emplace_back(res.size());

  kozlova_e_radix_batcher_sort_seq::RadixSortSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  testTaskSequential.pre_processing();
  testTaskSequential.run();
  testTaskSequential.post_processing();

  ASSERT_EQ(res, expect);
}