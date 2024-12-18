# Function to find include paths in a file
function Find-IncludePaths {
    param(
        [string]$FilePath
    )
    try {
        $content = Get-Content $FilePath -Raw
        $matches = [regex]::Matches($content, '#include <(.*?\.h)>')

        $includePaths = @()
        foreach ($match in $matches) {
            $includePath = $match.Groups[1].Value
            $includePaths += $includePath
        }
        return $includePaths

    } catch {
        Write-Error "Error reading or processing file: $_"
        return
    }
}

# Main script
Get-ChildItem -File -Recurse | ForEach-Object {
    Write-Host "Processing file: $($_.FullName)"
    $hFiles = Find-IncludePaths $_.FullName

    foreach ($hFile in $hFiles) {
        $parentFolder = Split-Path -Parent $hFile
        if (-not (Test-Path $parentFolder)) { New-Item -Path $parentFolder -ItemType Directory }
        Copy-Item -Path "~/Documents/bitcoin-source-code/src/$hFile" -Destination "$hFile" -Force -Recurse
        $cppFile = $hFile -replace (".h",".cpp")
        Copy-Item -Path "~/Documents/bitcoin-source-code/src/$cppFile" -Destination "$cppFile" -Force -Recurse

    }
    Write-Host "--------------------"
}
