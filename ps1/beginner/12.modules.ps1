$ErrorActionPreference='Stop'

$($env:PSModulePath).Split(";")
Get-Module -ListAvailable

Import-Module -Name ScheduledTasks

#Get-Command -Module ScheduledTasks

Get-ScheduledTask

Find-Module -Name AzureAD

try {
    Install-Module -Name AzureAD
    Import-Module AzureAD
    Remove-Module -Name AzureAD
    Uninstall-Module -Name AzureAD
}
catch {
    Write-Output $_.Exception.Message
}