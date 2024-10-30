$ErrorActionPreference='Stop'

$path="C:\KOJAPDJASDPIDHASOUBODASN"

try {
    $files=Get-ChildItem -Path $path
    $files.foreach({
        Write-Output $_.Name
    })
} catch {
    Write-Output $_.Exception.Message
} finally {
    Write-Output "I'll run always"
}