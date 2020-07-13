#pragma once

typedef enum syscall_type
{
  SYSCALL_EXIT = 1,
  SYSCALL_WRITE = 4,
  SYSCALL_MODIFY_LDT = 123,
  SYSCALL_SET_THREAD_AREA = 243,
  SYSCALL_EXIT_GROUP = 252,
  SYSCALL_SET_TID_ADDRESS = 258
} syscall_type;

void syscall_init();