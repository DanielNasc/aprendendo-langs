$myVariable="Daniel"

$myVariable.GetType()

$value1=2
$value2=4
$value3=3

[double]$result1=$value2 / $value1
$result2=$value2 / $value3

$result1
$result2

$result1.GetType()
$result2.GetType()

($result1 -eq $result2)
($result1 -eq $result2).GetType()

$today=Get-Date
$today
$today.GetType()