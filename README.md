# Three — контейнер для троичных чисел

Небольшая библиотека/демо, реализующая неизменяемый класс `Three` для работы с неотрицательными числами в троичной системе.

## Требования и соответствие

- **Интерфейс/реализация**: `include/Three.h` и `src/Three.cpp`.
- **Исключения**: проверка входных данных и ошибки вычитания — стандартные исключения (`std::invalid_argument`).
- **Арифметика**: методы `Sum`, `Sub` возвращают новые объекты.
- **Сравнение**: `Equal`, `Less`, `More`.
- **Неизменяемость**: исходные объекты не меняются; есть `ToString()` для проверки.

## Сборка

```bash
# из корня репозитория
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

## Запуск демо

```bash
./build/three_app
```

## Тесты (GoogleTest)

```bash
ctest --test-dir build --output-on-failure
# либо напрямую
./build/three_tests
```

## Структура

- `include/Three.h` — интерфейс класса
- `src/Three.cpp` — реализация
- `src/main.cpp` — небольшое демо
- `tests/ThreeTests.cpp` — модульные тесты
- `docs/analysis.md` — анализ соответствия требованиям
