#include <iostream>
#include <string>
#include <cstdio>
#include <array>

int main() {
  std::string command = "python myscript.py";
  std::string output;

  // Open a pipe to read the output of the Python script
  std::array<char, 128> buffer;
  std::auto_ptr<FILE> pipe(popen(command.c_str(), "r"));
  if (!pipe.get()) {
    throw std::runtime_error("popen() failed!");
  }

  // Read the output of the Python script from the pipe
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != NULL) {
    output += buffer.data();
  }

  // Print the output
  std::cout << "Output from Python script: " << output << std::endl;

  return 0;
}
