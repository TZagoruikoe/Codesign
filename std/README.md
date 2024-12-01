# Описание работы task.cpp
Необходимо было реализовать пример с использованием std::try_to_lock_t. Поскольку, 
фактически, это тип, который имеет константа std::try_to_lock, программа будет об
ее применении.
std::try_to_lock передается для указания типа стратегии блокировок, и позволяет
избежать блокировок, поэтому в программе task.cpp продемонстрирована работа нескольких 
потоков, которые одновременно пытаются захватить один мьютекс, но если один из потоков 
успевает захватить мьютекс, он выполнит некоторые вычисления на условном ГПУ, 
имитированные в do_fast_kernel_magic. При этом другие потоки, вместо блокировок, 
выполнят свою работу на условном ЦПУ в do_slow_cpu_calc.

# Запуск программы
Можно запустить с помощью Makefile
```
make clean && make
```