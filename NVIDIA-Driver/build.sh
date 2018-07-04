#!/bin/sh
echo "sudo service lightdm stop "
sudo service lightdm stop 

echo "sudo nvidia-installer"
sudo nvidia-installer

echo "sudo reboot"
sudo reboot
