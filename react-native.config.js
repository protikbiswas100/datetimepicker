const fs = require('fs');
const path = require('path');

// Check if we have an example windows project
const exampleWindowsSln = path.join(__dirname, 'example', 'windows', 'DateTimePickerDemo.sln');
const hasExampleWindows = fs.existsSync(exampleWindowsSln);

module.exports = {
  dependency: {
    platforms: {
      windows: {
        sourceDir: 'windows',
        solutionFile: 'DateTimePickerWindows.sln',
        projects: [
          {
            projectFile: 'DateTimePickerWindows\\DateTimePickerWindows.vcxproj',
            directDependency: true,
          },
        ],
      },
    },
  },
  dependencies: {
    ...(hasExampleWindows
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
  ...(hasExampleWindows ? {
    project: {
      android: {
        sourceDir: path.join('example', 'android'),
      },
      ios: {
        sourceDir: path.join('example', 'ios'),
      },
      windows: {
        sourceDir: path.join('example', 'windows'),
        solutionFile: 'DateTimePickerDemo.sln',
        project: {
          projectFile: path.join('DateTimePickerDemo', 'DateTimePickerDemo.vcxproj'),
        },
      },
    },
  } : undefined),
};
