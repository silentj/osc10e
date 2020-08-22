# One-time setup

- Downloaded [the VM](http://cs.westminstercollege.edu/~greg/osc10e/vm/index.html) and loaded into Virtualbox
- Installed the Virtualbox guest additions
- Forked [the book's repo](https://github.com/greggagne/osc10e) here
- Cloned the repo onto my machine
- Added a shared folder in Virtualbox for this repo:
    - Folder name: `operating-system-concepts`
    - Read/write
    - Permanent
    - NOT automount
- Set the shared folder to automount in the VM by editing `/etc/rc.local` and adding the line `mount -t vboxsf -o rw,uid=1000,gid=1000 operating-system-concepts /home/osc/operating-system-concepts`
- Copy the build directory to the shared home directory `rsync -rL /lib/modules/4.4.0-87-generic/build/ /home/osc/operating-system-concepts/vm-build-dir/`
- Ignore the `vm-build-dir`: `echo vm-build-dir >> .gitignore`
- Modify the vscode C/C++ settings to add the include directory (checked in the `.vscode` directory)

At that point, I should be able to edit things on the host and see those changes reflected in the VM


# Original README

This contains source code for the 10th edition of
"Operating System Concepts" by Silberschatz/Galvin/Gagne.
Published by John Wiley & Sons 2018

Source files are organized by chapter. 

To download all files, enter

    git clone https://github.com/greggagne/OSC10e.git

which will clone this repository on your local machine.

-- Greg Gagne June 2018.
