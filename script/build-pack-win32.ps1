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
$proj_dir="../"
$build_dir="../build/windows"
$output_dir="./release/windows"

& python cppnamelint.py bldgpack $proj_dir $build_dir $output_dir
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
if ($null -eq $AGENT_VERSION) {
    CMD /c PAUSE
}
$LastExitCode=0
Exit $LastExitCode