param
(
    [string]$vcpkgDir=""
)

echo "Generating akurator Visual Studio solution..."
echo "vcpkgDir:    $vcpkgDir"

$Env:VCPKG_ROOT = $vcpkgDir

cmake --preset visual-studio
