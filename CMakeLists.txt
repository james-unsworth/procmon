cmake_minimum_required(VERSION 3.16)

project(
  procmon
  VERSION 1.0
  LANGUAGES C)

add_executable( procmon
  src/main.c 
  src/sampler.c 
  src/parser.c
  src/snapshot.c
)

target_include_directories(procmon PRIVATE include)
