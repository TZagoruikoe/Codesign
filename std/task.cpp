#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

#include <time.h>
#include <sys/time.h>

static double rtclock() {
    struct timeval Tp;
    int stat;

    stat = gettimeofday(&Tp, NULL);
    if (stat != 0)
        std::cout << "Error return from gettimeofday: " << stat << std::endl;

    return (Tp.tv_sec + Tp.tv_usec * 1.0e-6);
}

void do_fast_kernel_magic() {
    std::cout << "Performing fast GPU calculations... Thread id: " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void do_slow_cpu_calc() {
    std::cout << "Performing slow CPU calculations... Thread id: " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

void calc(std::mutex &gpu) {
    std::unique_lock<std::mutex> lock{gpu, std::try_to_lock};
    if (lock.owns_lock()) {
        do_fast_kernel_magic();
    } else {
        do_slow_cpu_calc();
    }
}

int main() {
    std::mutex gpu;

    double start, end;
    
    start = rtclock();
    std::thread t1(calc, std::ref(gpu));
    std::thread t2(calc, std::ref(gpu));
    std::thread t3(calc, std::ref(gpu));

    t1.join();
    t2.join();
    t3.join();
    end = rtclock();

    std::cout << "Elapsed time: " << end - start << std::endl;

    return 0;
}