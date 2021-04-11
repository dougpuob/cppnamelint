
class FindFile {

    [string[]] FindExecFiles([string]$RootDir) {
        $RootDir = [IO.Path]::GetFullPath($RootDir)
        $FileList = [System.Collections.ArrayList]@()
        if ($GLOBAL:IsWindows) {
            $FileList = (Get-ChildItem $RootDir -Recurse -Include *.exe)
        } else {
            $CmdRet = (find $RootDir -executable -type f)
            ForEach($Path in $CmdRet) {
                file $Path | grep ELF
                if ($?) {
                    $FileProp = (Get-ItemProperty $Path)
                    $FileList.Add($FileProp)
                }
            }
        }

        return ($FileList | Sort-Object -Descending CreationTime).FullName
    }


    [string] FindTheLatestExecFile([string]$RootDir) {
        [string[]]$FileList = $this.FindExecFiles($RootDir)
        return $FileList[0]
    }
}


#==============================================================================
#==============================================================================

# Git clone target C++ project.
if (-Not (Test-Path modern-cpp-tutorial.git)) {
    git clone https://github.com/changkun/modern-cpp-tutorial.git modern-cpp-tutorial.git
}

# Remove previous log file.
if (Test-Path "modern-cpp-tutorial.log") {
    Remove-Item "modern-cpp-tutorial.log" -Force
}

# Prepare
$FindFileObj = [FindFile]::new()
$AppLoc = $FindFileObj.FindTheLatestExecFile([IO.Path]::Combine($PSScriptRoot, '..'))
$CfgLoc = [IO.Path]::Combine($PSScriptRoot, '../cppnamelint.toml')
Write-Host ("PSScriptRoot = {0}" -f $PSScriptRoot)
Write-Host ("AppLoc       = {0}" -f $AppLoc)
Write-Host ("CfgLoc       = {0}" -f $CfgLoc)
Write-Host ("---------------------------------------------------------")
Write-Host ("Found files")
$FoundList = (Get-ChildItem -Recurse .\modern-cpp-tutorial.git -Include *.cpp).FullName
foreach($File in $FoundList) {
    Write-Host $File
}

# Run
Write-Host ("---------------------------------------------------------")
Write-Host ("Run test")
foreach($File in $FoundList) {
    . $AppLoc check $File --config=$CfgLoc --logfile="modern-cpp-tutorial.log" | Tee-Object -Append "modern-cpp-tutorial.txt"
}