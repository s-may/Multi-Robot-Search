Multi-Robot-Search
==================

Software useful for coordinated search with large teams of robots 


==================
Installation for Mac:

1) install xcode and macports and run
xcode-select --install 
sudo port install qt4-mac cgal +qt4 +universal libgeotiff opencv boost libgeotiff yaml-cpp

2) install libQGLViewer and make sure you have a FindQGLViewer.cmake

3) go into build directory and run
cmake ../modules
make

4) go into the bin directoy and run
./gui_exe -f ../maps/freiburg.tiff






