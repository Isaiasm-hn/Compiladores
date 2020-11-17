cmake_minimum_required (VERSION 3.0)
project (test_parser)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../)

# Run ECC to generate the LL1 table
add_custom_command (
  OUTPUT expr_ll1_table.cpp expr_symbols.h
  COMMAND ecc -g ${PROJECT_SOURCE_DIR}/../expr_grammar_ll1.txt --src expr_ll1_table.cpp --hdr expr_symbols.h
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/../expr_grammar_ll1.txt
  )

set_source_files_properties(
    ${PROJECT_SOURCE_DIR}/../expr_parser.cpp 
    PROPERTIES OBJECT_DEPENDS expr_ll1_table.cpp
)
  
add_executable(${PROJECT_NAME} 
                    ${PROJECT_SOURCE_DIR}/../expr_parser.cpp
                    test_parser.cpp)
