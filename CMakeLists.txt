cmake_minimum_required(VERSION 3.20)

project(BooleanAlgebraFormulaGenerator LANGUAGES CXX)

add_executable(BAFormulaGenerator
    src/main.cpp
    src/validator.cpp
    src/tokenizer.cpp
    src/parser.cpp
)

target_compile_features(BAFormulaGenerator PRIVATE cxx_std_20)

set_target_properties(BAFormulaGenerator
    PROPERTIES
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)