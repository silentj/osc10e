Filecopy
========

Problem
-------

> In Section 2.3, we described a program that copies the contents of one 
> file to a destination file. This program works by first prompting the 
> user for the name of the source and destination files. Write this 
> program using either the POSIX or Windows API. Be sure to include 
> all necessary error checking, including ensuring that the source 
> file exists.

Compiling
---------

    gcc filecopy.c -o filecopy 

Tracing system calls
--------------------

> Once you have correctly designed and tested the program [...] run the program 
> using a utility that traces system calls. 
> 
> Linux: `strace ./filecopy`
>
> macOS: `sudo dtruss ./filecopy`

Command (copying the binary itself):

    strace ./filecopy filecopy filecopy-copy

Output:

    execve("./filecopy", ["./filecopy", "filecopy", "filecopy-copy"], [/* 21 vars */]) = 0
    brk(NULL)                               = 0xd43000
    access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
    access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
    open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
    fstat(3, {st_mode=S_IFREG|0644, st_size=33290, ...}) = 0
    mmap(NULL, 33290, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7fe765845000
    close(3)                                = 0
    access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
    open("/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
    read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P\t\2\0\0\0\0\0"..., 832) = 832
    fstat(3, {st_mode=S_IFREG|0755, st_size=1868984, ...}) = 0
    mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fe765844000
    mmap(NULL, 3971488, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fe76525f000
    mprotect(0x7fe76541f000, 2097152, PROT_NONE) = 0
    mmap(0x7fe76561f000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1c0000) = 0x7fe76561f000
    mmap(0x7fe765625000, 14752, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7fe765625000
    close(3)                                = 0
    mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fe765843000
    mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fe765842000
    arch_prctl(ARCH_SET_FS, 0x7fe765843700) = 0
    mprotect(0x7fe76561f000, 16384, PROT_READ) = 0
    mprotect(0x600000, 4096, PROT_READ)     = 0
    mprotect(0x7fe76584e000, 4096, PROT_READ) = 0
    munmap(0x7fe765845000, 33290)           = 0
    fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 0), ...}) = 0
    brk(NULL)                               = 0xd43000
    brk(0xd64000)                           = 0xd64000
    write(1, "source file name: filecopy\n", 27source file name: filecopy
    ) = 27
    write(1, "destination file name: filecopy-"..., 37destination file name: filecopy-copy
    ) = 37
    open("filecopy", O_RDONLY)              = 3
    open("filecopy-copy", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 4
    fstat(3, {st_mode=S_IFREG|0755, st_size=9168, ...}) = 0
    mmap(NULL, 1052672, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fe765741000
    read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\2\0>\0\1\0\0\0@\7@\0\0\0\0\0"..., 1048576) = 9168
    fstat(4, {st_mode=S_IFREG|0644, st_size=0, ...}) = 0
    mmap(NULL, 1052672, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fe76515e000
    read(3, "", 1048576)                    = 0
    read(3, "", 1048576)                    = 0
    close(3)                                = 0
    munmap(0x7fe765741000, 1052672)         = 0
    write(4, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\2\0>\0\1\0\0\0@\7@\0\0\0\0\0"..., 9168) = 9168
    close(4)                                = 0
    munmap(0x7fe76515e000, 1052672)         = 0
    write(1, "Copied 9168 bytes from filecopy "..., 49Copied 9168 bytes from filecopy to filecopy-copy
    ) = 49
    exit_group(0)                           = ?
    +++ exited with 0 +++

