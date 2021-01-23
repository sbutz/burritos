# os

## Build Requirements
- make
- gcc
- genisoimage
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
- Build Disk Image
- Test on Real Hardware
- Test: Syscall while interrupt? Prevent Timer Interrupt with Syscall?

## Debugging
Qemu Monitor:
```
telnet localhost 55555
```
