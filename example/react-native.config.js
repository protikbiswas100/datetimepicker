const path = require('path');

module.exports = {
  project: {
    ios: {
      sourceDir: 'ios',
    },
    android: {
      sourceDir: 'android',
    },
    windows: {
      sourceDir: 'windows',
      solutionFile: 'date-time-picker-example.sln',
      projectFile: path.join('DateTimePickerDemo', 'DateTimePickerDemo.vcxproj'),
    },
  },
  dependencies: {
    '@react-native-community/datetimepicker': {
      root: path.join(__dirname, '..'),
    },
  },
};

