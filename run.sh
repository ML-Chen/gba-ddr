#!/usr/bin/env bash
#
# Imagine having to run an emulator that composites once for X11 then gets 
# sent over VNC to finally by composited again by the user's host machine. Lunacy!
# 
# This script has been written for macOS but should run just as well on most Linux distros.
# 
# -gwgg
set -e

if ! which mednafen >/dev/null 2>&1
then
    cat - <<\EOF
It doesn't look like you have mednafen installed.
On mac, if you have brew:
$ brew install mednafen
On Ubuntu/Debian:
$ sudo apt-get install mednafen

On other platforms check your distro's package manager.
EOF
exit 1
fi


# Run builds in a build directory so everything stays nice and clean
if [ ! -d build ]; then
    mkdir build
else
    rm -rf build/*
fi

# The Makefile changes the user's $HOME/.mednafen config files.
# Since we're not running in a VM, lets not do that.
if [ ! -d .mednafen ]; then
    mkdir .mednafen
fi

if [ ! -f .mednafen/mednafen-09x.cfg ]; then
    echo "symlinking config file"
    ln -s ../mednafen-09x.cfg .mednafen/mednafen-09x.cfg
fi

export MEDNAFEN_HOME=$(pwd)/.mednafen

find . -mindepth 1 -maxdepth 1 ! -name build -exec cp -r {} build \;

docker_bootstrap() {
    docker run --rm -v "$(pwd)":/cs2110/host/ -it -w="/cs2110/host" --entrypoint "/bin/bash" -u="root:root" dbecker1/cs2110docker -c "$*"
}

# Now the good stuff...

cd build
docker_bootstrap make "$@"
cd ..

prog_name=$(find build -name '*.gba' | head -n 1)

if [ ! -z "$prog_name" ]; then
    exec mednafen "$prog_name"
else
    echo "Didn't find a .gba file to run"
fi

