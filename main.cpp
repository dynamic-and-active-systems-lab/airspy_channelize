// Include Files
#include "main.h"
#include "airspy_channelize.h"
#include "airspy_channelize_terminate.h"
#include "airspy_channelize_types.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "omp.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>
#include <stdlib.h>

int main(int argc, char ** argv)
{
  coder::array<int, 2U> channelsUsed;

  if (argc > 1) {
    channelsUsed.set_size(1, argc - 1);
  }

  for (int i=1; i<argc; i++) {
    channelsUsed[i-1] = atoi(argv[i]);
  }

  airspy_channelize(channelsUsed);


  // Terminate the application.
  // You do not need to do this more than one time.
  airspy_channelize_terminate();

  return 0;
}
