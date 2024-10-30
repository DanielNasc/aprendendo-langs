$name=Read-Host "Write your name:"
Write-Output "Yout name is $name"
$age=[int]$(Read-Host "Write your age:")
Write-Output "Your age is $age"

if ($age -lt 0) {
    Write-Output "Bro WHAT?"
    exit 1
}

switch($age) {
    {$_ -lt 10} {
        Write-Output "You're a child"
        Break
    }
    {$_ -lt 20} {
        Write-Output "You're an adolescent"
        Break
    }
    Default {
        Write-Output "You're an adult"
    }
}

switch($age) {
    0 {
        Write-Output "You are a baby :O"
        Break
    }
    21 {
        Write-Output "Now you can drink"
        Break
    }
    62 {
        Write-Output "Now you can retire"
        Break
    }
    Default {
        Write-Output "Nice age"
    }
}
