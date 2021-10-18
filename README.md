# burritos
An i386 OS.

## Build Requirements
- make
- gcc
- xorriso
- grub-mkrescue
- qemu (to run)

## Features
### Working
- VGA output
- Interrupts
- Charwise serial i/o
- Task switching
- Usermode

## TODO
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
