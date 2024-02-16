#include "tests.h"

TEST(Correct_file, test_one) {
  s21::Parser test("/Users/mammiemi/Project/CPP4_3DViewer_v2.0-2/data-samples/test_vertex.obj");
  std::vector<float> expect{-1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0, 0.0, -1.0, -1.0, 0.0, 1.0, 1.0, 0.0, -1.0, -1.0, 0.0, -1.0};
  
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
