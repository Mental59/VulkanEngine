conan install . --output-folder=build --profile=profiles/conanDebugProfile.txt --profile:b=profiles/conanDebugProfile.txt --build=missing
conan install . --output-folder=build --profile=profiles/conanReleaseProfile.txt --profile:b=profiles/conanReleaseProfile.txt --build=missing
