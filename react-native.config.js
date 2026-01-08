const project = (() => {
  const fs = require('fs');
  const path = require('path');
  
  // Don't define project config if running from example directory
  // to allow example's own config to take precedence  
  const examplePath = path.join(__dirname, 'example');
  const isRunningFromExample = process.cwd().startsWith(examplePath);
  if (isRunningFromExample) {
    return undefined;
  }

  try {
    // Don't use configureProjects for Windows as it creates invalid nested structure
    // Just return the config directly
    return {
      android: {
        sourceDir: path.join(__dirname, 'example', 'android'),
        manifestPath: path.join(__dirname, 'example', 'android', 'app', 'build', 'generated', 'rnta', 'src', 'main', 'AndroidManifest.xml'),
        packageName: 'com.microsoft.reacttestapp',
      },
      ios: {
        sourceDir: path.join(__dirname, 'example', 'ios'),
      },
      windows: {
        sourceDir: path.join('example', 'windows'),
        solutionFile: 'date-time-picker-example.sln',
        projectFile: path.join('DateTimePickerDemo', 'DateTimePickerDemo.vcxproj'),
      },
    };
  } catch (e) {
    return undefined;
  }
})();

module.exports = {
  dependency: {
    platforms: {
      windows: {
        sourceDir: 'windows',
        solutionFile: 'DateTimePickerWindows.sln',
      },
    },
  },
  dependencies: {
    ...(project
      ? {
        // Help rn-cli find and autolink this library
        '@react-native-community/datetimepicker': {
          root: __dirname,
        },
        'expo': {
          // otherwise RN cli will try to autolink expo
          platforms: {
            ios: null,
            android: null,
          },
        },
      }
      : undefined),
  },
  ...(project ? {project} : undefined),
};
