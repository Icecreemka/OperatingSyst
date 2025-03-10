#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>

struct employee {
  int num;
  char name[10];
  double hours;
};

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr << "Usage: Reporter <binary_file> <report_file> <hourly_rate>"
              << std::endl;
    return 1;
  }

  const char* binary_filename = argv[1];
  const char* report_filename = argv[2];
  double hourly_rate = std::atof(argv[3]);

  std::ifstream ifs(binary_filename, std::ios::binary);
  if (!ifs) {
    std::cerr << "Error opening binary file!" << std::endl;
    return 1;
  }

  std::ofstream ofs(report_filename);
  if (!ofs) {
    std::cerr << "Error opening report file!" << std::endl;
    return 1;
  }

  employee emp;
  ofs << "Report for file: " << binary_filename << std::endl;
  ofs << "ID\tName\tHours\tSalary" << std::endl;

  while (ifs.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
    double salary = emp.hours * hourly_rate;
    ofs << emp.num << "\t" << emp.name << "\t" << emp.hours << "\t" << salary
        << std::endl;
  }

  ifs.close();
  ofs.close();
  return 0;
}
