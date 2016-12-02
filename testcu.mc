function main() {
  var i, sum;
  i = 1;
  sum = 0;
  printf("  i   sum\n");
  while (i < 10) {
    i = add(i, 1);
    sum = add(sum, i);
    printf("  %ld   %ld\n", i, sum);
  }
  return 0;
}

function add(a1, a2) {
  var a;
  a = a1 + a2;
  return a;
}

