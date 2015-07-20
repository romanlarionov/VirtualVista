
#include "AppManager.h"

using namespace vv;

int main(int argc, char* argv[])
{
  // TODO: process command line input

  if (!AppManager::init()) return EXIT_FAILURE;
  AppManager::instance()->run();

  return EXIT_SUCCESS;
}