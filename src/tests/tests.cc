#include "tests.h"

TEST(Invalid_name, test_one) {
  EXPECT_THROW(Parser test("kek.obj"), std::invalid_argument);
}

TEST(Invalid_name, test_two) {
  EXPECT_THROW(Parser test(kPath + "cube_blender.obb"), std::invalid_argument);
}

TEST(Empty_date, empty_file) {
  Parser test(kPath + "empty.obj");
  EXPECT_EQ(test.GetReadStatus(), 0);
}

TEST(Empty_date, empty_vertex) {
  Parser test(kPath + "empty_vertex.obj");
  EXPECT_EQ(test.GetReadStatus() , 0);
}

TEST(Empty_date, empty_textures) {
  Parser test(kPath + "empty_textures.obj");
  EXPECT_EQ(test.GetTexturesStatus() , 0);
}

TEST(Empty_date, empty_normals) {
  Parser test(kPath + "empty_normals.obj");
  EXPECT_EQ(test.GetNormalsStatus(), 0);
}

TEST(Empty_date, empty_indices) {
  Parser test(kPath + "empty_indices.obj");
  EXPECT_EQ(test.GetReadStatus(), 0);
}

TEST(Empty_date, out_of_range) {
  Parser test(kPath + "out_of_range.obj");
  EXPECT_EQ(test.GetReadStatus(), 0);
}
