# Описание работы task.cu
Необходимо было реализовать пример с использованием конструкции 
cudaEventRecord. Поскольку она обычно используется для подсчета времени и для
синхронизации, программа демонстрирует оба функционала.

Были созданы события start и stop для блока, демонстрирующего подсчет времени,
а событие sync_event было создано для блока синхронизации потоков.

Первый блок (до 38 строки) демонстрирует подсчет времени, а именно, показано,
сколько времени требуется на заполнение векторов vec1 и vec2 и расчета их суммы
res в sumVec. Результат выводится на экран следующим образом:
```
Kernel execution time: <время> ms
```

Второй блок (после 38 строки) демонстрирует синхронизацию созданных потоков
stream1 и stream2, когда мы ожидаем завершения событий для обоих потоков в 
cudaStreamWaitEvent. На экран просто выводится сообщение об этом:
```
Streams synchronized after sync_event.
```

# Запуск программы
Во избежание фатальных экспериментов с ноутбуком, запуски производились на 
POLUS. Можно запустить с помощью Makefile:
```
make
```