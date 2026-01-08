# Running the Windows Example

## Prerequisites
- Windows 10 or later
- Visual Studio 2022 with C++ desktop development workload
- Windows SDK 10.0.26100.0 or 10.0.19041.0

## Running the Example

**Important**: The Windows example must be run from the repository root directory, not from the `example/` folder.

### From the repository root:

```bash
# Navigate to repository root (if in example folder)
cd c:\work\datetimepicker

# Run the Windows example
yarn start:windows
```

This command will:
1. Restore NuGet packages
2. Run autolinking
3. Build the Windows app
4. Launch the app

### Alternative: Build without running

```bash
yarn start:windows --no-launch
```

## Troubleshooting

### Autolinking errors
If you encounter autolinking errors, ensure you're running the command from the repository root (`c:\work\datetimepicker`), not from the `example/` folder.

### Windows SDK version errors
The project is configured to use Windows SDK 10.0.26100.0. If you have a different version installed, the build system will use the closest available version automatically.
