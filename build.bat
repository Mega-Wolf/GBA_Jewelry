@REM @echo off

@REM mkdir compiled
@REM pushd compiled

@REM REM TODO: The user program will provide the build file

@REM REM call "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvarsall" x64

@REM set CompilerFlags= ^
@REM  -DCOMPILER_MSVC ^
@REM  -DENGINE_INTERNAL=1 ^
@REM  -DEDITING_RULES=1 ^
@REM  -MTd ^
@REM  -nologo ^
@REM  -W4 -wd4201 -wd4505 ^
@REM  -Oi -GR- -EHa- -Gm- ^
@REM  -FC -Zi 
 
@REM REM -O2 -DNDEBUG

@REM set LinkerFlags= -opt:ref user32.lib Gdi32.lib winmm.lib opengl32.lib

@REM REM TODO: I have to delete everyone except the win32 one
@REM del *.pdb > NUL 2> NUL
@REM echo WAITING FOR PDB > lock.tmp

@REM ctime -begin ../buildTimings/platform.ctm
@REM cl %CompilerFlags% ../engine/platform/win32_layer.cpp /link /PDB:./win32_platform.pdb %LinkerFlags%
@REM set LastError=%ERRORLEVEL%
@REM ctime -end ../buildTimings/platform.ctm %LastError%
@REM REM ctime -stats ../buildTimings/platform.ctm

@REM if NOT %LastError%==0 (
@REM       echo [34m
@REM       echo ########################### ERROR BACKEND ###########################
@REM       echo ########################### ERROR BACKEND ###########################
@REM       echo ########################### ERROR BACKEND ###########################
@REM       echo [0m
@REM       REM exit /b
@REM       REM I would have to check what the error actually is; linker errors are okay
@REM )
@REM REM cl %CompilerFlags% -EP -P ./game/game.cpp -DNO_HEADERS
@REM REM call "metaprogramming.exe"
@REM ctime -begin ../buildTimings/user.ctm
@REM cl %CompilerFlags% ../game/game.cpp -LD /link -incremental:no /PDB:game_%random%.pdb /EXPORT:MainUpdateAndRender /EXPORT:MainGetSoundSamples
@REM set LastError=%ERRORLEVEL%
@REM ctime -end ../buildTimings/user.ctm %LastError%
@REM REM ctime -stats ../buildTimings/user.ctm

@echo off

REM release build: -fomit-frame-pointer -O3 ^
REM Find out: -ffunction-sections -fdata-sections

set Arch= -mthumb -mthumb-interwork
set CFlags= -g -gdwarf-2 -Wall ^
			-mcpu=arm7tdmi -mtune=arm7tdmi ^
			-ffast-math ^
			--specs=nosys.specs ^
			-nostartfiles -Tbuilding/lnkscript ^
			%Arch% ^
			-FC ^
                  -Wno-write-strings -Wno-comment -Wno-unknown-pragmas -Wno-switch
			
arm-none-eabi-gcc building/crt0.s game.cpp %CFlags% -o building/a.out

REM arm-none-eabi-gcc -S -l -C -fverbose-asm crt0.s ../game.cpp %CFlags% -O0

set LastError=%ERRORLEVEL%

if NOT %LastError%==0 (
      echo [31m
      echo ########################### ERROR ###########################
      echo ########################### ERROR ###########################
      echo ########################### ERROR ###########################
      echo [0m
      @echo Completed: [31m%date% %time%[0m
) else (
      echo [32m
      echo ########################### SUCCESS ###########################
      echo ########################### SUCCESS ###########################
      echo ########################### SUCCESS ###########################
      echo [0m
)


arm-none-eabi-objcopy -O binary building/a.out building/a.gba

REM del a.out

