
#include <cstdlib>

#include "vv/Application.h"

using namespace vv;

int main(int argc, char *argv[])
{
  // todo: process command line input

  Application application;
  if (!application.init()) return EXIT_FAILURE;
  application.run();

  return EXIT_SUCCESS;
}