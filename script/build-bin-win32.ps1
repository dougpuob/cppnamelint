$ROOT_DIR   = ".."
$BUILD_DIR  = "..\build\windows"
$SOURCE_DIR = "..\source"
if ($null -eq $BUILD_TYPE) {
    $BUILD_TYPE = "RELEASE"
}


#==----------------------------------------------------------------------------
# Check environment
#==----------------------------------------------------------------------------
Write-Output ""
Write-Output "=============================================================="
Write-Output " Checking environment"
Write-Output "=============================================================="
Write-Output (-join("ROOT_DIR   = ", $ROOT_DIR))
Write-Output (-join("BUILD_DIR  = ", $BUILD_DIR))
Write-Output (-join("SOURCE_DIR = ", $SOURCE_DIR))
Write-Output (-join("BUILD_TYPE = ", $BUILD_TYPE))
& python --version
if (0 -ne $LastExitCode) {
    Write-Output 'ERR : python runtime not found!!!'
    Exit $LastExitCode
}

& python cppnamelint.py chkenv
if (0 -ne $LastExitCode) {
    Write-Output 'ERR : python runtime not found!!!'
    Exit $LastExitCode
}


#==----------------------------------------------------------------------------
# Fetch submodule projects
#==----------------------------------------------------------------------------
Write-Output ""
Write-Output "=============================================================="
Write-Output " Git fetch submodule projects."
Write-Output "=============================================================="
Push-Location ..
& git submodule init
& git submodule update
Pop-Location


#==----------------------------------------------------------------------------
# Reformat source code by Clang-Format utility.
#==----------------------------------------------------------------------------
Write-Output ""
Write-Output "=============================================================="
Write-Output " Reformating source code by Clang-Format utility."
Write-Output "=============================================================="
& python cppnamelint.py format  $ROOT_DIR $SOURCE_DIR
if (0 -ne $LastExitCode) {
    Write-Output 'ERR : Failed to use `cppnamelint.py format` command'
    Exit $LastExitCode
}


#==----------------------------------------------------------------------------
# Create MSVC project solution files via CMake.
#==----------------------------------------------------------------------------
Write-Output ""
Write-Output "=============================================================="
Write-Output " Generate makefile via CMake"
Write-Output "=============================================================="
if (-Not (Test-Path $BUILD_DIR)) {
    New-Item -ItemType "directory" -Path $BUILD_DIR
}
& python cppnamelint.py bldgcfg $ROOT_DIR $BUILD_DIR $BUILD_TYPE
if (0 -ne $LastExitCode) {
    Write-Output 'ERR : Failed to use `cppnamelint.py bldgcfg` command'
    Exit $LastExitCode
}

#==----------------------------------------------------------------------------
# Successful
#==----------------------------------------------------------------------------
Write-Output ''
Write-Output 'INFO: Succss to execute this PS1 script.'
Write-Output ''
if ($null -eq $AGENT_VERSION) {
    CMD /c PAUSE
}
$LastExitCode=0
Exit $LastExitCode