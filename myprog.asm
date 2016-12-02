  global main
  extern printf
      
  segment .bss
  a$1 resq 1
  b$2 resq 1
  c$3 resq 1
    
    
  section .text
main:
  mov rax,23
  push rax
  pop qword[a$1]
  mov rax,24
  push rax
  pop qword[b$2]
  push qword[a$1]
  push qword[b$2]
  pop rbx
  pop rax
  imul rax,rbx
  push rax
  mov rax,25
  push rax
  pop rbx
  pop rax
  add rax,rbx
  push rax
  pop qword[c$3]
L2:
  push qword[a$1]
  mov rax,30
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  jl J1
  mov rax,0
  jmp J2
J1:
  mov rax, 1
J2:
  push rax
  pop rax
  cmp rax, 0
  je L3
  push qword[a$1]
  mov rax,1
  push rax
  pop rbx
  pop rax
  add rax,rbx
  push rax
  pop qword[a$1]
  jmp L2
L3:
  push qword[a$1]
  push qword[c$3]
  mov rax,2
  push rax
  pop rbx
  pop rax
  imul rax,rbx
  push rax
  pop rbx
  pop rax
  add rax,rbx
  push rax
  mov rax,16
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  jl J3
  mov rax,0
  jmp J4
J3:
  mov rax, 1
J4:
  push rax
  push qword[a$1]
  mov rax,8
  push rax
  pop rbx
  pop rax
  cmp rax,rbx
  jge J5
  mov rax,0
  jmp J6
J5:
  mov rax, 1
J6:
  push rax
  pop rbx
  pop rax
  and rax,rbx
  push rax
  pop rax
  cmp rax, 0
  je L4
  mov rax,5
  push rax
  pop qword[c$3]
  jmp L5
L4:
  mov rax,123456
  push rax
  pop qword[c$3]
  push qword[a$1]
  push qword[b$2]
  mov    rdi,fmt1
  pop   rdx
  pop   rsi
  mov    rax,0
  push   rbp
  call   printf
  pop    rbp
L5:

  section .data
  fmt1: db `%ld %ld\n`, 0
