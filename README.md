# burritos
An i386 kernel. Built for self educational purposes.

## Build Requirements
- make
- gcc
- xorriso
- grub-mkrescue
- qemu (for running)

## Features
### Working
- [x] VGA output
- [x] Interrupts
- [x] Charwise serial i/o
- [x] Task switching
- [x] Usermode
- [ ] Paging

## TODO
- add programs add multiboot modules, create task per module
- paging/virtual memory management
- higher half kernel
- Basic shell: read input, react to input
- Test: successful boot, userspace has no privileges, memory virtualization
- Better kprintf implementation
- Test: Boot-Test
- Test: Syscall while interrupt? Prevent Timer Interrupt with Syscall?
- Test: Memory access of user process (kernel mem, other task mem)
- Test: Mutliboot-Compliance (gnu mbchk)
- Test: Posix-Compliance

## Debugging
Qemu Monitor:
```
telnet localhost 55555
```
