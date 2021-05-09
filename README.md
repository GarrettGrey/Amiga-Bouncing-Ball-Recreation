# Amiga-Bouncing-Ball-Recreation
This was my capstone project for my Computer Science major at the University of Indianapolis. I used C++ and OpenGL to attempt a recreation of the Amiga Bouncing ball demo. Written and compiled on Linux. Because this is a graphical program, this will not work on the Windows Subsystem for Linux.

# Setup
This process wil only work on Debian/Ubuntu based Linux distrobutions.

1. Update your repositories and packages
    
    sudo apt update && sudo apt upgrade -y
2. Install the necesary packages for OpenGL

    sudo apt install freeglut3-dev binutils g++ mesa-common-dev build-essential libglew-dev libglm-dev mesa-utils
3. Compile the script

    g++ bounce2.cpp -lGL -lGLU - glut
4. Run the program

    ./a.out
