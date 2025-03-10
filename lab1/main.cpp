#include <windows.h>  

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

struct employee {
  int num;  
  char name[10];  
  double hours;   
};


void runProcess(const char* command) {
  int size_needed = MultiByteToWideChar(CP_ACP, 0, command, -1, NULL, 0);
  wchar_t* w_command = new wchar_t[size_needed];

  MultiByteToWideChar(CP_ACP, 0, command, -1, w_command, size_needed);

  STARTUPINFO si = {sizeof(si)};
  PROCESS_INFORMATION pi;
  if (!CreateProcessW(NULL, w_command, NULL, NULL, FALSE, 0, NULL, NULL, &si,
                      &pi)) {
    std::cerr << "Error creating process!" << std::endl;
    return;
  }
  WaitForSingleObject(pi.hProcess, INFINITE);
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
}

int main() {
  char binary_filename[100];
  int num_records;

  std::cout << "Enter binary filename: ";
  std::cin >> binary_filename;
  std::cout << "Enter number of records: ";
  std::cin >> num_records;

  char creator_command[200];
  snprintf(creator_command, sizeof(creator_command), "Creator %s %d",
           binary_filename, num_records);
  runProcess(creator_command);

  std::ifstream ifs(binary_filename, std::ios::binary);
  if (!ifs) {
    std::cerr << "Error opening binary file!" << std::endl;
    return 1;
  }

  employee emp;
  while (ifs.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
    std::cout << "Employee ID: " << emp.num << ", Name: " << emp.name
              << ", Hours: " << emp.hours << std::endl;
  }
  ifs.close();

  char report_filename[100];
  double hourly_rate;
  std::cout << "Enter report filename: ";
  std::cin >> report_filename;
  std::cout << "Enter hourly rate: ";
  std::cin >> hourly_rate;

  char reporter_command[200];
  snprintf(reporter_command, sizeof(reporter_command), "Reporter %s %s %f",
           binary_filename, report_filename, hourly_rate);
  runProcess(reporter_command);

  std::ifstream report_ifs(report_filename);
  if (!report_ifs) {
    std::cerr << "Error opening report file!" << std::endl;
    return 1;
  }

  std::string line;
  while (std::getline(report_ifs, line)) {
    std::cout << line << std::endl;
  }
  report_ifs.close();

  return 0;
}
