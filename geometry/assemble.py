# script to assemble all .hpp files into a single .hpp header file
# output: geomtry.hpp

import os

def assemble(files, output, extention):
    output_file = open(f"{output}.{extention}", "w")
    if extention == "cpp":
        output_file.write("#include \"geometry.hpp\"\n")
    if extention == "hpp":
        output_file.write("#pragma once\n")
    output_file.write("#include <cstdint>\n")

    for file in files:
        with open(f"{file}.{extention}" , 'r') as f:
            # remove the #pragma once
            # and #include lines
            lines = [line for line in f.readlines() if not line.startswith('#pragma') and not line.startswith('#include')]
            for line in lines:
                output_file.write(line);

hpp_files = [
    "vector",
    "shape",
    "point",
    "segment",
    "line",
    "ray",
    "circle"
]

cpp_files = [
    "point",
    "segment",
    "line",
    "ray",
    "circle"
]

assemble(hpp_files, "geometry", "hpp")
assemble(cpp_files, "geometry", "cpp")