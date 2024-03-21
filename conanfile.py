import os
import re

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain
from conan.tools.files import load


class Conan(ConanFile):
    # name = See set_name method below
    # version = See set_version method below

    # Optional metadata
    description = "a simple PID controller for visualization."
    url = "git@git.ar.int:anran.zhang/simple_pid_controller.git"
    license = "None"
    
    # Package generation configuration
    exports_sources = "*"
    generators = "CMakeDeps"
    no_copy_source = True
    requires = [
        # robot dynamics libs, pinocchio for examples
    ]

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "with_tests": [True, False],
        "build_python_interface":[True,False],
    }
    default_options = {
        "with_tests": True,
        "build_python_interface": True,
    }

    def set_name(self):
        cmake_content = load(self, "CMakeLists.txt").lower()
        match = re.search('project\s*\(([^\)]+)\)', cmake_content)
        if match:
            name = re.search('(\S+)', match.group(1)).group(1)
        else:
            raise RuntimeError('No project found in CMakeLists.txt')
        self.name = name

    def set_version(self):
        cmake_content = load(self, "CMakeLists.txt").lower()
        match = re.search('project\s*\(([^\)]+)\)', cmake_content)
        if match:
            version = re.search('version[\s\n]+(\d+(\.\d+(\.\d+)?)?)', match.group(1)).group(1)
        else:
            raise Exception('No project version specified in in CMakeLists.txt')
        self.version = version

    def build_requirements(self):
        if self.options.with_tests:
            self.test_requires("gtest/1.12.1")
        
    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables['WITH_TESTS'] = self.options.with_tests
        tc.variables['BUILD_PYTHON_INTERFACE'] = self.options.build_python_interface
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["simple_pid_controller"]
        self.env_info.LD_LIBRARY_PATH.extend([os.path.join(self.package_folder, x) for x in self.cpp_info.libdirs])
        if self.options.build_python_interface:
            self.env_info.PYTHONPATH.extend([os.path.join(self.package_folder, x) for x in self.cpp_info.libdirs])

