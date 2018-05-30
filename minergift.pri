PROJECT_OUTPUT = $$shell_path($$OUT_PWD/../output)

if (CONFIG(debug, debug|release)) {
    FOLDER = debug
} else {
    FOLDER = release
}

contains(QMAKE_HOST.os,.*Win.*){
	HOST_PLATFORM = WIN
	IS_WIN = 1
}

contains(QMAKE_HOST.os,.*Linux.*){
	HOST_PLATFORM = LINUX
	IS_LINUX = 1
}
