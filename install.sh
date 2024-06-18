 #!/bin/bash
 
 mkdir -p build
 cd build
 cmake ..
 make
 
 sudo cp brainfuck /usr/local/bin/
 
 cd ..
 rm -rf build
