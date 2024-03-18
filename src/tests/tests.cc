#include "tests.h"

TEST(Invalid_name, test_one) {
  EXPECT_THROW(NewParser test("kek.obj"), std::invalid_argument);
}

TEST(Invalid_name, test_two) {
  EXPECT_THROW(NewParser test(kPath + "cube_blender.obb"), std::invalid_argument);
}

TEST(Empty_date, empty_file) {
  NewParser test(kPath + "empty.obj");
  EXPECT_EQ(test.GetReadStatus(), 0);
}

TEST(Empty_date, empty_vertex) {
  NewParser test(kPath + "empty_vertex.obj");
  EXPECT_EQ(test.GetReadStatus() , 0);
}

TEST(Empty_date, empty_textures) {
  NewParser test(kPath + "empty_textures.obj");
  EXPECT_EQ(test.GetTexturesStatus() , 0);
}

TEST(Empty_date, empty_normals) {
  NewParser test(kPath + "empty_normals.obj");
  EXPECT_EQ(test.GetNormalsStatus(), 0);
}

TEST(Empty_date, empty_indices) {
  NewParser test(kPath + "empty_indices.obj");
  EXPECT_EQ(test.GetReadStatus(), 0);
}

TEST(Empty_date, out_of_range) {
  NewParser test(kPath + "out_of_range.obj");
  EXPECT_EQ(test.GetReadStatus(), 0);
}
