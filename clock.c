// October 25 2017 Wed 11:57 PM
// clock.c
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#ifdef linux
  #include <unistd.h>
#elif _WIN32
  #include <windows.h> // Sleep(1000);
#endif

#define ROW 11
#define COL 61
#define DigitHeight 11
#define DigitWidth 7
#define CHAR_V '|'      // char to represent clock, you can change this
#define CHAR_H '-'      // this too
#define CHAR_COL '@'    // and this

char _clock[ROW * COL];

static inline int
idx(int i, int j) {
  return i * COL + j;
}

void
printClock() {
  int i, j;
  for (i = 0; i < ROW; i++) {
    for (j = 0; j < COL; ++j) {
      putchar(_clock[idx(i, j)]);
    }
    putchar('\n');
  }
}

// h for horizontal and v for vertical
static void
writeBar(const int _i,const int _j,const int _len, const char _ch) { 
  int k;
  if (_ch == 'v') {
    for (k = _i; k < _i + _len; ++k)
      _clock[idx(k, _j)] = CHAR_V;
  } else if (_ch == 'h') {
    for (k = _j; k < _j + _len; ++k)
      _clock[idx(_i, k)] = CHAR_H;
  }
}

static void
writeColon(const int j) {
  _clock[idx(2, j)] = CHAR_COL;
  _clock[idx(3, j)] = CHAR_COL;
  _clock[idx(7, j)] = CHAR_COL;
  _clock[idx(8, j)] = CHAR_COL;
}

void
clearData() {
  int i;
  for (i = 0; i < ROW * COL; ++i)
    _clock[i] = ' ';
}

static void
writeDigit(const int _i, const int _j, const int digit) {
  switch (digit) {
    case 0:
      writeBar(_i + 1 , _j    , 4, 'v'); // upper left vertical
      writeBar(_i + 6 , _j    , 4, 'v'); // lower left vertical
      writeBar(_i + 1 , _j + 7, 4, 'v'); // upper right vertical
      writeBar(_i + 6 , _j + 7, 4, 'v'); // lower right vertical
      writeBar(_i     , _j + 1, 6, 'h'); // upper horizontal
      writeBar(_i + 10, _j + 1, 6, 'h'); // lower horizontal
      break;
    case 1:
      writeBar(_i + 1 , _j + 7, 4, 'v'); // upper right vertical
      writeBar(_i + 6 , _j + 7, 4, 'v'); // lower right vertical
      break;
    case 2:
      writeBar(_i + 6 , _j    , 4, 'v'); // lower left vertical
      writeBar(_i + 1 , _j + 7, 4, 'v'); // upper right vertical
      writeBar(_i     , _j + 1, 6, 'h'); // upper horizontal
      writeBar(_i + 10, _j + 1, 6, 'h'); // lower horizontal
      writeBar(_i + 5 , _j + 1, 6, 'h'); // middle horizontal
      break;
    case 3:
      writeBar(_i + 1 , _j + 7, 4, 'v'); // upper right vertical
      writeBar(_i + 6 , _j + 7, 4, 'v'); // lower right vertical
      writeBar(_i     , _j + 1, 6, 'h'); // upper horizontal
      writeBar(_i + 10, _j + 1, 6, 'h'); // lower horizontal
      writeBar(_i + 5 , _j + 1, 6, 'h'); // middle horizontal
      break;
    case 4:
      writeBar(_i + 1 , _j    , 4, 'v'); // upper left vertical
      writeBar(_i + 1 , _j + 7, 4, 'v'); // upper right vertical
      writeBar(_i + 6 , _j + 7, 4, 'v'); // lower right vertical
      writeBar(_i + 5 , _j + 1, 6, 'h'); // middle horizontal
      break;
    case 5:
      writeBar(_i + 1 , _j    , 4, 'v'); // upper left vertical
      writeBar(_i + 6 , _j + 7, 4, 'v'); // lower right vertical
      writeBar(_i     , _j + 1, 6, 'h'); // upper horizontal
      writeBar(_i + 10, _j + 1, 6, 'h'); // lower horizontal
      writeBar(_i + 5 , _j + 1, 6, 'h'); // middle horizontal
      break;
    case 6:
      writeBar(_i + 1 , _j    , 4, 'v'); // upper left vertical
      writeBar(_i + 6 , _j    , 4, 'v'); // lower left vertical
      writeBar(_i + 6 , _j + 7, 4, 'v'); // lower right vertical
      writeBar(_i     , _j + 1, 6, 'h'); // upper horizontal
      writeBar(_i + 10, _j + 1, 6, 'h'); // lower horizontal
      writeBar(_i + 5 , _j + 1, 6, 'h'); // middle horizontal
      break;
    case 7:
      writeBar(_i + 1 , _j + 7, 4, 'v'); // upper right vertical
      writeBar(_i + 6 , _j + 7, 4, 'v'); // lower right vertical
      writeBar(_i     , _j + 1, 6, 'h'); // upper horizontal
      break;
    case 8:
      writeBar(_i + 1 , _j    , 4, 'v'); // upper left vertical
      writeBar(_i + 6 , _j    , 4, 'v'); // lower left vertical
      writeBar(_i + 1 , _j + 7, 4, 'v'); // upper right vertical
      writeBar(_i + 6 , _j + 7, 4, 'v'); // lower right vertical
      writeBar(_i     , _j + 1, 6, 'h'); // upper horizontal
      writeBar(_i + 10, _j + 1, 6, 'h'); // lower horizontal
      writeBar(_i + 5 , _j + 1, 6, 'h'); // middle horizontal
      break;
    case 9:
      writeBar(_i + 1 , _j    , 4, 'v'); // upper left vertical
      writeBar(_i + 1 , _j + 7, 4, 'v'); // upper right vertical
      writeBar(_i + 6 , _j + 7, 4, 'v'); // lower right vertical
      writeBar(_i     , _j + 1, 6, 'h'); // upper horizontal
      writeBar(_i + 10, _j + 1, 6, 'h'); // lower horizontal
      writeBar(_i + 5 , _j + 1, 6, 'h'); // middle horizontal
      break;
  }
}

void
BuildClock() {
  time_t rawtime;
  struct tm *timeinfo;

  int hour, min, sec, a, b;

  for (;;) {
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    clearData();

    hour = timeinfo->tm_hour;
    if (hour > 12)
      hour -= 12;
    b = hour % 10;
    a = hour / 10;

    if (a)
      writeDigit(0, 0, a);
    writeDigit(0, 9, b);

    min = timeinfo->tm_min;
    b = min % 10;
    a = min / 10;

    writeDigit(0, 22, a);
    writeDigit(0, 31, b);

    sec = timeinfo->tm_sec;
    b = sec % 10;
    a = sec / 10;

    writeDigit(0, 44, a);
    writeDigit(0, 53, b);

    if (b & 1) {
      writeColon(19);
      writeColon(41);
    }

    printClock();

#ifdef linux
    sleep(1);
    system("clear");
#elif _WIN32
    Sleep(1000);
    system("cls");
#endif

  }
}

int main() {
  BuildClock();
  return 0;
}
