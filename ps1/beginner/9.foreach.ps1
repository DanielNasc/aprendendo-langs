1..1200 | ForEach-Object {
    1..6 | Get-Random
} | Group-Object | Select-Object Name, Count | Sort-Object Count -Descending


$names_arr=@("Daniel", "Beatriz", "Davi")
foreach($name in $names_arr) {
    Write-Output $name
}
