  global main
  extern printf
      
  segment .bss
  month$1 resq 1
  year$2 resq 1
  day$3 resq 1
  h$4 resq 1
  firstday$7 resq 1
  lastday$6 resq 1
  tmp$8 resq 1
  dday$5 resq 1
  nrows$9 resq 1
  row$10 resq 1
  colday$11 resq 1
  year$12 resq 1
  month$13 resq 1
    
    
  section .text
main:
  mov rax,12
  push rax
  pop qword[month$1]
  mov rax,2016
  push rax
  pop qword[year$2]
  push qword[month$1]
  mov rax,1
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  je J1
  mov rax,0
  jmp J2
J1:
  mov rax, 1
J2:
  push rax
  push qword[month$1]
  mov rax,2
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  je J3
  mov rax,0
  jmp J4
J3:
  mov rax, 1
J4:
  push rax
  pop rbx
  pop rax
  or rax,rbx
  push rax
  pop rax
  cmp rax, 0
  je L2
  push qword[month$1]
  mov rax,12
  push rax
  pop rbx
  pop rax
  add rax,rbx
  push rax
  pop qword[month$1]
  push qword[year$2]
  mov rax,1
  push rax
  pop rbx
  pop rax
  sub rax,rbx
  push rax
  pop qword[year$2]
L2:
  mov rax,1
  push rax
  pop qword[day$3]
  push qword[day$3]
  push qword[month$1]
  mov rax,1
  push rax
  pop rbx
  pop rax
  add rax,rbx
  push rax
  mov rax,26
  push rax
  pop rbx
  pop rax
  imul rax,rbx
  push rax
  mov rax,10
  push rax
  mov rdx,0
  pop rbx
  pop rax
  idiv rbx
  push rax
  pop rbx
  pop rax
  add rax,rbx
  push rax
  push qword[year$2]
  pop rbx
  pop rax
  add rax,rbx
  push rax
  push qword[year$2]
  mov rax,4
  push rax
  mov rdx,0
  pop rbx
  pop rax
  idiv rbx
  push rax
  pop rbx
  pop rax
  add rax,rbx
  push rax
  mov rax,6
  push rax
  push qword[year$2]
  mov rax,100
  push rax
  mov rdx,0
  pop rbx
  pop rax
  idiv rbx
  push rax
  pop rbx
  pop rax
  imul rax,rbx
  push rax
  pop rbx
  pop rax
  add rax,rbx
  push rax
  push qword[year$2]
  mov rax,400
  push rax
  mov rdx,0
  pop rbx
  pop rax
  idiv rbx
  push rax
  pop rbx
  pop rax
  add rax,rbx
  push rax
  pop qword[h$4]
  push qword[h$4]
  push qword[h$4]
  mov rax,7
  push rax
  mov rdx,0
  pop rbx
  pop rax
  idiv rbx
  push rax
  mov rax,7
  push rax
  pop rbx
  pop rax
  imul rax,rbx
  push rax
  pop rbx
  pop rax
  sub rax,rbx
  push rax
  pop qword[firstday$7]
  push qword[month$1]
  mov rax,12
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  jg J5
  mov rax,0
  jmp J6
J5:
  mov rax, 1
J6:
  push rax
  pop rax
  cmp rax, 0
  je L4
  push qword[month$1]
  mov rax,12
  push rax
  pop rbx
  pop rax
  sub rax,rbx
  push rax
  pop qword[month$1]
  push qword[year$2]
  mov rax,1
  push rax
  pop rbx
  pop rax
  add rax,rbx
  push rax
  pop qword[year$2]
L4:
  mov rax,0
  push rax
  pop qword[lastday$6]
  push qword[month$1]
  mov rax,4
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  je J7
  mov rax,0
  jmp J8
J7:
  mov rax, 1
J8:
  push rax
  push qword[month$1]
  mov rax,6
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  je J9
  mov rax,0
  jmp J10
J9:
  mov rax, 1
J10:
  push rax
  pop rbx
  pop rax
  or rax,rbx
  push rax
  push qword[month$1]
  mov rax,9
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  je J11
  mov rax,0
  jmp J12
J11:
  mov rax, 1
J12:
  push rax
  pop rbx
  pop rax
  or rax,rbx
  push rax
  push qword[month$1]
  mov rax,11
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  je J13
  mov rax,0
  jmp J14
J13:
  mov rax, 1
J14:
  push rax
  pop rbx
  pop rax
  or rax,rbx
  push rax
  pop rax
  cmp rax, 0
  je L6
  mov rax,30
  push rax
  pop qword[lastday$6]
  jmp L7
L6:
  push qword[month$1]
  mov rax,2
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  jne J15
  mov rax,0
  jmp J16
J15:
  mov rax, 1
J16:
  push rax
  pop rax
  cmp rax, 0
  je L8
  mov rax,31
  push rax
  pop qword[lastday$6]
  jmp L9
L8:
  push qword[year$2]
  call leapyear
  push rax
  pop rax
  cmp rax, 0
  je L10
  mov rax,29
  push rax
  pop qword[lastday$6]
  jmp L11
L10:
  mov rax,28
  push rax
  pop qword[lastday$6]
L11:
L9:
L7:
  push qword[month$1]
  call printmonth
  push rax
  pop qword[tmp$8]
  mov    rdi,fmt1
  mov    rax,0
  push   rbp
  call   printf
  pop    rbp
  mov rax,2
  push rax
  push qword[firstday$7]
  pop rbx
  pop rax
  sub rax,rbx
  push rax
  pop qword[dday$5]
  push qword[firstday$7]
  push qword[lastday$6]
  pop rbx
  pop rax
  add rax,rbx
  push rax
  mov rax,7
  push rax
  mov rdx,0
  pop rbx
  pop rax
  idiv rbx
  push rax
  mov rax,1
  push rax
  pop rbx
  pop rax
  add rax,rbx
  push rax
  pop qword[nrows$9]
  mov rax,1
  push rax
  pop qword[row$10]
L12:
  push qword[row$10]
  push qword[nrows$9]
  pop rbx
  pop rax
  cmp rax,rbx
  jle J17
  mov rax,0
  jmp J18
J17:
  mov rax, 1
J18:
  push rax
  pop rax
  cmp rax, 0
  je L13
  mov rax,1
  push rax
  pop qword[colday$11]
L14:
  push qword[colday$11]
  mov rax,7
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  jle J19
  mov rax,0
  jmp J20
J19:
  mov rax, 1
J20:
  push rax
  pop rax
  cmp rax, 0
  je L15
  push qword[dday$5]
  mov rax,1
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  jl J21
  mov rax,0
  jmp J22
J21:
  mov rax, 1
J22:
  push rax
  push qword[dday$5]
  push qword[lastday$6]
  pop rbx
  pop rax
  cmp rax,rbx
  jg J23
  mov rax,0
  jmp J24
J23:
  mov rax, 1
J24:
  push rax
  pop rbx
  pop rax
  or rax,rbx
  push rax
  pop rax
  cmp rax, 0
  je L16
  mov    rdi,fmt2
  mov    rax,0
  push   rbp
  call   printf
  pop    rbp
  jmp L17
L16:
  push qword[dday$5]
  mov    rdi,fmt3
  pop   rsi
  mov    rax,0
  push   rbp
  call   printf
  pop    rbp
L17:
  push qword[colday$11]
  mov rax,1
  push rax
  pop rbx
  pop rax
  add rax,rbx
  push rax
  pop qword[colday$11]
  push qword[dday$5]
  mov rax,1
  push rax
  pop rbx
  pop rax
  add rax,rbx
  push rax
  pop qword[dday$5]
  jmp L14
L15:
  mov    rdi,fmt4
  mov    rax,0
  push   rbp
  call   printf
  pop    rbp
  push qword[row$10]
  mov rax,1
  push rax
  pop rbx
  pop rax
  add rax,rbx
  push rax
  pop qword[row$10]
  jmp L12
L13:
  mov    rdi,fmt5
  mov    rax,0
  push   rbp
  call   printf
  pop    rbp
  mov rax,0
  push rax
  pop rax
  ret
leapyear:
  pop r15
  pop qword[year$12]
  push qword[year$12]
  mov rax,4
  push rax
  mov rdx,0
  pop rbx
  pop rax
  idiv rbx
  push rax
  mov rax,4
  push rax
  pop rbx
  pop rax
  imul rax,rbx
  push rax
  push qword[year$12]
  pop rbx
  pop rax
  cmp rax,rbx
  jne J25
  mov rax,0
  jmp J26
J25:
  mov rax, 1
J26:
  push rax
  pop rax
  cmp rax, 0
  je L18
  mov rax,0
  push rax
  pop rax
  push r15
  ret
L18:
  push qword[year$12]
  mov rax,100
  push rax
  mov rdx,0
  pop rbx
  pop rax
  idiv rbx
  push rax
  mov rax,100
  push rax
  pop rbx
  pop rax
  imul rax,rbx
  push rax
  push qword[year$12]
  pop rbx
  pop rax
  cmp rax,rbx
  jne J27
  mov rax,0
  jmp J28
J27:
  mov rax, 1
J28:
  push rax
  pop rax
  cmp rax, 0
  je L20
  mov rax,1
  push rax
  pop rax
  push r15
  ret
L20:
  push qword[year$12]
  mov rax,400
  push rax
  mov rdx,0
  pop rbx
  pop rax
  idiv rbx
  push rax
  mov rax,400
  push rax
  pop rbx
  pop rax
  imul rax,rbx
  push rax
  push qword[year$12]
  pop rbx
  pop rax
  cmp rax,rbx
  je J29
  mov rax,0
  jmp J30
J29:
  mov rax, 1
J30:
  push rax
  pop rax
  cmp rax, 0
  je L22
  mov rax,1
  push rax
  pop rax
  push r15
  ret
L22:
  mov rax,0
  push rax
  pop rax
  push r15
  ret
printmonth:
  pop r15
  pop qword[month$13]
  push qword[month$13]
  mov rax,1
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  je J31
  mov rax,0
  jmp J32
J31:
  mov rax, 1
J32:
  push rax
  pop rax
  cmp rax, 0
  je L24
  mov    rdi,fmt6
  mov    rax,0
  push   rbp
  call   printf
  pop    rbp
  mov rax,0
  push rax
  pop rax
  push r15
  ret
L24:
  push qword[month$13]
  mov rax,2
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  je J33
  mov rax,0
  jmp J34
J33:
  mov rax, 1
J34:
  push rax
  pop rax
  cmp rax, 0
  je L26
  mov    rdi,fmt7
  mov    rax,0
  push   rbp
  call   printf
  pop    rbp
  mov rax,0
  push rax
  pop rax
  push r15
  ret
L26:
  push qword[month$13]
  mov rax,3
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  je J35
  mov rax,0
  jmp J36
J35:
  mov rax, 1
J36:
  push rax
  pop rax
  cmp rax, 0
  je L28
  mov    rdi,fmt8
  mov    rax,0
  push   rbp
  call   printf
  pop    rbp
  mov rax,0
  push rax
  pop rax
  push r15
  ret
L28:
  push qword[month$13]
  mov rax,4
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  je J37
  mov rax,0
  jmp J38
J37:
  mov rax, 1
J38:
  push rax
  pop rax
  cmp rax, 0
  je L30
  mov    rdi,fmt9
  mov    rax,0
  push   rbp
  call   printf
  pop    rbp
  mov rax,0
  push rax
  pop rax
  push r15
  ret
L30:
  push qword[month$13]
  mov rax,5
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  je J39
  mov rax,0
  jmp J40
J39:
  mov rax, 1
J40:
  push rax
  pop rax
  cmp rax, 0
  je L32
  mov    rdi,fmt10
  mov    rax,0
  push   rbp
  call   printf
  pop    rbp
  mov rax,0
  push rax
  pop rax
  push r15
  ret
L32:
  push qword[month$13]
  mov rax,6
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  je J41
  mov rax,0
  jmp J42
J41:
  mov rax, 1
J42:
  push rax
  pop rax
  cmp rax, 0
  je L34
  mov    rdi,fmt11
  mov    rax,0
  push   rbp
  call   printf
  pop    rbp
  mov rax,0
  push rax
  pop rax
  push r15
  ret
L34:
  push qword[month$13]
  mov rax,7
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  je J43
  mov rax,0
  jmp J44
J43:
  mov rax, 1
J44:
  push rax
  pop rax
  cmp rax, 0
  je L36
  mov    rdi,fmt12
  mov    rax,0
  push   rbp
  call   printf
  pop    rbp
  mov rax,0
  push rax
  pop rax
  push r15
  ret
L36:
  push qword[month$13]
  mov rax,8
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  je J45
  mov rax,0
  jmp J46
J45:
  mov rax, 1
J46:
  push rax
  pop rax
  cmp rax, 0
  je L38
  mov    rdi,fmt13
  mov    rax,0
  push   rbp
  call   printf
  pop    rbp
  mov rax,0
  push rax
  pop rax
  push r15
  ret
L38:
  push qword[month$13]
  mov rax,9
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  je J47
  mov rax,0
  jmp J48
J47:
  mov rax, 1
J48:
  push rax
  pop rax
  cmp rax, 0
  je L40
  mov    rdi,fmt14
  mov    rax,0
  push   rbp
  call   printf
  pop    rbp
  mov rax,0
  push rax
  pop rax
  push r15
  ret
L40:
  push qword[month$13]
  mov rax,10
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  je J49
  mov rax,0
  jmp J50
J49:
  mov rax, 1
J50:
  push rax
  pop rax
  cmp rax, 0
  je L42
  mov    rdi,fmt15
  mov    rax,0
  push   rbp
  call   printf
  pop    rbp
  mov rax,0
  push rax
  pop rax
  push r15
  ret
L42:
  push qword[month$13]
  mov rax,11
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  je J51
  mov rax,0
  jmp J52
J51:
  mov rax, 1
J52:
  push rax
  pop rax
  cmp rax, 0
  je L44
  mov    rdi,fmt16
  mov    rax,0
  push   rbp
  call   printf
  pop    rbp
  mov rax,0
  push rax
  pop rax
  push r15
  ret
L44:
  push qword[month$13]
  mov rax,12
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  je J53
  mov rax,0
  jmp J54
J53:
  mov rax, 1
J54:
  push rax
  pop rax
  cmp rax, 0
  je L46
  mov    rdi,fmt17
  mov    rax,0
  push   rbp
  call   printf
  pop    rbp
  mov rax,0
  push rax
  pop rax
  push r15
  ret
L46:
  mov rax,1
  push rax
  pop rax
  push r15
  ret

  section .data
  fmt1: db `Su Mo Tu We Th Fr Sa\n`, 0
  fmt2: db `   `, 0
  fmt3: db `%2d `, 0
  fmt4: db `\n`, 0
  fmt5: db `\n`, 0
  fmt6: db `       January\n`, 0
  fmt7: db `      February\n`, 0
  fmt8: db `        March\n`, 0
  fmt9: db `        April\n`, 0
  fmt10: db `         May\n`, 0
  fmt11: db `        June\n`, 0
  fmt12: db `        July\n`, 0
  fmt13: db `       August\n`, 0
  fmt14: db `      September\n`, 0
  fmt15: db `       October\n`, 0
  fmt16: db `      November\n`, 0
  fmt17: db `      December\n`, 0
