# simple_pid_controller
a packaged simple pid controller in C++, providing python interfaces

## Getting started(only for local testing)
1. pull this repo and adapt conanfile requires accordingly!!
2. create and activate a python virtual environment that has `pybind` installed, you can use `requirements.txt` to create
```shell
mamba create -n simplePID --file requirements.txt
mamba activate simplePID
```
3. build this repo 
```shell
conan install . -if test_env -g virtualenv -g virtualrunenv -pr=release-gcc11 -s build_type=Debug
cmake -S . -B build < > ( depends on your conan output)
cmake --build build
```
4. have fun in jupyternotebook, launch it with 
```shell
./start.sh
```

