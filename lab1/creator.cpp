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
  if (argc != 3) {
    std::cerr << "Usage: Creator <filename> <num_of_records>" << std::endl;
    return 1;
  }

  const char* filename = argv[1];
  int num_records = std::atoi(argv[2]);

  std::ofstream ofs(filename, std::ios::binary);
  if (!ofs) {
    std::cerr << "Error opening file!" << std::endl;
    return 1;
  }

  employee emp;
  for (int i = 0; i < num_records; ++i) {
    std::cout << "Enter employee number: ";
    std::cin >> emp.num;
    std::cin.ignore();

    std::cout << "Enter employee name: ";
    std::cin.getline(emp.name, 10);

    std::cout << "Enter hours worked: ";
    std::cin >> emp.hours;

    ofs.write(reinterpret_cast<char*>(&emp), sizeof(emp));
  }

  ofs.close();
  return 0;
}
