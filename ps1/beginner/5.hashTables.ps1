$myHashTable=@{
    key=100
    fruit="Apple"
    boolean=$true
    hash=@{
        id=100
        name="John Doe"
    }
}

$myHashTable.GetType()
$myHashTable.Keys.Count
$myHashTable['boolean']
$myHashTable.ContainsKey('blabla')
$myHashTable.ContainsValue(100)
$myHashTable.Clear()
$myHashTable


$myCustomObject=New-Object -TypeName PSCustomObject

Write-Output 'My Custom Object:'
Add-Member -InputObject $myCustomObject -MemberType NoteProperty -Name 'EmployeeID' -Value '1011'
Add-Member -InputObject $myCustomObject -MemberType NoteProperty -Name 'FirstName' -Value 'Jhon Doe'
Add-Member -InputObject $myCustomObject -MemberType NoteProperty -Name 'Title' -Value 'CEO'

Get-Member -InputObject $myCustomObject

$myCustomObject2=[PSCustomObject]@{
    EmployeeID = '1111'
    FirstName = 'Bob'
    Title = 'CTO'
}

$myCustomObject
$myCustomObject2