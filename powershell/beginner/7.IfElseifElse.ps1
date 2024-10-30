1 -eq 2
1 -lt 2

'test' -eq 'TEST'
'test' -ceq 'TEST'

$path='C:\Users\Daniel\Desktop\scripts\2.test.ps1'

if (Test-Path -Path $path) {
    Write-Output "File `"$path`" exists"
    Get-Content $path
}

$rand=Get-Random -Minimum -100 -Maximum 100

if ($rand % 2 -eq 0) {
    Write-Output "$rand is even"
} elseif ($rand % 3 -eq 0) {
    Write-Output "$rand is odd and divisible by 3"
} elseif ($rand % 5 -eq 0) {
    Write-Output "$rand is odd and divisible by 5"
} else {
    Write-Output "$rand is odd"
}

# Roll fair dice
1..1200 | ForEach-Object {
    1..6 | Get-Random
} | Group-Object | Select-Object Name, Count | Sort-Object Count -Descending