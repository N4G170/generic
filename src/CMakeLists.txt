#list of cpp files

set(SOURCE_FILES "")
set(HEADER_FILES "")
set(INCLUDE_DIRECTORIES "")

set(SOURCE_FILES_TMP "")
set(HEADER_FILES_TMP "")
set(INCLUDE_DIRECTORIES_TMP "")

#list of subdiretories
set(FOLDERS a_star_map_demo rain snake base influence_wars solar particles other)

foreach(folder ${FOLDERS})
	add_subdirectory(${folder})

	#get VARIABLES from subdirectory
	get_directory_property(INCLUDE_DIRECTORIES DIRECTORY ${folder} DEFINITION INCLUDE_DIRECTORIES)#INCLUDE_DIRECTORIES
	get_directory_property(SOURCE_FILES DIRECTORY ${folder} DEFINITION SOURCE_FILES)#SOURCE_FILES
	get_directory_property(HEADER_FILES DIRECTORY ${folder} DEFINITION HEADER_FILES)#HEADER_FILES

	#APPEND TO MAIN VARIABLES
	list(APPEND INCLUDE_DIRECTORIES_TMP ${INCLUDE_DIRECTORIES})
	list(APPEND SOURCE_FILES_TMP ${SOURCE_FILES})
	list(APPEND HEADER_FILESTMP ${HEADER_FILES})
	#message("\n${folder} -> ${SOURCE_FILES_TMP}")

endforeach(folder)

#set variables to be read by parent
set(SOURCE_FILES ${SOURCE_FILES_TMP})
set(HEADER_FILES ${HEADER_FILES_TMP})
set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES_TMP})
