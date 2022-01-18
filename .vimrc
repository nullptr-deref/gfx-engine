set makeprg=cmake\ --build\ build/
let &makeef=getcwd()."/temp"
" MSVC error format
let &errorformat = '%f(%l\,%c)\:%*\s%t%*\w%*\s%*\w:%*\s%m%*\s[%o]'
let &errorformat .= ',%f(%l)\:%*\s%t%*\w%*\s%*\w:%*\s%m%*\s[%o]'
let &tags .= getcwd().'/tags'
let g:run_command = 'build\Debug\app'
