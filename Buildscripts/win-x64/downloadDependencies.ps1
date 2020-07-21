param
(
    [string]$vcpkgDir=""
)

echo "Download Akurator dependencies for Visual Studio ..."
echo "vcpkgDir:    $vcpkgDir"

$startTime = (Get-Date).TimeOfDay
$currentDir = Split-Path $MyInvocation.MyCommand.Path

cd ..\..\
$rootDir = (pwd).path
if ($vcpkgDir.Length -eq 0)
{
    $vcpkgDir = $rootDir + "\Vendor\vcpkg"
    echo "Default vcpkgDir: $vcpkgDir"
}
$vcpkgRoot = Split-Path -Parent $vcpkgDir

echo "vcpkgRoot: $vcpkgRoot"

cd $currentDir

# Find VCPKG from path if it already exists
$systemVCPKG = $(Get-Command vcpkg -ErrorAction SilentlyContinue).Source

# Test if VCPKG is already installed on system
# Download locally to specified/default vcpkg folder if not
if ($systemVCPKG)
{
    echo "vcpkg already installed on system, updating"
    $vcpkgDir = Split-Path -Parent $systemVCPKG
    [Environment]::SetEnvironmentVariable("VCPKGDir", $vcpkgDir,
        [EnvironmentVariableTarget]::User)
    cd $vcpkgDir
    # Update and rebuild vcpkg
    git pull
    bootstrap-vcpkg.bat
    # Remove any outdated packages (they will be installed again below)
    vcpkg remove --outdated --recurse
    vcpkg update # Not really functional it seems yet
}
elseif (Test-Path $vcpkgDir)
{
    cd $vcpkgDir
    $env:Path += ";" + $(Get-Location)
    $vcpkgDir = $(Get-Location)
    [Environment]::SetEnvironmentVariable("VCPKGDir", $vcpkgDir,
        [EnvironmentVariableTarget]::User)
    echo "vcpkg already installed locally, updating"
    # Update and rebuild vcpkg
    git pull
    bootstrap-vcpkg.bat
    # Remove any outdated packages (they will be installed again below)
    vcpkg remove --outdated --recurse
    vcpkg update
}
else
{
    cd $vcpkgRoot
    echo "vcpkg missing, downloading and installing..."
    git clone --depth 1 http://github.com/Microsoft/vcpkg.git
    cd vcpkg
    $env:Path += ";" + $(Get-Location)
    $vcpkgDir = $(Get-Location)
    [Environment]::SetEnvironmentVariable("VCPKGDir", $vcpkgDir,
        [EnvironmentVariableTarget]::User)
    powershell -exec bypass scripts\bootstrap.ps1
    vcpkg integrate install
}

cd $rootDir

# Generate VCPKG AlwaysAllowDownloads file if needed
New-Item -type file $vcpkgDir\downloads\AlwaysAllowDownloads -errorAction SilentlyContinue | Out-Null

# Download all vcpkg packages available
echo "Downloading VC packages..."

# Target can be arm-uwp, x64-uwp, x64-windows-static, x64-windows, x86-uwp, x86-windows-static, x86-windows
$targetTriplet = "x64-windows-static"
vcpkg --triplet $targetTriplet install boost-serialization boost-log
$vcpkgTiming = (Get-Date).TimeOfDay

# Comment for testing to avoid extracting if already done so
rm -Path deps -Force -Recurse -ErrorAction SilentlyContinue

$endTime = (Get-Date).TimeOfDay
$duration = $endTime - $startTime

echo " "
echo "Total duration: $($duration.TotalMinutes) minutes"
