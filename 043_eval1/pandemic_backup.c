#include "pandemic.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;

  if (strlen(line) == 0) {
    //* check if line is empty
    fprintf(stderr, "error: line empty, exit\n");
    exit(EXIT_FAILURE);
  }

  if (strchr(line, ',') == NULL) {
    //* check delimiter
    fprintf(stderr, "error: line does not contain ',', exit\n");
    exit(EXIT_FAILURE);
  }

  if (line[0] == ',') {
    //* check empty country name
    fprintf(stderr, "error: country name empty, exit\n");
    exit(EXIT_FAILURE);
  }

  //* ----- parsing country name ----- */
  int i = 0;
  while (line[i] != ',') {
    if (i >= 63) {
      //* check country name length
      fprintf(stderr, "error: name contains more than 64 chars, exit\n");
      exit(EXIT_FAILURE);
    }
    ans.name[i] = line[i];
    i++;
  }
  ans.name[i] = '\0';
  i++;

  //* ----- parsing population -----*/
  if (line[i] == '\n') {
    fprintf(stderr, "error: no population followed by country, exit\n");
    exit(EXIT_FAILURE);
  }

  /*
  uint64_t populationTemp = ans.population;

  while (line[i] != '\n') {
    if (line[i] == ',') {  // check for extra delimiter
      fprintf(stderr, "error: line contains more than 1 delimiter, exit\n");
      exit(EXIT_FAILURE);
    }
    if (!isdigit(line[i])) {  // check if char is number
      fprintf(stderr, "error: char not a number, exit\n");
      exit(EXIT_FAILURE);
    }
    ans.population = populationTemp * 10 + line[i] - '0';
    if (ans.population < populationTemp) {  // check for uint_64 overflow
      fprintf(stderr, "error: uint64_t overflowed, exit\n");
      exit(EXIT_FAILURE);
    }
    populationTemp = ans.population;
    i++;
  }
  */
  ans.population = atoi(line + i);

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME

  if (n_days <= 0) {
    fprintf(stderr, "error: number of days < 0, exit\n");
    exit(EXIT_FAILURE);
  }

  if (n_days < 7) {
    //* check if n_days < 7
    //fprintf(stderr, "error: total number of days less than 7, exit\n");
    //exit(EXIT_FAILURE);

    double sum = 0;
    for (size_t i = 0; i < n_days; i++) {
      sum += data[i];
    }
    avg[0] = sum / n_days;
    return;
  }

  for (size_t i = 0; i < n_days - 6; i++) {
    if (data[i] < 0) {
      fprintf(stderr, "error: daily cases contain negative number, exit\n");
      exit(EXIT_FAILURE);
    }
    double sum = 0;
    for (size_t j = i; j < i + 7; j++) {
      sum += data[j];
    }
    avg[i] = sum / 7;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  //* check n_days not negative
  if (n_days < 0) {
    fprintf(stderr, "error: n_days less than 0, exit\n");
    exit(EXIT_FAILURE);
  }
  if (pop < 0) {
    fprintf(stderr, "error: population less than 0\n");
  }

  double sum = 0;

  for (size_t i = 0; i < n_days; i++) {
    if (data[i] < 0) {
      fprintf(stderr, "error: daily cases contain negative number, exit\n");
      exit(EXIT_FAILURE);
    }
    sum += data[i];
    cum[i] = (sum / pop) * 100000;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  unsigned max = data[0][0];
  country_t countryMaxCnt = countries[0];
  int tie = 0;

  for (size_t i = 0; i < n_days; i++) {
    for (size_t j = 0; j < n_countries; j++) {
      if (data[j][i] < 0) {
        //* check for entries < 0
        fprintf(stderr, "error: data entry less than 0, exit\n");
        exit(EXIT_FAILURE);
      }
      if (i == 0 && j == 0) {
        //* skip data[0][0], already used to initialize max
        continue;
      }
      if (data[j][i] > max) {
        //* when new max found, rewrite max and country, clear tie
        max = data[j][i];
        countryMaxCnt = countries[j];
        tie = 0;
      }
      else if (data[j][i] == max && strcmp(countryMaxCnt.name, countries[j].name) != 0) {
        //* when tie found from different country, increment tie
        tie++;
      }
    }
  }

  if (tie > 0) {
    printf("There is a tie between at least two countries\n");
  }
  else {
    printf("%s has the most daily cases with %u\n", countryMaxCnt.name, max);
  }
}
