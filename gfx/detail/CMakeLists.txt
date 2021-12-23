cmake_minimum_required(VERSION 3.10)

project("renderer_detail")

set( DETAIL_HEADERS
	"include/Array.hpp"
)

set( DETAIL_SOURCES
	"Array.cpp"
)

add_library("renderer_detail" STATIC ${DETAIL_SOURCES} ${DETAIL_HEADERS})