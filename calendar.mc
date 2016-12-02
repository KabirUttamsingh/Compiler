function main() {
  var month, year, day, h, dday, lastday, firstday;

  month = 12;
  year = 2016;

  if (month == 1 || month == 2) {
    month = month + 12;
    year = year - 1;
  }
  
  day = 1;
  h = (day + (month + 1) * 26 / 10 + year + year/4 + 6 * (year/100) + year/400);
  firstday = h - h/7 * 7; 
        
  if (month > 12 ) {
    month = month - 12;
    year = year + 1;
  }

  lastday = 0;
  if (month == 4 || month == 6 || month == 9 || month == 11) {
    lastday = 30;
  } else { 
    if (month != 2) {
      lastday = 31;
    } else {
      if (leapyear(year)) {
        lastday = 29;
      } else {
        lastday = 28;
      }
    }
  }

  var tmp;
  tmp = printmonth(month);
  printf("Su Mo Tu We Th Fr Sa\n");
  var nrows, row, colday;
  dday = 2 - firstday;
  nrows = (firstday + lastday)/7 + 1;
  row = 1;
  while (row <= nrows) {
    colday = 1; 
    while (colday <= 7) {
      if (dday < 1 || dday > lastday) {
        printf("   ");
      } else {
        printf("%2d ", dday);
      }
      colday = colday + 1;
      dday = dday + 1;
    }
    printf("\n");
    row = row + 1;
  }
  printf("\n");
  return 0;
}

function leapyear(year) {
  if (year / 4 * 4 != year) {
    return 0;
  }
  if (year / 100 * 100 != year) {
    return 1;
  }
  if (year / 400 * 400 == year) {
    return 1;
  }
  return 0;
}

function printmonth(month) {
  if (month == 1) {
    printf("       January\n");
    return 0;
  } 
  if (month == 2) {
    printf("      February\n");
    return 0;
  }
  if (month == 3) {
    printf("        March\n");
    return 0;
  }
  if (month == 4) {
    printf("        April\n");
    return 0;
  }
  if (month == 5) {
    printf("         May\n");
    return 0;
  }
  if (month == 6) {
    printf("        June\n");
    return 0;
  }
  if (month == 7) {
    printf("        July\n");
    return 0;
  }
  if (month == 8) {
    printf("       August\n");
    return 0;
  }
  if (month == 9) {
    printf("      September\n");
    return 0;
  }
  if (month == 10) {
    printf("       October\n");
    return 0;
  }
  if (month == 11) {
    printf("      November\n");
    return 0;
  }
  if (month == 12) {
    printf("      December\n");
    return 0;
  }
  return 1;
}