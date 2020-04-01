#==----------------------------------------------------------------------------
# Remove previous generated files
#==----------------------------------------------------------------------------
Write-Output ""
Write-Output "=============================================================="
Write-Output " Remove previous generated files"
Write-Output "=============================================================="
if (Test-Path release) {
    Remove-Item -Path release/* -Force -Recurse
}


#==----------------------------------------------------------------------------
# Pack generated files to release folder.
#==----------------------------------------------------------------------------
Write-Output ""
Write-Output "=============================================================="
Write-Output " Pack generated files to release folder."
Write-Output "=============================================================="
& python cppnamelint.py bldgpack .. release
if (0 -ne $LastExitCode) {
    Write-Output (-join('ERR : Failed to use `cppnamelint.py bldgpack` command.' , " (LastExitCode=",$LastExitCode,")"))
    Exit $LastExitCode
}


#==----------------------------------------------------------------------------
# Successful
#==----------------------------------------------------------------------------
Write-Output ''
Write-Output 'INFO: Succss to execute this PS1 script.'
Write-Output ''
if (-Not $GITLAB_CI) {
    CMD /c PAUSE
}
$LastExitCode=0
Exit $LastExitCode