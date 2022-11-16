#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double total = initial;
  int timestampYear = startAge / 12;
  int timestampMonth = startAge % 12;

  for (int i = 0; i < working.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", timestampYear, timestampMonth, total);
    total = total * (1 + working.rate_of_return) + working.contribution;

    timestampMonth++;
    if (timestampMonth == 12) {
      timestampMonth = 0;
      timestampYear++;
    }
  }

  for (int i = 0; i < retired.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", timestampYear, timestampMonth, total);
    total = total * (1 + retired.rate_of_return) + retired.contribution;

    timestampMonth++;
    if (timestampMonth == 12) {
      timestampMonth = 0;
      timestampYear++;
    }
  }
}

int main() {
  retire_info working = {489, 1000, 0.045 / 12};
  retire_info retire = {384, -4000, 0.01 / 12};

  retirement(327, 21345, working, retire);

  return 0;
}
