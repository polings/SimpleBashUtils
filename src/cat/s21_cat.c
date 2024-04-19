#include "s21_cat.h"

int main(int argc, char **argv) {
  flag conf = {0};
  if (argc > 1) {
    // Получение списка флагов и сохранение их состояния в структуре conf
    if (parseParam(argc, argv, &conf) == 0) {
      // Чтение файлов и вывод содержимого на экран
      printFile(argc, argv, conf);
    }
    return 0;
  }
}
