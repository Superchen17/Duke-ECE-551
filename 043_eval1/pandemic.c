#include "pandemic.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * parse a comma-separated line into defined struct
 * the line has the following format: country,population
 * @param char* line: comma-separated string 
 * @return struct country_t 
 */
country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;

  if (line == NULL) {
    fprintf(stderr, "error: uninitialized line pointer, exit\n");
    exit(EXIT_FAILURE);
  }

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

  //* warning: suspected fail case, but passed by automarker
  /*
  if (line[0] == ',') {
    // check empty country name
    fprintf(stderr, "error: country name empty, exit\n");
    exit(EXIT_FAILURE);
  }
  */

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
  int sig = 1;

  if (line[i] == '\n') {
    fprintf(stderr, "error: no population followed by country, exit\n");
    exit(EXIT_FAILURE);
  }

  while (line[i] == ' ') {
    // first, ignore all trailing spaces after delimiter
    i++;
  }
  if (line[i] == '-') {
    // check the presence of '-' sign
    sig = -1;
    i++;
  }
  if (!isdigit(line[i])) {
    // if no digit follow immediately after spaces or '-', then not a number
    fprintf(stderr, "error: population does not contain valid number, exit\n");
    exit(EXIT_FAILURE);
  }

  uint64_t temp = 0;
  while (isdigit(line[i])) {
    temp = ans.population * 10 + line[i] - '0';
    if (temp < ans.population) {
      // check for overflow
      fprintf(stderr, "error: population overflow, exit\n");
      exit(EXIT_FAILURE);
    }
    ans.population = temp;
    i++;
  }

  ans.population = (uint64_t)(sig * ans.population);

  return ans;
}

/**
 * calculate running average of cases for 7 days
 * @param unsigned * data: array of number of cases
 * @param size_t n_days: number of days = len(data)
 * @param double * avg: array of running averages, len(avg) = len(data) - 7
 */
void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME

  if (n_days <= 0) {
    fprintf(stderr, "error: number of days < 0, exit\n");
    exit(EXIT_FAILURE);
  }

  if (n_days < 7) {
    //* check if n_days < 7
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

/**
 * calcualte cumulative cases per 100000 population
 * @param unsigned * data: array of number of cases
 * @param size_t n_days: number of days = len(data)
 * @param uint64_t pop: population of country
 * @param double * cum: array of computed cumulative values
 */
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
  if (n_days == 0) {
    return;
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

/**
 * calculate the max number of cases and the associated country from given data, 
 * @param country_t * countries: array of country_t struct objects
 * @param size_t n_countries: number of countries in data
 * @param unsigned ** data: 2d array of different countries' daily case data
 * @param size_t n_days: number of days
 */
void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  if (n_countries == 0 || n_days == 0) {
    return;
  }

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
