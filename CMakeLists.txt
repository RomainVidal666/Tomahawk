project(Tomahawk)

file (
	GLOB_RECURSE
	src_files
	src/*
)

add_executable (
	tomahawk
	${src_files}
)

target_link_libraries(
        tomahawk
        /home/romain/Documents/Esisar/Tomahawk/lib/librequest.so
)
