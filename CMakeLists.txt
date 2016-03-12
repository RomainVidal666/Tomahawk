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
