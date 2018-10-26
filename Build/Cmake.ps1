$OSName = [Environment]::OSVersion.Platform
Start-Process -FilePath "cmake.exe" -ArgumentList ".." , ("-B"+$OSName)
