# Main project directory
$mainProjectDir = Get-Location

# Function to run build_runner commands
function Invoke-BuildRunner {
    param (
        [string]$dir,
        [string]$name
    )
    Write-Host "Processing $name at $dir" -ForegroundColor Cyan
    Set-Location $dir

    Write-Host "Running 'flutter pub get' for $name" -ForegroundColor Green
    flutter pub get

    Write-Host "Running 'dart run build_runner clean' for $name" -ForegroundColor Green
    dart run build_runner clean

    Write-Host "Running 'dart run build_runner build --delete-conflicting-outputs' for $name" -ForegroundColor Green
    dart run build_runner build --delete-conflicting-outputs
}

# Extract submodule paths from .gitmodules
# Use a more specific regex '\.path$' to ensure we only get keys ending in .path
$submodulePaths = git config --file .gitmodules --name-only --get-regexp '\.path$' | ForEach-Object {
    git config --file .gitmodules --get $_
} | Where-Object { $_ -notmatch "http" }
# Run build_runner for each submodule
if ($submodulePaths) {
    foreach ($submoduleDirName in $submodulePaths) {
        $submodulePath = Join-Path -Path $mainProjectDir -ChildPath $submoduleDirName
        if (Test-Path $submodulePath) {
            Invoke-BuildRunner $submodulePath "submodule $submoduleDirName"
        }
        else {
            Write-Host "Submodule path $submodulePath not found, skipping." -ForegroundColor Yellow
        }
    }
}

# Clean and then run build_runner for the main project
Set-Location $mainProjectDir
Write-Host "Running 'flutter clean' for the main project before build" -ForegroundColor Yellow
flutter clean
# Run build_runner for the main project
Invoke-BuildRunner $mainProjectDir "main project"
