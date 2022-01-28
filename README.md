# burritos

An i386 kernel.
Built for self educational purposes
(to compensate for the disappointing operating system course at OTH).

## Build Requirements
- make
- gcc
- xorriso
- grub-mkrescue
- qemu (for running)

## Features
- [x] VGA output
- [x] Interrupts
- [x] Charwise serial i/o
- [x] Task switching
- [x] Usermode
- [ ] Paging

## TODO
- Programs as mutliboot modules
- Higher half kernel (for vm86 mode)
- Register irqs in modules
- Implement assert
- Implement kmalloc
- Implement memory allocation syscall
- Implement userspace heap
- Basic shell: read input, react to input
- Better kprintf implementation
- Test: successful boot, userspace has no privileges, memory virtualization
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
