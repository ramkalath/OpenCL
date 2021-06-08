# this is very specific for the PC I have. Might not work for other makes
# i think the nvidia drivers should have been installed before that
sudo apt update
sudo apt install nvidia-opencl-dev # this is for nvidia

sudo apt-get install beignet-opencl-icd ocl-icd-libopencl1 clinfo # this is for intel

clinfo # gives a comprehensive report on the cl devices that are enabled on the computer
