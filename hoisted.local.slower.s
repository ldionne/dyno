hoisted, handrolled local vtable (slower)

__ZL17BM_any_5_functionIN12_GLOBAL__N_116handrolled_local3anyEEvRN9benchmark5StateE: ## @_ZL17BM_any_5_functionIN12_GLOBAL__N_116handrolled_local3anyEEvRN9benchmark5StateE
  .cfi_startproc
## BB#0:                                ## %entry
  pushq %rbp
Ltmp182:
  .cfi_def_cfa_offset 16
Ltmp183:
  .cfi_offset %rbp, -16
  movq  %rsp, %rbp
Ltmp184:
  .cfi_def_cfa_register %rbp
  pushq %r15
  pushq %r14
  pushq %r12
  pushq %rbx
  subq  $64, %rsp
Ltmp185:
  .cfi_offset %rbx, -48
Ltmp186:
  .cfi_offset %r12, -40
Ltmp187:
  .cfi_offset %r14, -32
Ltmp188:
  .cfi_offset %r15, -24
  movq  %rdi, %r12
  movq  __ZN12_GLOBAL__N_116handrolled_localL6vtableINS0_3any7model_tIiEEEE+32(%rip), %rax
  movq  %rax, -48(%rbp)
  movq  __ZN12_GLOBAL__N_116handrolled_localL6vtableINS0_3any7model_tIiEEEE+24(%rip), %rax
  movq  %rax, -56(%rbp)
  movq  __ZN12_GLOBAL__N_116handrolled_localL6vtableINS0_3any7model_tIiEEEE+16(%rip), %rax
  movq  %rax, -64(%rbp)
  movq  __ZN12_GLOBAL__N_116handrolled_localL6vtableINS0_3any7model_tIiEEEE+8(%rip), %rax
  movq  %rax, -72(%rbp)
  movq  __ZN12_GLOBAL__N_116handrolled_localL6vtableINS0_3any7model_tIiEEEE(%rip), %rax
  movq  %rax, -80(%rbp)
  movl  $4, %edi
  callq __Znwm
  movl  $0, (%rax)
  movq  %rax, -40(%rbp)
  movq  16(%r12), %rax
  movl  (%rax), %r14d
  testl %r14d, %r14d
  je  LBB26_1
## BB#6:
  leaq  -80(%rbp), %r15
  jmp LBB26_7
  .align  4, 0x90
LBB26_10:                               ## %while.body
                                        ##   in Loop: Header=BB26_7 Depth=1
  movq  %r15, -88(%rbp)
  ## InlineAsm Start
  ## InlineAsm End
  movl  %r14d, %ebx
  .align  4, 0x90
LBB26_11:                               ## %for.body
                                        ##   Parent Loop BB26_7 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
  movq  -40(%rbp), %rdi
  callq *-80(%rbp)
  movq  -40(%rbp), %rdi
  callq *-72(%rbp)
  movq  -40(%rbp), %rdi
  callq *-64(%rbp)
  movq  -40(%rbp), %rdi
  callq *-56(%rbp)
  movq  -40(%rbp), %rdi
  callq *-48(%rbp)
  decl  %ebx
  jne LBB26_11
  jmp LBB26_7
LBB26_8:                                ## %if.then.i
                                        ##   in Loop: Header=BB26_7 Depth=1
  movq  %r12, %rdi
  callq __ZN9benchmark5State16StartKeepRunningEv
  jmp LBB26_9
  .align  4, 0x90
LBB26_7:                                ## %while.cond
                                        ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB26_11 Depth 2
  movzbl  (%r12), %eax
  cmpl  $1, %eax
  jne LBB26_8
LBB26_9:                                ## %if.end.i
                                        ##   in Loop: Header=BB26_7 Depth=1
  movq  8(%r12), %rax
  leaq  1(%rax), %rcx
  movq  %rcx, 8(%r12)
  cmpq  96(%r12), %rax
  jb  LBB26_10
  jmp LBB26_12
LBB26_1:
  leaq  -80(%rbp), %rbx
  jmp LBB26_2
  .align  4, 0x90
LBB26_5:                                ## %while.body.us
                                        ##   in Loop: Header=BB26_2 Depth=1
  movq  %rbx, -96(%rbp)
  ## InlineAsm Start
  ## InlineAsm End
LBB26_2:                                ## %while.cond.us
                                        ## =>This Inner Loop Header: Depth=1
  movzbl  (%r12), %eax
  cmpl  $1, %eax
  jne LBB26_3
LBB26_4:                                ## %if.end.i.us
                                        ##   in Loop: Header=BB26_2 Depth=1
  movq  8(%r12), %rax
  leaq  1(%rax), %rcx
  movq  %rcx, 8(%r12)
  cmpq  96(%r12), %rax
  jb  LBB26_5
  jmp LBB26_12
LBB26_3:                                ## %if.then.i.us
                                        ##   in Loop: Header=BB26_2 Depth=1
  movq  %r12, %rdi
  callq __ZN9benchmark5State16StartKeepRunningEv
  jmp LBB26_4
LBB26_12:                               ## %while.end
  movq  %r12, %rdi
  callq __ZN9benchmark5State17FinishKeepRunningEv
  addq  $64, %rsp
  popq  %rbx
  popq  %r12
  popq  %r14
  popq  %r15
  popq  %rbp
  retq
  .cfi_endproc
