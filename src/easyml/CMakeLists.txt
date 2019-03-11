find_package(OpenCV REQUIRED COMPONENTS core highgui imgproc)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Glog REQUIRED)
include_directories(${GLOG_INCLUDE_DIR})

file(GLOB_RECURSE LIB_SRCS *.cpp *.c)
add_library(EasyML ${LIB_SRCS})
target_link_libraries(EasyML ${OpenCV_LIBS} ${GLOG_LIBRARY})
install(TARGETS EasyML DESTINATION lib)
