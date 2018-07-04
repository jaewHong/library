#!/bin/sh
echo "make -j8"
make -j8

echo "make modules -j8"
make modules -j8

echo "sudo make modules_install"
sudo make modules_install

echo "sudo make install"
sudo make install

