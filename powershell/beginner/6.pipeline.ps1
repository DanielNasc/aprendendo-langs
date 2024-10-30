Get-Service 
    | ForEach-Object{Write-Output "Service $($_.displayname) is currently $($_.status)"}