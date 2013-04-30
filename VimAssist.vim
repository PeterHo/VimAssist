if !has('python')
    echo "Error: Required vim compiled with +python"
    finish
endif

" 更新Tags和Cscope
function! Update()
	let s:tags_dir = '.'.'/.vimprj/'
	if finddir(s:tags_dir) == ''    " 文件夹不存在 
		exec "!mkdir .vimprj" 
	endif

	" 生成tags文件
	exec "cd .vimprj"
	exec "!ctags --c-kinds=+p --c++-kinds=+p --fields=+iaS --extra=+q --languages=c,c++,javascript,java,python,lua,vim,matlab,make,sh,c, --langmap=c:+.C,c++:+.H,c++:+.inl,c++:+.ipp,javascript:+.as,python:+.pyw,lua:+.wlua,c:+.hlsl,c:+.vsh,c:+.psh,c:+.fx,c:+.fxh,c:+.cg,c:+.shd,c:+.glsl, -o./tags -R .."
	exec "cd .."

	" 生成cscope文件
	exec "!find . -type f -name \"*.c\" -o -name \"*.h\" -o -name \"*.S\" -o -name \"*.sh\" -o -name \"*.py\" > ./.vimprj/cscope.file"
	exec "!cscope -bq -f ./.vimprj/cscope.out -i ./.vimprj/cscope.file"
	exec "cs add ./.vimprj/cscope.out"

endfunction


"编译,调试,运行程序
function! SaveAndMake()
    "先关闭QuickFix窗口
    exec "ccl"
    "保存文档
    exec "w"

	" 如果是python,就直接运行
	if &filetype=="python"
		exec "!python ".expand("%:p")
		return
	endif

	" 如果是shell文件,也直接运行
	if &filetype=="sh"
		exec "!bash ".expand("%:p")
		return
	endif

    "没有Makefile就设置编译参数
    if !filereadable("Makefile")
        if &filetype=="c"
            set makeprg=gcc\ -o\ %<\ %
        elseif &filetype=="cpp"
            set makeprg=g++\ -o\ %<\ %
		endif
    endif

    "编译
    exec "make"
    "如果有错误,就打开QuickFix窗口
    exec "cw"
endfunction

function! RunExe()
    if filereadable("driver") && filereadable("Problem.html") && filereadable("testcases.txt")
        exec "!./driver"
    else
        let s:exename = strpart(getcwd(), strridx(getcwd(), "/")+1, strlen(getcwd()))
        exec "!./".s:exename."_out"
    endif
endfunction

function! DbgExe()
    if filereadable("driver") && filereadable("Problem.html") && filereadable("testcases.txt")
        exec "!nemiver ./driver"
    else
        let s:exename = strpart(getcwd(), strridx(getcwd(), "/")+1, strlen(getcwd()))
        exec "!nemiver ./".s:exename."_out"
    endif
endfunction


" 快速创建代码文件
function! CreateCAndH(filename)
    let s:cFileName = a:filename . ".c"
    let s:hFileName = a:filename . ".h"

    if !filereadable(s:cFileName)
        let s:FileText = "#include \"" . s:hFileName . "\""
        let s:TextList = [s:FileText, "", ""]
        call writefile(s:TextList, s:cFileName)
    endif

    if !filereadable(s:hFileName)
        let s:hFileMacro = strpart(getcwd(), strridx(getcwd(), "/")+1, strlen(getcwd()))
        let s:hFileMacro = toupper(s:hFileMacro . "_" . a:filename)
        let s:FileText = "#ifndef " . s:hFileMacro
        let s:FileText2 = "#define " . s:hFileMacro
        let s:FileText3 = "#endif"

        let s:TextList = [s:FileText, s:FileText2, "", "", s:FileText3]
        call writefile(s:TextList, s:hFileName)
    endif

    execute "e " . s:cFileName
    execute "e " . s:hFileName
endfunction


" 工程向导
function! s:CreateProject()
    execute("!python " . $HOME . "/.vim/plugin/VimAssist/ProjectWizard.pyw")
    if v:shell_error == 1
        source $HOME/.vim/plugin/VimAssist/prj.vim_
    endif
endfunction

command! -nargs=* MAKE call SaveAndMake(<f-args>)
command! -nargs=* M call SaveAndMake(<f-args>)
command! -nargs=* MI exec "make install"
command! -nargs=* CM exec "!cmake ."
command! -nargs=* EM exec "e ./CMakeLists.txt"
command! -nargs=* R call RunExe(<f-args>)
command! -nargs=* D call DbgExe(<f-args>)

command! -nargs=* CCH call CreateCAndH(<f-args>)
command! -nargs=* CH call CreateCAndH(expand("%:t:r"))

command! -nargs=0 CP call s:CreateProject()

