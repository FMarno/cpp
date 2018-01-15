import clang.cindex
from clang.cindex import Cursor, CursorKind, TranslationUnit

def find_child(parent, kind, spelling): #-> Optional[Cursor]
    for node in parent.get_children():
        if kind == node.kind and spelling == node.spelling:
            return node

def get_main(translation_unit): #-> Cursor
    return find_child(translation_unit.cursor, CursorKind.FUNCTION_DECL, 'main')

def dump(cursor):
    for t in cursor.get_tokens():
        print(t.spelling)

def get_translation_unit(compilation_database_dir, cpp_path): # -> TranslationUnit
    compilation_database = clang.cindex.CompilationDatabase.fromDirectory(compilation_database_dir)
    compilation_commands = compilation_database.getCompileCommands(cpp_path)
    compilation_arguments = get_full_args(compilation_commands)
    index = clang.cindex.Index.create()
    translation_unit = index.parse(input_file.name, compilation_arguments)
    for error in translation_unit.diagostics:
        print (error)
    return translation_unit


dump(get_main(get_translation_unit('_build', 'five.cpp' )))
