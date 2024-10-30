$myArray=@("Element 1", "Element 2")
$myArray.GetType()
$myArray.IsFixedSize
$myArray.Count
$myArray.Length
$myArray[0]
$myArray -ne "Element 1"

$myList=New-Object -TypeName System.Collections.ArrayList
[void]$myList.Add("Teste1")
[void]$myList.Add("Teste2")
$myList.AddRange($myArray)
$mylist.Count
$myList
$myList.Remove("Teste2")
Write-Output "Removed Teste2"
$myList

$arr=@()
$arrList=New-Object -TypeName System.Collections.ArrayList

Write-Output "Adicionar 5001 elementos"
(Measure-Command -Expression {@(0..5000).ForEach({$arr+=$_})}).TotalMilliseconds
(Measure-Command -Expression {@(0..5000).ForEach({$arrList.Add($_)})}).TotalMilliseconds