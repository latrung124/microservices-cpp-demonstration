@echo off
setlocal

:: Add Conan remote
conan remote add conancenter https://center.conan.io --force

:: Install dependencies with Conan
conan install . --output-folder=build --build=missing --remote=conancenter

:: Move to the build directory
cd build

:: Run Conan build script (ensure it exists)
if exist conanbuild.bat (
    call conanbuild.bat
) else (
    echo [WARNING] conanbuild.bat not found, skipping...
)

:: Configure CMake with Conan toolchain
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_TOOLCHAIN_FILE="conan_toolchain.cmake"

:: Print start build message
echo ======== Start build ========

:: Build the project in Release mode
cmake --build . --config Release

:: Print end build message
echo ======== End build ========

:: Return to the original directory
cd ..

endlocal