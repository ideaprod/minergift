PROJECT_OUTPUT = $$shell_path($$OUT_PWD/../output)

if (CONFIG(debug, debug|release)) {
    FOLDER = debug
} else {
    FOLDER = release
}
