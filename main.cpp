#include <string>
#include "RunProgramm.h"

#define FILE_NAME_ARG_INDEX 1

/**
 * Main
 * @param argc
 * @param argv includes the file name of the script.
 */
int main(int argc, char *argv[]) {
  RunProgramm *programm = new RunProgramm(argv[FILE_NAME_ARG_INDEX]);
  programm->run();
  delete(programm);
}
