hoisted, handrolled remote vtable (faster)

__ZL17BM_any_5_functionIN12_GLOBAL__N_117handrolled_remote3anyEEvRN9benchmark5StateE: ## @_ZL17BM_any_5_functionIN12_GLOBAL__N_117handrolled_remote3anyEEvRN9benchmark5StateE
  .cfi_startproc
## BB#0:                                ## %entry
  pushq %rbp
Ltmp175:
  .cfi_def_cfa_offset 16
Ltmp176:
  .cfi_offset %rbp, -16
  movq  %rsp, %rbp
Ltmp177:
  .cfi_def_cfa_register %rbp
  pushq %r15
  pushq %r14
  pushq %r12
  pushq %rbx
  subq  $32, %rsp
Ltmp178:
  .cfi_offset %rbx, -48
Ltmp179:
  .cfi_offset %r12, -40
Ltmp180:
  .cfi_offset %r14, -32
Ltmp181:
  .cfi_offset %r15, -24
  movq  %rdi, %r12
  leaq  __ZN12_GLOBAL__N_117handrolled_remoteL6vtableINS0_3any7model_tIiEEEE(%rip), %rax
  movq  %rax, -48(%rbp)
  movl  $4, %edi
  callq __Znwm
  movl  $0, (%rax)
  movq  %rax, -40(%rbp)
  movq  16(%r12), %rax
  movl  (%rax), %r14d
  testl %r14d, %r14d
  je  LBB25_1
## BB#6:
  leaq  -48(%rbp), %r15
  jmp LBB25_7
  .align  4, 0x90
LBB25_10:                               ## %while.body
                                        ##   in Loop: Header=BB25_7 Depth=1
  movq  %r15, -56(%rbp)
  ## InlineAsm Start
  ## InlineAsm End
  movl  %r14d, %ebx
  .align  4, 0x90
LBB25_11:                               ## %for.body
                                        ##   Parent Loop BB25_7 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
  movq  -48(%rbp), %rax
  movq  -40(%rbp), %rdi
  callq *(%rax)
  movq  -48(%rbp), %rax
  movq  -40(%rbp), %rdi
  callq *8(%rax)
  movq  -48(%rbp), %rax
  movq  -40(%rbp), %rdi
  callq *16(%rax)
  movq  -48(%rbp), %rax
  movq  -40(%rbp), %rdi
  callq *24(%rax)
  movq  -48(%rbp), %rax
  movq  -40(%rbp), %rdi
  callq *32(%rax)
  decl  %ebx
  jne LBB25_11
  jmp LBB25_7
LBB25_8:                                ## %if.then.i
                                        ##   in Loop: Header=BB25_7 Depth=1
  movq  %r12, %rdi
  callq __ZN9benchmark5State16StartKeepRunningEv
  jmp LBB25_9
  .align  4, 0x90
LBB25_7:                                ## %while.cond
                                        ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB25_11 Depth 2
  movzbl  (%r12), %eax
  cmpl  $1, %eax
  jne LBB25_8
LBB25_9:                                ## %if.end.i
                                        ##   in Loop: Header=BB25_7 Depth=1
  movq  8(%r12), %rax
  leaq  1(%rax), %rcx
  movq  %rcx, 8(%r12)
  cmpq  96(%r12), %rax
  jb  LBB25_10
  jmp LBB25_12
LBB25_1:
  leaq  -48(%rbp), %rbx
  jmp LBB25_2
  .align  4, 0x90
LBB25_5:                                ## %while.body.us
                                        ##   in Loop: Header=BB25_2 Depth=1
  movq  %rbx, -64(%rbp)
  ## InlineAsm Start
  ## InlineAsm End
LBB25_2:                                ## %while.cond.us
                                        ## =>This Inner Loop Header: Depth=1
  movzbl  (%r12), %eax
  cmpl  $1, %eax
  jne LBB25_3
LBB25_4:                                ## %if.end.i.us
                                        ##   in Loop: Header=BB25_2 Depth=1
  movq  8(%r12), %rax
  leaq  1(%rax), %rcx
  movq  %rcx, 8(%r12)
  cmpq  96(%r12), %rax
  jb  LBB25_5
  jmp LBB25_12
LBB25_3:                                ## %if.then.i.us
                                        ##   in Loop: Header=BB25_2 Depth=1
  movq  %r12, %rdi
  callq __ZN9benchmark5State16StartKeepRunningEv
  jmp LBB25_4
LBB25_12:                               ## %while.end
  movq  %r12, %rdi
  callq __ZN9benchmark5State17FinishKeepRunningEv
  addq  $32, %rsp
  popq  %rbx
  popq  %r12
  popq  %r14
  popq  %r15
  popq  %rbp
  retq
  .cfi_endproc