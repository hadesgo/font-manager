const { getAvailableFontsSync } = require('bindings')('fontmanager.node');
const util = require('util')

console.log(util.inspect(getAvailableFontsSync()))