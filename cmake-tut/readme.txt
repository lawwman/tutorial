resources (in the order you should read):
https://preshing.com/20170511/how-to-build-a-cmake-based-project/
https://preshing.com/20170522/learn-cmakes-scripting-language-in-15-minutes/

https://cmake.org/cmake-tutorial/   # not very beginner friendly. Many missing steps not explicitly stated.
https://medium.com/@onur.dundar1/cmake-tutorial-585dd180109b


Youtube vids (in the order you should watch):
C++ Tutorial for Beginners  - https://www.youtube.com/watch?v=vLnPwxZdW4Y
C++ Header Files            - https://www.youtube.com/watch?v=9RJTQmK0YPI
Writing Classes in Separate
Files using #define in C++  - https://www.youtube.com/watch?v=pywM36qKHvg
How to CMake Good           - https://www.youtube.com/watch?v=_yFPO1ofyF0&list=PLK6MXr8gasrGmIiSuVQXpfFuE1uPT615s
Introduction to Neural
Networks - The Nature of
Code                        - https://www.youtube.com/watch?v=XJ7HLz9VYz0&list=PLRqwX-V7Uu6Y7MdSCaIfsxc561QI0U0Tb&index=1


How to cmake build and generate through command line:
Make sure you are in the source dir and then run the following code:
> mkdir build
> cd build
> cmake -G "MinGW Makefiles" ..
> mingw32-make

The executable will be built.

How to compile and run C++ with mingw:  # http://www.mingw.org/wiki/mingw_for_first_time_users_howto
> g++ hello_world.cpp -o helloworld.exe   

If compiling with multiples files (note that you should have a util.hpp for helloworld.cpp to find util.cpp functions)
> g++ hello_world.cpp Perceptron.cpp -o hw.exe   


useful links:
https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html
https://coursework.vschool.io/create-a-gitignore/