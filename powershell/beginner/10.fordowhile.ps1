for($i=0; $i -lt 10; $i++) {
    Write-Output $i
}

$names_arr=@("Jhon", "Tim", "Edward")
for($i=0; $i -lt $names_arr.Length; $i++) {
    $names_arr[$i] += " Doe"
}
$names_arr


while((Get-Date).Second -lt 58) {
    Write-Output (Get-Date)
}

Write-Output "PARROT APP"
Write-Output "Press 'q' to quit"
do {
    $input_app=Read-Host -Prompt "Please enter a phrase"
    Write-Output "You entered $input_app"
} while($input_app -ne 'q')

Write-Output "PARROT APP 2"
Write-Output "Press 'q' to quit"
do {
    $input_app=Read-Host -Prompt "Please enter a phrase"
    Write-Output "You entered $input_app $($input_app -eq "q" ? ":D": "D:")"
} until($input_app -eq 'q')