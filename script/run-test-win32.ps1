#==----------------------------------------------------------------------------
# Run Python Unit Test cases
#==----------------------------------------------------------------------------
Write-Output ""
Write-Output "=============================================================="
Write-Output " Run Python Unit Test cases"
Write-Output "=============================================================="
$pushed=$false
if (Test-Path("test")) {
    $pushed=$true
    Push-Location test
}
$proc1 = Start-Process -Wait -PassThru -NoNewWindow python -ArgumentList testcppnamelintlib-exec.py  , -v
$proc2 = Start-Process -Wait -PassThru -NoNewWindow python -ArgumentList testcppnamelintlib-cmake.py , -v
$proc3 = Start-Process -Wait -PassThru -NoNewWindow python -ArgumentList testcppnamelintlib-file.py  , -v
if ($pushed) {
    Pop-Location
}
if (($proc1.ExitCode + $proc2.ExitCode + $proc3.ExitCode) -gt 0) {
    Write-Output ('       $proc1.ExitCode = '+$proc1.ExitCode.ToString())
    Write-Output ('       $proc2.ExitCode = '+$proc2.ExitCode.ToString())
    Write-Output ('       $proc3.ExitCode = '+$proc3.ExitCode.ToString())
    Write-Output ('ERROR: Failed to run python unit test cases!!!')
    Exit $LastExitCode
}


#==----------------------------------------------------------------------------
# Run Function Test cases (if cppnamelint.exe was FOUND)
#==----------------------------------------------------------------------------
if (Test-Path("cppnamelint.exe")) {
    Write-Output ""
    Write-Output "=============================================================="
    Write-Output " Run Function Test cases (if cppnamelint.exe was FOUND)"
    Write-Output "=============================================================="
    $pushed=$false
    if (Test-Path("test")) {
        $pushed=$true
        Push-Location test
    }
    $proc1 = Start-Process -Wait -PassThru -NoNewWindow python -ArgumentList testcppnamelint-main.py  , -v
    $proc2 = Start-Process -Wait -PassThru -NoNewWindow python -ArgumentList cppnamelint.py , bldgtest
    if ($pushed) {
        Pop-Location
    }
    $proc3 = Start-Process -Wait -PassThru -NoNewWindow ./cppnamelint.exe -ArgumentList test , --testlog=testlog.log

    if (($proc1.ExitCode + $proc2.ExitCode + $proc3.ExitCode) -gt 0) {
        Write-Output ('       $proc1.ExitCode = '+$proc1.ExitCode.ToString())
        Write-Output ('       $proc2.ExitCode = '+$proc2.ExitCode.ToString())
        Write-Output ('       $proc3.ExitCode = '+$proc3.ExitCode.ToString())
        Write-Output ('ERROR: Failed to run function test cases!!!')
        Exit $LastExitCode
    }
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