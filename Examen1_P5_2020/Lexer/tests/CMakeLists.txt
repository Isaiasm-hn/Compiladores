cmake_minimum_required (VERSION 3.0)
project (test_lexer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FA2LEXER "fa2lexer")

# Run fa2lexer to generate the lexer
add_custom_command (
    OUTPUT expr_tokens.h expr_lexer.cpp
    COMMAND ${FA2LEXER} --src expr_lexer.cpp --hdr expr_tokens.h --tpl ${PROJECT_SOURCE_DIR}/../fa/expr_lexer.fa2l
    MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/../fa/expr_lexer.fa2l
    DEPENDS ${PROJECT_SOURCE_DIR}/../fa/start.jff
            ${PROJECT_SOURCE_DIR}/../fa/number.jff
            ${PROJECT_SOURCE_DIR}/../fa/identifier.jff
            ${PROJECT_SOURCE_DIR}/../fa/arith.jff
          
            
  )

set_source_files_properties(
    ${PROJECT_SOURCE_DIR}/../expr_lexer.cpp
    PROPERTIES OBJECT_DEPENDS lexer.cpp
)

include_directories(${CMAKE_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../)
  
add_executable(${PROJECT_NAME}  expr_lexer.cpp
                                test_lexer.cpp)

