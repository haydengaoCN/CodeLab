#include <chrono>
#include <iostream>
#include <thread>

using std::literals::chrono_literals::operator""s;

int main() {
  auto start = std::chrono::steady_clock::now();
  {
    using std::literals::chrono_literals::operator""s;
		std::this_thread::sleep_for(1s);
  }
  auto end = std::chrono::steady_clock::now();
  
  std::cout << "Elapsed time in nanoseconds: "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
            << " ns" << std::endl;
 
  std::cout << "Elapsed time in microseconds: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
            << " µs" << std::endl;
 
  std::cout << "Elapsed time in milliseconds: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
            << " ms" << std::endl;
 
  std::cout << "Elapsed time in seconds: "
            << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
            << " sec";
  return 0;
}
