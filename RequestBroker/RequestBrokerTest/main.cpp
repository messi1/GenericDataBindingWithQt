#include <stdio.h>

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
  printf("Running RequestBroker Tests:\n");

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
